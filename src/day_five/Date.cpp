#include "Date.h"

namespace FProg {

  Date::Date(Day day, Month month, Year year) :
    m_day(day.value()), m_month(month.value()),
    m_year(year.value()) {
  }

  int Date::day() const {
    return m_day;
  }

  int Date::month() const {
    return m_month;
  }

  int Date::year() const {
    return m_year;
  }

  void Date::day(int day) {
    m_day = day;
  }

  void Date::month(int month) {
    m_month = month;
  }

  void Date::year(int year) {
    m_year = year;
  }

 }
