# Compilador
CC = gcc

CFLAGS= -std=gnu99 -Wall -O2 $(shell pkg-config --cflags glib-2.0)
CFLAGS_T = --std=gnu99 -Wall -O2 $(shell pkg-config --cflags libcpuid) $(shell pkg-config --cflags glib-2.0)

LDFLAGS=$(shell pkg-config --libs glib-2.0) $(shell pkg-config --libs libcpuid) -lm
LDFLAGS_T=-lm $(shell pkg-config --libs libcpuid) $(shell pkg-config --libs glib-2.0)

INC_DIR=includes
SRC_DIR=src


all: programa-principal

main.o: $(SRC_DIR)/main.c 
	$(CC) $(CFLAGS) -o $(SRC_DIR)/main.o $(PKG) -c $(SRC_DIR)/main.c

users.o: $(SRC_DIR)/users.c $(INC_DIR)/users.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/users.o $(PKG) -c $(SRC_DIR)/users.c

drivers.o: $(SRC_DIR)/drivers.c $(INC_DIR)/drivers.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/drivers.o $(PKG) -c $(SRC_DIR)/drivers.c

rides.o: $(SRC_DIR)/rides.c $(INC_DIR)/rides.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/rides.o $(PKG) -c $(SRC_DIR)/rides.c

parse_func.o: $(SRC_DIR)/parse_func.c $(INC_DIR)/parse_func.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/parse_func.o $(PKG) -c $(SRC_DIR)/parse_func.c

interpreter.o: $(SRC_DIR)/interpreter.c $(INC_DIR)/interpreter.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/interpreter.o $(PKG) -c $(SRC_DIR)/interpreter.c

profile.o: $(SRC_DIR)/profile.c $(INC_DIR)/profile.h
	$(COMPILER) $(CFLAGS) -o $(SRC_DIR)/profile.o $(PKG) -c $(SRC_DIR)/profile.c

rideAvr.o: $(SRC_DIR)/rideAvr.c $(INC_DIR)/rideAvr.h
	$(COMPILER) $(CFLAGS) -o $(SRC_DIR)/rideAvr.o $(PKG) -c $(SRC_DIR)/rideAvr.c


programa-principal: $(SRC_DIR)/main.o $(SRC_DIR)/users.o $(SRC_DIR)/drivers.o $(SRC_DIR)/rides.o $(SRC_DIR)/parse_func.o $(SRC_DIR)/interpreter.o $(SRC_DIR)/profile.o $(SRC_DIR)/rideAvr.o
	$(CC) $(CFLAGS) $(SRC_DIR)/users.o $(SRC_DIR)/drivers.o $(SRC_DIR)/rides.o $(SRC_DIR)/parse_func.o $(SRC_DIR)/interpreter.o $(SRC_DIR)/profile.o $(SRC_DIR)/rideAvr.o $(SRC_DIR)/main.o $(PKG) -o ./programa-principal


memcheck:
	valgrind --leak-check=yes -s ./programa-principal

clean:
	rm -rf $(SRC_DIR)/*.o programa-principal
