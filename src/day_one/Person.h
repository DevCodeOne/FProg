#pragma once

#include <string>

#include <ctime>

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
    Person(const Firstname &firstname, const Lastname &lastname,
           const std::time_t &birthday);
    Person &firstname(const std::string &firstname);
    Person &lastname(const std::string &lastname);
    const std::string &firstname() const;
    const std::string &lastname() const;
    const std::time_t &birthday() const;
  private:
    std::string m_firstname;
    std::string m_lastname;
    std::time_t m_birthday;
  };

}