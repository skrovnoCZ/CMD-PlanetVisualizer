#include <iostream>
#include <chrono>
#include "grid_screen.h"
#include "keyboard_keys.h"
#include "planets_editor.h"

using namespace std::chrono;

vector<string> grid_setter(size_t y, size_t x)
{
    std::string line;
    line.resize(x, SYMBOL_NULL);
    std::vector<std::string> vector_out(y, line);

    return vector_out;
}

string line_setter(string input, string sentence)
{
    for (size_t i = 0; i < sentence.size(); i++)
    {
        if (i + 1 < input.size())
        {
            input[i + 1] = sentence.at(i);
        }
    }

    return input;
}

void editor_precise()
{

}

void editor_basic(planets_editor* editor, keyboard_keys &keyboard, Planets &cust_planets, grid_screen* screen, bool enabler)
{
    time_point<steady_clock, duration<__int64, std::ratio<1, 1000000000>>> editor_time = high_resolution_clock::now();
    time_point<steady_clock, duration<__int64, std::ratio<1, 1000000000>>> editor_screen_time = high_resolution_clock::now();
    time_point<steady_clock, duration<__int64, std::ratio<1, 1000000000>>> editor_last_time = high_resolution_clock::now();
    bool editor_enabled = enabler;

    while (editor_enabled)
    {
        editor_time = high_resolution_clock::now();

        //cursor flasher (once a second)
        if ((float)duration_cast<milliseconds>(editor_time - editor_last_time).count() >= 1000.00000f)
        {
            editor_last_time = high_resolution_clock::now();

            editor->cursor_flash();
        }

        keyboard.keyboard_key_left();
        keyboard.keyboard_key_right();
        keyboard.keyboard_key_del();
        keyboard.keyboard_key_esc();

        switch (keyboard.get_key())
        {
        case VK_LEFT:
            if (editor->m_selector > 0)
            {
                editor->m_selector--;
            }
            else
            {
                editor->m_selector = cust_planets.get_vec_coord_size() - 1;
            }

            editor->set_grid(screen);
            editor->m_cursor_visible = true;
            editor->cursor_flash();
            editor_last_time = high_resolution_clock::now();
            break;
        case VK_RIGHT:
            if (editor->m_selector < cust_planets.get_vec_coord_size() - 1)
            {
                editor->m_selector++;
            }
            else
            {
                editor->m_selector = 0;
            }

            editor->set_grid(screen);
            editor->m_cursor_visible = true;
            editor->cursor_flash();
            editor_last_time = high_resolution_clock::now();
            break;
        case VK_DELETE:
            editor->delete_selected();
            screen->refresh_grid();
            screen->set_all_objects(cust_planets);
            editor->set_grid(screen);

            if (!(editor->m_selector > 0 && editor->m_selector < cust_planets.get_vec_coord_size() - 1))
            {
                editor->m_selector = 0;
            }
            break;
        case VK_ESCAPE:
            editor->set_grid(screen);
            editor_screen_time = high_resolution_clock::now();
            editor_enabled = false;
            break;
        default:
            break;
        }

        keyboard.reset_keys();

        if ((float)duration_cast<milliseconds>(editor_time - editor_screen_time).count() >= 16.66666f)
        {
            editor_screen_time = high_resolution_clock::now();
            editor->print_grid_editor();
        }
    }
}






