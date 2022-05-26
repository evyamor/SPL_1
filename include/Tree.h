//
// Created by אביתר מור on 10/11/2020.
//

#ifndef TREE_H
#define TREE_H

#include <vector>
#include <iostream>
#include <queue>
#include "../include/Graph.h"
#include "../include/Session.h"


//class Session;

class Tree{
public:
    Tree(int rootLabel);
    Tree(const Tree &other);
    virtual ~Tree();
    void addChild( Tree& child);
    static Tree* BFS( Session& session, int rootLabel) ;
    void BFS( Session& session,bool visited[], std::queue<Tree*> &bfsQ);
    static void credibility(int arr[], int countNodes);


    static Tree* createTree( Session& session, int rootLabel);
    virtual int traceTree()=0;
    std::vector<Tree*> getChildren();
    int getCountNodes();
    int getLabel() const;

protected:
    void getDepth(int* depths, int currentDepth);


    int getRootLabel() const;

private:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    CycleTree(CycleTree& ct);
    virtual int traceTree();



private:
    int currCycle;

};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    MaxRankTree(MaxRankTree& mrt);
    virtual int traceTree();
    void maxRN(int*);


};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    RootTree(RootTree& rt);
    virtual int traceTree();
};


#endif //ASS1_INCLUDE_TREE_H
