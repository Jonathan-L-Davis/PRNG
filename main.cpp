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
    
    LCG<{0x2360'ED05'1FC6'5DA4,0x4385'DF64'9FCB'5CED},{0,1}> my_first_lcg{0,0};
    for( int i = 0; i < 55; i++){
        std::cout << std::hex << "0x" << std::setw(16) << std::setfill('0') << my_first_lcg.next() << "\n";
    }//*/
    
}

