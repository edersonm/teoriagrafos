
#include <iostream>
#include "Exato.h"
#include "Util.h"

using namespace std;
#define minDegree(v,n) ((Util::Vertex) *(v+n-1)).degree
#define maxDegree(v) ((Util::Vertex) *v).degree
#define defineWorkingSet(v,l,d) while(((Util::Vertex)* (v + l + 1)).degree == d) ++l

std::vector<Util::Vertex> Exato::exato(Util::Vertex* vertexArray, int n){
    std::sort(vertexArray, vertexArray+n, Util::compareVertexByDegree); // ordena em ordem não crescente
    int l = 0;
    int d = maxDegree(vertexArray);
    int m = minDegree(vertexArray,n);
    while(d >= m){
        defineWorkingSet(vertexArray, l, d);
        auto clique = findClique(vertexArray, l, d);
        if(!clique.empty()) return clique;
        d--;
        }
    return {};
}

std::vector<Util::Vertex> Exato::findClique(Util::Vertex* vertexArray, int l, int d){
    if(d > l) return {};
    bool used[l + 1];
    bool found = false;
    std::vector<Util::Vertex> result;
    Exato::subsets(vertexArray, l + 1, d, 0, 0, used, &found, &result);
    if(found) return result;
    return {};
}


void Exato::subsets(Util::Vertex* vertexArray, int n, int k, int start, int currentLength, bool* used, bool* found, std::vector<Util::Vertex>* result){
    if(currentLength == k && !*found){
        std::vector<Util::Vertex> subset;
        subset.reserve(k);
        for(int i = 0; i < n; ++i){
            if(used[i]){
                Util::Vertex no = *(vertexArray + i);
                subset.push_back(no);
            }
        }
        if(subset.size() > 1 && Util::completeSubgraph(subset)){ // <= 2 é o casso trivial
            *found = true;
            std::cout << k << "-Clique encontrado:   ";
            for(Util::Vertex v : subset)
                std::cout << v.node << ", ";
            std::cout << std::endl;
            for(Util::Vertex t : subset)
                (*result).push_back(t);
            return;
        }
        return;
    }

    if(start == n){
        return;
    }

    used[start] = true;
    Exato::subsets(vertexArray, n, k, start + 1, currentLength + 1, used, found, result);

    used[start] = false;
    Exato::subsets(vertexArray, n, k, start + 1, currentLength, used, found, result);
    return;
}

