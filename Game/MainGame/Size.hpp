#pragma once

struct Size
{
  float width;
  float height;

  Size operator+(const float& scalar) const
  {
    return { width + scalar, height + scalar };
  }

  Size operator/(const float& scalar) const
  {
    return { width / scalar, height / scalar };
  }
};