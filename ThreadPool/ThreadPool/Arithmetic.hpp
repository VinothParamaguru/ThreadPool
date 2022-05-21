//
//  Arithmetic.hpp
//  ThreadPool
//
//  Created by Vinoth Paramaguru on 20/05/2022.
//

#ifndef Arithmetic_hpp
#define Arithmetic_hpp

#include <stdio.h>

class CArithmetic {
  
public:
    int add(int a, int b) {
        return a + b;
    }

    int sub(int a, int b) {
        return a - b;
    }

    int mul(int a, int b) {
        return a * b;
    }

    int divide(int a, int b) {
        return a / b;
    }
};

#endif /* Arithmetic_hpp */
