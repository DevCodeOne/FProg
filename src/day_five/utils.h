#pragma once

#include <iostream>
#include <string>

namespace FProg {

  template<typename T>
  class Intervall;

  template<typename T>
  Intervall<T> minmax(const T &val1, const T &val2);

  template<typename T>
  class Intervall final {
  private:
    Intervall(const T &min, const T &max) : m_min(min), m_max(max) {
    }

  public:
    const T m_min;
    const T m_max;

    //  T mean() const;

    friend Intervall<T> minmax<>(const T &val1, const T &val2);
  };

  // Rückgabe-Typ kann auch als auto angegeben werden, auch ohne
  // trailing return type. Das ist hilfreich, wenn man einen Rückgabe-Typ
  // haben möchte der von dem Template abhängig ist, muss der Compiler erst
  // die Parameterliste komplett eingesehen haben
  template<typename T>
  Intervall<T> minmax(const T &val1, const T &val2) {
    return val1 < val2 ? Intervall<T>{val1, val2} : Intervall<T>{val2, val1};
  }

  template<>
  Intervall<std::string> minmax(const std::string &val1, const std::string &val2) {
    if (val1.size() < val2.size())
      return Intervall<std::string>{val1, val2};
    return Intervall<std::string>{val2, val1};
  }

}

template<typename T>
std::ostream &operator<<(std::ostream &os, const FProg::Intervall<T> &intervall) {
  return os << "[ " << intervall.m_min << ", " << intervall.m_max << " ]";
}

/*
template<typename T>
T Intervall<T>::mean() const {
  return (m_min + m_max) / 2.0;
}
*/
