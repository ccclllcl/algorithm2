#include <iostream>
#include <cstdlib>  // for system()
#include <chrono>   // for timing
#include <thread>   // for sleep (if needed)

int main() {
    for (int i = 0; i < 100; ++i) {
        // 调用 rand_gen.exe
        int result_rand = std::system("rand_gen.exe");
        if (result_rand != 0) {
            std::cerr << "Error: rand_gen.exe failed with code " << result_rand << std::endl;
            return 1;  // 如果 rand_gen.exe 失败，终止程序
        }

        // 确保 rand_gen.exe 执行完毕后，调用 DDD.exe 并记录执行时间
        auto start = std::chrono::high_resolution_clock::now();

        int result_ddd = std::system("DDD.exe");
        if (result_ddd != 0) {
            std::cerr << "Error: DDD.exe failed with code " << result_ddd << std::endl;
            return 1;  // 如果 DDD.exe 失败，终止程序
        }

        // 计算DDD.exe的执行时间
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;

        // 输出执行时间（秒）
        std::cout << "DDD.exe execution time: " << elapsed_seconds.count() << " seconds" << std::endl;
    }

    return 0;
}
