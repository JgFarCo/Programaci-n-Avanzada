#include <iostream>
using namespace std;

struct Nodo{
    int id;
    Nodo* sig;
    int valor; 

    Nodo(int valor) {
        this->id=valor;
        this->sig= NULL;
    }
};

Nodo* crearCirculito(int n)
{
    if(n<=0) {return NULL;}

    Nodo* raiz = new Nodo(1);
    Nodo* actual = raiz;

    for(int i=2; i<=n; i++)
    {
        actual->sig = new Nodo(i);
        actual = actual->sig; 
    }

    actual->sig = raiz;

    return raiz;
}

void mostrarRestantes(Nodo* raiz, int tamano)
{
    if(tamano==0) {return;}

    Nodo* aux = raiz;

    cout<<"Circulo en este momento: "<<endl;
    for(int i = 0; i<tamano; i++)
    {
        cout<<aux->id<<endl;
        aux=aux->sig;
    }
}

Nodo* obtenerVictima(Nodo* base, int tamano)
{
    int pasos = tamano/2;
    Nodo* aux = base;
    for(int i = 0; i<pasos; i++)
    {
        aux = aux->sig;
    }

    return aux;
}

void eliminar(Nodo*& raiz, Nodo* eliminado, int tamano)
{
    if(tamano==0)
    {
        return;
    }

    if(tamano==1) 
    {
        delete raiz;
        raiz = NULL;
        return;
    }

    Nodo* anterior = raiz;
    
    while(anterior->sig != eliminado)
    {
        anterior = anterior->sig;
    }

    anterior->sig=eliminado->sig;

    if(eliminado==raiz)
    {
        raiz = eliminado->sig;
    }

    delete eliminado;
}

void Josephus(int n , int k)
{
    Nodo* raiz = crearCirculito(n);
    Nodo* actual = raiz; 
    int tamano = n; 
    
    cout<<"Que empiece el juego"<<endl; 
    mostrarRestantes(actual, tamano);

    while (tamano > 1)
    {
        for(int i = 0; i < k-1; i++) //k - 1 porque se empieza a contar desde el nodo raiz
        {
            actual = actual->sig; 
        }
    

    cout<<"La persona que va a ejecutar el asesinato es: "<<actual->id<<endl;

    Nodo* victima = obtenerVictima(actual, tamano);
    cout<<actual->id<<" mata a "<<victima->id<<endl; 

    if(victima==actual)
    {
        actual=actual->sig;
    }

    eliminar(actual, victima, tamano);
    tamano=tamano-1;

    mostrarRestantes(actual, tamano);
    }   

    cout<<"El sobreviviente del juego de Josephus fue "<<actual->id<<endl;

    delete actual;
}

int main(){
    int n, k;

    cout<<"Ingrese el numero de personas que van a participar del circulo: ";
    cin>>n;

    cout<<"Que numero determinara el rey Josephus?: ";
    cin>>k;

    if(n>0 && k>0)
    {
        Josephus(n,k);
    }
    else{
        cout<<"Ingrese valores para n y k que sean superiores a 0"<<endl;
    }

    return 0;
}