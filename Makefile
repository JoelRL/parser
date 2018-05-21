OBJS = src/*.cpp

CC = g++

COMPILER_FLAGS = -w -fno-exceptions

LINKER_FLAGS = -static-libgcc -static-libstdc++

OBJ_NAME = parser-v1

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)