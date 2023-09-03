#pragma once

// Include
#include <cmath>
#include "Size.hpp"

template<typename T> float sign(const T val)
{
  return (val >= 0) ? 1.0f : -1.0f;
}

template<typename T> struct Point
{
  T x, y;

  Point(T _x, T _y)
    : x(_x)
    , y(_y) {}

  Point()
    : x(0)
    , y(0) {}

  Point<T> operator+(const Point<T> other) const
  {
    return { x + other.x, y + other.y };
  }

  Point<T> operator+(const T& scalar) const
  {
    return { x + scalar, y + scalar };
  }

  Point<float> operator+(const Size other) const
  {
    return { x + other.width, y + other.height };
  }

  Point<T> operator-(const Point<T>& other) const
  {
    return { x - other.x, y - other.y };
  }

  Point<T> operator-(const T& scalar) const
  {
    return { x - scalar, y - scalar };
  }

  Point<T> operator*(const T& scalar) const
  {
    return { x * scalar, y * scalar };
  }

  Point<T> operator/(const T& scalar) const
  {
    return { x / scalar, y / scalar };
  }

  bool operator<=(const Point<T>& other) const
  {
    return (x <= other.x) && (y <= other.y);
  }

  bool operator>=(const Point<T>& other) const
  {
    return (x >= other.x) && (y >= other.y);
  }

  bool operator==(const Point<T>& other) const
  {
    return (x == other.x) && (y == other.y);
  }

  bool operator!=(const Point<T>& other) const
  {
    return (x != other.x) || (y != other.y);
  }

  [[nodiscard]] float magnitudeSquared() const
  {
    return x * x + y * y;
  }
  [[nodiscard]] float magnitude() const
  {
    return std::sqrt(magnitudeSquared());
  }

  [[nodiscard]] T dot(const Point<T>& other) const
  {
    return x * other.x + y * other.y;
  }

  [[nodiscard]] T length2(const Point<T>& other) const
  {
    const T dX = x - other.x;
    const T dY = y - other.y;
    return dX*dX + dY*dY;
  }

  Point<float> normalize()
  {
    const float mag = magnitude();
    if (mag != 0.0f)
    {
      return { x / mag, y / mag };
    }
    return { 0.0f, 0.0f };
  }

  void swap()
  {
    T temp = x;
    x = y;
    y = temp;
  }

  template<typename U>
  [[nodiscard]] Point<U> cast() const
  {
    return { static_cast<U>(x), static_cast<U>(y) };
  }

  static void calculateSinCos(float& sinA, float& cosA, const Point<T>& p0, const Point<T>& p1)
  {
    const T deltaX = p1.x - p0.x;
    const T deltaY = p1.y - p0.y;
    if (deltaX == 0)
    {
      sinA = 1.0f * sign(deltaY);
      cosA = 0.0f;
    }
    else
    {
      if (deltaY == 0)
      {
        sinA = 0.0f;
        cosA = 1.0f * sign(deltaX);
      }
      else
      {
        const float tgA = std::abs(static_cast<float>(deltaY) / static_cast<float>(deltaX));
        sinA = tgA / std::sqrt(1 + tgA * tgA) * sign(deltaY);
        cosA = std::sqrt(1 - sinA * sinA) * sign(deltaX);
      }
    }
  }
};