#ifndef NNG_POOL_H
#define NNG_POOL_H

#include "neural_net_genome.h"

//NNG_Pool can serve as a pool for both base Neural Net Genomes and Rubiks Genomes
template <class T>
class NNG_Pool {
protected:
    std::vector<T*> freeNNGs;
public:
    T* get_NNG(std::vector<int> topology); //either return a NNG if one is already available or create a new one then return it
    void return_NNG(T* nng); //return a NNG to the pool
    void cleanup(); //free all of the NNGs in the free_pool
};
#endif
