#pragma once

// Include
#include "GameObjectType.hpp"
#include "Point.hpp"
#include "Size.hpp"

class Body
{
public:
  Body(Point<float> _topLeft, Size _size, GameObjectType _type)
    : m_topLeft(_topLeft)
    , m_size(_size)
    , m_type(_type) {}

  Body()
    : m_topLeft({ 0.0f, 0.0f })
    , m_size({ 1.0f, 1.0f })
    , m_type(GameObjectType_None) {}

  void setX(const float x) { m_topLeft.x = x; }
  void setY(const float y) { m_topLeft.y = y; }
  void setTopLeft(const Point<float>& p) { m_topLeft = p; }
  [[nodiscard]] Point<float> getTopLeft() const
  {
    return m_topLeft;
  }
  [[nodiscard]] Point<float> getBottomRight() const
  {
    return m_topLeft + m_size - 1;
  }
  [[nodiscard]] Point<float> getCenter() const
  {
    return m_topLeft + (m_size / 2.0f);
  }

  void setSize(const Size& size) { m_size = size; }
  [[nodiscard]] Size getSize() const { return m_size; }

  void addBorder(const float border)
  {
    m_topLeft = m_topLeft - border;
    m_size = m_size + (border * 2.0f);
  }

  void setType(const GameObjectType type)
  {
    m_type = type;
  }
  [[nodiscard]] GameObjectType getType() const
  {
    return m_type;
  }

  void reset()
  {
    m_topLeft = Point<float>();
    m_size = Size();
    m_type = GameObjectType_None;
  }

private:
  Point<float> m_topLeft;
  Size m_size;
  GameObjectType m_type;
};