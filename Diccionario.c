#include "Funciones.h"

//Funcion Principal (main)

int main(int argc,char *argcv[])
{
  int cont = 0;
  char *op = NULL, *palabra = NULL, temp[30];

  //Modo comando
  if (argc == 3) {

    //Asigna y copia los parametros pasados en el comando
    op = (char *)malloc(sizeof(char)* strlen(argcv[1])+1);
    strncpy(op,argcv[1],strlen(argcv[1])+1);
    palabra = (char *)malloc(sizeof(char)* strlen(argcv[2])+1);
    strncpy(palabra,argcv[2],strlen(argcv[2])+1);
    ajustar_palabra(palabra);

    //Extrae los datos del archivo y carga en el TAD arbol trie
    GetInfo("arch.txt",&cont);
    Raiz = Inicializar();
    Raiz = SaveInfo(Raiz,cont-1);
    free(palabras);

    //Busca la palabra en el diccionario
    if ((strcmp(op,"s")== 0) || (strcmp(op,"S")== 0) || (strcmp(op,"A")== 0) || (strcmp(op,"a")== 0) || (strcmp(op,"T")== 0) || (strcmp(op,"t")== 0)){
      Buscar(Raiz,palabra,op);
    }
    else ("Comando Invalido\n\n");
  }

  //Modo iterativo
  if (argc == 1){
    do{
      free(op),free(palabra);
      op = (char *)malloc(sizeof(char)*8);
      palabra = (char *)malloc(sizeof(char)*15);
      printf(">");

      //Lee el comando escrito por el usuario y almacena la opcion y la palabra a buscar
      fgets(temp,30,stdin);
      sscanf(temp,"%s %s",op,palabra);

      //Busca la palabra si el archivo ya fue cargado
      if (((strcmp(op,"s")== 0) || (strcmp(op,"S")== 0) || (strcmp(op,"A")== 0) || (strcmp(op,"a")== 0)) || (strcmp(op,"T")== 0) || (strcmp(op,"t")== 0) && strlen(palabra) != 0){
        if (Raiz){
          ajustar_palabra(palabra);
          Buscar(Raiz,palabra,op);
        }
        else {
          printf("No se ha cargado ningun archivo\n\n");
        }
      }
      else {
        //Busca las opciones restantes en el menu de opciones del modo iterativo
        menu_iterativo(op,palabra);
      }
      printf("\n");
    }while ((strcmp(op,"Salir") != 0 || strcmp(op,"salir") != 0));
  }
  if (argc == 2){
    printf("Comando incompleto, vuelva a intentar\n\n");
  }

  return 0;
}
