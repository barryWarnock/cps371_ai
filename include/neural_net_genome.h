#ifndef NEURAL_NET_GENOME_H
#define NEURAL_NET_GENOME_H
#include <vector>
#include "neural_net.h"
#include "stochastic_back_propogation.h"
#include "nng_pool.h"

class Neural_Net_Genome {
protected:
    std::vector<int> topology;
    std::vector<double> weights;//genes
    NN_Data_Set data;//used to check fitness
public:
    Neural_Net_Genome(std::vector<int> topology, NN_Data_Set data);
    void init(std::vector<int> topology, NN_Data_Set data);
    Neural_Net get_as_net();
    double fitness();
    Neural_Net_Genome* mutate(NNG_Pool pool);
    Neural_Net_Genome* crossover(NNG_Pool pool);
};
#endif
