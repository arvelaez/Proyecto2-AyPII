#include "Funciones.h"

//Funcion para ejecutar opciones del modo iterativo

void menu_iterativo(char *op,char *palabra){
  int cont = 0;
  if ((strcmp(op,"cargar") == 0 || strcmp(op,"Cargar")== 0) && palabra){

    //Extrae los datos y carga en el arbol
    GetInfo(palabra,&cont);
    Raiz = Inicializar();
    Raiz = SaveInfo(Raiz,cont-1);
    printf("Archivo cargado exitosamente\n");
    free(palabras);
  }
  else if ((strcmp(op,"Ayuda") == 0 || strcmp(op,"ayuda")== 0)){
    printf("\nComandos disponibles:\n\n\t1. cargar (nombre): Extrae las palabras del archivo (nombre)\n\t");
    printf("2. s (palabra): Busca los sinonimos de (palabra)\n\t3. a (palabra): Busca los antonimos de (palabra)\n\t4. t (palabra): Busca los antonimos y lo sinonimos de (palabra)\n\t");
    printf("5. salir : sale de la aplicacion\n\n");
  }
  else if ((strcmp(op,"Salir") == 0 || strcmp(op,"salir")== 0)){
    printf("\n\tFin de ejecucion..\n\n");
    exit(1);
  }
  else {
    printf("Comando Invalido, vuelva a intentar\n");
  }
}

//Ajusta las palabras ingresadas por la linea de comando

void ajustar_palabra (char *palabra){
  int i,lim;

  palabra[0]=toupper(palabra[0]);
  lim=strlen(palabra);
  for (i=1;i<lim;i++){
    palabra[i]=tolower(palabra[i]);
  }
}

//Extrae la data del archivo y almacena en un arreglo dinamico temporal

void GetInfo(char *filename,int *cont){

  FILE *arch;
  char temp[50];
  register int i;

  //Abre el archivo
  if ((arch = fopen(filename,"r")) == NULL){
    printf("No se pudo abrir el archivo\n");
    exit(1);
  }

  //Cuenta las lineas del archivo para asignar tamano al arreglo dinamico
  while (!feof(arch)){
    fgets(temp,50,arch);
    (*cont)++;
  }

  //Posiciona el apuntador al principio del archivo
  rewind(arch);

  //Reserva memoria dinamica para arreglo dinamico
  if ((palabras = (Archivo *)malloc((*cont)*sizeof(Archivo)))== NULL){
    printf("No se ha podido reservar la memoria\n\n");
    exit(1);
  }

  //Extrae contenido del archivo y almacena en arreglo dinamico
  for (i=0;!feof(arch);i++){
    fgets(temp,50,arch);
    temp[strlen(temp)-1] = '\0';
    sscanf(temp,"%c %s %s",&palabras[i].modo,palabras[i].Palabra1,palabras[i].Palabra2);
  }

  //Cierra el archivo
  fclose(arch);
}

//Crea la raiz del arbol (Entrada al arbol)

Trie *Inicializar() {
  Trie *Raiz = NULL;

  //Reservamos memoria para la raiz
  if ((Raiz = (Trie *)malloc(sizeof(Trie))) == NULL){
    printf("No se ha podida reservar memoria para la raiz\n");
    exit(1);
  }

  //Inicializamos todos los apuntadores hijos a NULL
  for (register int i=0;i<26;i++){
    Raiz->hijos[i] = NULL;
  }
  return Raiz;
}

//Crea un nuevo nodo en el arbol

Trie *CreaNodo(char car){

  Trie *new = NULL;
  //Reserva memoria para el nodo
  if ((new = (Trie *)malloc(sizeof(Trie))) == NULL){
    printf("No se ha podida reservar memoria para el nodo\n");
    exit(1);
  }
  new->c = car;
  new->isWord = 0;
  new->contAntonimos = 0;
  new->contSinonimos = 0;

  //Inicializa todos los apuntadores hijos a NULL
  for (register int i=0;i<26;i++){
    new->hijos[i] = NULL;
  }
  return new;
}

//Carga todas las palabras del archivo en el arbol

Trie *SaveInfo(Trie *Raiz,int n){
  for (register int i=0;i<n;i++){
    Insertar(&Raiz,palabras[i].Palabra1,palabras[i].Palabra2,palabras[i].modo);
    Insertar(&Raiz,palabras[i].Palabra2,palabras[i].Palabra1,palabras[i].modo);
  }
  return Raiz;
}

