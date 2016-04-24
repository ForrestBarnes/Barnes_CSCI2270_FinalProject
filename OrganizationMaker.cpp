#include <string>
#include <iostream>
#include "Tree.h"

using namespace std;

int main(){
    Tree tree;
    bool run = true;
    while(run){
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
            <<"11. Quit"<<endl;
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
            cout<<tree.printOrgStructure()<<endl;
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
        else if(MainMenu=="11"){
            run = false;
        }
    }
    cout<<"Goodbye!\n";
    return 0;
}
