#include "../include/neural_net.h"
#include <algorithm>
#include <math.h>
#include <random>
#include <functional>

using namespace std;

mt19937 randomGenerator(random_device{}());

Neural_Net::Neural_Net(std::vector<int> layerSizes) {
    init(layerSizes);
}

void Neural_Net::init(std::vector<int> layerSizes) {
    this->layerSizes = layerSizes;

    //initialize weights to random values
    weights = vector<vector<vector<double>>>(layerSizes.size() - 1);
    for (int layer = 0; layer < weights.size(); layer++) {
        int actualLayer = layer+1; // no weights for the input layer
        weights[layer] = vector<vector<double>>(layerSizes[actualLayer]);

        double min = -1 / sqrt(layerSizes[actualLayer]);
        double max = 1 / sqrt(layerSizes[actualLayer]);
        uniform_real_distribution<double> randomDistribution(min, max);
        auto random_double = bind(randomDistribution, randomGenerator);

        for (auto &node : weights[layer]) {
            node = vector<double>(layerSizes[actualLayer-1]+1);
            generate(node.begin(), node.end(), [&random_double](){return random_double();});
        }
    }
}

std::vector<double> Neural_Net::feed_forward(std::vector<double> input) {
    if (input.size() != layerSizes[0]) {
        throw std::domain_error("Bad input, feed forward must take the same number of inputs as input neurons, expected ");
    }

    nets = vector<vector<double>>(layerSizes.size()-1);
    vector<vector<double>> activated = vector<vector<double>>(layerSizes.size());
    for (int i = 0; i < layerSizes.size(); i++) {
        if (i > 0) {
            nets[i - 1] = vector<double>(layerSizes[i], 0);
        }
        activated[i] = vector<double>(layerSizes[i]);
    }

    for (int i = 0; i < input.size(); i++) {
        activated[0][i] = input[i];
    }

    for (int layer = 1; layer < layerSizes.size(); layer++) {
        int adjustedLayerIndex = layer-1;

        for (int i = 0; i < layerSizes[layer]; i++) {
            for (int j = 0; j < layerSizes[adjustedLayerIndex]; j++) {
                nets[adjustedLayerIndex][i] += activated[adjustedLayerIndex][j] * weights[adjustedLayerIndex][i][j+1];
            }
            nets[adjustedLayerIndex][i] += BIAS * weights[adjustedLayerIndex][i][0];
            activated[layer][i] = tanh(nets[adjustedLayerIndex][i]);
        }
    }

    return activated[activated.size()-1];
}

std::vector<std::vector<double>> Neural_Net::get_previous_nets() {
    return nets;
}

SBP_Impl *Neural_Net::clone() {
    SBP_Impl* cloned = new Neural_Net(this->layerSizes);
    cloned->set_weights(this->weights);
    return cloned;
}