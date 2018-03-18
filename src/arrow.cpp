#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat mast_trgls[] = {
            -0.06f, -0.06f, -0.33f, // triangle 1 : begin
            -0.06f, -0.06f, 0.33f,
            -0.06f, 0.06f, 0.33f, // triangle 1 : end
            0.06f, 0.06f, -0.33f, // triangle 2 : begin
            -0.06f, -0.06f, -0.33f,
            -0.06f, 0.06f, -0.33f, // triangle 2 : end
            0.06f, -0.06f, 0.33f,
            -0.06f, -0.06f, -0.33f,
            0.06f, -0.06f, -0.33f,
            0.06f, 0.06f, -0.33f,
            0.06f, -0.06f, -0.33f,
            -0.06f, -0.06f, -0.33f,
            -0.06f, -0.06f, -0.33f,
            -0.06f, 0.06f, 0.33f,
            -0.06f, 0.06f, -0.33f,
            0.06f, -0.06f, 0.33f,
            -0.06f, -0.06f, 0.33f,
            -0.06f, -0.06f, -0.33f,
            -0.06f, 0.06f, 0.33f,
            -0.06f, -0.06f, 0.33f,
            0.06f, -0.06f, 0.33f,
            0.06f, 0.06f, 0.33f,
            0.06f, -0.06f, -0.33f,
            0.06f, 0.06f, -0.33f,
            0.06f, -0.06f, -0.33f,
            0.06f, 0.06f, 0.33f,
            0.06f, -0.06f, 0.33f,
            0.06f, 0.06f, 0.33f,
            0.06f, 0.06f, -0.33f,
            -0.06f, 0.06f, -0.33f,
            0.06f, 0.06f, 0.33f,
            -0.06f, 0.06f, -0.33f,
            -0.06f, 0.06f, 0.33f,
            0.06f, 0.06f, 0.33f,
            -0.06f, 0.06f, 0.33f,
            0.06f, -0.06f, 0.33f,
    };

    this->mcuboid = create3DObject(GL_TRIANGLES, 12 * 3, mast_trgls, COLOR_ORANGE, GL_FILL);

//    static const GLfloat sail_trgl1[] = {
//            -0.08f, -0.08f, 0.32f, // triangle 1 : begin
//            -0.08f, -0.08f, 0.5f,
//            -0.08f, 0.08f, 0.5f, // triangle 1 : end
//            0.08f, 0.08f, 0.32f, // triangle 2 : begin
//            -0.08f, -0.08f, 0.32f,
//            -0.08f, 0.08f, 0.32f, // triangle 2 : end
//            0.08f, -0.08f, 0.5f,
//            -0.08f, -0.08f, 0.32f,
//            0.08f, -0.08f, 0.32f,
//            0.08f, 0.08f, 0.32f,
//            0.08f, -0.08f, 0.32f,
//            -0.08f, -0.08f, 0.32f,
//            -0.08f, -0.08f, 0.32f,
//            -0.08f, 0.08f, 0.5f,
//            -0.08f, 0.08f, 0.32f,
//            0.08f, -0.08f, 0.5f,
//            -0.08f, -0.08f, 0.5f,
//            -0.08f, -0.08f, 0.32f,
//            -0.08f, 0.08f, 0.5f,
//            -0.08f, -0.08f, 0.5f,
//            0.08f, -0.08f, 0.5f,
//            0.08f, 0.08f, 0.5f,
//            0.08f, -0.08f, 0.32f,
//            0.08f, 0.08f, 0.32f,
//            0.08f, -0.08f, 0.32f,
//            0.08f, 0.08f, 0.5f,
//            0.08f, -0.08f, 0.5f,
//            0.08f, 0.08f, 0.5f,
//            0.08f, 0.08f, 0.32f,
//            -0.08f, 0.08f, 0.32f,
//            0.08f, 0.08f, 0.5f,
//            -0.08f, 0.08f, 0.32f,
//            -0.08f, 0.08f, 0.5f,
//            0.08f, 0.08f, 0.5f,
//            -0.08f, 0.08f, 0.5f,
//            0.08f, -0.08f, 0.5f,
//    };

    static const GLfloat sail_trgl1[] = {
            0.15f, 0.15f, 0.32f, // triangle 2 : begin
            -0.15f, -0.15f, 0.32f,
            -0.15f, 0.15f, 0.32f, // triangle 2 : end

            0.15f, 0.15f, 0.32f,
            0.15f, -0.15f, 0.32f,
            -0.15f, -0.15f, 0.32f,

            -0.15f, -0.15f, 0.32f,
            -0.15f, 0.15f, 0.32f,
            0.0f, 0.0f, 0.6f,

            -0.15f, -0.15f, 0.32f,
            0.15f, -0.15f, 0.32f,
            0.0f, 0.0f, 0.6f,

            0.15f, -0.15f, 0.32f,
            0.15f, 0.15f, 0.32f,
            0.0f, 0.0f, 0.6f,

            0.15f, 0.15f, 0.32f,
            -0.15f, 0.15f, 0.32f,
            0.0f, 0.0f, 0.6f,
    };

    this->sc1 = create3DObject(GL_TRIANGLES, 6*3, sail_trgl1, COLOR_RED, GL_FILL);
//    this->sc2 = create3DObject(GL_TRIANGLES, 3, sail_trgl2, COLOR_ORANGE, GL_FILL);
}

void Arrow::draw(glm::mat4 VP, float wind_angle, glm::vec3 pos) {
    this->position = pos;
    this->rotation = wind_angle;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->mcuboid);
    draw3DObject(this->sc1);
//        draw3DObject(this->sc1);
//        draw3DObject(this->sc2);
}

void Arrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::tick(glm::vec3 boatpos) {
    this->position = boatpos;
//    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

