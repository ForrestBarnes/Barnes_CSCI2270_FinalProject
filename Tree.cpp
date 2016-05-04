#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Tree.h"

using namespace std;

Tree::Tree(){
    companyNameChange();
    makeCEO();
};

Tree::~Tree(){
    deleteEverything(CEO);
};

/* Adds a person to the tree if the name is acceptable and the name
 * of their boss exists in the tree.
 */
void Tree::addPerson(string name, string boss){
    // First, remove all whitespace from the ends of the name.
    name = removeWhitespace(name);
    /* Make sure the name is okay (no copied names, no characters besides
     * alphanumerics, spaces, and dashes). If the name isn't okay, this
     * will print out an error explaining why.
     */
    if(acceptableName(name, CEO)){
        // Finds boss node in tree
        node* bossNode = findNode(boss);
        if(bossNode==NULL){
            cout<<"Could not find boss. Make sure name is spelled correctly."<<endl;
            return;
        }
        // Creates a new edge pointing to a new node with the right name and boss.
        addEdge(new edge(new node(name, bossNode)));
    }
};

// Changes the name of the group the person is in.
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
    if(newGroup.length()<1){
        cout<<"Group name must be at least one character long."<<endl;
        return;
    }
    /* This should technically never run, since delim2='\n', but it is worth double-checking.
     * This ensures any file exported by this program can still be properly imported again.
     */
    for(int i = 0; i<newGroup.length(); i++){
        if(newGroup[i]==delim2){
            cout<<"Character "<<i<<" in this group name is not allowed."<<endl;
            return;
        }
    }
    person->group = newGroup;
    if(person->employees!=NULL){
        string yesNo;
        cout<<"Change the group of all people who report to this person? (y/n)"<<endl;
        getline(cin, yesNo);
        /* If the user says yes to it, recursively change the group of all people
         * under this person in the organization.
         */
        if(yesNo.length()>0 && (yesNo[0]=='y' || yesNo[0]=='Y')){
            recursiveGroupChange(person, newGroup);
        }
    }
};

/* Exports the structure of the tree to a document. Document format is as follows:

CEO_name
mostSeniorEmployee,CEO_name,group
...
leastSeniorEmployee,boss,group

 * The file is output using BFS, but the importTree function can take either BFS
 * or DFS, so long as employees are always placed after their bosses in the document.
 * The group is left blank unless it is different from the group of the employee's boss.
 * The above example is using delim=',' and delim2='\n', but any set of delimiters besides
 * the dash and the space (which are used in the names of the people) can be used.
 */
void Tree::exportTree(std::string fileName){
    ofstream file;
    file.open(fileName.c_str());//c._str()
    if(!file.is_open()){
        cout<<"File failed to open. Nothing written."<<endl;
        file.close();
        return;
    }
    file.clear();
    // Creates a new linked list of all employees.
    edge* printList = new edge(CEO);
    edge* endofList = printList;
    file<<companyName<<delim2;//added feature
    while(printList!=NULL){
        // Finds the first employee of the current person
        edge* employee = printList->n->employees;
        // Iterates through the employees of the person, adding them to the linked list
        while(employee!=NULL){
            endofList = endofList->next = new edge(employee->n);
            employee = employee->next;
        }
        // Prints the name of the current person to the file
        file<<printList->n->name;
        if(printList->n!=CEO){
            // prints the person's boss and group to the file as necessary
            file<<delim<<printList->n->boss->name<<delim;
            if(printList->n->group!=printList->n->boss->group){
                file<<printList->n->group;
            }
        }
        // Ends the line
        file<<delim2;
        // Deletes the current element of the linked list and moves on to the next one.
        edge* temp = printList->next;
        delete printList;
        printList = temp;
    }
    file.close();
};

