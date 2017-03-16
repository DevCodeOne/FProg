#pragma once

#include <cstddef>
#include <cassert>

#include <memory>
#include <algorithm>
#include <iterator>
#include <utility>
#include <iostream>
#include <initializer_list>

#include "Person.h"

namespace FProg {

  template<typename T>
  class HeapArray final {
  public:

    using size_type = size_t;
    using value_type = T;

    class HeapArrayIterator final
      : public std::iterator<std::forward_iterator_tag, T> {

    public:

      explicit HeapArrayIterator(T *ptr);
      HeapArrayIterator &operator++();
      T &operator*();
      bool operator==(const HeapArrayIterator &rhs);
      bool operator!=(const HeapArrayIterator &rhs);
    private:
      T *m_ptr = nullptr;

    };

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
    HeapArrayIterator begin() const;
    HeapArrayIterator end() const;
    size_t size() const;
    size_t capacity() const;
    T &operator[](size_t index) const;

  private:
    size_t m_size = 0;
    size_t m_capacity = 0;
    std::unique_ptr<T[]> m_data;
  };

  template<typename T>
  HeapArray<T>::HeapArray(const std::initializer_list<T> &elements) {
    reserve(elements.size());

    std::copy(std::begin(elements), std::end(elements), std::back_inserter(*this));
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

    std::copy(std::begin(array), std::end(array), std::begin(*this));
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

    std::copy(std::begin(*this), std::end(*this), new_data.get());

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
  typename HeapArray<T>::HeapArrayIterator HeapArray<T>::begin() const {
    return typename HeapArray<T>::HeapArrayIterator(m_data.get());
  }

  template<typename T>
  typename HeapArray<T>::HeapArrayIterator HeapArray<T>::end() const {
    return typename HeapArray<T>::HeapArrayIterator(m_data.get() + m_size);
  }

  template<typename T>
  void HeapArray<T>::swap(HeapArray<T> &other) noexcept {
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_data, other.m_data);
  }

  template<typename T>
  HeapArray<T>::HeapArrayIterator::HeapArrayIterator(T *ptr) : m_ptr(ptr) {

  }

  template<typename T>
  typename HeapArray<T>::HeapArrayIterator &HeapArray<T>::HeapArrayIterator::operator++() {
    ++m_ptr;

    return *this;
  }

  template<typename T>
  T &HeapArray<T>::HeapArrayIterator::operator*() {
    return *m_ptr;
  }

  template<typename T>
  bool HeapArray<T>::HeapArrayIterator::operator==(const typename HeapArray<T>::HeapArrayIterator &rhs) {
    return this->m_ptr == rhs.m_ptr;
  }

  template<typename T>
  bool HeapArray<T>::HeapArrayIterator::operator!=(const typename HeapArray<T>::HeapArrayIterator &rhs) {
    return this->m_ptr != rhs.m_ptr;
  }
}

using PersonHeapArray = FProg::HeapArray<FProg::Person>;

// Geht nicht da das T eines abgeleiteten Typs nicht direkt abgeleitet werden kann,
// deswegen muss es zu einer Elementfunktion umgeschrieben werden
//template<typename T>
//bool operator==(const typename FProg::HeapArray<T>::HeapArrayIterator &it1,
//                const typename FProg::HeapArray<T>::HeapArrayIterator &it2) {
//  return it1.m_ptr == it2.m_ptr;
//}

//template<typename T>
//bool operator!=(const FProg::HeapArrayIterator<T> &it1,
//                const FProg::HeapArrayIterator<T> &it2) {
//  return !(it1 == it2);
//}

template<typename T>
inline void swap(FProg::HeapArray<T> &array1,
                 FProg::HeapArray<T> &array2) noexcept {
  array1.swap(array2);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const FProg::HeapArray<T> &array) {
  return os << "[ " << array.size() << " / " << array.capacity() << " ]";
}
