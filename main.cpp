#include <iostream>
#include <iomanip>
#include "u128.h"
#include "LCG.h"

uint8_t mul8_hi(uint8_t a, uint8_t b){
    
    uint8_t a0 = (a&0x0FU);
    uint8_t b0 = (b&0x0FU);
    uint8_t a1 = (a&0xF0U)>>4;
    uint8_t b1 = (b&0xF0U)>>4;
    
    uint8_t lo = (a0*b0)&0xFF;
    uint8_t hi = (a1*b1)&0xFF;
    uint8_t ma = (a1*b0)&0xFF;
    uint8_t mb = (a0*b1)&0xFF;
    
    uint8_t carry = ( (ma&0xF)+(mb&0xF)+(lo>>4))>>4;
    
    return (hi+(ma>>4)+(mb>>4)+carry)&0xFF;
}

struct u16{
    uint8_t x1,x0;
    
    friend u16 operator + (u16 a, u16 b){
        u16 c{};
        
        c.x0 = a.x0+b.x0;
        c.x1 = a.x1+b.x1;
        
        // overflow low to high
        if (c.x0 < a.x0)
            c.x1++;
        
        return c;
    }
    
    friend u16 operator * (u16 a, u16 b){
        u16 c{};
        
        uint8_t a0 = a.x0;
        uint8_t b0 = b.x0;
        uint8_t a1 = a.x1;
        uint8_t b1 = b.x1;
        
        u16 lo = {mul8_hi(a0,b0),uint8_t(a0*b0)};
        u16 ma = {uint8_t(a1*b0),0};
        u16 mb = {uint8_t(a0*b1),0};
        
        c = lo+ma+mb;
        
        return c;
    }
};

int main(){
    /*
    uint8_t a = 0x0B, b = 0xDA;
    
    uint16_t res = a*b;
    uint8_t lo = a*b;
    uint8_t hi = mul8_hi(a,b);
    
    std::cout << std::hex << int(a) << "*" << int(b) << " = ";
    std::cout << std::hex << res << ":";
    std::cout << std::hex << int(hi) << "'" << int(lo) << "\n";
    
    return 0;//*/
    
    /*
    
    uint16_t huh = uint16_t( uint64_t(0xFFFF)*uint64_t(0xFFFF) );
    int bad_count = 0;
    for(uint32_t x = 0; x <= 0xFFFF; x++){
        for(uint32_t y = 0; y <= 0xFFFF; y++){
            
            uint16_t a = x, b = y;
            
            u16 A{uint8_t(a>>8),uint8_t(a)},B{uint8_t(b>>8),uint8_t(b)};
            uint16_t c = uint64_t(a)*uint64_t(b);
            u16 C = A*B;
            
            uint16_t myC = (uint16_t(C.x1)<<8)|C.x0;
            
            if(c!=myC) bad_count++;
        }
        if( (x%0x0800)==0 ) std::cout << std::hex << "progress: " << bad_count << " failures so far.\n";
    }
    
    std::cout << "bad count:" << bad_count << "\n";//*/
    
    //*
    //u128 a{0xFFFF'FFFF'FFFF'FFFF,0xFFFF'FFFF'FFFF'FFFF},b{0xFFFF'FFFF'FFFF'FFFF,0xFFFF'FFFF'FFFF'FFFF},c{0,0};
    //u128 a{0,0},b{0,0},c{0,0};
    u128 a{0xFFFF'FFFF'FFFF'FFFF,0xFFFF'AAAA'AAAA'AAAA},b{0xFFFF'FFFF'FFFF'FFFF,0xFFFFFFFFFFFF7},c{0,0};
    c = a*b;
    
    std::cout << std::hex << "0x" << std::setw(16) << std::setfill('0') << a.x1 << "'"  << std::setw(16) << std::setfill('0')<< a.x0 << "\n";
    std::cout << std::hex << "0x" << std::setw(16) << std::setfill('0') << b.x1 << "'"  << std::setw(16) << std::setfill('0')<< b.x0 << "\n";
    std::cout << std::hex << "0x" << std::setw(16) << std::setfill('0') << c.x1 << "'"  << std::setw(16) << std::setfill('0')<< c.x0 << "\n";//*/
    /* terrible constants, lol. I'll search for better ones later.
    LCG<{0,5},{0,1}> my_first_lcg;
    for( int i = 0; i < 55; i++){
        std::cout << std::hex << "0x" << std::setw(16) << std::setfill('0') << my_first_lcg.next() << "\n";
        std::cout << std::hex << "0x" << std::setw(16) << std::setfill('0') << my_first_lcg.state.x1 << "'"  << std::setw(16) << std::setfill('0')<< my_first_lcg.state.x0 << "\n";
    }//*/
    
}

