//
// Created by אביתר מור on 10/11/2020.
//
#include "../include/Session.h"
#include <fstream>
#include "../include/json.hpp"
#include "../include/Agent.h"

using namespace  nlohmann;

Session::Session(const std::string &path) :
        cycle(0) ,
        g(parseGraph(path)),
        treeType(parseTreeType(path)),
        agents() {
    std::ifstream i(path);
    json config_json;
    i >> config_json;

    for (auto &ag: config_json["agents"]) {
        if (ag[0] == "C") { // to add contact tracer
            auto* c=new const ContactTracer();
            addAgent(*c);
            delete c;
        } else {    // add virus
            int temp = ag[1];
            auto *v= new const Virus(temp);
            addAgent(*v);
            this->enqueueInfected(temp);
            delete v;
        }
    }
}



Session::~Session(){ // delete
    for(auto & agent : agents){
        delete agent;
    }
}



std::vector <std::vector<int>>Session::parseGraph(const std::string &path) // method to extract the given input in json file
{
    std::ifstream i(path);
    json config_json;
    i >> config_json;
      // extract graph from json file as json file
    std::vector <std::vector<int>> graphMat= config_json["graph"];
    return graphMat;
}

void Session::addAgent(const Agent &agent) {
    Agent* temp= agent.clone();
    agents.push_back(temp);
}

void Session::addAgent(Agent *agent) {
    agents.push_back(agent);
}


void Session::setEdges(std::vector<std::vector<int>> &mat) {
    this->g.setEdges(mat);
}


Graph& Session::checkG() { return g; }

TreeType Session::parseTreeType(const std::string &path) // method to extract the given info in json file
{
    std::ifstream i(path);
    json config_json;
    i >> config_json;
    if (config_json["tree"] == "M") {
        return MaxRank;
    } else if (config_json["tree"] == "C") {
        return Cycle;
    } else return Root;
}

void Session::simulate() {
    cycle=0; // reset cycle to default
    while (!this->terminationCondition()) {
        for (auto agent : agents) {
            agent->act(*this);
        }
          this->cycle++;
    }
    agents.clear();
    // output file :
    json output;
    output["graph"] = g.getEdges();
    output["infected"] = g.infected();
    std::ofstream ot("./output.json");
    ot << output;

}

void Session::enqueueInfected(int i) { g.enq(i);}

int Session::dequeueInfected() {
    if(!g.getInfNodes().empty())
         return (g.deq());
    else
         return -1;
}


bool Session::terminationCondition() {
     // assumes that termination condition has not been met
    std::vector <std::vector<int>> grE = this->g.getEdges();
    // for every node we will check his connected component if all are of the same type
    for (int fN = 0; fN < this->g.numOfLines() ; fN++) {
        for (int sN = 0; sN < this->g.numOfLines() ; sN++) {
            if (grE[fN][sN] == 1) //  connected
            {
                if (this->g.isInfected(fN) != this->g.isInfected(sN)) {  // they are neighbors but not same type
                    return false; // enough to find one to break
                }
            }
        }
    }
    return true; // all vertices are either infected or none is infected in the connected particle
}
int Session::getCycle() const {
    return cycle;
}
TreeType Session::getTreeType() const {return this->treeType;}


Session::Session(Session &session): // copy constructor
        cycle(session.getCycle()) ,g(session.g),treeType(session.treeType),agents(session.agents) {}

