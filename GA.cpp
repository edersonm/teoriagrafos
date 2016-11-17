//
// Created by morps on 11/10/16.
//

#include <string>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include "GA.h"
#include <math.h>
#include <algorithm>
using namespace std;
//
//parameters

//class

//Functions
GA::GA(int glength, Util::Vertex* array) {
    this->glength = glength;
    this->graph = array;
    this->maxgen = maxgen;
    this->xmen = 0.015;
    this->xover = 0.8;
    this->psize = 50;
    this->clength = this->glength * this->psize;
    this->maxgen = 1000;
}

int GA::getClength() {
    return this->clength;
}
int GA::getGlength() {
    return this->glength;
}
int GA::getMaxgen() {
    return this->maxgen;
}
int GA::getPsize() {
    return this->psize;
}
float GA::getXmen() {
    return this->xmen;
}
float GA::getXover() {
    return this->xover;
}
void GA::setClength(int value) {
    this->clength=value;
}
void GA::setGlength(int value) {
    this->glength=value;
}
void GA::setMaxgen(int value) {
    this->maxgen = value;
}
void GA::setPsize(int value) {
    this->psize = value;
}
void GA::setXmen(float value) {
    this->xmen = value;
}
void GA::setXover(float value) {
    this->xover = value;
}
//End Functions


std::vector<bool>  GA::GetRandomBits(int length) {
    std::vector<bool> bits(length,false);
    float random = ((float)rand()/(RAND_MAX+1));
    for (int i=0; i<length; i++) {
        if (random > 0.5f)
            bits[i] = true;
        else
            bits[i] = false;
    }
    return bits;
}

Util::Vertex convertSubGraph(std::vector<bool> bits){
    Util::Vertex retorno;

    return retorno;
}

float GA::AssignFitness(std::vector<bool> bits) {

    float retorno = 0.0f;
    bool found = false;
    std::vector<Util::Vertex> teste;
    if(isClique(bits)){
        int temp = bitSize(bits);
        if(temp == glength-1){
            return 2;
        }else{
            retorno = 1/((glength-1)-bitSize(bits));
        }

    }else{
        retorno=-1;
    }
    return retorno;
}
bool GA::isClique(std::vector<bool> bits) {
    bool retorno = true;
    std::vector <int> test;
    for(int i =0;i<bits.size();i++){
        if(bits[i]){
            test.push_back(i+1);
        }
    }
    while(test.size() > 1){
        int t = test.back();
        test.pop_back();
        for(int i :test){
            if(find(std::begin(graph[i].adj),std::end(graph[i].adj),t) == graph[i].adj.end()){
                return false;
            }
        }
    }
    return retorno;

}

void GA::Mutate(std::vector<bool> bits) {
    float random = ((float)rand()/(RAND_MAX+1));
    for (int i=0; i<bits.size(); i++) {
        if (random < xmen) {
            if (bits[i] == true){
                bits[i] = false;
            }else{
                bits.at(i) = true;
            }
        }
    }
}

int GA::bitSize(std::vector<bool> bits){
    int retorno = 0;

    for(bool a : bits){
        if(a){
            retorno++;
        }
    }
    return retorno;

}


void GA::Crossover(std::vector<bool> offspring1, std::vector<bool> offspring2) {
    float random = ((float)rand()/(RAND_MAX+1));
    if (random < xover) {
        //create a random crossover point
        int crossover = (int) (random * clength);
        std::vector<bool> f1 (maxgen,false);
        std::vector<bool> f2 (maxgen,false);
        for(int i = 0;i<(glength*psize);i++){
            if(i<crossover){
                f1[i]=offspring1[i];
                f2[i]=offspring2[i];
            }else{
                f1[i]=offspring2[i];
                f2[i]=offspring1[i];
            }
        }
        offspring1 = f1;
        offspring2 = f2;
    }
}

std::vector<bool> GA::Roulette(int total_fitness, Chromo* Population) {
    float random = ((float)rand()/(RAND_MAX+1));
    float total = (float)(random * total_fitness);

    float fitness_temp = 0.0f;
    for (int i=0; i<psize; i++) {
        fitness_temp += Population[i].fitness;
        //if the fitness so far > random number return the chromo at this point
        if (fitness_temp >= total)
            return Population[i].bits;
    }

    return  std::vector<bool>  (1,false);;
}

void GA::PrintChromo(std::vector<bool> bits) {
    for(int i = 0;i<bits.size();i++){
        if(bits[i]){
            cout << (i+1)<<",";
        }
    }
    cout<<"\n";

}

int GA::run() {
    float retorno = 0.0f;
    srand((int)time(NULL));
    int genmin=0;
    int i = 0;
    Chromo pop[psize];
    //Create random population
    for (int i=0; i<psize; i++) {
        pop[i].bits      = GetRandomBits(clength);
        pop[i].fitness = 0.0f;
    }
    //flag for solution
    bool sfound = false;
    while(!sfound){
        float tfit = 0.0f; //para roleta
        //Verify each chromossome in the population and assign a fitness
        for (i=0; i<psize; i++) {
            pop[i].fitness = AssignFitness(pop[i].bits);
            tfit += pop[i].fitness;
            if(pop[i].fitness != -1){
                sfound = true;
                std::cout << "Solução encontrada em:" << genmin << " gerações " << "\n\n";
                PrintChromo(pop[i].bits);
                if(pop[i].fitness == 2){
                    return glength-1;
                }

            }
        }
        //Create new pop
        Chromo temp[psize];
        int cPop = 0;

        while (cPop < psize) {
            //Select parents
            std::vector<bool> offspring1 = Roulette(tfit, pop);
            std::vector<bool> offspring2 = Roulette(tfit, pop);

            //add crossover
            Crossover(offspring1, offspring2);
            //now mutate
            Mutate(offspring1);
            Mutate(offspring2);

            //add offspring to new population
            temp[cPop++] = Chromo(offspring1, 0.0f);
            temp[cPop++] = Chromo(offspring2, 0.0f);

        }
        //copy temp population into main population array
        for (i=0; i<psize; i++)
        {
            pop[i] = temp[i];
        }

        if(++genmin>maxgen){
            cout << "Sem solução encontrada no número máximo de gerações: " << maxgen <<"!\n\n";
            sfound = true;
        }
    }
    return retorno;
}
