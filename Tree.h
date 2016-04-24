#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

struct edge;

struct node{
    std::string name;
    node* boss = NULL;
    edge* employees = NULL;
    node(std::string person_name, node* boss_ptr){
        name = person_name;
        boss = boss_ptr;
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
    void addPerson(std::string person_name, std::string boss);
    void movePerson(std::string person_name, std::string newBoss);
    void personInfo(std::string person_name);
    std::string printOrgStructure();
    void promotePerson(std::string person_name);
    void removePerson(std::string person_name);
private:
    node* CEO = NULL;
    bool acceptableName(std::string name);
    node* findNode(std::string name);
    node* findNode(std::string name, node* person);
    void makeCEO();
    void movePerson(node* person, node* boss);
    std::string personInfo(node* person);
    node* removePerson(node* person);
};

#endif // TREE_H_INCLUDED
