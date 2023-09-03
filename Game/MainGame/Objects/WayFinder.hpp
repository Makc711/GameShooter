#pragma once

// Include
#include "Constants.hpp"
#include "Point.hpp"

// Forward declaration
class GameObject;

// Class WayFinder
class WayFinder
{
public:
  explicit WayFinder(const Array<Rectangle, kMaxNumOfObstaclesOnLevel>& levelBodies, size_t blocksCount);
  void findPath(
    Array<Point<float>, kSizeOfStack>& path,
    const Point<int>& start, 
    const Point<int>& end);

private:
  void fillGrid(const Array<Rectangle, kMaxNumOfObstaclesOnLevel>& levelBodies, const size_t blocksCount);
  [[nodiscard]] bool isValid(const Point<int>& point) const;
//  static bool isRectangleOverlap(const Rectangle& rect1, const Rectangle& rect2);

private:
  bool m_grid[kGridWidth][kGridHeight]{};
  Rectangle m_endRect;
//  int m_rows{};
//  int m_cols{};
//  int **m_fillMap{};
//  GamePoint m_stack[kSizeOfStack];
//  int m_coordinatesOfBlocks{};
};