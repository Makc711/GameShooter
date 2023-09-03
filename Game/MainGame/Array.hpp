#pragma once

// Include
#include <cstddef>
#include <type_traits>

template <typename T, size_t N> class Array
{
public:
  Array()
    : m_data{}
    , m_count(0) {}

  void pushBack(const T& value)
  {
    if (m_count < N) 
    {
      m_data[m_count++] = value;
    }
  }

  void deleteObject(const size_t index)
  {
    if (index < m_count) 
    {
      if constexpr (std::is_pointer_v<T>)
      {
        delete m_data[index];
        m_data[index] = nullptr;
      }

      for (size_t i = index; i < m_count - 1; i++) 
      {
        m_data[i] = m_data[i + 1];
      }
      m_count--;
    }

    if constexpr (std::is_pointer_v<T>)
    {
      m_data[m_count] = nullptr;
    }
  }

  void deleteObject(const T& object)
  {
    for (size_t i = 0; i < m_count; i++)
    {
      if (m_data[i] == object)
      {
        deleteObject(i);
      }
    }
  }

  void deleteLastFrom(const size_t startIndex)
  {
    if constexpr (std::is_pointer_v<T>)
    {
      for (size_t i = startIndex; i < m_count; i++)
      {
        delete m_data[i];
        m_data[i] = nullptr;
      }
    }
    
    if (startIndex < m_count) 
    {
      m_count = startIndex;
    }
  }

  void deleteAllObjects()
  {
    if constexpr (std::is_pointer_v<T>)
    {
      for (size_t i = 0; i < m_count; i++)
      {
        if (m_data[i])
        {
          delete m_data[i];
          m_data[i] = nullptr;
        }
      }
    }

    m_count = 0;
  }

  [[nodiscard]] size_t count() const
  {
    return m_count;
  }

  [[nodiscard]] bool isFull() const
  {
    return m_count == N;
  }

  T& operator[](size_t index)
  {
    return m_data[index];
  }

  const T& operator[](size_t index) const
  {
    return m_data[index];
  }

  [[nodiscard]] const T* begin() const
  {
    return m_data;
  }

  [[nodiscard]] const T* end() const
  {
    return m_data + m_count;
  }

private:
  T m_data[N];
  size_t m_count;
};