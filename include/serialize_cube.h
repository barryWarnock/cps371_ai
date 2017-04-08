#ifndef SERIALIZE_CUBE_H
#define SERIALIZE_CUBE_H

#include <string>
#include <map>
#include <vector>

std::string stringify_state(std::string state);

std::vector<double> vectorize_state(std::string state);

std::string stringify_move(std::string move);

std::string parse_move(std::vector<double> moveVector);

bool write_cube(std::string filename, std::map<std::string, std::string> stateMoves);

#endif
