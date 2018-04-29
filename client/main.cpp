//
//  main.cpp
//  EZBS_Praktikum_2_1
//
//  Created by Maximilian B. on 24.04.18.
//  Copyright © 2018 Maximilian B. All rights reserved.
//

#include <iostream>
#include "CalcMsg.hpp"
#include "client.hpp"

int main(int argc, const char * argv[]) {
    
    
    MsgClient client1(ADD, 3);
    
    MsgClient client2(MULT, 2);
    
    return 0;
}
