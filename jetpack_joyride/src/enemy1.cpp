#include "enemy1.h"
#include "main.h"

Enemy1::Enemy1(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = rand()%180;
    speed = 1;
    int const n = 10000;
    static GLfloat leftcircle_buffer_data[9*n];
    static GLfloat rightcircle_buffer_data[9*n];
    static const GLfloat rectangle_buffer_data[] = {
        0.0f, -0.025f, 0.0f, 
        1.0f, -0.025f, 0.0f,
        1.0f, 0.025f, 0.0f,
        1.0f, 0.025f, 0.0f,
        0.0f, 0.025f, 0.0f,
        0.0f, -0.025f, 0.0f
    };

    
    for(int i=0;i<n;i++)
    {
        leftcircle_buffer_data[9*i]=(0.2*cos(i*2*3.14159/n));
        leftcircle_buffer_data[9*i+1]=(0.2*sin(i*2*3.14159/n));
        leftcircle_buffer_data[9*i+2]=0.0;

        leftcircle_buffer_data[9*i+3]=(0.2*cos((i+1)*2*3.14159/n));
        leftcircle_buffer_data[9*i+4]=(0.2*sin((i+1)*2*3.14159/n));
        leftcircle_buffer_data[9*i+5]=0.0;

        leftcircle_buffer_data[9*i+6]=0.0;
        leftcircle_buffer_data[9*i+7]=0.0;
        leftcircle_buffer_data[9*i+8]=0.0;

        rightcircle_buffer_data[9*i]=1.0+(0.2*cos(i*2*3.14159/n));
        rightcircle_buffer_data[9*i+1]=(0.2*sin(i*2*3.14159/n));
        rightcircle_buffer_data[9*i+2]=0.0;

        rightcircle_buffer_data[9*i+3]=1.0+(0.2*cos((i+1)*2*3.14159/n));
        rightcircle_buffer_data[9*i+4]=(0.2*sin((i+1)*2*3.14159/n));
        rightcircle_buffer_data[9*i+5]=0.0;

        rightcircle_buffer_data[9*i+6]=1.0;
        rightcircle_buffer_data[9*i+7]=0.0;
        rightcircle_buffer_data[9*i+8]=0.0;
    }
    

    this->rectangle = create3DObject(GL_TRIANGLES, 2*3, rectangle_buffer_data, COLOR_ENEMY1_FIRE, GL_FILL);
    this->rightcircle = create3DObject(GL_TRIANGLES, n*3, rightcircle_buffer_data, COLOR_ENEMY1_OBJECT, GL_FILL);
    this->leftcircle = create3DObject(GL_TRIANGLES, n*3, leftcircle_buffer_data, COLOR_ENEMY1_OBJECT, GL_FILL);    
}

void Enemy1::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->rectangle);
    draw3DObject(this->leftcircle);
    draw3DObject(this->rightcircle);
}

void Enemy1::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy1::tick(int direction, bool jump) {
    
    if(!jump)
    {
        this->position.x += direction*speed/60;
    }
    else {
        this->position.y += direction*speed/20;
    }
}
