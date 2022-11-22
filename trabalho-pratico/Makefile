CC = gcc 
CFLAGS = -Wall -ansi `pkg-config --cflags --libs glib-2.0` -I$(IDIR)
COMPILER=gcc
HEADERS=libs
SRC=src
OBJ=obj

all: main parser hashtables interpreter profile rideAvr

main: $(SRC)/main.c $(HEADERS)/main.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/main.o $(PKG) -c $(SRC)/main.c

parser: $(SRC)/parser.c $(HEADERS)/parser.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/parser.o $(PKG) -c $(SRC)/parser.c

hashtables: $(SRC)/hashtables.c $(HEADERS)/hashtables.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/hashtables.o $(PKG) -c $(SRC)/hashtables.c

interpreter: $(SRC)/interpreter.c $(HEADERS)/interpreter.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/interpreter.o $(PKG) -c $(SRC)/interpreter.c

profile: $(SRC)/profile.c $(HEADERS)/profile.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/profile.o $(PKG) -c $(SRC)/profile.c

rideAvr: $(SRC)/rideAvr.c $(HEADERS)/rideAvr.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/rideAvr.o $(PKG) -c $(SRC)/rideAvr.c


programa-principal: $(SRC)/main.c $(OBJ)/main.o $(OBJ)/parser.o $(OBJ)/hashtables.o $(OBJ)/interpreter.o $(OBJ)/profile.o $(OBJ)/rideAvr.o
	$(COMPILER) $(FLAGS) $(OBJ)/parser.o $(OBJ)/hashtables.o $(OBJ)/interpreter.o $(OBJ)/profile.o $(OBJ)/rideAvr.o $(OBJ)/main.o  -o programa-principal


memcheck:
	valgrind --leak-check=yes -s ./programa-principal

clean:
	rm -rf $(OBJ)/*.o programa-principal
