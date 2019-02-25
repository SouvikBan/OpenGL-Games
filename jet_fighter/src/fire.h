#include "main.h"

#ifndef FIRE_H
#define FIRE_H


class Fire {
public:
    Fire() {}
    Fire(float x, float y, float z);
    glm::vec3 position;
    float rotation,pitch_angle,roll_angle,yaw_angle,x_vec,y_vec,z_vec;
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

#endif // FIRE_H
