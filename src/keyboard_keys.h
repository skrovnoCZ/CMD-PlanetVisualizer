#ifndef __KEYBOARD_KEYS__
#define __KEYBOARD_KEYS__

#include <Windows.h>
//#include <map>

#define VK_L_E 0x45 //key E (missing in Windows.h)
#define VK_L_I 0x49 //key I (missing in Windows.h)
/*
std::map<std::string, std::function<void(bool)>>functions;

void command_greet(bool new_input);
void command_add(bool new_input);
void command_help(bool new_input);

void commands()
{
    functions["hi"] = command_greet;  //command
    functions["add"] = command_add;   //command
    functions["help"] = command_help; //command
}
*/
class keyboard_keys
{
private:
    bool m_key_up;      //variable to prevent holding keyboard key
    bool m_key_down;    //variable to prevent holding keyboard key
    bool m_key_left;    //variable to prevent holding keyboard key
    bool m_key_right;   //variable to prevent holding keyboard key
    bool m_key_e;       //variable to prevent holding keyboard key
    bool m_key_alt;     //variable to prevent holding keyboard key
    bool m_key_i;       //variable to prevent holding keyboard key
    bool m_key_control; //variable to prevent holding keyboard key
    bool m_key_enter; //variable to prevent holding keyboard key
    bool m_key_escape;  //variable to prevent holding keyboard key
    bool m_key_minus;  //variable to prevent holding keyboard key
    bool m_key_plus;  //variable to prevent holding keyboard key
    bool m_key_del;  //variable to prevent holding keyboard key
    int m_key;          //variable to prevent holding keyboard key
public:
    keyboard_keys();
    void keyboard_key_up();
    void keyboard_key_down();
    void keyboard_key_left();
    void keyboard_key_right();
    void keyboard_key_e();
    void keyboard_key_alt();
    void keyboard_key_i();
    void keyboard_key_ctrl();
    void keyboard_key_enter();
    void keyboard_key_esc();
    void keyboard_key_minus();
    void keyboard_key_plus();
    void keyboard_key_del();
    void reset_keys();
    int get_key();
    ~keyboard_keys();
};

#endif