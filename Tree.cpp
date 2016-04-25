#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Tree.h"

using namespace std;

Tree::Tree(){
    makeCEO();
};

Tree::~Tree(){
    deleteEverything(CEO);
};

void Tree::addPerson(string name, string boss){
    name = removeWhitespace(name);
    if(acceptableName(name, CEO)){
        node* bossNode = findNode(boss);
        if(bossNode==NULL){
            cout<<"Could not find boss. Make sure name is spelled correctly."<<endl;
        }
        else{
            edge* newEdge = new edge(new node(name, bossNode));
            if(bossNode->employees==NULL){
                bossNode->last = bossNode->employees = newEdge;
            }
            else{
                bossNode->last = bossNode->last->next = newEdge;
            }
            newEdge->n->boss = bossNode;
        }
    }
};

void Tree::changeGroup(std::string person_name, std::string newGroup){
    node* person = findNode(person_name);
    if(person==NULL){
        cout<<"Could not find employee. Make sure name is spelled correctly."<<endl;
        return;
    }
    if(person==CEO){
        cout<<"You cannot change the CEO's group."<<endl;
        return;
    }
    person->group = newGroup;
    if(person->employees!=NULL){
        string yesNo;
        cout<<"Change the group of all people who report to this person? (y/n)"<<endl;
        getline(cin, yesNo);
        if(yesNo.length()>0 && (yesNo[0]=='y' || yesNo[0]=='Y')){
            recursiveGroupChange(person, newGroup);
        }
    }
};

void Tree::exportTree(std::string fileName){
    ofstream file;
    file.open(fileName);
    file.clear();
    file<<CEO->name<<delim2;
    edge* printList = new edge(CEO);
    edge* endofList = printList;
    while(printList!=NULL){
        edge* employee = printList->n->employees;
        while(employee!=NULL){
            endofList->next = new edge(employee->n);
            employee = employee->next;
            endofList = endofList->next;
        }
        if(printList->n!=CEO){
            file<<printList->n->name<<delim<<printList->n->boss->name<<delim;
            if(printList->n->group!=printList->n->boss->group){
                file<<printList->n->group;
            }
            file<<delim2;
        }
        edge* next = printList->next;
        delete printList;
        printList = next;
    }
    file.close();
};

void Tree::importTree(std::string fileName){
    ifstream file;
    file.open(fileName);
    if(!file.is_open()){
        cout<<"File not found."<<endl;
        return;
    }
    string line;
    cout<<"Are you sure you want to delete this structure and import a new one? (y/n)"<<endl;
    getline(cin, line);
    if(line.length()>0 && (line[0]=='y' || line[0]=='Y')){
        string errorMsg = "File is corrupt. No changes made.";
        getline(file, line, delim2);
        if(!acceptableName(line, NULL)){
            cout<<errorMsg<<endl;
            return;
        }
        node* newCEO = new node(line, NULL);
        while(!file.eof()){
            getline(file, line, delim2);
            if(line.length()>0){
                stringstream linestream(line);
                string name;
                getline(linestream, name, delim);
                if(!acceptableName(name, newCEO)){
                    cout<<errorMsg<<endl;
                    deleteEverything(newCEO);
                    return;
                }
                string bossName;
                getline(linestream, bossName, delim);
                node* boss = findNode(bossName, newCEO);
                if(boss==NULL){
                    cout<<errorMsg<<endl;
                    deleteEverything(newCEO);
                    return;
                }
                edge* newEdge = new edge(new node(name, boss));
                if(boss->employees==NULL){
                    boss->last = boss->employees = newEdge;
                }
                else{
                    boss->last = boss->last->next = newEdge;
                }
                newEdge->n->boss = boss;
                getline(linestream, bossName);
                if(bossName.length()>0){
                    findNode(name, newCEO)->group = bossName;
                }
            }
        }
        deleteEverything(CEO);
        CEO = newCEO;
    }
    file.close();
};

void Tree::movePerson(string person_name, string newBoss){
    node* person = findNode(person_name);
    if(person==NULL){
        cout<<"Could not find employee. Make sure name is spelled correctly."<<endl;
        return;
    }
    node* boss = findNode(newBoss);
    if(boss==NULL){
        cout<<"Could not find new boss. Make sure name is spelled correctly."<<endl;
        return;
    }
    movePerson(person, boss);
};

