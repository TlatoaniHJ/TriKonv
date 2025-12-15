//
// Created by Danny Mittal on 12/6/25.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <bitset>

/*const bool SIGNED = false;
const int NUM_TESTED_IDS = 3;
const int TESTED_IDS[NUM_TESTED_IDS] = {0, 1, 2};*/

const bool SIGNED = true;
const int NUM_TESTED_IDS = 6;
const int TESTED_IDS[NUM_TESTED_IDS] = {0, 6, 7, 11, 12, 13};

const bool DEBUG = false;
const int FROM = SIGNED ? -1 : 0;
const int TO = SIGNED ? 1 : 2;
const int NUM_TRIALS = 20;
const int KERNEL_SIZE = 100;
const int INPUT_SIZE = 1000000;

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

std::vector<int> conv_inventory(int id, std::vector<int> f, std::vector<int> g);

std::string conv_inventory_name(int id);

std::vector<int> generate(int from, int to, int length);

int main() {
    //srand(100);
    srand(23);

    std::vector<double> times[NUM_TESTED_IDS];
    for (int trial = 1; trial <= NUM_TRIALS; trial++) {

        std::vector<int> f = generate(FROM, TO, INPUT_SIZE);
        std::vector<int> g = generate(FROM, TO, KERNEL_SIZE);
        if (DEBUG) {
            std::cout << "TRIAL " << trial << std::endl;
            std::cout << "f = " << f << std::endl;
            std::cout << "g = " << g << std::endl;
        }

        std::vector<int> expected;
        for (int j = 0; j < NUM_TESTED_IDS; j++) {
            int id = TESTED_IDS[j];
            std::string name = conv_inventory_name(id);
            double start_time = current_time();
            std::vector<int> result = conv_inventory(id, f, g);
            double end_time = current_time();
            double elapsed_time = end_time - start_time;

            if (DEBUG) {
                std::cout << name << ": result = " << result << std::endl;
            }

            if (id == 0) {
                expected = result;
            } else if (result != expected) {
                std::cout << "FAIL " << name << std::endl;
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
    for (int j = 0; j < NUM_TESTED_IDS; j++) {
        std::cout << conv_inventory_name(TESTED_IDS[j]) << "\t|\t";
        double time_sum = 0;
        for (double time : times[j]) {
            //std::cout << time << '\t';
            time_sum += time;
        }
        double average_time = time_sum / ((double) NUM_TRIALS);
        std::cout << "|\taverage time = " << average_time << std::endl;
    }

    return 0;
}

using ull = unsigned long long;
using ll = long long;

std::vector<int> naive(std::vector<int> f, std::vector<int> g) {
    std::vector<int> result(f.size() + g.size() - 1);
    for (int j = 0; j < f.size(); j++) {
        for (int k = 0; k < g.size(); k++) {
            result[j + k] += f[j] * g[k];
        }
    }
    return result;
}

const int TOTAL_BITS = 64;

std::vector<int> hikonv_unsigned(std::vector<int> f, std::vector<int> g) {
    const int N = 5;
    const int K = 6;
    const int S = TOTAL_BITS / (N + K - 1);
    const int MASK = (1 << S) - 1;

    //std::cout << "N = " << N << ", K = " << K << ", S = " << S << std::endl;

    int result_true_size = f.size() + g.size() - 1;
    while (f.size() % N != 0) {
        f.push_back(0);
    }
    while (g.size() % K != 0) {
        g.push_back(0);
    }
    std::vector<ull> Bs(g.size() / K, 0);
    for (int j = 0; j < g.size(); j++) {
        Bs[j / K] += ((ull) g[j]) << (S * (j % K));
    }

    std::vector<int> result(f.size() + g.size() - 1, 0);

    for (int f_pos = 0; f_pos < f.size(); f_pos += N) {
        ull A = 0;
        for (int offset = 0; offset < N; offset++) {
            A += ((ull) f[f_pos + offset]) << (S * offset);
        }

        ull C = 0;
        int result_pos = f_pos;
        for (ull B : Bs) {
            C += A * B;
            result[result_pos] += C & MASK;
            result[result_pos + 1] += (C >> 6) & MASK;
            result[result_pos + 2] += (C >> 12) & MASK;
            result[result_pos + 3] += (C >> 18) & MASK;
            result[result_pos + 4] += (C >> 24) & MASK;
            result[result_pos + 5] += (C >> 30) & MASK;
            C >>= 36;
            result_pos += K;
        }
        for (int offset = 0; offset < N - 1; offset++) {
            result[result_pos + offset] += C & MASK;
            C >>= S;
        }
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

template<unsigned int N, unsigned int K>
std::vector<int> hikonv_signed(std::vector<int> f, std::vector<int> g) {
    const int S = TOTAL_BITS / (N + K - 1);
    const int SIGN_BIT = 1 << (S - 1);
    const int MASK = SIGN_BIT - 1;

    //std::cout << "N = " << N << ", K = " << K << ", S = " << S << std::endl;

    int result_true_size = f.size() + g.size() - 1;
    while (f.size() % N != 0) {
        f.push_back(0);
    }
    while (g.size() % K != 0) {
        g.push_back(0);
    }
    std::vector<ll> Bs(g.size() / K, 0);
    for (int j = 0; j < g.size(); j++) {
        Bs[j / K] += ((ll) g[j]) << (S * (j % K));
    }

    std::vector<int> result(f.size() + g.size() - 1, 0);

    for (int f_pos = 0; f_pos < f.size(); f_pos += N) {
        ll A = 0;
        for (int offset = 0; offset < N; offset++) {
            A += ((ll) f[f_pos + offset]) << (S * offset);
        }

        ll C = 0;
        int result_pos = f_pos;
        for (ll B : Bs) {
            C += A * B;
            for (int offset = 0; offset < K; offset++) {
                //std::cout << "result_pos + offset = " << result_pos + offset << ", C & MASK = " << (C & MASK) << ", sign bit = " << (C & SIGN_BIT) << std::endl;
                //std::cout << '\t' << "C = " << std::bitset<64>(C) << std::endl;
                result[result_pos + offset] += C & MASK;
                int sign_bit = C & SIGN_BIT;
                C >>= S;
                if (sign_bit) {
                    result[result_pos + offset] -= SIGN_BIT;
                    C++;
                }
            }
            result_pos += K;
        }
        for (int offset = 0; offset < N - 1; offset++) {
            //std::cout << "result_pos + offset = " << result_pos + offset << ", C & MASK = " << (C & MASK) << ", sign bit = " << (C & SIGN_BIT) << std::endl;
            //std::cout << '\t' << "C = " << std::bitset<64>(C) << std::endl;
            result[result_pos + offset] += C & MASK;
            if (C & SIGN_BIT) {
                result[result_pos + offset] -= SIGN_BIT;
                C += SIGN_BIT;
            }
            C >>= S;
        }
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> trikonv(std::vector<int> f, std::vector<int> g) {
    const int N = 7;
    const int K = 10;
    const int S = TOTAL_BITS / (N + K - 1);
    const int MASK = (1 << S) - 1;

    //std::cout << "N = " << N << ", K = " << K << ", S = " << S << std::endl;

    int result_true_size = f.size() + g.size() - 1;
    while (f.size() % N != 0) {
        f.push_back(0);
    }
    while (g.size() % K != 0) {
        g.push_back(0);
    }
    std::vector<ull> Bs(g.size() / K, 0);
    for (int j = 0; j < g.size(); j++) {
        Bs[j / K] += ((ull) g[j]) << (S * (j % K));
    }

    ull initial_base = 0;
    for (int offset = 0; offset < N - 1; offset++) {
        initial_base += ((ull) N) << (offset * S);
    }
    ull refill_base = 0;
    for (int offset = N - 1; offset < K + N - 1; offset++) {
        refill_base += ((ull) N) << (offset * S);
    }

    std::vector<int> result(f.size() + g.size() - 1, 0);

    for (int f_pos = 0; f_pos < f.size(); f_pos += N) {
        ull A = 0;
        for (int offset = 0; offset < N; offset++) {
            A += ((ull) f[f_pos + offset]) << (S * offset);
        }

        ull C = initial_base;
        int result_pos = f_pos;
        for (ull B : Bs) {
            C += refill_base + (A * B);
            result[result_pos] += (C & MASK) - N;
            result[result_pos + 1] += ((C >> 4) & MASK) - N;
            result[result_pos + 2] += ((C >> 8) & MASK) - N;
            result[result_pos + 3] += ((C >> 12) & MASK) - N;
            result[result_pos + 4] += ((C >> 16) & MASK) - N;
            result[result_pos + 5] += ((C >> 20) & MASK) - N;
            result[result_pos + 6] += ((C >> 24) & MASK) - N;
            result[result_pos + 7] += ((C >> 28) & MASK) - N;
            result[result_pos + 8] += ((C >> 32) & MASK) - N;
            result[result_pos + 9] += ((C >> 36) & MASK) - N;
            C >>= 40;
            result_pos += K;
        }
        for (int offset = 0; offset < N - 1; offset++) {
            //std::cout << "result_pos = " << result_pos << ", offset = " << offset << std::endl;
            //std::cout << '\t' << "C = " << std::bitset<64>(C) << std::endl;
            result[result_pos + offset] += (C & MASK) - N;
            C >>= S;
        }
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> hikonv_unsigned_2(std::vector<int> f, std::vector<int> g) {
    const int N = 5;
    const int K = 6;
    const int S = TOTAL_BITS / (N + K - 1);
    const int MASK = (1 << S) - 1;

    //std::cout << "N = " << N << ", K = " << K << ", S = " << S << std::endl;

    int result_true_size = f.size() + g.size() - 1;
    while (f.size() % N != 0) {
        f.push_back(0);
    }
    while (g.size() % K != 0) {
        g.push_back(0);
    }
    std::vector<ull> Bs(g.size() / K, 0);
    for (int j = 0; j < g.size(); j++) {
        Bs[j / K] += ((ull) g[j]) << (S * (j % K));
    }

    std::vector<int> result(f.size() + g.size() - 1, 0);

    for (int f_pos = 0; f_pos < f.size(); f_pos += N) {
        ull A = ((ull) f[f_pos])
                + (((ull) f[f_pos + 1]) << 6)
                + (((ull) f[f_pos + 2]) << 12)
                + (((ull) f[f_pos + 3]) << 18)
                + (((ull) f[f_pos + 4]) << 24);

        ull C = 0;
        int result_pos = f_pos;
        for (ull B : Bs) {
            C += A * B;
            result[result_pos] += C & MASK;
            result[result_pos + 1] += (C >> 6) & MASK;
            result[result_pos + 2] += (C >> 12) & MASK;
            result[result_pos + 3] += (C >> 18) & MASK;
            result[result_pos + 4] += (C >> 24) & MASK;
            result[result_pos + 5] += (C >> 30) & MASK;
            C >>= 36;
            result_pos += K;
        }
        result[result_pos] += C & MASK;
        result[result_pos + 1] += (C >> 6) & MASK;
        result[result_pos + 2] += (C >> 12) & MASK;
        result[result_pos + 3] += (C >> 18) & MASK;
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> hikonv_signed_2(std::vector<int> f, std::vector<int> g) {
    const int N = 5;
    const int K = 6;
    const int S = TOTAL_BITS / (N + K - 1);
    const int SIGN_BIT = 1 << (S - 1);
    const ll HIGH_SIGN_BIT = ((ull) 1) << ((K * S) - 1);
    const int MASK = SIGN_BIT - 1;

    //std::cout << "N = " << N << ", K = " << K << ", S = " << S << std::endl;

    int result_true_size = f.size() + g.size() - 1;
    while (f.size() % N != 0) {
        f.push_back(0);
    }
    while (g.size() % K != 0) {
        g.push_back(0);
    }
    std::vector<ll> Bs(g.size() / K, 0);
    for (int j = 0; j < g.size(); j++) {
        Bs[j / K] += ((ll) g[j]) << (S * (j % K));
    }

    std::vector<int> result(f.size() + g.size() - 1, 0);

    for (int f_pos = 0; f_pos < f.size(); f_pos += N) {
        ll A = ((ll) f[f_pos])
                + (((ll) f[f_pos + 1]) << 6)
                + (((ll) f[f_pos + 2]) << 12)
                + (((ll) f[f_pos + 3]) << 18)
                + (((ll) f[f_pos + 4]) << 24);

        ll C = 0;
        int result_pos = f_pos;
        for (ll B : Bs) {
            //std::cout << '\t' << "(C prev \t\t\t= " << std::bitset<64>(C) << ")" << std::endl;
            C += A * B;

            //std::cout << '\t' << "C \t\t\t\t\t= " << std::bitset<64>(C) << std::endl;
            result[result_pos] += (C & MASK) - ((C & SIGN_BIT));
            result[result_pos + 1] += ((C >> 6) & MASK) - ((C >> 6) & SIGN_BIT) + ((C >> 5) & 1);
            result[result_pos + 2] += ((C >> 12) & MASK) - ((C >> 12) & SIGN_BIT) + ((C >> 11) & 1);
            result[result_pos + 3] += ((C >> 18) & MASK) - ((C >> 18) & SIGN_BIT) + ((C >> 17) & 1);
            result[result_pos + 4] += ((C >> 24) & MASK) - ((C >> 24) & SIGN_BIT) + ((C >> 23) & 1);
            result[result_pos + 5] += ((C >> 30) & MASK) - ((C >> 30) & SIGN_BIT) + ((C >> 29) & 1);
            C += C & HIGH_SIGN_BIT;
            //std::cout << '\t' << "(C with sign bit\t= " << std::bitset<64>(C) << ")" << std::endl;
            C >>= 36;
            result_pos += K;
        }
        //std::cout << '\t' << "C = " << std::bitset<64>(C) << std::endl;
        result[result_pos] += (C & MASK) - ((C & SIGN_BIT));
        result[result_pos + 1] += ((C >> 6) & MASK) - ((C >> 6) & SIGN_BIT) + ((C >> 5) & 1);
        result[result_pos + 2] += ((C >> 12) & MASK) - ((C >> 12) & SIGN_BIT) + ((C >> 11) & 1);
        result[result_pos + 3] += ((C >> 18) & MASK) - ((C >> 18) & SIGN_BIT) + ((C >> 17) & 1);
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> trikonv_2(std::vector<int> f, std::vector<int> g) {
    const int N = 7;
    const int K = 10;
    const int S = TOTAL_BITS / (N + K - 1);
    const int MASK = (1 << S) - 1;

    //std::cout << "N = " << N << ", K = " << K << ", S = " << S << std::endl;

    int result_true_size = f.size() + g.size() - 1;
    while (f.size() % N != 0) {
        f.push_back(0);
    }
    while (g.size() % K != 0) {
        g.push_back(0);
    }
    std::vector<ull> Bs(g.size() / K, 0);
    for (int j = 0; j < g.size(); j++) {
        Bs[j / K] += ((ull) g[j]) << (S * (j % K));
    }

    ull initial_base = 0;
    for (int offset = 0; offset < N - 1; offset++) {
        initial_base += ((ull) N) << (offset * S);
    }
    ull refill_base = 0;
    for (int offset = N - 1; offset < K + N - 1; offset++) {
        refill_base += ((ull) N) << (offset * S);
    }

    std::vector<int> result(f.size() + g.size() - 1, 0);

    for (int f_pos = 0; f_pos < f.size(); f_pos += N) {
        ull A = ((ull) f[f_pos])
                + (((ull) f[f_pos + 1]) << 4)
                + (((ull) f[f_pos + 2]) << 8)
                + (((ull) f[f_pos + 3]) << 12)
                + (((ull) f[f_pos + 4]) << 16)
                + (((ull) f[f_pos + 5]) << 20)
                + (((ull) f[f_pos + 6]) << 24);

        ull C = initial_base;
        int result_pos = f_pos;
        for (ull B : Bs) {
            C += refill_base + (A * B);
            result[result_pos] += (C & MASK) - N;
            result[result_pos + 1] += ((C >> 4) & MASK) - N;
            result[result_pos + 2] += ((C >> 8) & MASK) - N;
            result[result_pos + 3] += ((C >> 12) & MASK) - N;
            result[result_pos + 4] += ((C >> 16) & MASK) - N;
            result[result_pos + 5] += ((C >> 20) & MASK) - N;
            result[result_pos + 6] += ((C >> 24) & MASK) - N;
            result[result_pos + 7] += ((C >> 28) & MASK) - N;
            result[result_pos + 8] += ((C >> 32) & MASK) - N;
            result[result_pos + 9] += ((C >> 36) & MASK) - N;
            C >>= 40;
            result_pos += K;
        }
        result[result_pos] += (C & MASK) - N;
        result[result_pos + 1] += ((C >> 4) & MASK) - N;
        result[result_pos + 2] += ((C >> 8) & MASK) - N;
        result[result_pos + 3] += ((C >> 12) & MASK) - N;
        result[result_pos + 4] += ((C >> 16) & MASK) - N;
        result[result_pos + 5] += ((C >> 20) & MASK) - N;
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> trikonv_not_tri(std::vector<int> f, std::vector<int> g) {
    const int N = 5;
    const int K = 8;
    const int S = TOTAL_BITS / (N + K - 1);
    const int MASK = (1 << S) - 1;

    //std::cout << "N = " << N << ", K = " << K << ", S = " << S << std::endl;

    int result_true_size = f.size() + g.size() - 1;
    while (f.size() % N != 0) {
        f.push_back(0);
    }
    while (g.size() % K != 0) {
        g.push_back(0);
    }
    std::vector<ull> Bs(g.size() / K, 0);
    for (int j = 0; j < g.size(); j++) {
        Bs[j / K] += ((ull) g[j]) << (S * (j % K));
    }

    const int ADDEND = 2 * N;
    ull initial_base = 0;
    for (int offset = 0; offset < N - 1; offset++) {
        initial_base += ((ull) ADDEND) << (offset * S);
    }
    ull refill_base = 0;
    for (int offset = N - 1; offset < K + N - 1; offset++) {
        refill_base += ((ull) ADDEND) << (offset * S);
    }

    std::vector<int> result(f.size() + g.size() - 1, 0);

    for (int f_pos = 0; f_pos < f.size(); f_pos += N) {
        ull A = ((ull) f[f_pos])
                + (((ull) f[f_pos + 1]) << 5)
                + (((ull) f[f_pos + 2]) << 10)
                + (((ull) f[f_pos + 3]) << 15)
                + (((ull) f[f_pos + 4]) << 20);

        ull C = initial_base;
        int result_pos = f_pos;
        for (ull B : Bs) {
            C += refill_base + (A * B);
            result[result_pos] += (C & MASK) - ADDEND;
            result[result_pos + 1] += ((C >> 5) & MASK) - ADDEND;
            result[result_pos + 2] += ((C >> 10) & MASK) - ADDEND;
            result[result_pos + 3] += ((C >> 15) & MASK) - ADDEND;
            result[result_pos + 4] += ((C >> 20) & MASK) - ADDEND;
            result[result_pos + 5] += ((C >> 25) & MASK) - ADDEND;
            result[result_pos + 6] += ((C >> 30) & MASK) - ADDEND;
            result[result_pos + 7] += ((C >> 35) & MASK) - ADDEND;
            C >>= 40;
            result_pos += K;
        }
        result[result_pos] += (C & MASK) - ADDEND;
        result[result_pos + 1] += ((C >> 5) & MASK) - ADDEND;
        result[result_pos + 2] += ((C >> 10) & MASK) - ADDEND;
        result[result_pos + 3] += ((C >> 15) & MASK) - ADDEND;
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> conv_inventory(int id, std::vector<int> f, std::vector<int> g) {
    switch (id) {
        case 0: return naive(f, g);
        case 1: return hikonv_unsigned(f, g);
        case 2: return hikonv_unsigned_2(f, g);
        case 6: return hikonv_signed<5, 6>(f, g);
        case 7: return hikonv_signed_2(f, g);
        case 11: return trikonv(f, g);
        case 12: return trikonv_2(f, g);
        case 13: return trikonv_not_tri(f, g);
    }
}

std::string conv_inventory_name(int id) {
    switch (id) {
        case 0: return "Naive\t\t\t\t\t\t";
        case 1: return "HiKonv unsigned (N = 5, K = 6)";
        case 2: return "HiKonv unsigned 2 (N = 5, K = 6)";
        case 6: return "HiKonv signed (N = 5, K = 6)";
        case 7: return "HiKonv signed 2 (N = 5, K = 6)";
        case 11: return "TriKonv (N = 7, K = 10)";
        case 12: return "TriKonv 2 (N = 7, K = 10)";
        case 13: return "(not)TriKonv (N = 5, K = 8)";
    }
}


std::vector<int> generate(int from, int to, int length) {
    std::vector<int> result(length);
    for (int j = 0; j < length; j++) {
        result[j] = from + (std::rand() % (to - from + 1));
    }
    return result;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.