#pragma once

struct u128{
    
    uint64_t x1 = 0, x0 = 0;
    
    uint64_t upper(){return x1;}
    
    // not using karatsuba's. If this is ever "production" code, I should probably switch to a variant of it.
    friend u128 operator * (u128 a, u128 b){
        //u128 c{};
        
        /*// I gave up & just used the __uint128_t built in.
        c.x0 = a.x0*b.x0;
        
        std::cout << std::hex << "0x" << std::setw(16) << std::setfill('0') << c.x0 << "\n";
        
        uint64_t    a0 = (a.x0&0xFFFF'FFFF),
                    b0 = (b.x0&0xFFFF'FFFF),
                    a1 = (a.x0>>32),
                    b1 = (b.x0>>32),
                    a2 = (a.x1&0xFFFF'FFFF),
                    b2 = (b.x1&0xFFFF'FFFF),
                    a3 = (a.x1>>32),
                    b3 = (b.x1>>32);
        // manual multiplication with 32 bit chunks. Keeps the overflow accurate.
        c.x1 = a0*b0;
        c.x1 >>= 32;
        c.x1 += a1*b0;
        c.x1 += a0*b1;
        
        c.x1 >>= 32;
        
        c.x1 += a0*b2;
        c.x1 += a1*b1;
        c.x1 += a2*b0;
        
        c.x1 += (a3*b0)<<32;
        c.x1 += (a2*b1)<<32;
        c.x1 += (a1*b2)<<32;
        c.x1 += (a0*b3)<<32;//*/
        
        __uint128_t aa = __uint128_t(a.x1)<<64|__uint128_t(a.x0);
        __uint128_t bb = __uint128_t(b.x1)<<64|__uint128_t(b.x0);
        __uint128_t cc = aa*bb;
        
        // we can skip the last multiplication because it's out of bounds for a 128 bit multiplication.
        
        return {uint64_t((cc)>>64),(uint64_t)cc};
    }
    
    friend u128 operator + (u128 a, u128 b){
        u128 c{};
        
        c.x0 = a.x0+b.x0;
        
        uint64_t al = (a.x0&0xFFFF'FFFF),ah = (a.x0>>32),bl = (b.x0&0xFFFF'FFFF),bh = (b.x0>>32);
        
        c.x1 = al+bl;
        c.x1 >>= 32;
        c.x1 += ah+bh;
        c.x1 >>= 32;
        
        c.x1 += a.x1+b.x1;
        
        return c;
    }
};

