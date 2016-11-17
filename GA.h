//
// Created by morps on 11/16/16.
//
#include<list>
#include<vector>
#include "Util.h"
#ifndef PROJETOTG_GA_H
#define PROJETOTG_GA_H
class GA{
public:
    struct Chromo{
        std::vector<bool> bits;
        float     fitness;

        Chromo(): bits( {false}), fitness(0.0f){};
        Chromo(std::vector<bool> bts, float ftns): bits(bts), fitness(ftns){}
    };

    void setPsize(int value);
    void setMaxgen(int value);
    void setXover(float value);
    void setXmen(float value);
    void setGlength(int value);
    void setClength(int value);
    int getPsize();
    int getMaxgen();
    float getXover();
    float getXmen();
    int getGlength();
    int getClength();
    GA(int glength, Util::Vertex* array);
    std::vector<bool> GetRandomBits(int length);
    float   AssignFitness(std::vector<bool> bits);
    std::vector<bool>  Roulette(int total_fitness, Chromo* Population);
    void    Mutate(std::vector<bool> bits);
    void    Crossover(std::vector<bool> offspring1, std::vector<bool> offspring2);
    void PrintChromo(std::vector<bool> bits);
    bool isClique(std::vector<bool> bits);
    int bitSize(std::vector<bool> bits);
    int run();

private:
    int psize;
    int maxgen;
    float xover;
    float xmen;
    int glength;
    int clength;
    Util::Vertex* graph;
};
//class

#endif //PROJETOTG_GA_H
