#include "land.h"
#include "main.h"

Land::Land(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    int n1 = 6;
    GLfloat vertex_buffer_data[9*n1],colour_buffer_data[9*n1];
    for(int i=0;i<n1;i++)
    {
        vertex_buffer_data[9*i]=(25*cos(i*2*3.14159/n1));
        colour_buffer_data[9*i]=14.0f/256.0f;
        
        vertex_buffer_data[9*i+1]=0.0;
        colour_buffer_data[9*i+1]=102.0f/256.0f;
        
        vertex_buffer_data[9*i+2]=(25*sin(i*2*3.14159/n1));
        colour_buffer_data[9*i+2]=85.0f/256.0f;
        
        vertex_buffer_data[9*i+3]=(25*cos((i+1)*2*3.14159/n1));
        colour_buffer_data[9*i+3]=14.0f/256.0f;
        
        vertex_buffer_data[9*i+4]=0.0;
        colour_buffer_data[9*i+4]=102.0f/256.0f;
        
        vertex_buffer_data[9*i+5]=(25*sin((i+1)*2*3.14159/n1));
        colour_buffer_data[9*i+5]=85.0f/256.0f;
        
        vertex_buffer_data[9*i+6]=0.0;
        colour_buffer_data[9*i+6]=14.0f/256.0f;
        
        vertex_buffer_data[9*i+7]=0.0;
        colour_buffer_data[9*i+7]=102.0f/256.0f;
        
        vertex_buffer_data[9*i+8]=0.0;
        colour_buffer_data[9*i+8]=85.0f/256.0f;

    }

    // GLuint vertexbuffer;
	glGenBuffers(1, &this->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data , GL_STATIC_DRAW);

	// GLuint colourbuffer;
	glGenBuffers(1, &this->colourbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->colourbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colour_buffer_data), colour_buffer_data , GL_STATIC_DRAW);

}

void Land::draw(glm::mat4 VP) {
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

    glDrawArrays(GL_TRIANGLES, 0, 72 );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteVertexArrays(1, &vao);
}

void Land::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Land::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

