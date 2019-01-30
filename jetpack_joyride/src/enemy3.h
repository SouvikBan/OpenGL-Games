#include "main.h"

#ifndef ENEMY3_H
#define ENEMY3_H


class Enemy3 {
public: 
    Enemy3() {}
    Enemy3(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    int direction;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float velocity_x, float velocity_y);
    bounding_box_t bounding_box();
    double speed;
private:
    VAO *up, *down;
};

#endif  // ENEMY3_H