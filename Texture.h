#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <math.h>
#include "Window.h"

namespace SDL
{

class Texture// \todo il faut trouver un moyen pour crée un tableau de Texture cela en créent des constructeur sans ou avec paramètre par défaut
{
public:
    Texture();
    Texture(Window &A);
    virtual ~Texture();
    void Create_Texture_Unicolour(int Red,int Green,int Blue); // create a texture whit a unique color

    inline void  RenderCopy_Texture(unsigned int x=0,unsigned int y=0,unsigned int w=0,unsigned int h=0) // make the texture appear in a position on screen
    {
        cd_rsrect.x=x;
        if(x>Window_of_texture->Get_Width())cd_rsrect.w=0;
        cd_rsrect.y=y;
        if(y>Window_of_texture->Get_High())cd_rsrect.w=0;
        cd_rsrect.w=w;
        if(cd_rsrect.w==0)cd_rsrect.w=Window_of_texture->Get_Width();
        cd_rsrect.h=h;
        if(cd_rsrect.h==0)cd_rsrect.h=Window_of_texture->Get_High();
        if(SDL_RenderCopy(Window_of_texture->Get_Renderer(),Texture_SDL,NULL,&cd_rsrect)!=0)
        {
            std::cerr<<"Texture::RenderCopy_Texture = "<<SDL_GetError()<<std::endl;
        }
    }

    inline void  RenderCopy_Texture_Part(unsigned int x=0, unsigned int y=0,unsigned int w=0,unsigned int h=0) // make a part of the texture appear in a position on screen
    {
        cd_rsrect.x=x;
        if(x>Window_of_texture->Get_Width())cd_rsrect.x=0;
        cd_rsrect.y=y;
        if(y>Window_of_texture->Get_High())cd_rsrect.y=0;
        if(w==0||w>Window_of_texture->Get_Width()-x)
        {
            cd_rsrect.w=cs_rsrect.w;
        }
        else cd_rsrect.w=w;
        if(h==0||h>Window_of_texture->Get_High()-y)
        {
            cd_rsrect.h=cs_rsrect.h;
        }
        else cd_rsrect.h=h;
        if(SDL_RenderCopy(Window_of_texture->Get_Renderer(),Texture_SDL,&cs_rsrect,&cd_rsrect)!=0)
        {
            std::cerr<<"Texture::RenderCopy_Texture = "<<SDL_GetError()<<std::endl;
        }
    }

    inline void  Set_Alpha(Uint8 A)
    {
        Alpha=A;
        SDL_SetTextureAlphaMod(Texture_SDL,Alpha);
    }

    void  Set_Size(unsigned int x,unsigned int y,unsigned int Width,unsigned int High);

    inline unsigned int Get_High()
    {
        return high;
    }

    inline unsigned int Get_Width()
    {
        return width;
    }
    void Set_WindowInUse(Window &A);

protected:
    SDL_Texture *Texture_SDL;
    Window *Window_of_texture;
    SDL_Rect cd_rsrect,cs_rsrect;
    int high,width;
    Uint8 Alpha;
};

class TextureText : public Texture
{
public:
    TextureText();
    TextureText(Window &A);
    TextureText(Window &A,const std::string TTF_File_Path,const std::string Text,int Taille_Police,Uint8 red,Uint8 green,Uint8 blue);
    virtual ~TextureText();
    void Create_Texture_From_Text(const std::string TTF_File_Path,const std::string Text,int Taille_Police,Uint8 red,Uint8 green,Uint8 blue); // In Progress
    void Scrol_Horiz(int x,int y,Texture &Background,bool direction);
    void Scrol_Vertic(int x,int y,Texture &Background,bool direction);

private:
    int Text_size;
};

class TextureImage : public Texture
{
public:
    TextureImage();
    TextureImage(Window &A);
    TextureImage(Window &A,const std::string File_Path);
    virtual ~TextureImage();
    void Create_Texture_From_File(const std::string File_Path); // create a texture from a file in the HDD (picture)
    void Alpha_Flode_ext(int x=0,int y=0,int w=0,int h=0); // make a texture appear whit an alpha blend mode effect
    void Alpha_Flode_cnt(float proportion=1); // make a texture appear whit an alpha blend mode effect within a centered area
    void Zoom_Alpha_Flode(); // make a texture appear whit a zoom and an alpha blend mode effect
};

}
#endif // TEXTURE_H
