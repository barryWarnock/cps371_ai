#include "../include/sbp_impl.h"

std::vector<int> SBP_Impl::get_layer_sizes() {
    return this->layerSizes;
}

std::vector<std::vector<std::vector<double>>> SBP_Impl::get_weights() {
    return this->weights;
}

void SBP_Impl::set_weights(std::vector<std::vector<std::vector<double>>> weights) {
    this->weights = weights;
}
