#ifndef __MYNETWORK_SERVER_H_
#define __MYNETWORK_SERVER_H_

#include <omnetpp.h>
#include <bits/stdc++.h>

using namespace omnetpp;

class Server : public cSimpleModule {
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
