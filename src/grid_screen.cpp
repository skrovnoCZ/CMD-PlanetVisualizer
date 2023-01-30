#include "grid_screen.h"



grid_screen::grid_screen(size_t new_height, size_t new_width)
{
    m_selector = 0;
    m_inicialise = false;
    m_in_grid = true;

    std::string string_x;

    string_x.resize(new_width, SYMBOL_NULL);

    std::vector<std::string> string_temp(new_height, string_x);
    m_grid = string_temp;

    refresh_grid();

    m_width = 0;
    m_height = m_grid.size();

    for (size_t i = 0; i < m_grid.size(); i++)
    {
        if (m_grid.at(i).size() > m_width)
        {
            m_width = m_grid.at(i).size();
        }
    }

    m_inicialise = true;
}

void grid_screen::set_object(Planets new_object, size_t new_y, size_t new_x)
{
    size_t x = (size_t)new_object.get_x_pos(new_x);
    size_t y = (size_t)new_object.get_y_pos(new_y);

    if ((y < m_height) && (x < m_width) && m_grid.at(y).at(x) != SYMBOL_WALL)
    {
        m_grid[y][x] = SYMBOL_PLANET;
    }
    else
    {
        std::cerr << "Object out of range!" << std::endl;
        m_in_grid = false;
    }
}

void grid_screen::set_all_objects(Planets new_object)
{
    for (size_t i = 0; i < new_object.get_vec_coord_size(); i++)
    {
        set_object(new_object, i, i);
    }
}

size_t grid_screen::get_width()
{
    return m_width;
}

size_t grid_screen::get_height()
{
    return m_height;
}

vector<string> grid_screen::get_grid()
{
    return m_grid;
}

void grid_screen::print_grid()
{
    system("CLS");

    for (size_t i = 0; i < m_grid.size(); i++)
    {
        std::cout << m_grid.at(i) << std::endl;
    }
}

void grid_screen::refresh_grid()
{
    if (m_inicialise)
    {
        std::string string_x;

        string_x.resize(m_width, SYMBOL_NULL);

        std::vector<std::string> string_temp(m_height, string_x);
        m_grid = string_temp;
    }

    for (size_t y = 0; y < m_grid.size(); y++)
    {
        for (size_t x = 0; x < m_grid.at(y).size(); x++)
        {
            if (!((y > 0) && (y < (m_grid.size() - 1))))
            {
                m_grid[y][x] = SYMBOL_WALL;
            }
            else if (!((x > 0) && (x < (m_grid.at(y).size() - 1))))
            {
                m_grid[y][x] = SYMBOL_WALL;
            }
        }
    }
}

bool grid_screen::get_in_grid_status()
{
    return m_in_grid;
}

grid_screen::~grid_screen()
{
}