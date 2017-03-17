#pragma once

#include <iostream>

namespace FProg {

  class Day final {
  public:
    inline explicit Day(unsigned int value)
      : m_value(value) {
    }

    inline int value() const {
      return m_value;
    }
  private:
    const int m_value;
  };

  class Month final {
  public:
    inline explicit Month(unsigned int value)
      : m_value(value) {
    }

    inline int value() const {
      return m_value;
    }
  private:
    const int m_value;
  };

  class Year final {
  public:
    inline explicit Year(unsigned int value)
      : m_value(value) {
    }

    inline int value() const {
      return m_value;
    }
  private:
    const int m_value;
  };

  class Date final {
  public:
    Date(Day day, Month month, Year year);
    int day() const;
    int month() const;
    int year() const;
    void day(int day);
    void month(int month);
    void year(int year);
  private:
    int m_day, m_month, m_year;
  };

  inline std::ostream &operator<<(std::ostream &os, const FProg::Date &date) {
    return os << date.day() << "/" << date.month() << "/" << date.year();
  }

  inline std::string to_string(const FProg::Date &date) {
    return std::to_string(date.day()) + "/" + std::to_string(date.month()) +
      "/" + std::to_string(date.year());

  }
}

