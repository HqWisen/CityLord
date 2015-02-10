TARGET=case building field neighborhood map

all: $(TARGET)

case: Case.hpp Case.cpp
	g++ -Wall -std=c++11 -c Case.hpp Case.cpp

building: Building.hpp
	g++ -Wall -std=c++11 -c Building.hpp

field: Field.hpp Field.cpp
	g++ -Wall -std=c++11 -c Field.hpp Field.cpp

neighborhood: Neighborhood.hpp
	g++ -Wall -std=c++11 -c Neighborhood.hpp

map: Map.hpp Map.cpp
	g++ -Wall -std=c++11 -c Map.hpp Map.cpp

clean:
	$(RM) $(TARGET)