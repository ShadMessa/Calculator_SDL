#include "Texture.h"

using namespace std; //\todo verify the returned value of every SDL function use SDL_GetError
using namespace SDL;

/***********************************************Prototype**************************************************************/

static string Cast_int_string (int n);
static string Convert_to_bin (int num);
static int Cast_binString_int (string &temp);

/*********************************************Constructor**************************************************************/
Texture::Texture() : Texture_SDL(NULL),high(0),width(0),Alpha(255)
{
    cd_rsrect= {0,0,0,0};
    cs_rsrect= {0,0,0,0};
    Window_of_texture=NULL;
}
Texture::Texture(Window &A) : Texture_SDL(NULL),high(0),width(0),Alpha(255)
{
    cd_rsrect= {0,0,0,0};
    cs_rsrect= {0,0,0,0};
    Window_of_texture=A.Get_Adresse();
}
TextureText::TextureText()
{
    high=0;
    width=0;
    Alpha=255;
    Texture_SDL=NULL;
    cd_rsrect= {0,0,0,0};
    cs_rsrect= {0,0,0,0};
    Window_of_texture=NULL;
}
TextureText::TextureText(Window &A) : Texture::Texture(A),Text_size(0)
{

}
TextureText::TextureText(Window &A,const std::string TTF_File_Path,const std::string Text,int Taille_Police,Uint8 red,Uint8 green,Uint8 blue) : TextureText::TextureText(A)
{
    Create_Texture_From_Text(TTF_File_Path,Text,Taille_Police,red,green,blue);
}
TextureImage::TextureImage()
{
    high=0;
    width=0;
    Alpha=255;
    Texture_SDL=NULL;
    cd_rsrect= {0,0,0,0};
    cs_rsrect= {0,0,0,0};
    Window_of_texture=NULL;
}
TextureImage::TextureImage(Window &A) : Texture::Texture(A)
{

}
TextureImage::TextureImage(Window &A,const std::string File_Path) : TextureImage::TextureImage(A)
{
    Create_Texture_From_File(File_Path);
}

/********************************************De-constructor************************************************************/

Texture::~Texture()
{
    SDL_DestroyTexture(Texture_SDL);
}
TextureText::~TextureText()
{

}
TextureImage::~TextureImage()
{

}

/*********************************************Texture_Creation********************************************************/

void Texture::Create_Texture_Unicolour(int Red,int Green,int Blue)
{
    string temp,red,green,blue,alpha;
    Uint32 Format_Pixel,i;
    Uint32 * pixels=NULL;
Second_Chance:
    temp="";
    red="";
    blue="";
    alpha="11111111";
    Format_Pixel=0;
    i=0;
    try
    {
        if (Window_of_texture==NULL) throw string("Window in use not set !");
        Texture_SDL=SDL_CreateTexture(Window_of_texture->Get_Renderer(),SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING
                                      ,Window_of_texture->Get_Width(),Window_of_texture->Get_High());
        /**////********************Algorithm_NOS2****************************************************************/
        /**/
        /**/         pixels = new Uint32[Window_of_texture->Get_Width() * Window_of_texture->Get_High()];
        /**/
        /**/           red   = Convert_to_bin(Red);
        /**/           green = Convert_to_bin(Green);
        /**/           blue  = Convert_to_bin(Blue);
        /**/           temp=alpha+red+green+blue;  // define the format by moving the parameters
        /**/           Format_Pixel=Cast_binString_int(temp); //todo repair accuracy lose
        /**/            for(i=0; i<=(Window_of_texture->Get_Width() * Window_of_texture->Get_High())-1; i++) // Filling the Uint32 Pixels
        /**/                {
        /**/                pixels[i]=Format_Pixel;
        /**/                }
        /**////**************************************************************************************************/

        SDL_UpdateTexture(Texture_SDL, NULL, pixels, Window_of_texture->Get_Width() * sizeof(Uint32));

        cout<<SDL_GetError()<<endl;
        if(Texture_SDL==NULL)
        {
            throw string("Can't create texture whit uniform color!");
        }
        delete []pixels;
        width=Window_of_texture->Get_Width();
        cs_rsrect.w=width;
        high=Window_of_texture->Get_High();
        cs_rsrect.h=high;
        SDL_SetTextureBlendMode(Texture_SDL,SDL_BLENDMODE_BLEND);
    }
    catch (string &error)
    {
        cerr<<"Error : "<<error<<" "<<this<<endl;
        cerr<<"Texture::Create_Texture_Unicolour = "<<SDL_GetError()<<endl;
        delete []pixels;
        if(error=="Wrong texture color parameter !")
        {
            goto Second_Chance;

        }
    }
}

