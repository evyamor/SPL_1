//
// Created by אביתר מור on 10/11/2020.
//

#include "../include/Graph.h"
#include <utility>
#include <vector>



Graph::Graph(std::vector <std::vector<int>> matrix) : edges(std::move(matrix)), infNodes(), memorialInfNodes(),pT(){}
Graph::Graph(const Graph &gr) : edges(gr.edges), infNodes(gr.infNodes), memorialInfNodes(gr.memorialInfNodes),pT(gr.pT){}

std::vector <std::vector<int>> Graph::getEdges() { return this->edges;}

void Graph::infectNode(int nodeInd) {
       pT.push_back(nodeInd); // infect and add to queue

}

bool Graph::isInfected(int nodeInd) {
    for (int infNode : memorialInfNodes) {
        if (infNode == nodeInd) {
            return true;
        }
    }
    return false;
}

int Graph::numOfLines() { return edges[0].size(); }

void Graph::enq(int i) {
   if(!isFullyInfected(i)) {
       infNodes.push_back(i); // infect and add to queue
     //  pT.push_back(i);
       memorialInfNodes.push_back(i);
   }


}
int Graph::deq() { // dequeues from InfNodes que
    int toRet = pT.front();
    pT.erase(pT.begin());
    infNodes.erase(infNodes.begin());
    return toRet;
}

std::vector<int> Graph::infected() { // returns output of infected nodes
    return this->memorialInfNodes;}

void Graph::setEdges( std::vector<std::vector<int>> &matrix) {this->edges=matrix;}

bool Graph::isFullyInfected(int node) {
    for(int & it : pT){
        if(it==node)
            return true;
    }
    return false;
}

std::vector<int> Graph::getInfNodes() {
    return this->pT;
}

bool Graph::isInfectedToBe(int nodeInd) {
    for(int & it : infNodes){
        if(it == nodeInd)
            return true;
    }
    return false;
}


