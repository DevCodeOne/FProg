#pragma once

#include <string>
#include <iostream>

#include <ctime>
#include <cstddef>

#include "Date.h"
#include "Serializer.h"

namespace FProg {
  class Firstname final {
  public:
    // inline um One-Definition Rule aufzuweichen
    // Bei ein bis zwei Zeilern in Header
    inline explicit Firstname(const std::string value) : m_value(value) {

    }

    inline const std::string &value() const {
      return m_value;
    }

  private:
    const std::string m_value;
  };

  class Lastname final {
  public:
    explicit Lastname(const std::string value) : m_value(value) {

    }

    const std::string &value() const {
      return m_value;
    }

  private:
    const std::string m_value;
  };

  // Zuerst mal final, weil Überlegungen dazu angestellt werden müssen
  class Person final {
  public:
    // Firstname wird gemoved in den Parameter firstname, wenn ein temporäres Objekt
    // benutzt wird also Move-Konstruktor von Firstname wird benutzt.
    // Dann wird der Parameter firstname in m_firstname gemoved
    Person(const Firstname firstname, const Lastname lastname,
           const Date &birthday);
    Person &firstname(const std::string &firstname);
    Person &lastname(const std::string &lastname);
    const std::string &firstname() const;
    const std::string &lastname() const;
    const Date &birthday() const;
    Serializer &serialize(Serializer &serializer) const;
  private:
    std::string m_firstname;
    std::string m_lastname;
    Date m_birthday;
  };

}

inline FProg::Firstname operator"" _first(const char *str, size_t) {
  return FProg::Firstname(str);
}

inline std::ostream &operator<<(std::ostream &os,
                                const FProg::Firstname &firstname) {
  return os << firstname.value();
}

inline FProg::Lastname operator"" _last(const char *str, size_t) {
  return FProg::Lastname(str);
}

inline std::ostream &operator<<(std::ostream &os,
                                const FProg::Lastname &lastname) {
  return os << lastname.value();
}

inline std::ostream &operator<<(std::ostream &os, const FProg::Person &person) {
  return os << person.firstname() << " " << person.lastname();
}
