#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

//#include "Employee.h"

struct node{
    std::string name;
    node* boss = NULL;
    edge* employees = NULL;
    group* group = NULL;
    node(std::string person_name, node* boss_ptr){
        name = person_name;
        boss = boss_ptr;
    }
};

struct edge{
    edge* next = NULL;
    node* node = NULL;
    edge(node* node_ptr){
        node = node_ptr;
    }
};

struct group{
    std::string name;
    edge* members = NULL;
    group* next = NULL;
    group(std::string group_name){
        name = group_name;
    }
};

class Tree{
public:
    void addNode(std::string name, std::string boss);
    void addToGroup(std::string person_name, std::string group);
    void exportOrgToFile();
    void importOrgFromFile();
    void personInfo(std::string name);
    std::string printOrgStructure();
protected:
private:
    node* CEO = NULL;
    edge* employeeList = NULL;
    group* groups = NULL;
    void addToBossGroup(node* node);
    node* findNode(std::string name);
    std::string personInfo(node* node);
};

#endif // TREE_H_INCLUDED
