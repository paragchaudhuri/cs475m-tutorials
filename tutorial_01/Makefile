CC = g++

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LIBS = -lGL -lglut
endif
ifeq ($(UNAME_S),Darwin)
    LIBS = -framework OpenGL -framework GLUT
endif

SRC = tutorial_01.cpp
BIN = tutorial_01

all	:	$(BIN)

$(BIN)	:	$(SRC)
	$(CC) $(SRC) -o $(BIN) $(LIBS)

clean	:
	rm -f $(BIN) *~
