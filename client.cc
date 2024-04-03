#include "client.h"
#include <fstream>
#include "ArrayMessage_m.h"
vector<vector<int>> server_response;
vector<int> server_index;
map<pair<vector<int>,string>, int> ML;
int n;
vector<int> data(100,0);
int cur_round = 0;
int timestamp = 0;
void Client::initialize() {

//    ifstream inputFile("topo.txt");
//    int n;
//    inputFile >> n;
//    inputFile.close();
//    par("n").setIntValue(n);
//    cout<<n<<endl;
    n = par("n");

    timestamp += 1;
    ArrayMessage *arrayMsg = new ArrayMessage("ArrayMessage");
    arrayMsg->setArraySize(3*n);
    arrayMsg->setType("server");

    // Populate the array field in the message
    for (int i = 0; i < 3*n; i++) {
        arrayMsg->setArrayData(i, rand());
//        cout<<arrayMsg->getArrayData(i)<<" ";
    }

    set<int> uniqueNumbers; // Set to store unique random numbers
    if(cur_round==0){
        int count = n / 2 + 1;
        random_device rd; // Obtain a random number from hardware
        mt19937 gen(rd()); // Seed the random number engine with rd
        uniform_int_distribution<> dis(0, n-1); // Define the range for random numbers

        while (uniqueNumbers.size() < count) {
            int randomNumber = dis(gen); // Generate a random number within the defined range
            uniqueNumbers.insert(randomNumber); // Insert the number into the set (ensures uniqueness)
        }
    }
    else{

        for(int i=0;i<n;i++){
            cout<<data[i]<<" ";
        }
        cout<<endl;
        vector<pair<int,int>> v;
        for(int i=0;i<n;i++){
            v.push_back({data[i],i});
        }
        sort(v.rbegin(), v.rend());
        for(int i=0;i<n/2+1;i++){
            uniqueNumbers.insert(v[i].second);
        }
    }

    for(auto x : uniqueNumbers){
        ArrayMessage *arrayMsgCopy = arrayMsg->dup();
        cout<<x<<" ";
        send(arrayMsgCopy, "out", x);
    }
    cout<<endl;
}

void Client::handleMessage(cMessage *msg) {
    // Handle incoming messages if needed
    timestamp += 1;
    n = par("n");
    ArrayMessage *message = dynamic_cast<ArrayMessage *>(msg);
    cModule *arrivalModule = msg->getArrivalModule();
    int len = message->getArraySize();
    vector<int> server_val;
    string type = message->getType();
    string id = message->getId();
    for(int i=0;i<len;i++){
        server_val.push_back(message->getArrayData(i));
    }
//    cout<<arrivalGate
    if(type == "server"){
        cModule *senderModule = msg->getSenderModule();
        string client_name =  senderModule->getFullName();
//        cout<<client_name<<endl;
        server_response.push_back(server_val);
        int index_val = client_name[client_name.size()-2]-'0';
        server_index.push_back(index_val);
        if(server_response.size() == n/2 + 1){
            vector<int> score(n,0);
            for(auto x:server_index){
                cout<<x<<" ";
            }
            cout<<endl;
            for(int j=0;j<n;j++){
                map<int,int> mp;
                int val = -1;
                int maxi = 0;
                for(int i=0;i<server_response.size();i++){
                    mp[server_response[i][j]]++;
                    if(mp[server_response[i][j]]>maxi){
                        val = server_response[i][j];
                        maxi = mp[server_response[i][j]];
                    }
                }
                for(int k=0;k<server_response.size();k++){
                    int i = server_index[k];
                    if(server_response[k][j]==val){
                        score[i]++;
                    }
                }
            }
            const char *module = arrivalModule->getName();
            string messageNameStr(module);
            ArrayMessage *server_score = new ArrayMessage("ArrayMessage");
            server_score->setArraySize(n);
            server_score->setType("client");
            server_score->setId(module);

            // Populate the array field in the message
            cout<<"score"<<endl;
            for (int i = 0; i < n; i++) {
                server_score->setArrayData(i, score[i]);
            }
            for(int i=0;i<n;i++){
                cout<<score[i]<<" ";
            }
            cout<<endl;
            server_response.clear();
            server_index.clear();
            send(server_score, "topo_out");
        }
    }
    else if(ML[{server_val, id}] < n){
        ML[{server_val, id}] += 1;
        for(int i=0;i<n;i++){
            data[i] += server_val[i];
        }
        cout<<"< "<<timestamp<<" > "<<id<<" < message propagated >"<<endl;
        send(message, "topo_out");
        cur_round += 1;
    }

}

Define_Module(Client);
