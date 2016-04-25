#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

struct edge;

struct node{
    std::string name;
    std::string group;
    node* boss = NULL;
    edge* employees = NULL;
    edge* last = NULL;
    node(std::string person_name, node* boss_ptr){
        name = person_name;
        boss = boss_ptr;
        if(boss==NULL){
            group = "Management";
        }
        else{
            group = boss->group;
        }
    }
};

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
    std::string printOrgStructure();
    void promotePerson(std::string person_name);
    void removePerson(std::string person_name);
private:
    node* CEO = NULL;
    char delim = ',';
    char delim2 = '\n';
    bool acceptableName(std::string name, node* top);
    void deleteEverything(node* top);
    node* findNode(std::string name);
    node* findNode(std::string name, node* person);
    void makeCEO();
    void movePerson(node* person, node* boss);
    std::string personInfo(node* person);
    void recursiveGroupChange(node* person, std::string newGroup);
    node* removePerson(node* person);
    std::string removeWhitespace(std::string str);
};

#endif // TREE_H_INCLUDED
