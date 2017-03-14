/*
 * ++C - C++ introduction
 * Copyright (C) 2013, 2014, 2015, 2016 Wilhelm Meier <wilhelm.meier@hs-kl.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

# ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable: 4996)
#  pragma warning(disable: 4573)
#endif

#include <iostream>
#include <cassert>
#include <string>
#include <cstdlib>

//#define EXPECT_EQ(a, b) {if (a != b) return false;}

#define CAT2(X, Y) X ## Y
#define CAT(X, Y) CAT2(X, Y)

#define SIMPLETEST(name) static PPC::SimpleTestCase CAT(SimpleTestCaseOnLine, __LINE__) = \
    PPC::SimpleTestCase(name, __FILE__, __LINE__) = []

namespace PPC {

class SimpleTestCase final {
public:
    SimpleTestCase(const char* name, const char* file, int line);

    template <typename T>
    SimpleTestCase& operator=(T lambda)
    {
        bool noOutput = false;
        bool noTests = false;
        const char* env = getenv("SIMPLETEST");
        if (env) {
            std::string envVar{env};
            if (envVar.find("nooutput") != std::string::npos) {
                noOutput = true;
            }
            if (envVar.find("notests") != std::string::npos) {
                noTests = true;
            }
        }
# ifndef NDEBUG
        if (!noOutput && !noTests) {
            std::cout << "Test(" << mName << "," << mFile << "," << mLine << ")";
        }
# endif
        if (!noTests) {
            ++mTestCount;
            if (lambda()) {
# ifndef NDEBUG
                if (!noOutput) {
                    std::cout << " ok " << "(" << mTestCount << "/" << mFailureCount << ")" << std::endl;
                }
# endif
            }
            else {
                ++mFailureCount;
# ifndef NDEBUG
                if (!noOutput) {
                    std::cout << " failed " << "(" << mTestCount << "/" << mFailureCount << ")" << std::endl;
                }
                else {
                    std::cerr << "Test(" << mName << "," << mFile << "," << mLine << ") failed " << "(" << mTestCount << "/" << mFailureCount << ")" << std::endl;
                }
# endif
            }
        }
        return *this;
    }
    static bool equal(double a, double b);
private:
    const char* mName{};
    int mLine{};
    const char* mFile{};
    static size_t mTestCount;
    static size_t mFailureCount;
};

//class SimpleTestCase {
//public:
//    SimpleTestCase(const char* name, const char* file, int line);

//    template <typename T>
//    SimpleTestCase& operator=(T lambda)
//    {
//        bool noOutput = false;
//        bool noTests = false;
//        const char* env = getenv("SIMPLETEST");
//        if (env) {
//            std::string envVar{env};
//            if (envVar.find("nooutput") != std::string::npos) {
//                noOutput = true;
//            }
//            if (envVar.find("notests") != std::string::npos) {
//                noTests = true;
//            }
//        }
//#ifndef NO_SIMPLETESTS
//# ifndef NDEBUG
//        if (!noOutput && !noTests) {
//            std::cout << "Test(" << mName << "," << mFile << "," << mLine << ")";
//        }
//# endif
//        if (!noTests) {
//            if (lambda()) {
//# ifndef NDEBUG
//                if (!noOutput) {
//                    std::cout << " ok" << std::endl;
//                }
//# endif
//            }
//            else {
//# ifndef NDEBUG
//                std::cout << " failed" << std::endl;
//# endif
//            }
//        }
//#else
//        (void)lambda;
//#endif
//        return *this;
//    }

//    static bool equal(double a, double b);
//private:
//    const char* mName;
//    int mLine;
//    const char* mFile;
//};

}
# ifdef _MSC_VER
#  pragma warning(pop)
#endif

