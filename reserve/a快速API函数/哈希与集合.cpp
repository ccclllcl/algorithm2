#include<bits/stdc++.h>
#define LL long long
const int P = 30000019;
int n;
using namespace std;
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
} HH;
int sta[P], top;
struct uset {
    struct edge {
        pair<int, LL> v;
        int next;
        edge() {} edge(pair<int, LL> _v, int _next) {
            v = _v;
            next = _next;
        }
    } e[20000011];
    int head[P], sz;
    uset() {
        memset(head, -1, sizeof(head));
        sz = 0;
    }
    void insert(pair<int, LL> x) {
        int u = HH(x.second * n + x.first) % P;
        sta[++top] = u;

        for (int i = head[u]; ~i; i = e[i].next)
            if (e[i].v == x)
                return;

        e[++sz] = edge(x, head[u]);
        head[u] = sz;
    }
    bool find(pair<int, LL> x) {
        int u = HH(x.second * n + x.first) % P;

        for (int i = head[u]; ~i; i = e[i].next)
            if (e[i].v == x)
                return 1;

        return 0;
    }
} st;