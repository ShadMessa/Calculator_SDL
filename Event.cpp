#include "Event.h"

using namespace std;
using namespace SDL;

/**************************************************Constructor***************************************************************/

Event_Mouse::Event_Mouse() : x(0),y(0)
{
    Get_Activ_Evet();
}

Event_Keyboard::Event_Keyboard() : Tab(NULL),num(0)
{
    Get_Activ_Evet();
}

Event_Window::Event_Window()
{
    SDL_GetEventState(SDL_WINDOWEVENT);
}
/***********************************************De-constructor***************************************************************/

Event_Mouse::~Event_Mouse()
{
    //dtor
}

Event_Keyboard::~Event_Keyboard()
{
    //dtor
}

Event_Window::~Event_Window()
{
    //dtor
}

/********************************************Assessors_Functions_&_Methodes***************************************************/

void Event_Mouse::Get_Activ_Evet()
{
    SDL_GetMouseState(&x,&y);
}

bool Event_Mouse::Is_RightKey_Active()
{
    if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3)) return 1;
    else return 0;
}

bool Event_Mouse::Is_LeftKey_Active()
{
    if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) return 1;
    else return 0;
}
bool Event_Mouse::Is_MiddleKey_Active()
{
    if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(2)) return 1;
    else return 0;
}
bool Event_Mouse::is_AnyKey_Up()
{
    if(SDL_HasEvent(SDL_MOUSEBUTTONUP)) return 1;
    else return 0;
}
bool Event_Mouse::is_AnyKey_Down()
{
    if(SDL_HasEvent(SDL_MOUSEBUTTONDOWN)) return 1;
    else return 0;
}
void Event_Keyboard::Get_Activ_Evet()
{
    Tab=SDL_GetKeyboardState(&num);
}
bool Event_Keyboard::Is_Key_Active(SDL_Keycode SDL_Key)
{
    return Tab[SDL_GetScancodeFromKey(SDL_Key)];
}
bool Event_Keyboard::is_AnyKey_Up()
{
    if(SDL_HasEvent(SDL_KEYUP)) return 1;
    else return 0;
}
bool Event_Keyboard::is_AnyKey_Down()
{
    if(SDL_HasEvent(SDL_KEYDOWN)) return 1;
    else return 0;
}
bool Event_Window::Get_Quit_Event()
{
    if(SDL_QuitRequested()==SDL_TRUE) return true;
    else return false;
}
