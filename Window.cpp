#include "Window.h"

using namespace std ;
using namespace SDL ;

/**************************************************Constructor***************************************************************/

Window::Window(string const Name_of_the_Window,unsigned int h,unsigned int w) :High(1),Width(1),MH(0),MW(0),mH(0),mW(0)
{
    Name =Name_of_the_Window;
    try
    {

        if(SDL_Init(SDL_INIT_EVERYTHING)<0)
        {
            throw string ("SDL initialization failed !");
        }

        if(w<10)Width=10;
        else Width=w;
        if(h<10)High=10;
        else High=h;
        Window_SDL = SDL_CreateWindow(Name.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Width,High,NULL);

        if(Window_SDL==NULL)
        {
            throw string ("Windows creation !");
        }

        Render=SDL_CreateRenderer(Window_SDL,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

        if(Render==NULL)
        {
            throw string ("Renderer creation !");
        }

        SDL_RenderPresent(Render);

    }
    catch(string const& e)
    {
        cerr<<"Error : "<<e<<endl;
        cerr<<"Error : "<<SDL_GetError()<<endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Fatal Error","Initialization failed !",Window_SDL);
        SDL_Quit();
    }
}

Window_App::Window_App(string const Name_of_the_Window,unsigned int h,unsigned int w) //\todo alors il y a un problème la fenêtre se crée en deux fois une petite puis une plus grande a la résolution voulue enfin je croit a vérifier
{ // cette class devrait crée une fenêtre a dimension non fixe donc pas besoin de paramètre pour sa résolution
    try
    {
    Name = Name_of_the_Window;

        if(SDL_Init(SDL_INIT_EVERYTHING)<0)
        {
            throw string ("SDL initialization failed !");
        }
        else
        {
            SDL_QuitSubSystem(SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER|SDL_INIT_HAPTIC);
        }

        if(w<10)Width=10;
        else Width=w;
        if(h<10)High=10; //non nécessaire
        else High=h;
    Window_SDL=SDL_CreateWindow(Name_of_the_Window.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Width,High,SDL_WINDOW_RESIZABLE);
        if(Window_SDL==NULL)
        {
            throw string ("Windows creation !");
        }

        Render=SDL_CreateRenderer(Window_SDL,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

        if(Render==NULL)
        {
            throw string ("Renderer creation !");
        }
                int i,num=SDL_GetNumDisplayModes(0);
        SDL_DisplayMode DM;
        if(num<0)
        {
            throw string("No Display Mode found !");
        }
        else
        {
            SDL_GetDisplayMode(0,0,&DM);
            MH=DM.h;
            MW=DM.w;
            mH=DM.h;
            mW=DM.w;
            for(i=1; i<=num; i++)
            {
                cout<<"min high "<<mH<<" min width "<<mW<<endl;
                SDL_GetDisplayMode(0,i,&DM);
                if(MH<DM.h)MH=DM.h;
                if(MW<DM.w)MW=DM.w;
                if(mH>DM.h)mH=DM.h;
                if(mW>DM.w)mW=DM.w;
            }
            //SDL_SetWindowMaximumSize(Window_SDL,) //\todo ceci devré contenire la résolution maximum mais mieu vaudré utilisé la résolution actuel de lécrant

            SDL_SetWindowMinimumSize(Window_SDL,mW,mH);
        }
        SDL_RenderPresent(Render);

    }
    catch(string const& e)
    {
        cerr<<"Error : "<<e<<endl;
        cerr<<"Error : "<<SDL_GetError()<<endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Fatal Error","Initialization failed !",Window_SDL);
        SDL_Quit();
    }
}

Window_Game::Window_Game(string const Name_of_the_Window)
{
    Width=Config_Window.Get_Width(); //\todo refaire la gestion des resolution de la fennetre utiliser SDL_GetDisplayMode pour avoir tous les mode disponnible
    High=Config_Window.Get_High();
    Name =Name_of_the_Window;
    try
    {
        if(SDL_Init(SDL_INIT_EVERYTHING)<0)
        {
            throw string ("SDL initialization failure !");
        }
        int i,num=SDL_GetNumDisplayModes(0);
        SDL_DisplayMode DM;
        if(num<0)
        {
            throw string("No Display Mode found !");
        }
        else
        {
            SDL_GetDisplayMode(0,0,&DM);
            MH=DM.h;
            MW=DM.w;
            mH=DM.h;
            mW=DM.w;
            for(i=1; i<=num; i++)
            {
                SDL_GetDisplayMode(0,i,&DM);
                if(MH<DM.h)MH=DM.h;
                if(MW<DM.w)MW=DM.w;
                if(mH>DM.h)mH=DM.h;
                if(mW>DM.w)mW=DM.w;
            }
        }
        //\todo keep working the size of this window must be one of these

        Window_SDL = SDL_CreateWindow(Name.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Width,High,
                                      SDL_WINDOW_RESIZABLE|Config_Window.Get_Param_Fullscrean());

        if(Window_SDL==NULL)
        {
            throw string ("Windows creation !");
        }

        Render=SDL_CreateRenderer(Window_SDL,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

        if(Render==NULL)
        {
            throw string ("Renderer creation !");
        }

        SDL_RenderPresent(Render);

    }
    catch(string const& e)
    {
        cerr<<"Error : "<<e<<endl;
        cerr<<"Error : "<<SDL_GetError()<<endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Fatal Error","Initialization failure !",Window_SDL);
        SDL_Quit();
    }
}

/***********************************************De-constructor***************************************************************/

Window::~Window()
{
    SDL_DestroyRenderer(Render);
    SDL_DestroyWindow(Window_SDL);
    SDL_Quit();
}
Window_App::~Window_App()
{

}
Window_Game::~Window_Game()
{

}

/********************************************Assessors_Functions_&_Methodes***************************************************/
Window * Window::Get_Adresse()
{
    return this;
}
SDL_Window * Window::Get_Window()
{
    return Window_SDL;
}
void Window::Set_Events()
{
    SDL_PumpEvents();
}

