#include <iostream>
#include <iomanip>
#include "u128.h"
#include "LCG.h"

int main(){
    /*
    u128 a{0xFFFF'FFFF'FFFF'FFFF,0xFFFF'FFFF'FFFF'FFFF},b{0xFFFF'FFFF'FFFF'FFFF,0xFFFF'FFFF'FFFF'FFFF},c{};
    c = a*b;
    
    std::cout << std::hex << "0x" << std::setw(16) << std::setfill('0') << c.x1 << "'"  << std::setw(16) << std::setfill('0')<< c.x0 << "\n";//*/
    // terrible constants, lol. I'll search for better ones later.
    LCG<{0,5},{0,1}> my_first_lcg;
    for( int i = 0; i < 55; i++){
        std::cout << std::hex << "0x" << std::setw(16) << std::setfill('0') << my_first_lcg.next() << "\n";
        std::cout << std::hex << "0x" << std::setw(16) << std::setfill('0') << my_first_lcg.state.x1 << "'"  << std::setw(16) << std::setfill('0')<< my_first_lcg.state.x0 << "\n";
    }
    
}

