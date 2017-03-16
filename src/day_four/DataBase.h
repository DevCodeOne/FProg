#pragma once

#include <string>
#include <fstream>

#include "HeapArray.h"
#include "Serializer.h"

namespace FProg {

  template<typename Container,
           typename SerializerT = StringSerializer>
  class Database final {
  public:

    using value_type = typename Container::value_type;

    Database(const std::string &filename);
    ~Database();
    Database<Container, SerializerT> &operator+=(const value_type &value);
    Database<Container, SerializerT> &operator<<(const value_type &value);
  private:
    Container m_container;
    SerializerT m_serializer;
    std::string m_filename;
  };

  template<typename Container, typename SerializerT>
  Database<Container, SerializerT>::Database(const std::string &filename)
    : m_container(), m_serializer(),
      m_filename(filename) {
    std::ifstream file(m_filename);
    std::string line;
    while (getline(file, line)) {
      StringDeserializer deserializer{line};

      auto ret = value_type::deserialize(deserializer);
      if (ret)
        m_container.push_back(ret.value());
    }
  }

  template<typename Container, typename SerializerT>
  Database<Container, SerializerT>::~Database() {
    std::ofstream output_file(m_filename, std::fstream::trunc);

    for (const auto &element : m_container) {
      element.serialize(m_serializer);
    }

   output_file << m_serializer.value();
  }

  template<typename Container, typename SerializerT>
  Database<Container, SerializerT> &
  Database<Container, SerializerT>::operator+=(const value_type &value) {
    m_container.push_back(value);

    return *this;
  }

  template<typename Container, typename SerializerT>
  Database<Container, SerializerT> &
  Database<Container, SerializerT>::operator<<(const value_type &value) {
    m_container.push_back(value);

    return *this;
  }
}
