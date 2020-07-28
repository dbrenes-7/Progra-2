#include <stdio.h>
#include <stdlib.h>
#define Nodo struct nodo
#define Arista struct arista
#define Lista struct pila

Nodo{
    char dato;
    Nodo* siguiente;
    Arista* adyacencia;
    int visitado,terminado;
    int monto;
    char anterior;
};

Arista{
    Nodo*vrt;
    Arista*siguiente;
    int peso;
    int tiempo;
};

Lista{
    Nodo* dato;
    Lista*siguiente;
};

Nodo*inicio=NULL;
Lista*ini=NULL;
Lista*final=NULL;

void insertarNodo();
void agregarArista(Nodo*aux,Nodo*aux2,Arista*nuevo);
void insertarArista();
void visualizarGrafo();
void recorridos();
void recorridoAnchura();
void recorridoProfundidad(Nodo* aux);
void insertarPila(Nodo* aux);
void insertarCola(Nodo* aux);
Nodo*desencolar();
void reiniciar();
void simulacion_Vehiculo_Taxi();
int configuracion_Inicial();

int main(){
    int opcion;
    do{
        printf("-------------------------------------\n");
        printf(" 1. Insertar Vertice                 \n");
        printf(" 2. Insertar Arista                  \n");
        printf(" 3. Mostrar Listas                   \n");
        printf(" 4. Recorrer Grafo                   \n");
        printf(" 5. Simulaciones                     \n");
        printf(" 6. Salir                            \n");
        printf("-------------------------------------\n");
        printf("Escoge opcion: ");
        scanf("%d",&opcion);

        if(opcion==1){insertarNodo();}
        else if (opcion==2){insertarArista();}
        else if (opcion==3){visualizarGrafo();}
        else if(opcion==4){recorridos();}
        else if (opcion==5){configuracion_Inicial();}
        else if (opcion==6){ return 1;}
    }while(opcion<=6);



    return 1;
}

void insertarNodo(){
    Nodo* aux;
    Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
    fflush(stdin);
    printf("\nIngrese vertice:");
    scanf("%c",&nuevo->dato);
    nuevo->siguiente=NULL;
    nuevo->adyacencia=NULL;
    nuevo->visitado=nuevo->terminado=0;
    nuevo->monto=-1;
    nuevo->anterior=0;
    if(inicio==NULL){
        inicio=nuevo;
    }else{
        aux=inicio;
        while(aux->siguiente!=NULL){
            aux=aux->siguiente;
        }
        aux->siguiente=nuevo;
    }

}

void insertarArista(){
    char ini, fin;
    Arista* nuevo=(Arista*)malloc(sizeof(Arista));
    nuevo->siguiente=NULL;
    Nodo* aux;
    Nodo* aux2;
    if(inicio==NULL){
        printf("\n--------------------------\n");
        printf("\nError: El grafo esta vacio\n");
        printf("\n--------------------------\n");
        return;
    }
    fflush(stdin);
    printf("\nIngresar Nodo Inicial y Final:");
    scanf("%c %c",&ini,&fin);
    printf("\nIngresar Peso de la arista:");
    scanf("%i",&nuevo->peso);
    printf("\nIngresar el Tiempo de la arista:");
    scanf("%i",&nuevo->tiempo);
    aux=inicio;
    aux2=inicio;
    while(aux2!=NULL){
        if(aux2->dato==fin){
            break;
        }
        aux2=aux2->siguiente;
    }
    if(aux2==NULL){
        printf("\n---------------------\n");
        printf("\nVertice no encontrado\n");
        printf("\n---------------------\n");
        return;
    }
    while(aux!=NULL){
        if(aux->dato==ini){
            agregarArista(aux,aux2,nuevo);
            return;
        }
        aux = aux->siguiente;
    }
    if(aux==NULL)
        printf("\n---------------------\n");
        printf("\nVertice no encontrado\n");
        printf("\n---------------------\n");
}

void agregarArista(Nodo* aux,Nodo* aux2,Arista* nuevo){
    Arista* a;
    if(aux->adyacencia==NULL){
        aux->adyacencia=nuevo;
        nuevo->vrt=aux2;
    }else{
        a=aux->adyacencia;
        while(a->siguiente!=NULL)
            a=a->siguiente;
        nuevo->vrt=aux2;
        a->siguiente=nuevo;
    }
}

void visualizarGrafo(){
    Nodo*aux=inicio;
    Arista* ar;
    printf("Nodos\n");
    while(aux!=NULL){
        printf("%c:    ",aux->dato);
        if(aux->adyacencia!=NULL){
            ar=aux->adyacencia;
            while(ar!=NULL){
                printf(" %c",ar->vrt->dato);
                ar=ar->siguiente;
            }
        }
        printf("\n");
        aux=aux->siguiente;
    }
    printf("\n");
}

