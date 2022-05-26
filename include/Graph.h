//
// Created by אביתר מור on 10/11/2020.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <vector>


class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    Graph(const Graph& gr);

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    void enq(int);
    int deq();
    int numOfLines();
    std::vector<std::vector<int>> getEdges();
    std::vector<int> infected();
    void setEdges( std::vector<std::vector<int>> &matrix);
    bool isFullyInfected(int node);
    std::vector<int> getInfNodes();
    bool isInfectedToBe(int nodeInd);

private:


    std::vector<std::vector<int>> edges;
    std::vector<int> infNodes;
    std::vector<int> memorialInfNodes; // will keep all of the infected nodes
    std::vector<int> pT;
};

#endif //GRAPH_H
