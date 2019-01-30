#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public: 
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int direction, bool jump, float velocity);
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *circle, *rectangle, *jetpack;
};

#endif  // PLAYER_H