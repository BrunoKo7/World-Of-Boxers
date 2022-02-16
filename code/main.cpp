#include "graphics.h"
#include "Game.h"
#include "config.h"

//The custom callback function that the library calls 
//to check for and set the current application state.
void update(float ms)
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->update();
}

//The window content drawing function.
void draw()
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->draw();
}

int main()
{
    Game mygame; 
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "World Of Boxers");

    graphics::setUserData(&mygame);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);         
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);     

    mygame.init();
    graphics::startMessageLoop();
    return 0;
}