#include "sea.h"
#include "main.h"

Sea::Sea(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    
    static const GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        20000.0f, 0.0f, 0.0f,
        20000.0f, 0.0f, 20000.0f,
        20000.0f, 0.0f, 20000.0f,
        0.0f, 0.0f, 20000.0f,
        0.0f, 0.0f, 0.0f 
    };

    static const GLfloat colour_buffer_data[] = {
        32.0f/256.0f, 178.0f/256.0f, 170.0f/256.0f,
        32.0f/256.0f, 178.0f/256.0f, 170.0f/256.0f,
        32.0f/256.0f, 178.0f/256.0f, 170.0f/256.0f,
        32.0f/256.0f, 178.0f/256.0f, 170.0f/256.0f,
        32.0f/256.0f, 178.0f/256.0f, 170.0f/256.0f,
        32.0f/256.0f, 178.0f/256.0f, 170.0f/256.0f,
    };

    // GLuint vertexbuffer;
	glGenBuffers(1, &this->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data , GL_STATIC_DRAW);

	// GLuint colourbuffer;
	glGenBuffers(1, &this->colourbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->colourbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colour_buffer_data), colour_buffer_data , GL_STATIC_DRAW);

}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);  
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    GLuint vao;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    
    //1st attribute buffer : vertices
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

    // 2nd attribute buffer : colour
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

    glDrawArrays(GL_TRIANGLES, 0, 18 );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteVertexArrays(1, &vao);
}

void Sea::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Sea::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

