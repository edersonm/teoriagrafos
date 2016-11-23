#include <iostream>
#include <stdlib.h>
#include "Util.h"
#include "GA.h"
#include "Exato.h"
#include <algorithm>
#include <vector>
#include <array>

int main(){

    int p = 28, q = 93;
    std::string prefix = "graphs/graph_", posfix  = ".in";

//    Util::b_exato(p, q, prefix, posfix);     //benchmark do exato do arquivo p até o q e salva os arquivos json
//    Util::b_ga(p, q, prefix, posfix);        //o mesmo só que para o genético
//    Util::b_debug(p, q, prefix, posfix);     // roda do arquivo p até o q em ambos e printa o clique encontrado e outras info

    Util::b_compare(p, q, prefix, posfix);    //benchmark de ambos, usar isso pro artigo;




//    std::cout <<"teste tamanho:" <<n<<"\n\n";
//   GA ga(n,vertexArray);
//   int resultado = ga.run();
//
//   if(resultado != 0){
//      std::cout<< "Clique máximo encontrado: " << resultado << "\n\n";
//   }
}

