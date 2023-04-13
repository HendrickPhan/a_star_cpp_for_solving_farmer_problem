#include "node.hpp"
#include <vector>
#include <algorithm>

// state
const int LEFT_SIDE = 0;
const int RIGHT_SIDE = 1;

// state index
const int GOAT = 0;
const int WOLF = 1;
const int CABBAGE = 2;
const int FARMER = 3;

// ACTIONS
const string MOVE_GOAT_RIGHT = "MOVE_GOAT_RIGHT";
const string MOVE_GOAT_LEFT = "MOVE_GOAT_LEFT";
const string MOVE_WOLF_RIGHT = "MOVE_WOLF_RIGHT";
const string MOVE_WOLF_LEFT = "MOVE_WOLF_LEFT";
const string MOVE_CABBAGE_RIGHT = "MOVE_CABBAGE_RIGHT";
const string MOVE_CABBAGE_LEFT = "MOVE_CABBAGE_LEFT";
const string MOVE_FARMER_RIGHT = "MOVE_FARMER_RIGHT";
const string MOVE_FARMER_LEFT = "MOVE_FARMER_LEFT";

const int COST_BETWEEN_NODE = 1;

class Manage
{
public:
    Manage(){};

    Node* findBestPath(Node* initNode, Node* goalNodes)
    {
        // add initNode to open set
        std::vector<Node*> openNodeSet;
        std::vector<Node*> closeNodeSet;
        openNodeSet.push_back(initNode);
     
        while (openNodeSet.size() > 0)
        {
            int bestIdx = bestNodeIndex(openNodeSet);
            Node* bestNode = openNodeSet[bestIdx];
            // remove node from open set
            openNodeSet.erase(openNodeSet.begin() + bestIdx);
            // if equal goal then return path
            if (*bestNode == *goalNodes)
            {
                return bestNode;
            }

            // add bestNode to close and create new state
            closeNodeSet.push_back(bestNode);

            // execute actions
            Node *nodeMoveGoatRight = moveGoatRight(bestNode);
            addNodeToSets(nodeMoveGoatRight, openNodeSet, closeNodeSet);
            Node *nodeMoveGoatLeft = moveGoatLeft(bestNode);
            addNodeToSets(nodeMoveGoatLeft, openNodeSet, closeNodeSet);
            Node *nodeMoveWolfRight = moveWolfRight(bestNode);
            addNodeToSets(nodeMoveWolfRight, openNodeSet, closeNodeSet);
            Node *nodeMoveWolfLeft = moveWolfLeft(bestNode);
            addNodeToSets(nodeMoveWolfLeft, openNodeSet, closeNodeSet);
            Node *nodeMoveCabbageRight = moveCabbageRight(bestNode);
            addNodeToSets(nodeMoveCabbageRight, openNodeSet, closeNodeSet);
            Node *nodeMoveCabbageLeft = moveCabbageLeft(bestNode);
            addNodeToSets(nodeMoveCabbageLeft, openNodeSet, closeNodeSet);
            Node *nodeMoveFarmerRight = moveFarmerRight(bestNode);
            addNodeToSets(nodeMoveFarmerRight, openNodeSet, closeNodeSet);
            Node *nodeMoveFarmerLeft = moveFarmerLeft(bestNode);
            addNodeToSets(nodeMoveFarmerLeft, openNodeSet, closeNodeSet);
        }

        return NULL;
    }

    int bestNodeIndex(std::vector<Node*> openNodeSet)
    {
        int smalledF = openNodeSet[0]->getF();
        int bestIdx = 0;
        for (int i = 1; i < openNodeSet.size(); i++)
        {
            if (openNodeSet[i]->getF() < smalledF)
            {
                bestIdx = i;
                smalledF = openNodeSet[i]->getF();
            }
        }
        return bestIdx;
    }

    void addNodeToSets(Node *node, std::vector<Node*>& openNodeSet, std::vector<Node*>& closeNodeSet)
    {
        if (node == NULL)
        {
            return;
        }
     
        if (
            (std::find_if(
                closeNodeSet.begin(), 
                closeNodeSet.end(), 
                [node](Node *x){return *x == *node;}
            ) != closeNodeSet.end()) ||
            (std::find_if(openNodeSet.begin(), openNodeSet.end(), [node](Node *x){return *x == *node;}) != openNodeSet.end()))
        {
            return;
        }
        // add node to open set
        openNodeSet.push_back(node);
    }

    int calculateHeuristic(State *s)
    {
        // In here i'm calculating heuristic by sum of total state at right side
        // Example: only goat and farmer in right side then heuristic will be 2
        int heuristic = 0;
        for (int i = 0; i < s->getTotal(); i++)
        {
            if (s->getStates()[i] == RIGHT_SIDE)
            {
                heuristic++;
            }
        }
        return heuristic;
    };
    // checkers
    bool wolfEatGoat(State *s)
    {
        return s->getStates()[GOAT] == s->getStates()[WOLF] && // wolf and goat in same side
               s->getStates()[FARMER] != s->getStates()[GOAT]; // farmer not same side with wolf and goat
    }

    bool goatEatCabbage(State *s)
    {
        return s->getStates()[GOAT] == s->getStates()[CABBAGE] && // goat and cabbage in same side
               s->getStates()[FARMER] != s->getStates()[GOAT];    // farmer not same side with goat and cabbage
    }

