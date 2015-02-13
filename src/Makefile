TARGET=case building field neighborhood map server client
OBJECTS = Socket.o Map.o Field.o Case.o Building.o ClientSocket.o ServerSocket.o server.o ClientSocket.o ServerSocket.o
FLAGS = -g -Wall -std=c++11
GC = g++

all: $(TARGET)

case: Case.hpp Case.cpp
	$(GC) $(FLAGS)  -c Case.hpp Case.cpp

building: Building.hpp
	$(GC) $(FLAGS) -c Building.hpp

field: Field.hpp Field.cpp
	$(GC) $(FLAGS) -c Field.hpp Field.cpp

neighborhood: Neighborhood.hpp
	$(GC) $(FLAGS) -c Neighborhood.hpp

map: Map.hpp Map.cpp
	$(GC) $(FLAGS) -c Map.hpp Map.cpp

server : server.o ServerSocket.o ClientSocket.o Socket.o
	$(GC) $(FLAGS) server.o ServerSocket.o ClientSocket.o Socket.o -o server

client : client.o Socket.o ServerSocket.o ClientSocket.o
	$(GC) $(FLAGS) Socket.o ServerSocket.o client.o ClientSocket.o -o client

client.o : client.cpp
	$(GC) $(FLAGS) -c client.cpp -o client.o
	
server.o : server.cpp
	$(GC) $(FLAGS) -c server.cpp -o server.o

Socket.o :  Socket.hpp Socket.cpp
	$(GC) $(FLAGS) -c Socket.cpp -o Socket.o
ClientSocket.o :  ClientSocket.hpp ClientSocket.cpp
	$(GC) $(FLAGS) -c ClientSocket.cpp -o ClientSocket.o
ServerSocket.o :  ServerSocket.hpp ServerSocket.cpp
	$(GC) $(FLAGS) -c ServerSocket.cpp -o ServerSocket.o


clean:
	$(RM) $(TARGET)
	$(RM) $(OBJECTS)
