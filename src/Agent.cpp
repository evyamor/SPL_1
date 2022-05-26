//
// Created by אביתר מור on 10/11/2020.
//
#include "../include/Agent.h"
#include "../include/Tree.h"

//AGENT
Agent::Agent() = default;

Agent::~Agent() = default;

// CONTACT TRACER
ContactTracer::ContactTracer() = default;

ContactTracer::ContactTracer(const ContactTracer &c) : ContactTracer() {}

ContactTracer::~ContactTracer() = default;
ContactTracer* ContactTracer::clone() const {
    return new ContactTracer();
}

void ContactTracer::act(Session &session) {

    int rootNode = session.dequeueInfected();
    if(rootNode!=-1) {
        Tree *t = Tree::BFS(session, rootNode); // creates BFS tree
        int disconnectLabel = t->traceTree();
        std::vector<std::vector<int>> currMatrix = session.checkG().getEdges();

        for (int j = 0; j < session.checkG().numOfLines(); j++) {
            currMatrix[disconnectLabel][j] = 0; // disconnect all neighbors from the node
            currMatrix[j][disconnectLabel] = 0; // since matrix is symmetrical
        }

        // session.setGraph(currMatrix); // update the session's graph
        session.setEdges(currMatrix);
        delete t;
    }
}

//VIRUS
Virus::Virus(int nodeInd) : nodeInd(nodeInd) {}

Virus::Virus(const Virus &v) : Virus(v.nodeInd) {} // copy constructor
Virus::~Virus() = default;

Virus* Virus::clone() const {
    return new Virus(this->nodeInd);
}

void Virus::act(Session &session) {
    Graph &gra = session.checkG();
    std::vector<int> edges = gra.getEdges()[nodeInd];
    if(gra.isInfectedToBe(nodeInd)){
        if(!(gra.isFullyInfected(nodeInd))) {
        gra.infectNode(nodeInd);
    }}
    // search next node to mark
    for (int nodeIt = 0; nodeIt <(int) edges.size(); nodeIt++) { // keep search till you find one neighbor to infect or none left to infect
        if (edges[nodeIt] == 1 && (!gra.isInfected(nodeIt))) { // have a neighbor that's not infected
            gra.enq(nodeIt);
            auto *v = new Virus(nodeIt);
            session.addAgent(v->clone());
            delete v;
            return;
        }
    }

}




