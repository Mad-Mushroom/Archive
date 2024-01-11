COMPILER = g++
NAME = Apocalypse
OUTPUT = $(BIN-DIR)/$(NAME)
SRC-DIR = ./src
BIN-DIR = ./bin
FILES = $(shell find $(SRC-DIR) -name '*.cpp')
COMPILER-FLAGS = -Wall -std=c++11
LINKER-FLAGS = -lraylib

compile:
	$(COMPILER) $(COMPILER-FLAGS) -o $(OUTPUT) $(FILES) $(LINKER-FLAGS)

run:
	$(OUTPUT)

compile.run:
	$(COMPILER) $(COMPILER-FLAGS) -o $(OUTPUT) $(FILES) $(LINKER-FLAGS)
	$(OUTPUT)

clean:
	rm $(OUTPUT)

compile.run.clean:
	$(COMPILER) $(COMPILER-FLAGS) -o $(OUTPUT) $(FILES) $(LINKER-FLAGS)
	$(OUTPUT)
	rm $(OUTPUT)
