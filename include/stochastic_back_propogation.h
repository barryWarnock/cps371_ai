#ifndef STOCHASTIC_BACK_PROPOGATION_H
#define STOCHASTIC_BACK_PROPOGATION_H

#include <vector>
#include "sbp_impl.h"

void neural_net_sbp(std::vector<std::pair<std::vector<double>, std::vector<double>>> trainingTuples, SBP_Impl* nn, int trainingIterations, int epochs);

#endif
