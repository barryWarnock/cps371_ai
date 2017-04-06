#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <tuple>
#include <vector>

/**
 * elite + mutation + crossover must equal 100
 * @param population the number of genomes per population
 * @param generations the number of generations to run the algorithm for
 * @param elite the percentage of the population that should move forward unchanged (where more fit genomes have a higher chance of moving on)
 * @param mutation the percentage of the population that should be mutated and moved forward
 * @param crossover the percentage of the population that should be created through crossover
 * @return a vector of tuples representing the (best, average, worst) fitnesses per generation
 */
std::vector<std::tuple<double, double, double>> run_genetic_algorithm(int population, int generations,
                                                                      int elite, int mutation, int crossover);
#endif
