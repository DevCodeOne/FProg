#include "Person.h"

#include "simpletest.h"

SIMPLETEST("Person Namecheck") {
  FProg::Person p{FProg::Firstname("Herbert"), FProg::Lastname("Waffman"),
      FProg::Date(FProg::Day(0), FProg::Month(0), FProg::Year(0))};

  if (p.firstname() == "Herbert" && p.lastname() == "Waffman")
    return true;

  return false;
};

SIMPLETEST("Person Geburtstagcheck") {
  FProg::Person p{FProg::Firstname("Herbert"), FProg::Lastname("Waffman"),
      FProg::Date(FProg::Day(14), FProg::Month(3), FProg::Year(2017))};

  if (p.birthday().year() == 2017
      && p.birthday().month() == 3
      && p.birthday().day() == 14)
    return true;

  return false;
};

namespace FProg {

  Person::Person(const Firstname firstname, const Lastname lastname,
                 const Date &birthday)
    : m_firstname(std::move(firstname.value())),
      m_lastname(std::move(lastname.value())),
      m_birthday(birthday), m_valid(true) {

  }

  Person &Person::firstname(const std::string &firstname) {
    m_firstname = firstname;

    return *this;
  }

  Person &Person::lastname(const std::string &lastname) {
    m_lastname = lastname;

    return *this;
  }

  Serializer &Person::serialize(Serializer &serializer) const {
    serializer.start("Person");
    serializer.write(AttributeValue().name("Firstname").value(m_firstname));
    serializer.write(AttributeValue().name("Lastname").value(m_lastname));
    serializer.write(AttributeValue().name("Birthday").
                     value(to_string(m_birthday)));
    serializer.end();
    return serializer;
  }

  const std::string &Person::firstname() const {
    return m_firstname;
  }

  const std::string &Person::lastname() const {
    return m_lastname;
  }

  const Date &Person::birthday() const {
    return m_birthday;
  }

}
