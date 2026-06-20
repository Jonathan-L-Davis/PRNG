#pragma once

#include <iostream>
#include <iomanip>

uint64_t mul64_hi(uint64_t a, uint64_t b){
    
    uint64_t a0 = (a&0xFFFF'FFFFU);
    uint64_t b0 = (b&0xFFFF'FFFFU);
    uint64_t a1 = (a>>32);
    uint64_t b1 = (b>>32);
    
    uint64_t lo = a0*b0;
    uint64_t hi = a1*b1;
    uint64_t ma = a1*b0;
    uint64_t mb = a0*b1;
    
    uint64_t carry = ( (0xFFFF'FFFFU&ma)+(0xFFFF'FFFFU&mb)+(lo>>32))>>32;
    
    return hi+(ma>>32)+(mb>>32)+carry;
}

struct u128{
    
    uint64_t x1 = 0, x0 = 0;
    
    uint64_t upper(){return x1;}
    
    friend u128 operator + (u128 a, u128 b){
        u128 c{};
        
        c.x0 = a.x0+b.x0;
        c.x1 = a.x1+b.x1;
        
        // overflow low to high
        if (c.x0 < a.x0)
            c.x1++;
        
        return c;
    }
    
    friend u128 operator * (u128 a, u128 b){
        u128 c{};
        
        uint64_t a0 = a.x0;
        uint64_t b0 = b.x0;
        uint64_t a1 = a.x1;
        uint64_t b1 = b.x1;
        
        u128 lo,ma,mb;
        lo = {mul64_hi(a0,b0),a0*b0};
        ma = {a1*b0,0};
        mb = {a0*b1,0};
        
        c = lo+ma+mb;
        
        return c;
    }
};