void TextureImage::Create_Texture_From_File(const string File_Path)
{
    try
    {
        if (Window_of_texture==NULL) throw string("Window in use not set !");
        if(File_Path.c_str()==NULL)
        {
            throw string("File path corrupt !");
        }
        Texture_SDL=IMG_LoadTexture(Window_of_texture->Get_Renderer(),File_Path.c_str());
        if(Texture_SDL==NULL)
        {
            throw string("Can't create texture from file !");
        }
        else
        {
            if(SDL_QueryTexture(Texture_SDL,NULL,NULL,&width,&high)!=0)
            {
                throw string("QueryTexture could not get revolution ! ");
            }
            else
            {
                cs_rsrect.w=width;
                cs_rsrect.h=high;
            }
            SDL_SetTextureBlendMode(Texture_SDL,SDL_BLENDMODE_BLEND);
        }
    }
    catch(string &error)
    {
        cerr<<"Error : "<<error<<endl;
        error=error+" "+File_Path;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"File fail",error.c_str(),Window_of_texture->Get_Window());
    }
}

void TextureText::Create_Texture_From_Text(const std::string TTF_File_Path,const std::string Text,int Taille_Police,Uint8 red,Uint8 green,Uint8 blue) // In Progress
{
    red=red%256;
    blue=blue%256;
    green=green%256;
    try
    {
        if (Window_of_texture==NULL) throw string("Window in use not set !");
        if(TTF_Init()!=0)
        {
            throw string ("Can't initialize TTF !");
        }
        TTF_Font *Police= TTF_OpenFont(TTF_File_Path.c_str(), Taille_Police);
        if(Police==NULL)
        {
            throw string ("TTF file not found !");
        }
        SDL_Color Couleur= {red,green,blue,this->Alpha};
        SDL_Surface *Temp;
        Temp=TTF_RenderText_Blended(Police,Text.c_str(),Couleur);
        SDL_free(Texture_SDL);
        Texture_SDL=SDL_CreateTextureFromSurface(Window_of_texture->Get_Renderer(),Temp);

        TTF_CloseFont(Police);
        SDL_FreeSurface(Temp);
        TTF_Quit();

        if(Texture_SDL==NULL)
        {
            throw string("Error in TTF !");
        }
        else
        {
            if(SDL_QueryTexture(Texture_SDL,NULL,NULL,&width,&high)!=0)
            {
                throw string("QueryTexture could not get revolution ! ");
            }
            else
            {
                cs_rsrect.w=width;
                cs_rsrect.h=high;
            }
            SDL_SetTextureBlendMode(Texture_SDL,SDL_BLENDMODE_BLEND);
        }

    }
    catch(string &e)
    {
        cerr<<"ERROR :"<<e<<endl;
        e=e+" "+TTF_File_Path;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"TTF ERROR",e.c_str(),Window_of_texture->Get_Window());

    }
}

/**********************************************Effect_function*********************************************************/

void TextureImage::Alpha_Flode_ext(int x,int y,int w,int h) // \todo make this function work correctly and so on plus how to make a portion of it appear alone
{
    SDL_Rect position;
    position.x=x;
    position.y=y;
    position.w=w;
    position.h=h;
    try
    {

    if(Texture_SDL==0)
    {
        throw string("The Texture was not filled yet !");
    }
    SDL_SetTextureBlendMode(Texture_SDL,SDL_BLENDMODE_BLEND);
        if (Window_of_texture==NULL) throw string("Window in use not set !");
        int i;
        for(i=0; i<225; i++)
        {
            SDL_Delay(10);
            SDL_SetTextureAlphaMod(Texture_SDL,i);
            SDL_RenderCopy(Window_of_texture->Get_Renderer(),Texture_SDL,NULL,&position);
            SDL_RenderPresent(Window_of_texture->Get_Renderer());
        }
    }
    catch(string &error)
    {
        cerr<<"ERROR : "<<error<<endl;

    }

}

void TextureImage::Alpha_Flode_cnt(float  proportion)
{
    int cptn=0;
    while(proportion>1)
    {
        cptn++;
        if(proportion>1)
        {
            proportion/=2;
        }
        if(cptn>100)
        {
            proportion=1;
            break;
        }
    }
    try
    {

    SDL_Rect position;

    if (Window_of_texture==NULL) throw string("Window in use not set !");
    position.w=Window_of_texture->Get_Width()*proportion;
    position.h=Window_of_texture->Get_High()*proportion;
    position.x=Window_of_texture->Get_Width()/2-position.w/2;
    position.y=Window_of_texture->Get_High()/2-position.h/2;


    if(Texture_SDL==0)
    {
        throw string("The Texture was not filled yet !");
    }
    SDL_SetTextureBlendMode(Texture_SDL,SDL_BLENDMODE_BLEND);
        int i;
        for(i=0; i<225; i++)
        {
            SDL_Delay(10);
            SDL_SetTextureAlphaMod(Texture_SDL,i);
            SDL_RenderCopy(Window_of_texture->Get_Renderer(),Texture_SDL,NULL,&position);
            SDL_RenderPresent(Window_of_texture->Get_Renderer());
        }
    }
    catch(string &error)
    {
        cerr<<"ERROR : "<<error<<endl;
    }

}

