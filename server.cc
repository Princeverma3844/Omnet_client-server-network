#include "server.h"
#include "ArrayMessage_m.h"
using namespace std;
#include <fstream>
void Server::initialize() {
    // Server initialization code
}

void Server::handleMessage(cMessage *msg) {

    ifstream inputFile("topo.txt");
    vector<int> mal_nodes;
    int value;
    while (inputFile >> value) {
        mal_nodes.push_back(value);
    }
    inputFile.close();

    ArrayMessage *arrayMsg = dynamic_cast<ArrayMessage *>(msg);
//    cGate *arrivalGate = msg->getArrivalGate();
//    string gate_name = arrivalGate->getFullName();
//    cout<<"gate"<<endl;
    const char *receiverFullName = getFullName();
    string server_name(receiverFullName);
    int server_idx = server_name[server_name.size()-2]-'0';
    cModule *senderModule = msg->getSenderModule();
    string client_name =  senderModule->getName();
    int len = client_name.size() - 1;
    int gate_number = client_name[len] - '0';
    if(gate_number > 10){
        gate_number = 0;
    }
    if (arrayMsg) {
        // Process the array data
        int n = arrayMsg->getArraySize();
        int max_array[n/3];
        if(mal_nodes[server_idx]==0){
            int idx = 0;
            while(idx < n){
                int val1 = arrayMsg->getArrayData(idx);
                int val2 = arrayMsg->getArrayData(idx + 1);
                int val3 = arrayMsg->getArrayData(idx + 2);
                int val = max(val1, max(val2 ,val3));
                max_array[idx/3] = val;
                idx += 3;
            }
        }
        else{
            int idx = 0;
            while(idx < n){
                int val1 = arrayMsg->getArrayData(idx);
                int val2 = arrayMsg->getArrayData(idx + 1);
                int val3 = arrayMsg->getArrayData(idx + 2);
                int val = min(val1, min(val2 ,val3));
                max_array[idx/3] = val;
                idx += 3;
            }
        }
        n /= 3;
        ArrayMessage *arrayMsg = new ArrayMessage("ArrayMessage");
        arrayMsg->setArraySize(n);
        arrayMsg->setType("server");
        // Populate the array field in the message
        for (int i = 0; i < n; i++) {
            arrayMsg->setArrayData(i, max_array[i]);
        }

        ArrayMessage *res = arrayMsg->dup();
//        cout<<gate_number<<endl;
        send(res, "out", gate_number);
    } else {
        // Handle other types of messages if needed
        cout << "Server received an unexpected message" << endl;
        cMessage *mes = new cMessage("hi server");
        send(mes, "out");
//        delete msg;
    }
}

Define_Module(Server);
