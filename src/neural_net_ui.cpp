#include "../include/neural_net_ui.h"
#include "../include/sbp_impl.h"
#include "../include/neural_net.h"
#include <iostream>
#include <memory>
#include <fstream>

using namespace std;

unique_ptr<SBP_Impl> create_nn();
void view_weights(SBP_Impl* nn);
void feed_forward(SBP_Impl* nn);
void train(SBP_Impl* nn);
void save(SBP_Impl* nn);
void load(SBP_Impl* nn);

void neural_net_ui_main() {
    unique_ptr<SBP_Impl> nn = create_nn();
    int input;
    do {
        cout << "What would you like to do:\n"
             << "[0] exit\n"
             << "[1] view weights\n"
             << "[2] feed forward\n"
             << "[3] train\n"
             << "[4] save\n"
             << "[5] load\n"
             << endl;
        cin >> input;

        switch (input) {
            case 0:
                break;
            case 1:
                view_weights(nn.get());
                break;
            case 2:
                feed_forward(nn.get());
                break;
            case 3:
                train(nn.get());
                break;
            case 4:
                save(nn.get());
                break;
            case 5:
                load(nn.get());
                break;
            default:
                cout << "not a valid option" << endl;
        }
    } while (input);
}

unique_ptr<SBP_Impl> create_nn() {
    int layers;
    cout << "How many layers: ";
    cin >> layers;

    vector<int> layerSizes(layers);
    for (int layer =0; layer < layers; layer++) {
        cout << "How many nodes in layer " << layer << ": ";
        cin >> layerSizes[layer];
    }

    cout << endl;
    return move(unique_ptr<SBP_Impl>(new Neural_Net(layerSizes)));
}

void view_weights(SBP_Impl* nn) {
    cout << "The first weight in each node is its bias weight. The rest are the weights for the nodes from the previous layer" << endl;
    for (auto layer : nn->get_weights()) {
        cout << "  layer:" << endl;
        for (auto node : layer) {
            cout << "    node:" << endl;
            for (double from : node) {
                cout << "      " << from << endl;
            }
        }
    }
    cout << endl;
}

void feed_forward(SBP_Impl* nn) {
    int inputSize = nn->get_layer_sizes()[0];
    vector<double> inputs(inputSize);

    for (int i = 0; i < inputSize; i++) {
        cout << "enter input for node " << i << ": ";
        cin >> inputs[i];
    }

    vector<double> outputs = nn->feed_forward(inputs);
    cout << "result: ";
    for (double output : outputs) {
        cout << output << ", ";
    } cout << endl;

    cout << endl;
}

void train(SBP_Impl* nn) {
    cout << "not yet implemented" << endl;
    cout << endl;
}

void save(SBP_Impl* nn) {
    cout << "please enter a filename: ";
    string filename;
    cin >> filename;

    ofstream file;
    file.open(filename, ios::out);
    if (!file.is_open()) {
        cout << "Failed to open " << filename << endl;
    } else {
        vector<vector<vector<double>>> weights = nn->get_weights();
        for (auto layer : weights) {
            for (auto node : layer) {
                for (double weight : node) {
                    file << weight << ",";
                }
                file << "\n";
            }
            file << "\n";
        }
        file.close();
    }

    cout << endl;
}

void load(SBP_Impl* nn) {
    cout << "not yet implemented" << endl;
    cout << endl;
}