//Inserta una palabra en el arbol y anade la otra en su lista de sinonimos o antonimos

void Insertar(Trie **Raiz,char word1[],char word2[],char modo){
  Trie *p = *Raiz;
  int index = 0;

  //Inserta o recorre a word1 en el arbol
  for (register int i=0;word1[i];i++){
    index = word1[i]-'a';
    if (p->hijos[index] == NULL){
      p->hijos[index] = CreaNodo(word1[i]);
    }
    p = p->hijos[index];
  }

  //Marca como fin de palabra el nodo actual
  p->isWord = 1;

  //Almacena a word2 en la lista de sinonimos de word1
  if (modo == 'S'){
    if (!SeEncuentra(p->sinonimos,p->contSinonimos,word2)){
      p->sinonimos[p->contSinonimos] = (char *)malloc(sizeof(char)*(strlen(word2)+1));
      strncpy(p->sinonimos[p->contSinonimos],word2,strlen(word2)+1);
      p->contSinonimos+=1;
    }
  }
  //Almacena a word2 en la lista de antonimos de word1
  else if (modo == 'A'){
    if (!SeEncuentra(p->antonimos,p->contAntonimos,word2)) {
      p->antonimos[p->contAntonimos] = (char *)malloc(sizeof(char)*(strlen(word2)+1));
      strncpy(p->antonimos[p->contAntonimos],word2,strlen(word2)+1);
      p->contAntonimos+=1;
    }
  }
}

//Busca la lista de sinonimos o antonimos de una palabra

void Buscar(Trie *Raiz,char word[],char *modo){
  Trie *p = Raiz;
  int index = 0;
  register int i;

  //Ciclo para recorrer el arbol
  for (i=0;word[i];i++){
    index = word[i]-'a';
    if (p->hijos[index] == NULL) {
      printf("La palabra no se encuentra en el diccionario\n");
      return;
    }
    p = p->hijos[index];
  }

  //Busca lista de sinonimos o antonimos
  if (!word[i] && p->isWord == 1){
    if (strcmp(modo,"S") == 0 || strcmp(modo,"s") == 0){
      if (p->contSinonimos == 0){
        printf("El archivo ingresado no posee sinonimos para esta palabra\n");
        return;
      }
      else {
        //Imprime lista
        for (register int j=0;j<(p->contSinonimos);j++){
          printf("%s ",p->sinonimos[j]);
        }
        printf("\n");
      }
    }
    else if (strcmp(modo,"A") == 0 || strcmp(modo,"a") == 0){
      if (p->contAntonimos == 0){
        printf("El archivo ingresado no posee antonimos para esta palabra\n");
        return;
      }
      else {
        //Imprime lista
        for (register int j=0;j<(p->contAntonimos);j++){
          printf("%s ",p->antonimos[j]);
        }
        printf("\n");
      }
    }
    else if (strcmp(modo,"t") == 0 || strcmp(modo,"T") == 0){
      if (p->contAntonimos == 0 && p->contSinonimos != 0){
        printf("El archivo ingresado no posee antonimos para esta palabra\n");
        printf("\nSinonimos:\n");

        //Imprime lista sinonimos
        for (register int j=0;j<(p->contSinonimos);j++){
          printf("%s ",p->sinonimos[j]);
        }
        printf("\n");
        return;
      }
      if (p->contAntonimos =! 0 && p->contSinonimos == 0){
        printf("El archivo ingresado no posee sinonimos para esta palabra\n");
        printf("\nAntonimos:\n");

        //Imprime lista sinonimos
        for (register int j=0;j<(p->contAntonimos);j++){
          printf("%s ",p->antonimos[j]);
        }
        printf("\n");
        return;
      }
      if(p->contAntonimos =! 0 && p->contSinonimos != 0) {
        printf("Antonimos:\n");

        //Imprime lista Antonimos
        for (register int j=0;j<(p->contAntonimos);j++){
          printf("%s ",p->antonimos[j]);
        }
        printf("\n");
        printf("\nSinonimos:\n");
        //Imprime lista sinonimos
        for (register int j=0;j<(p->contSinonimos);j++){
          printf("%s ",p->sinonimos[j]);
        }
        printf("\n");
      }
    }
  }
}


//Verifica que la palabra proxima a inserta, no se encuentre contenida en la lista

int SeEncuentra(char *sinonimos[],int n,char *word){
  register int i;
  for (i=0;i<n;i++){
    if (strcmp(sinonimos[i],word) == 0) return 1;
  }
  return 0;
}
