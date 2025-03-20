#include "include/game.h"
#include "stdio.h"

//  ]

Mesh GenChunk(int size, int resolution) {
  Mesh mesh = {0};
  mesh.triangleCount = resolution * resolution * 2; // Setiap kotak punya 2 segitiga
  int vertexCount = (resolution + 1) * (resolution + 1);
  float tileSize = ((float)size) / resolution;
  float uvFract = 1.0f / resolution;
  
  mesh.vertexCount = vertexCount;
  mesh.vertices = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
  mesh.indices = (short unsigned int *)MemAlloc(mesh.triangleCount * 3 * sizeof(short unsigned int)); // 3 indeks per segitiga
  mesh.texcoords = (float *)MemAlloc(mesh.vertexCount * 2 * sizeof(float)); // 2 koordinat per vertex
  mesh.normals = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float)); // 3 komponen per normal
  
  // Generate vertices, texcoords, normals
  int vertexIndex = 0;
  for(int z = 0; z < resolution + 1; z++) {
    for(int x = 0; x < resolution + 1; x++) {
      // Posisi vertex
      mesh.vertices[vertexIndex*3] = x * tileSize;
      mesh.vertices[vertexIndex*3 + 1] = 0;
      mesh.vertices[vertexIndex*3 + 2] = z * tileSize;
      
      // Normal (menghadap ke atas)
      mesh.normals[vertexIndex*3] = 0;
      mesh.normals[vertexIndex*3 + 1] = 1;
      mesh.normals[vertexIndex*3 + 2] = 0;
      
      // Texcoords
      mesh.texcoords[vertexIndex*2] = (float)x * uvFract;
      mesh.texcoords[vertexIndex*2 + 1] = (float)z * uvFract;
      
      vertexIndex++;
    }
  }
  
  // Generate indices
  int indexCount = 0;
  for(int z = 0; z < resolution; z++) {
    for(int x = 0; x < resolution; x++) {
      int topLeft = z * (resolution + 1) + x;
      int topRight = topLeft + 1;
      int bottomLeft = (z + 1) * (resolution + 1) + x;
      int bottomRight = bottomLeft + 1;
      // printf("[%d, %d, %d, %d (%d)]", topLeft, topRight, bottomLeft, bottomRight, indexCount);
      
      // Segitiga 1 (kiri atas, kanan atas, kanan bawah)
      mesh.indices[indexCount++] = topLeft;
      mesh.indices[indexCount++] = topRight;
      mesh.indices[indexCount++] = bottomRight;
      
      // Segitiga 2 (kiri atas, kanan bawah, kiri bawah)
      mesh.indices[indexCount++] = topLeft;
      mesh.indices[indexCount++] = bottomRight;
      mesh.indices[indexCount++] = bottomLeft;
    }
  }
  
  UploadMesh(&mesh, false);
  return mesh;
}