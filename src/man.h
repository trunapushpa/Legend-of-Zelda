#include "main.h"

#ifndef MAN_H
#define MAN_H


class Man {
public:
    Man() {}
    Man(float x, float y, float z);
    glm::vec3 position, tcam, hcam;
    float rotation, gravity, speedy;
    float width, length, height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void rotate(float angle);
    void set_rot(float angle);
    double speed;
    int color;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object8;
    VAO *object9;
    VAO *object10;
};


#endif //MAN_H
