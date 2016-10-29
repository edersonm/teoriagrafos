//
// Created by morps on 10/13/16.
//

#include <stdlib.h>
#include<fstream>
#include<sstream>
#include<list>
#include<iostream>
#include <climits> // para usar INT_MAX
#include<string>
#include <vector>
#include "Util.h"
#include <cstring>
#include <algorithm>
using namespace std;

// **************************** FUNÇÕES GERAIS ************************************************

// Convert string to integer
int Util::GetStr2Int(string strConvert) {
    int intReturn;
    intReturn = atoi(strConvert.c_str());
    return(intReturn);
}

// Convert integer to string
string Util::GetInt2Str(int intConvert) {
    stringstream out;
    out << intConvert;
    return(out.str());
}

// **************************** LEITURA DO ARQUIVO DE ENTRADA *******************************

// lê o arquivo de entrada e "carrega" na lista de adjacências Vet
// variável n é passada por referência (não por valor), porque será modificada
void Util::readFileLista(string arquivo,int *n,VertexType Vet[]){
    string line;
    short v,u,i,temp;
    ifstream myfile; // abre arquivo e aponta para próximo elemento a ser lido
    myfile.open (arquivo.c_str(),ios::in);
    if (myfile.is_open()){
        i=0;
        while (myfile.good()){
            i++;
            getline(myfile,line);
            if (i==1) *n=GetStr2Int(line);// número de vértices do grafo, converte string para inteiro
            else if (line.length()>0){ // demais vértices do grafo
                temp=line.find_first_of(":");
                v=GetStr2Int(line.substr(0,temp));
                line=line.substr(temp+1);
                while (line.length()>1){
                    temp=line.find_first_of(",");
                    u=GetStr2Int(line.substr(0,temp));
                    line=line.substr(temp+1);
                    Vet[v].Adj.push_back(u);
                    Vet[u].Adj.push_back(v);
                }
            }
        }
        myfile.close();
        for(i=1;i!=*n;i++){
            Vet[i].l = Vet[i].Adj.size();
        }
    }
    else cout << "Unable to open file";
}

// **************************** FUNÇÕES SOBRE A LISTA DE ADJACÊNCIAS *******************************

//lê a lista de adjacências Vet e "imprime" o conteúdo para o usuário
void Util::writeGraphLista(int n,VertexType Vet[]){
    int u;
    list<int>:: iterator it;
    for(int i=1;i<=n;i++){
        std::cout << "O vértice "<< i << " é adjacente a: ";
        for (it=Vet[i].Adj.begin(); it!=Vet[i].Adj.end(); it++){
            u=*it;
            std::cout << u << ", ";
        }
        std::cout << "\n";
    }
}


void Util::inserePrimeiro(CList * L, int u){

    if(L->a == -1){
        L->a = u;
    }else{
        CList * temp = new CList;
        temp->a = L->a;
        temp->b = L->b;
        L->a = u;
        L->b = temp;
    }

}

void Util::writeCList(CList * C){
    if(C->b){
        std::cout << C->a << ", ";
        writeCList(C->b);
    }else{
        std::cout << C->a << ", ";
    }
}



