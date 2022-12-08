#pragma once
#include <iostream>
#include <chrono>
#include <string>

struct Timer{
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<float> duration{};
    std::string function_name;


    explicit Timer(const std::string &name)
    {
        start = std::chrono::high_resolution_clock::now();
        function_name = name;
    }

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        float ms = duration.count() * 1000.0f;
        std::cout << "Execution of " << function_name.c_str() << " took " << ms << "ms\n";
    }
};
