CC=g++
OBJDIR=./obj
BINDIR=./bin
LIBS=-ldl -pthread
DIRS=-I.
CFLAGS=-std=c++0x -g

#############################
# Binary Config
#############################

SERVER_OBJ_LIST=imageFactory.o comicFrames.o frameDetect.o lodepng.o receiver.o sender.o worker.o main.o imagePreprocessor.o queue.o
SERVER_OBJ=$(patsubst %, $(OBJDIR)/%, $(SERVER_OBJ_LIST))
SERVER_DEPS=
SERVER_BIN=server

# This is just my secret target for doing quick and dirty tests
TEST_OBJ_LIST=lodepng.o test.o imageFactory.o imagePreprocessor.o 
TEST_OBJ=$(patsubst %, $(OBJDIR)/%, $(TEST_OBJ_LIST))
TEST_DEPS=zipdep/ioapi.o zipdep/unzip.o zipdep/libz.a
TEST_BIN=test

#############################
# Binary Targets
#############################

all: $(SERVER_BIN) 

$(SERVER_BIN): $(SERVER_OBJ) $(SERVER_DEPS)
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS) $(LIBS) $(DIRS)

$(TEST_BIN): $(TEST_OBJ) $(TEST_DEPS)
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS) $(LIBS) $(DIRS)

#############################
# Rules for building .o
#############################

$(OBJDIR)/%.o: %.cpp $(TEST_DEPS) folders
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

$(OBJDIR)/lodepng.o: lodepng/lodepng.cpp folders
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

#############################
# Phony Targets
#############################

.PHONY: clean lightclean folders

folders:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

lightclean:
	rm -rf *.gch

clean:
	rm -rf bin/* obj/* *.gch
