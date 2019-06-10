#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*****
*   int n_lineas
*****
*   funcion que obtiene la cantidad de lineas del archivo
*****
*   Input:
*     char *arch: puntero de tipo caracter, que almacena el nombre del archivo
*****
*   Returns:
*     int nlineas, numero de lineas que tiene el archivo en valor Entero
*****/
int n_lineas(char *arch){//Obtiene la cantidad de lineas del archivo entregado
  int nlineas = 1; // Inicia el contador en 1
  int c;//almacenara los caracteres a leer
  FILE *fp=fopen(arch,"r"); //Se abre el archivo
  if (fp==NULL){
    printf("No se puede abrir el archivo\n"); //Si existe algun error lo notifica
  }
  while(!feof(fp)){// Mueve la posicion de lectura en archivo caracter por caracter
    c = fgetc(fp); //Guarda el caracter leido
    if (c == '\n')nlineas++; //Si este es igual a \n, entonces significa que hay una linea
  }
  fclose(fp);
  return nlineas; //Retorna las lineas
}
/*****
*   int **busquedas
*****
*   funcion hecha para almacenar todas las busquedas mediante un arreglo de arreglos. La posicion n del arreglo contiene a la palabra n, y dentro de ese arreglo se encuentran las paginas donde aparece
*   la palabra. La posicion 0 de cada arreglo dentro del arreglo mayor, contiene el su respectivo tamanio.
*****
*   Input:
*     vacio
*****
*   Returns:
*     int **busq, arreglo con arreglos que contienen cantidad de paginas por palabra buscada, y todas las paginas en las cuales se encuentra la palabra buscada
*****/
int **busquedas(){
  FILE *fp=fopen("palabras.dat","r"); //Abre el archivo
  if (fp==NULL){
    printf("No se puede abrir el archivo\n");//notifica si existio algun error
  }
  int nlineas = n_lineas("palabras.dat"); //Se definen la cantidad de lineas
  int nNumeros, flag = 0, c; //Se definen las variables que se utilizan mas adelante. nNumeros almacenara la cantidad de numeros en una linea
  int contador = 0, t;
  int **busq = (int **)malloc(sizeof(int*)*nlineas);
  while(!feof(fp)){// Contador de lineas
    if(flag == 0){
      fscanf(fp,"%d", &nNumeros);
      flag = 1;
      busq[contador] = (int*)malloc(sizeof(int)*(nNumeros+1));
      busq[contador][0] = nNumeros; // En la posicion 0 del arreglo se coloca el tamanio que tendra este
      for(t = 1; t < nNumeros + 1; t++){
        int n;
        fscanf(fp, "%d", &n);
        busq[contador][t] = n;
      }
      contador++;
    }
    c = fgetc(fp);
    if (c == '\n'){
      fscanf(fp,"%d", &nNumeros);
      busq[contador] = (int*)malloc(sizeof(int)*(nNumeros+1));
      busq[contador][0] = nNumeros;
      for(t = 1; t < nNumeros + 1; t++){
        int n;
        fscanf(fp, "%d", &n);
        busq[contador][t] = n;
      }
      contador++;
    }
  }
  fclose(fp);
  return busq;
}
/*****
*   void ordenar
*****
*   funcion que ordena un arreglo de manera creciente, con el algoritmo "bubble sort"
*****
*   Input:
*     int **b: arreglo de arreglos con enteros
*     int l: largo del entero anterior
*****
*   Returns:
*     entero 0 si corrio correctamente
*****/
int ordenar(int **b, int l){
  int i, j, z, aux;
  for(z = 0; z < l; z++){
    for(i = b[z][0]; i > 0; i--){
      if(b[z][0] != 1){
        for(j = 2; j <= i; j++){
          if(b[z][j-1] > b[z][j]){
            aux = b[z][j-1];
            b[z][j-1] = b[z][j];
            b[z][j] = aux;
          }
        }
      }
    }
  }
  return 0;
}//Se utiliza el algoritmo ordenamiento de burbuja
/*****
*   int maximo
*****
*   funcion que da el maximo entre dos numeros, en este caso son el largo de dos arreglos
*****
*   Input:
*     int a,b: dos enteros dados para comparacion
*****/
int maximo(int a, int b){
  if(a > b) {
    return a;
  }
    return b;
}
/*****
*   int salida
*****
*   funcion que busca la interseccion entre las paginas que tienen las 2 palabras y luego escribe la informacion en el archivo de salida
*****
*   Input:
*     int **b: arreglo con arreglos de palabras
*     int l: largo del arreglo
*****
*   Returns:
*     0 si se corrio correctamente, 1 si existio algun error
*****/
int salida(int **b, int l){
  FILE *fp = fopen("consultas.dat", "r");
  if (fp==NULL){
    printf("No se puede abrir el archivo\n");
    return 1;
  }
  FILE *res = fopen("salida.dat", "w");
  int palabra1, palabra2, i, j;
  int largo = n_lineas("consultas.dat");
  for(i = 0; i < largo-1; i++){
    fscanf(fp,"%d %d",&palabra1, &palabra2);
    int bandera = 1;
    int contador = 0;
    int z = 1, h = 1;
    int m = maximo(b[palabra1][0],b[palabra2][0]);
    int *number = (int*)malloc(sizeof(int)*m);
    while(h < (b[palabra1][0]+1) && z < (b[palabra2][0]+1)){
      if(b[palabra1][h] < b[palabra2][z])h++;
      else if(b[palabra1][h] > b[palabra2][z])z++;
      else{
        number[contador] = b[palabra2][z];
        h++;z++;contador++;
        bandera = 0;
      }
    }
    if(bandera==1) fprintf(res, "%d\n", contador);
    if(bandera==0){
      for(j = 0; j < contador; j++){
        if(j == 0) fprintf(res, "%d ", contador);
        if(j == contador-1) fprintf(res, "%d\n", number[j]);
        if(j != contador-1) fprintf(res, "%d ", number[j]);
      }
    }
    void free(void * number);
  }

  fclose(fp);
  fclose(res);
  return 0;
}

/*****
*   int main
*****
*   funcion principal creada para correr el resto de las funciones anteriores
*****
*   Input:
*     vacio
*****
*   Returns:
*     int 0, para asegurar que el programa compilo de manera correctamente
*****/
int main(){
  int **b = busquedas();
  int l = n_lineas("palabras.dat"), i, seguro;
  ordenar(b , l);
  seguro = salida(b, l);
  if(seguro != 0)printf("No se creo el archivo correctamente\n");

  // ##########LIBERAR MEMORIA###########
  for (i=0; i<l; i++) free ((void *)b[i]);
  free ((void *)b);
  return 0;
  }
