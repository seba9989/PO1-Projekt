#include <stddef.h>
#include "raylib.h"
#include "gui/pause/pause.h"

int main(void) {
  // Initialization
  //---------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "Arkanoid");

  int framesCounter = 0;

  SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
  //----------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    framesCounter++;

    if (!PAUSE) {
      
    }

    BeginDrawing();
    {
      ClearBackground(RAYWHITE);

      PauseMenu();  

      DrawFPS(10, 10);
    }
    EndDrawing();
  }

  // De-Initialization
  //---------------------------------------------------------
  CloseWindow();  // Close window and OpenGL context
  //----------------------------------------------------------

  return 0;
}