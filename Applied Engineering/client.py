import zmq
import sys

port = "5556"
ip = "192.168.0.55"


context = zmq.Context()
print("Connecting to server...")
socket = context.socket(zmq.REQ)
socket.connect ("tcp://" + ip + ":" + port)


for request in range (1,10):
    print("Sending request ", request,"...")
    socket.send_string("Hello")
    message = socket.recv()
    print("Received reply ", request, "[", message, "]")