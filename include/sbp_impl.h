#ifndef SBP_IMPL_H
#define SBP_IMPL_H

#include <vector>

class SBP_Impl {
protected:
    const int BIAS = 1;
    std::vector<int> layerSizes;
    std::vector<std::vector<std::vector<double>>> weights; // weights[layer][node][fromNode] where fromNode 0 is the bias
public:
    virtual void init(std::vector<int> layerSizes) = 0;
    virtual std::vector<double> feed_forward(std::vector<double> input) = 0;
    virtual std::vector<std::vector<double>> get_previous_nets() = 0;
    virtual SBP_Impl *clone() = 0;

    //getters and setters
    std::vector<int> get_layer_sizes();

    std::vector<std::vector<std::vector<double>>> get_weights();
    void set_weights(std::vector<std::vector<std::vector<double>>> weights);
};

#endif
