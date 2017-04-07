#include <random>
#include "../include/neural_net_genome.h"
using namespace std;

Neural_Net_Genome *Neural_Net_Genome::get_NNG(std::vector<int> topology) {
    Neural_Net_Genome* nng;
    if (freeNNGs.size() > 0) {
        nng = freeNNGs.front();
        freeNNGs.pop();
        nng->init(topology);
    } else {
        nng = new Neural_Net_Genome(topology);
    }
    return nng;
}

void Neural_Net_Genome::free_NNG(Neural_Net_Genome *nng) {
    freeNNGs.push(nng);
}

void Neural_Net_Genome::cleanup() {
    while(freeNNGs.size() > 0) {
        delete(freeNNGs.front());
        freeNNGs.pop();
    }
}

Neural_Net_Genome::Neural_Net_Genome(std::vector<int> topology) {
    this->init(topology);
    random_device rnd;
    for (double& weight : weights) {
        int iValue = (rnd()%200)+1;
        weight = (iValue < 101) ? (-1 * 1.0/iValue) : (1.0/(iValue-100));
    }
}

void Neural_Net_Genome::init(std::vector<int> topology) {
    this->topology = topology;
}

Neural_Net Neural_Net_Genome::get_as_net() {
    return Neural_Net(topology);
}

Neural_Net_Genome *Neural_Net_Genome::mutate() {
    Neural_Net_Genome* nng = get_NNG(topology);
    random_device rnd;
    for (int i = 0; i < weights.size(); i++) {
        bool doMutate = rnd()%2;
        if (doMutate) {
            int percentage = (rnd()%400)+1;//1-200 is negative, 201-400 is positive 1%-200%
            double currentWeight = weights.at(i);
            double onePercent = currentWeight/100;
            double delta = (percentage<201) ? (-1 * onePercent * percentage) : ((percentage-200) * onePercent);
            nng->weights.at(i) = delta + currentWeight;
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