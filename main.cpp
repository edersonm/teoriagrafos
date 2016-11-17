//
// Created by Lucas Rangel on 20/10/16.
//
#include <iostream>
#include <stdlib.h>
#include "Util.h"
#include "ExactAlgorithm.h"
#include "GA.h"
#include <algorithm>
#include <vector>

int main(){
   std::string files[] = {"G1.in", "G2.in", "G3.in", "G4.in", "k5.in", "G1_.in", "r1.in", "r2.in", "r3.in"};
   std::string testFile = files[0]; // 0 e 5
   int n = Util::getn(testFile);
   std::cout << "n :" << n << std::endl;


   Util::Vertex* vertexArray =  Util::readGraph(testFile);
   Util::printVertexArray(vertexArray, n);
   std::vector<Util::Vertex> result = Util::exato(vertexArray, n); //Executando algoritmo exato.

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

