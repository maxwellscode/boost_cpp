//
//  server.hpp
//  EZBS_Praktikum_2
//
//  Created by Maximilian B. on 24.04.18.
//  Copyright © 2018 Maximilian B. All rights reserved.
//

#ifndef server_h
#define server_h

class MsgServer {
    
    float add(float * operands, int size);
    float mult(float * operands, int size);
    void createServer(int maxCycle);
    void deleteQueues();
    
public:
    
    MsgServer(int maxCycle);
    ~MsgServer();
    
};

#endif /* server_h */
