#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include "sbp_impl.h"

class Neural_Net : public SBP_Impl {
protected:
    std::vector<std::vector<double>> nets = std::vector<std::vector<double>>();
public:
    Neural_Net(std::vector<int> layerSize);
    void init(std::vector<int> layerSizes);
    std::vector<double> feed_forward(std::vector<double> input);
    std::vector<std::vector<double>> get_previous_nets();
    SBP_Impl *clone();
};


#endif