void TextureImage::Zoom_Alpha_Flode()
{
    try
    {

    if (Window_of_texture==NULL) throw string("Window in use not set !");
    if(Texture_SDL==0)
    {
        throw string("The Texture was not filled yet !");
    }
    SDL_SetTextureBlendMode(Texture_SDL,SDL_BLENDMODE_BLEND);

        int i,w=70,h=100;

        for(i=0; i<128; i++)
        {
            SDL_Delay(10);
            SDL_SetTextureAlphaMod(Texture_SDL,i);
            RenderCopy_Texture(Window_of_texture->Get_Width()/2-w/2,Window_of_texture->Get_High()/2-h/2,w,h);
            Window_of_texture->Show_Render();

            w++;
            h++;
        }
        for(i=128; i>2; i--)
        {
            SDL_Delay(10);
            SDL_SetTextureAlphaMod(Texture_SDL,i);
            RenderCopy_Texture(Window_of_texture->Get_Width()/2-w/2,Window_of_texture->Get_High()/2-h/2,w,h);
            Window_of_texture->Show_Render();
            w++;
            h++;
        }
    }
    catch(string &error)
    {
        cerr<<"ERROR : "<<error<<endl;

    }

}

void TextureText::Scrol_Horiz(int x,int y,Texture &Background,bool direction) // \todo i have to erase the previous blit before blit it again
{
    int i;
    if(direction)
    {
        for(i=-cd_rsrect.w; i<=x-(cd_rsrect.w/2); i++)
        {
            Background.RenderCopy_Texture(i,y,cd_rsrect.w,cd_rsrect.h);
            RenderCopy_Texture(i,y,cd_rsrect.w,cd_rsrect.h);
            SDL_Delay(25);
            i=i+4;
        }
    }
    else
    {
        for(i=Window_of_texture->Get_Width(); i>=x-(cd_rsrect.w/2); i--)
        {
            Background.RenderCopy_Texture(i,y,cd_rsrect.w,cd_rsrect.h);
            RenderCopy_Texture(i,y,cd_rsrect.w,cd_rsrect.h);
            SDL_Delay(25);
            i=i+4;
        }
    }


}

/**********************************************Other_function***********************************************************/

static string Cast_int_string (int n)
{
    if(n<0)
    {
        n=n*-1;
    }
    if(n>=256)
    {
        n=n%256;
    }

    int i,temp=0;
    string s_temp="",chifre="";
    for(i=3; i>=1; i--)
    {
        if(i==3)
        {
            temp=(n-n%100)/100;
        }
        if(i==2)
        {
            temp=(n%100-n%10)/10;
        }
        if(i==1)
        {
            temp=n%10;
        }

        switch(temp)
        {
        case 0:
            s_temp="0";
            break;
        case 1:
            s_temp="1";
            break;
        case 2:
            s_temp="2";
            break;
        case 3:
            s_temp="3";
            break;
        case 4:
            s_temp="4";
            break;
        case 5:
            s_temp="5";
            break;
        case 6:
            s_temp="6";
            break;
        case 7:
            s_temp="7";
            break;
        case 8:
            s_temp="8";
            break;
        case 9:
            s_temp="9";
            break;
        default:
            break;
        }
        chifre=chifre+s_temp;
    }
    return chifre.c_str();
}

static int Cast_binString_int (string &temp)
{
    int unsigned i=0;
    int chifre=0;
    for(i=0; i<=temp.length()-1; i++)
    {
        if(temp[i]=='1')
        {
            chifre=chifre+pow(2,temp.length()-1-i);
        }
    }
    return chifre;
}

static string Convert_to_bin (int num)
{
    int i=0;
    string temp="",bin_num="";
    while(num!=0)
    {
        if(num%2)
        {
            temp=temp+"1";
        }
        else
        {
            temp=temp+"0";
        }
        num=num/2;
    }
    while(temp.length()<8)
    {
        temp=temp+"0";
    }
    for(i=temp.length()-1; i>=0; i--)
    {
        bin_num=bin_num+temp[i];
    }
    return bin_num.c_str();
}

void Texture::Set_Size(unsigned int x,unsigned int y,unsigned int Width,unsigned int High)
{
    try
    {
        if(x>Window_of_texture->Get_Width())
        {
            throw string("Incorrect easting Value ! ");
        }
        if(y>Window_of_texture->Get_High())
        {
            throw string("Incorrect ordered Value ! ");
        }
        if(High>Window_of_texture->Get_High()-y)
        {
            throw string("Incorrect high Value ! ");
        }
        if(Width>Window_of_texture->Get_Width()-x)
        {
            throw string("Incorrect width Value ! ");
        }
        cs_rsrect.x=x;
        cs_rsrect.y=y;
        if(Width==0)
        {
            cs_rsrect.w=width;
        }
        else    cs_rsrect.w=Width;
        if(High==0)
        {
            cs_rsrect.h=high;
        }
        else    cs_rsrect.h=High;
    }
    catch(string const& Error)
    {
        cerr<<" Texture::Set_Size = "<<Error<<this<<endl;
    }
}
void Texture::Set_WindowInUse(Window &A)
{
    Window_of_texture=A.Get_Adresse();
}

/************************************************************************************************************************/
