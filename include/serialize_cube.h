#ifndef SERIALIZE_CUBE_H
#define SERIALIZE_CUBE_H

#include <string>
#include <map>

std::string stringify_state(std::string move);

std::string stringify_move(std::string move);

bool write_cube(std::string filename, std::map<std::string, std::string> stateMoves);

#endif
