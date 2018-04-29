//
//  client.cpp
//  EZBS_Praktikum_2
//
//  Created by Maximilian B. on 24.04.18.
//  Copyright © 2018 Maximilian B. All rights reserved.
//

#include <iostream>
#include <boost/interprocess/ipc/message_queue.hpp>
#include "CalcMsg.hpp"
#include "client.hpp"


using namespace boost::interprocess;

std::mutex ex;

void MsgClient::createClient(MsgTyp msgTyp, int operandsCount) {
    
    std::cout << "Starting client..." << std::endl;
    
    try {
        
        // Open existing queues
        message_queue queue_send(open_only, QUEUE_SEND);
        message_queue queue_recieve(open_only, QUEUE_RECIEVE);
        
        
        responseMsgProtocol resP;
        message_queue::size_type recvd_size;
        unsigned int priority = 0;
        
        
        requestMsgProtocol reqP;
        reqP.msgTyp = msgTyp;
        reqP.number = std::rand() % INT_MAX;
        reqP.operandsCount = operandsCount;
        
        std::cout << std::endl;
        std::cout << "Sending request (->):" << std::endl;
        std::cout << "** Service: " << reqP.msgTyp << std::endl;
        std::cout << "** Nr.: " << reqP.number << std::endl;
        std::cout << "** Operands: " <<reqP.operandsCount << std::endl;
        
        for(int i=0; i < reqP.operandsCount; i++) {
            reqP.operands[i] = std::rand() % 16 + 1;
            std::cout << "** Operand: " << reqP.operands[i] << std::endl;
        }
        
        ex.lock();
        
        queue_send.send(&reqP, sizeof(reqP), priority);
        
        queue_recieve.receive(&resP, sizeof(resP), recvd_size, priority);
        
        ex.unlock();
        
        if(recvd_size != sizeof(resP)) {
            std::cout << "Error: recieved size not equal to actual size!" << std::endl;
        } else {
            std::cout << std::endl;
            std::cout << "Recieved server response (<-):" << std::endl;
            std::cout << "** Nr.: " << resP.number << std::endl;
            std::cout << "** Result: " << resP.result << std::endl;
        }
        
    } catch (interprocess_exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    
}

MsgClient::MsgClient(MsgTyp msgTyp, int operandsCount) {
    
    MsgClient::createClient(msgTyp, operandsCount);
    
}
