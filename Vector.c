#include "Vector.h"

void intercambiar(void* e1, void* e2, size_t tamDato);
void* buscarMenor(void* ini,  void* fin, size_t tamDato, Cmp comp);

void intercambiar(void* e1, void* e2, size_t tamDato)
{
    void* aux = malloc(tamDato);

    memcpy(aux, e1, tamDato);
    memcpy(e1, e2, tamDato);
    memcpy(e2, aux, tamDato);

    free(aux);
}

void* buscarMenor(void* ini, void* fin, size_t tamDato, Cmp comp)
{
    void* m = ini;
    for(void* i = ini + tamDato; i <= fin ; i += tamDato)
    {
        if(comp(i, m) < 0)
            m = i;
    }
    return m;
}

bool vectorCrear(Vector* vec, size_t tamElem)
{
    void* pointer = malloc(tamElem * TAM_INI);
    if(pointer == NULL)
        return false;
    vec->ini = pointer;


    vec->ce = 0;
    vec->cap = TAM_INI;
    vec->tamElem = tamElem;

    return true;
}

void vectorDestruir(Vector* vec)
{
    free(vec->ini);
    vec->ini = NULL;
}

bool vectorRedimensionar(Vector* v, float porc)
{
    int nuevoTam = porc * v->cap;
    if(nuevoTam < TAM_INI)
        nuevoTam = TAM_INI;
    void* nuevoIni = realloc(v->ini, nuevoTam * v->tamElem);
    if(nuevoIni == NULL)
        return false;

    v->ini = nuevoIni;
    v->cap = nuevoTam;

    return true;
}


void vectorRecorrer(const Vector* v, const Accion accion)
{
    void* ult = v->ini + v->ce * v->tamElem;
    for(void* i = v->ini ; i < ult ; i += v->tamElem)
        accion(i);
}

void* vectorObtenerDato(const Vector* v, const int indice)
{
    if(indice >= v->ce)
        return NULL;

    void* posDato = v->ini + indice * v->tamElem;

    return posDato;
}


void vectorVaciar(Vector* v)
{
    free(v->ini);
    v->ini = malloc(TAM_INI * v->tamElem);
    if(v->ini == NULL)
        return;
    v->ce = 0;
    v->cap = TAM_INI;
}



int vectorInsertarAlFinal(Vector* v, const void* dato)
{
    if(v->ce == v->cap)
    {
        if(vectorRedimensionar(v, 1.5) == false)
            return SIN_MEM;
    }

    void* posIns = v->ini + v->ce * v->tamElem;

    memcpy(posIns, dato, v->tamElem);

    v->ce++;

    return TODO_OK;
}



int vectorOrdInsertar(Vector* v, const void* dato, Cmp comp)
{
    if(v->ce == v->cap)
    {
        if(vectorRedimensionar(v, 1.5) == false)
            return SIN_MEM;
    }

    void* posIns = v->ini;
    void* ult = v->ini + v->ce * v->tamElem;

    while (comp(posIns, dato) < 0 && posIns < ult)
        posIns+=v->tamElem;

    for(void* i = ult; i > posIns; i-=v->tamElem)
        memcpy(i, i-v->tamElem, v->tamElem);

    memcpy(posIns, dato, v->tamElem);
    v->ce++;
    return TODO_OK;
}

int vectorInsertarEnPos(Vector* v, const void* dato, int pos)
{
    if(v->ce == v->cap)
    {
        if(vectorRedimensionar(v, 1.5) == false)
            return SIN_MEM;
    }

    void* posIns;
    if(pos >= v->ce)
        posIns = v->ini + v->ce*v->tamElem;
    else
        posIns = v->ini + pos * v->tamElem;

    memcpy(posIns, dato, v->tamElem);
    v->ce++;

    return TODO_OK;
}

int vectorEliminarPosicion(Vector* v, int indice)
{
    void* posElim;
    void* ult = v->ini + v->ce * v->tamElem;
    if(indice < 0 || indice >= v->ce)
        posElim = ult;
    else
        posElim = v->ini + indice * v->tamElem;

    for(void* i = posElim; i < ult - v->tamElem; i += v->tamElem)
        memcpy(i, i+v->tamElem, v->tamElem);

    v->ce--;
    if(v->ce <= v->cap / 5)
    {
        if(vectorRedimensionar(v, 0.5) == false)
            return SIN_MEM;
    }

    return TODO_OK;
}

int vectorOrdEliminarElemento(Vector* v, const void* dato, Cmp comp)
{
    void* posElim = v->ini;
    void* ult = v->ini + v->ce * v->tamElem;

    while (comp(posElim, dato) < 0 && posElim < ult)
        posElim+=v->tamElem;

    if(posElim == ult)
        return ERR_NO_EXISTE;
    if(comp(posElim, dato) != 0)
        return ERR_NO_EXISTE;

    for(void* i = posElim; i < ult - v->tamElem; i += v->tamElem)
        memcpy(i, i+v->tamElem, v->tamElem);

    v->ce--;
    if(v->ce <= v->cap / 5)
    {
        if(vectorRedimensionar(v, 0.5) == false)
            return SIN_MEM;
    }
    return TODO_OK;
}

int vectorEliminarElemento(Vector* v, const void* dato, Cmp comp)
{
    void* ult = v->ini + v->ce * v->tamElem;
    void* i = v->ini;

    while(i < ult)
    {
        if(comp(i, dato) == 0)
        {
            for(void* j = i; j < ult - v->tamElem; j += v->tamElem)
                memcpy(j, j+v->tamElem, v->tamElem);
            v->ce--;
            ult -= v->tamElem;
        }
        else
            i+=v->tamElem;
    }

    if(v->ce <= v->cap / 5)
    {
        if(vectorRedimensionar(v, 0.5) == false)
            return SIN_MEM;
    }
    return TODO_OK;
}

void vectorOrdenar( Vector* v,  Cmp comp)
{
    void* ult = v->ini + v->ce * v->tamElem;
    for(void* i = v->ini ; i < ult ; i+=v->tamElem)
    {
        void* m = buscarMenor(i, ult - v->tamElem, v->tamElem, comp);
        intercambiar(i, m, v->tamElem);
    }
}

int vectorBuscar(const Vector* v, const void* dato, const Cmp comp)
{
    int pos;
    void* i = v->ini;
    void* ult = v->ini + v->ce * v->tamElem;

    while(comp(i, dato) != 0 && i < ult)
        i+=v->tamElem;

    if(i == ult)
        pos = -1;
    else
       pos = (i-v->ini) / v->tamElem;

    return pos;
}
int vectorBuscarBinario(Vector* v, const void* dato, Cmp comp)
{
    return 0;
}

int vectorCantidadElementos(const Vector* v)
{
    return v->ce;
}

//void vectorEnteroInicializarRandom(Vector* v, int ce)
//{
//    v->ce = ce;
//    v->cap = ce;
//    v->ini = realloc(v->ini, ce * sizeof(int));
//
//    srand(time(NULL));
//
//   for(int i = 0; i < ce; i++)
//        v->ini[i] = rand() % 100;
//}
