#include "main.h"

#ifndef BALLOON_H
#define BALLOON_H


class Balloon {
public:
    Balloon() {}
    Balloon(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float velocity;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
    double speed;
private:
    VAO *tip, *body;
};

#endif // BALLOON_H
