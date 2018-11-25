# Put this makefile inside the src directory (with all the cpp files)

# The compiler to be used
CC = g++

# Path to header files
HDIR = ./headers

# Locate the directory for #include, so instead of doing #include "path/to/header.h", we can just do #include "header.h"
CFLAGS = -I$(HDIR)

# Path to object files
ODIR = ./obj

# Path to library files
LDIR = ../lib
LIBS = -lm

#### CHANGE THIS if adding more header files (automatically include the .h file) ####
_DEPS = Vect.h Ray.h Color.h Light.h Object.h Plane.h Sphere.h Camera.h Source.h

# $(patsubst pattern,replacement,text)
DEPS = $(patsubst %,$(HDIR)/%,$(_DEPS))

#### CHANGE THIS if adding more cpp files (but not .h file) ####
SOURCES = $(_DEPS:.h=.cpp) main.cpp

# Object files = Sources files with .o instead of .cpp
_OBJ = $(SOURCES:.cpp=.o)

# $(patsubst pattern,replacement,text)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Name of the executable file
EXECUTABLE = raytracer

#######################################################################

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

$(EXECUTABLE): $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

# .PHONY keeps make from doing something with a file named clean
.PHONY: clean 

clean: 
	rm -f $(EXECUTABLE)
	rm -f $(ODIR)/*.o
