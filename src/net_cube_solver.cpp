
#include "../include/neural_net.h"
#include "../include/rubiks_cube.h"
#include "../include/serialize_cube.h"

using namespace std;

int solve_cube_with_net(Neural_Net *net, shared_ptr<Rubiks_Cube> cube, int maxMoves) {
    Rubiks_Cube goal(cube->size());
    vector<double> currentState;
    string move;

    for (int moveNum = 0; moveNum < maxMoves+1; moveNum++) {
        if (cube->equal_to(&goal)) {
            return moveNum;
        } else if (moveNum < maxMoves) {//ensures that if the last move is the one that solves it that it is counted
            currentState = vectorize_state(cube->get_state());
            move = parse_move(net->feed_forward(currentState));
            cube.reset(cube->do_move(move));
        }
    }

    return -1;//not solved in MaxMoves
}
