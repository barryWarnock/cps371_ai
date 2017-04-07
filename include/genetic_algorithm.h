#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <tuple>
#include <vector>
#include <functional>
#include "neural_net_genome.h"
/**
 * elite + mutation + crossover must equal 100
 * @param population the number of genomes per population
 * @param generations the number of generations to run the algorithm for
 * @param elite the percentage of the population that should move forward unchanged (where more fit genomes have a higher chance of moving on)
 * @param mutation the percentage of the population that should be mutated and moved forward
 * @param crossover the percentage of the population that should be created through crossover
 * @param fitness_callback a lambda that when given a pointer to a Neural_Net_Genome returns its fitness
 * @param topology a vector representing the desired topology for the genomes
 * @return a vector of tuples representing the (best, average, worst) fitnesses per generation
 */
std::vector<std::tuple<double, double, double>> run_genetic_algorithm(int population, int generations,
                                                                      unsigned int elite, unsigned int mutation, unsigned int crossover,
                                                                      std::function<double(Neural_Net_Genome*)> fitness_callback,
                                                                      std::vector<int> topology);

/**
 * clears the neural_net_genome pool
 * this cant happen in run_genetic_algorithm if it is called is parallel with itself
 */
void genetic_algorithm_cleanup();
#endif
