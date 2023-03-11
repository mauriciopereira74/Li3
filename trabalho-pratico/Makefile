# Compilador
CC = gcc

CFLAGS= -Wall -O3 -lm $(shell pkg-config --cflags glib-2.0)
CFLAGS_T = --std=gnu99 -Wall -O2 

LDFLAGS=$(shell pkg-config --libs glib-2.0) 
LDFLAGS_T=-lm $(shell pkg-config --libs glib-2.0)

INC_DIR=includes
SRC_DIR=src


all: programa-principal

main.o: $(SRC_DIR)/main.c 
	$(CC) $(CFLAGS) -o $(SRC_DIR)/main.o -c $(SRC_DIR)/main.c $(LDFLAGS)

users.o: $(SRC_DIR)/users.c $(INC_DIR)/users.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/users.o -c $(SRC_DIR)/users.c $(LDFLAGS)

drivers.o: $(SRC_DIR)/drivers.c $(INC_DIR)/drivers.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/drivers.o -c $(SRC_DIR)/drivers.c $(LDFLAGS)

rides.o: $(SRC_DIR)/rides.c $(INC_DIR)/rides.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/rides.o -c $(SRC_DIR)/rides.c $(LDFLAGS)

parse_func.o: $(SRC_DIR)/parse_func.c $(INC_DIR)/parse_func.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/parse_func.o -c $(SRC_DIR)/parse_func.c $(LDFLAGS)

user_interface.o: $(SRC_DIR)/user_interface.c $(INC_DIR)/user_interface.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/user_interface.o -c $(SRC_DIR)/user_interface.c $(LDFLAGS)

interpreter.o: $(SRC_DIR)/interpreter.c $(INC_DIR)/interpreter.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/interpreter.o -c $(SRC_DIR)/interpreter.c $(LDFLAGS)

querie_aux.o: $(SRC_DIR)/querie_aux.c $(INC_DIR)/querie_aux.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/querie_aux.o -c $(SRC_DIR)/querie_aux.c $(LDFLAGS)

queries_itr.o: $(SRC_DIR)/queries_itr.c $(INC_DIR)/queries_itr.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/queries_itr.o -c $(SRC_DIR)/queries_itr.c $(LDFLAGS)

queries.o: $(SRC_DIR)/queries.c $(INC_DIR)/queries.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/queries.o -c $(SRC_DIR)/queries.c $(LDFLAGS)

programa-principal: $(SRC_DIR)/main.o $(SRC_DIR)/users.o $(SRC_DIR)/drivers.o $(SRC_DIR)/rides.o $(SRC_DIR)/parse_func.o $(SRC_DIR)/user_interface.o $(SRC_DIR)/interpreter.o $(SRC_DIR)/querie_aux.o $(SRC_DIR)/queries.o $(SRC_DIR)/queries_itr.o  
	$(CC) -o ./programa-principal $(SRC_DIR)/main.o $(SRC_DIR)/users.o $(SRC_DIR)/drivers.o $(SRC_DIR)/rides.o $(SRC_DIR)/parse_func.o $(SRC_DIR)/user_interface.o $(SRC_DIR)/interpreter.o $(SRC_DIR)/queries.o $(SRC_DIR)/querie_aux.o $(SRC_DIR)/queries_itr.o $(LDFLAGS) $(CFLAGS)


memcheck:
	valgrind --leak-check=yes -s ./programa-principal

clean:
	rm -rf $(SRC_DIR)/*.o programa-principal
