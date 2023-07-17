#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include <iomanip>

#define ARR_1K 1'000
#define ARR_10K 10'000
#define ARR_100K 100'000
#define ARR_1M 1'000'000
#define MAX_NUMBER 1'000

void set_random_num(std::vector<int>& vec) {
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist(0, MAX_NUMBER);
    std::generate(vec.begin(), vec.end(), [&](){ return dist(gen); });
}

void threads1(std::vector<int>& vec1_1k, std::vector<int>& vec2_1k, 
              std::vector<int>& vec1_10k, std::vector<int>& vec2_10k, 
              std::vector<int>& vec1_100k, std::vector<int>& vec2_100k, 
              std::vector<int>& vec1_1m, std::vector<int>& vec2_1m ) {
    /* Один поток */
    // 1'000;
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1([&vec1_1k, &vec2_1k](){
        for (int i = 0; i < vec1_1k.size(); i++)
            vec1_1k[i] + vec2_1k[i];
    });
    t1.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(6) << delta.count() << "ms";

    // 10'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t2([&vec1_10k, &vec2_10k](){
        for (int i = 0; i < vec1_10k.size(); i++)
            vec1_10k[i] + vec2_10k[i];
    });
    t2.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";

    // 100'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t3([&vec1_100k, &vec2_100k](){
        for (int i = 0; i < vec1_100k.size(); i++)
            vec1_100k[i] + vec2_100k[i];
    });
    t3.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";

    // 1'000'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t4([&vec1_1m, &vec2_1m](){
        for (int i = 0; i < vec1_1m.size(); i++)
            vec1_1m[i] + vec2_1m[i];
    });
    t4.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";
}

void threads2(std::vector<int>& vec1_1k, std::vector<int>& vec2_1k, 
              std::vector<int>& vec1_10k, std::vector<int>& vec2_10k, 
              std::vector<int>& vec1_100k, std::vector<int>& vec2_100k, 
              std::vector<int>& vec1_1m, std::vector<int>& vec2_1m ) {
    /* 2 потока */
    // 1'000
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1([&vec1_1k, &vec2_1k](){ for (int i = 0; i < vec1_1k.size(); i+=2) vec1_1k[i] + vec2_1k[i]; });
    std::thread t2([&vec1_1k, &vec2_1k](){ for (int i = 1; i < vec1_1k.size(); i+=2) vec1_1k[i] + vec2_1k[i]; });
    t1.detach();
    t2.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(5) << delta.count() << "ms";

    // 10'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t3([&vec1_10k, &vec2_10k](){ for (int i = 0; i < vec1_10k.size(); i+=2) vec1_10k[i] + vec2_10k[i]; });
    std::thread t4([&vec1_10k, &vec2_10k](){ for (int i = 1; i < vec1_10k.size(); i+=2) vec1_10k[i] + vec2_10k[i]; });
    t3.detach();
    t4.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";

    // 100'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t5([&vec1_100k, &vec2_100k](){ for (int i = 0; i < vec1_100k.size(); i+=2) vec1_100k[i] + vec2_100k[i]; });
    std::thread t6([&vec1_100k, &vec2_100k](){ for (int i = 1; i < vec1_100k.size(); i+=2) vec1_100k[i] + vec2_100k[i]; });
    t5.detach();
    t6.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";

    // 1'000'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t7([&vec1_1m, &vec2_1m](){ for (int i = 0; i < vec1_1m.size(); i+=2) vec1_1m[i] + vec2_1m[i]; });
    std::thread t8([&vec1_1m, &vec2_1m](){ for (int i = 1; i < vec1_1m.size(); i+=2) vec1_1m[i] + vec2_1m[i]; });
    t7.detach();
    t8.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";
}

