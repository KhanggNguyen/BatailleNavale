
CXX=g++
CXXFLAGS= -Wall -ansi -pedantic -g -lncurses -std=c++11
LDFLAGS= 
EXEC=BatNavale 

all: $(EXEC)

BatNavale: main.o  bateau.o option.o selection.o setup.o tabOptions.o terrain.o window.o joueur.o jouer.o
	$(CXX) -o BatNavale main.o  bateau.o option.o selection.o setup.o tabOptions.o terrain.o window.o joueur.o jouer.o $(CXXFLAGS)

main.o: main.cpp window.h jouer.h setup.h
	$(CXX) -o main.o -c main.cpp $(CXXFLAGS)

bateau.o: bateau.cpp bateau.h
	$(CXX) -o bateau.o -c bateau.cpp $(CXXFLAGS)

option.o: option.cpp option.h
	$(CXX) -o option.o -c option.cpp $(CXXFLAGS)

selection.o: selection.cpp selection.h
	$(CXX) -o selection.o -c selection.cpp $(CXXFLAGS)

setup.o: setup.cpp setup.h 
	$(CXX) -o setup.o -c setup.cpp $(CXXFLAGS)

tabOptions.o: tabOptions.cpp tabOptions.h
	$(CXX) -o tabOptions.o -c tabOptions.cpp $(CXXFLAGS)

terrain.o: terrain.cpp terrain.h setup.h
	$(CXX) -o terrain.o -c terrain.cpp $(CXXFLAGS)

window.o: window.cpp window.h
	$(CXX) -o window.o -c window.cpp $(CXXFLAGS)

joueur.o: joueur.cpp joueur.h
	$(CXX) -o joueur.o -c joueur.cpp $(CXXFLAGS)

jouer.o: jouer.cpp jouer.h
	$(CXX) -o jouer.o -c jouer.cpp $(CXXFLAGS)

# DO NOT DELETE

window.o: /usr/include/curses.h /usr/include/ncurses_dll.h
window.o: /usr/include/stdint.h /usr/include/features.h
window.o: /usr/include/stdc-predef.h /usr/include/stdio.h
window.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
window.o: /usr/include/unctrl.h
