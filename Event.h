#ifndef EVENT_H
#define EVENT_H

#include<SDL2/SDL.h>
#include<iostream>

namespace SDL
{

class Event_Mouse
{
public:

    Event_Mouse();
    ~Event_Mouse();
    void Get_Activ_Evet();
    int inline Get_X_Pos()  //\todo il faut chager se nom Abscise en anglais
    {
        return x;
    }
    int inline Get_Y_Pos()  //\todo il faut changer se nom ordonne en anglais
    {
        return y;
    }
    bool Is_RightKey_Active();
    bool Is_LeftKey_Active();
    bool Is_MiddleKey_Active();
    bool is_AnyKey_Up();
    bool is_AnyKey_Down();

private:
    int x,y;

} ;

class Event_Keyboard
{
public:

    Event_Keyboard();
    ~Event_Keyboard();
    void Get_Activ_Evet();
    bool Is_Key_Active(SDL_Keycode SDL_Key);
    bool is_AnyKey_Up();
    bool is_AnyKey_Down();

private:
    const Uint8 *Tab;
    int num;

};
class Event_Window
{
public:

    Event_Window();
    ~Event_Window();
    void Get_Activ_Evet();
    bool Get_Quit_Event();

private:

};

}
#endif // EVENT_H
