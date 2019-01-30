#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    
    static const GLfloat body_buffer_data[] = {
        -0.25f,-0.15f,0.0f,
        -0.25f,-0.65f,0.0f,
         0.25f,-0.65f,0.0f,
         0.25f,-0.65f,0.0f,
         0.25f,-0.15f,0.0f,
        -0.25f,-0.15f,0.0f,
    };

    static const GLfloat jet_buffer_data[] = {
        -0.25f,-0.20f,0.0f,
        -0.35f,-0.20f,0.0f,
        -0.35f,-0.60f,0.0f,
        -0.35f,-0.60f,0.0f,
        -0.25f,-0.60f,0.0f,
        -0.25f,-0.20f,0.0f
    };

    int const n = 500;
    static GLfloat circle_buffer_data[9*n];
    
    for(int i=0;i<n;i++)
    {
        circle_buffer_data[9*i]=(0.15*cos(i*2*3.14159/n));
        circle_buffer_data[9*i+1]=(0.15*sin(i*2*3.14159/n));
        circle_buffer_data[9*i+2]=0.0;

        circle_buffer_data[9*i+3]=(0.15*cos((i+1)*2*3.14159/n));
        circle_buffer_data[9*i+4]=(0.15*sin((i+1)*2*3.14159/n));
        circle_buffer_data[9*i+5]=0.0;

        circle_buffer_data[9*i+6]=0.0;
        circle_buffer_data[9*i+7]=0.0;
        circle_buffer_data[9*i+8]=0.0;

    }
    this->circle = create3DObject(GL_TRIANGLES, n*3, circle_buffer_data, COLOR_SKIN, GL_FILL);
    this->rectangle = create3DObject(GL_TRIANGLES, 2*3, body_buffer_data, COLOR_PLAYER, GL_FILL);
    this->jetpack = create3DObject(GL_TRIANGLES, 2*3, jet_buffer_data, COLOR_JETPACK, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->circle);
    draw3DObject(this->rectangle);
    draw3DObject(this->jetpack);
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick(int direction, bool jump, float velocity) {
    //this->rotation += speed;
    if(!jump)
    {
        this->position.x += direction*speed/40;
        this->position.y -= velocity/50;
    }
    else
        this->position.y += direction*speed/10;
}

bounding_box_t Player::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y , 0.6, 0.8  };
    return bbox;
}