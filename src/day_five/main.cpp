#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <experimental/optional>

#include "Person.h"
#include "Tracer.h"
#include "HeapArray.h"
#include "utils.h"
#include "DataBase.h"

using namespace FProg;

int main(int argc, char *argv[]) {
  std::vector<std::string> arguments;
  std::copy(argv + 1, argv + argc, std::back_inserter(arguments));

  Database<HeapArray<Person>> database{"output.db"};

  if (arguments.size() >= 1) {
    if (arguments[0] == "list") {
      std::cout << database;
    } else if (arguments[0] == "add" && arguments.size() == 3) {
      Date d{Day{0}, Month{0}, Year{0}};
      database << Person(Firstname(arguments[1]),
                         Lastname(arguments[2]), d);
    } else if (arguments[0] == "search" && arguments.size() == 3) {
      const std::string &firstname = arguments[1];
      const std::string &lastname = arguments[2];

      auto predicate = [&firstname, &lastname](const Person &p){
        return p.firstname() == firstname && p.lastname() == lastname;
      };

      auto results = database.search(predicate);
      for (const auto &element : results)
        std::cout << element << std::endl;
    }
  }

  return 0;
}
