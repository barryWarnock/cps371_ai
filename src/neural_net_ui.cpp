#include "../include/neural_net_ui.h"
#include "../include/sbp_impl.h"
#include "../include/neural_net.h"
#include "../include/stochastic_back_propogation.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <cstring>

using namespace std;

unique_ptr<SBP_Impl> create_nn();
void view_weights(SBP_Impl* nn);
void feed_forward(SBP_Impl* nn);
void train(SBP_Impl* nn);
void save(SBP_Impl* nn);
SBP_Impl* load();

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
                nn.reset(load());
                break;
            default:
                cout << "not a valid option" << endl;
        }
    } while (input);
}

unique_ptr<SBP_Impl> create_nn() {
    cout << "[0] manually specify neural net size\n"
         << "[1] load neural net from file\n"
         << endl;
    int type;
    cin >> type;
    if (type) {
        SBP_Impl *nn = load();
        if (nn) {
            return move(unique_ptr<SBP_Impl>(nn));
        } else {
            cout << "Failed to load from file, defaulting to manual" << endl;
        }
    }
    int layers;
    cout << "How many layers: ";
    cin >> layers;

    vector<int> layerSizes(layers);
    for (int layer = 0; layer < layers; layer++) {
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
    }
    cout << endl;

    cout << endl;
}

void train(SBP_Impl* nn) {
    cout << "please enter a filename containing training data: ";
    string filename;
    cin >> filename;

    ifstream file;
    file.open(filename, ios::in);
    if (!file.is_open()) {
        cout << "failed to load file, aborting." << endl;
    } else {
        vector<pair<vector<double>, vector<double>>> trainingTuples;

        string line, in, out;
        while (getline(file, line)) {
            in = strtok((char*)line.c_str(), "|");
            out = strtok(NULL, "|");
            vector<double> inVector, outVector;

            char* num;
            num = strtok((char*)in.c_str(), ",");
            do {
                inVector.push_back(atof(num));
            } while ((num = strtok(NULL, ",")));

            num = strtok((char*)out.c_str(), ",");
            do {
                outVector.push_back(atof(num));
            } while ((num = strtok(NULL, ",")));

            trainingTuples.push_back(make_pair(inVector, outVector));
        }

        cout << "training, please wait" << endl;

        double error = neural_net_sbp(trainingTuples, nn, trainingTuples.size() * 30, 5);

        cout << "training resulted in an error of: " << error << endl;
    }
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

SBP_Impl* load() {
    cout << "please enter a filename: ";
    string filename;
    cin >> filename;

    ifstream file;
    file.open(filename, ios::in);
    if (!file.is_open()) {
        cout << "Failed to open " << filename << endl << endl;
        return NULL;
    } else {
        vector<int> newLayerSizes;
        vector<vector<vector<double>>> newWeights;

        string line;
        vector<vector<double>> layer;

        while (getline(file, line)) {
            if (line == "") {
                newWeights.push_back(layer);

                layer = vector<vector<double>>();
            } else {
                vector<double> node;

                string weightStr;
                weightStr = strtok((char*)line.c_str(), ",");

                while (true) {
                    node.push_back(atof(weightStr.c_str()));
                    char* weightCSTR = strtok(NULL, ",");
                    if (weightCSTR == NULL) {
                        break;
                    }
                    weightStr = weightCSTR;
                }

                layer.push_back(node);
            }
        }

        for (auto layer : newWeights) {
            newLayerSizes.push_back(layer[0].size()-1);
        }
        newLayerSizes.push_back(newWeights[newWeights.size()-1].size());

        cout << endl;

        file.close();

        SBP_Impl* nn = new Neural_Net(newLayerSizes);
        nn->set_weights(newWeights);

        return nn;
    }
}