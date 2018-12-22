GCC := gcc
RM := rm
TARGET := 537malloc
CPPFLAGS := -pthread -Wall -Wextra -g
OBJECTS	:= AVL.o traverse.o 537malloc.o main.o

all: $(OBJECTS)
	$(GCC) $(OBJECTS) -o $(TARGET) $(CPPFLAGS)

main.o: main.c
	$(GCC) $(CPPFLAGS) -c main.c -o main.o

AVL.o: AVL.c
	$(GCC) $(CPPFLAGS) -c AVL.c -o AVL.o

traverse.o: traverse.c
	$(GCC) $(CPPFLAGS) -c traverse.c -o traverse.o
 
537malloc.o: 537malloc.c
	$(GCC) $(CPPFLAGS) -c 537malloc.c -o 537malloc.o

clean:
	$(RM) $(OBJECTS) $(TARGET)
