#include <stdio.h>
/*
void maxPasajeros(int numPasajeros,int no){
    int arr[10], i, j, c, heap_root, temp;
    //"no" va a ser el numero de simulaciones
    //aqui se ingresan los datos del heap
    for (i = 0; i <  no; i++)
        scanf("%d", &arr[i]);
    for (i = 1; i <  no; i++)
    {
        c = i;
        do
        {
            heap_root  = (c - 1) / 2;
            //to create MAX arr  array
            if  (arr[heap_root] < arr[c])
            {
                temp =  arr[heap_root];
                arr[heap_root] = arr[c];
                arr[c]  = temp;
            }
            c =  heap_root;
        } while (c !=  0);
    }

    printf("Heap  array : ");
    for (i = 0; i <  no; i++)
        printf("%d\t ", arr[i]);
    for (j = no - 1; j  >= 0; j--)
    {
        temp = arr[0];
        arr[0] = arr[j];
        arr[j] = temp;
        heap_root = 0;
        do
        {
            c = 2 *  heap_root + 1;
            if  ((arr[c] < arr[c + 1]) && c < j-1)
                c++;
            if  (arr[heap_root]<arr[c] && c<j)
            {
                temp =  arr[heap_root];
                arr[heap_root] = arr[c];
                arr[c]  = temp;
            }
            heap_root  = c;
        } while (c  < j);
    }
    printf("\nSorted  array : ");
    printf("\nMenor: %d",arr[0]);
    printf("\nMayor: %d",arr[-1]);
    printf("\n");
}



int main()
{
    int arr[10], no,  i, j, c, heap_root, temp;
    printf("Input number of elements: ");//este va a ser el numero de simulaciones
    scanf("%d", &no);
    printf("\nInput array values one by one : ");//aqui se ingresan los datos del heap
    for (i = 0; i <  no; i++)
        scanf("%d", &arr[i]);
    for (i = 1; i <  no; i++)
    {
        c = i;
        do
        {
            heap_root  = (c - 1) / 2;
            //to create MAX arr  array
            if  (arr[heap_root] < arr[c])
            {
                temp =  arr[heap_root];
                arr[heap_root] = arr[c];
                arr[c]  = temp;
            }
            c =  heap_root;
        } while (c !=  0);
    }

    printf("Heap  array : ");
    for (i = 0; i <  no; i++)
        printf("%d\t ", arr[i]);
    for (j = no - 1; j  >= 0; j--)
    {
        temp = arr[0];
        arr[0] = arr[j];
        arr[j] = temp;
        heap_root = 0;
        do
        {
            c = 2 *  heap_root + 1;
            if  ((arr[c] < arr[c + 1]) && c < j-1)
                c++;
            if  (arr[heap_root]<arr[c] && c<j)
            {
                temp =  arr[heap_root];
                arr[heap_root] = arr[c];
                arr[c]  = temp;
            }
            heap_root  = c;
        } while (c  < j);
    }
    printf("\nSorted  array : ");
    printf("\nMenor: %d",arr[0]);
    printf("\nMayor: %d",arr[-1]);
    printf("\n");
}

printf("|---------------------------------|\n");
printf("| 1. Mayor cantidad de pasajeros  |\n");
printf("| 2. Menor cantidad de pasajeros  |\n");
printf("| 3. Mayor distancia recorrida    |\n");
printf("| 4. Menor distancia recorrida    |\n");
printf("| 5. Salir                        |\n");
printf("|---------------------------------|\n");
printf("Escoge opcion: ");
scanf("%d", &opcion);

 */