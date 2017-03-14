#include <iostream>

#include "Person.h"
#include "Tracer.h"

using namespace FProg;

void bar() {
  Tracer t(__PRETTY_FUNCTION__);
}

void foo() {
  Tracer t(__PRETTY_FUNCTION__);
  bar();
  bar();
}

void test123() {
  Tracer t(__PRETTY_FUNCTION__);
  foo();
}

int main() {
  std::cout << __cplusplus << std::endl;

  Date d{Day(0), Month(0), Year(0)};
  Person p(FProg::Firstname("Heribert"), FProg::Lastname("Waffman"), d);

  auto firstname = "Peter"_first;
  auto lastname = "Mueller"_last;

  Person p2{firstname, lastname, d};
  Person p3{"Mueller"_first, "Mueller"_last, d};

  StringSerializer serializer;
  p.serialize(serializer);
  p2.serialize(serializer);
  p3.serialize(serializer);

  std::cout << serializer.value() << std::endl;

  test123();

  return 0;
}
