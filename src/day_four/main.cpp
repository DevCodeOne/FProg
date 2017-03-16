#include <iostream>

#include "Person.h"
#include "Tracer.h"
#include "HeapArray.h"
#include "utils.h"

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
  HeapArray<Person> array;
  array.push_back(p);
  array.push_back(p2);
  array.push_back(p3);
  array.push_back(p4);
  array.push_back(p5);

  for (size_t i = 0; i < array.size(); i++) {
    std::cout << array[i] << std::endl;
  }

  std::cout << array << std::endl;

  StringSerializer serializer;
  p.serialize(serializer);
  p2.serialize(serializer);
  p3.serialize(serializer);

  std::cout << serializer.value() << std::endl;

  test123();

  auto intervall = minmax(5, 4);
  auto intervall2 = minmax<std::string>("Test", "123");
  auto intervall3 = minmax(5.5, 5.6);

  std::cout << intervall << std::endl;
  std::cout << intervall2 << std::endl;
  std::cout << intervall3 << std::endl;

  HeapArray<int> int_array{0, 1, 2, 3};
  for (decltype(int_array)::size_type i = 0;
       i < int_array.size(); i++)
    std::cout << int_array[i] << " ";

  std::cout << std::endl;

  for (const auto &ele : int_array) {
    std::cout << ele << std::endl;
  }

  std::cout << int_array << std::endl;

  // Benutze std::begin ist generischer, denn ein Typ
  // könnte die Elementfunktion nicht implementieren
  // std::fill(std::begin(int_array), std::begin(int_array), 42);

  // ppc2100 lesen
  return 0;
}
