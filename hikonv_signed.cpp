//
// Created by Danny Mittal on 12/15/25.
//

#include "header.h"

template<unsigned int N, unsigned int K>
std::vector<int> hikonv_signed(std::vector<int> f, std::vector<int> g) {
    const int S = 64 / (N + K - 1);
    const int SIGN_BIT = 1 << (S - 1);
    const int MASK = SIGN_BIT - 1;

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

std::vector<int> hikonv_signed_9_1(std::vector<int> f, std::vector<int> g) {
    const int N = 9;
    const int K = 1;
    const int S = 64 / (N + K - 1);
    const int SIGN_BIT = 1 << (S - 1);
    const ll HIGH_SIGN_BIT = ((ull) 1) << ((K * S) - 1);
    const int MASK = SIGN_BIT - 1;

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
               + (((ll) f[f_pos + 1]) << 7)
               + (((ll) f[f_pos + 2]) << 14)
               + (((ll) f[f_pos + 3]) << 21)
               + (((ll) f[f_pos + 4]) << 28)
               + (((ll) f[f_pos + 5]) << 35)
               + (((ll) f[f_pos + 6]) << 42)
               + (((ll) f[f_pos + 7]) << 49)
               + (((ll) f[f_pos + 8]) << 56);

        ll C = 0;
        int result_pos = f_pos;
        for (ll B : Bs) {
            C += A * B;
            result[result_pos] += (C & MASK) - ((C & SIGN_BIT));
            C += C & HIGH_SIGN_BIT;
            C >>= 7;
            result_pos += K;
        }
        result[result_pos] += (C & MASK) - ((C & SIGN_BIT));
        result[result_pos + 1] += ((C >> 7) & MASK) - ((C >> 7) & SIGN_BIT) + ((C >> 6) & 1);
        result[result_pos + 2] += ((C >> 14) & MASK) - ((C >> 14) & SIGN_BIT) + ((C >> 13) & 1);
        result[result_pos + 3] += ((C >> 21) & MASK) - ((C >> 21) & SIGN_BIT) + ((C >> 20) & 1);
        result[result_pos + 4] += ((C >> 28) & MASK) - ((C >> 28) & SIGN_BIT) + ((C >> 27) & 1);
        result[result_pos + 5] += ((C >> 35) & MASK) - ((C >> 35) & SIGN_BIT) + ((C >> 34) & 1);
        result[result_pos + 6] += ((C >> 42) & MASK) - ((C >> 42) & SIGN_BIT) + ((C >> 41) & 1);
        result[result_pos + 7] += ((C >> 49) & MASK) - ((C >> 49) & SIGN_BIT) + ((C >> 48) & 1);
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> hikonv_signed_6_5(std::vector<int> f, std::vector<int> g) {
    const int N = 6;
    const int K = 5;
    const int S = 64 / (N + K - 1);
    const int SIGN_BIT = 1 << (S - 1);
    const ll HIGH_SIGN_BIT = ((ull) 1) << ((K * S) - 1);
    const int MASK = SIGN_BIT - 1;

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
               + (((ll) f[f_pos + 4]) << 24)
               + (((ll) f[f_pos + 5]) << 30);

        ll C = 0;
        int result_pos = f_pos;
        for (ll B : Bs) {
            C += A * B;
            result[result_pos] += (C & MASK) - ((C & SIGN_BIT));
            result[result_pos + 1] += ((C >> 6) & MASK) - ((C >> 6) & SIGN_BIT) + ((C >> 5) & 1);
            result[result_pos + 2] += ((C >> 12) & MASK) - ((C >> 12) & SIGN_BIT) + ((C >> 11) & 1);
            result[result_pos + 3] += ((C >> 18) & MASK) - ((C >> 18) & SIGN_BIT) + ((C >> 17) & 1);
            result[result_pos + 4] += ((C >> 24) & MASK) - ((C >> 24) & SIGN_BIT) + ((C >> 23) & 1);
            C += C & HIGH_SIGN_BIT;
            C >>= 30;
            result_pos += K;
        }
        result[result_pos] += (C & MASK) - ((C & SIGN_BIT));
        result[result_pos + 1] += ((C >> 6) & MASK) - ((C >> 6) & SIGN_BIT) + ((C >> 5) & 1);
        result[result_pos + 2] += ((C >> 12) & MASK) - ((C >> 12) & SIGN_BIT) + ((C >> 11) & 1);
        result[result_pos + 3] += ((C >> 18) & MASK) - ((C >> 18) & SIGN_BIT) + ((C >> 17) & 1);
        result[result_pos + 4] += ((C >> 24) & MASK) - ((C >> 24) & SIGN_BIT) + ((C >> 23) & 1);
    }

    while (result.size() > result_true_size) {
        result.pop_back();
    }
    return result;
}

std::vector<int> hikonv_signed_5_6(std::vector<int> f, std::vector<int> g) {
    const int N = 5;
    const int K = 6;
    const int S = 64 / (N + K - 1);
    const int SIGN_BIT = 1 << (S - 1);
    const ll HIGH_SIGN_BIT = ((ull) 1) << ((K * S) - 1);
    const int MASK = SIGN_BIT - 1;

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
            C += A * B;
            result[result_pos] += (C & MASK) - ((C & SIGN_BIT));
            result[result_pos + 1] += ((C >> 6) & MASK) - ((C >> 6) & SIGN_BIT) + ((C >> 5) & 1);
            result[result_pos + 2] += ((C >> 12) & MASK) - ((C >> 12) & SIGN_BIT) + ((C >> 11) & 1);
            result[result_pos + 3] += ((C >> 18) & MASK) - ((C >> 18) & SIGN_BIT) + ((C >> 17) & 1);
            result[result_pos + 4] += ((C >> 24) & MASK) - ((C >> 24) & SIGN_BIT) + ((C >> 23) & 1);
            result[result_pos + 5] += ((C >> 30) & MASK) - ((C >> 30) & SIGN_BIT) + ((C >> 29) & 1);
            C += C & HIGH_SIGN_BIT;
            C >>= 36;
            result_pos += K;
        }
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

Algorithm HIKONV_SIGNED_UNOPTIMIZED{hikonv_signed<5, 6>, "HiKonv signed (unoptimized, N = 5, K = 6)", -2, 1, true};
Algorithm HIKONV_SIGNED_9_1{hikonv_signed_9_1, "HiKonv signed (N = 9, K = 1)", -2, 1, true};
Algorithm HIKONV_SIGNED_6_5{hikonv_signed_6_5, "HiKonv signed (N = 6, K = 5)", -2, 1, true};
Algorithm HIKONV_SIGNED_5_6{hikonv_signed_5_6, "HiKonv signed (N = 5, K = 6)", -2, 1, true};