# Server_Client_Process_Implemented_Using_Socket(AF_INET) and_Thread

# Project : Implementation of Socket (AF_INET) 

Author : Sajan Kumar Jha

Description : This project best explains the working of network socket.  Here we are using socket to perform end point communication between 2 process running on 2 different machine/sytems.
                               
                               ____________________                           ________________________
                               |                  |                           |                      |
                               |                  |                           |                      |
                               |    system 1      |                           |       system 2       |
                               |                  |                           |                      |        
                               |                  |                           |                      |
                               ____________________                           _________________________
                               
                                    process X                                            Process Y
                                        | FD                                             FD |
                                     ~~~~~~~~                                            ~~~~~~~~~        
                                     Socket 1                                             Socket 2
                                     ~~~~~~~~                                            ~~~~~~~~~   
                                         |__IP/port_no____|     Network      |__IP/port_no__|
                                                          |__________________| 
                               
  so, basically the above diagram briefly explains what actually is being happening in this project so lets understand this. lets assume that process x is a server process and process y be a client process.
  Now socket is a communication end point,here process x which is server is getting connected with socket using file descriptor(FD) and the other end of the socket is getting connected with the network using
  IP/port no and then from network,another socket is connected on the other side which is eventually get connected to process Y which is a client process.

  # Steps for ESTABLISHING SOCKECT CONN. at server
    
    1.fetch file descriptor using int socket(Domain,type,protocol);
                  * Domain : AF_UNIX,AF_INET
                  * type   : Connection-Oriented(SOCK_STREAM),Connection-less(SOCK_DGRAM)
                  * protocol: TCP/UDP(3rd layer protocol),IP(layer 2 protocol)

    2. Now use bind(file_descriptor,(struct sockaddr*)&addr,addrlen) function to give name to socket which will be visible in the network.
                  * struct sockaddr {
                                        short int sin_family;
                                        int sin_port;
                                        struct in_addr sin_addr;
                                      };
                    here in sin_family we have to take AF_INET,
                    in sin_port we'll mention the port number that will common on both server and client side as htons(5000),
                    in sin_addr.s_addr = htonl (INADDR_ANY) <------------------------------------------------- on Server side.
                    in sin_addr.s_addr = inet_addr("IP address of server") <---------------------------------- on Client side.
                  * socklen_t len = sizeof (struct sockadd_in);
       Thus this ends up the socket initialization.
     3. Now its time to listen up the call from the client side by using listen call as listen(file descriptor,queue depth);
                  * here queue depth is number indication the no. of client request queued as server process one by one.
     4. Now , Accept request using int accept(file descriptor,Client socket address format, address length);
        As this will be done after performing some checks as follows:
          1. address format compatiability
          2. domain compatiability
          3. type compatiability
          4. protocol compatiability
          if all this parameter is checked and passed then accept call will return a new file descriptor of psudo port which will be used by server (exclusively to communicated with that particular requesting client) and thus by using
          read() and write() calls both server and client can communicate with each other.
     5. finally the close(file descriptor) will be used to close the communication channel.
  
  # Steps for ESTABLISHING SOCKET CONN. at client ends
    
    1. int Socket(Domain,type,protocol) call <--- return the file descriptor
    2. Use connect(file descriptor,server socket address format,address length);
    3. When connection is successfull, then use read()/write() call to communicate with server
    4. finally close the channel using close(file descriptor);
    
 Now, here for each connect request the server is creating a new Thread which communicate with the client,gets the processed output from another server which is basically a process server and deliver it back to the client.
 after the data is delievered to the client the socket is closed and thread exit eventually.
                    
                               
                               
                               -
