# Usurper's Retribution Makefile ... you'll want SDL newer than 1.2.5 installed, probably...

CPP  = g++
CC   = gcc
OBJ  = ur.o ur_object.o ur_layer.o ur_sprite.o ur_map.o ur_menu.o ur_font.o ur_titlescreen.o ur_audio.o
LIBS =  `sdl-config --libs` `pkg-config --libs libopenmpt`
INCS =  
BIN  = ur
CXXFLAGS = $(INCS) -std=c++17 `sdl-config --cflags` -g -Wall -Wno-deprecated `pkg-config --cflags libopenmpt`

.PHONY: all all-before all-after clean clean-custom

all: all-before ur all-after


clean: clean-custom
	rm -f $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o "ur" $(LIBS)  $(CXXFLAGS)

ur.o: ur.cpp
	$(CPP) -c ur.cpp -o ur.o $(CXXFLAGS)

ur_object.o: ur_object.cpp
	$(CPP) -c ur_object.cpp -o ur_object.o $(CXXFLAGS)

ur_layer.o: ur_layer.cpp
	$(CPP) -c ur_layer.cpp -o ur_layer.o $(CXXFLAGS)

ur_sprite.o: ur_sprite.cpp
	$(CPP) -c ur_sprite.cpp -o ur_sprite.o $(CXXFLAGS)

ur_map.o: ur_map.cpp
	$(CPP) -c ur_map.cpp -o ur_map.o $(CXXFLAGS)

ur_menu.o: ur_menu.cpp
	$(CPP) -c ur_menu.cpp -o ur_menu.o $(CXXFLAGS)

ur_font.o: ur_font.cpp
	$(CPP) -c ur_font.cpp -o ur_font.o $(CXXFLAGS)

ur_titlescreen.o: ur_titlescreen.cpp
	$(CPP) -c ur_titlescreen.cpp -o ur_titlescreen.o $(CXXFLAGS)

ur_audio.o: ur_audio.cpp
	$(CPP) -c ur_audio.cpp -o ur_audio.o $(CXXFLAGS)
