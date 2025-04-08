#include <iostream>
#include <graphics.h>
#include <math.h>
using namespace std;

struct Point3D {
    float x, y, z;
    Point3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
};

void drawCube(Point3D origin, float size, float angle) {
    Point3D vertices[8] = {
        {origin.x, origin.y, origin.z},
        {origin.x + size, origin.y, origin.z},
        {origin.x + size, origin.y + size, origin.z},
        {origin.x, origin.y + size, origin.z},
        {origin.x, origin.y, origin.z + size},
        {origin.x + size, origin.y, origin.z + size},
        {origin.x + size, origin.y + size, origin.z + size},
        {origin.x, origin.y + size, origin.z + size}
    };

    int proj[8][2];
    for(int i = 0; i < 8; i++)
        proj[i][0] = vertices[i].x + vertices[i].z * cos(angle),
        proj[i][1] = vertices[i].y + vertices[i].z * sin(angle);
    
    setcolor(15);
    int edges[12][2] = {
    {0,1}, {1,2}, {2,3}, {3,0}, // bottom face
    {4,5}, {5,6}, {6,7}, {7,4}, // top face
    {0,4}, {1,5}, {2,6}, {3,7}  // vertical edges
	};
    for(auto &edge : edges)
        line(proj[edge[0]][0], proj[edge[0]][1], proj[edge[1]][0], proj[edge[1]][1]);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    drawCube({200, 200, 0}, 100, M_PI / 6);
    outtextxy(180, 150, (char*)"Parallel Projection of Cube");

    getch();
    closegraph();
    return 0;
}

