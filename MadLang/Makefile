COMPILER = g++
NAME = MadLang
OUTPUT = $(BIN-DIR)/$(NAME)
SRC-DIR = ./src
BIN-DIR = ./bin
FILES = $(SRC-DIR)/*.cpp $(SRC-DIR)/lexer/*.cpp
COMPILER-FLAGS = -Wall
#LINKER-FLAGS =

build:
	$(COMPILER) $(COMPILER-FLAGS) -o $(OUTPUT) $(FILES) $(LINKER-FLAGS)

run:
	./$(OUTPUT)

build.run:
	$(COMPILER) $(COMPILER-FLAGS) -o $(OUTPUT) $(FILES) $(LINKER-FLAGS)
	./$(OUTPUT)

clean:
	rm $(OUTPUT)

build.run.clean:
	$(COMPILER) $(COMPILER-FLAGS) -o $(OUTPUT) $(FILES) $(LINKER-FLAGS)
	./$(OUTPUT)
	rm $(OUTPUT)
