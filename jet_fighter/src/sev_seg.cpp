#include "sev_seg.h"
#include "main.h"

Seven::Seven(float x, float y, float z) {

    this->position = glm::vec3(x, y, z);
    this->rotation = 0;


    GLfloat a[] = { 
        -0.11f, 0.11f, 0.0f,
        -0.08f, 0.08f, 0.0f,
        0.11f, 0.11f, 0.0f,
        -0.08f, 0.08f, 0.0f,
        0.11f, 0.11f, 0.0f,
        0.08f, 0.08f, 0.0f
    };

    GLfloat b[] = {
        -0.11f, 0.11f, 0.0f,
        -0.08f, 0.08f, 0.0f,
        -0.08f, 0.02f, 0.0f,
        -0.11f, 0.11f, 0.0f,
        -0.08f, 0.08f, 0.0f,
        -0.11f, 0.02f, 0.0f
    };

    GLfloat c[] = {
        -0.11f, -0.11f, 0.0f,
        -0.08f, -0.08f, 0.0f,
        -0.08f, -0.02f, 0.0f,
        -0.11f, -0.11f, 0.0f,
        -0.08f, -0.08f, 0.0f,
        -0.11f, -0.02f, 0.0f
    };

    GLfloat d[] = {
        -0.11f, -0.11f, 0.0f,
        -0.08f, -0.08f, 0.0f,
        0.11f, -0.11f, 0.0f,
        -0.08f, -0.08f, 0.0f,
        0.11f, -0.11f, 0.0f,
        0.08f, -0.08f, 0.0f
    };

    GLfloat e[] = {
        0.11f, -0.11f, 0.0f,
        0.08f, -0.08f, 0.0f,
        0.08f, -0.02f, 0.0f,
        0.11f, -0.11f, 0.0f,
        0.08f, -0.08f, 0.0f,
        0.11f, -0.02f, 0.0f
    };

    GLfloat f[] = {
        0.11f, 0.11f, 0.0f,
        0.08f, 0.08f, 0.0f,
        0.08f, 0.02f, 0.0f,
        0.11f, 0.11f, 0.0f,
        0.08f, 0.08f, 0.0f,
        0.11f, 0.02f, 0.0f
    };

    GLfloat g[] = {
        -0.08f, 0.02f, 0.0f,
        -0.08f, -0.02f, 0.0f,
        0.08f, 0.02f, 0.0f,
        -0.08f, -0.02f, 0.0f,
        0.08f, 0.02f, 0.0f,
        0.08f, -0.02f, 0.0f
    };

    

    glGenBuffers(1, &this->a_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->a_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(a), a, GL_STATIC_COPY_ARB);


    glGenBuffers(1, &this->b_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->b_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(b), b, GL_STATIC_COPY_ARB);


    glGenBuffers(1, &this->c_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->c_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(c), c, GL_STATIC_COPY_ARB);

    glGenBuffers(1, &this->d_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->d_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(d), d, GL_STATIC_COPY_ARB);


    glGenBuffers(1, &this->e_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->e_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(e), e, GL_STATIC_COPY_ARB);


    glGenBuffers(1, &this->f_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->f_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(f), f, GL_STATIC_COPY_ARB);

    glGenBuffers(1, &this->g_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->g_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g), g, GL_STATIC_COPY_ARB);

}

void Seven::draw(glm::mat4 VP, int light) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of seven arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    GLuint vao;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);

    if (light == 0) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->a_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (light == 1) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->b_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (light == 2) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->c_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (light == 3) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->d_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (light == 4) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->e_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (light == 5) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->f_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (light == 6) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->g_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

}

void Seven::draw_num(glm::mat4 VP, int digit) {
    switch (digit)
    {
        case 0:
            this->draw(VP, 0);
            this->draw(VP, 1);
            this->draw(VP, 2);
            this->draw(VP, 3);
            this->draw(VP, 4);
            this->draw(VP, 5);
            break;
    
        case 1:
            this->draw(VP, 1);
            this->draw(VP, 2);
            break;
    
        case 2:
            this->draw(VP, 0);
            this->draw(VP, 1);
            this->draw(VP, 3);
            this->draw(VP, 4);
            this->draw(VP, 6);
            break;
    
        case 3:
            this->draw(VP, 0);
            this->draw(VP, 1);
            this->draw(VP, 2);
            this->draw(VP, 3);
            this->draw(VP, 6);
            break;
    
        case 4:
            this->draw(VP, 1);
            this->draw(VP, 2);
            this->draw(VP, 5);
            this->draw(VP, 6);
            break;
    
        case 5:
            this->draw(VP, 0);
            this->draw(VP, 5);
            this->draw(VP, 6);
            this->draw(VP, 2);
            this->draw(VP, 3);
            break;
    
        case 6:
            this->draw(VP, 0);
            this->draw(VP, 5);
            this->draw(VP, 6);
            this->draw(VP, 4);
            this->draw(VP, 2);
            this->draw(VP, 3);
            break;
    
        case 7:
            this->draw(VP, 0);
            this->draw(VP, 1);
            this->draw(VP, 2);
            break;
    
        case 8:
            this->draw(VP, 0);
            this->draw(VP, 1);
            this->draw(VP, 2);
            this->draw(VP, 3);
            this->draw(VP, 4);
            this->draw(VP, 5);
            this->draw(VP, 6);
            break;
    
        case 9:
            this->draw(VP, 0);
            this->draw(VP, 1);
            this->draw(VP, 2);
            this->draw(VP, 3);
            this->draw(VP, 5);
            this->draw(VP, 6);
            break;
    
            
        default:
            break;
    }
}

void Seven::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Seven::tick() {
    
}
