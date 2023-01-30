#ifndef __GRID_SCREEN__
#define __GRID_SCREEN__

#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include "planets.h"

#define SYMBOL_PLANET 'O'
#define SYMBOL_WALL (char)219
#define SYMBOL_NULL ' '

class grid_screen
{
private:
    std::vector<std::string> m_grid;
    size_t m_width;
    size_t m_height;
    bool m_inicialise;
    bool m_in_grid;
public:
    int m_selector;

    grid_screen(size_t new_height, size_t new_width);
    void set_object(Planets new_object, size_t new_y, size_t new_x);
    void set_all_objects(Planets new_object);
    size_t get_width();
    size_t get_height();
    vector<string> get_grid();
    void print_grid();
    void refresh_grid();
    bool get_in_grid_status();
    ~grid_screen();
};

#endif