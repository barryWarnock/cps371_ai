//
// Created by warnock on 24/01/17.
//

#ifndef RUBIKS_CUBE_H
#define RUBIKS_CUBE_H

#include <string>
#include "searchable.h"

enum Cube_Colour{
    WHITE = 'w',
    YELLOW = 'y',
    BLUE = 'b',
    GREEN = 'g',
    ORANGE= 'o',
    RED = 'r'
};

enum Cube_Axis{
    X = 0,
    Y = 1,
    Z = 2
};

enum Cube_Direction{
    CLOCKWISE = 0,
    COUNTER_CLOCKWISE = 1
};

class Rubiks_Cube : public Searchable{
protected:
    std::string cubeString;
    int n;
    int index_from_fxy(int face, int x, int y);
    Cube_Colour read_logical(int face, int x, int y);
    void write_logical(int face, int x, int y, Cube_Colour value);
    /**
     * used when going from an even face to an odd face or vice-versa.
     * @param index the value you need 'flipped'
     * @return
     */
    int flip_index(int index);
    int translate_face(int face, Cube_Axis axis, Cube_Direction direction);
    void rotate_face(int face, Cube_Direction direction);

public:
    Rubiks_Cube(int n);
    Rubiks_Cube(int n, std::string startState);
    virtual std::vector<Search_Node*> generate_children();
    virtual std::string get_state();
    virtual int run_heuristic();
    std::string pretty_print_state();
    Rubiks_Cube * do_move(Cube_Axis axis, int slice, Cube_Direction direction);
    virtual bool equal_to(Searchable *other); //it's probably just me not understanding operator overloading well enough but it seemed needlessly messy for this
};


#endif //RUBIKS_CUBE_H
