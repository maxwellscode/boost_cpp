//
//  client.hpp
//  EZBS_Praktikum_2
//
//  Created by Maximilian B. on 24.04.18.
//  Copyright © 2018 Maximilian B. All rights reserved.
//

#ifndef client_h
#define client_h


class MsgClient {
    
    void createClient(MsgTyp msgTyp, int operandsCount);
    
public:
    
    MsgClient(MsgTyp msgTyp, int operandsCount);
    ~MsgClient();
    
};

#endif /* client_h */
