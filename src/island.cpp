#include "island.h"
#include "main.h"

Island::Island(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->color = 0 + (rand() % static_cast<int>(2 - 0 + 1));
    this->gravity = -0.002f;
    speed = 0.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
            -400.0f, 0.0f, -400.0f, // triangle 1 : begin
            -400.0f, 0.0f, 400.0f,
            -400.0f, 0.8f, 400.0f, // triangle 1 : end
            400.0f, 0.8f, -400.0f, // triangle 2 : begin
            -400.0f, 0.0f, -400.0f,
            -400.0f, 0.8f, -400.0f, // triangle 2 : end
            400.0f, 0.0f, 400.0f,
            -400.0f, 0.0f, -400.0f,
            400.0f, 0.0f, -400.0f,
            400.0f, 0.8f, -400.0f,
            400.0f, 0.0f, -400.0f,
            -400.0f, 0.0f, -400.0f,
            -400.0f, 0.0f, -400.0f,
            -400.0f, 0.8f, 400.0f,
            -400.0f, 0.8f, -400.0f,
            400.0f, 0.0f, 400.0f,
            -400.0f, 0.0f, 400.0f,
            -400.0f, 0.0f, -400.0f,
            -400.0f, 0.8f, 400.0f,
            -400.0f, 0.0f, 400.0f,
            400.0f, 0.0f, 400.0f,
            400.0f, 0.8f, 400.0f,
            400.0f, 0.0f, -400.0f,
            400.0f, 0.8f, -400.0f,
            400.0f, 0.0f, -400.0f,
            400.0f, 0.8f, 400.0f,
            400.0f, 0.0f, 400.0f,
            400.0f, 0.8f, 400.0f,
            400.0f, 0.8f, -400.0f,
            -400.0f, 0.8f, -400.0f,
            400.0f, 0.8f, 400.0f,
            -400.0f, 0.8f, -400.0f,
            -400.0f, 0.8f, 400.0f,
            400.0f, 0.8f, 400.0f,
            -400.0f, 0.8f, 400.0f,
            400.0f, 0.0f, 400.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data, COLOR_DLAND, GL_FILL);

    GLfloat trgls_data[90009];
    for (int i = -400; i <= 400 ; i+=16) {
        for (int j = -400; j <= 400 ; j+=16) {
//            trgls_data[((i+100)/4)*450 + ((j+100)/4)*9] = (float)i+boat.position.x;
//            trgls_data[((i+100)/4)*450 + ((j+100)/4)*9 + 1] = 0;
//            trgls_data[((i+100)/4)*450 + ((j+100)/4)*9 + 2] = (float)j+boat.position.z;
//
//            trgls_data[((i+100)/4)*450 + ((j+100)/4)*9 + 3] = (float)i+boat.position.x;
//            trgls_data[((i+100)/4)*450 + ((j+100)/4)*9 + 4] = 0;
//            trgls_data[((i+100)/4)*450 + ((j+100)/4)*9 + 5] = (float)j+4+boat.position.z;
//
//            trgls_data[((i+100)/4)*450 + ((j+100)/4)*9 + 6] = (float)i+4+boat.position.x;
//            trgls_data[((i+100)/4)*450 + ((j+100)/4)*9 + 7] = 0;
//            trgls_data[((i+100)/4)*450 + ((j+100)/4)*9 + 8] = (float)j+boat.position.z;

            trgls_data[((i+400)/16)*450 + ((j+400)/16)*9] = (float)i;
            trgls_data[((i+400)/16)*450 + ((j+400)/16)*9 + 1] = 0.82;
            trgls_data[((i+400)/16)*450 + ((j+400)/16)*9 + 2] = (float)j;

            trgls_data[((i+400)/16)*450 + ((j+400)/16)*9 + 3] = (float)i;
            trgls_data[((i+400)/16)*450 + ((j+400)/16)*9 + 4] = 0.82;
            trgls_data[((i+400)/16)*450 + ((j+400)/16)*9 + 5] = (float)j+16;

            trgls_data[((i+400)/16)*450 + ((j+400)/16)*9 + 6] = (float)i+16;
            trgls_data[((i+400)/16)*450 + ((j+400)/16)*9 + 7] = 0.82;
            trgls_data[((i+400)/16)*450 + ((j+400)/16)*9 + 8] = (float)j;
        }
    }
    this->object2 = create3DObject(GL_TRIANGLES, 50 * 50 * 3, trgls_data, COLOR_LLAND, GL_FILL);
}

void Island::draw(glm::mat4 VP) {
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
//    }
}

void Island::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Island::tick() {
//    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

