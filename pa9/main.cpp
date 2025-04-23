#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Application.h"


int main() 
{
    srand(time(NULL));
    App app;

    //main loop
    while (app.IsOpen()) 
    {
        app.WinUpdate();
        app.Update();
        app.Render();
    }
    return 0;
}