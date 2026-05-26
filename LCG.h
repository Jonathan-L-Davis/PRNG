#pragma once

#include "u128.h"

template< u128 a, u128 c >
struct LCG{
    u128 state;
    
    uint64_t next(){
        state = state*a+c;
        return state.upper();
    }
};

