#include "Texture.h"
#include "Event.h"

using namespace std;
using namespace SDL;

struct Button
{
    SDL_Rect position={0,0,0,0};
    TextureImage When_Selected;
    TextureImage When_Unselected;
    TextureText Ref;

};
typedef struct Button Button;

int main(int argc, char* argv[])
{
    //////////////////////////////////////////////Variables_Declarations/////////////////////////////////////////////////////
    Window Calcul("Calculatrice",300,300);
    TextureImage Screen(Calcul);
    Texture Backgound(Calcul),Screen_Back(Calcul);
    int i,j=122,k=10;
    Button Clavier[16];
    Event_Keyboard KE;
    Event_Mouse ME;
    //////////////////////////////////////////////Variables_Initialisation/////////////////////////////////////////////////////
    for(i=0;i<=15;i++)
    {
        Clavier[i].position.h=40;
        Clavier[i].position.w=40;
        Clavier[i].position.x=k;
        Clavier[i].position.y=j;
        j+=40+2;
        if(i==2|i==6|i==9|i==13)
        {j=122;k+=40+5;}

        Clavier[i].Ref.Set_WindowInUse(Calcul);
        Clavier[i].When_Selected.Set_WindowInUse(Calcul);
        Clavier[i].When_Selected.Create_Texture_From_File("Files/selec.png");
        Clavier[i].When_Unselected.Set_WindowInUse(Calcul);
        Clavier[i].When_Unselected.Create_Texture_From_File("Files/unselec.png");
    }
    Clavier[0].Ref.Create_Texture_From_Text("Files/palai.ttf","1",128,255,255,255);
    Clavier[1].Ref.Create_Texture_From_Text("Files/palai.ttf","4",128,255,255,255);
    Clavier[2].Ref.Create_Texture_From_Text("Files/palai.ttf","7",128,255,255,255);
    Clavier[3].Ref.Create_Texture_From_Text("Files/palai.ttf","2",128,255,255,255);
    Clavier[4].Ref.Create_Texture_From_Text("Files/palai.ttf","5",128,255,255,255);
    Clavier[5].Ref.Create_Texture_From_Text("Files/palai.ttf","8",128,255,255,255);
    Clavier[6].Ref.Create_Texture_From_Text("Files/palai.ttf","0",128,255,255,255);
    Clavier[7].Ref.Create_Texture_From_Text("Files/palai.ttf","3",128,255,255,255);
    Clavier[8].Ref.Create_Texture_From_Text("Files/palai.ttf","6",128,255,255,255);
    Clavier[9].Ref.Create_Texture_From_Text("Files/palai.ttf","9",128,255,255,255);
    Clavier[10].Ref.Create_Texture_From_Text("Files/palai.ttf","+",128,255,255,255);
    Clavier[11].Ref.Create_Texture_From_Text("Files/palai.ttf","-",128,255,255,255);
    Clavier[12].Ref.Create_Texture_From_Text("Files/palai.ttf","x",128,255,255,255);
    Clavier[13].Ref.Create_Texture_From_Text("Files/palai.ttf","/",128,255,255,255);
    Clavier[14].Ref.Create_Texture_From_Text("Files/palai.ttf","C",128,255,255,255);
    Clavier[15].Ref.Create_Texture_From_Text("Files/palai.ttf","=",128,255,255,255);

    Screen.Create_Texture_From_File("Files/screen.png");
    Backgound.Create_Texture_Unicolour(230,230,230);
    Screen_Back.Create_Texture_Unicolour(250,250,250);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   toe:

    Backgound.RenderCopy_Texture();
    Screen.RenderCopy_Texture(5,5,290,105);
    for(i=0;i<=15;i++)
    {
        Clavier[i].When_Unselected.RenderCopy_Texture(Clavier[i].position.x,Clavier[i].position.y,Clavier[i].position.w,Clavier[i].position.h);
        Clavier[i].Ref.RenderCopy_Texture(Clavier[i].position.x+5,Clavier[i].position.y+5,Clavier[i].position.w-7,Clavier[i].position.h-7);
    }

    Calcul.Show_Render();
SDL_Delay(5000);
goto toe;

    return 0;
}
