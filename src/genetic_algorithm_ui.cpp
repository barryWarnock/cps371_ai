#include "../include/genetic_algorithm_ui.h"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include "../include/genetic_algorithm.h"
#include "cmath"
using namespace std;

void xor_experiment();
void cube_experiment();

void genetic_algorithm_ui_main() {
    int in;
    do {
        cout << "[0] exit" << endl
             << "[1] xor experiment" << endl
             << "[2] rubiks cube experiment" << endl;
        cin >> in;

        switch (in) {
            case 1:
                xor_experiment();
                break;
            case 2:
                cube_experiment();
                break;
            default:
                cout << "not a valid choice" << endl;
                break;
        }
    } while (in != 0);
}


void general_experiment(function<double(Neural_Net_Genome*)> fitness_callback, vector<int> topology,
                        int populationMin, int populationMax, int populationInc,
                        int generationsMin, int generationsMax, int generationsInc) {
    cout << "name of file to save experiment data in: ";
    string filename;
    cin >> filename;

    ofstream file;
    file.open(filename, ios::out);
    if (!file.is_open()) {
        cout << "Failed to open " << filename << endl;
    } else {

        vector<pair<tuple<int, int, int, int, int>, vector<tuple<double, double, double> > > > results;

#pragma omp parallel for
        for (int generations = generationsMin; generations <= generationsMax; generations += generationsInc) {
            for (int popSize = populationMin; popSize <= populationMax; popSize += populationInc) {
                for (int elite = 10; elite <= 100; elite += 10) {
                    for (int mutation = 0; mutation <= 100 - elite; mutation += 10) {
                        int crossover = 100 - (mutation + elite);
                        auto result = run_genetic_algorithm(popSize, generations, elite, mutation, crossover,
                                                            fitness_callback,
                                                            topology);
#pragma omp critical (PRINT_GA_RESULTS)
                        {
                            cout << "(g,p,e,m,c): " << "(" << generations << ","
                                 << popSize << ","
                                 << elite << ","
                                 << mutation << ","
                                 << crossover << ")" << endl;
                            results.push_back(make_pair(make_tuple(generations, popSize, elite, mutation, crossover),result));
                        }
                    }
                }
            }
        }

        genetic_algorithm_cleanup();

        sort(results.begin(), results.end(), [](pair<tuple<int, int, int, int, int>, vector<tuple<double, double, double> > > a,
                                              pair<tuple<int, int, int, int, int>, vector<tuple<double, double, double> > > b){
            return get<0>(a.second.at(a.second.size()-1)) > get<0>(b.second.at(b.second.size()-1));
        });

        file << "generations,population,elite%,mutation%,crossover%,gen#,best,average,worst" << endl;
        for (auto generations : results) {
            for (int generation = 0; generation < generations.second.size(); generation++) {
                file << get<0>(generations.first) << "," << get<1>(generations.first) << "," << get<2>(generations.first) << "," << get<3>(generations.first) << "," << get<4>(generations.first)
                     << "," << generation
                     << "," << get<0>(generations.second.at(generation)) << "," << get<1>(generations.second.at(generation)) << "," << get<2>(generations.second.at(generation))
                     << endl ;
            }
            file << endl;
        }

        file.close();
    }
}

void xor_experiment() {
    vector<int> topology = {2,10,1};
    auto xor_fitness = [](Neural_Net_Genome* genome) {
        Neural_Net net = genome->get_as_net();

        double totalError = 0;
        totalError += abs(-1-net.feed_forward({1, 1}).at(0));
        totalError += abs(1-net.feed_forward({1, -1}).at(0));
        totalError += abs(1-net.feed_forward({-1, 1}).at(0));
        totalError += abs(-1-net.feed_forward({-1, -1}).at(0));

        //max error - actual error
        return 8.0 - totalError;
    };

    general_experiment(xor_fitness, topology,
                       500, 5000, 500,
                       1000, 10000, 1000);
}


void cube_experiment() {

}