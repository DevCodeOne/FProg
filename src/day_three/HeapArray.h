#pragma once

#include <cstddef>

#include <memory>

#include "Person.h"

namespace FProg {
  class PersonHeapArray final {
  public:
    PersonHeapArray();
    PersonHeapArray(const PersonHeapArray &array) = delete;
    PersonHeapArray(const PersonHeapArray &&array) = delete;
    void reserve(size_t new_capacity);
    void push_back(const Person &person);

    inline Person &operator[](size_t index) {
      return m_data[index];
    }

    inline size_t size() const {
      return m_size;
    }

    inline size_t capacity() const {
      return m_capacity;
    }

  private:
    std::unique_ptr<Person[]> m_data = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;
  };
}
