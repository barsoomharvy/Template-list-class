/////////////////////////  listtemplate.h file  //////////////////////////////
// Simple linked list, uses Node as linked list node

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <fstream>
using namespace std;

//--------------------------  class List  ------------------------------------
// ADT List: finite, ordered collection of zero or more items.
//           The ordering is determined by operator< of T class.
//
// Assumptions:
//   -- Control of <, printing, etc. of T information is in the T class.
//   -- There is no dummy head node, head points to first node.
//      If the list is empty, head is NULL.
//   -- The insert allocates memory for a Node, ptr to the data is passed in.
//      Allocating memory and setting data is the responsibility of the caller.
//
// Note this definition is not a complete class and is not fully documented.
//----------------------------------------------------------------------------

template <typename T>
class List {

   // output operator for class List, print data,
   // responsibility for output is left to object stored in the list
   friend ostream& operator<<(ostream& output, const List<T>& thelist) {
      typename List<T>::Node* current = thelist.head;
      while (current != NULL) {
         output << *current->data;
         current = current->next;
      }
      return output;
}

public:
   List();                                  // default constructor
   ~List();                                 // destructor
   List(const List&);                       // copy constructor
   List& operator=(const List&);            // assigns the param list to global.
   bool operator==(const List&) const;      // Checks if 2 lists are equal
   bool operator!=(const List&) const;      // Checks if 2 lists are not equal
   bool insert(T*);                         // insert one Node into list
   bool remove(const T&, T*&);              // removes the given node from the
                                            //list
   bool retrieve(const T&, T*&) const;      // Retrieves the given data
   bool isEmpty() const;                    // is list empty?
   void buildList(ifstream&);               // build a list from datafile
   void merge(List&, List&);                // merges 2 lists together leaving
                                            // the given ones empty.
   void intersect(List&, List&);            //finds in common data in both
                                            //lists leaving both unchanged.
   void copy(const List&);                  // copy method used in copy Cnst &
                                            //operator=
   void makeEmpty();                        // deletes memory of object.

   // needs many more member functions to become a complete ADT

private:
   struct Node {            // the node in a linked list
      T* data;              // pointer to actual data, operations in T
      Node* next;
   };

   Node* head;              // pointer to first node in list
};


//----------------------------------------------------------------------------
// Constructor
template <typename T>
List<T>::List() {
   head = NULL;
}

//----------------------------------------------------------------------------
//Destructor
template <typename T>
List<T>::~List()
{
    makeEmpty();
}

//----------------------------------------------------------------------------
//Copy Constructor
template <typename T>
List<T>::List(const List& list)
{
    copy(list);
}

//----------------------------------------------------------------------------
//Operator=
template <typename T>
List<T>& List<T>::operator=(const List& list)
{
    
    if (this != &list)
    {
        //deleting object so it is reassigned assignList
        makeEmpty();
        if (list.head != NULL)
            copy(list);
    }
    
    return *this;
}

//----------------------------------------------------------------------------
//operator==
//checks if 2 lists are equal
template <typename T>
bool List<T>::operator==(const List& list) const
{
    if (isEmpty() || list.isEmpty())
        return false;
    //if calling object is the parameter
    if (this == &list)
        return true;
    
    Node* cur = head;
    Node* cur2 = list.head;
    
    //going until one or both lists aren't null
    while (cur != NULL && cur2 != NULL)
    {
        //returning false if not equal
        if (*cur->data != *cur2->data)
            return false;
        
        //next pointer in curs
        cur = cur->next;
        cur2 = cur2->next;
    }
    //if both are null, it means that the lists are equal and we return true.
    if (cur == NULL && cur2 == NULL)
        return true;
    
    return false;
}

//----------------------------------------------------------------------------
//operator!=
//checks if 2 lists are not equal
template <typename T>
bool List<T>::operator!=(const List& list) const
{
    return !operator==(list);
}

//----------------------------------------------------------------------------
// insert
// insert an item into list; operator< of the T class
// has the responsibility for the sorting criteria
template <typename T>
bool List<T>::insert(T* dataptr) {

   Node* ptr= new Node;
   if (ptr == NULL) return false;                 // out of memory, bail
   ptr->data = dataptr;                           // link the node to data

   // if the list is empty or if the node should be inserted before
   // the first node of the list
   if (isEmpty() || *ptr->data < *head->data) {
      ptr->next = head;
      head = ptr;
   }
     
   // then check the rest of the list until we find where it belongs
   else {
      Node* current = head->next;          // to walk list
      Node* previous = head;               // to walk list, lags behind

      // walk until end of the list or found position to insert
      while (current != NULL && *current->data < *ptr->data) {
            previous = current;                  // walk to next node
            current = current->next;
      }

      // insert new node, link it in
      ptr->next = current;
      previous->next = ptr;
   }
   return true;
}

