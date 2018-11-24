CC = g++
CFLAGS = -I.
OBJS = main.o Vect.o Color.o Light.o 

all: raytracer

raytracer: $(OBJS)
	$(CC) $(OBJS) -o raytracer $(CFLAGS)
	rm -f $(OBJS)

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)

Vect.o: Vect.cpp
	$(CC) -c Vect.cpp $(CFLAGS)

Color.o: Color.cpp
	$(CC) -c Color.cpp $(CFLAGS)

Light.o: Light.cpp
	$(CC) -c Light.cpp $(CFLAGS)

clean:
	rm -f raytracer $(OBJS)