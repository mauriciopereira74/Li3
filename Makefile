###############
CC = cc 
IDIR = ../include

CFLAGS = -Wall -ansi `pkg-config --cflags --libs glib-2.0` -I$(IDIR)
#-------------
BIN_DIR = bin
BLD_DIR = build
INC_DIR = includes
SRC_DIR = src
#-------------
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%*.c,$(BLD_DIR)/%*.o,$(SRC))
#-------------
PROGRAM = programa-principal
##############

.DEFAULT_GOAL = build

build: setup $(BIN_DIR)/$(PROGRAM)

$(BIN_DIR)/$(PROGRAM): $(OBJS)
	$(CC) -I $(INC_DIR) $(CFLAGS) -o $@ $^
 
$(BLD_DIR)/%*.o: $(SRC_DIR)/%.c
	$(CC) -I $(INC_DIR) $(CFLAGS) -o $@ $^

.PHONY: setup
setup:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BLD_DIR)

.PHONY: clean
clean:
	@-rm -r $(BLD_DIR)
	@-rm $(BIN_DIR)/$(PROGRAM)
