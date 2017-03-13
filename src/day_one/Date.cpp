#include "Date.h"

Date::Date(int tag, int monat, int jahr) :
  m_tag(tag), m_monat(monat), m_jahr(jahr) {

}

int Date::tag() const {
  return m_tag;
}

int Date::monat() const {
  return m_monat;
}

int Date::jahr() const {
  return m_jahr;
}

long long int Date::duration() const {
  return m_duration;
}

void Date::tag(int tag) {
  m_tag = tag;
}
void Date::monat(int monat) {
  m_monat = monat;
}
void Date::jahr(int jahr) {
  m_jahr = jahr;
}
void Date::duration(long long int duration) {
  m_duration = duration;
}
