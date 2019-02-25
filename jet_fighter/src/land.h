#include "main.h"

#ifndef LAND_H
#define LAND_H


class Land {
public:
    Land() {}
    Land(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > colour;
    GLuint vertexbuffer, colourbuffer;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // LAND_H
