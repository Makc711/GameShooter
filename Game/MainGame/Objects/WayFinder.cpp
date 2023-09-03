#include "WayFinder.hpp"
#include <functional>
#include "Enemy.hpp"

// Class WayFinder
WayFinder::WayFinder(const Array<Rectangle, kMaxNumOfObstaclesOnLevel>& levelBodies, const size_t blocksCount)
{
  m_endRect = {{0, 0}, { kHumanSize * 2, kHumanSize * 2 }, GameObjectType_Enemy};
  fillGrid(levelBodies, blocksCount);
}

void WayFinder::fillGrid(const Array<Rectangle, kMaxNumOfObstaclesOnLevel>& levelBodies, const size_t blocksCount)
{
  for (size_t blockIndex = 0; blockIndex < blocksCount; blockIndex++)
  {
    const auto blockTopLeft = levelBodies[blockIndex].getTopLeft() / kStep;
    const auto blockTopLeftX = static_cast<int>(std::round(blockTopLeft.x));
    const auto blockTopLeftY = static_cast<int>(std::round(blockTopLeft.y));
    const auto blockBottomRight = levelBodies[blockIndex].getBottomRight() / kStep;
    const auto blockBottomRightX = static_cast<int>(std::round(blockBottomRight.x));
    const auto blockBottomRightY = static_cast<int>(std::round(blockBottomRight.y));
    for (int x = blockTopLeftX; x <= blockBottomRightX; x++)
    {
      for (int y = blockTopLeftY; y <= blockBottomRightY; y++)
      {
        m_grid[x][y] = true;
      }
    }
  }
}

struct Node
{
  Point<int> point;
  int gCost;
  int hCost;
  Node* parent;

  Node(Point<int> _point, int _gCost, int _hCost, Node* _parent)
    : point(_point)
    , gCost(_gCost)
    , hCost(_hCost)
    , parent(_parent) {}

  Node() 
    : point(Point<int>())
    , gCost(0)
    , hCost(0)
    , parent(nullptr) {}

  [[nodiscard]] int fCost() const
  {
    return gCost + hCost;
  }

  bool operator>(const Node& other) const
  {
    return fCost() > other.fCost();
  }
};

bool WayFinder::isValid(const Point<int>& point) const
{
  return (point.x >= 0) && (point.x < kGridWidth) && (point.y >= 0) && (point.y < kGridHeight) && (m_grid[point.x][point.y] == false);
}

//bool WayFinder::isRectangleOverlap(const Rectangle& rect1, const Rectangle& rect2)
//{
//  const auto topLeftRect1 = rect1.getTopLeft();
//  const auto bottomRightRect1 = rect1.getBottomRight();
//  const auto topLeftRect2 = rect2.getTopLeft();
//  const auto bottomRightRect2 = rect2.getBottomRight();
//  if (topLeftRect1.x > bottomRightRect2.x ||
//      bottomRightRect1.x < topLeftRect2.x ||
//      topLeftRect1.y > bottomRightRect2.y ||
//      bottomRightRect1.y < topLeftRect2.y) 
//  {
//    return false; // No overlap
//  }
//  return true;
//}

void WayFinder::findPath(
  Array<Point<float>, kSizeOfStack>& path,
  const Point<int>& start, 
  const Point<int>& end)
{
  StaticPriorityQueue<Node, kSizeOfStack, std::greater<>> openSet{};
  bool visited[kGridWidth][kGridHeight]{};

  openSet.emplace(start, 0, std::abs(end.x - start.x) + std::abs(end.y - start.y), nullptr);

  Point<int> directions[] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
  m_endRect.setTopLeft(end.cast<float>());

  while (!openSet.empty())
  {
    Node current = openSet.top();
    openSet.pop();

    if (Enemy::isPointIntersectRect(((current.point * kStep) + (kStep / 2)).cast<float>(), m_endRect))
    {
      while (current.parent != nullptr) 
      {
        path.pushBack(((current.point * kStep) + (kStep / 2)).cast<float>());
        current = *current.parent;
      }
      return;
    }

    visited[current.point.x][current.point.y] = true;

    for (const Point<int>& dir : directions)
    {
      Point<int> newPoint = current.point + dir;

      if (isValid(newPoint) && !visited[newPoint.x][newPoint.y])
      {
        const int newGCost = current.gCost + 1;
        const int newHCost = std::abs(end.x - newPoint.x) + std::abs(end.y - newPoint.y);
                    
        openSet.emplace(newPoint, newGCost, newHCost, &current);
      }
    }
  }
}
