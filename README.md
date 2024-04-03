# P2P-Network

## Objective
The objective of this project is to implement a Gossip protocol over a client-to-peer network to broadcast messages and ensure the liveness of connected peers. This README provides an overview of the network setup.

## Network Setup
The network consists of two types of nodes:

- **Server Nodes:** Server nodes will take the task from the clients and will return the output for that task.
- **Client Nodes:** Client nodes will send the task to the server and will provide score to the servers based on their malicious behaviour.

## Input Format
The value of n will be given by the running of python script.

## How To Run
1. Run the python script and provide the value of n in that script.
2. Build and run the project and do the simulation.


## Proof of correctness
- **gossips:** All the clients starts to propagate gossips the with neighbour clients as soon as they get message.
- **broadcast:** The server scores are updated at the end of the simualtion.

