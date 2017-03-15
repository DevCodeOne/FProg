#pragma once

#include <cstddef>
#include <cassert>

#include <memory>
#include <utility>
#include <iostream>
#include <initializer_list>

#include "Person.h"

namespace FProg {

  template<typename T>
  class HeapArray final {
  public:

    using size_type = size_t;

    HeapArray();
    HeapArray(const std::initializer_list<T> &elements);
    explicit HeapArray(size_t capacity);
    HeapArray(const HeapArray &array);
    HeapArray(HeapArray &&array);
    HeapArray &operator=(const HeapArray &array);
    HeapArray &operator=(HeapArray &&array);
    T &operator[](size_t index);
    void reserve(size_t new_capacity);
    void swap(HeapArray &other) noexcept;
    void push_back(const T &element);
    inline size_t size() const;
    inline size_t capacity() const;
    T &operator[](size_t index) const;
  private:
    size_t m_size = 0;
    size_t m_capacity = 0;
    std::unique_ptr<T[]> m_data;

  };

  template<typename T>
  HeapArray<T>::HeapArray(const std::initializer_list<T> &elements) {
    reserve(elements.size());

    for (auto element : elements)
      push_back(element);
  }

  template<typename T>
  HeapArray<T>::HeapArray() {
    reserve(4);
  }

  template<typename T>
  HeapArray<T>::HeapArray(size_t capacity) {
    reserve(capacity);
  }

  template<typename T>
  HeapArray<T>::HeapArray(const HeapArray &array)
    : m_size(array.size()),
      m_capacity(array.capacity()),
      m_data(std::make_unique<T[]>(m_capacity)) {

    for (size_t i = 0; i < m_size; i++)
      m_data[i] = array.m_data[i];
  }

  // Copy-Swap Idiom
  template<typename T>
  HeapArray<T>::HeapArray(HeapArray &&array) {
    HeapArray tmp(array);
    swap(array);
  }

  template<typename T>
  void HeapArray<T>::reserve(size_t new_capacity) {
    if (new_capacity < m_size)
      return;

    auto new_data = std::make_unique<T[]>(new_capacity);

    for (size_t i = 0; i < m_size; i++)
      new_data[i] = m_data[i];

    m_data = std::move(new_data);
    m_capacity = new_capacity;
  }

  template<typename T>
  void HeapArray<T>::push_back(const T &element) {
    if (m_size == m_capacity)
      reserve(m_capacity == 0 ? 1 : m_capacity * 2);

    m_data[m_size++] = element;
  }

  template<typename T>
  HeapArray<T> &HeapArray<T>::operator=(const HeapArray &array) {
    HeapArray tmp(array);
    swap(tmp);

    return *this;
  }

  template<typename T>
  HeapArray<T> &HeapArray<T>::operator=(HeapArray<T> &&array) {
    swap(array);

    return *this;
  }

  template<typename T>
  T &HeapArray<T>::operator[](size_t index) {
    assert(index < m_size);

    return m_data[index];
  }

  template<typename T>
  T &HeapArray<T>::operator[](size_t index) const {
    assert(index < m_size);

    return m_data[index];
  }

  template<typename T>
  size_t HeapArray<T>::size() const {
    return m_size;
  }

  template<typename T>
  size_t HeapArray<T>::capacity() const {
    return m_capacity;
  }

  template<typename T>
  void HeapArray<T>::swap(HeapArray<T> &other) noexcept {
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_data, other.m_data);
  }
}

using PersonHeapArray = FProg::HeapArray<FProg::Person>;

template<typename T>
inline void swap(FProg::HeapArray<T> &array1,
                 FProg::HeapArray<T> &array2) noexcept {
  array1.swap(array2);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const FProg::HeapArray<T> &array) {
  return os << "[ " << array.size() << " / " << array.capacity() << " ]";
}
