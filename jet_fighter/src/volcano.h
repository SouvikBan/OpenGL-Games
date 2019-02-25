#include "main.h"

#ifndef VOLCANO_H
#define VOLACNO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float z);
    glm::vec3 position;
    float rotation,pitch_angle,roll_angle,yaw_angle;
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;
    GLuint vertexbuffer, uvbuffer,colourbuffer;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // VOLCANO_H