// BFS começando a partir do vértice s
void Util::bfs(int s,int n,VertexType Vet[]){
    int u;

    // marca todos os vértices como não visitados e sem predecessor
    for(int i = 1; i <= n; i++){
        Vet[i].visitado=false;
        Vet[i].p=-1;
    }
    Vet[s].p=s; // o vértice inicial da BFS é predecessor dele mesmo

    // cria uma lista encadeada que será a fila da BFS
    list<int> fila;

    // marca o vértice atual como visitado e o enfileira
    Vet[s].visitado = true;
    fila.push_back(s); // enfileira, ou seja, adiciona elemento no final da lista

    // it é iterador usado para obter todos os vértices adjacentes de um vértice
    list<int>:: iterator it;

    while(!fila.empty()){ // enquanto a fila não estiver vazia
        // desenfileira um vértice da fila e imprime

        s = fila.front(); // obtém o primeiro elemento da lista
        fila.pop_front(); // remove o primeiro elemento da lista
        std::cout << "\n Vertice:" <<s ;
        // Obtém todos os vértices adjacentes do vértice "desenfileirado"
        for (it=Vet[s].Adj.begin(); it!=Vet[s].Adj.end(); it++){
            u=*it;
            // se vértice adjacente ainda não foi visitado, marca como visitado e o enfileira
            if (!Vet[u].visitado){
                Vet[u].visitado=true; // marca como visitado
                Vet[u].p=s; // guarda quem foi o vértice predecessor na BFS desse vértice
                fila.push_back(u); // enfileira, ou seja, adiciona elemento no final da lista
            }
        }
    }
}

// verifica se o grafo de entrada é conexo
bool Util::isConnected(int n,VertexType Vet[]){
    bool retorno = true;
    int i,j;
    int cont;
    for (i=n; i!=1; i--){
        cont = 1;
        std::cout << "\n Caminho mínimo de "<<i<<"\n" ;
        for(j = Vet[i].p;j!=Vet[j].p;j=Vet[j].p) {
            if (j == -1) {
                return false;
            }

        }
    }
    return retorno;

}
//Needs fix
int Util::commonMembers(list <int> a, list <int> b){
    int retorno = 0;
    list<int>:: iterator it1,it2;
    for(it1 = a.begin();it1!=a.end();it1++) {
         for(it2 = b.begin();it2!=b.end();it2++){
            if(*it1== *it2){
                retorno++;
                break;
            }
        }
    }
    return retorno;
}
//+- working
bool Util::hasclique(int n, VertexType Vet[]){

    bool retorno = false;
    int i,u;
    list<int>:: iterator it;
    for (i=n; i>2; i--){
        for (it=Vet[i].Adj.begin(); it!=Vet[i].Adj.end(); it++){
            u=*it;
            if (commonMembers(Vet[i].Adj,Vet[u].Adj)> 0 )  {
                return true;
            }
        }
    }

    return retorno;
}

//Needs fix
int Util::cliquesize(int n, VertexType Vet[]){

    int retorno = 0;
    bool teste = false;
    int i,u;
    list<int>:: iterator it;
    for (i=n; i>2; i--){
        for (it=Vet[i].Adj.begin(); it!=Vet[i].Adj.end(); it++){
            u=*it;
            int temp = commonMembers(Vet[i].Adj,Vet[u].Adj);
            //std::cout << "\ncaso:"<<n<<"  "<<temp << "\n";
            retorno = temp > retorno ? temp : retorno;
        }
    }

return retorno == 0 ? retorno:retorno+1;
}
void Util::imprimeOrdem(int n, VertexType *Vet) {
    int i;
    for(i =1;i!=n;i++ ){
        std::cout << "Ordem de:"<<i<<":  "<<Vet[i].l << "\n";
    }
}


// DFS começando a partir do vértice s
void Util::dfs(int u,int n,VertexType Vet[],int *cont){
    int v;

    Vet[u].visitado=true;
    Vet[u].d=*cont;
    cout << "Vértice entrando na dfs: " << u <<" - Valor de cont atribuído: " << Vet[u].d << "\n";

    // it é iterador usado para obter todos os vértices adjacentes de um vértice
    list<int>:: iterator it;

    // Obtém todos os vértices adjacentes do vértice u
    for (it=Vet[u].Adj.begin(); it!=Vet[u].Adj.end(); it++){
        v=*it;
        // se vértice adjacente ainda não foi visitado, marca como visitado e chama recursão
        if (!Vet[v].visitado){
            Vet[v].p=u; // marca como visitado
            (*cont)++;
            dfs(v,n,Vet,cont);
        }
    }
    cout << "Vértice saindo na dfs: " << u <<" - Valor de cont atribuído: " << Vet[u].d << "\n";

}

