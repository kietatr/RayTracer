CC = g++
CFLAGS = -c -Wall
LDFLAGS =

SOURCES = main.cpp Vect.cpp Ray.cpp Color.cpp Light.cpp Object.cpp Plane.cpp Sphere.cpp Camera.cpp Source.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = raytracer

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
