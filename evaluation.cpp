//
// Created by Danny Mittal on 12/6/25.
//

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include "header.h"
#include "baselines.cpp"
#include "hikonv_unsigned.cpp"
#include "hikonv_signed.cpp"
#include "trikonv.cpp"

#include <iostream>
#include <iomanip>

// parameters generally varied for evaluation
const bool SIGNED = true;
const bool SWAPPED = false;

// parameters you may change if you want
const bool DEBUG = false;
const int NUM_TRIALS = 20;
const int LARGE_SIZE = 1000000;
const int SMALL_SIZE = 100;

// list of algorithms (can comment and uncomment to include/exclude certain algorithms)
std::vector<Algorithm> ALGORITHMS = {
        NAIVE, // this must always be first
        FFT,

        HIKONV_UNSIGNED_UNOPTIMIZED,
        HIKONV_UNSIGNED_9_1,
        HIKONV_UNSIGNED_8_2,
        HIKONV_UNSIGNED_7_4,
        HIKONV_UNSIGNED_6_5,
        HIKONV_UNSIGNED_5_6,
        HIKONV_UNSIGNED_128,

        HIKONV_SIGNED_UNOPTIMIZED,
        HIKONV_SIGNED_9_1,
        HIKONV_SIGNED_6_5,
        HIKONV_SIGNED_5_6,

        TRIKONV_UNOPTIMIZED,
        TRIKONV_11_2,
        TRIKONV_10_3,
        TRIKONV_9_4,
        TRIKONV_7_10,
        TRIKONV_2_BIT,
};

// parameters that should generally remain fixed
const int FROM = SIGNED ? -1 : 0;
const int TO = SIGNED ? 1 : 2;
const int KERNEL_SIZE = SWAPPED ? LARGE_SIZE : SMALL_SIZE;
const int INPUT_SIZE = SWAPPED ? SMALL_SIZE : LARGE_SIZE;

double current_time() {
    auto current_time = std::chrono::system_clock::now();
    auto duration_in_seconds = std::chrono::duration<double>(current_time.time_since_epoch());
    return duration_in_seconds.count();
}

std::ostream& operator<< (std::ostream& out, const std::vector<int>& v) {
    if ( !v.empty() ) {
        out << '[';
        std::ranges::copy(v, std::ostream_iterator<int>(out, ", "));
        out << "\b\b]"; // use two ANSI backspace characters '\b' to overwrite final ", "
    }
    return out;
}

void find_discrepancy(std::vector<int> expected, std::vector<int> actual) {
    if (actual.size() != expected.size()) {
        std::cout << "expected size " << expected.size() << ", actual size " << actual.size() << std::endl;
        return;
    }
    for (int j = 0; j < expected.size(); j++) {
        if (expected[j] != actual[j]) {
            std::cout << "at index " << j << ", expected " << expected[j] << ", actual " << actual[j] << std::endl;
            return;
        }
    }
    std::cout << "no discrepancy?" << std::endl;
}

std::vector<int> generate(int from, int to, int length) {
    std::vector<int> result(length);
    for (int j = 0; j < length; j++) {
        result[j] = from + (std::rand() % (to - from + 1));
    }
    return result;
}

int main() {
    srand(23);

    std::vector<Algorithm> considered;
    for (auto algorithm : ALGORITHMS) {
        if (algorithm.lower_bound <= FROM && algorithm.upper_bound >= TO && (!SWAPPED || algorithm.can_swap)) {
            considered.push_back(algorithm);
        }
    }

    std::vector<std::vector<double>> times(considered.size());
    for (int trial = 1; trial <= NUM_TRIALS; trial++) {

        std::vector<int> f = generate(FROM, TO, INPUT_SIZE);
        std::vector<int> g = generate(FROM, TO, KERNEL_SIZE);
        if (DEBUG) {
            std::cout << "TRIAL " << trial << std::endl;
            std::cout << "f = " << f << std::endl;
            std::cout << "g = " << g << std::endl;
        }

        std::vector<int> expected;
        for (int j = 0; j < considered.size(); j++) {
            Algorithm algorithm = considered[j];
            double start_time = current_time();
            std::vector<int> result = algorithm.function(f, g);
            double end_time = current_time();
            double elapsed_time = end_time - start_time;

            if (DEBUG) {
                std::cout << algorithm.name << ": result = " << result << std::endl;
            }

            if (j == 0) {
                expected = result;
            } else if (result != expected) {
                std::cout << "FAIL " << algorithm.name << std::endl;
                find_discrepancy(expected, result);
                return 0;
            }

            times[j].push_back(elapsed_time);
        }
        if (DEBUG) {
            std::cout << std::endl;
        }
    }

    std::cout << "RESULTS" << std::endl;
    for (int j = 0; j < considered.size(); j++) {
        std::cout << std::setw(47) << considered[j].name << " |\t";
        double time_sum = 0;
        for (double time : times[j]) {
            if (DEBUG) {
                std::cout << time << '\t';
            }
            time_sum += time;
        }
        if (DEBUG) {
            std::cout << "| ";
        }
        double average_time = time_sum / ((double) NUM_TRIALS);
        std::cout << "average time = " << average_time << std::endl;
    }

    return 0;
}
