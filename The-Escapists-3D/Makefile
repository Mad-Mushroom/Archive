COMPILER=g++
SRC-DIR=src/*.cpp
BIN-DIR=bin/escapists3d
CPP-FLAGS-WIN=-Wall -o $(BIN-DIR) $(SRC-DIR)
LD-FLAGS-WIN=-lglu32 -lglut32 -lopengl32 -static-libstdc++
CPP-FLAGS-OSX=-Wall -o $(BIN-DIR) $(SRC-DIR)
LD-FLAGS-OSX=-lglut -framework OpenGL -static-libstdc++
CPP-FLAGS-LINUX=-Wall -o $(BIN-DIR) $(SRC-DIR)
LD-FLAGS-LINUX=-static-libstdc++

win.compile:
	$(COMPILER) $(CPP-FLAGS-WIN) $(LD-FLAGS-WIN)

win.compile.run:
	$(COMPILER) $(CPP-FLAGS-WIN) $(LD-FLAGS-WIN)
	$(BIN-DIR) -launched

osx.compile:
	$(COMPILER) $(CPP-FLAGS-OSX) $(LD-FLAGS-OSX)

osx.compile.run:
	$(COMPILER) $(CPP-FLAGS-OSX) $(LD-FLAGS-OSX)
	$(BIN-DIR) -launched

linux.compile:
	$(COMPILER) $(CPP-FLAGS-LINUX) $(LD-FLAGS-LINUX)

linux.compile.run:
	$(COMPILER) $(CPP-FLAGS-LINUX) $(LD-FLAGS-LINUX)
	$(BIN-DIR) -launched