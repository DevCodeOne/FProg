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
    long long int duration() const;
    void day(int day);
    void month(int month);
    void year(int year);
    void duration(long long int m_duration);
  private:
    int m_day, m_month, m_year;
    long long int m_duration;
  };

}

inline std::ostream &operator<<(std::ostream &os, const FProg::Date &date) {
  return os << date.day() << "/" << date.month() << "/" << date.year();
}
