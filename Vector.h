#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
//typedef enum { false, true } bool;

#define TAM_INI 10

#define TODO_OK 0
#define SIN_MEM 1

#define ERR_NO_EXISTE 1

typedef struct{
    void* ini;
    int ce;
    int cap;
    size_t tamElem;
}Vector;

typedef void (*Accion) (const void* e);
typedef int (*Cmp) (const void* e1, const void* e2);




//Aloja en memoria el vector, con TAM_INI de capacidad maxima de tamaño tamElem
bool vectorCrear(Vector* vec, size_t tamElem);
//Realiza el free del vector y pone en NULL el puntero a void de inicio
void vectorDestruir(Vector* vec);
bool vectorRedimensionar(Vector* v, float porc);

void vectorRecorrer(const Vector* v, const Accion accion);
void vectorVaciar(Vector* v);

void* vectorObtenerDato(const Vector* v, const int indice);

int vectorInsertarAlFinal(Vector* v, const void* dato);
int vectorOrdInsertar(Vector* v, const void* dato, Cmp comp);
int vectorInsertarEnPos(Vector* v, const void* dato, int pos);

int vectorEliminarPosicion(Vector* v, int indice);
int vectorEliminarElemento(Vector* v, const void* dato, Cmp comp); //Elimina duplicados
int vectorOrdEliminarElemento(Vector* v, const void* dato, Cmp comp);

void vectorOrdenar( Vector* v,  Cmp comp);
int vectorBuscar(const Vector* v, const void* dato, const Cmp comp);
int vectorBuscarBinario(Vector* v, const void* dato, Cmp comp);

int vectorCantidadElementos(const Vector* v);

//void vectorEnteroInicializarRandom(Vector* v, int ce);




#endif // VECTOR_H_INCLUDED