void threads4(std::vector<int>& vec1_1k, std::vector<int>& vec2_1k, 
              std::vector<int>& vec1_10k, std::vector<int>& vec2_10k, 
              std::vector<int>& vec1_100k, std::vector<int>& vec2_100k, 
              std::vector<int>& vec1_1m, std::vector<int>& vec2_1m ) {
    /* 4 потока */
    // 1'000
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1([&vec1_1k, &vec2_1k](){ for(int i=0; i < vec1_1k.size(); i+=4) vec1_1k[i] + vec2_1k[i]; });
    std::thread t2([&vec1_1k, &vec2_1k](){ for(int i=1; i < vec1_1k.size(); i+=4) vec1_1k[i] + vec2_1k[i]; });
    std::thread t3([&vec1_1k, &vec2_1k](){ for(int i=2; i < vec1_1k.size(); i+=4) vec1_1k[i] + vec2_1k[i]; });
    std::thread t4([&vec1_1k, &vec2_1k](){ for(int i=3; i < vec1_1k.size(); i+=4) vec1_1k[i] + vec2_1k[i]; });
    t1.detach();
    t2.detach();
    t3.detach();
    t4.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(5) << delta.count() << "ms";

    // 10'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t5([&vec1_10k, &vec2_10k](){ for(int i=0; i < vec1_10k.size(); i+=4) vec1_10k[i] + vec2_10k[i]; });
    std::thread t6([&vec1_10k, &vec2_10k](){ for(int i=1; i < vec1_10k.size(); i+=4) vec1_10k[i] + vec2_10k[i]; });
    std::thread t7([&vec1_10k, &vec2_10k](){ for(int i=2; i < vec1_10k.size(); i+=4) vec1_10k[i] + vec2_10k[i]; });
    std::thread t8([&vec1_10k, &vec2_10k](){ for(int i=3; i < vec1_10k.size(); i+=4) vec1_10k[i] + vec2_10k[i]; });
    t5.detach();
    t6.detach();
    t7.detach();
    t8.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";

    // 100'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t9([&vec1_100k, &vec2_100k](){ for(int i=0; i < vec1_100k.size(); i+=4) vec1_100k[i] + vec2_100k[i]; });
    std::thread t10([&vec1_100k, &vec2_100k](){ for(int i=1; i < vec1_100k.size(); i+=4) vec1_100k[i] + vec2_100k[i]; });
    std::thread t11([&vec1_100k, &vec2_100k](){ for(int i=2; i < vec1_100k.size(); i+=4) vec1_100k[i] + vec2_100k[i]; });
    std::thread t12([&vec1_100k, &vec2_100k](){ for(int i=3; i < vec1_100k.size(); i+=4) vec1_100k[i] + vec2_100k[i]; });
    t9.detach();
    t10.detach();
    t11.detach();
    t12.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";

    // 1'000'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t13([&vec1_1m, &vec2_1m](){ for(int i=0; i < vec1_1m.size(); i+=4) vec1_1m[i] + vec2_1m[i]; });
    std::thread t14([&vec1_1m, &vec2_1m](){ for(int i=1; i < vec1_1m.size(); i+=4) vec1_1m[i] + vec2_1m[i]; });
    std::thread t15([&vec1_1m, &vec2_1m](){ for(int i=2; i < vec1_1m.size(); i+=4) vec1_1m[i] + vec2_1m[i]; });
    std::thread t16([&vec1_1m, &vec2_1m](){ for(int i=3; i < vec1_1m.size(); i+=4) vec1_1m[i] + vec2_1m[i]; });
    t13.detach();
    t14.detach();
    t15.detach();
    t16.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";

}

