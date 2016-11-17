//
// Created by morps on 10/19/16.
//
#include<string>
#include<list>
#include<vector>
#include<array>

#ifndef PROJETOTG_UTIL_H
#define PROJETOTG_UTIL_H

class Util
{

private :
    int maxVert;
     // constante que define o número máximo de vértices
public :
    typedef struct {
        std::list <int> Adj;	// armazena adjacências do vértice
        bool visitado; 	// indica se o vértice já foi visitado na DFS
        int p;			// indica o pai/predecessor do vértice na DFS
        int d;			// número DFS
        int l;
    } VertexType;
    typedef struct CList {
        int a;			// first!
        struct CList* b;			// second!
    } CList;
    struct Vertex{
        int node;
        std::list<int> adj;
        int degree;
        bool operator< (const Util::Vertex& right) const { return node < right.node;}
    };

    static int getn(std::string fileName);
    static Vertex *readGraph(std::string fileName);
    static Vertex *readNXGraph(std::string fileName);
    static std::array<double, 3> readGraphInfo(std::string fileName);

    static bool compareVertexByDegree(Vertex a, Vertex b);

    static void printVertexArray(Vertex *v, int n);


    static bool completeSubgraph(std::vector<Util::Vertex> subgraph);
    static bool completeSubgraphh(std::vector<Util::Vertex> subgraph, int d);


    static void b_exato(int q, int w, std::string prefix, std::string posfix);
};
#endif //PROJETOTG_UTIL_H