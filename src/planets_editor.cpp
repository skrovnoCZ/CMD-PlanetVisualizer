#include "planets_editor.h"



planets_editor::planets_editor()
{
    m_cursor_visible = true;
    m_selector = 0;
}

void planets_editor::set_planets_shortcut(Planets* new_object)
{
    m_planets = new_object;
}

void planets_editor::set_grid(grid_screen* new_grid)
{
    m_grid = new_grid->get_grid();

    m_width = 0;
    m_height = m_grid.size();

    for (size_t i = 0; i < m_grid.size(); i++)
    {
        if (m_grid.at(i).size() > m_width)
        {
            m_width = m_grid.at(i).size();
        }
    }
}

void planets_editor::cursor_flash()
{
    if (m_planets->get_vec_coord_size() > 0)
    {
        size_t x = (size_t)m_planets->get_x_pos(m_selector);
        size_t y = (size_t)m_planets->get_y_pos(m_selector);

        if (m_cursor_visible)
        {
            m_grid[y][x] = '+';
            m_cursor_visible = false;
        }
        else
        {
            m_grid[y][x] = SYMBOL_PLANET;
            m_cursor_visible = true;
        }
    }
}

size_t planets_editor::get_width()
{
    return m_width;
}

size_t planets_editor::get_height()
{
    return m_height;
}

void planets_editor::delete_selected()
{
    m_planets->remove_planet(m_selector);
}

void planets_editor::print_grid_editor()
{
    system("CLS");

    for (size_t i = 0; i < m_grid.size(); i++)
    {
        std::cout << m_grid.at(i) << std::endl;
    }
}

planets_editor::~planets_editor()
{
}
