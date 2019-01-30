#include "projectiles.h"
#include "main.h"

Projectile::Projectile(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    int const n1 = 10000, n2 = 6 ;
    static GLfloat inner_buffer_data[9*n2], outer_buffer_data[9*n1];
    
    for(int i=0;i<n1;i++)
    {
        outer_buffer_data[9*i]=(0.3*cos(i*2*3.14159/n1));
        outer_buffer_data[9*i+1]=(0.3*sin(i*2*3.14159/n1));
        outer_buffer_data[9*i+2]=0.0;

        outer_buffer_data[9*i+3]=(0.3*cos((i+1)*2*3.14159/n1));
        outer_buffer_data[9*i+4]=(0.3*sin((i+1)*2*3.14159/n1));
        outer_buffer_data[9*i+5]=0.0;

        outer_buffer_data[9*i+6]=0.0;
        outer_buffer_data[9*i+7]=0.0;
        outer_buffer_data[9*i+8]=0.0;

    }
     for(int i=0;i<n2;i++)
    {
        inner_buffer_data[9*i]=(0.15*cos(i*2*3.14159/n2));
        inner_buffer_data[9*i+1]=(0.15*sin(i*2*3.14159/n2));
        inner_buffer_data[9*i+2]=0.0;

        inner_buffer_data[9*i+3]=(0.15*cos((i+1)*2*3.14159/n2));
        inner_buffer_data[9*i+4]=(0.15*sin((i+1)*2*3.14159/n2));
        inner_buffer_data[9*i+5]=0.0;

        inner_buffer_data[9*i+6]=0.0;
        inner_buffer_data[9*i+7]=0.0;
        inner_buffer_data[9*i+8]=0.0;

    }
    this->outerobject = create3DObject(GL_TRIANGLES, n1*3, outer_buffer_data, color, GL_FILL);
    this->innerobject = create3DObject(GL_TRIANGLES, n2*3, inner_buffer_data, COLOR_PLATFORM, GL_FILL);
}

void Projectile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->outerobject);
    draw3DObject(this->innerobject);

}

void Projectile::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Projectile::tick(float velocity) {
    this->position.x -= speed/30;
    this->position.y -= velocity/80;
}

bounding_box_t Projectile::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y , 0.6,0.6};
    return bbox;
}