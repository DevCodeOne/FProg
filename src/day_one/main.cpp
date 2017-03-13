#include <iostream>

#include "Person.h"

int main() {
  std::cout << __cplusplus << std::endl;

  FProg::Person p(FProg::Firstname("Heribert"), FProg::Lastname("Waffman"), 0L);

  return 0;
}
