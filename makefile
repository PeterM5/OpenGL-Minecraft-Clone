# the compiler:
CC = g++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS = -g -Wall

# includes:
INCLUDE = -I ./include/

# library dir
LDIR = -L./lib/

# libraries:
LIBS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

# source dir
SRC = ./src/

# The build target
TARGET = build


all: $(TARGET)

$(TARGET): $(SRC)*
	$(CC) -o $(TARGET) $(SRC)main.cpp $(SRC)glad.c $(CFLAGS) $(INCLUDE) $(LDIR) $(LIBS)



clean:
	rm $(TARGET)