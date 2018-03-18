#include "main.h"

#ifndef TREASURE_H
#define TREASURE_H


class Treasure {
public:
    Treasure() {}
    Treasure(float x, float y, float z);
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


#endif //TREASURE_H
