#ifndef VECTOR_H
#define VECTOR_H

// template <typename T>
struct Vector
{
  int x, y;

  Vector(int x, int y) : x(x), y(y)
  {
  }

  Vector &operator=(const Vector &other)
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

  Vector &operator+=(const Vector &vector)
  {
    add(vector.x, vector.y);
    return *this;
  }

  Vector operator+(const Vector &vector)
  {
    return Vector(x + vector.x, y + vector.y);
  }

  Vector &operator*=(const Vector &vector)
  {
    multiply(vector.x, vector.y);
    return *this;
  }

  Vector operator*(const Vector &vector)
  {
    return Vector(x * vector.x, y * vector.y);
  }

  Vector &operator*=(const int &v)
  {
    multiply(v, v);
    return *this;
  }

  Vector operator*(const int &v)
  {
    return Vector(x * v, y * v);
  }
};

#endif