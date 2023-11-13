#ifndef BANKACC_CPP
#define BANKACC_CPP
#include <iostream>
#include <mutex>
#include <thread>


class BankAcc {
private:
    float score;
    std::mutex mtx;

public:
    BankAcc(){
        score = 0;
    }

    BankAcc(float initialScore)
    {
        this->score = initialScore;
    }
    
    void change(float operation)
    {
        std::lock_guard<std::mutex> mtxGuard(mtx);
        std::cout << "Processing...\n";
        float before = this -> score;
        this->score += operation;
        float after = this -> score;
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
        std::string info = "On the account before the operation: " + std::to_string(before) + ", operation: " + std::to_string(operation) + ", after operation: " + std::to_string(after) + ".\n";
        std::cout << info;
    
    }

    float getScore(){
        std::lock_guard<std::mutex> mtxGuard(mtx);
        return score;
    }
};

#endif//BANKACC_CPP
