#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
class State
{
    private:
        int* s;
        int total;
    public:
    State(
        int* s,
        int total
    ) : s(s), total(total){}

    int getTotal() const{
        return total;
    }

    int* getStates() const{
        return s;
    } 

    string getString() {
        string a;
        for (int i =0; i< total; i++) {
            a += to_string(i) + ":" + to_string(s[i]) + "\n";
        }
        return a;
    }

    void setState(int i, int v) const{
        s[i] = v;
    } 

    State* copy() {
        int *copyS = new int[total];
        std::copy(s, s+total, copyS);
        return new State(copyS, total);
    }

};  

bool operator==(const State lS, const State rS){
    if(lS.getTotal() != rS.getTotal()) {
        return false;
    }
    for(int i = 0; i< rS.getTotal(); i++) {
        if (lS.getStates()[i] != rS.getStates()[i]) {
            return false;
        }
    }
    return true;
}