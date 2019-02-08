#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED
#include <SDL2/SDL.h>
#include "Config.h"

namespace SDL //The SDL name space contain all the class created by SDL basic functions
{

class Window
{
public:
    Window(std::string const Name_of_the_Window="No_Name",unsigned int h=10,unsigned int w=10);
    virtual ~Window();
    inline unsigned int  Get_High()
    {
        return High;
    }
    inline unsigned int  Get_Width()
    {
        return Width;
    }
    inline void Show_Render()
    {
        SDL_RenderPresent(Render);
    }
    void Set_Events();
    SDL_Window * Get_Window();
    inline SDL_Renderer * Get_Renderer()
    {
        return Render;
    }
    Window * Get_Adresse();

protected:
    SDL_Window *Window_SDL;
    SDL_Renderer *Render;
    std::string Name;
    unsigned int High,Width;
    unsigned int MH,MW,mH,mW;

};

class Window_App : public Window
{
public:
    Window_App(std::string const Name_of_the_Window,unsigned int h,unsigned int w);
    virtual ~Window_App();
private:

};

class Window_Game : public Window //\todo what about the cursor make it bunden
{
public:
    Window_Game(std::string Name_of_the_Window);
    virtual ~Window_Game();
//\todo ajouter une methode pour changer la taille de la fenetre

private:

    Config Config_Window;
};

}

#endif // WINDOW_H_INCLUDED
