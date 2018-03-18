#include "main.h"
#include "boat.h"

#ifndef WATER_H
#define WATER_H


class Water {
public:
    Water() {}
    Water(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, Boat boat);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object2;
};

#endif // WATER_H
