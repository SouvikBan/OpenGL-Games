#include "main.h"

#ifndef FIGHTER_H
#define FIGHTER_H


class Fighter {
public:
    Fighter() {}
    Fighter(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;
    GLuint vertexbuffer, uvbuffer;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // FIGHTER_H
