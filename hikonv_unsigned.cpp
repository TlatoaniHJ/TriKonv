//
// Created by Danny Mittal on 12/15/25.
//

#include "header.h"

template<unsigned int N, unsigned int K>
std::vector<int> hikonv_unsigned(std::vector<int> f, std::vector<int> g) {
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
            for (int offset = 0; offset < K; offset++) {
                result[result_pos + offset] += C & MASK;
                C >>= S;
            }
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

std::vector<int> hikonv_unsigned_9_1(std::vector<int> f, std::vector<int> g) {
    const int N = 9;
    const int K = 1;
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

    std::vector<int> result(f.size() + g.size() - 1, 0);

    for (int f_pos = 0; f_pos < f.size(); f_pos += N) {
        ull A = ((ull) f[f_pos])
                + (((ull) f[f_pos + 1]) << 7)
                + (((ull) f[f_pos + 2]) << 14)
                + (((ull) f[f_pos + 3]) << 21)
                + (((ull) f[f_pos + 4]) << 28)
                + (((ull) f[f_pos + 5]) << 35)
                + (((ull) f[f_pos + 6]) << 42)
                + (((ull) f[f_pos + 7]) << 49)
                + (((ull) f[f_pos + 8]) << 56);

        ull C = 0;
        int result_pos = f_pos;
        for (ull B : Bs) {
            C += A * B;
            result[result_pos] += C & MASK;
            C >>= 7;
            result_pos += K;
        }
        result[result_pos] += C & MASK;
        result[result_pos + 1] += (C >> 7) & MASK;
        result[result_pos + 2] += (C >> 14) & MASK;
        result[result_pos + 3] += (C >> 21) & MASK;
        result[result_pos + 4] += (C >> 28) & MASK;
        result[result_pos + 5] += (C >> 35) & MASK;
        result[result_pos + 6] += (C >> 42) & MASK;
        result[result_pos + 7] += (C >> 49) & MASK;
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> hikonv_unsigned_8_2(std::vector<int> f, std::vector<int> g) {
    const int N = 8;
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

    std::vector<int> result(f.size() + g.size() - 1, 0);

    for (int f_pos = 0; f_pos < f.size(); f_pos += N) {
        ull A = ((ull) f[f_pos])
                + (((ull) f[f_pos + 1]) << 7)
                + (((ull) f[f_pos + 2]) << 14)
                + (((ull) f[f_pos + 3]) << 21)
                + (((ull) f[f_pos + 4]) << 28)
                + (((ull) f[f_pos + 5]) << 35)
                + (((ull) f[f_pos + 6]) << 42)
                + (((ull) f[f_pos + 7]) << 49);

        ull C = 0;
        int result_pos = f_pos;
        for (ull B : Bs) {
            C += A * B;
            result[result_pos] += C & MASK;
            result[result_pos + 1] += (C >> 7) & MASK;
            C >>= 14;
            result_pos += K;
        }
        result[result_pos] += C & MASK;
        result[result_pos + 1] += (C >> 7) & MASK;
        result[result_pos + 2] += (C >> 14) & MASK;
        result[result_pos + 3] += (C >> 21) & MASK;
        result[result_pos + 4] += (C >> 28) & MASK;
        result[result_pos + 5] += (C >> 35) & MASK;
        result[result_pos + 6] += (C >> 42) & MASK;
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> hikonv_unsigned_7_4(std::vector<int> f, std::vector<int> g) {
    const int N = 7;
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

    std::vector<int> result(f.size() + g.size() - 1, 0);

    for (int f_pos = 0; f_pos < f.size(); f_pos += N) {
        ull A = ((ull) f[f_pos])
                + (((ull) f[f_pos + 1]) << 6)
                + (((ull) f[f_pos + 2]) << 12)
                + (((ull) f[f_pos + 3]) << 18)
                + (((ull) f[f_pos + 4]) << 24)
                + (((ull) f[f_pos + 5]) << 30)
                + (((ull) f[f_pos + 6]) << 36);

        ull C = 0;
        int result_pos = f_pos;
        for (ull B : Bs) {
            C += A * B;
            result[result_pos] += C & MASK;
            result[result_pos + 1] += (C >> 6) & MASK;
            result[result_pos + 2] += (C >> 12) & MASK;
            result[result_pos + 3] += (C >> 18) & MASK;
            C >>= 24;
            result_pos += K;
        }
        result[result_pos] += C & MASK;
        result[result_pos + 1] += (C >> 6) & MASK;
        result[result_pos + 2] += (C >> 12) & MASK;
        result[result_pos + 3] += (C >> 18) & MASK;
        result[result_pos + 4] += (C >> 24) & MASK;
        result[result_pos + 5] += (C >> 30) & MASK;
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> hikonv_unsigned_6_5(std::vector<int> f, std::vector<int> g) {
    const int N = 6;
    const int K = 5;
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

    std::vector<int> result(f.size() + g.size() - 1, 0);

    for (int f_pos = 0; f_pos < f.size(); f_pos += N) {
        ull A = ((ull) f[f_pos])
                + (((ull) f[f_pos + 1]) << 6)
                + (((ull) f[f_pos + 2]) << 12)
                + (((ull) f[f_pos + 3]) << 18)
                + (((ull) f[f_pos + 4]) << 24)
                + (((ull) f[f_pos + 5]) << 30);

        ull C = 0;
        int result_pos = f_pos;
        for (ull B : Bs) {
            C += A * B;
            result[result_pos] += C & MASK;
            result[result_pos + 1] += (C >> 6) & MASK;
            result[result_pos + 2] += (C >> 12) & MASK;
            result[result_pos + 3] += (C >> 18) & MASK;
            result[result_pos + 4] += (C >> 24) & MASK;
            C >>= 30;
            result_pos += K;
        }
        result[result_pos] += C & MASK;
        result[result_pos + 1] += (C >> 6) & MASK;
        result[result_pos + 2] += (C >> 12) & MASK;
        result[result_pos + 3] += (C >> 18) & MASK;
        result[result_pos + 4] += (C >> 24) & MASK;
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> hikonv_unsigned_5_6(std::vector<int> f, std::vector<int> g) {
    const int N = 5;
    const int K = 6;
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

using u128 = __uint128_t;

std::vector<int> hikonv_unsigned_128(std::vector<int> f, std::vector<int> g) {
    const int N = 14;
    const int K = 5;
    const int S = 128 / (N + K - 1);
    const int MASK = (1 << S) - 1;

    //std::cout << "N = " << N << ", K = " << K << ", S = " << S << std::endl;

    int result_true_size = f.size() + g.size() - 1;
    while (f.size() % N != 0) {
        f.push_back(0);
    }
    while (g.size() % K != 0) {
        g.push_back(0);
    }
    std::vector<u128> Bs(g.size() / K, 0);
    for (int j = 0; j < g.size(); j++) {
        Bs[j / K] += ((u128) g[j]) << (S * (j % K));
    }

    std::vector<int> result(f.size() + g.size() - 1, 0);

    for (int f_pos = 0; f_pos < f.size(); f_pos += N) {
        u128 A = ((u128) f[f_pos])
                 + (((u128) f[f_pos + 1]) << 7)
                 + (((u128) f[f_pos + 2]) << 14)
                 + (((u128) f[f_pos + 3]) << 21)
                 + (((u128) f[f_pos + 4]) << 28)
                 + (((u128) f[f_pos + 5]) << 35)
                 + (((u128) f[f_pos + 6]) << 42)
                 + (((u128) f[f_pos + 7]) << 49)
                 + (((u128) f[f_pos + 8]) << 56)
                 + (((u128) f[f_pos + 9]) << 63)
                 + (((u128) f[f_pos + 10]) << 70)
                 + (((u128) f[f_pos + 11]) << 77)
                 + (((u128) f[f_pos + 12]) << 84)
                 + (((u128) f[f_pos + 13]) << 91);

        u128 C = 0;
        int result_pos = f_pos;
        for (u128 B : Bs) {
            C += A * B;
            result[result_pos] += C & MASK;
            result[result_pos + 1] += (C >> 7) & MASK;
            result[result_pos + 2] += (C >> 14) & MASK;
            result[result_pos + 3] += (C >> 21) & MASK;
            result[result_pos + 4] += (C >> 28) & MASK;
            C >>= 35;
            result_pos += K;
        }
        result[result_pos] += C & MASK;
        result[result_pos + 1] += (C >> 7) & MASK;
        result[result_pos + 2] += (C >> 14) & MASK;
        result[result_pos + 3] += (C >> 21) & MASK;
        result[result_pos + 4] += (C >> 28) & MASK;
        result[result_pos + 5] += (C >> 35) & MASK;
        result[result_pos + 6] += (C >> 42) & MASK;
        result[result_pos + 7] += (C >> 49) & MASK;
        result[result_pos + 8] += (C >> 56) & MASK;
        result[result_pos + 9] += (C >> 63) & MASK;
        result[result_pos + 10] += (C >> 70) & MASK;
        result[result_pos + 11] += (C >> 77) & MASK;
        result[result_pos + 12] += (C >> 84) & MASK;
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

Algorithm HIKONV_UNSIGNED_UNOPTIMIZED{hikonv_unsigned<5, 6>, "HiKonv unsigned (unoptimized, N = 5, K = 6)", 0, 3, true};
Algorithm HIKONV_UNSIGNED_9_1{hikonv_unsigned_9_1, "HiKonv unsigned (N = 9, K = 1)", 0, 3, true};
Algorithm HIKONV_UNSIGNED_8_2{hikonv_unsigned_8_2, "HiKonv unsigned (N = 8, K = 2)", 0, 3, true};
Algorithm HIKONV_UNSIGNED_7_4{hikonv_unsigned_7_4, "HiKonv unsigned (N = 7, K = 4)", 0, 3, true};
Algorithm HIKONV_UNSIGNED_6_5{hikonv_unsigned_6_5, "HiKonv unsigned (N = 6, K = 5)", 0, 3, true};
Algorithm HIKONV_UNSIGNED_5_6{hikonv_unsigned_5_6, "HiKonv unsigned (N = 5, K = 6)", 0, 3, true};
Algorithm HIKONV_UNSIGNED_128{hikonv_unsigned_128, "HiKonv unsigned 128-bit (N = 14, K = 5)", 0, 3, true};