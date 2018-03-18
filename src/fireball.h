#include "main.h"

#ifndef FIREBALL_H
#define FIREBALL_H


class Fireball {
public:
    Fireball() {}
    Fireball(float x, float y, float z, bool isfireball);
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


#endif //FIREBALL_H
