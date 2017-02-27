#include <iostream>
#include "../include/neural_net.h"
#include "tests.h"
#include <vector>
#include <cmath>

using namespace std;

bool test_create_3_4_2_nn() {
    vector<int> sizes = {3,4,2};
    Neural_Net nn = Neural_Net(sizes);
    vector<int> layers = nn.get_layer_sizes();

    if (layers != sizes) {
        cout << "Failed to create a neural net with sizes {3,4,2}" << endl;
        return false;
    } else {
        cout << "Created a neural net with sizes {3,4,2}" << endl;
        cout << "It has the initial weights:" << endl;
        for (auto layer : nn.get_weights()) {
            cout << "  layer:" << endl;
            for (auto nodes : layer) {
                cout << "    node:" << endl;
                for (double from : nodes) {
                    cout << "      " << from << endl;
                }
            }
        }
        return true;
    }
}

bool test_ff_1_1() {
    vector<int> sizes = {1,1};
    Neural_Net nn(sizes);

    vector<vector<vector<double>>> weights = {{{1, 1}}};
    nn.set_weights(weights);

    vector<double> input = {1};
    vector<double> output = nn.feed_forward(input);
    if (abs(output[0] - 0.964028) > 0.000001) {
        cout << "Failed to feed forward (1-1), " << "expected: " << 0.964028 << ". got: " << output[0] << endl;
        return false;
    } else {
        cout << "Successfully fed forward on a 1-1 network" << endl;
        return true;
    }
}

bool test_ff_2_1() {
    vector<int> sizes = {2,1};
    Neural_Net nn(sizes);

    vector<vector<vector<double>>> weights = {{{0, 1, 1}}};
    nn.set_weights(weights);

    vector<double> input = {1, 1};
    vector<double> output = nn.feed_forward(input);
    if (abs(output[0] - 0.964028) > 0.000001) {
        cout << "Failed to feed forward (2-1), " << "expected: " << 0.964028 << ". got: " << output[0] << endl;
        return false;
    } else {
        cout << "Successfully fed forward on a 2-1 network" << endl;
        return true;
    }
}

bool test_ff_1_1_1() {
    vector<int> sizes = {1,1,1};
    Neural_Net nn(sizes);

    vector<vector<vector<double>>> weights = {{{0, 1}},{{0, 1}}};
    nn.set_weights(weights);

    vector<double> input = {1};
    vector<double> output = nn.feed_forward(input);
    if (abs(output[0] - 0.642015) > 0.000001) {
        cout << "Failed to feed forward (1-1-1), " << "expected: " << 0.642015 << ". got: " << output[0] << endl;
        return false;
    } else {
        cout << "Successfully fed forward on a 1-1-1 network" << endl;
        return true;
    }
}

int neural_net_tests() {
    cout << "Beginning neural net tests:" << endl;

    int failed = 0;
    failed += !test_create_3_4_2_nn();
    failed += !test_ff_1_1();
    failed += !test_ff_1_1_1();
    failed += !test_ff_2_1();

    cout << "neural net tests complete" << endl << endl;
    return failed;
}