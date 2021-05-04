#include "Entity.h"

Entity::Entity(){}

Entity::Entity(int x, int y, int width, int height) : x(x), y(y),
                        width(width), height(height), speedX(0), speedY(0){}

Entity::~Entity() {}