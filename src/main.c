#include "include/game.h"

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
  Model model = LoadModelFromMesh(GenChunk(8, 4));
  DisableCursor();
  while (!WindowShouldClose()) {
    Vector3 moveDir = {0};
    if(IsKeyDown(KEY_W)) {
      moveDir.z += 1;
    }
    if(IsKeyDown(KEY_A)) {
      moveDir.x -= 1;
    }
    if(IsKeyDown(KEY_S)) {
      moveDir.z -= 1;
    }
    if(IsKeyDown(KEY_D)) {
      moveDir.x += 1;
    }
    if(IsKeyDown(KEY_SPACE)) {
      moveDir.y += 1;
    }
    if(IsKeyDown(KEY_LEFT_SHIFT)) {
      moveDir.y -= 1;
    }
    moveDir = Vector3Normalize(moveDir);
    cam.position = Vector3Add(cam.position, Vector3Scale(GetCameraForward(&cam), moveDir.z));
    cam.position = Vector3Add(cam.position, Vector3Scale(GetCameraRight(&cam), moveDir.x));
    cam.target = Vector3Add(cam.target, Vector3Scale(GetCameraForward(&cam), moveDir.z));
    cam.target = Vector3Add(cam.target, Vector3Scale(GetCameraRight(&cam), moveDir.x));
    cam.position.y += moveDir.y;
    cam.target.y += moveDir.y;
    cam.up = (Vector3){0.0f, 1.0f, 0.0f};
    UpdateCamera(&cam, CAMERA_FIRST_PERSON);
    BeginDrawing();
      ClearBackground(RAYWHITE);
      BeginMode3D(cam);
        DrawModel(model, Vector3Zero(), 1.0f, GREEN);
        DrawCube(Vector3Zero(), 1, 1, 1, RED);
      EndMode3D();
      DrawText(TextFormat("Pos: (%06.3f, %06.3f, %06.3f)", cam.position.x, cam.position.y, cam.position.z), screenWidth - 300, 0, 16, BLACK);
      DrawText(TextFormat("Target: (%06.3f, %06.3f, %06.3f)", cam.target.x, cam.target.y, cam.target.z), screenWidth - 300, 50, 16, BLACK);
    EndDrawing();
  }
  ShowCursor();
  
  CloseWindow();
  
  return 0;
}