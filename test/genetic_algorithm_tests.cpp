#include "tests.h"
#include <iostream>
#include "../include/genetic_algorithm.h"
#include "cmath"

using namespace std;

bool test_train_xor() {
    cout << "training neural nets to solve xor using a genetic algorithm" << endl;
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

    auto results = run_genetic_algorithm(100, 100, 35, 30, 35, xor_fitness, topology);
    genetic_algorithm_cleanup();

    bool success = get<0>(results.at(0)) < get<0>(results.at(results.size()-1));

    if (success) {
        cout << "successfully trained neural net using GA" << endl;
    } else {
        cout << "genetic algorithm did not reduce neural network error" << endl;
    }

    return success;
}

int genetic_algorithm_tests() {
    cout << "Beginning genetic algorithm tests:" << endl;

    int failed = 0;
    failed += !test_train_xor();

    cout << "genetic algorithm tests complete" << endl << endl;
    return failed;
}