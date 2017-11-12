CC=g++
CFLAGS= -DNO_FREETYPE -fopenmp  -L. -I. 
LIBS= -lm -lpngwriter -lpng16 -lz

ray: main.cpp simple_ray.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm ray
