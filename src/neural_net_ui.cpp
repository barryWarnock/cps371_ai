#include "../include/neural_net_ui.h"
#include "../include/sbp_impl.h"
#include "../include/neural_net.h"
#include "../include/stochastic_back_propogation.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <cstring>
#include <sstream>
#include <algorithm>

using namespace std;

unique_ptr<SBP_Impl> create_nn();
void view_weights(SBP_Impl* nn);
void feed_forward(SBP_Impl* nn);
void train(SBP_Impl* nn);
void save(SBP_Impl* nn);
SBP_Impl* load();
void experiment();
void test_csv(SBP_Impl* nn);

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
             << "[6] experiment\n"
             << "[7] test against training csv\n"
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
            case 6:
                experiment();
                break;
            case 7:
                test_csv(nn.get());
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

/**
 * loads training tuples from a file
 * @param filename
 * @return a pair of bool and the tuples, if the bool is false the function failed to load from the file
 */
pair<bool, vector<pair<vector<double>, vector<double>>>> training_tuples_from_file(string filename) {
    ifstream file;
    file.open(filename, ios::in);
    if (!file.is_open()) {
        return make_pair(false, vector<pair<vector<double>, vector<double>>>(0));
    } else {
        vector<pair<vector<double>, vector<double>>> trainingTuples;

        string line, in, out;
        while (getline(file, line)) {
            in = strtok((char *) line.c_str(), "|");
            out = strtok(NULL, "|");
            vector<double> inVector, outVector;

            char *num;
            num = strtok((char *) in.c_str(), ",");
            do {
                if (num != "") inVector.push_back(atof(num));
            } while ((num = strtok(NULL, ",")));

            num = strtok((char *) out.c_str(), ",");
            do {
                if (num != "") outVector.push_back(atof(num));
            } while ((num = strtok(NULL, ",")));

            trainingTuples.push_back(make_pair(inVector, outVector));
        }
        return make_pair(true, trainingTuples);
    }
}

void train(SBP_Impl* nn) {
    cout << "please enter a filename containing training data: ";
    string filename;
    cin >> filename;

    auto trainingTuplesPair = training_tuples_from_file(filename);
    if (!trainingTuplesPair.first) {
        cout << "failed to load file, aborting." << endl;
    } else {
        auto trainingTuples = trainingTuplesPair.second;
        int iterations, epochs;
        double learningRate, momentum, weightDecay;

        cout << "epochs: ";
        cin >> epochs;
        cout << "epoch iterations: ";
        cin >> iterations;
        cout << "learning rate: ";
        cin >> learningRate;
        cout << "momentum: ";
        cin >> momentum;
        cout << "weight decay: ";
        cin >> weightDecay;

        cout << "training, please wait" << endl;

        double error = neural_net_sbp(trainingTuples, nn, iterations, epochs, learningRate, momentum, weightDecay);

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

void experiment() {
    string filename;
    cout << "name of file containing training tuples: ";
    cin >> filename;

    auto trainingTuplesPair = training_tuples_from_file(filename);
    if (!trainingTuplesPair.first) {
        cout << "failed to load file, aborting." << endl;
    } else {
        auto trainingTuples = trainingTuplesPair.second;

        int inputSize = trainingTuples[0].first.size();
        int outputSize = trainingTuples[0].second.size();

        vector<pair<double, string>> best;

        for (int H = 5; H <= 30; H += 5) {
            vector<int> sizes = {inputSize, H, outputSize};
            for (double l = 0.01; l <= 0.1; l += 0.01) {
                for (double M = 0; M < 1; M += 0.3) {
                        for (int numEpochs = 10; numEpochs <= 30; numEpochs += 10) {
#pragma omp parallel for
                            for (int i = 100; i <= 400; i += 100) {
                                Neural_Net nn(sizes);
                                double error = neural_net_sbp(trainingTuples, &nn, i * trainingTuples.size(), numEpochs,
                                                              l, M);
#pragma omp critical
                                {
                                    stringstream description;

                                    description << "H: " << H << endl
                                                << "l: " << l << endl
                                                << "M: " << M << endl
                                                << "numEpochs: " << numEpochs << endl
                                                << "i: " << i << endl;

                                    best.push_back(make_pair(error, description.str()));

                                    cout << error << endl << description.str() << endl << endl;
                                }
                            }
                        }
                }
            }
        }

        sort(best.begin(), best.end(), [](pair<double, string> a, pair<double, string> b) {return a.first > b.first;});
        cout << "top 5:";
        for (int i = 0; i < 5; i++) {
            cout << "   error: " << best[i].first << endl
                 << best[i].second
                 << endl << endl;
        }
    }
}

void test_csv(SBP_Impl* nn) {
    string filename;
    cout << "name of file containing training tuples: ";
    cin >> filename;

    auto trainingTuplesPair = training_tuples_from_file(filename);
    if (!trainingTuplesPair.first) {
        cout << "failed to load file, aborting." << endl;
    } else {
        auto trainingTuples = trainingTuplesPair.second;

        bool stop = false;
        while (!stop) {
            unsigned int input;
            cout << "please choose a tuple index between 0 and " << trainingTuples.size()-1 << ": ";
            cin >> input;
            if (input >= trainingTuples.size()) continue;

            auto in = trainingTuples[input].first;
            auto expectedOut = trainingTuples[input].second;
            auto actualOut = nn->feed_forward(in);

            cout << "expected [";
            for (double d : expectedOut) {
                cout << d << ",";
            }
            cout << "]" << endl
                 << "received [";
            for (double d : actualOut) {
                cout << d << ",";
            }
            cout << "]" << endl << endl;

            cout << "or after 'stretching' to extremes\n"
                 << "         [";
            for (double d : actualOut) {
                cout << ((d > 0) ? 1 : -1) << ",";
            }
            cout << "]" << endl << endl;

            cout << "[0] exit\n"
                 << "[1] keep testing\n"
                 << endl;
            cin >> input;

            stop = !input;
        }
    }
}