all: server

server:
	g++ -pthread server.cpp -o server -w
