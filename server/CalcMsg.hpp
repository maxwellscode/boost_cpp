//
//  CalcMsg.hpp
//  EZBS_Praktikum_2
//
//  Created by Maximilian B. on 24.04.18.
//  Copyright © 2018 Maximilian B. All rights reserved.
//

#ifndef CalcMsg_h
#define CalcMsg_h

#define QUEUE_SEND "queue_send"
#define QUEUE_RECIEVE "queue_recieve"
#define MAX_OPERANDS 100

enum MsgTyp {
    ADD,
    MULT,
    MSG_TYPE_END
};

struct requestMsgProtocol {
    MsgTyp msgTyp;
    int number;
    int operandsCount;
    float operands [MAX_OPERANDS];
};

struct responseMsgProtocol {
    int number;
    float result;
};


#endif /* CalcMsg_h */
