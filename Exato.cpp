
#include <iostream>
#include "Exato.h"
#include <thread>
#include <future>
#include "Util.h"
#include <algorithm>

using namespace std;
#define minDegree(v,n) ((Util::Vertex) *(v+n-1)).degree
#define maxDegree(v) ((Util::Vertex) *v).degree
#define defineWorkingSet(v,l,d) while(l + 1 < n && ((Util::Vertex)* (v + l + 1)).degree == d) ++l
std::atomic<bool> clique_found(false);
//std::int maxThread;
std::array<int, 3> currentMaxSize;

std::vector<Util::Vertex> parallelFindClique(Util::Vertex* vertexArray, int l,int d)
{
        auto clique = Exato::findClique(vertexArray, l, d);
        if(!clique.empty()) {
            clique_found = true;
            return clique;
        }
        return {};
}

bool isCliqueAlreadyFound(int maxDegree){
    if(clique_found){
        for(int i=0; i<3; i++){
            if(maxDegree < currentMaxSize[i])
                return false;
            else
                return true;
        }
    }
    return false;

}

std::vector<Util::Vertex> Exato::exato(Util::Vertex* vertexArray, int n){
//    maxThread = 3;
    std::sort(vertexArray, vertexArray+n, Util::compareVertexByDegree); // ordena em ordem não crescente
    int number = vertexArray[0].degree;
    int mode = number;
    int count = 1;
    int countMode = 1;
    cout << "--------------- : " << endl;
    for (int i=0; i<n; i++)
    {
        if(vertexArray[i].degree >= 2) {
           // cout << "degree : " << vertexArray[i].degree << endl;
            if (vertexArray[i].degree == number) { // count occurrences of the current number
                count++;
            } else { // now this is a different number
                if (count > countMode) {
                    countMode = count; // mode is the biggest ocurrences
                    mode = number;
                }
                count = 1; // reset count for the new number
                number = vertexArray[i].degree;
            }
        }
    }
    cout << "mode : " << mode << endl;
    cout << "--------------- : " << endl;
    int l = 0;
    int d = maxDegree(vertexArray);
    int m = minDegree(vertexArray,n);
    while(d >= m){
        clique_found = false;
        defineWorkingSet(vertexArray, l, d);
        std::future<std::vector<Util::Vertex>> ret = std::async(parallelFindClique,vertexArray,l,d);
        currentMaxSize[0] = d;

        if(d < 1)
            return {};
        --d;
        defineWorkingSet(vertexArray, l, d);
        std::future<std::vector<Util::Vertex>> ret1 = std::async(parallelFindClique,vertexArray,l,d);
        currentMaxSize[1] = d;

        --d;
        defineWorkingSet(vertexArray, l, d);
        std::future<std::vector<Util::Vertex>> ret2 = std::async(parallelFindClique,vertexArray,l,d);
        currentMaxSize[2] = d;

        auto clique = ret.get();
        if(!clique.empty()){
            return clique;
        }
        auto clique2 = ret1.get();
        if(!clique2.empty()) {
            return clique2;
        }
        auto clique3 = ret2.get();
        if(!clique3.empty()) {
            return clique3;
        }
        d--;
    }
    return {};
}


std::vector<Util::Vertex> Exato::findClique(Util::Vertex* vertexArray, int l, int d){
    if(d > l) return {};
    bool used[l + 1];
    bool found = false;
    std::vector<Util::Vertex> result;
    cout << "thread name: " << this_thread::get_id() << " - valor do L: " << l << endl;
    Exato::subsets(vertexArray, l + 1, d, 0, 0, used, &found, &result);
    if(found) return result;
    return {};
}


void Exato::subsets(Util::Vertex* vertexArray, int n, int k, int start, int currentLength, bool* used, bool* found, std::vector<Util::Vertex>* result){
    if(isCliqueAlreadyFound(k)) return;
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

