#include "propulsion.h"
#include "main.h"

Propulsion::Propulsion(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 180;
    speed = 1;
    GLfloat outer_buffer_data[100000], inner_buffer_data[100000];
    int j=0;
    int angle = 0;
    for (int i=0; i<540; i++) {
        if(i%3==0){
            outer_buffer_data[j++] = 0.0f;
            outer_buffer_data[j++] = 0.0f;
            outer_buffer_data[j++] = 0.0f;
        } else if(i%3==1) {
            outer_buffer_data[j++] = 0.3*cos((angle*3.1428)/180);
            outer_buffer_data[j++] = 0.3*sin((angle*3.1428)/180);
            outer_buffer_data[j++] = 0.0f;
            angle+=1;
        } else {
            outer_buffer_data[j++] = 0.3*cos((angle*3.1428)/180);
            outer_buffer_data[j++] = 0.3*sin((angle*3.1428)/180);
            outer_buffer_data[j++] = 0.0f;
        }
    }

    this->object = create3DObject(GL_TRIANGLES, 540, outer_buffer_data, color, GL_FILL);
}

void Propulsion::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Propulsion::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Propulsion::tick() {
    //this->rotation += speed;
    this->position.y -= speed/60;
}

