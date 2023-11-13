#ifndef OPERATIONS_CPP
#define OPERATIONS_CPP
#include "BankAcc.cpp"
#include <vector>


class Operations {
private:
    static const int MAX = 2;
    BankAcc* bankAcc;
    std::vector<float> operations;
    std::vector<float> retryOperations;

    void Retry(){
        for (int  i = 0; i < MAX; ++i) {
            if (!retryOperations.empty()) {
                for(int j = 0; j < retryOperations.size(); ++j){
                    if (bankAcc -> getScore() + retryOperations[j] >= 0) {
                        bankAcc -> change(retryOperations.front());
                        retryOperations.erase(retryOperations.begin() + j);
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    }
                }
            }
            else
                break;
        }

    }

public:
    Operations(std::vector<float> &scenes, BankAcc *bankAcc) : operations{scenes}, bankAcc{bankAcc}, retryOperations{} {}
    
    void startOperations(){
        for (auto operation : operations) {
            if (bankAcc -> getScore() + operation >= 0) {
                bankAcc -> change(operation);
            }
            else {
                retryOperations.push_back(operation);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        Retry();
    }
};


#endif//OPERATIONS_CPP


