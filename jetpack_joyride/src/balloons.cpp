#include "balloons.h"
#include "main.h"

Balloon::Balloon(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->velocity = 0;
    speed = 1;
    int const n = 10000 ;
    static GLfloat vertex_buffer_data[9*n], body_buffer_data[9*n];
    
    for(int i=0;i<n;i++)
    {
        body_buffer_data[9*i]=(0.2*cos(i*2*3.14159/n));
        body_buffer_data[9*i+1]=(0.2*sin(i*2*3.14159/n));
        body_buffer_data[9*i+2]=0.0;

        body_buffer_data[9*i+3]=(0.2*cos((i+1)*2*3.14159/n));
        body_buffer_data[9*i+4]=(0.2*sin((i+1)*2*3.14159/n));
        body_buffer_data[9*i+5]=0.0;

        body_buffer_data[9*i+6]=0.0;
        body_buffer_data[9*i+7]=0.0;
        body_buffer_data[9*i+8]=0.0;
        
        vertex_buffer_data[9*i]=(0.05*cos(i*2*3.14159/n));
        vertex_buffer_data[9*i+1]=-0.25-(0.05*sin(i*2*3.14159/n));
        vertex_buffer_data[9*i+2]=0.0;

        vertex_buffer_data[9*i+3]=(0.05*cos((i+1)*2*3.14159/n));
        vertex_buffer_data[9*i+4]=-0.25-(0.05*sin((i+1)*2*3.14159/n));
        vertex_buffer_data[9*i+5]=0.0;

        vertex_buffer_data[9*i+6]=0.0;
        vertex_buffer_data[9*i+7]=-0.25;
        vertex_buffer_data[9*i+8]=0.0;

    }

    this->tip = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
    this->body = create3DObject(GL_TRIANGLES, n*3, body_buffer_data, color, GL_FILL);
}

void Balloon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->tip);
    draw3DObject(this->body);
}

void Balloon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Balloon::tick() {
    //this->rotation += speed;
    this->position.x += speed/15;
    this->position.y -= this->velocity/80;
}

bounding_box_t Balloon::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y , 0.4,0.5};
    return bbox;
}