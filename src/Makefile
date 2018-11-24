OBJ = main.o
CLS = main.cpp
INC = -I "./"

raytracer: $(OBJ)
	g++ $(OBJ) -o raytracer
	rm -f $(OBJ)

main.o:
	g++ -c $(CLS) $(INC)

clean:
	rm -f $(OBJ) raytracer
