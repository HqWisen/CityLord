# ***** Makefile of exe ****** 
# DON'T CALL AN EXECUTABLE WITH A PACKAGE NAME !

# -- client
CLIENT = citylord
DEPC = client socket lib

# -- server
SERVER = citylordserver
DEPS = server request socket thread lib
# -- test
TEST = testexe
DEPT = test socket lib
# -- 

# -- Do not edit below this line --

TARGETS = $(CLIENT) $(SERVER)
# $(TEST)

DEPCA = $(addsuffix .a,$(addprefix $(BIN_DIR)/,$(DEPC)))
DEPSA = $(addsuffix .a,$(addprefix $(BIN_DIR)/,$(DEPS)))
DEPTA = $(addsuffix .a,$(addprefix $(BIN_DIR)/,$(DEPT)))
default: $(TARGETS)
client: $(CLIENT)
server: $(SERVER)
test: $(TEST)

include rules.mk

$(CLIENT): $(DEPCA)
	$(CC) $(FLAGS) $(DEPCA) -o $(CLIENT)

$(SERVER): $(DEPSA)
	$(CC) $(FLAGS) $(DEPSA) -o $(SERVER)
	
$(TEST): $(DEPTA)
	$(CC) $(FLAGS) $(DEPTA) -o $(TEST)

$(BIN_DIR)/socket.a:	
	$(MAKE) -C common/socket
$(BIN_DIR)/thread.a:	
	$(MAKE) -C common/thread
$(BIN_DIR)/lib.a:	
	$(MAKE) -C common/lib
$(BIN_DIR)/client.a:
	$(MAKE) -C client
$(BIN_DIR)/server.a:
	$(MAKE) -C server
$(BIN_DIR)/request.a:
	$(MAKE) -C server/request
$(BIN_DIR)/test.a:
	$(MAKE) -C test
cleanexe:
	$(RM) $(TARGETS)
	
clean: cleanobj cleanbin cleanexe
