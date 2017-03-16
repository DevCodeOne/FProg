#include <iostream>

#include "Person.h"
#include "Tracer.h"
#include "HeapArray.h"
#include "utils.h"
#include "DataBase.h"

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

  auto firstname = "Peter"_first;
  auto lastname = "Mueller"_last;

  Person p(FProg::Firstname("Heribert"), FProg::Lastname("Waffman"), d);
  Person p2{firstname, lastname, d};
  Person p3{"Mueller"_first, "Mueller"_last, d};
  Person p4{"Typ"_first, "Last"_last, d};
  Person p5{"Typ2"_first, "Last"_last, d};

  Database<HeapArray<Person>> database{"output.db"};

  database << p << p2 << p3 << p4 << p5;

  return 0;
}
