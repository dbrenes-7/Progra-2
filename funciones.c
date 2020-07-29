#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Nodo struct nodo
#define Arista struct arista
#define Lista struct pila
#define TAMANO 100

Nodo{
    char dato[TAMANO];
    Nodo* siguiente;
    Arista* adyacencia;
    int visitado,terminado;
    int monto;
    char anterior[TAMANO];
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
void insertarPila(Nodo* aux);
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
        else if(opcion==4){ return 1;}
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
    scanf("%s",&nuevo->dato);
    nuevo->siguiente=NULL;
    nuevo->adyacencia=NULL;
    nuevo->visitado=nuevo->terminado=0;
    nuevo->monto=-1;
    strcpy(nuevo->anterior,"0");
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
    char ini[TAMANO], fin[TAMANO];
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
    scanf("%s %s",&ini,&fin);
    printf("\nIngresar Peso de la arista:");
    scanf("%i",&nuevo->peso);
    printf("\nIngresar el Tiempo de la arista:");
    scanf("%i",&nuevo->tiempo);
    aux=inicio;
    aux2=inicio;
    while(aux2!=NULL){
        if(strcmp(aux2->dato,fin)==0){
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
        if(strcmp(aux->dato,ini)==0){
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
        printf("%s:    ",aux->dato);
        if(aux->adyacencia!=NULL){
            ar=aux->adyacencia;
            while(ar!=NULL){
                printf(" %s",ar->vrt->dato);
                ar=ar->siguiente;
            }
        }
        printf("\n");
        aux=aux->siguiente;
    }
    printf("\n");
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
    char a[TAMANO],b[TAMANO];
    int tiempo=0,distancia=0;
    int random_Pasajeros=rand()%maxPasajeros;
    fflush(stdin);
    printf("\nIngresar punto de incio y destino:");
    scanf("%s %s",&a,&b);
    while(aux!=NULL){
        if(strcmp(aux->dato,a)==0){
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
                strcpy(a->vrt->anterior,aux->dato);
                //a->vrt->anterior=aux->dato;
                distancia = distancia + a->peso;
                tiempo = tiempo + a->tiempo;
            }
            a=a->siguiente;
        }
        aux=inicio;
        Nodo*min=inicio;
        while(strncmp(min->anterior,"0",1)==0 || min->terminado ==1)
            min=min->siguiente;
        while(aux!=NULL){
            if(aux->monto<min->monto && aux->terminado==0 && strncmp(aux->anterior,"0",1)!=0)
                min=aux;
            aux=aux->siguiente;
        }
        aux=min;
        aux->terminado=1;
        if(strcmp(aux->dato,b)==0)
            break;
    }
    while(strncmp(aux->anterior,"0",1)!=0){
        insertarPila(aux);
        char temp[TAMANO];
        strcpy(temp,aux->anterior);
        aux=inicio;
        while(strcmp(aux->dato,temp)!=0){
            aux=aux->siguiente;
        }
    }
    insertarPila(aux);
    printf("\nRecorrido\n");
    while(ini!=NULL){
        printf("%s ",desencolar()->dato);
    }
    printf("\n");
    printf("Distancia del viaje: %d\n",distancia);
    printf("Tiempo de viaje: %d\n",tiempo);
    printf("Numero de pasajeros: %d\n",random_Pasajeros);
    reiniciar();
}

void simulacion_Bus_Tren(int maxPasajeros){
    Nodo*aux=inicio;
    char a[TAMANO],b[TAMANO];
    int tiempo=0,distancia=0,random;
    int pasajeros_entrada=rand()%maxPasajeros,pasajeros_salida=0;
    fflush(stdin);
    printf("\nIngresar punto de incio y destino:");
    scanf("%s %s",&a,&b);
    while(aux!=NULL){
        if(strcmp(aux->dato,a)==0){
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
                printf("Primer anterior: %s",a->vrt->anterior);
                strcpy(a->vrt->anterior,aux->dato);
                printf("Segundo anterior: %s",a->vrt->anterior);
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
        while(strncmp(min->anterior,"0",1)==0 || min->terminado ==1)
            min=min->siguiente;
        while(aux!=NULL){
            if(aux->monto<min->monto && aux->terminado==0 && strncmp(aux->anterior,"0",1)!=0)
                min=aux;
            aux=aux->siguiente;
        }
        aux=min;
        aux->terminado=1;
        if(strcmp(aux->dato,b)==0)
            break;
    }
    while(strncmp(aux->anterior,"0",1)!=0){
        insertarPila(aux);
        char temp[TAMANO];
        strcpy(temp,aux->anterior);
        aux=inicio;
        while(strcmp(aux->dato,temp)!=0){
            aux=aux->siguiente;
        }
    }
    insertarPila(aux);
    printf("\nRecorrido\n");
    while(ini!=NULL){
        printf("%s ",desencolar()->dato);
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