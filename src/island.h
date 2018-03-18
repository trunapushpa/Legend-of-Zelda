#include "main.h"

#ifndef ISLAND_H
#define ISLAND_H


class Island {
public:
    Island() {}
    Island(float x, float y, float z);
    glm::vec3 position;
    float rotation, gravity;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    int color;
private:
    VAO *object;
    VAO *object2;
};


#endif //ISLAND_H
