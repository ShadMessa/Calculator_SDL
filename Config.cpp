#include "Config.h"

using namespace std ;
using namespace SDL ;

//\todo synchronyse between high and width

Config::Config(string const Name)
{
    File_Name="Data/"+Name+".cfg"; //\todo what if DATA doesnt exist check that
}
Config::~Config()
{
    delete &File_Name;

}
int Config::Get_Param_Fullscrean() const
{
    try
    {
        string Mot_temp;
        int i;
        ifstream File_IC(File_Name.c_str());

        if(File_IC.is_open())
        {
            throw string("No file found !");
        }
        for(i=0; i<9; i++)
        {
            File_IC>>Mot_temp;
        }
        if(Mot_temp!=":")
        {
            throw string("File corrupt !");
        }
        File_IC>>Mot_temp;
        File_IC.close();
        if(Mot_temp=="1")
        {
            return 0x000001;   //the file have to contain one of those value
        }
        else if(Mot_temp=="0")
        {
            return 0x00000;   //in the line 4 or it'll be considered as corrupt
        }
        else
        {
            throw string("File corrupt !");
        }
    }
    catch(string const& FATAL_ERROR)
    {
        cerr<<FATAL_ERROR<<"\t";
        if(FATAL_ERROR=="No file found !"||FATAL_ERROR=="File corrupt !")
        {

            cout<<File_Name<<endl;
            ofstream File_OC(File_Name.c_str());
            File_OC<<"\t\t["<<File_Name<<"]\nHight : 480\nWidth : 640\nFullsceen : 0"<<endl;
            File_OC.close();
        }
        return 0;
    }
}

///////////////////////////////////////////////////*******************************///////////////////////////////////////////////////////

int Config::Get_Width() const
{
GO_back_do_it_again:
    try
    {
        string Mot_temp="";
        int Chifre=0,i;
        ifstream File_IC(File_Name.c_str());
        if(File_IC.is_open())
        {
            throw string("No file found !");
        }
        for(i=0; i<6; i++)
        {
            File_IC>>Mot_temp;
        }
        if(Mot_temp!=":")
        {
            throw string("File corrupt !");
        }
        File_IC>>Mot_temp;
        File_IC.close();

        if(Mot_temp=="640"||Mot_temp=="800"||Mot_temp=="1024"||Mot_temp=="1280")//the file have to contain one of those value
        {
            //in the line 3 or it'll be considered as corrupt
            Chifre=atoi(Mot_temp.c_str());
            return Chifre;
        }
        else
        {
            throw string("File corrupt !");
        }
    }

    catch(string const& FATAL_ERROR)
    {
        cerr<<FATAL_ERROR<<" ";
        if(FATAL_ERROR=="No file found !"||FATAL_ERROR=="File corrupt !")
        {
            cout<<File_Name<<endl;
            ofstream File_OC(File_Name.c_str());
            File_OC<<"\t\t["<<File_Name<<"]\nHight : 480\nWidth : 640\nFullsceen : 0"<<endl;
            File_OC.close();
        }
        goto GO_back_do_it_again;
    }
}

///////////////////////////////////////////////////*******************************///////////////////////////////////////////////////////

int Config::Get_High() const
{
GO_back_do_it_again:
    try
    {
        string Mot_temp="";
        int Chifre=0,i;
        ifstream File_IC(File_Name.c_str());

        if(File_IC.is_open())
        {
            throw string("No file found !");
        }
        for(i=0; i<3; i++)
        {
            File_IC>>Mot_temp;
        }
        if(Mot_temp!=":")
        {
            throw string("File corrupt !");
        }
        File_IC>>Mot_temp;
        File_IC.close();
        if(Mot_temp=="480"||Mot_temp=="600"||Mot_temp=="768")//the file have to contain one of those value
        {
            //in the line 2 or it'll be considered as corrupt
            Chifre=atoi(Mot_temp.c_str());
            return Chifre;
        }
        else
        {
            throw string("File corrupt !");
        }
    }

    catch(string const& FATAL_ERROR)
    {
        cerr<<FATAL_ERROR<<" ";
        if(FATAL_ERROR=="No file found !"||FATAL_ERROR=="File corrupt !")
        {
            cout<<File_Name<<endl;
            ofstream File_OC(File_Name.c_str());
            File_OC<<"\t\t["<<File_Name<<"]\nHight : 480\nWidth : 640\nFullsceen : 0"<<endl;
            File_OC.close();
        }
        goto GO_back_do_it_again;
    }
}
