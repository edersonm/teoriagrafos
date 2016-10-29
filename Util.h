//
// Created by morps on 10/19/16.
//
#include<string>
#include<list>
#include<vector>

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
    typedef struct {
        int node;
        std::list<int> adj;
        int degree;
    } Vertex;

    //with default value
    int GetStr2Int(std::string strConvert = "");
    std::string GetInt2Str(int intConvert= 0);
    void readFileLista(std::string arquivo ,int *n,VertexType Vet[]);
    void writeGraphLista(int n,VertexType Vet[] );
    void inserePrimeiro(CList * L , int u );
    void imprimeOrdem(int n,VertexType Vet[] );
    void writeCList(CList * C );
    void bfs(int s,int n,VertexType Vet[]);
    bool isConnected(int n,VertexType Vet[]);
    void dfs(int u,int n,VertexType Vet[],int *cont);
    void ordenatop(int u,int n,VertexType Vet[],CList * L);
    int commonMembers(std::list <int> a, std::list <int> b);

    bool hasclique(int n, VertexType Vet[]);
    int cliquesize(int n, VertexType Vet[]);
    Util(int maxV);

    static int getn(std::string fileName);


    static Vertex *readGraph(std::string fileName);

    static bool compareVertexByDegree(Vertex a, Vertex b);

    static void printVertexArray(Vertex *v, int n);

    static void subsets(Util::Vertex *vertexArray, int n, int k, int start, int currLen, bool* used, bool* found, std::vector<Util::Vertex>* result);

    static bool completeSubgraph(std::vector<Util::Vertex> subgraph);

    static std::vector<Util::Vertex> exato(Vertex *vertexArray, int n);

};
#endif //PROJETOTG_UTIL_H