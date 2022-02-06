#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*Estructura numero 1: Aqui se vuelca la informacion del archivo*/
typedef struct Archivo {
    char Palabra1[20];    // 1era palabra de la linea que se lee
    char Palabra2[20];    // 2da palabra de la linea que se lee
    char modo;            // Indica si es antonimo(A-a) o sinonimo(S-s)
}Archivo;
Archivo *palabras;

/*Estructura numero 2:  Esta es para los nodos de nuestro arbol*/
typedef struct trieNode {
    char c;                           //Caracter del nodo
    int isWord;                       //Booleano que nos indica si en ese nodo termina una palabra
    struct trieNode *hijos[26];       //Arreglo de apuntadores para cada letra del alfabeto
    int contAntonimos;                //Cantidad de Antonimos
    int contSinonimos;                //Cantidad de Sinonimos
    char *sinonimos[5];               //Lista de sinonimos
    char *antonimos[5];               //Lista de antonimos
}Trie;
Trie *Raiz;


/*----------------------------------------------*/
/*----------------------------------------------*/

//BLOQUE 1 : Extraer informacion del arhcivo de texto

//Extrae los datos del archivo y los almacena en el arreglo dinamico
void GetInfo(char *filename,int *cont);

/*----------------------------------------------*/
/*----------------------------------------------*/

//BLOQUE 2: Carga del Diccionario en el arbol

//Inicializa la raiz del arbol
Trie *Inicializar();

//Crea Nodos en el arbol
Trie *CreaNodo(char car);

//Carga la data del arreglo dinamico en el arbol
Trie *SaveInfo(Trie *Raiz,int n);

//Inserta palabras en el arbol
void Insertar(Trie **Raiz,char word1[],char word2[],char modo);

/*----------------------------------------------*/
/*----------------------------------------------*/

//BLOQUE 3 : Busqueda de palabras

//Busca Palabras en el arbol
void Buscar(Trie *Raiz,char word[],char *modo);

//Verifica si un sinonimo ya se encuentra en la lista
int SeEncuentra(char *sinonimos[],int n,char *word);

/*----------------------------------------------*/
/*----------------------------------------------*/

//Funciones de complementacion

//Menu de opciones para el modo iterativo
void menu_iterativo(char *op,char *palabra);

//Funcion para adjustar una palabra ingresada por teclado
void ajustar_palabra (char *palabra);

/*----------------------------------------------*/
/*----------------------------------------------*/
