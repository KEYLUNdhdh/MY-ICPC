#include <bits/stdc++.h>

uint64_t rnd_state = 1145141919810ULL; 
inline uint32_t fast_rnd() {
    rnd_state ^= rnd_state << 13;
    rnd_state ^= rnd_state >> 7;
    rnd_state ^= rnd_state << 17;
    return rnd_state;
}