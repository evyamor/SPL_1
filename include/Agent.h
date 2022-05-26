//
// Created by אביתר מור on 10/11/2020.
//

#ifndef AGENT_H
#define AGENT_H

#include <vector>
#include "../include/Session.h"

class Agent{
public:
    Agent();

    virtual void act(Session& session)=0;
    virtual ~Agent();
    virtual Agent* clone() const=0;

};

class ContactTracer: public Agent{
public:
    ContactTracer();
    ContactTracer(const ContactTracer &c);
    virtual ContactTracer* clone() const;
    virtual ~ContactTracer();
    virtual void act(Session& session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    Virus(const Virus &v);
    virtual Virus* clone() const;
    virtual ~Virus();
    virtual void act(Session& session);

private:
    const int nodeInd;

};
#endif //ASS1_INCLUDE_AGENT_H
