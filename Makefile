SHELL = powershell.exe

CXXFLAGS = -std=c++20

INC_DIRS = \
	"./SFML/include" \
	"./headers/Frontend" \
	"./headers/Backend" \
	"."
LIB_DIRS = "./SFML/lib"

LDLIBS = -lsfml-graphics -lsfml-network -lsfml-window -lsfml-main -lsfml-system

BIN = TreeVisualizer

BUILD_DIR = ./release
JUNK_DIR = $(BUILD_DIR)/junk
SRC_DIR = ./src/Frontend ./src/Backend .

CPP_FILES = $(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.cpp))
OBJ_FILES = $(CPP_FILES:%.cpp=$(JUNK_DIR)/%.o)
DEP_FILES = $(OBJ_FILES:%.o=%.d)

all: pre-build $(BUILD_DIR)/$(BIN)

pre-build:
	-$(foreach dir,$(SRC_DIR),mkdir "$(JUNK_DIR)/$(dir)";)

$(BUILD_DIR)/$(BIN): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(^:%="%") -o $@ $(LIB_DIRS:%=-L%) $(LDLIBS)

$(JUNK_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@ $(INC_DIRS:%=-I%)

-include $(DEP_FILES)

clean:
	-rm -force "$(BUILD_DIR)/*.exe"
	-$(foreach dir,$(SRC_DIR),rm -force "$(JUNK_DIR)/$(dir)/*.o";)
	-$(foreach dir,$(SRC_DIR),rm -force "$(JUNK_DIR)/$(dir)/*.d";)

rebuild: clean all
