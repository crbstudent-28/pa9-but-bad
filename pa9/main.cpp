#include "Application.h"
#include "TestApp.h"
#include "ApplicationBase.h"

int main() 
{
    srand(time(NULL));
    App* game = new App();
    TestApp* tApp = nullptr;
    AppBase* app = game;

    //main loop
    while (app->IsOpen()) 
    {
        if (app->WinUpdate())
        {
            tApp = new TestApp();
            app = tApp;
        }
        app->Update();
    }
    return 0;
}