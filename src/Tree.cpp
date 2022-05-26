//
// Created by אביתר מור on 10/11/2020.
//
#include "../include/Tree.h"
#include <queue>



Tree::Tree(int rootLabel) : node(rootLabel), children() {} // constructor


Tree::Tree(const Tree &other): node(other.node), children(0){ //copy constructor
    for(auto& child: other.children){
        addChild(*child);
    }
}

Tree::~Tree() { // delete
    for (auto & i : children) {
        delete i;
    }
}


void Tree::addChild(Tree &child) {
    children.push_back(&child);
}


int Tree::getCountNodes() {
    int childNumber = 1;
    for (int i = 0; i < (int)this->children.size(); i++) {
        childNumber = childNumber + children[i]->getCountNodes();
    }
    return childNumber;
}

Tree *Tree::createTree(Session &session, int rootLabel) {
    TreeType en = session.getTreeType();
    switch (en) {
        case TreeType::MaxRank : {
            Tree *mat = new MaxRankTree(rootLabel);
            //mat->BFS(session.checkG(),en, session.getCycle());
            return mat;
        }
        case TreeType::Cycle : {
            Tree *ct = new CycleTree(rootLabel, session.getCycle());
           // ct->BFS(session.checkG(),en, session.getCycle());
            return ct;
        }
        case TreeType::Root : {
            Tree *rt = new RootTree(rootLabel);
           // rt->BFS(session.checkG(),en, session.getCycle());
            return rt;
        }
    }
    return nullptr;
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}


int CycleTree::traceTree() {
    int i = 0;
    Tree * tree = this;
    std::vector<Tree*> tree_children = this->getChildren();
        while ((i < currCycle )&& (!tree_children.empty())) { // go left as many cycle rounds as possible
                tree = tree_children[0]; // go left
                tree_children=tree->getChildren(); // promote children
                i++;
            }

    return tree->getLabel();
}




void Tree::getDepth(int *depths, int currentDepth) {
    depths[this->getLabel()] = currentDepth;
    for (int i = 0; i <(int) children.size(); i++) {
        this->getChildren()[i]->getDepth(depths, currentDepth + 1);
    }
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

void MaxRankTree::maxRN(int rank[]) { // inserts into rank arr every node's rank
    if(!this->getChildren().empty()) {
        rank[this->getLabel()] = (int)this->getChildren().size();
        for (int i = 0; i < (int) this->getChildren().size(); i++) {
            ((MaxRankTree *) (this->getChildren()[i]))->maxRN(rank);
        }
    }
    else
        rank[this->getLabel()]=0;
}

int MaxRankTree::traceTree() { // return the index of the node with max rank
    int countNodes = this->getCountNodes();

    if(countNodes==1)
        return this->getRootLabel();

    int arrDepth[countNodes]; // children count array

    int arrRA[countNodes]; // rank count array

    for(int i=0;i<countNodes;i++){
        arrDepth[i]=-1;  // initialize all to negative ranks
        arrRA[i]=0; // initialize all to rank 0
    }

    this->getDepth(arrDepth, 0);
    this->maxRN(arrRA);
    credibility(arrRA, countNodes);
    int currMax = 0;
    for (int i = 0; i < countNodes; i++) { // length? --- we want the smallest i which has biggest rank and of lowest depth possible
        if (arrRA[currMax] < arrRA[i])
            currMax=i;
        if(arrRA[currMax]== arrRA[i] && ((currMax > i)|(arrDepth[currMax] > arrDepth[i])))    // they are of equal ranks thus we prefer the one with lower depth and lower index
              // if curr max rank node has higher depth or is more left in the tree
                    currMax = i;
    }


    return currMax;
}

MaxRankTree::MaxRankTree(MaxRankTree &mrt):Tree(mrt.getRootLabel()) {} // copy constructor


RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

int RootTree::traceTree() { // return the index of the root of the tree
    return this->getRootLabel();
}



int Tree::getRootLabel() const {
    return node;
}

std::vector<Tree*> Tree::getChildren(){
    return this->children;
}
int Tree::getLabel() const {return this->node;}



Tree* Tree::BFS( Session& session, int rootLabel) {
    std::vector<std::vector<int>> sessionEdges = session.checkG().getEdges();
    bool visited[session.checkG().numOfLines()];

    for (int i = 0; i < session.checkG().numOfLines(); i++) { // initializing default value
        visited[i] = false;
    }

    // Create a queue for BFS
    auto *bfsQ=new std::queue<Tree*>;
    //create root tree
    Tree *tree = createTree(session, rootLabel);

    visited[rootLabel] = true; // start point
    bfsQ->push(tree);

    bfsQ->front()->BFS(session,visited,*bfsQ); // recursively create trees

    delete bfsQ;
    return tree;
}
void Tree::BFS( Session& session, bool visited[], std::queue<Tree*> &bfsQ){ // dont know how to not pass by value visited, tried many different options
    int currRoot=bfsQ.front()->getRootLabel();
    for (int i = 0; i < session.checkG().numOfLines(); i++) { // initializing default value
        if (( session.checkG().getEdges()[currRoot][i]== 1 )&&( !visited[i]) ) {
            visited[i]= true;
            Tree* new_child=createTree(session,i);
            bfsQ.push(new_child);
            this->addChild(*new_child);
        }
    }
    bfsQ.pop(); // take out head to continue bfs

    // continues BFS recursively if can
    if(!bfsQ.empty()){
        bfsQ.front()->BFS(session,visited,bfsQ);
    }
}

void Tree::credibility(int *arr, int countNodes) {
    for(int i=0;i<countNodes;i++){
        if(arr[i]>countNodes-1)
            arr[i]=0;
    }
}
RootTree::RootTree(RootTree &rt): Tree(rt.getRootLabel()) {} // copy constructor
CycleTree::CycleTree(CycleTree &ct):Tree(ct.getRootLabel()),currCycle(ct.currCycle){} // copy constructor
