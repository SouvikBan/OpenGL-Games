#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float player_position);
    bounding_box_t bounding_box();
    double speed;
private:
    VAO *head, *body;
};

#endif // DRAGON_H
