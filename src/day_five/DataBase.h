#pragma once

#include <string>
#include <fstream>
#include <cassert>
#include <functional>
#include <experimental/optional>

#include "HeapArray.h"
#include "Serializer.h"
#include "Deserializer.h"

namespace FProg {

  // Typemapping um Deserializer und Serializer zu verbinden,
  // also um den passenden Deserializer zu einem Serializer zu finden.
  // Es werden denn Spezialisierungen erstellt für die jeweiligen Serializer
  template<typename Serializer>
  struct SerializerMapping {
  };

  template<>
  struct SerializerMapping<StringSerializer> {
    using deserializer_type = StringDeserializer;
  };

  template<typename Container,
           typename SerializerT = StringSerializer,
           typename DeserializerT =
           typename SerializerMapping<SerializerT>::deserializer_type>
  class Database final {
  public:

    using value_type = typename Container::value_type;

    Database(const std::string &filename);
    ~Database();
    Database<Container,
             SerializerT,
             DeserializerT> &operator+=(const value_type &value);
    Database<Container,
             SerializerT,
             DeserializerT> &operator<<(const value_type &value);
    const value_type &operator[](size_t index) const;
    Container search(const std::function<bool(value_type)> &predicate) const;
    size_t size() const;
  private:
    Container m_container;
    SerializerT m_serializer;
    std::string m_filename;
  };

  template<typename Container, typename SerializerT, typename DeserializerT>
  Database<Container,
           SerializerT,
           DeserializerT>::Database(const std::string &filename)
    : m_container(), m_serializer(),
      m_filename(filename) {
    std::ifstream file(m_filename);
    std::string line;

    if (!file)
      return;

    while (getline(file, line)) {
      DeserializerT deserializer{line};

      auto ret = value_type::deserialize(deserializer);
      if (ret)
        m_container.push_back(*ret);
    }
  }

  template<typename Container, typename SerializerT, typename DeserializerT>
  Database<Container,
           SerializerT,
           DeserializerT>::~Database() {
    std::ofstream output_file(m_filename, std::fstream::trunc);

    for (const auto &element : m_container) {
      element.serialize(m_serializer);
    }

   output_file << m_serializer.value();
  }

  template<typename Container, typename SerializerT, typename DeserializerT>
  Database<Container, SerializerT, DeserializerT> &
  Database<Container,
           SerializerT,
           DeserializerT>::operator+=(const value_type &value) {
    m_container.push_back(value);

    return *this;
  }

  template<typename Container, typename SerializerT, typename DeserializerT>
  size_t Database<Container,
           SerializerT,
           DeserializerT>::size() const {
    return m_container.size();
  }

  template<typename Container, typename SerializerT, typename DeserializerT>
  Database<Container, SerializerT, DeserializerT> &
  Database<Container,
           SerializerT,
           DeserializerT>::operator<<(const value_type &value) {
    m_container.push_back(value);

    return *this;
  }

  template<typename Container, typename SerializerT, typename DeserializerT>
  const typename Database<Container, SerializerT, DeserializerT>::value_type &
  Database<Container, SerializerT, DeserializerT>::operator[](size_t index) const {
    assert(index < m_container.size());

    return m_container[index];
  }

  template<typename C, typename S, typename D>
  C Database<C, S, D>::search(const std::function<bool(value_type)> &predicate) const {
    C results;
    std::copy_if(std::begin(m_container), std::end(m_container),
                 std::back_inserter(results), predicate);

    return results;
  }

}

template<typename Container,
         typename SerializerT = FProg::StringSerializer,
         typename DeserializerT =
         typename FProg::SerializerMapping<SerializerT>::deserializer_type>
inline std::ostream &operator<<(std::ostream &os,
                               FProg::Database<Container,
                               SerializerT,
                               DeserializerT> &database) {
  for (size_t i = 0; i < database.size(); i++) {
    os << database[i] << std::endl;
  }

  return os;
}
