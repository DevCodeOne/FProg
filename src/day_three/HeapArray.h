#pragma once

#include <cstddef>

#include <memory>
#include <cassert>
#include <utility>

#include "Person.h"

namespace FProg {
  class PersonHeapArray final {
  public:
    inline PersonHeapArray() {
      reserve(4);
    }

    explicit inline PersonHeapArray(size_t capacity) {
      reserve(capacity);
    }

    inline PersonHeapArray(const PersonHeapArray &array)
      : m_size(array.size()),
        m_capacity(array.capacity()),
        m_data(std::make_unique<Person[]>(m_capacity)) {

      for (size_t i = 0; i < m_size; i++)
        m_data[i] = array.m_data[i];
    }

    // Copy-Swap Idiom
    inline PersonHeapArray(PersonHeapArray &&array) {
      PersonHeapArray tmp(array);
      swap(array);
    }

    void reserve(size_t new_capacity) {
      if (new_capacity < m_size)
        return;

      auto new_data = std::make_unique<Person[]>(new_capacity);

      for (size_t i = 0; i < m_size; i++)
        new_data[i] = m_data[i];

      m_data = std::move(new_data);
      m_capacity = new_capacity;
    }

    void push_back(const Person &person);

    inline PersonHeapArray &operator=(const PersonHeapArray &array) {
      PersonHeapArray tmp(array);
      swap(tmp);

      return *this;
    }

    inline PersonHeapArray &operator=(PersonHeapArray &&array) {
      swap(array);

      return *this;
    }

    inline Person &operator[](size_t index) {
      assert(index < m_size);

      return m_data[index];
    }

    inline Person &operator[](size_t index) const {
      assert(index < m_size);

      return m_data[index];
    }

    inline size_t size() const {
      return m_size;
    }

    inline size_t capacity() const {
      return m_capacity;
    }

    void swap(PersonHeapArray &other) noexcept {
      std::swap(m_size, other.m_size);
      std::swap(m_capacity, other.m_capacity);
      std::swap(m_data, other.m_data);
    }

  private:
    size_t m_size = 0;
    size_t m_capacity = 0;
    std::unique_ptr<Person[]> m_data;

  };
}

inline void swap(FProg::PersonHeapArray &array1,
                 FProg::PersonHeapArray &array2) noexcept {
  array1.swap(array2);
}