void recorridos(){
    char vertice;
    Nodo*aux=inicio,*aux2=inicio;
    if(inicio!=NULL){
        fflush(stdin);
        printf("\nEscoger vertice inicial:");
        scanf("%c",&vertice);
        while(aux!=NULL){
            if(aux->dato==vertice)
                break;
            aux=aux->siguiente;
        }
        if(aux==NULL){
            printf("\n---------------------\n");
            printf("\nVertice no encontrado\n");
            printf("\n---------------------\n");
        }else{
            printf("Recorrido por anchura: ");
            aux->visitado=1;
            insertarCola(aux);
            recorridoAnchura();
            reiniciar();
            printf("\nRecorrido por profundidad: ");
            recorridoProfundidad(aux);
            while(aux2!=NULL){
                if(aux2->terminado==0)
                    recorridoProfundidad(aux2);
                aux2=aux2->siguiente;
            }
            while(ini!=NULL)
                printf("%c ",desencolar()->dato);
            reiniciar();
            printf("\n");
        }
    }
}
// 0407 Contrase�a de MemoLey
// 1-0 Contrase�a de internet
void recorridoAnchura(){
    Nodo*aux=desencolar();
    if(aux==NULL)
        return;
    printf("%c ",aux->dato);
    if(aux->adyacencia!=NULL){
        Arista*a=aux->adyacencia;
        while(a!=NULL){
            if(a->vrt->visitado==0){
                insertarCola(a->vrt);
                a->vrt->visitado=1;
            }
            a=a->siguiente;
        }
    }
    recorridoAnchura();

}

void recorridoProfundidad(Nodo* aux){
    Arista*a;
    aux->visitado=1;
    if(aux->adyacencia!=NULL){
        a=aux->adyacencia;
        while(a!=NULL){
            if(a->vrt->visitado==0){
                recorridoProfundidad(a->vrt);
            }
            a=a->siguiente;
        }
    }
    aux->terminado=1;
    insertarPila(aux);
}

int buscarNodo(Nodo* aux,char buscado){
    Arista*a;
    aux->visitado=1;
    if(aux->adyacencia!=NULL){
        a=aux->adyacencia;
        while(a!=NULL){
            if(a->vrt->visitado==0){
                recorridoProfundidad(a->vrt);
            }
            a=a->siguiente;
        }
    }
    aux->terminado=1;
    insertarPila(aux);
    if(aux->dato==buscado){
        return 0;
    }
}

void insertarPila(Nodo* aux){
    Lista*nuevo=(Lista*)malloc(sizeof(Lista));
    nuevo->dato=aux;
    nuevo->siguiente=NULL;
    if(ini==NULL){
        ini=nuevo;
        final=nuevo;
    }else{
        nuevo->siguiente=ini;
        ini=nuevo;
    }
}

void insertarCola(Nodo*aux){
    Lista*nuevo=(Lista*)malloc(sizeof(Lista));
    nuevo->dato=aux;
    nuevo->siguiente=NULL;
    if(ini==NULL){
        ini=nuevo;
        final=nuevo;
    }else{
        final->siguiente=nuevo;
        final=nuevo;
    }
}

Nodo*desencolar(){
    Lista*aux;
    if(ini==NULL){
        return NULL;
    }else{
        aux=ini;
        ini=ini->siguiente;
        aux->siguiente=NULL;
        if(ini==NULL)
            final=NULL;
    }
    Nodo*resultado=aux->dato;
    free(aux);
    return resultado;
}

void reiniciar(){
    if(inicio!=NULL){
        Nodo*aux=inicio;
        while(aux!=NULL){
            aux->visitado=aux->terminado=0;
            aux=aux->siguiente;
        }
    }
}
//Lorem Ipsum
void simulacion_Vehiculo_Taxi(int maxPasajeros){
    Nodo*aux=inicio;
    char a,b;
    int tiempo=0,distancia=0;
    int random_Pasajeros=rand()%maxPasajeros;
    fflush(stdin);
    printf("\nIngresar punto de incio y destino:");
    scanf("%c %c",&a,&b);
    while(aux!=NULL){
        if(aux->dato==a){
            aux->terminado=1;
            aux->monto=0;
            break;
        }
        aux=aux->siguiente;
    }
    if(aux==NULL){
        printf("\n---------------------\n");
        printf("\nVertice no encontrado\n");
        printf("\n---------------------\n");
        return;
    }
    while(aux!=NULL){
        Arista*a=aux->adyacencia;
        while(a!=NULL){
            if(a->vrt->monto==-1 || (aux->monto+a->peso)<a->vrt->monto){
                a->vrt->monto=aux->monto+a->peso;
                a->vrt->anterior=aux->dato;
                distancia = distancia + a->peso;
                tiempo = tiempo + a->tiempo;
            }
            a=a->siguiente;
        }
        aux=inicio;
        Nodo*min=inicio;
        while(min->anterior==0 || min->terminado ==1)
            min=min->siguiente;
        while(aux!=NULL){
            if(aux->monto<min->monto && aux->terminado==0 && aux->anterior!=0)
                min=aux;
            aux=aux->siguiente;
        }
        aux=min;
        aux->terminado=1;
        if(aux->dato==b)
            break;
    }
    while(aux->anterior!=0){
        insertarPila(aux);
        char temp=aux->anterior;
        aux=inicio;
        while(aux->dato!=temp){
            aux=aux->siguiente;
        }
    }
    insertarPila(aux);
    printf("\nRecorrido\n");
    while(ini!=NULL){
        printf("%c ",desencolar()->dato);
    }
    printf("\n");
    printf("Distancia del viaje: %d\n",distancia);
    printf("Tiempo de viaje: %d\n",tiempo);
    printf("Numero de pasajeros: %d\n",random_Pasajeros);
    reiniciar();
}

