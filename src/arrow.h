#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, float wind_angle, glm::vec3 pos);
    void set_position(float x, float y, float z);
    void tick(glm::vec3);
private:
    VAO *mcuboid;
    VAO *sc1;
    VAO *sc2;
};

#endif // BALL_H