// **************************** ORDENAÇÃO TOPOLÓTICA COM BUSCA EM PROFUNDIDADE ************************
void Util::ordenatop(int u,int n,VertexType Vet[],CList * L){
    int v;

    Vet[u].visitado=true;


    // it é iterador usado para obter todos os vértices adjacentes de um vértice
    list<int>:: iterator it;

    // Obtém todos os vértices adjacentes do vértice u
    for (it=Vet[u].Adj.begin(); it!=Vet[u].Adj.end(); it++){
        v=*it;
        // se vértice adjacente ainda não foi visitado, marca como visitado e chama recursão
        if (!Vet[v].visitado){
            Vet[v].p=u; // marca como visitado
            ordenatop(v,n,Vet,L);
        }

    }
    inserePrimeiro(L,u);
}

Util::Util(int maxV) {
    maxVert = maxV;
}

//-------------------------------------------------------------------------------------------------------------

int Util::getn(string fileName){
    std::ifstream file(fileName.c_str(), ios::in);
    std::cout << file.is_open() << endl;
    std::string line;
    if (file.is_open() && std::getline(file, line)){
        int n = stoi(line);
        return n;
    }
    return -1;
}

Util::Vertex* Util::readGraph(std::string fileName){
    Util::Vertex* VertexArray = NULL;
    std::ifstream file(fileName.c_str(), ios::in);
    std::cout << file.is_open() << endl;
    int n;
    if (file.is_open()){
        std::string line;
        if (std::getline(file, line)){
            n = stoi(line) + 1;
            VertexArray = new Vertex [n];
        }else {return NULL;}
        while(std::getline(file, line)){
            int k = stoi(std::strtok(&line[0], ":,"));
            for(char* c = std::strtok(NULL, ":,"); c != NULL; c = std::strtok(NULL, ":,")){
                int a = stoi(c);
                VertexArray[k].adj.push_back(a);
                VertexArray[a].adj.push_back(k);
            }
        }
    }
    file.close();
    for(int i = 1; i < n; ++i){
        VertexArray[i].node = i;
        VertexArray[i].degree = VertexArray[i].adj.size();
    }

    return VertexArray;
}

bool Util::compareVertexByDegree(Util::Vertex a, Util::Vertex b){
   return a.degree > b.degree;
}

void Util::printVertexArray(Util::Vertex* v, int n){
    for(int i = 1; i < n; ++i){
        std::cout << "Node " << v[i].node << " degree " << v[i].degree << "  ->  ";
        for(int r : v[i].adj){
           std::cout << v[r].node << " ";
        }
        std::cout << std::endl;
    }
    std::cout << endl << endl;
}

void Util::subsets(Util::Vertex* vertexArray, int n, int k, int start, int currentLength, bool* used, bool* found, std::vector<Util::Vertex>* result){

    if(currentLength == k && !*found){

        std::vector<Util::Vertex> subset;
        for(int i = 0; i < n; ++i){
            if(used[i]){
                Util::Vertex no = *(vertexArray + i);
                subset.push_back(no);
            }
        }

        if(subset.size() > 2 && Util::completeSubgraph(subset)){ // <= 2 é o casso trivial
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
    Util::subsets(vertexArray, n, k, start + 1, currentLength + 1, used, found, result);

    used[start] = false;
    Util::subsets(vertexArray, n, k, start + 1, currentLength, used, found, result);
    return;
}

bool Util::completeSubgraph(std::vector<Util::Vertex> subgraph){ // recebe um conjunto de vértices subgraph e reorna true se subgraph é completo
    for(Util::Vertex v : subgraph){
        for(Util::Vertex u : subgraph){
            auto result = std::find(std::begin(v.adj), std::end(v.adj), u.node);
            if(result == std::end(v.adj) && v.node != u.node){
                return false;
            }
        }
    }
    return true;
}

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
