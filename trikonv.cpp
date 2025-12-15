//
// Created by Danny Mittal on 12/15/25.
//

#include "header.h"

template<unsigned int N, unsigned int K>
std::vector<int> trikonv(std::vector<int> f, std::vector<int> g) {
    const int S = 64 / (N + K - 1);
    const int MASK = (1 << S) - 1;

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
            for (int offset = 0; offset < K; offset++) {
                result[result_pos + offset] += (C & MASK) - N;
                C >>= S;
            }
            result_pos += K;
        }
        for (int offset = 0; offset < N - 1; offset++) {
            result[result_pos + offset] += (C & MASK) - N;
            C >>= S;
        }
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> trikonv_11_2(std::vector<int> f, std::vector<int> g) {
    const int N = 11;
    const int K = 2;
    const int S = 64 / (N + K - 1);
    const int MASK = (1 << S) - 1;

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
                + (((ull) f[f_pos + 1]) << 5)
                + (((ull) f[f_pos + 2]) << 10)
                + (((ull) f[f_pos + 3]) << 15)
                + (((ull) f[f_pos + 4]) << 20)
                + (((ull) f[f_pos + 5]) << 25)
                + (((ull) f[f_pos + 6]) << 30)
                + (((ull) f[f_pos + 7]) << 35)
                + (((ull) f[f_pos + 8]) << 40)
                + (((ull) f[f_pos + 9]) << 45)
                + (((ull) f[f_pos + 10]) << 50);

        ull C = initial_base;
        int result_pos = f_pos;
        for (ull B : Bs) {
            C += refill_base + (A * B);
            result[result_pos] += (C & MASK) - N;
            result[result_pos + 1] += ((C >> 5) & MASK) - N;
            C >>= 10;
            result_pos += K;
        }
        result[result_pos] += (C & MASK) - N;
        result[result_pos + 1] += ((C >> 5) & MASK) - N;
        result[result_pos + 2] += ((C >> 10) & MASK) - N;
        result[result_pos + 3] += ((C >> 15) & MASK) - N;
        result[result_pos + 4] += ((C >> 20) & MASK) - N;
        result[result_pos + 5] += ((C >> 25) & MASK) - N;
        result[result_pos + 6] += ((C >> 30) & MASK) - N;
        result[result_pos + 7] += ((C >> 35) & MASK) - N;
        result[result_pos + 8] += ((C >> 40) & MASK) - N;
        result[result_pos + 9] += ((C >> 45) & MASK) - N;
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> trikonv_10_3(std::vector<int> f, std::vector<int> g) {
    const int N = 10;
    const int K = 3;
    const int S = 64 / (N + K - 1);
    const int MASK = (1 << S) - 1;

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
                + (((ull) f[f_pos + 1]) << 5)
                + (((ull) f[f_pos + 2]) << 10)
                + (((ull) f[f_pos + 3]) << 15)
                + (((ull) f[f_pos + 4]) << 20)
                + (((ull) f[f_pos + 5]) << 25)
                + (((ull) f[f_pos + 6]) << 30)
                + (((ull) f[f_pos + 7]) << 35)
                + (((ull) f[f_pos + 8]) << 40)
                + (((ull) f[f_pos + 9]) << 45);

        ull C = initial_base;
        int result_pos = f_pos;
        for (ull B : Bs) {
            C += refill_base + (A * B);
            result[result_pos] += (C & MASK) - N;
            result[result_pos + 1] += ((C >> 5) & MASK) - N;
            result[result_pos + 2] += ((C >> 10) & MASK) - N;
            C >>= 15;
            result_pos += K;
        }
        result[result_pos] += (C & MASK) - N;
        result[result_pos + 1] += ((C >> 5) & MASK) - N;
        result[result_pos + 2] += ((C >> 10) & MASK) - N;
        result[result_pos + 3] += ((C >> 15) & MASK) - N;
        result[result_pos + 4] += ((C >> 20) & MASK) - N;
        result[result_pos + 5] += ((C >> 25) & MASK) - N;
        result[result_pos + 6] += ((C >> 30) & MASK) - N;
        result[result_pos + 7] += ((C >> 35) & MASK) - N;
        result[result_pos + 8] += ((C >> 40) & MASK) - N;
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> trikonv_9_4(std::vector<int> f, std::vector<int> g) {
    const int N = 9;
    const int K = 4;
    const int S = 64 / (N + K - 1);
    const int MASK = (1 << S) - 1;

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
                + (((ull) f[f_pos + 1]) << 5)
                + (((ull) f[f_pos + 2]) << 10)
                + (((ull) f[f_pos + 3]) << 15)
                + (((ull) f[f_pos + 4]) << 20)
                + (((ull) f[f_pos + 5]) << 25)
                + (((ull) f[f_pos + 6]) << 30)
                + (((ull) f[f_pos + 7]) << 35)
                + (((ull) f[f_pos + 8]) << 40);

        ull C = initial_base;
        int result_pos = f_pos;
        for (ull B : Bs) {
            C += refill_base + (A * B);
            result[result_pos] += (C & MASK) - N;
            result[result_pos + 1] += ((C >> 5) & MASK) - N;
            result[result_pos + 2] += ((C >> 10) & MASK) - N;
            result[result_pos + 3] += ((C >> 15) & MASK) - N;
            C >>= 20;
            result_pos += K;
        }
        result[result_pos] += (C & MASK) - N;
        result[result_pos + 1] += ((C >> 5) & MASK) - N;
        result[result_pos + 2] += ((C >> 10) & MASK) - N;
        result[result_pos + 3] += ((C >> 15) & MASK) - N;
        result[result_pos + 4] += ((C >> 20) & MASK) - N;
        result[result_pos + 5] += ((C >> 25) & MASK) - N;
        result[result_pos + 6] += ((C >> 30) & MASK) - N;
        result[result_pos + 7] += ((C >> 35) & MASK) - N;
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> trikonv_7_10(std::vector<int> f, std::vector<int> g) {
    const int N = 7;
    const int K = 10;
    const int S = 64 / (N + K - 1);
    const int MASK = (1 << S) - 1;

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

std::vector<int> trikonv_5_8(std::vector<int> f, std::vector<int> g) {
    const int N = 5;
    const int K = 8;
    const int S = 64 / (N + K - 1);
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

Algorithm TRIKONV_UNOPTIMIZED{trikonv<7, 10>, "TriKonv (unoptimized, N = 7, K = 10)", -1, 1, true};
Algorithm TRIKONV_11_2{trikonv_11_2, "TriKonv (N = 11, K = 2)", -1, 1, true};
Algorithm TRIKONV_10_3{trikonv_10_3, "TriKonv (N = 10, K = 3)", -1, 1, true};
Algorithm TRIKONV_9_4{trikonv_9_4, "TriKonv (N = 9, K = 4)", -1, 1, true};
Algorithm TRIKONV_7_10{trikonv_7_10, "TriKonv (N = 7, K = 10)", -1, 1, true};
Algorithm TRIKONV_2_BIT{trikonv_5_8, "TriKonv for 2-bit quantization (N = 5, K = 8)", -1, 1, true};