#include "man.h"
#include "main.h"

Man::Man(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->height = 1.233f;
    this->length = 0.51f;
    this->color = 0 + (rand() % static_cast<int>(2 - 0 + 1));
    this->gravity = -0.002f;
    this->hcam = glm::vec3(x, y + 2 * this->height, z + (this->length));
    this->tcam = glm::vec3(x, 6, z - 7.0f);
    speed = 0.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
            -1.0f, 1.7f, -0.5f, // triangle 1 : begin
            -1.0f, 1.7f, 0.5f,
            -1.0f, 3.7f, 0.5f, // triangle 1 : end
            1.0f, 3.7f, -0.5f, // triangle 2 : begin
            -1.0f, 1.7f, -0.5f,
            -1.0f, 3.7f, -0.5f, // triangle 2 : end
            1.0f, 1.7f, 0.5f,
            -1.0f, 1.7f, -0.5f,
            1.0f, 1.7f, -0.5f,
            1.0f, 3.7f, -0.5f,
            1.0f, 1.7f, -0.5f,
            -1.0f, 1.7f, -0.5f,
            -1.0f, 1.7f, -0.5f,
            -1.0f, 3.7f, 0.5f,
            -1.0f, 3.7f, -0.5f,
            1.0f, 1.7f, 0.5f,
            -1.0f, 1.7f, 0.5f,
            -1.0f, 1.7f, -0.5f,
            -1.0f, 3.7f, 0.5f,
            -1.0f, 1.7f, 0.5f,
            1.0f, 1.7f, 0.5f,
            1.0f, 3.7f, 0.5f,
            1.0f, 1.7f, -0.5f,
            1.0f, 3.7f, -0.5f,
            1.0f, 1.7f, -0.5f,
            1.0f, 3.7f, 0.5f,
            1.0f, 1.7f, 0.5f,
            1.0f, 3.7f, 0.5f,
            1.0f, 3.7f, -0.5f,
            -1.0f, 3.7f, -0.5f,
            1.0f, 3.7f, 0.5f,
            -1.0f, 3.7f, -0.5f,
            -1.0f, 3.7f, 0.5f,
            1.0f, 3.7f, 0.5f,
            -1.0f, 3.7f, 0.5f,
            1.0f, 1.7f, 0.5f // end of monster body
    };

    for (int i = 0; i < 12*3*3; ++i) {
        vertex_buffer_data[i]/= 3.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data, COLOR_MBODY, GL_FILL);

    GLfloat vertex_buffer_data2[] = {
            -0.2f - 0.5f, 0.0f, -0.2f, // triangle 1 : begin
            -0.2f - 0.5f, 0.0f, 0.2f,
            -0.2f - 0.5f, 1.7f, 0.2f, // triangle 1 : end
            0.2f - 0.5f, 1.7f, -0.2f, // triangle 2 : begin
            -0.2f - 0.5f, 0.0f, -0.2f,
            -0.2f - 0.5f, 1.7f, -0.2f, // triangle 2 : end
            0.2f - 0.5f, 0.0f, 0.2f,
            -0.2f - 0.5f, 0.0f, -0.2f,
            0.2f - 0.5f, 0.0f, -0.2f,
            0.2f - 0.5f, 1.7f, -0.2f,
            0.2f - 0.5f, 0.0f, -0.2f,
            -0.2f - 0.5f, 0.0f, -0.2f,
            -0.2f - 0.5f, 0.0f, -0.2f,
            -0.2f - 0.5f, 1.7f, 0.2f,
            -0.2f - 0.5f, 1.7f, -0.2f,
            0.2f - 0.5f, 0.0f, 0.2f,
            -0.2f - 0.5f, 0.0f, 0.2f,
            -0.2f - 0.5f, 0.0f, -0.2f,
            -0.2f - 0.5f, 1.7f, 0.2f,
            -0.2f - 0.5f, 0.0f, 0.2f,
            0.2f - 0.5f, 0.0f, 0.2f,
            0.2f - 0.5f, 1.7f, 0.2f,
            0.2f - 0.5f, 0.0f, -0.2f,
            0.2f - 0.5f, 1.7f, -0.2f,
            0.2f - 0.5f, 0.0f, -0.2f,
            0.2f - 0.5f, 1.7f, 0.2f,
            0.2f - 0.5f, 0.0f, 0.2f,
            0.2f - 0.5f, 1.7f, 0.2f,
            0.2f - 0.5f, 1.7f, -0.2f,
            -0.2f - 0.5f, 1.7f, -0.2f,
            0.2f - 0.5f, 1.7f, 0.2f,
            -0.2f - 0.5f, 1.7f, -0.2f,
            -0.2f - 0.5f, 1.7f, 0.2f,
            0.2f - 0.5f, 1.7f, 0.2f,
            -0.2f - 0.5f, 1.7f, 0.2f,
            0.2f - 0.5f, 0.0f, 0.2f
    };

    for (int i = 0; i < 12*3*3; ++i) {
        vertex_buffer_data2[i]/= 3.0f;
    }

    this->object2 = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data2, COLOR_LEG, GL_FILL);

    GLfloat vertex_buffer_data3[] = {
            -0.2f + 0.5f, 0.0f, -0.2f, // triangle 1 : begin
            -0.2f + 0.5f, 0.0f, 0.2f,
            -0.2f + 0.5f, 1.7f, 0.2f, // triangle 1 : end
            0.2f + 0.5f, 1.7f, -0.2f, // triangle 2 : begin
            -0.2f + 0.5f, 0.0f, -0.2f,
            -0.2f + 0.5f, 1.7f, -0.2f, // triangle 2 : end
            0.2f + 0.5f, 0.0f, 0.2f,
            -0.2f + 0.5f, 0.0f, -0.2f,
            0.2f + 0.5f, 0.0f, -0.2f,
            0.2f + 0.5f, 1.7f, -0.2f,
            0.2f + 0.5f, 0.0f, -0.2f,
            -0.2f + 0.5f, 0.0f, -0.2f,
            -0.2f + 0.5f, 0.0f, -0.2f,
            -0.2f + 0.5f, 1.7f, 0.2f,
            -0.2f + 0.5f, 1.7f, -0.2f,
            0.2f + 0.5f, 0.0f, 0.2f,
            -0.2f + 0.5f, 0.0f, 0.2f,
            -0.2f + 0.5f, 0.0f, -0.2f,
            -0.2f + 0.5f, 1.7f, 0.2f,
            -0.2f + 0.5f, 0.0f, 0.2f,
            0.2f + 0.5f, 0.0f, 0.2f,
            0.2f + 0.5f, 1.7f, 0.2f,
            0.2f + 0.5f, 0.0f, -0.2f,
            0.2f + 0.5f, 1.7f, -0.2f,
            0.2f + 0.5f, 0.0f, -0.2f,
            0.2f + 0.5f, 1.7f, 0.2f,
            0.2f + 0.5f, 0.0f, 0.2f,
            0.2f + 0.5f, 1.7f, 0.2f,
            0.2f + 0.5f, 1.7f, -0.2f,
            -0.2f + 0.5f, 1.7f, -0.2f,
            0.2f + 0.5f, 1.7f, 0.2f,
            -0.2f + 0.5f, 1.7f, -0.2f,
            -0.2f + 0.5f, 1.7f, 0.2f,
            0.2f + 0.5f, 1.7f, 0.2f,
            -0.2f + 0.5f, 1.7f, 0.2f,
            0.2f + 0.5f, 0.0f, 0.2f
    };

    for (int i = 0; i < 12*3*3; ++i) {
        vertex_buffer_data3[i]/= 3.0f;
    }

    this->object3 = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data3, COLOR_LEG, GL_FILL);
}

