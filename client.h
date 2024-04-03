#ifndef __MYNETWORK_CLIENT_H_
#define __MYNETWORK_CLIENT_H_

#include <omnetpp.h>
#include <bits/stdc++.h>

using namespace omnetpp;
using namespace std;

class Client : public cSimpleModule {
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
