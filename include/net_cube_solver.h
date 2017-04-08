#ifndef NET_CUBE_SOLVER_H
#define NET_CUBE_SOLVER_H

#include "../include/neural_net.h"
#include "../include/rubiks_cube.h"
#include <memory>

/**
 * uses a neural net to solve a rubiks cube
 * @param net the neural net to use to solve the cube, in layer has 324 nodes and out layer has 8
 * @param cube
 * @param maxMoves the max number of moves to try
 * @return either the number of moves it took to solve or -1 if it was not solved
 */
int solve_cube_with_net(Neural_Net* net, std::shared_ptr<Rubiks_Cube> cube, int maxMoves);
#endif
