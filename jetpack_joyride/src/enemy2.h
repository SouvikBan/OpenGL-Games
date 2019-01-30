#include "main.h"

#ifndef ENEMY2_H
#define ENEMY2_H


class Enemy2 {
public: 
    Enemy2() {}
    Enemy2(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    int direction;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *leftcircle, *rightcircle, *rectangle;
};

#endif  // ENEMY2_H