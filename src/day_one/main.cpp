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

  Person p(FProg::Firstname("Heribert"), FProg::Lastname("Waffman"), 0L);

  auto firstname = "Peter"_first;
  auto lastname = "Mueller"_last;

  Person p2{firstname, lastname, 0L};
  Person p3{"Mueller"_first, "Mueller"_last, 0L};

  test123();

  return 0;
}
