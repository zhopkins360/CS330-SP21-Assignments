###############################################################################
# server-python.py
# Name:Zackary Hopkins
###############################################################################

import sys
import socket

RECV_BUFFER_SIZE = 2048
QUEUE_LENGTH = 10

def server(server_port):
    global s 
    s = None
    ##finds a socket with both ip address types and TCP stream spesifications
    res = socket.getaddrinfo(None, server_port, socket.AF_UNSPEC, socket.SOCK_STREAM, 0, socket.AI_PASSIVE)
    #takes the first result from the liast and splites the tuple into 5 vars
    af, socktype, proto, canoname, sa = res[0]
    #creates the fd with the right family, socket type and protocal
    s = socket.socket(af, socktype, proto)
    #binds the socket and sets up the listen
    s.bind(sa)
    s.listen(1)
    while True:
        ##accepts the clients connection and creates a new fd to use
        new_s, clientAddr = s.accept()
        #takes the data that was in ascii bytes then decodes it into a str
        data = new_s.recv(RECV_BUFFER_SIZE)
        data_str = data.decode('ascii')
        #loop while there is data still being received
        while not len(data_str) == 0:
            #prints out the data gotten
            print(data_str,end='')
            #tries to read more data from stdin
            data = new_s.recv(RECV_BUFFER_SIZE)
            data_str = data.decode('ascii')
        #pushes the output in stdout
        sys.stdout.flush()
        #closes the clients socket
        new_s.close()
            
    pass

def main():
    """Parse command-line argument and call server function """
    if len(sys.argv) != 2:
        sys.exit("Usage: python3 server-python.py [Server Port]")
    server_port = int(sys.argv[1])
    server(server_port)

if __name__ == "__main__":
    main()
