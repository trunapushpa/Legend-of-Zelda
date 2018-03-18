#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z, float width, float length, float height) {
    this->health = 5;
    this->points = 0;
    this->width = width;
    this->length = length;
    this->height = height;
    this->position = glm::vec3(x, y, z);
    this->hcam = glm::vec3(x, y + 2 * this->height, z + (this->length));
    this->tcam = glm::vec3(x, 6, z - 7.0f);
    this->rotation = 0;
    this->gravity = -0.01f;
    this->cannon_roty = 30.0f;
    this->cannon_rotz = 0.0f;
    this->acceleration = -0.0009f;
    speed = 0;
    speedy = 0;

    float w = width / 2, l = length / 2;

    static const GLfloat base_rect[] = {
            -w, 0.0f, -l,
            w, 0.0f, -l,
            -w, 0.0f, l,
            -w, 0.0f, l,
            w, 0.0f, l,
            w, 0.0f, -l
    };

    this->base = create3DObject(GL_TRIANGLES, 2 * 3, base_rect, COLOR_GREEN, GL_FILL);

    static const GLfloat sides_rect[] = {
            -w, 0.0f, -l,
            -w, 0.0f, l,
            -w - 0.7f * w, height, -l,
            -w - 0.7f * w, height, -l,
            -w - 0.7f * w, height, l,
            -w, 0.0f, l,

            w, 0.0f, -l,
            w, 0.0f, l,
            w + 0.7f * w, height, -l,
            w + 0.7f * w, height, -l,
            w + 0.7f * w, height, l,
            w, 0.0f, l,
    };

    this->sides = create3DObject(GL_TRIANGLES, 4 * 3, sides_rect, COLOR_LBROWN, GL_FILL);

    static const GLfloat back_trgs[] = {
            -w, 0.0f, -l,
            w, 0.0f, -l,
            -w - 0.7f * w, height, -l,
            -w - 0.7f * w, height, -l,
            w + 0.7f * w, height, -l,
            w, 0.0f, -l,
    };

    this->back = create3DObject(GL_TRIANGLES, 2 * 3, back_trgs, COLOR_BROWN, GL_FILL);

    static const GLfloat front_trgs[] = {
            -w, 0.0f, l,
            w, 0.0f, l,
            -w - 0.7f * w, height, l,
            -w - 0.7f * w, height, l,
            w + 0.7f * w, height, l,
            w, 0.0f, l,

            w + 0.7f * w, height, l,
            -w - 0.7f * w, height, l,
            0.0f, 2 * height, l,
    };

    this->front = create3DObject(GL_TRIANGLES, 3 * 3, front_trgs, COLOR_BROWN, GL_FILL);

    static const GLfloat cannon_trgls[] = {
            -0.10f, 0.21f, 0.0f, // triangle 1 : begin
            -0.10f, 0.21f, 1.65f,
            -0.10f, 0.41f, 1.65f, // triangle 1 : end
            0.10f, 0.41f, 0.0f, // triangle 2 : begin
            -0.10f, 0.21f, 0.0f,
            -0.10f, 0.41f, 0.0f, // triangle 2 : end
            0.10f, 0.21f, 1.65f,
            -0.10f, 0.21f, 0.0f,
            0.10f, 0.21f, 0.0f,
            0.10f, 0.41f, 0.0f,
            0.10f, 0.21f, 0.0f,
            -0.10f, 0.21f, 0.0f,
            -0.10f, 0.21f, 0.0f,
            -0.10f, 0.41f, 1.65f,
            -0.10f, 0.41f, 0.0f,
            0.10f, 0.21f, 1.65f,
            -0.10f, 0.21f, 1.65f,
            -0.10f, 0.21f, 0.0f,
            -0.10f, 0.41f, 1.65f,
            -0.10f, 0.21f, 1.65f,
            0.10f, 0.21f, 1.65f,
            0.10f, 0.41f, 1.65f,
            0.10f, 0.21f, 0.0f,
            0.10f, 0.41f, 0.0f,
            0.10f, 0.21f, 0.0f,
            0.10f, 0.41f, 1.65f,
            0.10f, 0.21f, 1.65f,
            0.10f, 0.41f, 1.65f,
            0.10f, 0.41f, 0.0f,
            -0.10f, 0.41f, 0.0f,
            0.10f, 0.41f, 1.65f,
            -0.10f, 0.41f, 0.0f,
            -0.10f, 0.41f, 1.65f,
            0.10f, 0.41f, 1.65f,
            -0.10f, 0.41f, 1.65f,
            0.10f, 0.21f, 1.65f,
    };

    this->cannon = create3DObject(GL_TRIANGLES, 12 * 3, cannon_trgls, COLOR_RED, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->front);
    draw3DObject(this->base);
    draw3DObject(this->sides);
    draw3DObject(this->back);
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate(this->position);    // glTranslatef
//    rotate = glm::rotate((float) ((this->cannon_roty) * M_PI / 180.0f), glm::vec3(-1, 0, 0));
    rotate = glm::rotate((float) ((this->rotation + this->cannon_rotz) * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate *= glm::rotate((float) ((this->cannon_roty) * M_PI / 180.0f), glm::vec3(-1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->cannon);
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->hcam = glm::vec3(x, y + 2 * this->height, z + (this->length));
    this->hcam.x = this->position.x + 2.0f * (float) sin(this->rotation * M_PI / 180.0f);
    this->hcam.z = this->position.z + 2.0f * (float) cos(this->rotation * M_PI / 180.0f);
    this->tcam.x = this->position.x - 7.0f * (float) sin(this->rotation * M_PI / 180.0f);
    this->tcam.z = this->position.z - 7.0f * (float) cos(this->rotation * M_PI / 180.0f);
}

void Boat::rotate(float angle) {
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
    this->hcam.x = this->position.x + 2.0f * (float) sin(this->rotation * M_PI / 180.0f);
    this->hcam.z = this->position.z + 2.0f * (float) cos(this->rotation * M_PI / 180.0f);
    this->tcam.x = this->position.x - 7.0f * (float) sin(this->rotation * M_PI / 180.0f);
    this->tcam.z = this->position.z - 7.0f * (float) cos(this->rotation * M_PI / 180.0f);
}

void Boat::set_rot(float angle){
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
    this->hcam.x = this->position.x + 2.0f * (float) sin(this->rotation * M_PI / 180.0f);
    this->hcam.z = this->position.z + 2.0f * (float) cos(this->rotation * M_PI / 180.0f);
    this->tcam.x = this->position.x - 7.0f * (float) sin(this->rotation * M_PI / 180.0f);
    this->tcam.z = this->position.z - 7.0f * (float) cos(this->rotation * M_PI / 180.0f);
}

void Boat::tick(float wind_mag, float wind_angle) {
    wind_angle += 180.0f;
    float brot = this->rotation + 180.0f;
    this->acceleration = -0.005f;
    if (cos((wind_angle - brot) * M_PI / 180.0f) > 0) {
        this->acceleration = wind_mag * (float) cos((wind_angle - brot) * M_PI / 180.0f);
    }
    this->speed += acceleration;
    if (this->speed > 0.6f)
        this->speed = 0.6f;
    this->speedy += gravity;
    this->position.y += this->speedy;
    if (this->position.y <0.12f)
        this->speedy = 0.1f;
    if (this->speed < 0)
        this->speed = 0;

//    std::cout << this->position.y << std::endl;

    this->set_position(this->position.x + (this->speed) * (float) sin(this->rotation * M_PI / 180.0f), this->position.y,
                       this->position.z + (this->speed) * (float) cos(this->rotation * M_PI / 180.0f));
//    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

