###############################################################################
# client-python.py
# Name:Zackary Hopkins
###############################################################################

import sys
import socket

SEND_BUFFER_SIZE = 2048

def client(server_ip, server_port):
    """TODO: Open socket and send message from sys.stdin"""
    _input = sys.stdin
    _input = _input.read(SEND_BUFFER_SIZE)
    
    global s 
    s = None
    ##finds a socket with both ip address types and TCP stream spesifications
    for res in socket.getaddrinfo(server_ip, server_port, socket.AF_UNSPEC, socket.SOCK_STREAM):
        #sets vars to be used in making the socket
        af, socktype, proto, canonname, sa = res
        #tries to create the socket if not loops back
        try:
            s = socket.socket(af, socktype, proto)
        except OSError as msg:
            s = None
            continue
        #tries to connect on the socket 
        try:
            s.connect(sa)
        except OSError as msg:
            s.close()
            s = None
            continue
        break
    
    s.send(_input.encode(),SEND_BUFFER_SIZE)
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
