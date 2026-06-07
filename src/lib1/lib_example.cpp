module lib_example;

import std;

#include <logging/logging.hpp>

namespace modern_cmake_template {

    namespace {
        int doSomethingPrivate(int x) {
            return x * x;
        }
    }

    int example::exampleFunction(int value) {
        LOGIFACE_LOG(debug, "exampleFunction invoked");
        return value * 2;
    }

    int example::anotherExampleFunction(int value) {
        LOGIFACE_LOG(debug, "anotherExampleFunction invoked");
        int result = doSomethingPrivate(value);
        return result + 10;
    }

}
