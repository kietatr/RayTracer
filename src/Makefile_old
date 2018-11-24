CC = g++
CFLAGS = -I.
OBJS = main.o Vect.o Ray.o Color.o Light.o Object.o Plane.o Sphere.o Camera.o Source.o

all: raytracer

raytracer: $(OBJS)
	$(CC) $(OBJS) -o raytracer $(CFLAGS)
	rm -f $(OBJS)

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)

Ray.o: Ray.cpp
	$(CC) -c Ray.cpp $(CFLAGS)

Object.o: Object.cpp
	$(CC) -c Object.cpp $(CFLAGS)

Vect.o: Vect.cpp
	$(CC) -c Vect.cpp $(CFLAGS)

Plane.o: Plane.cpp
	$(CC) -c Plane.cpp $(CFLAGS)

Sphere.o: Sphere.cpp
	$(CC) -c Sphere.cpp $(CFLAGS)

Color.o: Color.cpp
	$(CC) -c Color.cpp $(CFLAGS)

Light.o: Light.cpp
	$(CC) -c Light.cpp $(CFLAGS)

Camera.o: Camera.cpp
	$(CC) -c Camera.cpp $(CFLAGS)

Source.o: Source.cpp
	$(CC) -c Source.cpp $(CFLAGS)

clean:
	rm -f raytracer $(OBJS)