void Man::draw(glm::mat4 VP) {
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
    draw3DObject(this->object2);
    draw3DObject(this->object3);
//    draw3DObject(this->object4);
//    draw3DObject(this->object5);
//    draw3DObject(this->object6);
//    draw3DObject(this->object7);
//    draw3DObject(this->object8);
//    draw3DObject(this->object9);
//    draw3DObject(this->object10);
//    }
}

void Man::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->hcam = glm::vec3(x, y + 2 * this->height, z + (this->length));
    this->hcam.x = this->position.x + 2.0f * (float) sin(this->rotation * M_PI / 180.0f);
    this->hcam.z = this->position.z + 2.0f * (float) cos(this->rotation * M_PI / 180.0f);
    this->tcam.x = this->position.x - 7.0f * (float) sin(this->rotation * M_PI / 180.0f);
    this->tcam.z = this->position.z - 7.0f * (float) cos(this->rotation * M_PI / 180.0f);
}

void Man::rotate(float angle){
    this->rotation += angle;
    if (this->rotation >= 360)
        this->rotation -= 360;
    if (this->rotation <= -360)
        this->rotation += 360;
    if (this->rotation < 0) {
        this->rotation += 360;
    }
    if (this->rotation > 180) {
        this->rotation -= 360;
    }
    this->hcam.x = this->position.x + 1.0f * (float) sin(this->rotation * M_PI / 180.0f);
    this->hcam.z = this->position.z + 1.0f * (float) cos(this->rotation * M_PI / 180.0f);
    this->tcam.x = this->position.x - 7.0f * (float) sin(this->rotation * M_PI / 180.0f);
    this->tcam.z = this->position.z - 7.0f * (float) cos(this->rotation * M_PI / 180.0f);
}

void Man::set_rot(float angle){
    this->rotation = angle;
    if (this->rotation >= 360)
        this->rotation -= 360;
    if (this->rotation <= -360)
        this->rotation += 360;
    if (this->rotation < 0) {
        this->rotation += 360;
    }
    if (this->rotation > 180) {
        this->rotation -= 360;
    }
    this->hcam.x = this->position.x + 1.0f * (float) sin(this->rotation * M_PI / 180.0f);
    this->hcam.z = this->position.z + 1.0f * (float) cos(this->rotation * M_PI / 180.0f);
    this->tcam.x = this->position.x - 7.0f * (float) sin(this->rotation * M_PI / 180.0f);
    this->tcam.z = this->position.z - 7.0f * (float) cos(this->rotation * M_PI / 180.0f);
}

void Man::tick() {
//    this->speed += this->gravity;
//    this->position.y += speed;
//    if (this->position.y < -0.2)
//        this->speed = 0.03f;
//    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

