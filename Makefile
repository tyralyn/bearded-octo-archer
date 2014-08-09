all: main.cpp raytracer

SOURCES    = main.cpp MATRIX4.cpp
OBJECTS    = $(SOURCES:.cpp=.o)

.cpp.o:
	g++ -c -Wall -I./ $< -o $@

raytracer : $(OBJECTS)
	g++ $(OBJECTS) -lGL -lGLU -lglut $(LDFLAGS) -o $@

clean:
	rm -f *.o
