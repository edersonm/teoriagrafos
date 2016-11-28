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
    this->xmen = 0.05;
    this->xover = 0.8;
    if(clength<25){
        this->psize = 50;
        this->maxgen = 50*clength;
    }else if(clength<50 ){
        this->psize= 100;
        this->maxgen = 40*clength;
    }else{
        this->maxgen = 2000;
        this->psize= 200;
    }

    this->clength = clength;
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
    srand((int)time(NULL));
    Chromo retorno;

    std::vector<bool> bits(length,false);

    for (int i=0; i<length; i++) {
        float random = ((float)rand()/(float)(RAND_MAX));
        if (random > 0.5f)
            bits[i] = true;
        else
            bits[i] = false;
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
    float grau = grauAv(bits);
    //cout<<"grau:"<<grau<<"\n";
    //cout<< "tamanho:"<<clength-1 << "elementos"<< temp;
    if(temp <2){
        return 0.0f;
    } else{
        if(isClique(bits)){
            return (float)temp;
        }else{
            if(grau>=1){
                return (1.0f/grau);
            }else{
                return (1.0f*grau);
            }
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

}

void GA::mutate(std::vector<bool>& bits) {
    srand((int)time(NULL));
	//Get a random member from chromossome and mutate based on the adj list:
		float random = ((float)rand()/(float)(RAND_MAX));    	
		if (random < xmen) {    
			
			int i = (int) clength*random;
	    	//Get a random member from the adj list and mutate its position on the chromossome	
			auto it = find (bits.begin()+i, bits.end(), true);		
			int num = (int)(graph[it-bits.begin()].adj.size())*random;
			if(it != bits.end()){
				auto it2 = std::next(graph[it-bits.begin()].adj.begin(), num);
				if (bits[*it2]){
					bits[it-bits.begin()] = false;
				}else{
					bits[*it2]=true;
				}
			} 			
    	}
}

void GA::mutate2(std::vector<bool>& bits) {
    srand((int)time(NULL));
    //Get a random member from chromossome and mutate based on the adj list:
    float random = ((float)rand()/(float)(RAND_MAX));
    if (random < xmen) {
        int i = (int) clength*random;
        //Get a random member from the adj list and mutate its position on the chromossome
        std::list <int>::iterator ite = graph[i].adj.begin();
        std::list <int>::iterator comeco = graph[i].adj.begin();
        for(int a =0;a<clength;a++){
            if(ite != graph[i].adj.end()){
                if(a==i || a == (*ite)){
                    bits[a]=true;
                }else{
                    bits[a]=false;
                }
            } else{
                bits[a]=false;
            }
            ++ite;
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


void GA::crossover(std::vector<bool>& offspring1, std::vector<bool>& offspring2) {
    srand((int)time(NULL));
	
    float random = ((float)rand()/(float)(RAND_MAX));
    if (random < xover) {
        //create a random crossover point
        int crossover = (int) (random * clength);
        float random2 = ((float) rand() / (float) (RAND_MAX));
        std::vector<bool>::iterator it ;
        if (random2 < 0.5f) {
            it = find(offspring1.begin() + crossover, offspring1.end(), true);
        }else {
            it = find(offspring2.begin() + crossover, offspring2.end(), true);
        }
        if (it != offspring1.end() && it != offspring2.end() ) {
            if (random2 < 0.5f) {
                std::list<int>::iterator el =graph[it - offspring1.begin()].adj.begin();
                for (int i=0;i<clength;i++) {
                    if(i== *el || i == it-offspring1.begin()){
                        if(i!= *el && it!=offspring1.end()){
                            it++;
                        }
                        offspring1[i] = true;
                        offspring2[i] = true;

                    }else{
                        offspring1[i]=false;
                        offspring2[i] = false;
                    }
                }
            }else{
                std::list<int>::iterator el =graph[it - offspring2.begin()].adj.begin();
                for (int i=0;i<clength;i++) {
                    if(i== *el|| i == it-offspring2.begin()){
                        if(i!= *el && it!=offspring1.end()){
                            it++;
                        }
                        offspring1[i] = true;
                        offspring2[i] = true;
                    }else{
                        offspring1[i]=false;
                        offspring2[i] = false;
                    }

                }
            }
        }
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
    float s = 0.0f;
    int t = 0;
    for (int p=0; p<getPsize(); p++) {
        if(Population[p].fitness>s){
            s = Population[p].fitness;
            t = p;
        }
    }
    return Population[t].bits;
}


int GA::run() {
//    cout << "Iniciando algoritmo genético com:população:" <<psize << ", iterações:"<< maxgen << ", cromossomo de tamanho:"<< clength<<"\n\n";
    int retorno = 0;
    float sol = 0.0f;
    float tempsol = sol;
    float tempfit = 0.0f;
    srand((int)time(NULL));
    int genmin=0;
    int nochange = 0;
    int nochange2 = 0;
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
            if(pop[i].fitness >= 2.0f){
                sfound = true;
                if(pop[i].fitness == clength){
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
//        cout<<"geração:"<< genmin << " FitnessTotal: "<< tfit <<"\n";
        //Create new pop
        Chromo *temp = new Chromo[psize];
        int cPop = 0;
        //Elitism

        std::vector<bool> elit =elitism(pop);
		//cout<<"Melhor:"<< assignFitness(elit)<<"\n";
		

        temp[cPop] = Chromo(elit, 0.0f);
        while (cPop < psize) {
            //Select parents
            std::vector<bool> offspring1 = roulette(tfit, pop);
            std::vector<bool> offspring2 = roulette(tfit, pop);
            //printChromo(offspring1);
            //add crossover
            crossover(offspring1, offspring2);
            //printChromo(offspring1);
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
            mutate2(offspring1);
            //printChromo(offspring1);
            mutate2(offspring2);

            //add offspring to new population
            temp[cPop++] = Chromo(offspring1, 0.0f);
            if(cPop<psize){
                temp[cPop++] = Chromo(offspring2, 0.0f);
            }


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
            }else{
                if(tempfit ==0.0f){
                    tempfit = tfit;
                }else{
                    if(tempfit == tfit ){
                        if(nochange2++ == (2*tenpercent)){
                            //kill half of the people
                            for (int i=(psize/2); i<psize; i++) {
                                pop[i] = getRandomChromo(clength);
                            }
                            nochange2=0;
                        }
                    }
                }
            }
        }
    }
    return retorno;
}
