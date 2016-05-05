#include <string>
#include <iostream>
#include "Tree.h"

using namespace std;

int main(){
    Tree tree;
    while(true){
        cout<<"===========Main Menu===========\n"
            <<"1. Add an Employee\n"
            <<"2. Get Employee Info\n"
            <<"3. Print Organization Structure\n"
            <<"4. Promote Employee\n"
            <<"5. Remove Person\n"
            <<"6. Move Person\n"
            <<"7. Move Person and all employees\n"
            <<"8. Export to file\n"
            <<"9. Import from file\n"
            <<"10. Change group\n"
            <<"11. Rename Company\n"
            <<"12. Quit"<<endl;
        // Declares a MainMenu string to take input
        string MainMenu;
        getline(cin, MainMenu);
        if(MainMenu=="1"){
            cout<<"Enter name:"<<endl;
            getline(cin, MainMenu);
            string bossName;
            cout<<"Enter boss's name:"<<endl;
            getline(cin, bossName);
            tree.addPerson(MainMenu, bossName);
        }
        else if(MainMenu=="2"){
            cout<<"Enter name:"<<endl;
            getline(cin, MainMenu);
            tree.personInfo(MainMenu);
        }
        else if(MainMenu=="3"){
            tree.printOrgStructure();
        }
        else if(MainMenu=="4"){
            cout<<"Enter name:"<<endl;
            getline(cin, MainMenu);
            tree.promotePerson(MainMenu);
        }
        else if(MainMenu=="5"){
            cout<<"Enter name:"<<endl;
            getline(cin, MainMenu);
            tree.removePerson(MainMenu);
        }
        else if(MainMenu=="6"){
            cout<<"Enter name:"<<endl;
            getline(cin, MainMenu);
            string bossName;
            cout<<"Enter new boss's name:"<<endl;
            getline(cin, bossName);
            tree.movePerson(MainMenu, bossName);
        }
        else if(MainMenu=="7"){
            cout<<"Enter name:"<<endl;
            getline(cin, MainMenu);
            string bossName;
            cout<<"Enter new boss's name:"<<endl;
            getline(cin, bossName);
            tree.movePersonAndEmployees(MainMenu, bossName);
        }
        else if(MainMenu=="8"){
            cout<<"Enter file name:"<<endl;
            getline(cin, MainMenu);
            tree.exportTree(MainMenu);
        }
        else if(MainMenu=="9"){
            cout<<"Enter file name:"<<endl;
            getline(cin, MainMenu);
            tree.importTree(MainMenu);
        }
        else if(MainMenu=="10"){
            cout<<"Enter name:"<<endl;
            getline(cin, MainMenu);
            string groupName;
            cout<<"Enter new group name:"<<endl;
            getline(cin, groupName);
            tree.changeGroup(MainMenu, groupName);
        }
        else if(MainMenu=="11"){ //added feature
            tree.companyNameChange();
        }
        else if(MainMenu=="12"){
            cout<<"Goodbye!\n";
            return 0;
        }
    }
}

//----------------------------------------------------------------------
//------------------------Added Features--------------------------------
//          -OrganizationMaker.cpp
//              - Line 86       change company name option
//          - Tree.h
//              - Line 58       added company name change function
//              - Line 72       added company name variable
//          - Tree.cpp
//              - Line 10       input for company name
//              - Line 103      added company name to export function
//              - Line 144-146, added company name changer to import file
//                     196
//              - Line 285-286  prints company name with organization structure
//              - Line 620-623  company name change function
