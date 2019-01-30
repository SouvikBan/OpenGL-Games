#include "main.h"

#ifndef PROPULSION_H
#define PROPULSION_H


class Propulsion {
public:
    Propulsion() {}
    Propulsion(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // PROPULSION_H
