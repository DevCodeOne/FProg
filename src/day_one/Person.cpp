#include "Person.h"

#include "simpletest.h"

SIMPLETEST("Person Namecheck") {
  FProg::Person p{FProg::Firstname("Herbert"), FProg::Lastname("Waffman"), 0L};

  if (p.firstname() == "Herbert" && p.lastname() == "Waffman")
    return true;

  return false;
};

SIMPLETEST("Person Geburtstagcheck") {
  FProg::Person p{FProg::Firstname("Herbert"), FProg::Lastname("Waffman"), 42L};

  if (p.birthday() == 42L)
    return true;

  return false;
};

namespace FProg {

  Person::Person(const Firstname &firstname, const Lastname &lastname,
                 const std::time_t &birthday)
    : m_firstname(firstname.value()), m_lastname(lastname.value()),
      m_birthday(birthday) {

  }

  Person &Person::firstname(const std::string &firstname) {
    m_firstname = firstname;

    return *this;
  }

  Person & Person::lastname(const std::string &lastname) {
    m_lastname = lastname;

    return *this;
  }

  const std::string &Person::firstname() const {
    return m_firstname;
  }

  const std::string &Person::lastname() const {
    return m_lastname;
  }

  const std::time_t &Person::birthday() const {
    return m_birthday;
  }

}
