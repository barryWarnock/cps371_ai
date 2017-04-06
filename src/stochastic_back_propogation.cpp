
#include <random>
#include <memory>
#include <cstring>
#include "../include/stochastic_back_propogation.h"

using namespace std;

double tanh_derivative(double value) {
    return 1 - (value * value);
}

double calculate_error(vector<double> expected, vector<double> actual);
double calculate_neural_net_error(SBP_Impl* nn, vector<pair<vector<double>, vector<double>>> trainingTuples);

double neural_net_sbp(NN_Data_Set trainingTuples, SBP_Impl* nn,
                      int trainingIterations, int epochs, double learningRate, double momentum,
                      double weightDecay) {
    unique_ptr<SBP_Impl> bestNN(nn->clone());
    int numLayers = nn->get_layer_sizes().size();


    for (int epoch = 0; epoch < epochs; epoch++) {
        unique_ptr<SBP_Impl> currentNN(bestNN->clone());
        currentNN->init(nn->get_layer_sizes());
        vector<vector<vector<double>>> weightDeltas(0);
        auto weights = currentNN->get_weights();
        weightDeltas = vector<vector<vector<double>>>(weights.size());
        for (int layer = 0; layer < weights.size(); layer++) {
            weightDeltas[layer] = vector<vector<double>>(weights[layer].size());
            for (int node = 0; node < weights[layer].size(); node++) {
                weightDeltas[layer][node] = vector<double>(weights[layer][node].size(), 0);
            }
        }

        for (int i = 0; i < trainingIterations; i++) {
            vector<vector<double>> error(numLayers-1);

            pair<vector<double>, vector<double>> trainingTuple = trainingTuples[random_device{}() % trainingTuples.size()];
            vector<double> in = trainingTuple.first;
            vector<double> expectedOut = trainingTuple.second;

            vector<double> actualOut = currentNN->feed_forward(in);

            //calculate error for output layer
            int outputLayerNumber = numLayers-2;
            error[outputLayerNumber] = vector<double>(actualOut.size());
            for (int j = 0; j < actualOut.size(); j++) {
                error[outputLayerNumber][j] = (expectedOut[j] - actualOut[j]) * tanh_derivative(actualOut[j]);
            }

            //calculate error for hidden layers
            for (int layer = numLayers-2; layer > 0; layer--) {
                int layerLength = currentNN->get_layer_sizes()[layer];
                error[layer-1] = vector<double>(layerLength, 0);
                for (int node = 0; node < layerLength; node++) {
                    for (int nextLayerNode = 0; nextLayerNode < currentNN->get_layer_sizes()[layer+1]; nextLayerNode++) {
                        error[layer-1][node] += (error[layer][nextLayerNode]
                                * currentNN->get_weights()[layer][nextLayerNode][node+1]
                                * tanh_derivative(tanh(currentNN->get_previous_nets()[layer-1][node])))
                                ;
                    }
                }
            }

            for (int layer = 0; layer < weights.size(); layer++) {
                for (int node = 0; node < weights[layer].size(); node++) {
                    for (int weightIndex = 0; weightIndex < weights[layer][node].size(); weightIndex++) {
                        double weight = weights[layer][node][weightIndex];
                        double input = weightIndex ? currentNN->get_previous_nets()[layer][node] : 1;
                        double momentumDelta = momentum * weightDeltas[layer][node][weightIndex];
                        double weightDecayDelta = weightDecay * learningRate * weight;
                        weightDeltas[layer][node][weightIndex] = (learningRate * error[layer][node] * input);
                        weights[layer][node][weightIndex] = weight + weightDeltas[layer][node][weightIndex]
                                                            + momentumDelta - weightDecayDelta;
                    }
                }
            }

            currentNN->set_weights(weights);
        }

        if (calculate_neural_net_error(bestNN.get(), trainingTuples) > calculate_neural_net_error(currentNN.get(), trainingTuples)) {
            bestNN.reset(currentNN.release());
        }
    }

    nn->set_weights(bestNN->get_weights());
    return calculate_neural_net_error(nn, trainingTuples);
}

double calculate_error(vector<double> expected, vector<double> actual) {
    double error = 0;
    for (int i = 0; i < expected.size(); i++) {
        error += pow(expected[i]-actual[i], 2)/2;
    }
    return error;
}

double calculate_neural_net_error(SBP_Impl* nn, vector<pair<vector<double>, vector<double>>> trainingTuples) {
    double totalError = 0;
    for (auto tuple : trainingTuples) {
        totalError += calculate_error(nn->feed_forward(tuple.first), tuple.second);
    }
    return totalError/trainingTuples.size();
}