void threads8(std::vector<int>& vec1_1k, std::vector<int>& vec2_1k, 
              std::vector<int>& vec1_10k, std::vector<int>& vec2_10k, 
              std::vector<int>& vec1_100k, std::vector<int>& vec2_100k, 
              std::vector<int>& vec1_1m, std::vector<int>& vec2_1m ) {
    /* 8 потоков */
    // 1'000
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1([&vec1_1k, &vec2_1k](){ for(int i=0; i < vec1_1k.size(); i+=8) vec1_1k[i] + vec2_1k[i]; });
    std::thread t2([&vec1_1k, &vec2_1k](){ for(int i=1; i < vec1_1k.size(); i+=8) vec1_1k[i] + vec2_1k[i]; });
    std::thread t3([&vec1_1k, &vec2_1k](){ for(int i=2; i < vec1_1k.size(); i+=8) vec1_1k[i] + vec2_1k[i]; });
    std::thread t4([&vec1_1k, &vec2_1k](){ for(int i=3; i < vec1_1k.size(); i+=8) vec1_1k[i] + vec2_1k[i]; });
    std::thread t5([&vec1_1k, &vec2_1k](){ for(int i=4; i < vec1_1k.size(); i+=8) vec1_1k[i] + vec2_1k[i]; });
    std::thread t6([&vec1_1k, &vec2_1k](){ for(int i=5; i < vec1_1k.size(); i+=8) vec1_1k[i] + vec2_1k[i]; });
    std::thread t7([&vec1_1k, &vec2_1k](){ for(int i=6; i < vec1_1k.size(); i+=8) vec1_1k[i] + vec2_1k[i]; });
    std::thread t8([&vec1_1k, &vec2_1k](){ for(int i=7; i < vec1_1k.size(); i+=8) vec1_1k[i] + vec2_1k[i]; });
    t1.detach();
    t2.detach();
    t3.detach();
    t4.detach();
    t5.detach();
    t6.detach();
    t7.detach();
    t8.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(4) << delta.count() << "ms";

    // 10'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t9([&vec1_10k, &vec2_10k](){ for(int i=0; i < vec1_10k.size(); i+=8) vec1_10k[i] + vec2_10k[i]; });
    std::thread t10([&vec1_10k, &vec2_10k](){ for(int i=1; i < vec1_10k.size(); i+=8) vec1_10k[i] + vec2_10k[i]; });
    std::thread t11([&vec1_10k, &vec2_10k](){ for(int i=2; i < vec1_10k.size(); i+=8) vec1_10k[i] + vec2_10k[i]; });
    std::thread t12([&vec1_10k, &vec2_10k](){ for(int i=3; i < vec1_10k.size(); i+=8) vec1_10k[i] + vec2_10k[i]; });
    std::thread t13([&vec1_10k, &vec2_10k](){ for(int i=0; i < vec1_10k.size(); i+=8) vec1_10k[i] + vec2_10k[i]; });
    std::thread t14([&vec1_10k, &vec2_10k](){ for(int i=1; i < vec1_10k.size(); i+=8) vec1_10k[i] + vec2_10k[i]; });
    std::thread t15([&vec1_10k, &vec2_10k](){ for(int i=2; i < vec1_10k.size(); i+=8) vec1_10k[i] + vec2_10k[i]; });
    std::thread t16([&vec1_10k, &vec2_10k](){ for(int i=3; i < vec1_10k.size(); i+=8) vec1_10k[i] + vec2_10k[i]; });
    t9.detach();
    t10.detach();
    t11.detach();
    t12.detach();
    t13.detach();
    t14.detach();
    t15.detach();
    t16.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";

    // 100'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t17([&vec1_100k, &vec2_100k](){ for(int i=0; i < vec1_100k.size(); i+=8) vec1_100k[i] + vec2_100k[i]; });
    std::thread t18([&vec1_100k, &vec2_100k](){ for(int i=1; i < vec1_100k.size(); i+=8) vec1_100k[i] + vec2_100k[i]; });
    std::thread t19([&vec1_100k, &vec2_100k](){ for(int i=2; i < vec1_100k.size(); i+=8) vec1_100k[i] + vec2_100k[i]; });
    std::thread t20([&vec1_100k, &vec2_100k](){ for(int i=3; i < vec1_100k.size(); i+=8) vec1_100k[i] + vec2_100k[i]; });
    std::thread t21([&vec1_100k, &vec2_100k](){ for(int i=0; i < vec1_100k.size(); i+=8) vec1_100k[i] + vec2_100k[i]; });
    std::thread t22([&vec1_100k, &vec2_100k](){ for(int i=1; i < vec1_100k.size(); i+=8) vec1_100k[i] + vec2_100k[i]; });
    std::thread t23([&vec1_100k, &vec2_100k](){ for(int i=2; i < vec1_100k.size(); i+=8) vec1_100k[i] + vec2_100k[i]; });
    std::thread t24([&vec1_100k, &vec2_100k](){ for(int i=3; i < vec1_100k.size(); i+=8) vec1_100k[i] + vec2_100k[i]; });
    t17.detach();
    t18.detach();
    t19.detach();
    t20.detach();
    t21.detach();
    t22.detach();
    t23.detach();
    t24.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";

    // 1'000'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t25([&vec1_1m, &vec2_1m](){ for(int i=0; i < vec1_1m.size(); i+=8) vec1_1m[i] + vec2_1m[i]; });
    std::thread t26([&vec1_1m, &vec2_1m](){ for(int i=1; i < vec1_1m.size(); i+=8) vec1_1m[i] + vec2_1m[i]; });
    std::thread t27([&vec1_1m, &vec2_1m](){ for(int i=2; i < vec1_1m.size(); i+=8) vec1_1m[i] + vec2_1m[i]; });
    std::thread t28([&vec1_1m, &vec2_1m](){ for(int i=3; i < vec1_1m.size(); i+=8) vec1_1m[i] + vec2_1m[i]; });
    std::thread t29([&vec1_1m, &vec2_1m](){ for(int i=0; i < vec1_1m.size(); i+=8) vec1_1m[i] + vec2_1m[i]; });
    std::thread t30([&vec1_1m, &vec2_1m](){ for(int i=1; i < vec1_1m.size(); i+=8) vec1_1m[i] + vec2_1m[i]; });
    std::thread t31([&vec1_1m, &vec2_1m](){ for(int i=2; i < vec1_1m.size(); i+=8) vec1_1m[i] + vec2_1m[i]; });
    std::thread t32([&vec1_1m, &vec2_1m](){ for(int i=3; i < vec1_1m.size(); i+=8) vec1_1m[i] + vec2_1m[i]; });
    t25.detach();
    t26.detach();
    t27.detach();
    t28.detach();
    t29.detach();
    t30.detach();
    t31.detach();
    t32.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";
}

