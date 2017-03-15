
#include "simpletest.h"
#include "HeapArray.h"

namespace FProg {

  SIMPLETEST("Copy-Constructor Test") {
    HeapArray<int> array1{1, 2, 4, 5, 6};
    HeapArray<int> array2{array1};

    for (decltype(array1)::size_type i = 0; i < array1.size(); i++)
      if (array1[i] != array2[i])
        return false;
    return true;
  };

  SIMPLETEST("Push-Back Test") {
    HeapArray<int> array1{1, 2, 4, 5, 6};
    // Ist der Konstruktor mit der initializer_list aufpassen !
    // HeapArray<int> array2{0};
    HeapArray<int> array2(0);

    for (decltype(array1)::size_type i = 0; i < array1.size(); i++)
      array2.push_back(array1[i]);

    for (decltype(array1)::size_type i = 0; i < array1.size(); i++)
      if (array1[i] != array2[i])
        return false;
    return true;
  };

}
