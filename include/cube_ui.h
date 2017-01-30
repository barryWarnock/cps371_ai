#ifndef CUBE_FACADE_H
#define CUBE_FACADE_H

#include <memory>
#include <iostream>
#include "rubiks_cube.h"

/**
 * gives the user a list of things they can do to a cube
 */
void cube_ui_main();

/**
 * asks the user how big of a cube to make then creates it
 * @return the new cube
 */
std::unique_ptr<Rubiks_Cube> create_cube();

/**
 * allows the user to rotate a cube with move strings of their choice
 * @param cube the cube to rotate
 */
void manually_rotate(std::unique_ptr<Rubiks_Cube> *cube);

/**
 * asks the user what depth to mix a cube to and then mixes it to that depth
 * @param cube the cube to rotate
 */
void randomly_rotate(std::unique_ptr<Rubiks_Cube> *cube);

/**
 * prints the cube
 * @param cube the cube to print
 */
void view_cube(std::unique_ptr<Rubiks_Cube> *cube);

/**
 * find a path and print it out
 * @param cube the cube to solve
 */
void solve_cube(std::unique_ptr<Rubiks_Cube> *cube);

#endif