int main()
{
    vector<string> welcome_screen;
    bool welcome_screen_fine = true;
    size_t line_pos;
    welcome_screen = grid_setter(15, 51);   //13 lines and 51 characters

    for (size_t y = 0; y < welcome_screen.size(); y++)
    {
        for (size_t x = 0; x < welcome_screen.at(y).size(); x++)
        {
            if (!((y > 0) && (y < (welcome_screen.size() - 1))))
            {
                welcome_screen[y][x] = SYMBOL_WALL;
            }
            else if (!((x > 0) && (x < (welcome_screen.at(y).size() - 1))))
            {
                welcome_screen[y][x] = SYMBOL_WALL;
            }
        }
    }

    line_pos = 2;
    welcome_screen.at(line_pos) = line_setter(welcome_screen.at(line_pos), "             Planets Orbit Simulator             ");
    line_pos = 3;
    welcome_screen.at(line_pos) = line_setter(welcome_screen.at(line_pos), "                  text edition                   ");
    line_pos = 4;
    welcome_screen.at(line_pos) = line_setter(welcome_screen.at(line_pos), "         planets physics by 'mattebert88'        ");
    line_pos = 5;
    welcome_screen.at(line_pos) = line_setter(welcome_screen.at(line_pos), "_________________________________________________");
    line_pos = 9;
    welcome_screen.at(line_pos) = line_setter(welcome_screen.at(line_pos), " Please set your cmd font to 'Raster' 8x8!!!     ");
    line_pos = 11;
    welcome_screen.at(line_pos) = line_setter(welcome_screen.at(line_pos), " Please select desired grid dimensions.          ");
    line_pos = 12;
    welcome_screen.at(line_pos) = line_setter(welcome_screen.at(line_pos), " 119x119 is optimal for 1080p screens:           ");

    if (welcome_screen_fine)
    {
        size_t width;
        size_t height;
        float speed_multiplier;
        float physics_speed = 10000.00000f; //refresh every 10ms
        bool editor_enabled = false;

        while (true)
        {
            system("CLS");

            for (size_t i = 0; i < welcome_screen.size(); i++)
            {
                cout << welcome_screen.at(i) << endl;
            }

            cout << endl;
            cout << "X: ";
            cin >> width;
            cout << "\nY: ";
            cin >> height;
            cout << "\nRealtime speed 'float'.\n1 = normal speed, >1 = faster speed\n\nMultiplier: ";
            cin >> speed_multiplier;
            //speed_multiplier /= 1000.00000f;   //ns
            system("CLS");
            cout << endl;

            grid_screen* p_screen = new grid_screen(width, height);
            Planets custom_planets;
            planets_editor editor;
            keyboard_keys keyboard;

            custom_planets.AddPoint((float)(width / 2.0f), (float)(width / 2.0f), 0.0f, 0.0f, 80.0f, true);
            custom_planets.AddPoint((float)(width / 2.0f) + 5.0f, (float)(width / 2.0f) + 5.0f, -2.0f, 1.0f, 40.0f, false);
            custom_planets.AddPoint((float)(width / 2.0f) - 5.0f, (float)(width / 2.0f) - 5.0f, 1.0f, -2.0f, 40.0f, false);
            custom_planets.AddPoint((float)(width / 2.0f) - 3.0f, (float)(width / 2.0f) - 3.0f, 1.0f, -2.0f, 0.1f, false);

            time_point<steady_clock, duration<__int64, std::ratio<1, 1000000000>>> current_time = high_resolution_clock::now();
            time_point<steady_clock, duration<__int64, std::ratio<1, 1000000000>>> physics_time = high_resolution_clock::now();
            time_point<steady_clock, duration<__int64, std::ratio<1, 1000000000>>> screen_time = high_resolution_clock::now();
            time_point<steady_clock, duration<__int64, std::ratio<1, 1000000000>>> editor_time = high_resolution_clock::now();
            time_point<steady_clock, duration<__int64, std::ratio<1, 1000000000>>> editor_screen_time = high_resolution_clock::now();

            while (p_screen->get_in_grid_status())
            {
                current_time = high_resolution_clock::now();
                const float time_elapsed = (float)duration_cast<nanoseconds>(current_time - physics_time).count();

                //refresh rate of calculation update
                if ((float)duration_cast<nanoseconds>(current_time - physics_time).count() >= physics_speed)
                {
                    physics_time = high_resolution_clock::now();
                    p_screen->refresh_grid();
                    custom_planets.NextTimeInterval((time_elapsed * speed_multiplier) / 1000000000.00000f); //dividing by 1000000000 converts time_elapsed from nanoseconds to seconds

                    //update planets location in screen grid
                    /*
                    for (size_t i = 0; i < custom_planets.get_vec_coord_size(); i++)
                    {
                        p_screen->set_object(custom_planets, i, i);
                    }
                    */
                    p_screen->set_all_objects(custom_planets);
                }

                //refresh rate of screen rendering (16.66666 = around 60fps. 16.66666 * 60 = 999ms)
                if ((float)duration_cast<milliseconds>(current_time - screen_time).count() >= 16.66666f)
                {
                    screen_time = high_resolution_clock::now();
                    p_screen->print_grid();
                }

                keyboard.keyboard_key_e();

                if (keyboard.get_key() == VK_L_E)
                {
                    editor_enabled = true;
                    editor.set_grid(p_screen);
                    editor.set_planets_shortcut(&custom_planets);
                    keyboard.reset_keys();
                }

                while (editor_enabled)
                {
                    editor_time = high_resolution_clock::now();

                    keyboard.keyboard_key_alt();
                    keyboard.keyboard_key_up();
                    keyboard.keyboard_key_down();
                    keyboard.keyboard_key_left();
                    keyboard.keyboard_key_right();
                    keyboard.keyboard_key_del();
                    keyboard.keyboard_key_esc();

                    switch (keyboard.get_key())
                    {
                    case VK_MENU:
                        editor_basic(&editor, keyboard, custom_planets, p_screen, true);
                        break;
                    case VK_UP:
                        if (editor.m_selector_y > 0)
                        {

                        }
                        break;
                    case VK_DOWN:
                        if (editor.m_selector_y < editor.get_height() - 1)
                        {

                        }
                        break;
                    case VK_LEFT:
                        if (editor.m_selector_x > 0)
                        {

                        }
                        break;
                    case VK_RIGHT:
                        if (editor.m_selector_x > editor.get_width() - 1)
                        {

                        }
                        break;
                    case VK_DELETE: //works only for planets directly on grid based on size_t
                        break;
                    case VK_ESCAPE:
                        editor_enabled = false;
                        physics_time = high_resolution_clock::now();
                        break;
                    default:
                        break;
                    }
                    
                    keyboard.reset_keys();

                    if ((float)duration_cast<milliseconds>(editor_time - editor_screen_time).count() >= 16.66666f)
                    {
                        editor_screen_time = high_resolution_clock::now();
                        editor.print_grid_editor();
                    }
                }
            }

            if (p_screen != nullptr)
            {
                delete p_screen;
                p_screen = nullptr;
            }
        }
    }

    return 0;
}