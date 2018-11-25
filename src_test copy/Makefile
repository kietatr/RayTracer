OBJ = main.o Color.o Vect.o Source.o Light.o Ray.o Camera.o Object.o
INC = -I "./"

raytracer: $(OBJ)
	g++ $(OBJ) -o raytracer
	rm -f $(OBJ)

main.o:
	g++ -c main.cpp $(INC)

Color.o:
	g++ -c Color.cpp $(INC)

Vect.o:
	g++ -c Vect.cpp $(INC)

Source.o:
	g++ -c Source.cpp $(INC)

Light.o:
	g++ -c Light.cpp $(INC)

Ray.o:
	g++ -c Ray.cpp $(INC)

Camera.o:
	g++ -c Camera.cpp $(INC)

Object.o:
	g++ -c Object.cpp $(INC)

clean:
	rm -f $(OBJ) raytracer