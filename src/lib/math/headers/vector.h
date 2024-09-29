#ifndef VECTOR_H
#define VECTOR_H

// Vector 2D composed of two int
typedef struct {
    int x;
    int y;
} Vector2i;

// Construct a vector 2D composed of two int
Vector2i vector2i(int x, int y);

// Sum two vector 2D composed of two int
Vector2i vector2i_add(Vector2i u, Vector2i v);

// Vector 2D composed of two float
typedef struct {
    float x;
    float y;
} Vector2f;

// Construct a vector 2D composed of two float
Vector2f vector2f(float x, float y);

// Sum two vector 2D composed of two float
Vector2f vector2f_add(Vector2f u, Vector2f v);

// Divide a vector 2D composed of two float by a int
Vector2f vector2f_dividei(Vector2f u, int x);

#endif