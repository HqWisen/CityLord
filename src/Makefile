TARGET=case building field neighborhood map server
OBJECTS = Socket.o
# ClientSocket.o ServerSocket.o
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

server : server.o Socket.o
	$(GC) $(FLAGS) Socket.o server.o -o server

server.o : server.cpp Socket.cpp
	$(GC) $(FLAGS) -c server.cpp -o server.o

Socket.o :  Socket.hpp Socket.cpp
	$(GC) $(FLAGS) -c Socket.cpp -o Socket.o
#ClientSocket.o :  ClientSocket.hpp ClientSocket.cpp
#	g++ $(FLAGS) -c ClientSocket.cpp -o ClientSocket.o
#ServerSocket.o :  ServerSocket.hpp ServerSocket.cpp
#	g++ $(FLAGS) -c ServerSocket.cpp -o ServerSocket.o

clean:
	$(RM) $(TARGET)
	$(RM) $(OBJECTS)