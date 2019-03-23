CXX = g++

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

########

all: prog.exe

prog.exe: $(OBJ)
	$(CXX) $^ -o $@ -Wall -Wextra -std=c++14

clean:
		rm -f $(OBJ) prog.exe
		
rebuild: clean all

.PHONY: all clean
	
debug:
	echo $(SRC) $(OBJ)