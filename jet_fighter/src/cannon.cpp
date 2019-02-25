#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 180;
    this->speed = 0;
    bool res = loadOBJ("../src/cannon.obj",this->vertices, this->uvs, this->normals);
    GLfloat colour_buffer_data[this->vertices.size() * 3];

    for(int i=0; i<this->vertices.size();i++)
    {
        colour_buffer_data[3*i]=100.0f/256.0f;
        colour_buffer_data[3*i+1]=30.0f/256.0f;
        colour_buffer_data[3*i+2]=22.0f/256.0f;
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

void Cannon::draw(glm::mat4 VP) {
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

void Cannon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {
    //this->rotation += speed;
    this->position.z += this->speed/120.0f;
    // this->position.y -= speed;
}

bounding_box_t Cannon::bounding_box() {
    float x = this->position.x, y = this->position.y, z=this->position.z;
    bounding_box_t bbox = { x, y , z, 1  };
    return bbox;
}