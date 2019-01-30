#include "main.h"

#ifndef WALLDESIGN_H
#define WALLDESIGN_H


class WallDesign {
public:
    WallDesign() {}
    WallDesign(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // WALLDESIGN_H
