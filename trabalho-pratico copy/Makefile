# Compilador
CC = gcc

CFLAGS= -std=gnu99 -Wall -O2 -lm $(shell pkg-config --cflags glib-2.0)
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

interpreter.o: $(SRC_DIR)/interpreter.c $(INC_DIR)/interpreter.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/interpreter.o -c $(SRC_DIR)/interpreter.c $(LDFLAGS)

profile.o: $(SRC_DIR)/profile.c $(INC_DIR)/profile.h
	$(COMPILER) $(CFLAGS) -o $(SRC_DIR)/profile.o -c $(SRC_DIR)/profile.c $(LDFLAGS)

rideAvr.o: $(SRC_DIR)/rideAvr.c $(INC_DIR)/rideAvr.h
	$(COMPILER) $(CFLAGS) -o $(SRC_DIR)/rideAvr.o -c $(SRC_DIR)/rideAvr.c $(LDFLAGS)

#list.o: $(SRC_DIR)/list.c $(INC_DIR)/list.h
#	$(COMPILER) $(CFLAGS) -o $(SRC_DIR)/list.o -c $(SRC_DIR)/list.c $(LDFLAGS)

programa-principal: $(SRC_DIR)/main.o $(SRC_DIR)/users.o $(SRC_DIR)/drivers.o $(SRC_DIR)/rides.o $(SRC_DIR)/parse_func.o $(SRC_DIR)/interpreter.o $(SRC_DIR)/profile.o $(SRC_DIR)/rideAvr.o #$(SRC_DIR)/list.o
	$(CC) $(CFLAGS) $(SRC_DIR)/main.o $(SRC_DIR)/users.o $(SRC_DIR)/drivers.o $(SRC_DIR)/rides.o $(SRC_DIR)/parse_func.o $(SRC_DIR)/interpreter.o $(SRC_DIR)/profile.o $(SRC_DIR)/rideAvr.o  -o ./programa-principal $(LDFLAGS)


memcheck:
	valgrind --leak-check=yes -s ./programa-principal

clean:
	rm -rf $(SRC_DIR)/*.o programa-principal
