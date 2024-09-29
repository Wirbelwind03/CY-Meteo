#include "headers/vector.h"

Vector2i vector2i(int x, int y){
    Vector2i result = { x, y };
    return result;
}

Vector2i vector2i_add(Vector2i u, Vector2i v){
    Vector2i result = { u.x + v.x, u.y + v.y };
    return result;
}

Vector2f vector2f(float x, float y){
    Vector2f result = { x, y };
    return result;
}

Vector2f vector2f_add(Vector2f u, Vector2f v){
    Vector2f result = { u.x + v.x, u.y + v.y };
    return result;
}

Vector2f vector2f_dividei(Vector2f u, int x){
    Vector2f result = { u.x / x, u.y / x};
    return result;
}
