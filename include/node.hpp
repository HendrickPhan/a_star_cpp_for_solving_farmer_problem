#include <iostream>
#include "state.hpp"

using namespace std;

class Node
{
    private:
        int i; // index of this node
        string a; // action to create this node
        int g; // cost from start to this node
        int h; // heuristic cost from this node to goal
        State* s; 
        Node* p; // parent node

    public:
    static int index;

    Node(
        string a,
        int g,
        int h,
        State* s,
        Node* p
    ) : 
        a(a),
        g(g),
        h(h),
        s(s),
        p(p)
    {
        i = index;
        index++;
    }
    
    int getI() const{
        return i;
    }
    
    int getG() const{
        return g;
    }
    
    int getH() const{
        return h;
    }

    int getF() const{
        return g + h;
    }

    string getA() const{
        return a;
    }
    
    Node* getP() const{
        return p;
    }
    
    State* getState() const{
        return s;
    }
};  
int Node::index = 0;

bool operator==(const Node lN, const Node rN) {
   return *lN.getState() == *rN.getState();
}