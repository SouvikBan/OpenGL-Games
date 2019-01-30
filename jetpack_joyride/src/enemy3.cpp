#include "enemy3.h"
#include "main.h"

Enemy3::Enemy3(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->direction = 1;
    speed = 1;
    static const GLfloat up_buffer_data[] = {
        0.0f, 0.0f, 0.0f, 
        0.2f, 0.0f, 0.0f,
        0.4f, 0.3f, 0.0f,
        0.4f, 0.3f, 0.0f,
        0.2f, 0.3f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    static const GLfloat down_buffer_data[] = {
        0.0f, 0.0f, 0.0f, 
        0.2f, 0.0f, 0.0f,
        0.4f, -0.3f, 0.0f,
        0.4f, -0.3f, 0.0f,
        0.2f, -0.3f, 0.0f,
        0.0f, 0.0f, 0.0f
    };
    
   


    this->up = create3DObject(GL_TRIANGLES, 2*3, up_buffer_data, color, GL_FILL);
    this->down = create3DObject(GL_TRIANGLES, 2*3, down_buffer_data, color, GL_FILL);
   
}

void Enemy3::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->up);
    draw3DObject(this->down);
}

void Enemy3::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy3::tick(float velocity_x, float velocity_y) {
    this->position.x -= velocity_x/40;
    this->position.y += velocity_y/80; 
}

bounding_box_t Enemy3::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y , 0.2, 0.4};
    return bbox;
}