# ***** Makefile of citylord ****** 

# -- client
CLIENT = citylord
DEPC = client socket models update thread server

# -- server
SERVER = citylordserver
DEPS = server request socket thread models

# -- gui

GUI = citylordgui

# -- test
TEST = testexe
DEPT = test models
# -- 

# -- Do not edit below this line --

TARGETS = $(CLIENT) $(SERVER) $(GUI)
# $(TEST)

DEPCA = $(addsuffix .a,$(addprefix $(BIN_DIR)/,$(DEPC)))
DEPSA = $(addsuffix .a,$(addprefix $(BIN_DIR)/,$(DEPS)))
DEPTA = $(addsuffix .a,$(addprefix $(BIN_DIR)/,$(DEPT)))

default: $(TARGETS)
client: $(CLIENT)
server: $(SERVER)
gui: $(GUI)
test: $(TEST)

include rules.mk

$(CLIENT): $(DEPCA)
	$(CC) $(FLAGS) $(DEPCA) -o $(CLIENT)

$(SERVER): $(DEPSA)
	$(CC) $(FLAGS) $(DEPSA) -o $(SERVER)

$(GUI):
	rm -f src/client/gui/makefile
	cd src/client/gui/; qmake -o makefile; cd -
	$(MAKE) -C src/client/gui/
	
$(TEST): $(DEPTA)
	$(CC) $(FLAGS) $(DEPTA) -o $(TEST)

$(BIN_DIR)/socket.a:	
	$(MAKE) -C src/common/socket
$(BIN_DIR)/thread.a:	
	$(MAKE) -C src/common/thread
$(BIN_DIR)/models.a:	
	$(MAKE) -C src/common/models
$(BIN_DIR)/client.a:
	$(MAKE) -C src/client
$(BIN_DIR)/server.a:
	$(MAKE) -C src/server
$(BIN_DIR)/request.a:
	$(MAKE) -C src/server/request
$(BIN_DIR)/update.a:
	$(MAKE) -C src/client/update
$(BIN_DIR)/test.a:
	$(MAKE) -C src/test
cleanexe:
	$(RM) $(TARGETS)
	
clean: cleanbin cleanexe
