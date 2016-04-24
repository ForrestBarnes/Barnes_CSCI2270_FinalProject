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
            <<"5. Remove Employee\n"
            <<"6. Move Employee\n"
            <<"7. Quit"<<endl;
        // Declares a MainMenu string to take input
        string MainMenu;
        getline(cin, MainMenu);
        // Takes only the first character of the input
        MainMenu = MainMenu.substr(0,1);
        // Checks that first character against possible values
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
            run = false;
        }
    }
    cout<<"Goodbye!\n";
    return 0;
}
