//
// Created by morps on 10/13/16.
//

#include "Principal.h"
#include "Util.cpp"
#include "PreProcessing.cpp"
#include <iostream>

using namespace std;

int main() {
    int limite = 50;
    int n;
    Util u(limite);
    PreProcessing pre;
    string arquivo="k5.in";
    Util::VertexType Vet[limite];
    u.readFileLista(arquivo,&n,Vet);
    cout << "Lendo arquivo: " <<arquivo << endl;
    std::cout << "\n\nLeitura do Grafo em Lista de Adjacências\n\n";
    u.writeGraphLista(1,Vet);
    pre.orderByAdjacencies(Vet);
    std::cout << "\n\nGrafo possui cliques?"<< u.hasclique(5,Vet) << "\n\n";
    std::cout << "\n\nMaior cliques?"<< u.cliquesize(5,Vet) << "\n\n";
    return 0;
}
