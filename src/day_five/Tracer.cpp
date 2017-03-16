#include <iostream>

#include "Tracer.h"

namespace FProg {

  unsigned int Tracer::m_num_tracer_objects = 0;

  Tracer::Tracer(const std::string &function_name)
    : m_function_name(function_name) {
    for (unsigned int i = 0; i < m_num_tracer_objects; i++)
      std::cout << "   ";
    std::cout << "-->" << m_function_name << std::endl;
    m_num_tracer_objects++;
  }

  Tracer::~Tracer() {
    m_num_tracer_objects--;
    for (unsigned int i = 0; i < m_num_tracer_objects; i++)
      std::cout << "   ";
    std::cout << "<--" << m_function_name << std::endl;
  }

}
