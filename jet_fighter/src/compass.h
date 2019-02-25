#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z,float angle);
    glm::vec3 position;
    float rotation;
    GLuint vertexbuffer;
    GLuint colorbuffer;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(float angle);
private:
    VAO *object;
};

#endif // COMPASS_H