void Tree::movePersonAndEmployees(std::string person_name, std::string newBoss){
    node* person = findNode(person_name);
    if(person==NULL){
        cout<<"Could not find this person. "
            <<"Make sure name is spelled correctly."<<endl;
        return;
    }
    if(findNode(newBoss, person)!=NULL){
        cout<<newBoss<<" reports to "<<person_name
            <<", making this move impossible."<<endl;
        return;
    }
    node* boss = findNode(newBoss);
    if(boss==NULL){
        cout<<"Could not find boss. "
            <<"Make sure name is spelled correctly."<<endl;
        return;
    }
    edge* thisPerson = person->boss->employees;
    if(thisPerson->n==person){
        person->boss->employees = thisPerson->next;
        if(person->boss->employees==NULL){
            person->boss->last = NULL;
        }
    }
    else{
        while(thisPerson->next->n!=person){
            thisPerson = thisPerson->next;
        }
        edge* temp = thisPerson->next;
        thisPerson->next = temp->next;
        if(person->boss->last==temp){
            person->boss->last = thisPerson;
        }
        thisPerson = temp;
    }
    thisPerson->next = NULL;
    if(boss->employees==NULL){
        boss->employees = boss->last = thisPerson;
    }
    else{
        boss->last = boss->last->next = thisPerson;
    }
    person->boss = boss;
};

void Tree::personInfo(string person_name){
    cout<<personInfo(findNode(person_name))<<endl;
};

string Tree::printOrgStructure(){
    string returnString;
    edge* printList = new edge(CEO);
    edge* endofList = printList;
    while(printList!=NULL){
        edge* employee = printList->n->employees;
        while(employee!=NULL){
            endofList->next = new edge(employee->n);
            employee = employee->next;
            endofList = endofList->next;
        }
        returnString = returnString.append(personInfo(printList->n)).append("\n\n");
        edge* next = printList->next;
        delete printList;
        printList = next;
    }
    return returnString.substr(0, returnString.length()-1);
};

void Tree::promotePerson(string person_name){
    node* person = findNode(person_name);
    if(person==NULL){
        cout<<"Could not find employee. Make sure name is spelled correctly."<<endl;
        return;
    }
    if(person==CEO){
        cout<<"You cannot promote the CEO."<<endl;
        return;
    }
    if(person->boss==CEO){
        string CEO_name = CEO->name;
        CEO->name = person->name;
        person->name = CEO_name;
        if(person!=CEO->employees->n){
            edge* empl = CEO->employees;
            while(empl->next->n!=person){
                empl = empl->next;
            }
            edge* exCEO = empl->next;
            empl->next = exCEO->next;
            exCEO->next = CEO->employees;
            CEO->employees = exCEO;
            if(CEO->last = exCEO){
                CEO->last = empl;
            }
        }
    }
    else{
        edge* personEdge = person->boss->employees;
        if(personEdge->n==person){
            person->boss->employees = personEdge->next;
            if(person->boss->employees==NULL){
                person->boss->last = NULL;
            }
        }
        else{
            edge* coworker = personEdge;
            while(coworker->next->n!=person){
                coworker = coworker->next;
            }
            personEdge = coworker->next;
            coworker->next = personEdge->next;
            personEdge->next = NULL;
        }
        person->boss = person->boss->boss;
        person->boss->last = person->boss->last->next = personEdge;
    }
};

void Tree::removePerson(string person_name){
    node* person = findNode(person_name);
    if(person==NULL){
        cout<<"Could not find this person. "
            <<"Make sure name is spelled correctly."<<endl;
        return;
    }
    delete removePerson(person);
};

bool Tree::acceptableName(string name, node* top){
    if(name.length()<2){
        cout<<"A name must include at least two characters."<<endl;
        return false;
    }
    if(findNode(name, top)!=NULL){
        cout<<"This name already exists in the organization. "
            <<"Please choose a different name."<<endl;
        return false;
    }
    for(int i = 0; i<name.length(); i++){
        int ascii = int(name[i]);
        // Makes sure the character is a space, a dash, or alphanumeric.
        if(!(ascii==32 || ascii==45 || (ascii>47 && ascii<58)
                   || (ascii>64 && ascii<91) || (ascii>96 && ascii<123))){
            cout<<"Names can only have spaces, dashes,"
                <<"and alphanumeric characters."<<endl;
            return false;
        }
    }
    return true;
};