void threads16(std::vector<int>& vec1_1k, std::vector<int>& vec2_1k, 
              std::vector<int>& vec1_10k, std::vector<int>& vec2_10k, 
              std::vector<int>& vec1_100k, std::vector<int>& vec2_100k, 
              std::vector<int>& vec1_1m, std::vector<int>& vec2_1m ) {
    /* 16 потоков */
    // 1'000
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1([&vec1_1k, &vec2_1k](){ for(int i=0; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t2([&vec1_1k, &vec2_1k](){ for(int i=1; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t3([&vec1_1k, &vec2_1k](){ for(int i=2; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t4([&vec1_1k, &vec2_1k](){ for(int i=3; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t5([&vec1_1k, &vec2_1k](){ for(int i=4; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t6([&vec1_1k, &vec2_1k](){ for(int i=5; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t7([&vec1_1k, &vec2_1k](){ for(int i=6; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t8([&vec1_1k, &vec2_1k](){ for(int i=7; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t9([&vec1_1k, &vec2_1k](){ for(int i=8; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t10([&vec1_1k, &vec2_1k](){ for(int i=9; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t11([&vec1_1k, &vec2_1k](){ for(int i=10; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t12([&vec1_1k, &vec2_1k](){ for(int i=11; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t13([&vec1_1k, &vec2_1k](){ for(int i=12; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t14([&vec1_1k, &vec2_1k](){ for(int i=13; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t15([&vec1_1k, &vec2_1k](){ for(int i=14; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    std::thread t16([&vec1_1k, &vec2_1k](){ for(int i=15; i < vec1_1k.size(); i+=16) vec1_1k[i] + vec2_1k[i]; });
    t1.detach();
    t2.detach();
    t3.detach();
    t4.detach();
    t5.detach();
    t6.detach();
    t7.detach();
    t8.detach();
    t9.detach();
    t10.detach();
    t11.detach();
    t12.detach();
    t13.detach();
    t14.detach();
    t15.detach();
    t16.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(3) << delta.count() << "ms";

    // 10'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t17([&vec1_10k, &vec2_10k](){ for(int i=0; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t18([&vec1_10k, &vec2_10k](){ for(int i=1; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t19([&vec1_10k, &vec2_10k](){ for(int i=2; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t20([&vec1_10k, &vec2_10k](){ for(int i=3; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t21([&vec1_10k, &vec2_10k](){ for(int i=4; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t22([&vec1_10k, &vec2_10k](){ for(int i=5; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t23([&vec1_10k, &vec2_10k](){ for(int i=6; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t24([&vec1_10k, &vec2_10k](){ for(int i=7; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t25([&vec1_10k, &vec2_10k](){ for(int i=8; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t26([&vec1_10k, &vec2_10k](){ for(int i=9; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t27([&vec1_10k, &vec2_10k](){ for(int i=10; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t28([&vec1_10k, &vec2_10k](){ for(int i=11; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t29([&vec1_10k, &vec2_10k](){ for(int i=12; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t30([&vec1_10k, &vec2_10k](){ for(int i=13; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t31([&vec1_10k, &vec2_10k](){ for(int i=14; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    std::thread t32([&vec1_10k, &vec2_10k](){ for(int i=15; i < vec1_10k.size(); i+=16) vec1_10k[i] + vec2_10k[i]; });
    t17.detach();
    t18.detach();
    t19.detach();
    t20.detach();
    t21.detach();
    t22.detach();
    t23.detach();
    t24.detach();
    t25.detach();
    t26.detach();
    t27.detach();
    t28.detach();
    t29.detach();
    t30.detach();
    t31.detach();
    t32.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";

    // 100'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t33([&vec1_100k, &vec2_100k](){ for(int i=0; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t34([&vec1_100k, &vec2_100k](){ for(int i=1; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t35([&vec1_100k, &vec2_100k](){ for(int i=2; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t36([&vec1_100k, &vec2_100k](){ for(int i=3; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t37([&vec1_100k, &vec2_100k](){ for(int i=4; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t38([&vec1_100k, &vec2_100k](){ for(int i=5; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t39([&vec1_100k, &vec2_100k](){ for(int i=6; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t40([&vec1_100k, &vec2_100k](){ for(int i=7; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t41([&vec1_100k, &vec2_100k](){ for(int i=8; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t42([&vec1_100k, &vec2_100k](){ for(int i=9; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t43([&vec1_100k, &vec2_100k](){ for(int i=10; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t44([&vec1_100k, &vec2_100k](){ for(int i=11; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t45([&vec1_100k, &vec2_100k](){ for(int i=12; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t46([&vec1_100k, &vec2_100k](){ for(int i=13; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t47([&vec1_100k, &vec2_100k](){ for(int i=14; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    std::thread t48([&vec1_100k, &vec2_100k](){ for(int i=15; i < vec1_100k.size(); i+=16) vec1_100k[i] + vec2_100k[i]; });
    t33.detach();
    t34.detach();
    t35.detach();
    t36.detach();
    t37.detach();
    t38.detach();
    t39.detach();
    t40.detach();
    t41.detach();
    t42.detach();
    t43.detach();
    t44.detach();
    t45.detach();
    t46.detach();
    t47.detach();
    t48.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";

    // 1'000'000
    start = std::chrono::high_resolution_clock::now();
    std::thread t49([&vec1_1m, &vec2_1m](){ for(int i=0; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t50([&vec1_1m, &vec2_1m](){ for(int i=1; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t51([&vec1_1m, &vec2_1m](){ for(int i=2; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t52([&vec1_1m, &vec2_1m](){ for(int i=3; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t53([&vec1_1m, &vec2_1m](){ for(int i=4; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t54([&vec1_1m, &vec2_1m](){ for(int i=5; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t55([&vec1_1m, &vec2_1m](){ for(int i=6; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t56([&vec1_1m, &vec2_1m](){ for(int i=7; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t57([&vec1_1m, &vec2_1m](){ for(int i=8; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t58([&vec1_1m, &vec2_1m](){ for(int i=9; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t59([&vec1_1m, &vec2_1m](){ for(int i=10; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t60([&vec1_1m, &vec2_1m](){ for(int i=11; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t61([&vec1_1m, &vec2_1m](){ for(int i=12; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t62([&vec1_1m, &vec2_1m](){ for(int i=13; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t63([&vec1_1m, &vec2_1m](){ for(int i=14; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    std::thread t64([&vec1_1m, &vec2_1m](){ for(int i=15; i < vec1_1m.size(); i+=16) vec1_1m[i] + vec2_1m[i]; });
    t49.detach();
    t50.detach();
    t51.detach();
    t52.detach();
    t53.detach();
    t54.detach();
    t55.detach();
    t56.detach();
    t57.detach();
    t58.detach();
    t59.detach();
    t60.detach();
    t61.detach();
    t62.detach();
    t63.detach();
    t64.join();
    end = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(11) << delta.count() << "ms";

}

int main(void) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::vector<int> v1_1k(ARR_1K);
    std::vector<int> v2_1k(ARR_1K);
    set_random_num(v1_1k);
    set_random_num(v2_1k);

    std::vector<int> v1_10K(ARR_10K);
    std::vector<int> v2_10K(ARR_10K);
    set_random_num(v1_10K);
    set_random_num(v2_10K);

    std::vector<int> v1_100K(ARR_100K);
    std::vector<int> v2_100K(ARR_100K);
    set_random_num(v1_100K);
    set_random_num(v2_100K);

    std::vector<int> v1_1m(ARR_1M);
    std::vector<int> v2_1m(ARR_1M);
    set_random_num(v1_1m);
    set_random_num(v2_1m);

    // cout
    std::thread test([](){});
    std::cout << "Количество аппаратных ядер - " << test.hardware_concurrency() << std::endl << std::endl;
    test.join();

    std::cout << std::setw(14) << ARR_1K << std::setw(13) << ARR_10K << std::setw(13) << ARR_100K << std::setw(13) << ARR_1M << std::endl;
    std::cout << "1 поток ";
    threads1(v1_1k, v2_1k, v1_10K, v2_10K, v1_100K, v2_100K, v1_1m, v2_1m);
    std::cout << std::endl;

    std::cout << "2 потока ";
    threads2(v1_1k, v2_1k, v1_10K, v2_10K, v1_100K, v2_100K, v1_1m, v2_1m);
    std::cout << std::endl;
    
    std::cout << "4 потока ";
    threads4(v1_1k, v2_1k, v1_10K, v2_10K, v1_100K, v2_100K, v1_1m, v2_1m);
    std::cout << std::endl;

    std::cout << "8 потоков ";
    threads8(v1_1k, v2_1k, v1_10K, v2_10K, v1_100K, v2_100K, v1_1m, v2_1m);
    std::cout << std::endl;

    std::cout << "16 потоков ";
    threads16(v1_1k, v2_1k, v1_10K, v2_10K, v1_100K, v2_100K, v1_1m, v2_1m);
    std::cout << std::endl;
    return EXIT_SUCCESS;
}