#include "fire.h"
#include "main.h"
#include <cmath>

Fire::Fire(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 1;
    bool res = loadOBJ("../src/fire.obj",this->vertices, this->uvs, this->normals);
    GLfloat colour_buffer_data[this->vertices.size() * 3];

    for(int i=0; i<this->vertices.size();i++)
    {
        colour_buffer_data[3*i]=255.0f/256.0f;
        colour_buffer_data[3*i+1]=140.0f/256.0f;
        colour_buffer_data[3*i+2]=0.0f/256.0f;
    }
    // GLuint vertexbuffer;
	glGenBuffers(1, &this->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);

	// GLuint uvbuffer;
	// glGenBuffers(1, &this->uvbuffer);
	// glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
    // glBufferData(GL_ARRAY_BUFFER, this->uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->colourbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->colourbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colour_buffer_data),colour_buffer_data , GL_STATIC_DRAW);
}

void Fire::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);  
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate );
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
    glBindBuffer(GL_ARRAY_BUFFER, this->colourbuffer);
    glVertexAttribPointer(
        1,                                // attribute
        3,                                // size
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

void Fire::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Fire::tick() {
    float denom = sqrt((this->x_vec*this->x_vec)+(this->y_vec*this->y_vec)+(this->z_vec*this->z_vec));
    this->position.x -= (this->speed/12.0f)*(this->x_vec)/(denom);
    this->position.y -= (this->speed/12.0f)*(this->y_vec)/(denom);
    this->position.z -= (this->speed/12.0f)*(this->z_vec)/(denom);
    // printf("xmove:%f", this->x_vec);
}

bounding_box_t Fire::bounding_box() {
    float x = this->position.x, y = this->position.y, z=this->position.z;
    bounding_box_t bbox = { x, y , z, 0.2  };
    return bbox;
}