void simulacion_Bus_Tren(int maxPasajeros){
    Nodo*aux=inicio;
    char a,b;
    int tiempo=0,distancia=0,random;
    int pasajeros_entrada=rand()%maxPasajeros,pasajeros_salida=0;
    fflush(stdin);
    printf("\nIngresar punto de incio y destino:");
    scanf("%c %c",&a,&b);
    while(aux!=NULL){
        if(aux->dato==a){
            aux->terminado=1;
            aux->monto=0;
            break;
        }
        aux=aux->siguiente;
    }
    if(aux==NULL){
        printf("\n---------------------\n");
        printf("\nVertice no encontrado\n");
        printf("\n---------------------\n");
        return;
    }
    while(aux!=NULL){
        Arista*a=aux->adyacencia;
        while(a!=NULL){
            if(a->vrt->monto==-1 || (aux->monto+a->peso)<a->vrt->monto){
                a->vrt->monto=aux->monto+a->peso;
                a->vrt->anterior=aux->dato;
                distancia = distancia + a->peso;
                tiempo = tiempo + a->tiempo;
                printf("\nIniciaron %d pasajeros",pasajeros_entrada);
                pasajeros_salida=rand()%(maxPasajeros-pasajeros_entrada);
                printf("\nSe bajaron %d pasajeros",pasajeros_salida);
                pasajeros_entrada = (pasajeros_entrada - pasajeros_salida);
                random = rand()%(maxPasajeros-pasajeros_entrada);
                printf("\nSe subieron %d pasajeros\n", random);
                pasajeros_entrada = pasajeros_entrada + random;

            }
            a=a->siguiente;
        }
        aux=inicio;
        Nodo*min=inicio;
        while(min->anterior==0 || min->terminado ==1)
            min=min->siguiente;
        while(aux!=NULL){
            if(aux->monto<min->monto && aux->terminado==0 && aux->anterior!=0)
                min=aux;
            aux=aux->siguiente;
        }
        aux=min;
        aux->terminado=1;
        if(aux->dato==b)
            break;
    }
    while(aux->anterior!=0){
        insertarPila(aux);
        char temp=aux->anterior;
        aux=inicio;
        while(aux->dato!=temp){
            aux=aux->siguiente;
        }
    }
    insertarPila(aux);
    printf("\nRecorrido\n");
    while(ini!=NULL){
        printf("%c ",desencolar()->dato);
    }
    printf("\n");
    printf("Distancia del viaje: %d\n",distancia);
    printf("Tiempo de viaje: %d\n",tiempo);
    printf("LLegaron %d pasajeros al destino\n",pasajeros_entrada);
    reiniciar();
}

int configuracion_Inicial(){
    int opcion, maxPasajeros, numSimulaciones;
    printf("\n[1]Tren\n[2]Bus\n[3]Taxi\n[4]Vehiculo personal\nElija el metodo de transporte: ");
    scanf("%d",&opcion);
    printf("\nIndique la cantidad maxima de pasajeros del medio de transporte: ");
    scanf("%d",&maxPasajeros);
    printf("\nIngrese la cantidad de simulaciones que vaya a realizar: ");
    scanf("%d",&numSimulaciones);

    for (int i = 0; i < numSimulaciones; ++i) {
        if(opcion==1){simulacion_Bus_Tren(maxPasajeros);}
        else if (opcion==2){simulacion_Bus_Tren(maxPasajeros);}
        else if (opcion==3){simulacion_Vehiculo_Taxi(maxPasajeros);}
        else if (opcion==4){simulacion_Vehiculo_Taxi(maxPasajeros);}
    }
    return 0;
}