void Tree::deleteEverything(node* top){
    if(top!=NULL){
        edge* deleteList = top->employees;
        delete top;
        edge* endList = deleteList;
        while(endList!=NULL && endList->next!=NULL){
            endList = endList->next;
        }
        while(deleteList!=NULL){
            endList->next = deleteList->n->employees;
            while(endList->next!=NULL){
                endList = endList->next;
            }
            edge* next = deleteList->next;
            delete deleteList->n;
            delete deleteList;
            deleteList = next;
        }
    }
};

node* Tree::findNode(string name){
    return findNode(name, CEO);
};

node* Tree::findNode(string name, node* person){
    if(person==NULL || person->name==name){
        return person;
    }
    else{
        edge* empl = person->employees;
        while(empl!=NULL){
            //cout<<name<<endl;
            node* toReturn = findNode(name, empl->n);
            if(toReturn!=NULL){
                return toReturn;
            }
            empl = empl->next;
        }
        return NULL;
    }
};

void Tree::makeCEO(){
    string name;
    do{
        cout<<"Please enter the name of a CEO:"<<endl;
        getline(cin, name);
        name = removeWhitespace(name);
    }while(!acceptableName(name, NULL));
    CEO = new node(name, NULL);
};

void Tree::movePerson(node* person, node* boss){
    if(person->boss!=boss){
        removePerson(person);
        person->boss = boss;
        if(boss->employees==NULL){
            boss->last = boss->employees = new edge(person);
        }
        else{
            boss->last = boss->last->next = new edge(person);
        }
    }
};

string Tree::personInfo(node* person){
    if(person==NULL){
        return "Could not find Employee. Make sure name is spelled correctly.";
    }
    string returnString = string("Name: ").append(person->name);
    returnString.append("\nGroup: ").append(person->group).append("\nBoss: ");
    if(person->boss==NULL){
        returnString.append("N/A");
    }
    else{
        returnString.append(person->boss->name);
    }
    returnString.append("\nEmployees: ");
    if(person->employees==NULL){
        returnString.append("N/A");
    }
    else{
        edge* empl = person->employees;
        while(empl!=NULL){
            returnString.append(empl->n->name).append(", ");
            empl = empl->next;
        }
        returnString = returnString.substr(0, returnString.length()-2);
    }
    return returnString;
};

void Tree::recursiveGroupChange(node* person, string newGroup){
    person->group = newGroup;
    edge* empl = person->employees;
    while(empl!=NULL){
        recursiveGroupChange(empl->n, newGroup);
        empl = empl->next;
    }
};

node* Tree::removePerson(node* person){
    if(person==NULL){
        return person;
    }
    if(person==CEO){
        if(person->employees==NULL){
            makeCEO();
        }
        else{
            CEO = person->employees->n;
            if(person->employees->next!=NULL){
                person->last->next = CEO->employees;
                edge* temp = CEO->employees = person->employees->next;
                while(temp!=person->last->next){
                    temp->n->boss = CEO;
                    temp = temp->next;
                }
            }
            delete person->employees;
            person->last = person->employees = NULL;
            CEO->boss = NULL;
            CEO->group = person->group;
        }
        return person;
    }
    edge* coworker = person->boss->employees;
    if(coworker->n==person){
        coworker = coworker->next;
        delete person->boss->employees;
        if(coworker==NULL){
            coworker = person->boss->last = person->boss->employees = person->employees;
            while(coworker!=NULL){
                coworker->n->boss = person->boss;
                coworker = coworker->next;
            }
        }
        else{
            person->boss->employees = coworker;
        }
    }
    else{
        while(coworker->next->n!=person){
            coworker = coworker->next;
        }
        edge* next = coworker->next;
        coworker->next = next->next;
        if(person->boss->last==next){
            person->boss->last = coworker;
        }
        delete next;
        person->boss->last->next = person->employees;
        while(person->boss->last->next!=NULL){
            person->boss->last->n->boss = person->boss;
            person->boss->last = person->boss->last->next;
        }
    }
    person->boss = NULL;
    person->employees = NULL;
    return person;
};

string Tree::removeWhitespace(string str){
    while(str.length()>0 && str[0]==' '){
        str = str.substr(1, str.length());
    }
    while(str.length()>0 && str[str.length()-1]==' '){
        str = str.substr(0, str.length()-1);
    }
    return str;
};
