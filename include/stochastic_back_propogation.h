#ifndef STOCHASTIC_BACK_PROPOGATION_H
#define STOCHASTIC_BACK_PROPOGATION_H

#include <vector>
#include "sbp_impl.h"

double neural_net_sbp(std::vector<std::pair<std::vector<double>, std::vector<double>>> trainingTuples, SBP_Impl* nn,
                      int trainingIterations, int epochs, double learningRate = 0.01, double momentum = 0.0,
                      double weightDecay = 0.0);

#endif
