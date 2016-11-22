//
// Created by morps on 11/10/16.
//

#include <string>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include "GA.h"
#include "Util.h"
#include <math.h>
#include <algorithm>
using namespace std;
//
//parameters

//class

//Functions
GA::GA(int clength, Util::Vertex* array) {
    this->glength = 1;
    this->graph = array;
    this->maxgen = maxgen;
    this->xmen = 0.015;
    this->xover = 0.8;
    this->psize = 50;
    this->clength = clength;
    this->maxgen = 100*clength;
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


GA::Chromo GA::getRandomChromo(int length) {
    Chromo retorno;

    std::vector<bool> bits(length,false);

    for (int i=0; i<length; i++) {
        float random = ((float)rand()/(float)(RAND_MAX));
        if (random > 0.5f)
            bits[i] = true;
        else
            bits[i] = false;
    }
    bool teste= true;
    for(int i =0;i<length;i++){
        if(bits[i]){
            teste = false;
        }
    }
    if(teste){
        printChromo(bits);
    }
    retorno.bits = bits;
    retorno.fitness = 0.0f;
    return retorno;
}

Util::Vertex convertSubGraph(std::vector<bool> bits){
    Util::Vertex retorno;

    return retorno;
}

float GA::assignFitness(std::vector<bool> bits) {

    bool found = false;
    std::vector<Util::Vertex> teste;
    int temp = bitSize(bits);
    int grau = grauAv(bits);
    //cout<<"grau:"<<grau<<"\n";
    //cout<< "tamanho:"<<clength-1 << "elementos"<< temp;
    if(isClique(bits)){
        if(temp == clength){
            return 2.0f;
        }else{
            return (1.0f/((float)(clength)-(float)temp));
        }
    }
    if(temp ==0){
        return 0.0f;
    } else{
        if(grau>1){
            return (float)(1.0f/(((float)(clength)-2.0f))*0.90*(grauAv(bits)-1)/(clength-2));
        }else{
            return (float)(1.0f/(((float)(clength)-2.0f))*0.90*(grauAv(bits))/(clength-2));
        }

    }

}

float GA::grauAv(std::vector<bool> bits){
    float retorno = 0.0f;
    int cont = 0;
    for(int i=0;i<bits.size();i++){
        if(bits[i]){
            retorno+= (float)graph[i].degree;
            cont++;
        }
    }
    retorno = retorno/(float)cont;

    return retorno;
}

bool GA::isClique(std::vector<bool> bits) {

    return Util::GACompleteSubgraph(bits,graph);




//    bool retorno = true;
//    std::vector <int> test;
//    if(bitSize(bits) <= 1){
//        return false;
//    }
//    for(int i =0;i<bits.size();i++){
//        if(bits[i]){
//            test.push_back(i);
//        }
//    }
//    while(test.size() > 1){
//        int t = test.back();
//        test.pop_back();
//        for(int i :test){
//            if(find(std::begin(graph[i].adj),std::end(graph[i].adj),t) == graph[i].adj.end()){
//                return false;
//            }
//        }
//    }
//    return retorno;

}

void GA::mutate(std::vector<bool> bits) {
    srand((int)time(NULL));

    for (int i=0; i<bits.size(); i++) {
        float random = ((float)rand()/(float)(RAND_MAX));
        if (random < xmen) {
            if (bits[i]){
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


void GA::crossover(std::vector<bool> offspring1, std::vector<bool> offspring2) {
    srand((int)time(NULL));
    float random = ((float)rand()/(float)(RAND_MAX));
    if (random < xover) {
        //create a random crossover point
        int crossover = (int) (random * clength);
        std::vector<bool> f1 (maxgen,false);
        std::vector<bool> f2 (maxgen,false);
        for(int i = 0;i<(clength);i++){
            if(i<crossover){
                f1[i]=offspring1[i];
                f2[i]=offspring2[i];
            }else{
                f1[i]=offspring2[i];
                f2[i]=offspring1[i];
            }
        }
        offspring1.swap(f1);
        offspring2.swap(f2);
    }

}

std::vector<bool> GA::roulette(float total_fitness, Chromo* Population) {
    float random = ((float)rand()/(RAND_MAX));

    float total = (float)(random * total_fitness);
    //Matar os negativos, normalizar a partir dos negativos, ou dar sort e matar
    float fitness_temp = 0.0f;
    for (int i=0; i<psize; i++) {
        fitness_temp += Population[i].fitness;
        //if the fitness so far > random number return the chromo at this point
        if (fitness_temp >= total)
            return Population[i].bits;
    }

    return  std::vector<bool>  (clength,false);
}

void GA::printChromo(std::vector<bool> bits) {

    for(int i = 0;i<bits.size();i++){
        if(bits[i]){
            cout << i<<",";
        }
    }
    cout << "\n\n";

}

std::vector<bool> GA::elitism(Chromo* Population) {
    float sol = 0.0f;
    int temp = 0;
    for (int p=0; p<psize; p++) {
        if(Population[p].fitness>sol){
            sol = Population[p].fitness;
            temp = p;
        }
    }
    return Population[temp].bits;
}


int GA::run() {
//    cout << "Iniciando algoritmo genético com:população:" <<psize << ", iterações:"<< maxgen << ", cromossomo de tamanho:"<< clength<<"\n\n";
    int retorno = 0;
    float sol = 0.0f;
    float tempsol = sol;
    srand((int)time(NULL));
    int genmin=0;
    int nochange = 0;
    int tenpercent = ((int)maxgen/10);
    int i = 0;
    Chromo *pop = new Chromo[psize];
    //Create random population
    for (int i=0; i<psize; i++) {
        pop[i] = getRandomChromo(clength);
    }
    //flag for solution
    bool sfound = false;
    while(!sfound || nochange<=tenpercent){

        float tfit = 0.0f; //para roleta
        //Verify each chromossome in the population and assign a fitness
        for (i=0; i<psize; i++) {
            pop[i].fitness = assignFitness(pop[i].bits);
            tfit += pop[i].fitness;
            if(pop[i].fitness >= (1.0f/((float)(clength)-2.0f))){
                sfound = true;
                if(pop[i].fitness == 2){
//                    cout << "Melhor solução encontrada:" <<pop[i].fitness<<" em " << genmin << " gerações " << "\n";
                    return clength;
                }
                if(pop[i].fitness > sol){
//                    cout << "Solução encontrada:" <<pop[i].fitness<<" em " << genmin << " gerações " << "\n";
//                    printChromo(pop[i].bits);
                    sol = pop[i].fitness;
                    retorno = bitSize(pop[i].bits);
                }else{
                    if(nochange>= tenpercent){
//                        cout << "Melhor solução encontrada sem mudanças depois de 10%:" <<pop[i].fitness<<" em " << genmin << " gerações " << "\n";
//                        printChromo(pop[i].bits);
                        return bitSize(pop[i].bits);
                    }
                }
            }
        }
        //cout<<"geração:"<< genmin << " FitnessTotal: "<< tfit <<"\n";
        //Create new pop
        Chromo *temp = new Chromo[psize];
        int cPop = 0;
        //Elitism

        std::vector<bool> elit =elitism(pop) ;
        //temp[cPop++] = Chromo(elit, 0.0f);

        while (cPop < psize) {
            //Select parents
            std::vector<bool> offspring1 = roulette(tfit, pop);
            std::vector<bool> offspring2 = roulette(tfit, pop);
            //printChromo(offspring1);
            //add crossover
            crossover(offspring1, offspring2);

            //Force variability if too similar
            int con = 0;
            float temx = xmen;
            for(int i = 0;i<offspring1.size();i++){
                if(offspring1[i] == offspring2[i] ){
                    con++;
                }
            }

            if(con == clength){
                xmen = 0.5f;
            }

            //now mutate
            mutate(offspring1);
            //printChromo(offspring1);
            mutate(offspring2);

            //add offspring to new population
            temp[cPop++] = Chromo(offspring1, 0.0f);
            temp[cPop++] = Chromo(offspring2, 0.0f);

        }
        //copy temp population into main population array
        for (i=0; i<psize; i++)
        {
            pop[i] = temp[i];
        }
        genmin++;
        if(genmin>maxgen){
//            cout << "Sem solução encontrada no número máximo de gerações: " << maxgen <<"!\n\n";
            sfound = true;
            nochange = tenpercent+1;
            return retorno;
        }
        if(tempsol<sol){
            tempsol = sol;

        }else{
            if(sfound){
                nochange++;
                if(nochange>=tenpercent){
//                    cout<<retorno;
                }
            }
        }
    }
    return retorno;
}
