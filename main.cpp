
/********************************************************
 * Henrique Colonese Echternacht             - 201835028
 * Lívia Pereira Ozório                      - 201835011
 * Regina Sarah Monferrari Amorim de Paula   - 201835007
 *******************************************************/
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
#include "Leitura.h"
#include "Ordenacao.h"
#include "Book.h"
#include "Author.h"
#include "Hash.h"
#include "ArvoreVP.h"
#include "NoVP.h"
#include "ArvoreB.h"

using namespace std;

string arvore_b_2 = "Arvore B (2)";
string arvore_b_10 = "Arvore B (20)";
string arvore_vp = "Arvore Vermelha e Preta";

///clone
///Escrita no arquivo de saida
void Escrita(ofstream* Saida, string tipo_arvore, double tempo_processamento, int comparacoes, int copias, int tamanho)
{
        *Saida << tipo_arvore << endl;
        *Saida << "Tamanho: " << tamanho << endl;
        *Saida << "Tempo de Processamento: " << tempo_processamento << endl;
        *Saida << "Numero de Comparacoes: " << comparacoes << endl;
        *Saida << "Numero de Copias: " << copias << endl << endl;
}

void Escrita_parte2(ofstream* Saida, vector<Author*> autor)
{
        *Saida << "PARTE 2" << endl;
        *Saida << "M = " << autor.size() << endl;
        int tam = autor.size();
        for(int i = 0; i < autor.size(); i++)
        {
          *Saida << "Nome Autor: " << autor[i]->get_nome()  << " Frequencia: " << autor[i]->get_contador() << endl;
        }
}



int main()
{
    int N = 0;
    ///Tamanho dataset autores
    int M = 703200; 
    ///Numero de buscas
    int m = 50; 
    ifstream entrada;
    ofstream saidaInsercao, saidaBusca, saidaParte2;
    Hash* authors = new Hash(M);
    leituraAuthor(authors, M);

    entrada.open("arquivos/entrada.txt");
    saidaInsercao.open("arquivos/saidaInsercao.txt");
    saidaBusca.open("arquivos/saidaBusca.txt");
    saidaParte2.open("arquivos/saidaParte2.txt");

    if(entrada.is_open())
    {
        string n;
        getline(entrada, n);
        N = std::stoi(n);
        int tamanho[N];
       
        for (int i = 0; i < N; i++)
        {
            vector<Author*> autor_ordenado;
            ArvoreVP vp;
            ArvoreB b_2(2);
            ArvoreB b_10(20);

            getline(entrada, n);
            tamanho[i] = std::stoi(n);

            Book *lista = new Book[tamanho[i]];
            Book *lista2 = new Book[tamanho[i]];
            
            leitura_dataset(lista, tamanho[i], authors, &autor_ordenado);

            igual(lista2, lista, tamanho[i]);

            numComparacoes = 0;
            numCopias = 0;

            int tamOrdenado=autor_ordenado.size();
            
            ///PARTE 2
            MergeSortInt(&autor_ordenado[0], 0, tamOrdenado-1);

            Escrita_parte2(&saidaParte2, autor_ordenado);

            ///PARTE 3 INSERCAO
            saidaInsercao << endl << "PARTE 3 Insercao" << endl << endl;
            auto start = std::chrono::steady_clock::now();
            insercao_b(lista, &b_2, tamanho[i]);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;

            Escrita(&saidaInsercao, arvore_b_2, elapsed_seconds.count(), b_2.num_comparacoes, b_2.num_copias, tamanho[i]);
          
            start = std::chrono::steady_clock::now();
            insercao_b(lista, &b_10, tamanho[i]);
            end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_sec = end-start;

            Escrita(&saidaInsercao, arvore_b_10, elapsed_sec.count(), b_10.num_comparacoes, b_10.num_copias, tamanho[i]);
     
            start = std::chrono::steady_clock::now();
            insercao_vp(lista, &vp, tamanho[i]);
            end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_second = end-start;

            Escrita(&saidaInsercao, arvore_vp, elapsed_second.count(), vp.num_comparacoes, vp.num_copias, tamanho[i]);
            cout << "A insercao nas arvores foi finalizada!" << endl;
//----------------------------------------------------------
            ///PARTE 3 BUSCA
            saidaBusca << endl << "PARTE 3 Busca" << endl << endl;
            start = std::chrono::steady_clock::now();
            busca_b(lista,&b_2, 5);
            end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_sec1 = end-start;

            Escrita(&saidaBusca, arvore_b_2, elapsed_sec1.count(), b_2.num_comparacoes_busca, b_2.num_copias, tamanho[i]);
          
            start = std::chrono::steady_clock::now();
            busca_b(lista, &b_10, 5);
            end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_sec2 = end-start;

            Escrita(&saidaBusca, arvore_b_10, elapsed_sec2.count(), b_10.num_comparacoes_busca, b_10.num_copias, tamanho[i]);
     
            start = std::chrono::steady_clock::now();
            busca_vp(lista, &vp, 5);
            end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_sec3 = end-start;

            Escrita(&saidaBusca, arvore_vp, elapsed_sec3.count(), vp.num_comparacoes_busca, vp.num_copias, tamanho[i]);

            cout << "A busca nas arvores foi finalizada!" << endl;
            delete[] lista;
            delete[] lista2;
        }
        saidaInsercao.close();
        saidaBusca.close();
        saidaParte2.close();
        cout << "Programa finalizado!" << endl;
    }
    else
    {
        cout << "Erro ao abrir o arquivo" << endl;
    }
    return 0;
}