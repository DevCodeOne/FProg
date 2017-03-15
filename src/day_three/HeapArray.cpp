#include "HeapArray.h"

namespace FProg {

  PersonHeapArray::PersonHeapArray() {
    reserve(4);
  }

  void PersonHeapArray::reserve(size_t new_capacity) {
    if (new_capacity < m_size)
      return;

    auto new_data = std::make_unique<Person[]>(new_capacity);

    for (size_t i = 0; i < m_size; i++)
      new_data[i] = m_data[i];

    m_data = std::move(new_data);
    m_capacity = new_capacity;
  }

  void PersonHeapArray::push_back(const Person &person) {
    if (m_size+1 == m_capacity)
      reserve(m_capacity * 2);

    m_data[m_size++] = person;
  }
}