//----------------------------------------------------------------------------
//remove
//removes the given node from the list and returns true
template<typename T>
bool List<T>::remove(const T& target, T*& p)
{
    if (isEmpty())
        return false;
    
    //checking if the head is the target value
    if (*head->data == target)
    {
        p = head->data; //setting the data to p and the walking had to delete the node.
        Node* temp = head;
        head = head->next;
        
        if (temp->data != NULL)
            delete temp->data;
        
        delete temp;
        return true;
    }
    
    Node* cur = head;
    
    while (cur->next != NULL) //walking the next so we change the next to the node after
    {                         //the one we want to remove.
        if (*cur->next->data == target)
        {
            p = cur->next->data;
            Node* temp = cur->next;
            cur->next = cur->next->next;
            //data could be null.
            if (temp->data != NULL)
                delete temp->data;
            
            delete temp;
            return true;
        }
        
        cur = cur->next;
    }
    //if target isn't found, p is null and then return false.
    p = NULL;
    return false;
}

//----------------------------------------------------------------------------
//retrieve
//retrieves a given target without deleting it from the list
template <typename T>
bool List<T>::retrieve(const T& target, T*& p) const
{
    if (isEmpty())
        return false;
    
    Node* cur = head;
    //going until node is found and returning.
    while (cur != NULL)
    {
        if (*cur->data == target)
        {
            p = cur->data;
            return true;
        }
        
        cur = cur->next;
    }
    //if target isn't found, set p to null and then return false.
    p = NULL;
    return false;
}

//----------------------------------------------------------------------------
// isEmpty
// check to see if List is empty as defined by a NULL head
template <typename T>
bool List<T>::isEmpty() const {
   return head == NULL;
}

//----------------------------------------------------------------------------
// buildList
// continually insert new items into the list
template <typename T>
void List<T>::buildList(ifstream& infile) {
   T* ptr;
   bool successfulRead;                            // read good data
   bool success;                                   // successfully insert
   for (;;) {
      ptr = new T;
      successfulRead = ptr->setData(infile);       // fill the T object
      if (infile.eof()) {
         delete ptr;
         break;
      }

      // insert good data into the list, otherwise ignore it
      if (successfulRead) {
         success = insert(ptr);
      }
      else {
         delete ptr;
      }
      if (!success) break;
   }
}

//----------------------------------------------------------------------------
//merge method
//merges 2 lists together and leaves them empty
template <typename T>
void List<T>::merge(List& list1, List& list2)
{
    if (this == &list1 && this == &list2)
        return;
    
    //When both lists are empty, we make object empty and return.
    if (list1.isEmpty() && list2.isEmpty())
    {
        makeEmpty();
        return;
    }
    
    
    //if one of the lists is empty and the object is the other list, there's
    //nothing to merge, and we just return.
    if ((list1.isEmpty() && this == &list2) ||
       (list2.isEmpty() && this == &list1))
    {
        return;
    }

    //if the 1st list is empty, and the object isn't 2nd list, we makeEmpty
    //on the object, and copy list2 to object, then set to NULL
    if (list1.isEmpty())
    {
        *this = list2;
        list2.makeEmpty();
        return;
    }
    //Same check as previous if statement but switch params.
    if (list2.isEmpty())
    {
        *this = list1;
        list1.makeEmpty();
        return;
    }
    //if the parameters are the same, we make empty the object, and set it to one of
    //the lists since they're same and no merge is one of them.
    if(list1 == list2)
    {
        makeEmpty();
        *this = list1;
        list1.makeEmpty();
        list2.makeEmpty();
        return;
    }
    
    Node* fakeHead;

    //checking the data of cur with cur2 if it's less or equal since there
    //could be duplicates.
    if (*list1.head->data <= *list2.head->data)
    {
        //setting fakehead to cur and then giving fakehead a next pointer
        //setting it to null and traversing it as well as cur.
        fakeHead = list1.head;
        list1.head = list1.head->next;
        fakeHead->next = NULL;
    }
    //same logic as previous if statement. Using else if statement so it is
    //skipped if there are duplicates
    else if (*list2.head->data < *list1.head->data)
    {
        fakeHead = list2.head;
        list2.head = list2.head->next;
        fakeHead->next = NULL;
    }
    
    
    //pointer to fakeHead to traverse and setting the next.
    Node* p = fakeHead;
    Node* cur = list1.head;
    Node* cur2 = list2.head;
    
    while (cur != NULL && cur2 != NULL)
    {
        if (*cur->data <= *cur2->data)
        {
            //starting at p->next since p points to fakeHead which has one node
            //already. Then we traverse so it's pointing to it.
            p->next = cur;
            p = p->next;
            cur = cur->next;
        }
        
        else if (*cur2->data < *cur->data)
        {
            p->next = cur2;
            p = p->next;
            cur2 = cur2->next;
        }
    }
    
    //if cur was null and cur2 still wasn't then traversing through cur2
    //with the same logic as in the loop.
    if (cur == NULL)
    {
        while (cur2 != NULL)
        {
            p->next = cur2;
            p = p->next;
            cur2 = cur2->next;
        }
    }
    //Same as previous check but with other list. If the lists have the same
    //amount of nodes, both if statements are skipped.
    if (cur2 == NULL)
    {
        while (cur != NULL)
        {
            p->next = cur;
            p = p->next;
            cur = cur->next;
        }
    }
    //emptying object so we set it to fakeHead
    makeEmpty();
    //leaving the parameters' head to null
    list1.head = NULL;
    list2.head = NULL;
    head = fakeHead;

}

