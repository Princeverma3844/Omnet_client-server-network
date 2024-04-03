import ned.IdealChannel;

network Network
{
    parameters:
        //        int n = 5; = 6; = 4; = 5;  // Change the number of servers as needed
        //        int n = 5; = 6; = 4; @unit(number) = topoReader("topo.txt", 1); // Read value from topo.txt
        int n = 5;
//        @display("bgb=584,450");

        @display("bgb=1017,466");
    submodules:
        client: Client {
            @display("p=720,135");
        }

        servers[n]: Server {
//            @display("p=310,78; i=device/server");
//			  @display("p=" + intuniform(100, 400) + ',' + intuniform(100, 400));
        }
        client1: Client {
            @display("p=667,412");
        }
        client2: Client {
            @display("p=565,234");
        }
        client3: Client {
            @display("p=470,273");
        }
        client4: Client {
            @display("p=392,317");
        }
        client5: Client {
            @display("p=646,195");
        }
    connections: // network level connections

        //		client.out[0] --> servers[0].in;
        for i=0..n-1 {
            client.out[i] --> servers[i].in[0];
            servers[i].out[0] --> client.in[i];
        }
        for i=0..n-1 {
            client1.out[i] --> servers[i].in[1];
            servers[i].out[1] --> client1.in[i];
        }
        for i=0..n-1 {
            client2.out[i] --> servers[i].in[2];
            servers[i].out[2] --> client2.in[i];
        }
        for i=0..n-1 {
            client3.out[i] --> servers[i].in[3];
            servers[i].out[3] --> client3.in[i];
        }
        for i=0..n-1 {
            client4.out[i] --> servers[i].in[4];
            servers[i].out[4] --> client4.in[i];
        }
        for i=0..n-1 {
            client5.out[i] --> servers[i].in[5];
            servers[i].out[5] --> client5.in[i];
        }
        client1.topo_out --> IdealChannel --> client4.topo_in;
        client4.topo_out --> IdealChannel --> client3.topo_in;
        client3.topo_out --> IdealChannel --> client2.topo_in;
        client2.topo_out --> IdealChannel --> client5.topo_in;
        client.topo_out --> IdealChannel --> client1.topo_in;
        client5.topo_out --> IdealChannel --> client.topo_in;
}


