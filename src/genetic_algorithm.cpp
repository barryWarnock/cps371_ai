#include <cmath>
#include <assert.h>
#include <map>
#include <algorithm>
#include <list>
#include "../include/genetic_algorithm.h"
using namespace std;

vector<Neural_Net_Genome*> select_elites(vector<Neural_Net_Genome*>& population, int numElites, function<double(Neural_Net_Genome *)> fitness_callback) {
    list<pair<double, Neural_Net_Genome*>> orderedPop(population.size());
    for (auto nng : population) {
        orderedPop.push_back(make_pair(fitness_callback(nng), nng));
    }
    orderedPop.sort([]( const pair<double,Neural_Net_Genome*> &a, const pair<double,Neural_Net_Genome*> &b ) { return a.first > b.first; });
    vector<Neural_Net_Genome*> elites;

    for (int i = 0; i < numElites; i++) {
        //pick elites
    }
}

vector<std::tuple<double, double, double>>
run_genetic_algorithm(int population, int generations, unsigned int elite, unsigned int mutation, unsigned int crossover,
                      function<double(Neural_Net_Genome *)> fitness_callback, vector<int> topology) {
    if (elite + mutation + crossover != 100) {
        throw exception();
    }
    int numElite = round(population * (elite/100.0));
    int numMutated = round(population * (mutation/100.0));
    int numCrossover = round(population * (crossover/100.0));
    assert(numElite+numMutated+numCrossover);

    vector<Neural_Net_Genome*>* currentPopulation = new vector<Neural_Net_Genome*>(population);
    for (int i = 0; i < population; i++) {
        currentPopulation->at(i) = Neural_Net_Genome::get_NNG(topology);
    }

    vector<tuple<double, double, double>> results = vector<tuple<double, double, double>>(generations);

    vector<Neural_Net_Genome*>* nextPopulation = new vector<Neural_Net_Genome*>(population);
    for (int generation = 0; generation < generations; generation++) {
        for (int i = 0; i < numElite; i++) {

        }
        for (int i = 0; i < numMutated; i++) {

        }
        for (int i = 0; i < numCrossover; i++) {

        }
    }
    return results;
}