//----------------------------------------------------------------------------
//intersect method
//finds common data in 2 lists and adds to object.
template <typename T>
void List<T>::intersect(List& list1, List& list2)
{
    //when both lists are empty, there is no intersection, so we return.
    if (list1.isEmpty() || list2.isEmpty())
    {
        makeEmpty(); //since both lists are empty, calling object holds
                     //nothing.
        return;
    }
    //if the object is both parameters, the intersection is already set.
    if (this == &list1 && this == &list2)
        return;
    
    //when object is one of the params, and the other is null, no need to
    //intersect so we return.
    if (this == &list1 && list2.isEmpty())
    {
        makeEmpty();
        return;
    }
    //same logic as previous if but switched.
    if (this == &list2 && list1.isEmpty())
    {
        makeEmpty();
        return;
    }
    
    Node* fakeHead;
    Node* cur = list1.head;
    Node* cur2 = list2.head;
    
    //iterating until both are null since after one is null, there is no more intersections
    while (cur != NULL && cur2 != NULL)
    {
        //dereferencing the datas and checking if they're equal, and creating a new node
        //for head and new Tsand setting it to the data of cur (same as cur2).
        //then walking the curs.
        if (*cur->data == *cur2->data)
        {
            fakeHead = new Node;
            fakeHead->data = new T;
            *fakeHead->data = *cur->data;
            fakeHead->next = NULL;
            cur = cur->next;
            cur2 = cur2->next;
            break;
        }
        
        if (*cur->data < *cur2->data)
        {
            cur = cur->next;
        }
        else //cur2's data is < cur's data
            cur2 = cur2->next;
    }
    
    if (fakeHead != NULL)
    {
        Node* p = fakeHead;
    
        while (cur != NULL && cur2 != NULL)
        {
            if (*cur->data == *cur2->data)
            {
                //starting with p's next since p is pointing to fakeHead which
                //should have one node already from previous loop.
                p->next = new Node;
                p = p->next;
                p->next = NULL;
                p->data = new T;
                *p->data = *cur->data;
                cur = cur->next;
                cur2 = cur2->next;
                continue;
            }
        
            if (*cur->data < *cur2->data)
            {
                cur = cur->next;
            }
            else //cur2's data is < cur's data
                cur2 = cur2->next;
        }
        
    }
    //setting the object empty so we assign it fakeHEad.
    makeEmpty();
    
    head = fakeHead;
}
//----------------------------------------------------------------------------
//copy method
//used in copy Constructor & operator=
template <typename T>
void List<T>::copy(const List& copy)
{
    //setting the head nodes first
    if (copy.head != NULL)
    {
        head = new Node;
        head->data = new T;
        *head->data = *copy.head->data;
    
        //cur pointing to head so we connect the next nodes using next.
        Node* cur = head;
        //already took care of first node so walking the list starting from second
        //node.
        Node* cur2 = copy.head->next;
    
        while (cur2 != NULL)
        {
            //creating a new node, setting the data to list's data and next to
            //null, then going to the next of both.
            cur->next = new Node;
            cur = cur->next;
            cur->data = new T;
            *cur->data = *cur2->data;
            cur->next = NULL;
            cur2 = cur2->next;

        }
    }
}

//----------------------------------------------------------------------------
//clear method
//used in destructor & operator=
template <typename T>
void List<T>::makeEmpty()
{
    while (head != NULL)
    {
        Node* temp = head;
        head = head->next;
    
        if (temp->data != NULL)
            delete temp->data;
        
        delete temp;
        temp = NULL;
    }
}
#endif
