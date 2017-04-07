#include <random>
#include <iostream>
#include "../include/neural_net_genome.h"
using namespace std;

queue<Neural_Net_Genome*> Neural_Net_Genome::freeNNGs = queue<Neural_Net_Genome*>();


Neural_Net_Genome *Neural_Net_Genome::get_NNG(std::vector<int> topology) {
    Neural_Net_Genome* nng;
#pragma omp critical
    {
        if (!freeNNGs.empty()) {
            nng = freeNNGs.front();
            freeNNGs.pop();
            nng->init(topology);
        } else {
            nng = new Neural_Net_Genome(topology);
        }
    }
    return nng;
}

void Neural_Net_Genome::free_NNG(Neural_Net_Genome *nng) {
#pragma omp critical
    freeNNGs.push(nng);
}

void Neural_Net_Genome::cleanup() {
#pragma omp critical
    {
        while (!freeNNGs.empty()) {
            delete (freeNNGs.front());
            freeNNGs.pop();
        }
    }
}

Neural_Net_Genome::Neural_Net_Genome(std::vector<int> topology) {
    this->init(topology);
}

void Neural_Net_Genome::init(std::vector<int> topology) {
    this->topology = topology;
    int totalWeights = 0;
    for (int i = 1; i < topology.size(); i++) {
        totalWeights += topology.at(i) * (topology.at(i-1)+1);//a weight for each node to each node in the next layer plus bias
    }
    weights = vector<double>(totalWeights);
    random_device rnd;
    for (double& weight : weights) {
        int iValue = (rnd()%200)+1;
        weight = (iValue < 101) ? (-1 * 1.0/iValue) : (1.0/(iValue-100));
    }
}

Neural_Net Neural_Net_Genome::get_as_net() {
    Neural_Net net(topology);
    auto weightVectors = net.get_weights();

    int i = 0;
    for (auto& layer : weightVectors) {
        for (auto& node : layer) {
            for (double& weight : node) {
                weight = weights.at(i++);
            }
        }
    }

    net.set_weights(weightVectors);
    return net;
}

Neural_Net_Genome *Neural_Net_Genome::mutate() {
    Neural_Net_Genome* nng = get_NNG(topology);
    random_device rnd;
    for (int i = 0; i < weights.size(); i++) {
        double currentWeight = weights.at(i);
        bool doMutate = rnd()%2;
        if (doMutate) {
            int percentage = (rnd()%400)+1;//1-200 is negative, 201-400 is positive 1%-200%
            double onePercent = currentWeight/100;
            double delta = (percentage<201) ? (-1 * onePercent * percentage) : ((percentage-200) * onePercent);
            nng->weights.at(i) = delta + currentWeight;
        } else {
            nng->weights.at(i) =currentWeight;
        }
    }
    return nng;
}

Neural_Net_Genome *Neural_Net_Genome::crossover(Neural_Net_Genome * other) {
    Neural_Net_Genome* nng = get_NNG(topology);
    random_device rnd;
    for (int i = 0; i < weights.size(); i++) {
        bool fromMe = rnd()%2;
        if (fromMe) {
            nng->weights.at(i) = this->weights.at(i);
        } else {
            nng->weights.at(i) = other->weights.at(i);
        }
    }
    return nng;
}