#include "raylib.h"

bool PAUSE = false;

void PauseMenu()
{
  SetExitKey(KEY_NULL);
  if (IsKeyPressed(KEY_ESCAPE)) PAUSE = !PAUSE;
  if (PAUSE) DrawText("PAUSED", 350, 200, 30, GRAY);
}