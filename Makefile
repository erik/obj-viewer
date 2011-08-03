CC	:= clang++
IFLAGS 	:= -I include/
CFLAGS	:= -Wall -Wextra -Wno-unused-parameter -std=c++98
DFLAGS	:= -g -DDEBUG

LNFLAGS	:= -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system -lm -lGL -lGLU
EXE 	:= objviewer

.SUFFIXES=.cpp

SRC 	:= $(shell find 'src' -name '*.cpp' )
OBJ 	:= $(SRC:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(IFLAGS) $(LNFLAGS) -o$(EXE)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(EXE)

debug:
	@$(MAKE) $(MFLAGS) CFLAGS="$(CFLAGS) $(DFLAGS)"

.PHONY= all clean debug
