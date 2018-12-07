# Path to source files
SDIR = ./
# Path to object files
ODIR = ./obj
# Path to header files
HDIR = ./headers

INC = -I $(HDIR)

# EDIT _HEAD when adding more files
_HEAD = App.h Color.h Vect.h Source.h Light.h Ray.h Camera.h Object.h Plane.h Sphere.h Triangle.h
_SRC = main.cpp $(_HEAD:.h=.cpp)
_OBJ = $(_SRC:.cpp=.o)

HEAD = $(patsubst %,$(HDIR)/%,$(_HEAD))
SRC = $(patsubst %,$(SDIR)/%,$(_SRC))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

EXECUTABLE = raytracer

###############################################################

# Create .o from .cpp (if .h is changed, recreate .o too)
$(ODIR)/%.o: $(SDIR)/%.cpp $(HEAD)
	g++ -c $< -o $@ $(INC)

# Create executable from .o
$(EXECUTABLE): $(OBJ)
	g++ $^ -o $@ $(INC)

# .PHONY keeps make from doing something with a file named clean
.PHONY: clean 

clean: 
	rm -f $(EXECUTABLE)
	rm -f $(OBJ)
