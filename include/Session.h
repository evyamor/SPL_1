#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include <string>
#include "../include/Graph.h"



class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session(const std::string& path);
    Session(Session& session);
    ~Session();

    void simulate();
    void addAgent(const Agent& agent);
    void addAgent(Agent *agent);
   void setEdges(std::vector<std::vector<int>> &mat);


    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;

    int getCycle() const;

    Graph& checkG();


private:
    static std::vector<std::vector<int>> parseGraph(const std::string& path);
    static TreeType parseTreeType(const std::string& path);
    bool terminationCondition();
    int cycle;
    Graph g;
    const TreeType treeType;
    std::vector<Agent*> agents;




};

#endif //ASS1_INCLUDE_SESSION_H
