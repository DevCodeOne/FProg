#pragma once

class Date {
public:
  Date(int tag, int monat, int jahr);
  int tag() const;
  int monat() const;
  int jahr() const;
  long long int duration() const;
  void tag(int tag);
  void monat(int monat);
  void jahr(int jahr);
  void duration(long long int m_duration);
private:
  long long int m_duration;
  int m_tag, m_monat, m_jahr;
};
