#include "../include/genetic_algorithm_ui.h"
#include <iostream>
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


void xor_experiment() {
    vector<int> topology = {2,3,1};
    auto xor_fitness = [](Neural_Net_Genome* genome) {
        Neural_Net net = genome->get_as_net();
        double totalError = 0;
        totalError += abs(-1-net.feed_forward({1, 1}).at(0));
        totalError += abs(1-net.feed_forward({1, 0}).at(0));
        totalError += abs(1-net.feed_forward({0, 1}).at(0));
        totalError += abs(-1-net.feed_forward({0, 0}).at(0));

        //max error - actual error
        return 8.0 - totalError;
    };

    vector<vector<tuple<double, double, double>>> results;

/*#pragma omp parallel for
    for (int generations = 1000; generations <= 10000; generations += 1000) {
        for (int popSize = 500; popSize <= 5000; popSize += 500) {
            for (int elite = 10; elite <= 100; elite += 10) {
                for (int mutation = 0; mutation <= 100 - elite; mutation += 10) {
                    int crossover = 100 - (mutation+elite);
                    auto result = run_genetic_algorithm(popSize, generations, elite, mutation, crossover, xor_fitness,
                                                        topology);
#pragma omp critical (PRINT_GA_RESULTS)
                    {
                        cout << "(g,p,e,m,c): " << "(" << generations << ","
                             << popSize << ","
                             << elite << ","
                             << mutation << ","
                             << crossover << ")" << endl;
                        results.push_back(result);
                    }
                }
            }
        }
    }*/
#pragma omp parallel for
    for (int generations = 10; generations <= 100; generations += 10) {
        for (int popSize = 500; popSize <= 1000; popSize += 500) {
            for (int elite = 10; elite <= 100; elite += 10) {
                for (int mutation = 0; mutation <= 100 - elite; mutation += 10) {
                    int crossover = 100 - (mutation+elite);
                    auto result = run_genetic_algorithm(popSize, generations, elite, mutation, crossover, xor_fitness,
                                                        topology);
#pragma omp critical
                    {
                        cout << "(g,p,e,m,c): " << "(" << generations << ","
                             << popSize << ","
                             << elite << ","
                             << mutation << ","
                             << crossover << ")" << endl;
                        results.push_back(result);
                    }
                }
            }
        }
    }
    genetic_algorithm_cleanup();

    for (auto result : results) {
        cout << get<0>(result[0]) << "," << get<1>(result[0]) << "," << get<2>(result[0]) << "," << endl;
    }
    abort();
}


void cube_experiment() {

}