//
// Created by Ederson Montagner on 11/12/16.
//

#include "ExactAlgorithm.h"
#include "Util.h"

std::vector<Util::Vertex> Util::exato(Util::Vertex* vertexArray, int n){

    std::sort(vertexArray, vertexArray+n, Util::compareVertexByDegree); // ordena em ordem não crescente
    int l = 0, d = ((Util::Vertex)* vertexArray).degree; // começa com tamanho 1 e o grau do primeiro vertice
    while( vertexArray+l <= vertexArray+n && d > 1){
        while(((Util::Vertex)* (vertexArray + l + 1)).degree == d) ++l; // incluí os vértices de grau d, isso aqui é bom?? como binomial(n,k) varia??
        if(l + 1 >= d){
            bool u[l + 1];
            bool found = false;
            std::vector<Util::Vertex> result;
            Util::subsets(vertexArray, l + 1, d, 0,0, u, &found, &result);
            if(found) return result;
        }
        --d;
    }
}
