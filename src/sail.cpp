#include "sail.h"
#include "main.h"

Sail::Sail(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat mast_trgls[] = {
            -0.03f,0.0f,-0.03f, // triangle 1 : begin
            -0.03f,0.0f, 0.03f,
            -0.03f, 3.85f, 0.03f, // triangle 1 : end
            0.03f, 3.85f,-0.03f, // triangle 2 : begin
            -0.03f,0.0f,-0.03f,
            -0.03f, 3.85f,-0.03f, // triangle 2 : end
            0.03f,0.0f, 0.03f,
            -0.03f,0.0f,-0.03f,
            0.03f,0.0f,-0.03f,
            0.03f, 3.85f,-0.03f,
            0.03f,0.0f,-0.03f,
            -0.03f,0.0f,-0.03f,
            -0.03f,0.0f,-0.03f,
            -0.03f, 3.85f, 0.03f,
            -0.03f, 3.85f,-0.03f,
            0.03f,0.0f, 0.03f,
            -0.03f,0.0f, 0.03f,
            -0.03f,0.0f,-0.03f,
            -0.03f, 3.85f, 0.03f,
            -0.03f,0.0f, 0.03f,
            0.03f,0.0f, 0.03f,
            0.03f, 3.85f, 0.03f,
            0.03f,0.0f,-0.03f,
            0.03f, 3.85f,-0.03f,
            0.03f,0.0f,-0.03f,
            0.03f, 3.85f, 0.03f,
            0.03f,0.0f, 0.03f,
            0.03f, 3.85f, 0.03f,
            0.03f, 3.85f,-0.03f,
            -0.03f, 3.85f,-0.03f,
            0.03f, 3.85f, 0.03f,
            -0.03f, 3.85f,-0.03f,
            -0.03f, 3.85f, 0.03f,
            0.03f, 3.85f, 0.03f,
            -0.03f, 3.85f, 0.03f,
            0.03f,0.0f, 0.03f,

            -0.03f,1.77f,0.0f, // triangle 1 : begin
            -0.03f,1.77f, 1.65f,
            -0.03f, 1.83f, 1.65f, // triangle 1 : end
            0.03f, 1.83f,0.0f, // triangle 2 : begin
            -0.03f,1.77f,0.0f,
            -0.03f, 1.83f,0.0f, // triangle 2 : end
            0.03f,1.77f, 1.65f,
            -0.03f,1.77f,0.0f,
            0.03f,1.77f,0.0f,
            0.03f, 1.83f,0.0f,
            0.03f,1.77f,0.0f,
            -0.03f,1.77f,0.0f,
            -0.03f,1.77f,0.0f,
            -0.03f, 1.83f, 1.65f,
            -0.03f, 1.83f,0.0f,
            0.03f,1.77f, 1.65f,
            -0.03f,1.77f, 1.65f,
            -0.03f,1.77f,0.0f,
            -0.03f, 1.83f, 1.65f,
            -0.03f,1.77f, 1.65f,
            0.03f,1.77f, 1.65f,
            0.03f, 1.83f, 1.65f,
            0.03f,1.77f,0.0f,
            0.03f, 1.83f,0.0f,
            0.03f,1.77f,0.0f,
            0.03f, 1.83f, 1.65f,
            0.03f,1.77f, 1.65f,
            0.03f, 1.83f, 1.65f,
            0.03f, 1.83f,0.0f,
            -0.03f, 1.83f,0.0f,
            0.03f, 1.83f, 1.65f,
            -0.03f, 1.83f,0.0f,
            -0.03f, 1.83f, 1.65f,
            0.03f, 1.83f, 1.65f,
            -0.03f, 1.83f, 1.65f,
            0.03f,1.77f, 1.65f,
    };

    this->mast = create3DObject(GL_TRIANGLES, 24*3, mast_trgls, COLOR_DGREEN, GL_FILL);

    static const GLfloat sail_trgl1[] = {
            0.0f, 3.8f, 0.0f,
            0.0f, 3.2f, 0.0f,
            0.0f, 3.2f, 1.0f,
    };

    static const GLfloat sail_trgl2[] = {
            0.0f, 3.2f, 0.0f,
            0.0f, 3.2f, 1.0f,
            0.0f, 1.8f, 0.0f,
    };

    static const GLfloat sail_trgl3[] = {
            0.0f, 1.8f, 0.0f,
            0.0f, 3.2f, 1.0f,
            0.0f, 1.8f, 1.6f,
    };

    this->sailc1 = create3DObject(GL_TRIANGLES, 3, sail_trgl1, COLOR_ORANGE, GL_FILL);
    this->sailc2 = create3DObject(GL_TRIANGLES, 3, sail_trgl2, COLOR_ORANGE, GL_FILL);
    this->sailc3 = create3DObject(GL_TRIANGLES, 3, sail_trgl3, COLOR_YELLOW, GL_FILL);
}

void Sail::draw(glm::mat4 VP, float wind_angle, float boat_angle) {
//    std::cout << wind_angle << std::endl;
    wind_angle += 180.0f;
    boat_angle += 180.0f;
    if (cos((wind_angle-boat_angle)*M_PI/180.0f)>0){
//        std::cout << wind_angle-boat_angle << std::endl;
//        std::cout << wind_angle << std::endl;
        if ((wind_angle-boat_angle < 0 || wind_angle - boat_angle>180) && wind_angle - boat_angle> -180){
            this->rotation = 90.0f+wind_angle;
//            std::cout << "Want This??\n";
        }
        else{
            this->rotation = -90.0f+wind_angle;
        }
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
        // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
        // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->mast);
        draw3DObject(this->sailc1);
        draw3DObject(this->sailc2);
        draw3DObject(this->sailc3);
    }
}

void Sail::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Sail::tick(glm::vec3 boatpos) {
    this->position = boatpos;
//    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

