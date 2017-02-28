#include <iostream>
#include <random>
#include <memory>
#include <cstring>
#include "../include/stochastic_back_propogation.h"

using namespace std;
/*
begin initialize network topology (# hidden units), w, criterion θ, η, m ← 0
do m ← m + 1
x m ← randomly chosen pattern
w ij ← w ij + ηδ j x i ; w jk ← w jk + ηδ k y j
until ∇J(w) < θ
return w
end
 */
double calculate_error(vector<double> expected, vector<double> actual);
double calculate_neural_net_error(SBP_Impl* nn, vector<pair<vector<double>, vector<double>>> trainingTuples);

void neural_net_sbp(vector<pair<vector<double>, vector<double>>> trainingTuples, SBP_Impl* nn,
                    int trainingIterations, int epochs) {
    unique_ptr<SBP_Impl> bestNN(nn->clone());

    int len = bestNN->get_layer_sizes().size();

    for (int epoch = 0; epoch < epochs; epoch++) {
        unique_ptr<SBP_Impl> currentNN(bestNN->clone());

        currentNN->init(nn->get_layer_sizes());
        for (int i = 0; i < trainingIterations; i++) {
            pair<vector<double>, vector<double>> trainingTuple = trainingTuples[random_device{}() % trainingTuples.size()];
            vector<double> in = trainingTuple.first;
            vector<double> expectedOut = trainingTuple.second;

            vector<double> actualOut = nn->feed_forward(in);

            
        }
        if (calculate_neural_net_error(bestNN.get(), trainingTuples) > calculate_neural_net_error(currentNN.get(), trainingTuples)) {
            bestNN.reset(currentNN.release());
        }
    }

    nn->set_weights(bestNN->get_weights());
}

double calculate_error(vector<double> expected, vector<double> actual) {
    double error = 0;
    for (int i = 0; i < expected.size(); i++) {
        error += pow(expected[i]-actual[i], 2);
    }
    return sqrt(error);
}

double calculate_neural_net_error(SBP_Impl* nn, vector<pair<vector<double>, vector<double>>> trainingTuples) {
    double totalError = 0;
    for (auto tuple : trainingTuples) {
        totalError += calculate_error(nn->feed_forward(tuple.first), tuple.second);
    }
    return totalError;
}