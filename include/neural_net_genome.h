#ifndef NEURAL_NET_GENOME_H
#define NEURAL_NET_GENOME_H
#include <vector>
#include <queue>
#include "neural_net.h"

class Neural_Net_Genome {
protected:
    static std::queue<Neural_Net_Genome*> freeNNGs();//used to prevent unnecessary reallocations of memory
    std::vector<int> topology;
    std::vector<double> weights;//genes
public:
    //pooling functions
    static Neural_Net_Genome* get_NNG(std::vector<int> topology); //either return a NNG if one is already available or create a new one then return it
    static void free_NNG(Neural_Net_Genome* nng); //return a NNG to the pool
    static void cleanup(); //free all of the NNGs in the free_pool
    //end of pooling

    Neural_Net_Genome(std::vector<int> topology);
    void init(std::vector<int> topology);
    Neural_Net get_as_net();
    Neural_Net_Genome* mutate();
    Neural_Net_Genome* crossover(Neural_Net_Genome* other);
};

#endif
