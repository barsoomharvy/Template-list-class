#include <iostream>
using namespace std;

#include "list.h"
#include "nodedata.h"
#include "employee.h"

//---------------------- testCopyConstructor --------------------------------
// Not a member function, pass by value forces a copy to be made.
// After makeEmpty, the pass by reference list will be empty, while
// the pass by value list will be the original list as in main.
// Also tests destructor behind the scenes.
//---------------------------------------------------------------------------

template <typename Object>
void testCopyConstructor(List<Object>& byRefList, List<Object> byValList) {
   cout << "Test Copy Constructor and Destructor" << endl;
   cout << "------------------------------------" << endl;
   byRefList.makeEmpty();
   cout << "after emptying, byRefList is: " << endl << byRefList << endl;
   cout << "byValList is: " << endl << byValList << endl;
}

int main() {
   // list of NodeData, to be sorted by numerical value, then char
   List<NodeData> mylist, mylist2, mylist3;
   NodeData* p = new NodeData(20, 'n');  mylist.insert(p);
   p = new NodeData(10, 'f');  mylist.insert(p);
   p = new NodeData(16, 'u');  mylist.insert(p);
   p = new NodeData(25, '!');  mylist.insert(p);

   p = new NodeData(16, 'u');  mylist2.insert(p);
   p = new NodeData(15, 't');  mylist2.insert(p);
   p = new NodeData(19, 'f');  mylist2.insert(p);
   p = new NodeData(14, 's');  mylist2.insert(p);
   p = new NodeData(25, '!');  mylist2.insert(p);
   p = new NodeData(18, 'f');  mylist2.insert(p);
   cout << "mylist:" << endl << mylist << endl;
   cout << "mylist2:" << endl << mylist2 << endl;
   mylist3.intersect(mylist, mylist2);
   cout << "mylist3:" << endl << mylist3 << endl;

//    Many lists of employees,
//    to be sorted alphabetically by last name, then first.
//    Vary the data files to test your list code.
   bool success;
   Employee* oneEmployee;
   List<Employee> company1, company2, company3, company4, company5, company6,
                  company7, company8, company9, company10, company11;
   ifstream infile1("data31.txt"), infile2("data32.txt"),
            infile3("data33.txt"), infile4("data34.txt");

   company1.buildList(infile1);
   company2.buildList(infile2);
   company3.buildList(infile3);
   company4.buildList(infile4);
   company5 = company1;
   company6 = company2;
   company7 = company3;
   company8 = company4;


    company1.merge(company3, company2);
    cout<<company1 << endl<< endl;
    cout<<company2 << endl<< endl;
    company1.merge(company1, company1);
    company5.merge(company6, company7);
    company1.merge(company2, company3);
    company1.merge(company2, company11);
   cout<<company1 << endl<< endl;
    company2.intersect(company1, company4);
    company5.intersect(company3, company6);

    company10.intersect(company3, company9);

    company8.intersect(company1, company6);

//    company2.intersect(company1, company11);
//    company9.intersect(company11, company7);
//    company10.intersect(company5, company8);
//
//    company11.intersect(company1, company4);
//
//

    company2.merge(company3, company1);
    company11.merge(company11, company11);
    company11.merge(company11, company8);
    company3.merge(company4, company8);
    company6.merge(company8, company8);
    cout<<company3 << endl<< endl;
    cout<<company5 << endl<< endl;
    cout<<company11 << endl<< endl;


//
   cout << "test -- merge 1 and 2 into 5" << endl;
   cout << "----------------------------" << endl;
   cout << "Company1:" << endl << company1 << endl;
   cout << "Company2:" << endl << company2 << endl;
   company5.merge(company3, company2);
    company1.merge(company5, company5);
   cout << "company1 is " << (company1.isEmpty() ? "empty" : "not empty")
        << endl;
   cout << "company2 is " << (company2.isEmpty() ? "empty" : "not empty")
        << endl;
    cout<< company5 << endl;
   cout << "Company11:" << endl << company1 << endl;

   cout << "test == " << endl;
   cout << "--------" << endl;
   Employee emp1("Harry", "smith");      // last name, first name
   Employee emp2("jason", "edward");
   // knows emp1 and emp2 are in the lists, so deletes without checking
    cout << "Company10:" << endl << company11 << endl;
    cout << "Company11:" << endl << company11 << endl;
    cout << "company10 " << (company11 == company11 ? "equals":"does not equal")
    << " company11" << endl;

   cout << "Company10:" << endl << company10 << endl;
   cout << "Company11:" << endl << company11 << endl;
   cout << "company10 " << (company10 == company11 ? "equals":"does not equal")
        << " company11" << endl;
   cout << "Company11:" << endl << company11 << endl;
   cout << "company10 " << (company10 == company11 ? "equals":"does not equal")
        << " company11" << endl;


   cout << "test == and !=: merge 7 and 8 into 9 (same as 5)" << endl;
   cout << "------------------------------------------------" << endl;
   cout << "Company7:" << endl << company7 << endl;
   cout << "Company8:" << endl << company8 << endl;
   company9.merge(company8, company7);
   cout << "Company9:" << endl << company9 << endl;
   cout << "company7 " << (company7 == company9 ? "equals" : "does not equal")
        << " company7" << endl;
   cout << "company7 " << (company9 != company9 ? "does not equal" : "equals")
        << " company7" << endl;

//    note after merge, 3 is empty, 4 is merged 3 and 4
   cout << "test -- merge 3 and 4 into 4" << endl;
   cout << "----------------------------" << endl;
   cout << "Company3:" << endl << company3 << endl;
   cout << "Company4:" << endl << company4 << endl;
   company4.merge(company3, company4);
   cout << "company3 is " << (company3.isEmpty() ? "empty" : "not empty")
        << endl;
   cout << "Company4:" << endl << company4 << endl;

   cout << "test -- merge empty 3 and 4 into 4, no change to 4" << endl;
   cout << "--------------------------------------------------" << endl;
   cout << "Company3:" << endl << company3 << endl;
   cout << "Company4:" << endl << company4 << endl;
   company4.merge(company3, company4);
   cout << "company3 is " << (company3.isEmpty() ? "empty" : "not empty")
        << endl;
   cout << "Company4 again (same):" << endl << company4 << endl;

   cout << "test -- merge 4 and empty 3 into 4, no change to 4" << endl;
   cout << "--------------------------------------------------" << endl;
   company4.merge(company4, company3);
   cout << "company3 is " << (company3.isEmpty() ? "empty" : "not empty")
        << endl;
   cout << "Company4 again (same):" << endl << company4 << endl;

   cout << "test -- merge 6 and empty 3 into 4" << endl;
   cout << "----------------------------------" << endl;
   company4.merge(company6, company3);
   cout << "company3 is " << (company3.isEmpty() ? "empty" : "not empty")
        << endl;
   cout << "company6 is " << (company6.isEmpty() ? "empty" : "not empty")
        << endl;
   cout << "Company4:" << endl << company4 << endl;

   cout << "test remove and retrieve on 4" << endl;
   cout << "-----------------------------" << endl;
   Employee emp3("Andrew", "Jackson");
   Employee emp4("Peter", "Hawkins");
   success = company4.retrieve(emp3, oneEmployee);
   if (success) cout << "Found in list:  " << *oneEmployee << endl;
   else         cout << "Did not find andrew in list" << endl;
   success = company4.retrieve(emp4, oneEmployee);
   if (success) cout << "Found in list:  " << *oneEmployee << endl;
   else         cout << "Did not find peter in list" << endl;
   Employee emp5("Verena", "George");
   Employee emp6("David", "Edward");
   Employee emp7("Thomas", "Edison");
   success = company4.remove(emp5, oneEmployee);
   if (success) {
      cout << "Removed:  " << *oneEmployee << endl;
      delete oneEmployee;                          // could insert elsewhere
   }
   else
      cout << "Did not find verena in list" << endl;
   success = company4.remove(emp6, oneEmployee);
   if (success) {
      cout << "Removed:  " << *oneEmployee << endl;
      delete oneEmployee;
   }
   else
      cout << "Did not find rella in list" << endl;
   success = company4.remove(emp7, oneEmployee);
   if (success) {
      cout << "Removed:  " << *oneEmployee << endl;
      delete oneEmployee;
   }
   else
      cout << "Did not find bear in list" << endl;
   cout << "Company4 after removes:" << endl << company4 << endl;

//   testCopyConstructor(company4, company4);
//   cout << "back in main, Company10:" << endl << company10 << endl;
    
    return 0;

}


