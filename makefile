diccionario: Diccionario.o Funciones.o
	gcc  Diccionario.o Funciones.o -o diccionario

Diccionario.o: Diccionario.c Funciones.h
	gcc -c Diccionario.c

Funciones.o: Funciones.c Funciones.h
	gcc -c Funciones.c

clean:
	rm -f diccionario *.o
