//
//  server.cpp
//  EZBS_Praktikum_2
//
//  Created by Maximilian B. on 24.04.18.
//  Copyright © 2018 Maximilian B. All rights reserved.
//

#include <iostream>
#include <boost/interprocess/ipc/message_queue.hpp>
#include "CalcMsg.hpp"
#include "server.hpp"


using namespace boost::interprocess;


// ADD service
float MsgServer::add(float * operands, int size) {
    float res = 0.0;
    
    for(int i=0; i<size; i++) {
        res += operands[i];
    }
    return res;
}

// MULT service
float MsgServer::mult(float * operands, int size) {
    float res = 1.0;
    
    for(int i=0; i<size; i++) {
        res *= operands[i];
    }
    return res;
}

// Delete existing queues
void MsgServer::deleteQueues() {
    
    try {
        std::cout << "Removing existing queues" << std::endl;
        message_queue::remove(QUEUE_SEND);
        message_queue::remove(QUEUE_RECIEVE);
        
    } catch(interprocess_exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

// Create new Server
void MsgServer::createServer(int maxCycle) {
    
    std::cout << "Starting server..." << std::endl;
    
    // On Server startup clear existing queue's
    MsgServer::deleteQueues();
    
    try {
        
        // Create new queue's
        // Options: open_only, open_or_create, open_read_only
        std::cout << "Creating queues..." << std::endl;
        message_queue queue_send(create_only, QUEUE_SEND, 100, sizeof(requestMsgProtocol));
        message_queue queue_recieve(create_only, QUEUE_RECIEVE, 100, sizeof(responseMsgProtocol));
        
        unsigned int priority = 0;
        
        requestMsgProtocol reqMsg;
        message_queue::size_type recvd_size;
        
        
        for(int i=0; i<maxCycle; i++) {
            
            while(queue_send.try_receive(&reqMsg, sizeof(reqMsg), recvd_size, priority)) {
                
                if(recvd_size != sizeof(reqMsg)) {
                    
                    std::cout << "Error: recieved size not equal to actual size!" << std::endl;
                    
                } else {
                    
                    std::cout << std::endl;
                    std::cout << "Recieved new package (<-):" << std::endl;
                    std::cout << "** Service: " << reqMsg.msgTyp << std::endl;
                    std::cout << "** Nr.: " << reqMsg.number << std::endl;
                    std::cout << "** Operands Count: " << reqMsg.operandsCount << std::endl;
                    
                    for(int i=0; i < reqMsg.operandsCount; i++) {
                        std::cout << "** Operand: " << reqMsg.operands[i] << std::endl;
                    }
                    
                    
                    float res=0.0;
                    
                    switch (reqMsg.msgTyp) {

                        case ADD:
                            res = add(reqMsg.operands, reqMsg.operandsCount);
                            break;
                            
                        case MULT:
                            res = mult(reqMsg.operands, reqMsg.operandsCount);
                            break;
                            
                        case MSG_TYPE_END:
                            break;
                            
                        default:
                            continue;
                    }
                    
                    
                    // Respond to client
                    responseMsgProtocol resMsg;
                    resMsg.number = reqMsg.number;
                    resMsg.result = res;
                    
                    std::cout << std::endl;
                    std::cout << "Sending response (->):" << std::endl;
                    std::cout << "** Nr.: " << resMsg.number << std::endl;
                    std::cout << "** Result: " << resMsg.result << std::endl;
                    
                    queue_recieve.send(&resMsg, sizeof(resMsg), priority);
                    
                }
            }
            
            std::cout << "." << std::endl;
            sleep(1);
        }
        
    } catch(interprocess_exception& ex) {
        
        std::cout << ex.what() << std::endl;
        
        // Try to delete message queues
        MsgServer::deleteQueues();

    }
}

MsgServer::MsgServer(int maxCycle) {
    MsgServer::createServer(maxCycle);
}

MsgServer::~MsgServer() {
    MsgServer::deleteQueues();
}
