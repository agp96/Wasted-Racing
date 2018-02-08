#pragma once

#include <SFML/Window.hpp>


class EngineFacade{

public:

    EngineFacade(){};
    ~EngineFacade(){};

    void init();
    void update(){};
    void close(){};

    //Setters
    void setWidth(int w)                {       width = w;      }
    void setHeight(int h)               {       height = h;     }

    //Getters
    sf::Window* getWindow()             {       return window;          }
    int getWidth()                      {       return width;           }
    int getHeight()                     {       return height;          }


private:

    sf::Window* window;
    int width, height;

};