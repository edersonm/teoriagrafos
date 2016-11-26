#include <stdlib.h>
#include<fstream>
#include<sstream>
#include<list>
#include<iostream>
#include<string>
#include <vector>
#include "Util.h"
#include "Exato.h"
#include <cstring>
#include <algorithm>
#include <array>
#include "json.hpp"
#include "GA.h"
#include <chrono>

using namespace std;
using json = nlohmann::json;


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
    for(int i = 0; i < n; ++i){
        std::cout << "Node " << v[i].node << " degree " << v[i].degree << "  ->  ";
        for(int r : v[i].adj){
           std::cout << v[r].node << " ";
        }
        std::cout << std::endl;
    }
    std::cout << endl << endl;
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

bool Util::GACompleteSubgraph(std::vector<bool> bits, Util::Vertex* v){

    std::vector<Util::Vertex> sub;

    for(int i = 0; i < bits.size(); ++i){
        if(bits[i]) sub.push_back((Util::Vertex) *(v + i));
    }

    return Util::completeSubgraph(sub);
}

Util::Vertex* Util::readNXGraph(std::string fileName){
    Util::Vertex* VertexArray = NULL;
    std::ifstream file(fileName.c_str(), ios::in);
    if(!file.is_open()){
       std::cout << "ops não foi possível abir o arquivo\n";
        return NULL;
    }
    int n;
    if (file.is_open()){
        std::string line;
        if (std::getline(file, line)){
            std::strtok(&line[0], ":");
            n = stoi(std::strtok(NULL, ":"));
            VertexArray = new Vertex [n];
        }else {return NULL;}
        std::getline(file, line);std::getline(file, line);
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
    for(int i = 0; i < n; ++i){
        VertexArray[i].node = i;
        VertexArray[i].degree = VertexArray[i].adj.size();
    }

    return VertexArray;
}

std::array<double, 3> Util::readGraphInfo(std::string fileName) {
    std::array<double, 3> info;
    std::ifstream file(fileName.c_str(), ios::in);
    if (file.is_open()){
        std::string line;
        for(int i = 0; i < 3; ++i){
            if (std::getline(file, line)) {
                std::strtok(&line[0], ":");
                info[i] = stod(std::strtok(NULL, ":"));
            }
        }
        }else {
            std::cout << "ops não foi possível abir o arquivo\n";
        }
    return info;
}


void Util::b_exato(int q, int w, std::string prefix, std::string posfix){
    for(int i = q; i <= w; i++){
        std::string fileName = prefix + to_string(i) + posfix;
        std::array<double,3> info = Util::readGraphInfo(fileName);
        Util::Vertex* vertexArray =  Util::readNXGraph(fileName);

        auto start = std::chrono::steady_clock::now();

        auto result = Exato::exato(vertexArray, info[0]);



        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;

        json benchmarkResults = {
                {"algorithm", "exato"},
                {"n_nodes", info[0]},
                {"n_edges", info[1]},
                {"density", info[2]},
                {"clique_size", result.size()},
                {"run_time", diff.count()}
        };

        ofstream jsonFile;
        jsonFile.open("benchmark_jsons/benchmark_exato_" + to_string(i) + ".json");
        if(jsonFile.is_open()){
            jsonFile << benchmarkResults;
            jsonFile.close();
        }else{
            std::cout << "ops nao foi possível abrir o json\n";
        }

    }
}

void Util::b_ga(int q, int w, std::string prefix, std::string posfix){
    for(int i = q; i <= w; i++){
        std::string fileName = prefix + to_string(i) + posfix;
        std::array<double,3> info = Util::readGraphInfo(fileName);
        Util::Vertex* vertexArray =  Util::readNXGraph(fileName);

        auto start = std::chrono::steady_clock::now();

        GA ga(info[0], vertexArray);
        int result = ga.run();


        auto end = std::chrono::steady_clock::now();
        auto diff = end - start;

        json benchmarkResults = {
                {"algorithm", "ga"},
                {"n_nodes", info[0]},
                {"n_edges", info[1]},
                {"density", info[2]},
                {"clique_size", result},
                {"run_time", diff.count()}
        };

        ofstream jsonFile;
        jsonFile.open("benchmark_jsons/benchmark_ga_" + to_string(i) + ".json");
        if(jsonFile.is_open()){
            jsonFile << benchmarkResults;
            jsonFile.close();
        }else{
            std::cout << "ops nao foi possível abrir o json\n";
        }

    }
}

void Util::b_debug(int q, int w, std::string prefix, std::string posfix){
    for(int i = q; i <= w; i++){
        std::string fileName = prefix + to_string(i) + posfix;
        std::array<double,3> info = Util::readGraphInfo(fileName);
        Util::Vertex* vertexArray =  Util::readNXGraph(fileName);


        GA ga(info[0], vertexArray);
        int GAresult = ga.run();
        auto EXresult = Exato::exato(vertexArray, info[0]);

        std::cout << "\n\n---   Compare   ---  " << fileName << " n_nodes: " << info[0] << " n_edges: " << info[1] << " density: " << info[2];
        std::cout << "\nexato: " << EXresult.size() << "   GA: " << GAresult << "\n";

    }
}



void Util::b_compare(int q, int w, std::string prefix, std::string posfix) {
    for(int p = q; p <= w; p++){
        std::cout << "benchmark arquivo n: " << p << std::endl;
        Util::b_exato(p, p, prefix, posfix);
        Util::b_ga(p, p, prefix, posfix);
    }
}
