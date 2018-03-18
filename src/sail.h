#include "main.h"

#ifndef SAIL_H
#define SAIL_H


class Sail {
public:
    Sail() {}
    Sail(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, float wind_angle, float boat_angle);
    void set_position(float x, float y, float z);
    void tick(glm::vec3);
private:
    VAO *mast;
    VAO *sailc1;
    VAO *sailc2;
    VAO *sailc3;
};

#endif // BALL_H
