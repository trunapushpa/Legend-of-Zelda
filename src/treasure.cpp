#include "treasure.h"
#include "main.h"

Treasure::Treasure(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->gravity = -0.002f;
    speed = 0.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
            -1.0f, 0.85f, -1.0f, // triangle 1 : begin
            -1.0f, 0.85f, 1.0f,
            -1.0f, 2.35f, 1.0f, // triangle 1 : end
            1.0f, 2.35f, -1.0f, // triangle 2 : begin
            -1.0f, 0.85f, -1.0f,
            -1.0f, 2.35f, -1.0f, // triangle 2 : end
            1.0f, 0.85f, 1.0f,
            -1.0f, 0.85f, -1.0f,
            1.0f, 0.85f, -1.0f,
            1.0f, 2.35f, -1.0f,
            1.0f, 0.85f, -1.0f,
            -1.0f, 0.85f, -1.0f,
            -1.0f, 0.85f, -1.0f,
            -1.0f, 2.35f, 1.0f,
            -1.0f, 2.35f, -1.0f,
            1.0f, 0.85f, 1.0f,
            -1.0f, 0.85f, 1.0f,
            -1.0f, 0.85f, -1.0f,
            -1.0f, 2.35f, 1.0f,
            -1.0f, 0.85f, 1.0f,
            1.0f, 0.85f, 1.0f,
            1.0f, 2.35f, 1.0f,
            1.0f, 0.85f, -1.0f,
            1.0f, 2.35f, -1.0f,
            1.0f, 0.85f, -1.0f,
            1.0f, 2.35f, 1.0f,
            1.0f, 0.85f, 1.0f,
            1.0f, 2.35f, 1.0f,
            1.0f, 2.35f, -1.0f,
            -1.0f, 2.35f, -1.0f,
            1.0f, 2.35f, 1.0f,
            -1.0f, 2.35f, -1.0f,
            -1.0f, 2.35f, 1.0f,
            1.0f, 2.35f, 1.0f,
            -1.0f, 2.35f, 1.0f,
            1.0f, 0.85f, 1.0f // end of monster body
    };

    this->object = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data, COLOR_BROWN, GL_FILL);

}

void Treasure::draw(glm::mat4 VP) {
//    this->rotation += 3.0f;
//    for (this->rotation = 0; this->rotation<180; this->rotation+=2){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
//    draw3DObject(this->object2);
//    }
}

void Treasure::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Treasure::tick() {
//    this->speed += this->gravity;
//    this->position.y += speed;
//    if (this->position.y < -0.2)
//        this->speed = 0.03f;
//    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

