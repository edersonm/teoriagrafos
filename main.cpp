#include <iostream>
#include <stdlib.h>
#include "Util.h"
#include "ExactAlgorithm.h"
#include "GA.h"
#include "Exato.h"
#include <algorithm>
#include <vector>
#include <array>

int main(){
    std::string files[] = {"G1.in", "graph_5.in","G2.in", "G3.in", "G4.in", "k5.in", "G1_.in", "r1.in", "r2.in", "r3.in"};
    std::string testFile = "graphs/" + files[1];

   std::array<double,3> info = Util::readGraphInfo(testFile);
    int n = info[0];
   Util::Vertex* vertexArray =  Util::readNXGraph(testFile);
   Util::printVertexArray(vertexArray, n);
   std::vector<Util::Vertex> result = Util::exato(vertexArray, n); //Executando algoritmo exato.
    auto r = Exato::exato(vertexArray, n);
    std::cout << r.size() << std::endl;

    Util::b_exato(1, 6, "graphs/graph_", ".in");

   std::cout << "\nclique encontrado: \n";
   for(Util::Vertex u : result)
      std::cout << u.node << ", ";
    std::cout << "" << std::endl;
//   Util::exato(vertexArray, n);
   //Genetic
   GA ga(n,vertexArray);
   int resultado = ga.run();
   if(resultado != 0){
      std::cout<< "Clique máximo encontrado: " << resultado << "\n\n";
   }
}

