#pragma once

#include "LCG.h"

struct PCG_r{
    LCG<{0x2360'ED05'1FC6'5DA4,0x4385'DF64'9FCB'5CED},{0,1}> inner_LCG;
}