    // actions
    Node *createNode(Node *node, State *newState, string action)
    {
        if (this->goatEatCabbage(newState) || this->wolfEatGoat(newState))
        {
            return NULL;
        }
        return new Node(
            action,
            node->getG() + COST_BETWEEN_NODE,
            this->calculateHeuristic(newState),
            newState,
            node);
    }

    //
    Node *moveGoatRight(Node *node)
    {
        State *s = node->getState();
        // require farmer in left to move goat to right
        if (s->getStates()[FARMER] == RIGHT_SIDE || s->getStates()[GOAT] == RIGHT_SIDE)
        {
            return NULL;
        }
        State *newState = s->copy();
        newState->setState(GOAT, RIGHT_SIDE);
        newState->setState(FARMER, RIGHT_SIDE);
        // require wolf not eat goat and goat not eat cabbage
        return createNode(node, newState, MOVE_GOAT_RIGHT);
    }

    Node *moveGoatLeft(Node *node)
    {
        State *s = node->getState();
        // require farmer in left to move goat to right
        if (s->getStates()[FARMER] == LEFT_SIDE || s->getStates()[GOAT] == LEFT_SIDE)
        {
            return NULL;
        }
        State *newState = s->copy();
        newState->setState(GOAT, LEFT_SIDE);
        newState->setState(FARMER, LEFT_SIDE);
        // require wolf not eat goat and goat not eat cabbage
        return createNode(node, newState, MOVE_GOAT_LEFT);
    }

    Node *moveWolfRight(Node *node)
    {
        State *s = node->getState();
        // require farmer in left to move goat to right
        if (s->getStates()[FARMER] == RIGHT_SIDE || s->getStates()[WOLF] == RIGHT_SIDE)
        {
            return NULL;
        }
        State *newState = s->copy();
        newState->setState(WOLF, RIGHT_SIDE);
        newState->setState(FARMER, RIGHT_SIDE);
        return createNode(node, newState, MOVE_WOLF_RIGHT);
    }

    Node *moveWolfLeft(Node *node)
    {
        State *s = node->getState();
        // require farmer in left to move goat to right
        if (s->getStates()[FARMER] == LEFT_SIDE || s->getStates()[WOLF] == LEFT_SIDE)
        {
            return NULL;
        }
        State *newState = s->copy();
        newState->setState(WOLF, LEFT_SIDE);
        newState->setState(FARMER, LEFT_SIDE);
        return createNode(node, newState, MOVE_WOLF_LEFT);
    }

    Node *moveCabbageRight(Node *node)
    {
        State *s = node->getState();
        // require farmer in left to move goat to right
        if (s->getStates()[FARMER] == RIGHT_SIDE || s->getStates()[CABBAGE] == RIGHT_SIDE)
        {
            return NULL;
        }
        State *newState = s->copy();
        newState->setState(CABBAGE, RIGHT_SIDE);
        newState->setState(FARMER, RIGHT_SIDE);
        // require wolf not eat goat and goat not eat cabbage
        return createNode(node, newState, MOVE_CABBAGE_RIGHT);
    }

    Node *moveCabbageLeft(Node *node)
    {
        State *s = node->getState();
        // require farmer in left to move goat to right
        if (s->getStates()[FARMER] == LEFT_SIDE || s->getStates()[CABBAGE] == LEFT_SIDE)
        {
            return NULL;
        }
        State *newState = s->copy();
        newState->setState(CABBAGE, LEFT_SIDE);
        newState->setState(FARMER, LEFT_SIDE);
        // require wolf not eat goat and goat not eat cabbage
        return createNode(node, newState, MOVE_CABBAGE_LEFT);
    }

    Node *moveFarmerRight(Node *node)
    {
        State *s = node->getState();
        // require farmer in left to move goat to right
        if (s->getStates()[FARMER] == RIGHT_SIDE )
        {
            return NULL;
        }
        State *newState = s->copy();
        newState->setState(FARMER, RIGHT_SIDE);
        // require wolf not eat goat and goat not eat cabbage
        return createNode(node, newState, MOVE_FARMER_RIGHT);
    }

    Node *moveFarmerLeft(Node *node)
    {
        State *s = node->getState();
        // require farmer in left to move goat to right
        if (s->getStates()[FARMER] == LEFT_SIDE )
        {
            return NULL;
        }
        State *newState = s->copy();
        newState->setState(FARMER, LEFT_SIDE);
        // require wolf not eat goat and goat not eat cabbage
        return createNode(node, newState, MOVE_FARMER_LEFT);
    }

    string formatedStateString(State *state) {
        string a;
        a += "Goat: ";
        a += ((state->getStates()[0] == 0) ? "Left": "Right");
        a += "\n";

        a += "Wolf: ";
        a += ((state->getStates()[1] == 0) ? "Left": "Right");
        a += "\n";

        a += "Cabbage: ";
        a += ((state->getStates()[2] == 0) ? "Left": "Right");
        a += "\n";


        a += "Farmer: "; 
        a += ((state->getStates()[3] == 0) ? "Left": "Right");
        a += "\n";
       
        return a;
    }
};