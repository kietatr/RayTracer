CC = g++
CFLAGS = -I.
OBJS = main.o Color.o 

all: raytracer

raytracer: $(OBJS)
	$(CC) $(OBJS) -o raytracer $(CFLAGS)
	rm -f $(OBJS)

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)

Color.o: Color.cpp
	$(CC) -c Color.cpp $(CFLAGS)


clean:
	rm -f raytracer $(OBJS)