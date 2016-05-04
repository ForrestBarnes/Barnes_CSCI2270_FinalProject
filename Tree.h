#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

/* Creates the linked list struct without defining it so I
 * can use edge* in my node definition without getting erros.
 */
struct edge;

struct node{
    std::string name;
    std::string group;
    node* boss = NULL;
    // First element in the linked list of employees.
    edge* employees = NULL;
    // Last element in the linked list of employees.
    edge* last = NULL;
    node(std::string person_name, node* boss_ptr){
        name = person_name;
        boss = boss_ptr;
        // If this is the CEO, their group becomes management.
        if(boss==NULL){
            group = "Management";
        }
        // Otherwise, their group becomes their boss's group.
        else{
            group = boss->group;
        }
    }
};

/* The struct for a linked list of nodes. I used this
 * instead of a vector because I've had problems with
 * vectors being constrained to a particular size before.
 * This doesn't happen if I create a linked list myself.
 */
struct edge{
    edge* next = NULL;
    node* n = NULL;
    edge(node* node_ptr){
        n = node_ptr;
    }
};

class Tree{
public:
    Tree();
    ~Tree();
    void addPerson(std::string name, std::string boss);
    void changeGroup(std::string person_name, std::string newGroup);
    void exportTree(std::string fileName);
    void importTree(std::string fileName);
    void movePerson(std::string person_name, std::string newBoss);
    void movePersonAndEmployees(std::string person_name, std::string newBoss);
    void personInfo(std::string person_name);
    void printOrgStructure();
    void promotePerson(std::string person_name);
    void removePerson(std::string person_name);
    void companyNameChange();//added feature
private:
    node* CEO = NULL;
    char delim = ',';
    char delim2 = '\n';
    bool acceptableName(std::string name, node* top);
    void addEdge(edge* empl);
    void deleteEverything(node* top);
    node* findNode(std::string name);
    node* findNode(std::string name, node* person);
    void makeCEO();
    void personInfo(node* person);
    void recursiveGroupChange(node* person, std::string newGroup);
    node* removePerson(node* person);
    std::string removeWhitespace(std::string str);
    std::string companyName;//Added Feature
};

#endif // TREE_H_INCLUDED