// Imports an organizational structure from a file.
void Tree::importTree(std::string fileName){
    ifstream file;
    file.open(fileName.c_str());//added c._str()
    if(!file.is_open()){
        cout<<"File not found."<<endl;
        return;
    }
    string line;
    cout<<"Are you sure you want to delete this organization and import a new one? (y/n)"<<endl;
    getline(cin, line);
    if(line.length()>0 && (line[0]=='y' || line[0]=='Y')){
        string errorMsg = "File is corrupt. No changes made.";
        std::string company_Name;//added Feature
        getline(file,line,delim2);//added Feature
        company_Name = line;//added Feature
        getline(file, line, delim2);
        if(!acceptableName(line, NULL)){
            cout<<errorMsg<<endl;
            return;
        }
        /* The first name given is the CEO. I don't want to change the current organization
         * until I'm certain the file is not corrupted, so I instead create an entirely new
         * organization, and only delete the old one after the file has been fully read in.
         */
        node* newCEO = new node(line, NULL);
        while(!file.eof()){
            getline(file, line, delim2);
            // We ignore empty lines in the document
            if(line.length()>0){
                stringstream linestream(line);
                string name;
                getline(linestream, name, delim);
                if(!acceptableName(name, newCEO)){
                    cout<<errorMsg<<endl;
                    /* This is why deleteEverything takes an argument: so we can delete
                     * everything we are currently trying to import rather than the
                     * original tree.
                     */
                    deleteEverything(newCEO);
                    return;
                }
                string bossName;
                getline(linestream, bossName, delim);
                /* This is one of the reasons findNode can take a second argument: so
                 * we can look for people even if they're not under the current CEO.
                 */
                node* boss = findNode(bossName, newCEO);
                if(boss==NULL){
                    cout<<errorMsg<<endl;
                    deleteEverything(newCEO);
                    return;
                }
                node* temp = new node(name, boss);
                addEdge(new edge(temp));
                getline(linestream, bossName, delim2);
                // Adds the group, if it exists.
                if(bossName.length()>1){
                    temp->group = bossName;
                }
            }
        }
        // Deletes the original tree, then finishes the import by pointing CEO at the new tree.
        deleteEverything(CEO);
        CEO = newCEO;
        companyName = company_Name;
    }
    file.close();
};

// Moves a person by removing them from the tree, then re-adding them to a new boss.
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
    if(person->boss!=boss){
        // Removes the person from the tree, then re-adds them to the given boss.
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

// Moves a person by relocating the element in the linked list that points to them.
void Tree::movePersonAndEmployees(std::string person_name, std::string newBoss){
    node* person = findNode(person_name);
    if(person==NULL){
        cout<<"Could not find this person. "
            <<"Make sure name is spelled correctly."<<endl;
        return;
    }
    /* Looks for the new boss under the person, then outputs an error if the new
     * boss is one of the current employees of the person.
     */
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
    // If this is the first person in the linked list
    if(thisPerson->n==person){
        // Set the boss's first employee to the next employee in the list
        person->boss->employees = thisPerson->next;
        if(person->boss->employees==NULL){
            // If this was the only employee, set the last employee to NULL
            person->boss->last = NULL;
        }
    }
    else{
        // Go through the list until you reach the employee before this one
        while(thisPerson->next->n!=person){
            thisPerson = thisPerson->next;
        }
        // temp is the employee to be removed
        edge* temp = thisPerson->next;
        // Set the previous employee so it skips the employee to be removed in the linked list
        thisPerson->next = temp->next;
        /* If the employee to be removed was the last employee, set the last employee to
         * the previous employee.
         */
        if(person->boss->last==temp){
            person->boss->last = thisPerson;
        }
        // Set thisPerson to the employee to be removed
        thisPerson = temp;
    }
    // Make sure the employee to be removed has no connection to their previous employer
    thisPerson->next = NULL;
    // Add the person to their new boss
    person->boss = boss;
    addEdge(thisPerson);
};

// Prints information about a person given their name.
void Tree::personInfo(string person_name){
    personInfo(findNode(person_name));
};

// Prints information about the entire organization structure.
void Tree::printOrgStructure(){
    cout<<companyName<<"'s "<<"Structure\n";//Added Feature
    cout<<"===============================\n";//Added Feature
    // Uses BFS to print out all employees in order of seniority
    edge* printList = new edge(CEO);
    edge* endofList = printList;
    while(printList!=NULL){
        // Prints out information about person
        personInfo(printList->n);
        cout<<endl;
        // Starts at first employee of current person
        edge* employee = printList->n->employees;
        while(employee!=NULL){
            // Iterates through employees, adding them to the end of the linked list
            endofList = endofList->next = new edge(employee->n);
            employee = employee->next;
        }
        // Moves on to the next person, deleting the current element of the linked list
        edge* temp = printList->next;
        delete printList;
        printList = temp;
    }
};

/* Promotes an employee. If the employee is directly below CEO, the CEO effectively
 * switches places with them, but becomes their most senior employee. Otherwise, the
 * employee and all their underlings go up one level in the organization.
 */
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
        // They literally just switch names
        string CEO_name = CEO->name;
        CEO->name = person->name;
        person->name = CEO_name;
        /* If the old CEO is not the new CEO's most senior employee, he becomes
         * the most senior employee.
         */
        if(person!=CEO->employees->n){
            edge* empl = CEO->employees;
            // Iterate until empl is the employee one before the former CEO.
            while(empl->next->n!=person){
                empl = empl->next;
            }
            edge* exCEO = empl->next;
            // empl gets linked to the node after exCEO
            empl->next = exCEO->next;
            // The exCEO gets linked to the former first employee in the list
            exCEO->next = CEO->employees;
            // The exCEO becomes the first employee in the list
            CEO->employees = exCEO;
            /* If the exCEO was the last person in the list, send the pointer to the
             * last element to empl instead.
             */
            if(CEO->last = exCEO){
                CEO->last = empl;
            }
        }
        return;
    }
    /* If none of the above conditions are met, just move this employee and their
     * employees up a level.
     */
    movePersonAndEmployees(person_name, person->boss->boss->name);
};

