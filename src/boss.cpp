#include "boss.h"
#include "main.h"

Boss::Boss(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->health = 5;
    this->gravity = -0.002f;
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
        vertex_buffer_data[i]*= 3.0f;
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
        vertex_buffer_data2[i]*= 3.0f;
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
        vertex_buffer_data3[i]*= 3.0f;
    }

    this->object3 = create3DObject(GL_TRIANGLES, 12 * 3, vertex_buffer_data3, COLOR_LEG, GL_FILL);

    GLfloat vertext_buffer_data4[] = {
            -0.2f - 0.7f, 3.7f, -0.2f,
            -0.2f - 0.7f, 3.7f, 0.2f,
            0.0f - 0.7f, 4.8f, 0.0f,

            -0.2f - 0.7f, 3.7f, 0.2f,
            0.2f - 0.7f, 3.7f, 0.2f,
            0.0f - 0.7f, 4.8f, 0.0f,

            0.2f - 0.7f, 3.7f, 0.2f,
            0.2f - 0.7f, 3.7f, -0.2f,
            0.0f - 0.7f, 4.8f, 0.0f,

            0.2f - 0.7f, 3.7f, -0.2f,
            -0.2f - 0.7f, 3.7f, -0.2f,
            0.0f - 0.7f, 4.8f, 0.0f,


            -0.2f + 0.7f, 3.7f, -0.2f,
            -0.2f + 0.7f, 3.7f, 0.2f,
            0.0f + 0.7f, 4.8f, 0.0f,

            -0.2f + 0.7f, 3.7f, 0.2f,
            0.2f + 0.7f, 3.7f, 0.2f,
            0.0f + 0.7f, 4.8f, 0.0f,

            0.2f + 0.7f, 3.7f, 0.2f,
            0.2f + 0.7f, 3.7f, -0.2f,
            0.0f + 0.7f, 4.8f, 0.0f,

            0.2f + 0.7f, 3.7f, -0.2f,
            -0.2f + 0.7f, 3.7f, -0.2f,
            0.0f + 0.7f, 4.8f, 0.0f,
    };

    for (int i = 0; i < 8*3*3; ++i) {
        vertext_buffer_data4[i]*= 3.0f;
    }

    this->object4 = create3DObject(GL_TRIANGLES, 8 * 3, vertext_buffer_data4, COLOR_GREY, GL_FILL);

    GLfloat g_vertex_buffer_data[579];

    for (int i = 0; i <= 63; ++i) {
        g_vertex_buffer_data[i*9] = 0.0f;
        g_vertex_buffer_data[i*9+1] = 0.0f;
        g_vertex_buffer_data[i*9+2] = 0.0f;
        if (i==0){
            g_vertex_buffer_data[i*9+3] = 0.0f;
            g_vertex_buffer_data[i*9+4] = 0.2;
            g_vertex_buffer_data[i*9+5] = 0.0f;
        }
        else{
            g_vertex_buffer_data[i*9+3] = g_vertex_buffer_data[(i-1)*9+6];
            g_vertex_buffer_data[i*9+4] = g_vertex_buffer_data[(i-1)*9+7];
            g_vertex_buffer_data[i*9+5] = g_vertex_buffer_data[(i-1)*9+8];
        }
        g_vertex_buffer_data[i*9+6] = (float)cos(-0.1)*g_vertex_buffer_data[i*9+3] - (float)sin(-0.1)*g_vertex_buffer_data[i*9+4];
        g_vertex_buffer_data[i*9+7] = (float)sin(-0.1)*g_vertex_buffer_data[i*9+3] + (float)cos(-0.1)*g_vertex_buffer_data[i*9+4];
        g_vertex_buffer_data[i*9+8] = 0.0f;
    }

    for (int i = 0; i <= 63; ++i) {
        g_vertex_buffer_data[i * 9] -= 0.5f;
        g_vertex_buffer_data[i * 9 + 1] += 3.0f;
        g_vertex_buffer_data[i * 9 + 2] += 0.51f;
        g_vertex_buffer_data[i * 9 + 3] -= 0.5f;
        g_vertex_buffer_data[i * 9 + 4] += 3.0f;
        g_vertex_buffer_data[i * 9 + 5] += 0.51f;
        g_vertex_buffer_data[i * 9 + 6] -= 0.5f;
        g_vertex_buffer_data[i * 9 + 7] += 3.0f;
        g_vertex_buffer_data[i * 9 + 8] += 0.51f;
    }

    for (int i = 0; i < 63*3*3; ++i) {
        g_vertex_buffer_data[i]*= 3.0f;
    }

    this->object5 = create3DObject(GL_TRIANGLES, 63 * 3, g_vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);

    for (int i = 0; i <= 63; ++i) {
        g_vertex_buffer_data[i * 9] += 3.0f;
        g_vertex_buffer_data[i * 9 + 3] += 3.0f;
        g_vertex_buffer_data[i * 9 + 6] += 3.0f;
    }

    this->object6 = create3DObject(GL_TRIANGLES, 63 * 3, g_vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);

    for (int i = 0; i <= 63; ++i) {
        g_vertex_buffer_data[i * 9 + 2] -= 3.04f;
        g_vertex_buffer_data[i * 9 + 5] -= 3.04f;
        g_vertex_buffer_data[i * 9 + 8] -= 3.04f;
    }

    this->object7 = create3DObject(GL_TRIANGLES, 63 * 3, g_vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);

    for (int i = 0; i <= 63; ++i) {
        g_vertex_buffer_data[i * 9] -= 3.0f;
        g_vertex_buffer_data[i * 9 + 3] -= 3.0f;
        g_vertex_buffer_data[i * 9 + 6] -= 3.0f;
    }

    this->object8 = create3DObject(GL_TRIANGLES, 63 * 3, g_vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);

    GLfloat vertex_buffer_data9[] = {
            -0.35f, 2.5f + 0.0f, 0.51f,
            0.35f, 2.5f + 0.0f, 0.51f,
            -0.35f, 2.5f + -0.35f, 0.51f,

            -0.35f, 2.5f + -0.35f, 0.51f,
            0.35f, 2.5f + -0.35f, 0.51f,
            0.35f, 2.5f + 0.0f, 0.51f,
    };

    for (int i = 0; i < 2*3*3; ++i) {
        vertex_buffer_data9[i]*= 3.0f;
    }

    this->object9 = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data9, COLOR_ORANGE, GL_FILL);

    GLfloat vertex_buffer_data10[] = {
            -0.35f, 2.5f + 0.0f, -0.51f,
            0.35f, 2.5f + 0.0f, -0.51f,
            -0.35f, 2.5f + -0.35f, -0.51f,

            -0.35f, 2.5f + -0.35f, -0.51f,
            0.35f, 2.5f + -0.35f, -0.51f,
            0.35f, 2.5f + 0.0f, -0.51f,
    };

    for (int i = 0; i < 2*3*3; ++i) {
        vertex_buffer_data10[i]*= 3.0f;
    }

    this->object10 = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data10, COLOR_ORANGE, GL_FILL);
}

void Boss::draw(glm::mat4 VP) {
    this->rotation += 3.0f;
//    for (this->rotation = 0; this->rotation<180; this->rotation+=2){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if (this->health>=2)
        draw3DObject(this->object);
    if (this->health>=1){
        draw3DObject(this->object2);
        draw3DObject(this->object3);
    }
    if (this->health>=5)
        draw3DObject(this->object4);
    if (this->health>=3){
        draw3DObject(this->object5);
        draw3DObject(this->object6);
        draw3DObject(this->object7);
        draw3DObject(this->object8);
    }
    if (this->health>=4){
        draw3DObject(this->object9);
        draw3DObject(this->object10);
    }
//    }
}

void Boss::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boss::tick() {
//    this->speed += this->gravity;
//    this->position.y += speed;
//    if (this->position.y < -0.2)
//        this->speed = 0.03f;
//    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

