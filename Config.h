#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

namespace SDL //The SDL name_space contain all the classes created by SDL basic functions
{

class Config  // The Configuration class contain methods to obtain general parameters for window configuring
{
public:
    Config(std::string const Name="Config");
    ~Config();
    int Get_Width() const; // return Width value from a Configuration file
    int Get_High() const; // return High value from a Configuration file
    int Get_Param_Fullscrean() const; // return FullScreen Parameter as a bool value from a Configuration file
    int Get_Language() const ;

private:

    std::string File_Name;

};
}
#endif // CONFIG_H
