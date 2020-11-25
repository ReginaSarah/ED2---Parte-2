#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <utility>
#include <random>
#include <chrono>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <algorithm>
#include <vector> 
#include <boost/algorithm/string.hpp>
#include "Book.h"
#include "Author.h"
#include "Hash.h"
#include "ArvoreVP.h"
#include "NoVP.h"

using namespace std;

#define MENOR -1
#define IGUAL 0
#define MAIOR 1
#define INFINITO -1

int numComparacoes = 0;
int numCopias = 0;

///Função para igualar dois vetores de livros
void igual(Book livro1[], Book livro2[], int tamanho)
{
    for(int i = 0; i < tamanho; i++)
    {
        livro1[i] = livro2[i];
    }
}


///Auxiliar MergeSort para inteiro
void MergeTripleSortInt(Author** autor_ordenado, int primeiro, int meio, int ultimo)
{
    int x, y, z;
    int a = meio - primeiro +1;
    int b = ultimo - meio;
    Author *Primeiro = new Author[a];
    Author *Segundo  = new Author[b];
    for(int x = 0; x < a; x++)
    {
        Primeiro[x] = *autor_ordenado[primeiro+x];
    }
    for(int y = 0; y < b; y++)
    {
        Segundo[y] = *autor_ordenado[meio+1+y];
    }

    x = 0;
    y = 0;
    z = primeiro;

    while(x < a && y < b)
    {
        if(Primeiro[x].get_contador() >= Segundo[y].get_contador())
        {
            *autor_ordenado[z] = Primeiro[x];
            x++;
            numCopias++;
        }
        else
        {
            *autor_ordenado[z] = Segundo[y];
            y++;
            numCopias++;
        }
        z++;
    }
    while(x < a)
    {
        *autor_ordenado[z] = Primeiro[x];
        x++;
        z++;
        numCopias++;
    }
    while(y < b)
    {
        *autor_ordenado[z] = Segundo[y];
        y++;
        z++;
        numCopias++;
    }
    
    delete [] Primeiro;
    delete [] Segundo;
}

///Metodo MergeSort para inteiro
void MergeSortInt(Author **autor_ordenado, int primeiro, int ultimo)
{
    int media;
    if(primeiro < ultimo)
    {
        media = primeiro + (ultimo - primeiro)/2;
        MergeSortInt(autor_ordenado, primeiro, media);
        MergeSortInt(autor_ordenado, media+1, ultimo);
        MergeTripleSortInt(autor_ordenado, primeiro, media, ultimo);
    }
}
