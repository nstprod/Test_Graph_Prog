CC = gcc
//CFLAGS = -Wall -Wextra -pedantic
OBJ = test.o
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) 

clean:
	rm -f $(OBJ) $(TARGET) 
	rm output/*