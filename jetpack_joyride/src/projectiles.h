#include "main.h"

#ifndef PROJECTILES_H
#define PROJECTILES_H


class Projectile {
public:
    Projectile() {}
    Projectile(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float velocity);
    bounding_box_t bounding_box();
    double speed;
private:
    VAO *innerobject, *outerobject;
};

#endif // PROJECTILES_H
