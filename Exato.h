#ifndef PROJETOTG_EXATO_H
#define PROJETOTG_EXATO_H


#include <vector>
#include "Util.h"

class Exato {

    static void subsets(Util::Vertex *vertexArray, int n, int k, int start, int currentLength, bool *used, bool *found,
                 std::vector<Util::Vertex> *result);

public:
    static std::vector<Util::Vertex> exato(Util::Vertex *vertexArray, int n);

    template <typename Iterator>
    static bool next_combination(const Iterator first, Iterator k, const Iterator last);

    static std::vector<Util::Vertex> findClique(Util::Vertex *vertexArray, int l, int k);
};


#endif //PROJETOTG_EXATO_H
