#include "main.h"

#ifndef FIGHTER_H
#define FIGHTER_H


class Fighter {
public:
    Fighter() {}
    Fighter(float x, float y, float z);
    glm::vec3 position;
    float rotation,pitch_angle,roll_angle,yaw_angle;
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;
    GLuint vertexbuffer, uvbuffer;
    int life, fuel;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // FIGHTER_H
