CXX      = clang++
CXXFLAGS = -g3 -std=c++20 -Ofast
LDFLAGS  = -g3 -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

SRC = src
INC = src/include
BIN = bin
OBJ = $(BIN)/obj

SOURCE_FILES = sulk.cpp main.cpp
OBJECT_FILES  = $(SOURCE_FILES:%.cpp=$(OBJ)/%.o)

build: sulk

run: sulk
	./sulk

clean:
	@echo Cleaning binaries
	@rm -rf bin
	@echo Cleaning executable
	@rm sulk

sulk: $(OBJECT_FILES)
	@echo Generating executable
	@$(CXX) $(LDFLAGS) -o $@ $^

$(OBJECT_FILES): $(OBJ)/%.o: $(SRC)/%.cpp $(INC)/%.h
	@mkdir -p $(@D)
	@echo Compiling $< to $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@