###############################################################################
# client-python.py
# Name:Zackary Hopkins
###############################################################################

import sys
import socket

SEND_BUFFER_SIZE = 2048

def client(server_ip, server_port):
    
    global s 
    s = None
    ##finds a socket with both ip address types and TCP stream spesifications
    res = socket.getaddrinfo(server_ip, server_port, socket.AF_UNSPEC, socket.SOCK_STREAM)
    #sets vars to be used in making the socket
    af, socktype, proto, canonname, sa = res[0]
    #tries to create the socket if not loops back
    s = socket.socket(af, socktype, proto)
    #tries to connect on the socket 
    s.connect(sa)

    #reads in data from the data in stdin
    _input = sys.stdin.read(SEND_BUFFER_SIZE)
    #loop to check if there is more data to send
    while not len(_input) == 0:
        #turns the str into ascii bytes
        byteInput = bytes(_input,'ascii')
        #sends the bytes to the serve
        s.send(byteInput,SEND_BUFFER_SIZE)
        #reads more data from stdin
        _input = sys.stdin.read(SEND_BUFFER_SIZE)
    #closes the socket
    s.close()
    pass

def main():
    """Parse command-line arguments and call client function """
    if len(sys.argv) != 3:
        sys.exit("Usage: python3 client-python.py [Server IP] [Server Port] < [message]")
    server_ip = sys.argv[1]
    server_port = int(sys.argv[2])
    client(server_ip, server_port)

if __name__ == "__main__":
    main()