// Deletes a person from the tree.
void Tree::removePerson(string person_name){
    node* person = findNode(person_name);
    if(person==NULL){
        cout<<"Could not find this person. "
            <<"Make sure name is spelled correctly."<<endl;
        return;
    }
    delete removePerson(person);
};

/* Makes sure the name is acceptable. This includes searching the tree (starting at top)
 * for a match, which is why there is an extra argument.
 */
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

// Adds an employee to the boss of the node contained in the employee.
void Tree::addEdge(edge* empl){
    node* boss = empl->n->boss;
    if(boss->employees==NULL){
        /* If the boss has no employees yet, this becomes the only employee,
         * the first and the last employee under that boss.
         */
        boss->last = boss->employees = empl;
    }
    else{
        /* If the boss does have employees, add the new edge to the last edge
         * in the list, then change the pointer boss->last so it points to
         * the new edge.
         */
        boss->last = boss->last->next = empl;
    }
}

// Deletes every node below the given node using BFS.
void Tree::deleteEverything(node* top){
    if(top!=NULL){
        edge* deleteList = top->employees;
        edge* endList = top->last;
        // Deletes the CEO
        delete top;
        while(deleteList!=NULL){
            /* Links the last employee in the list to the first employee
             * of the person about to be deleted.
             */
            endList->next = deleteList->n->employees;
            // Sends the end of the list to the real end of the list
            if(deleteList->n->last!=NULL){
                endList = deleteList->n->last;
            }
            edge* temp = deleteList->next;
            // You have to delete the node and the linked list element
            delete deleteList->n;
            delete deleteList;
            deleteList = temp;
        }
    }
};

// Searches for the name starting at the CEO.
node* Tree::findNode(string name){
    return findNode(name, CEO);
};

