#pragma once

#include <string>

namespace FProg {

  class Tracer {
  public:
    Tracer(const std::string &function_name);
    ~Tracer();
  private:
    std::string m_function_name;
    static unsigned int m_num_tracer_objects;
  };

}
