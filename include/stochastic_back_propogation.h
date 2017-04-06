#ifndef STOCHASTIC_BACK_PROPOGATION_H
#define STOCHASTIC_BACK_PROPOGATION_H

#include <vector>
#include "sbp_impl.h"
typedef std::vector<std::pair<std::vector<double>, std::vector<double>>> NN_Data_Set;
double neural_net_sbp(NN_Data_Set trainingTuples, SBP_Impl* nn,
                      int trainingIterations, int epochs, double learningRate = 0.01, double momentum = 0.0,
                      double weightDecay = 0.0);

#endif
