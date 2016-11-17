#include <iostream>
#include <stdlib.h>
#include "Util.h"
<<<<<<< Updated upstream
#include "ExactAlgorithm.h"
=======
#include "Exato.h"
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
   std::vector<Util::Vertex> result = Util::exato(vertexArray, n); //Executando algoritmo exato.
=======
>>>>>>> Stashed changes

    auto r = Exato::exato(vertexArray, n);
    std::cout << r.size() << std::endl;

    Util::b_exato(1, 6, "graphs/graph_", ".in");

}

