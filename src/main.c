#include "raylib.h"
#include "rcamera.h"

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 480;
  InitWindow(screenWidth, screenHeight, "Test");
  SetTargetFPS(60);
  Camera cam = { 0 };
  cam.position = (Vector3){0.0f, 4.0f, 0.0f};
  cam.target = (Vector3){0.0f, 2.0f, 2.0f};
  cam.up = (Vector3){0.0f, 1.0f, 0.0f};
  cam.fovy = 60.0f;
  cam.projection = CAMERA_PERSPECTIVE;
  DisableCursor();
  while (!WindowShouldClose()) {
    // Vector3 cam_mov = {0.0f, 0.0f, 0.0f};
    if(IsKeyDown(KEY_W)) {
      cam.position.z += 1;
      cam.target.z += 1;
    }
    if(IsKeyDown(KEY_A)) {
      cam.position.x -= 1;
      cam.target.x -= 1;
    }
    if(IsKeyDown(KEY_S)) {
      cam.position.z -= 1;
      cam.target.z -= 1;
    }
    if(IsKeyDown(KEY_D)) {
      cam.position.x += 1;
      cam.target.x += 1;
    }
    // cam.target.x = cam.position.x;
    // cam.target.z = cam.position.x + 2;
    cam.up = (Vector3){0.0f, 1.0f, 0.0f};
    UpdateCamera(&cam, CAMERA_FIRST_PERSON);
    BeginDrawing();
      ClearBackground(RAYWHITE);
      BeginMode3D(cam);
        DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){10.0f, 10.0f}, GREEN);
      EndMode3D();
      DrawText(TextFormat("Pos: (%06.3f, %06.3f, %06.3f)", cam.position.x, cam.position.y, cam.position.z), screenWidth - 300, 0, 16, BLACK);
      DrawText(TextFormat("Target: (%06.3f, %06.3f, %06.3f)", cam.target.x, cam.target.y, cam.target.z), screenWidth - 300, 50, 16, BLACK);
    EndDrawing();
  }
  ShowCursor();
  
  CloseWindow();
  
  return 0;
}