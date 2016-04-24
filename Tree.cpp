#include <iostream>
#include <string>
#include "Tree.h"

using namespace std;

Tree::Tree(){
    makeCEO();
};

Tree::~Tree(){
    if(CEO!=NULL){
        edge* deleteList = CEO->employees;
        delete CEO;
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

void Tree::addPerson(string name, string boss){
    name = removeWhitespace(name);
    if(acceptableName(name)){
        node* bossNode = findNode(boss);
        if(bossNode==NULL){
            cout<<"Could not find boss. Make sure name is spelled correctly."<<endl;
        }
        else{
            edge* emplList = bossNode->employees;
            edge* newEdge = new edge(new node(name, bossNode));
            if(emplList==NULL){
                bossNode->employees = newEdge;
            }
            else{
                while(emplList->next!=NULL){
                    emplList = emplList->next;
                }
                emplList->next = newEdge;
            }
            newEdge->n->boss = bossNode;
        }
    }
};

void Tree::changeGroup(std::string person_name, std::string newGroup){
    //
};

void Tree::exportTree(std::string fileName){
    //
};

void Tree::importTree(std::string fileName){
    //
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
    //
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
        }
    }
    else{
        edge* personEdge = person->boss->employees;
        edge* newCoworker = person->boss->boss->employees;
        while(newCoworker->next!=NULL){
            newCoworker = newCoworker->next;
        }
        if(personEdge->n==person){
            person->boss->employees = personEdge->next;
        }
        else{
            edge* coworker = personEdge;
            while(coworker->next->n!=person){
                coworker = coworker->next;
            }
            personEdge = coworker->next;
            coworker->next = personEdge->next;
        }
        newCoworker->next = personEdge;
        person->boss = person->boss->boss;
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

bool Tree::acceptableName(string name){
    if(name.length()<2){
        cout<<"A name must include at least two characters."<<endl;
        return false;
    }
    if(findNode(name)!=NULL){
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
    }while(!acceptableName(name));
    CEO = new node(name, NULL);
};

void Tree::movePerson(node* person, node* boss){
    if(person->boss!=boss){
        removePerson(person);
        person->boss = boss;
        if(boss->employees==NULL){
            boss->employees = new edge(person);
        }
        else{
            edge* empl = boss->employees;
            while(empl->next!=NULL){
                empl = empl->next;
            }
            empl->next = new edge(person);
        }
    }
};

string Tree::personInfo(node* person){
    if(person==NULL){
        return "Could not find Employee. Make sure name is spelled correctly.";
    }
    string returnString = string("Name: ").append(person->name).append("\nBoss: ");
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

node* Tree::removePerson(node* person){
    if(person==NULL){
        return person;
    }
    if(person==CEO){
        if(person->employees==NULL){
            CEO = NULL;
            makeCEO();
        }
        else{
            CEO = person->employees->n;
            if(person->employees->next!=NULL){
                edge* lowerEmployees = CEO->employees;
                edge* lastHighEmployee = CEO->employees = person->employees->next;
                while(lastHighEmployee->next!=NULL){
                    lastHighEmployee->n->boss = CEO;
                    lastHighEmployee = lastHighEmployee->next;
                }
                lastHighEmployee->n->boss = CEO;
                lastHighEmployee->next = lowerEmployees;
            }
            delete person->employees;
            person->employees = NULL;
            CEO->boss = NULL;
        }
        return person;
    }
    edge* coworker = person->boss->employees;
    if(coworker->n==person){
        coworker = coworker->next;
        delete person->boss->employees;
        if(coworker==NULL){
            coworker = person->boss->employees = person->employees;
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
        delete next;
    }
    if(coworker!=NULL){
        while(coworker->next!=NULL){
            coworker = coworker->next;
        }
        coworker = coworker->next = person->employees;
        while(coworker!=NULL){
            coworker->n->boss = person->boss;
            coworker = coworker->next;
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