// Finds the person using recursive DFS.
node* Tree::findNode(string name, node* person){
    if(person==NULL || person->name==name){
        return person;
    }
    else{
        edge* empl = person->employees;
        // Searches through employees until there are none left or the name is found
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

// Forces the name to input a good name for the CEO before continuing.
void Tree::makeCEO(){
    string name;
    do{
        cout<<"Please enter the name of a CEO:"<<endl;
        getline(cin, name);
        name = removeWhitespace(name);
    }while(!acceptableName(name, NULL));
    CEO = new node(name, NULL);
};

// Returns information about a person.
void Tree::personInfo(node* person){
    if(person==NULL){
        cout<<"Could not find Employee. Make sure name is spelled correctly."<<endl;
        return;
    }
    cout<<"Name: "<<person->name<<"\nGroup: "<<person->group<<"\nBoss: ";
    if(person->boss==NULL){
        cout<<"N/A";
    }
    else{
        cout<<person->boss->name;
    }
    cout<<"\nEmployees: ";
    if(person->employees==NULL){
        cout<<"N/A";
    }
    else{
        edge* empl = person->employees;
        while(empl!=NULL){
            cout<<empl->n->name;
            if(empl->next!=NULL){
                cout<<", ";
            }
            empl = empl->next;
        }
        cout<<endl;
    }
};

// Recursively (DFS) changes the group of all people below the given node
void Tree::recursiveGroupChange(node* person, string newGroup){
    person->group = newGroup;
    edge* empl = person->employees;
    while(empl!=NULL){
        recursiveGroupChange(empl->n, newGroup);
        empl = empl->next;
    }
};

/* Removes a person from the organization, and returns a pointer to that person.
 * IMPORTANT NOTE: Exactly one edge between people must be deleted for a person
 * to be removed from the organization. This must happen, no matter what.
 */
node* Tree::removePerson(node* person){
    if(person==NULL){
        return person;
    }
    if(person==CEO){
        if(person->employees==NULL){
            // If the CEO has no employees, you need a new CEO
            makeCEO();
        }
        else{
            // Effectively promote the CEO's most senior employee
            CEO = person->employees->n;
            /* Adds the new CEO's employees to the old CEO's payroll, then
             * hands them all back to the new CEO. This is done to preserve
             * seniority. If the old CEO had only one employee, this is not
             * necessary.
             */
            if(person->employees->next!=NULL){
                // Adds the new CEO's employees to the old CEO's list of employees
                person->last->next = CEO->employees;
                /* Sets the new CEO's first employee to their former coworker, the
                 * second most senior employee of the former CEO.
                 */
                edge* temp = CEO->employees = person->employees->next;
                // Makes sure all the old CEO's employees know who's boss
                while(temp!=person->last->next){
                    temp->n->boss = CEO;
                    temp = temp->next;
                }
            }
            // Deletes the link between the former CEO and the new CEO
            delete person->employees;
            // Sets everything necessary to NULL
            person->last = person->employees = NULL;
            CEO->boss = NULL;
            // Sets the CEO's group to the default "Management"
            CEO->group = person->group;
        }
        return person;
    }
    // Code only gets here if the person is not the CEO
    edge* coworker = person->boss->employees;
    // If this is the most senior employee of the boss...
    if(coworker->n==person){
        coworker = coworker->next;
        // Delete the link between the boss and this person
        delete person->boss->employees;
        if(coworker==NULL){
            /* If this person was the boss's only employee, the boss inherits all employees
             * of this person.
             */
            coworker = person->boss->employees = person->employees;
            person->boss->last = person->last;
        }
        else{
            // The boss still inherits all this person's employees
            person->boss->employees = coworker;
            coworker = person->boss->last->next = person->employees;
            if(person->last!=NULL){
                person->boss->last = person->last;
            }
        }
    }
    else{
        // Set coworker to the employee just before this person
        while(coworker->next->n!=person){
            coworker = coworker->next;
        }
        // This is the connection between the person and their former boss
        edge* personEdge = coworker->next;
        coworker->next = personEdge->next;
        if(person->boss->last==personEdge){
            person->boss->last = coworker;
        }
        delete personEdge;
        // The boss STILL inherits all this person's employees.
        coworker = person->boss->last->next = person->employees;
        if(person->last!=NULL){
            person->boss->last = person->last;
        }
    }
    // Makes sure all new employees know who their new boss is.
    while(coworker!=NULL){
        coworker->n->boss = person->boss;
        coworker = coworker->next;
    }
    // Sets everything connecting the person to the organization to NULL
    person->boss = NULL;
    person->employees = person->last = NULL;
    return person;
};

// Removes whitespace from the ends of the given string.
string Tree::removeWhitespace(string str){
    while(str.length()>0 && str[0]==' '){
        str = str.substr(1, str.length());
    }
    while(str.length()>0 && str[str.length()-1]==' '){
        str = str.substr(0, str.length()-1);
    }
    return str;
};


void Tree::companyNameChange(){
    cout<<"Name of Company:"<<endl;//Added Feature
    getline(cin,companyName);//Added Feature
}

