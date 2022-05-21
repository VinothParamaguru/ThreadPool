//
//  main.cpp
//  ThreadPool
//
//  Created by Vinoth Paramaguru on 20/05/2022.
//

#include <iostream>
#include "ThreadPool.hpp"
#include "Arithmetic.hpp"

int main(int argc, const char * argv[]) {
    
    CThreadPool pool(5);
    CArithmetic arithmetic_operations;
    pool.AddJob(std::bind(&CArithmetic::add, &arithmetic_operations, 2, 2));
    pool.AddJob(std::bind(&CArithmetic::sub, &arithmetic_operations, 2, 2));
    pool.AddJob(std::bind(&CArithmetic::mul, &arithmetic_operations, 2, 2));
    return 0;
}
