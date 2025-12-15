//
// Created by Danny Mittal on 12/7/25.
//

#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const ll MOD = 1000000007;

struct Event {
    bool add;
    ll day;
    ll color;
};

class Trie {
    int population = 0;
public: ll sum = 0;
    Trie* left = nullptr;
    Trie* right = nullptr;

public: void update(Event event, int height) {
        if (height == 0) {
            if (event.add) {
                population++;
                sum += event.color;
            } else {
                population--;
                sum += MOD - event.color;
            }
        } else {
            if ((event.day & (1L << (height - 1))) == 0L) {
                if (left == nullptr) {
                    left = new Trie();
                }
                left->update(event, height - 1);
            } else {
                if (right == nullptr) {
                    right = new Trie();
                }
                right->update(event, height - 1);
            }
            if (left == nullptr || left->population == 0) {
                if (right == nullptr || right->population == 0) {
                    population = 0;
                    sum = 0;
                } else {
                    population = right->population;
                    sum = 2LL * right->sum;
                }
            } else {
                if (right == nullptr || right->population == 0) {
                    population = left->population;
                    sum = 2LL * left->sum;
                } else {
                    population = right->population;
                    sum = left->sum + right->sum;
                }
            }
        }
        if (sum >= MOD) {
            sum -= MOD;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (; t; t--) {
        int n, k, q;
        cin >> n >> k >> q;
        vector<vector<Event>> events(n + 1);
        for (; q; q--) {
            ll day, color;
            int from, to;
            cin >> day >> from >> to >> color;

            Event add, remove;
            add.add = true;
            add.day = day;
            add.color = color;
            remove.add = false;
            remove.day = day;
            remove.color = color;
            events[from - 1].push_back(add);
            events[to].push_back(remove);
        }
        Trie root;
        ll answer = 0;
        for (int x = 0; x < n; x++) {
            for (Event event : events[x]) {
                root.update(event, k);
            }
            answer += root.sum;
        }
        cout << answer % MOD << '\n';
    }
    cout << flush;
}