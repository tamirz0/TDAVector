#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"

void mostrarEntero(const void* e);
int cmpEntero(const void* e1, const void* e2);
int* ingresoYValidacion(int min, int max);

int main()
{
    Vector Enteros;

    vectorCrear(&Enteros, sizeof(int));

    for(int i = 15 ; i >= 1 ; i--)
        vectorInsertarAlFinal(&Enteros, &i);

    vectorRecorrer(&Enteros, mostrarEntero);

//    int a = -1;
//    vectorInsertarEnPos(&Enteros, &a, 0);

    int* dato = vectorObtenerDato(&Enteros, 0);
    if(dato != NULL)
        printf("\nPrimer Dato = %d\n", *dato);
//    printf("\nPrimer Dato = %d", *((int*)vectorObtenerDato(&Enteros, 0)));
//    vectorRecorrer(&Enteros, mostrarEntero);


//    int aux = 10;
//    vectorInsertarAlFinal(&Enteros, &aux);
//    vectorInsertarAlFinal(&Enteros, &aux);
//    vectorInsertarAlFinal(&Enteros, &aux);
//    aux = 15;
//    vectorInsertarAlFinal(&Enteros, &aux);
//    aux = 10;
//    vectorInsertarAlFinal(&Enteros, &aux);
//
//    vectorRecorrer(&Enteros, mostrarEntero);
//
//    vectorEliminarElemento(&Enteros, &aux, cmpEntero);
//    aux = 15;
//    vectorEliminarElemento(&Enteros, &aux, cmpEntero);
//    vectorEliminarPosicion(&Enteros, 0);
//    int aux = 10;
//    vectorOrdEliminarElemento(&Enteros, &aux, cmpEntero);
    int aux = 15;
    printf("\nPosicion de %d: %d\n", aux, vectorBuscar(&Enteros, &aux, cmpEntero));

    vectorOrdenar(&Enteros, cmpEntero);
    vectorRecorrer(&Enteros, mostrarEntero);
    dato = vectorObtenerDato(&Enteros, 0);
    if(dato != NULL)
        printf("\nPrimer Dato = %d\n", *dato);
    printf("\nPosicion de %d: %d\n", aux, vectorBuscar(&Enteros, &aux, cmpEntero));
    vectorDestruir(&Enteros);
    return 0;
}

void mostrarEntero(const void* e)
{
    const int* i = e;
    printf("\n%d", *i);
}

int cmpEntero(const void* e1, const void* e2)
{
    const int* i1 = e1;
    const int* i2 = e2;

    return *i1 - *i2;
}

int* ingresoYValidacion(int min, int max)
{
    int* var = malloc(sizeof(int));
    if(!var)
        return NULL;

    do{
        printf("\nIngrese un valor entre %d y %d: ", min, max);
        scanf_s("%d", var);
    }while(*var < min || *var > max);

    return var;
}
