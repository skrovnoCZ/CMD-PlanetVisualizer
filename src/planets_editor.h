#ifndef __PLANETS_EDITOR__
#define __PLANETS_EDITOR__

#include <iostream>
#include "grid_screen.h"

class planets_editor
{
private:
    vector<string> m_grid;
    Planets* m_planets;
    size_t m_width;
    size_t m_height;
public:
    //variables public to speed up proccess
    size_t m_selector;
    size_t m_selector_x;
    size_t m_selector_y;
    bool m_cursor_visible;

    planets_editor();
    void set_planets_shortcut(Planets* new_object);
    void set_grid(grid_screen* new_grid);
    void cursor_flash();
    size_t get_width();
    size_t get_height();
    void delete_selected();
    void print_grid_editor();
    ~planets_editor();
};

#endif