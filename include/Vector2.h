#ifndef VECTOR_H
#define VECTOR_H

// template <typename T>
struct Vector2
{
  int x, y;

  Vector2(int x, int y) : x(x), y(y)
  {
  }

  Vector2 &operator=(const Vector2 &other)
  {
    x = other.x;
    y = other.y;
    return *this;
  }

  void multiply(int xFactor, int yFactor)
  {
    x *= xFactor;
    y *= yFactor;
  }

  void add(const int &xAdd, const int &yAdd)
  {
    x += xAdd;
    y += yAdd;
  }

  Vector2 &operator+=(const Vector2 &vector)
  {
    add(vector.x, vector.y);
    return *this;
  }

  Vector2 operator+(const Vector2 &vector)
  {
    return Vector2(x + vector.x, y + vector.y);
  }

  Vector2 &operator*=(const Vector2 &vector)
  {
    multiply(vector.x, vector.y);
    return *this;
  }

  Vector2 operator*(const Vector2 &vector)
  {
    return Vector2(x * vector.x, y * vector.y);
  }

  Vector2 &operator*=(const int &v)
  {
    multiply(v, v);
    return *this;
  }

  Vector2 operator*(const int &v)
  {
    return Vector2(x * v, y * v);
  }
};

#endif