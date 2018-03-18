#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z, float width, float length, float height);
    glm::vec3 position, tcam, hcam;
    int health, points;
    float rotation, cannon_rotz, cannon_roty;
    float width, length, height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void rotate(float angle);
    void set_rot(float angle);
    void tick(float wind_mag, float wind_angle);
    float speed, speedy, gravity, acceleration;
private:
    VAO *base;
    VAO *sides;
    VAO *front;
    VAO *back;
    VAO *cannon;
};

#endif // BOAT_H
