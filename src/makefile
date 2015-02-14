TARGETS = clientexe serverexe
default: $(TARGETS)

include rules.mk

clientexe: $(BIN_DIR)/socket.a $(BIN_DIR)/client.a
	$(CC) $(FLAGS) $(BIN_DIR)/client.a $(BIN_DIR)/socket.a -o clientexe

serverexe: $(BIN_DIR)/socket.a $(BIN_DIR)/server.a
	$(CC) $(FLAGS) $(BIN_DIR)/server.a $(BIN_DIR)/socket.a -o serverexe
	
testexe: $(BIN_DIR)/socket.a  $(BIN_DIR)/lib.a  $(BIN_DIR)/client.a  $(BIN_DIR)/server.a $(BIN_DIR)/test.a
	$(CC) $(FLAGS) $(BIN_DIR)/test.a $(BIN_DIR)/socket.a $(BIN_DIR)/lib.a  $(BIN_DIR)/client.a  $(BIN_DIR)/server.a -o testexe


$(BIN_DIR)/socket.a:	
	$(MAKE) -C common/socket
$(BIN_DIR)/lib.a:	
	$(MAKE) -C common/lib
$(BIN_DIR)/client.a:
	$(MAKE) -C client
$(BIN_DIR)/server.a:
	$(MAKE) -C server
	
cleanexe:
	$(RM) $(TARGETS)
	
clean: cleanobj cleanbin cleanexe
