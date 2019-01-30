#include "dragon.h"
#include "main.h"

Dragon::Dragon(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    
    static const GLfloat body_buffer_data[] = {
        0.3f, 1.0f, 0.0f,
        3.3f, 1.0f, 0.0f,
        3.3f,-1.0f, 0.0f,
        3.3f,-1.0f, 0.0f,
        0.3f,-1.0f, 0.0f,
        0.3f, 1.0f, 0.0f
    };

    int const n = 500;
    static GLfloat head_buffer_data[9*n];
    
    for(int i=0;i<n;i++)
    {
        head_buffer_data[9*i]=(0.3*cos(i*2*3.14159/n));
        head_buffer_data[9*i+1]=(0.3*sin(i*2*3.14159/n));
        head_buffer_data[9*i+2]=0.0;

        head_buffer_data[9*i+3]=(0.3*cos((i+1)*2*3.14159/n));
        head_buffer_data[9*i+4]=(0.3*sin((i+1)*2*3.14159/n));
        head_buffer_data[9*i+5]=0.0;

        head_buffer_data[9*i+6]=0.0;
        head_buffer_data[9*i+7]=0.0;
        head_buffer_data[9*i+8]=0.0;

    }
    this->head = create3DObject(GL_TRIANGLES, n*3, head_buffer_data, COLOR_HEAD, GL_FILL);
    this->body = create3DObject(GL_TRIANGLES, 2*3, body_buffer_data, COLOR_DRAGON, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->head);
    draw3DObject(this->body);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon::tick(float player_position) {
    if (player_position >= this->position.y)
        this->position.y += speed/40;
    else 
        this->position.y -= speed/40;
    
}


bounding_box_t Dragon::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y , 0.6, 0.8  };
    return bbox;
}