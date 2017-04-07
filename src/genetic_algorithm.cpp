#include <iostream>

#include <cmath>
#include <assert.h>
#include <map>
#include <algorithm>
#include <list>
#include <random>
#include "../include/genetic_algorithm.h"
using namespace std;

vector<Neural_Net_Genome*> select_elites(list<pair<double, Neural_Net_Genome*>>& population, int numElites, function<double(Neural_Net_Genome *)> fitness_callback) {
    vector<Neural_Net_Genome*> elites;
    list<pair<double, list<pair<double, Neural_Net_Genome*> >::iterator > > accumulated;
    random_device rnd;

    for (int i = 0; i < numElites; i++) {
        //normalize fitnesses
        double fitnessSum = 0;
        for (pair<double,Neural_Net_Genome*> genome : population) {
            fitnessSum += genome.first;
        }

        double accumulatedFitness = 0;
        for (list<pair<double,Neural_Net_Genome*> >::iterator genome = population.begin(); genome != population.end(); genome++) {
            genome->first /= fitnessSum;
            accumulatedFitness += genome->first;
            accumulated.push_back(make_pair(accumulatedFitness, genome));
        }

        //pick a random elite
        Neural_Net_Genome* elite = nullptr;
        double r = ((rnd()%accumulated.size())+1)/accumulated.size();
        for (auto genome : accumulated) {
            if (genome.first >= r) {
                elite = genome.second->second;
                population.erase(genome.second);
                break;
            }
        }
        if (!elite) {
            elite = population.back().second;
            population.erase(accumulated.back().second);
        }
        elites.push_back(elite);

        accumulated.clear();
    }

    return elites;
}

vector<std::tuple<double, double, double>>
run_genetic_algorithm(int population, int generations, unsigned int elite, unsigned int mutation, unsigned int crossover,
                      function<double(Neural_Net_Genome *)> fitness_callback, vector<int> topology) {
    if (elite + mutation + crossover != 100) {
        throw domain_error("elite/mutation/crossover percentages must sum up to 100%");
    }
    int numElite = round(population * (elite/100.0));
    int numMutated = round(population * (mutation/100.0));
    int numCrossover = round(population * (crossover/100.0));
    while(numElite+numMutated+numCrossover<population) {
        numElite++;
    }

    assert(numElite+numMutated+numCrossover == population);

    vector<Neural_Net_Genome*>* currentPopulation = new vector<Neural_Net_Genome*>(population);
    for (int i = 0; i < population; i++) {
        currentPopulation->at(i) = Neural_Net_Genome::get_NNG(topology);
    }

    random_device rnd;
    vector<tuple<double, double, double>> results = vector<tuple<double, double, double>>(generations);

    list<pair<double, Neural_Net_Genome*> > orderedPop;//(fitness, genome)
    vector<Neural_Net_Genome*>* nextPopulation = new vector<Neural_Net_Genome*>();
    for (int generation = 0; generation < generations; generation++) {
        //calculate fitnesses
        orderedPop.clear();
        for (auto nng : *currentPopulation) {
            orderedPop.push_back(make_pair(fitness_callback(nng), nng));
        }
        orderedPop.sort([]( const pair<double,Neural_Net_Genome*> &a, const pair<double,Neural_Net_Genome*> &b ) {
            return a.first > b.first; });

        //log current generation best/average/worst
        double totFitness = 0;
        for (auto genome : orderedPop) {
            totFitness += genome.first;
        }
        results.at(generation) = make_tuple(orderedPop.front().first, totFitness/population, orderedPop.back().first);

        //create next generation
        vector<Neural_Net_Genome*> elites = select_elites(orderedPop, numElite, fitness_callback);
        nextPopulation->insert(nextPopulation->end(), elites.begin(), elites.end());
        for (int i = 0; i < numMutated; i++) {
            int a = rnd()%elites.size();
            nextPopulation->push_back(elites.at(a)->mutate());
        }
        for (int i = 0; i < numCrossover; i++) {
            int a = rnd()%elites.size();
            int b = rnd()%elites.size();
            while(elites.size() > 1 && b == a) {
                b = rnd()%elites.size();
            }
            nextPopulation->push_back(elites.at(a)->crossover(elites.at(b)));
        }

        for (auto genome : orderedPop) {
            Neural_Net_Genome::free_NNG(genome.second);
        }
        currentPopulation->clear();
        vector<Neural_Net_Genome*>* tmpPopulation = currentPopulation;
        currentPopulation = nextPopulation;
        nextPopulation = tmpPopulation;
    }
    for (int i = 0; i < currentPopulation->size(); i++) {
        Neural_Net_Genome::free_NNG(currentPopulation->at(i));
    }
    delete currentPopulation;
    delete nextPopulation;
    return results;
}

void genetic_algorithm_cleanup() {
    Neural_Net_Genome::cleanup();
}