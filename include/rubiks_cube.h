//
// Created by warnock on 24/01/17.
//

#ifndef RUBIKS_CUBE_H
#define RUBIKS_CUBE_H

#include <string>
#include "searchable.h"

enum Colour{
    WHITE = 'w',
    YELLOW = 'y',
    BLUE = 'b',
    GREEN = 'g',
    ORANGE= 'o',
    RED = 'r'
};

enum Axis{
    X,
    Y,
    Z
};

enum Direction{
    CLOCKWISE,
    COUNTER_CLOCKWISE
};

class Rubiks_Cube : public Searchable{
protected:
    std::string cubeString;
    int n;

    int index_from_fxy(int face, int x, int y);

    Colour read_logical(int face, int x, int y);

    void write_logical(int face, int x, int y, Colour value);

    /**
     * used when going from an even face to an odd face or vice-versa.
     * @param index the value you need 'flipped'
     * @return
     */
    int flip_index(int index);

    int translate_face(int face, Axis axis, Direction direction);

    void rotate_face(int face, Direction direction);

public:
    Rubiks_Cube(int n);
    Rubiks_Cube(int n, std::string startState);
    virtual std::vector<Searchable> generate_children();
    virtual std::string get_state();
    virtual int run_heuristic();
    std::string pretty_print_state();
    Rubiks_Cube do_move(Axis axis, int slice, Direction direction);
};


#endif //RUBIKS_CUBE_H
