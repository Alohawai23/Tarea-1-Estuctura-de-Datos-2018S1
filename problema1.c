#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {/*curso, dado por pauta*/
  char sigla[7];
  int semestre;
} curso;

typedef struct{/*nota, dado por pauta*/
  char rolEstudiante[12];
  char siglaCurso[7];
  int nota;
} nota;

typedef struct{//Hecho para organizar los alumnos mediante su nombre y rol
  char nombre[25];
  char apellido[25];
  char rol[12];
} alumno;

typedef struct{//Hecho para almacenar los cursos del semestre 1 aprobados de los alumnos
  int nota;
  char siglaCurso[7];
  int cursos_aprobados;
} aprobadoS1;

typedef struct{//Hecho para almacenar los cursos del semestre 2 aprobados de los alumnos
  int nota;
  char siglaCurso[7];
  int cursos_aprobados;
} aprobadoS2;

/*****
*   int largo_notas
*****
*   Funcion que entrega la cantidad de notas
*****
*   Input:
*     vacio
*****
*   Returns:
*     entero nNotas, numero de notas como valor Entero
*****/
int largo_notas(){ //Entregara la cantidad de notas
  int seguro; // Se utilizara para saber si un archivo se leyo correctamente
  FILE *fh = fopen("notas.dat","rb"); //Abre el archivo
  if(fh==NULL){
    printf("Su archivo notas.dat no se pudo  abrir correctamente\n");/*si el archivo no se abre, avisa que no se abrio correctamente*/
  }
  int nNotas; //Almacenara el entero M notas
  seguro = fread(&nNotas, sizeof(int), 1, fh); //Lee el numero de nota M en el archivo
  if(seguro != 1)printf("No se pudo leer el archivo notas.dat correctamente\n"); //Advierte que no se logro leer correctamente el archivo
  fclose(fh); //Cierra el archivo
  return nNotas;
}
/*****
*   int largo_cursos
*****
*   Funcion que obtiene y entrega la cantidad de Cursos
*****
*   Input:
*     vacio
*****
*   Returns:
*     entero cCursos, cantidad de cursos en valor Entero
*****/
int largo_cursos(){ //Obtiene la cantidad de cursos
  int seguro; // Se utilizara para saber si un archivo se leyo correctamente
  FILE *fh = fopen("cursos.dat","rb");
  if(fh==NULL){
    printf("Su archivo cursos.dat no se pudo abrir\n");/*si el archivo no se abre, avisa que no se abrio correctamente*/
  }
  int nCursos; //Almacenara el entero C cursos
  seguro = fread(&nCursos, sizeof(int), 1, fh); //Lee el numero de cursos en el archivo
  if(seguro != 1)printf("No se pudo leer el archivo cursos.dat correctamente\n"); //Advierte que no se logro leer correctamente el archivo
  fclose(fh);
  return nCursos;
}
/*****
*   int largo_alumnos
*****
*   funcion que obtiene y entrega la cantidad de alumnos
*****
*   Input:
*     vacio
*****
*   Returns:
*     int nAl, cantidad de alumnos en valor Entero
*****/
int largo_alumnos(){ //Obtiene la cantidad de alumnos
  int seguro; // Se utilizara para saber si un archivo se leyo correctamente
  int nAl; // String que almacenara el numero de alumnos
  FILE *fp = fopen("alumnos.txt", "r"); //Se abre el archivo de alumnos para lectura
  if(fp == NULL){
    printf("Su archivo alumnos.txt no se pudo abrir\n");/*Si el archivo no se abre, avisa que no se abrio correctamente*/
  }
  seguro = fscanf(fp,"%d", &nAl); // Asigna nAl la cantidad de alumnos leida en la primera linea
  if(seguro != 1)printf("No se pudo leer el archivo alumnos.txt correctamente\n"); //Advierte que no se logro leer correctamente el archivo
  fclose(fp);
  return nAl;
}
/*****
*   nota * Notas
*****
*   funcion creada para leer notas en el archivo dado, mediante fread y entrega un arreglo de structs con las Notas
*****
*   Input:
*     vacio
*****
*   Returns:
*     array Notas, arreglo con structs donde estan almacenadas las notas de cada alumno
*****/
nota * notas(){/*funcion para leer notas*/
  int seguro; // Se utilizara para saber si un archivo se leyo correctamente
  int nNotas = largo_notas(); //Almacenara el entero M notas
  FILE *fh = fopen("notas.dat","rb");
  if(fh==NULL){
    printf("Su archivo notas.dat no se pudo abrir correctamente\n");/*si el archivo no se abre, avisa que no se abrio correctamente*/
  }
  fseek(fh, sizeof(int), SEEK_SET); // Mueve la posicion hacia el primer rol del archivo
  nota *Notas = (nota*)malloc(sizeof(nota)*nNotas);// Se define un arrego dinamico que tendra el struct notas
  if(Notas == NULL)printf("No se pudo crear el arreglo Notas correctamente\n"); //Advierte si no se logro crear el arreglo
  seguro = fread(Notas, sizeof(nota), nNotas, fh); //Asigna a cada struct del arreglo el rol de estudiante, nota y sigla del curso respectivo leido desde el archivo de notas
  if(seguro != nNotas)printf("No se pudo leer el archivo notas.dat correctamente\n"); //Advierte que no se logro leer correctamente el archivo
  return Notas; //Retorna el arreglo de notas
}
/*****
*   curso * Cursos
*****
*   funcion creada para leer los cursos del archivo y almacenarlos en un arreglo con structs de tipo curso
*****
*   Input:
*     vacio
*****
*   Returns:
*   array Cs, arreglo que almacena los structs de los distintos Cursos
*****/
curso * cursos(){ //Funcion creada para leer los cursos y almacenarlos en un arreglo con struct curso
  int seguro; // Se utilizara para saber si un archivo se leyo correctamente
  FILE *fp=fopen("cursos.dat","rb");
  if(fp==NULL){
    printf("Su archivo cursos.dat no se pudo abrir correctamente\n");
  }
  int cCursos = largo_cursos();
  fseek(fp, sizeof(int),SEEK_SET);
  curso *Cs=(curso*)malloc(sizeof(curso)*cCursos); //Crea un arreglo dinamico donde se almacenan cCursos structs
  if(Cs == NULL)printf("No se pudo crear el arreglo Cs correctamente\n"); //Advierte si no se logro crear el arreglo
  seguro = fread(Cs,sizeof(curso),cCursos,fp); //guarda la sigla de curso y el semestre en el arreglo leido desde el archivo cursos.dat
  if(seguro != cCursos)printf("No se pudo leer el archivo cursos.dat correctamente\n"); //Advierte que no se logro leer correctamente el archivo
  fclose(fp);
  return Cs;
}
/*****
*   alumno * alumnos
*****
*   funcion que almacena los alumnos en un arreglo con structs del tipo alumno
*****
*   Input:
*     vacio
*****
*   Returns:
*     array Al, arreglo que almacena los structs de cada alumno
*****/
alumno * alumnos(){ //Almacena los alumnos en un arrgelo con struct de alumnos
  int seguro; // Se utilizara para saber si un archivo se leyo correctamente
  int i = 0; //Contador que se utilizara mas adelante
  char r[12]; // String que almacenara el rolEstudiante
  char name[25]; //String que almacenara el nombre (se asume que un nombre no puede tener mas de 25 caracteres)
  char Sname[25]; //String que almacenara el apellido (se asume que un apellido no puede tener mas de 25 caracteres)
  char anio[5]; //String que almacenara el anio
  int nAlumnos; // Entero que almacenara el numero de alumnos
  FILE *fp = fopen("alumnos.txt", "r"); //Se abre el archivo de alumnos para lectura
  if(fp == NULL){
    printf("El archivo alumnos.txt no se pudo abrir correctamente\n");/*Si el archivo no se abre, avisa que no se abrio correctamente*/
  }
  fseek(fp,0, SEEK_SET); //Mueve la posicion al comienzo del archivo
  seguro = fscanf(fp,"%d", &nAlumnos); //Obtiene la cantidad de alumnos
  if(seguro != 1)printf("No se pudo leer el archivo alumnos.txt correctamente\n"); //Advierte que no se logro leer correctamente el archivo
  alumno *Al = (alumno*)malloc(sizeof(alumno)*nAlumnos); //Se define un arreglo dinamico con el struct alumno
  if(Al == NULL)printf("No se pudo crear el arreglo Al correctamente\n"); //Advierte si no se logro crear el arreglo
  while(i < nAlumnos){
    seguro = fscanf(fp, "%s %s %s %s", r, name, Sname, anio); //Se leenel nombre, apellido, rolEstudiante y anio del archivo y se asignan a sus respectivs variables.
    if(seguro != 4)printf("No se pudo leer el archivo alumnos.txt correctamente\n");
    strcpy(Al[i].rol, r); //Se guarda el rol en el arreglo
    strcpy(Al[i].nombre, name); //Se guarda el nombre en el arreglo
    strcpy(Al[i].apellido, Sname);//Se guarda el apellido en el arreglo
    i++;
  }
  return Al;
}
/*****
*   void aprobados
*****
*   funcion que creara los archivos con los alumnos aprobados por cada semestre
*****
*   Input:
*     nota *Ns: arreglo con todas las notas en structs
*     int nt: cantidad de notas como valor Entero
*     curso *Cs: arreglo con los distintos Cursos
*     int ct: cantidad de cursos como valor Entero
*     alumno *Al: arreglo con los distintos alumnos
*     int at: cantidad de alumnos como entero
*****
*   Returns:
*     vacio
*****/
void aprobados(nota *Ns, int nt, curso *Cs,int ct, alumno *Al, int at){ //Funcion que creara los archivos con los aprobados (nt= largo del arreglo de notas, ct= largo del arreglo de cursos, at = largo del arreglo de alumnos)
  FILE *s1 = fopen("aprobados_s1.txt", "w+");// Se crea el archivo alumnos_s1.txt
  if(s1==NULL){
    printf("El archivo alumnos_s1.txt no se puedo crear\n");/*si el archivo no se abre, avisa que no se abrio correctamente*/
  }
  FILE *s2 = fopen("aprobados_s2.txt", "w+");// Se crea el archivo alumnos_s2.txt
  if(s2==NULL){
    printf("El archivo alumnos_s2.txt no se puedo crear\n");/*si el archivo no se abre, avisa que no se abrio correctamente*/
  }
  int i, q, z, j, v,a; //Variables que seran utilizadas para iterar
  int s_1,s_2;
  s_1=0;
  s_2=0;
  for (a=0;a<ct;a++){//almacena la cantidad de cursos por semestre
    if (Cs[a].semestre==1)s_1++;
    else if(Cs[a].semestre==2)s_2++;
  }
  for(i = 0; i < at; i++){ //Comienza la iteracion sobre todos los alumnos
    int h = 0;
    int p = 0;
    int p_1=0;
    int p_2=0;
    aprobadoS1 *pers = (aprobadoS1*)malloc(sizeof(aprobadoS1)*ct); //Arreglo que almacenara los ramos del primer semestre aprobados por el alumno con su nota
    if(pers == NULL)printf("No se pudo crear el arreglo pers correctamente\n"); //Advierte si no se logro crear el arreglo
    aprobadoS2 *pers2 = (aprobadoS2*)malloc(sizeof(aprobadoS2)*ct); //Arreglo que almacenara los ramos del segundo semestre aprobados por el alumno con su nota
    if(pers2 == NULL)printf("No se pudo crear el arreglo pers2 correctamente\n"); //Advierte si no se logro crear el arreglo
    for(j = 0; j < nt; j++){ //Se comienza a iterar sobre las notas
      if(Ns[j].nota >= 55 && strcmp(Ns[j].rolEstudiante, Al[i].rol) == 0) { //Si la nota es mayor a 55 y el rol corresponde con el estudiante en el que se esta iterando, se comienza la iteracion sobre los cursos
        for(z = 0; z < ct; z++){
          if(strcmp(Ns[j].siglaCurso, Cs[z].sigla) == 0){ //Se ve si la sigla del curso que se aprobo con 55 o mas coincide con la sigla del struct curso para encontar si es del S1 o S2
            if(Cs[z].semestre == 1){ //Si es del semestre 1 agrega la nota y el nombre del curso al arreglo dinamico.
              strcpy(pers[h].siglaCurso, Ns[j].siglaCurso);
              pers[h].nota = Ns[j].nota;
              p_1++;
              h++;
            }
            else if(Cs[z].semestre == 2){ //Si es del semestre 2 agrega la nota y el nombre del curso al arreglo dinamico del semestre 2.
              strcpy(pers2[p].siglaCurso, Ns[j].siglaCurso);
              pers2[p].nota = Ns[j].nota;
              p_2++;
              p++;
            }
          }
        }
      }
    }

    for(q = 0; q < h; q++){ //Se comienza a iterar sobre el arreglo dinamico del semestre 1
      if (p_1==s_1){
        if(q == 0)fprintf(s1, "%s %s %s ",Al[i].nombre, Al[i].apellido, Al[i].rol); //Si es la primera vez que se itera, se debe escribir el nombre, apellido y rol del alumno en el que estaba iterando
        if(q == h-1)fprintf(s1, "%s %d\n", pers[q].siglaCurso, pers[q].nota); //Si es la ultima iteracion, se debe agregar un \n a la escritura
        if(q != h-1)fprintf(s1, "%s %d ", pers[q].siglaCurso, pers[q].nota);// Se escribe la nota y el nombre del curso en el archivo
      }
    }
    for(v = 0; v < p; v++){// Se realiza lo mismo que el ciclo anterior pero con el archivo del semestre 2
      if (p_2==s_2){
        if(v == 0)fprintf(s2, "%s %s %s ",Al[i].nombre, Al[i].apellido, Al[i].rol);
        if(v == p-1)fprintf(s2, "%s %d\n", pers2[v].siglaCurso, pers2[v].nota);
        if(v != p-1)fprintf(s2, "%s %d ", pers2[v].siglaCurso, pers2[v].nota);
      }
    }


    void free(void * pers); //Se libera la memoria del arreglo del semestre 1
    void free(void * pers2); //Se libera la memoria del arreglo del semestre 2
      }
      fclose(s1);
      fclose(s2);
          }
/*****
*   int main
*****
*   funcion principal, hecha para correr el resto de las funciones anteriores y liberar memoria
*****
*   Input:
*     vacio
*****
*   Returns:
*     int 0, para mostrar que el programa se corrio de manera correcta
*****/
int main() {
  int m = largo_notas(); //Entero que entregara el largo del arrgelo de notas
  int n = largo_cursos(); //Entero que entregara el largo del arrgelo de cursos
  int c = largo_alumnos(); //Entero que entregara el largo del arrgelo de alumnos
  nota *Nt = notas(); //Se obtiene el arreglo de notas (leer funcion para saber mas)
  curso *Cs = cursos(); //Se obtiene el arreglo de curso (leer funcion para saber mas)
  alumno *Al = alumnos(); //Se obtiene el arreglo de alumnos (leer funcion para saber mas)
  aprobados(Nt, m, Cs, n, Al, c); //Funcion que crea los archivos
  /*#########LIBERAR MEMORIA########*/
  void free(void * Notas);
  void free(void * Cs);
  void free(void * Al);
  return 0;
}
