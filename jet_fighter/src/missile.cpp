#include "missile.h"
#include "main.h"

Missile::Missile(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 180;
    this->speed = 20;
    bool res = loadOBJ("../src/missile.obj",this->vertices, this->uvs, this->normals);
   
    // GLuint vertexbuffer;
	glGenBuffers(1, &this->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);

	// GLuint uvbuffer;
	glGenBuffers(1, &this->uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, this->uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);

}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);  
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 yaw     = glm::rotate((float) (this->yaw_angle * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 pitch   = glm::rotate((float) (this->pitch_angle * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 roll  =  glm::rotate((float) (this->roll_angle * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate * yaw * pitch * roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    GLuint vao;

    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
    glVertexAttribPointer(
        1,                                // attribute
        2,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteVertexArrays(1, &vao);

}

void Missile::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Missile::tick() {
    this->position.z += this->speed/120.0f*cos(this->yaw_angle*M_PI / 180.0f);
    this->position.x += this->speed/120.0f* sin(this->yaw_angle * M_PI / 180.0f);
    this->position.y += this->speed/120.0f*sin(this->pitch_angle * M_PI / 180.0f);
}

bounding_box_t Missile::bounding_box() {
    float x = this->position.x, y = this->position.y, z=this->position.z;
    bounding_box_t bbox = { x, y , z, 1  };
    return bbox;
}
