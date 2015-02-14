RM = rm -rf

CC = g++
AR  = ar
FLAGS = -g -Wall -std=c++11
ROOT=$(shell git rev-parse --show-toplevel)
BIN_DIR = $(ROOT)/bin

SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.hpp)
OBJECTS=$(addprefix  $(BIN_DIR)/$(NAME)/, $(subst .cpp,.o,$(SOURCES)))



build: $(BIN_DIR)/$(NAME).a $(OBJECTS)

$(BIN_DIR)/$(NAME)/%.o: %.cpp $(HEADERS) $(BIN_DIR)/$(NAME)/
	$(CC) $(FLAGS) -c $< -o $@

$(BIN_DIR)/$(NAME).a: $(OBJECTS)
	$(AR) rcu $@ $(OBJECTS)

	
$(BIN_DIR)/$(NAME)/:
	@mkdir -p $@

.PHONY: clean
cleanobj:
	$(RM) $(OBJECTS)
cleanbin:
	$(RM) $(BIN_DIR)
clean: cleanobj

