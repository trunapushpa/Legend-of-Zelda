#include "main.h"

#ifndef BOOSTERBOX_H
#define BOOSTERBOX_H


class Boosterbox {
public:
    Boosterbox() {}
    Boosterbox(float x, float y, float z);
    glm::vec3 position;
    float rotation, gravity;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speedx, speedy, speedz;
    int color;
private:
    VAO *object;
    VAO *object2;
};


#endif //BOOSTERBOX_H
