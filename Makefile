# Makefile for cosmoball

# G++ compiler options
CXX = g++
CXXFLAGS = -g

# linker options
LDLIBS = sfml-graphics sfml-audio sfml-window sfml-system

# File dependencies, groupings, and names
APTDEPENDENCIES = libsfml-dev

# Default functions for using make
.PHONY: clean depends
.DEFAULT: cosmoball
clean:
	git clean -xfd
depends:
	sudo apt-get -y install ${APTDEPENDENCIES}

# Main executable
cosmoball: main.o Entity.o Button.o TileMap.o
	@$(CXX) $(CXXFLAGS) $(LDLIBS:%=-l%) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^