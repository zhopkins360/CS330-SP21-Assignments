###############################################################################
# server-python.py
# Name:Zackary Hopkins
###############################################################################

import sys
import socket

RECV_BUFFER_SIZE = 2048
QUEUE_LENGTH = 10

def server(server_port):
    """TODO: Listen on socket and print received message to sys.stdout"""
    global s 
    s = None
    ##finds a socket with both ip address types and TCP stream spesifications
    for res in socket.getaddrinfo(None, server_port, socket.AF_UNSPEC, socket.SOCK_STREAM, 0, socket.AI_PASSIVE):
        af, socktype, proto, canoname, sa = res
        try:
            s = socket.socket(af, socktype, proto)
        except OSError as msg:
            s = None
            continue
        try:
            s.bind(sa)
            s.listen(1)
        except OSError as msg:
            s.close()
            s = None
            continue
        break

    ##accepts the clients connection and gives fd and their address
    while True:
        new_s, clientAddr = s.accept()
        with new_s:
            data = new_s.recv(RECV_BUFFER_SIZE)
            data_str = data.decode()
            print(data_str,end="")
            sys.stdout.flush()
            new_s.close()
            
    pass

def main():
    """Parse command-line argument and call server function """
    if len(sys.argv) != 2:
        sys.exit("Usage: python server-python.py [Server Port]")
    server_port = int(sys.argv[1])
    server(server_port)

if __name__ == "__main__":
    main()
