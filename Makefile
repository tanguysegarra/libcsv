CXX = g++
CC = $(CXX)
CXXFLAGS = -Wall -Werror -Wextra -std=c++17 -pedantic -O3 -Iinclude

VPATH = src/

BIN = main
OBJ = \
      main.o \

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ)

clean:
	$(RM) $(BIN) $(OBJ)
