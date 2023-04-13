#include <fstream>
#include <iostream>
#include "include/manage.hpp"

using namespace std;

int main()
{
    // Print standard output
    Manage *manage = new Manage();
    int totalState = 4;
    cout << "0 is left, 1 is right." << endl;
    int gS;
    int wS;
    int cS;
    int fS;

    int gGS;
    int wGS;
    int cGS;
    int fGS;

    cout << "Enter start Goat side" << endl;
    cin >> gS;
    cout << "Enter start Wolf side" << endl;
    cin >> wS;
    cout << "Enter start Cabbage side" << endl;
    cin >> cS;
    cout << "Enter start Farmer side" << endl;
    cin >> fS;

    cout << "Enter goal Goat side" << endl;
    cin >> gGS;
    cout << "Enter goal Wolf side" << endl;
    cin >> wGS;
    cout << "Enter goal Cabbage side" << endl;
    cin >> cGS;
    cout << "Enter goal Farmer side" << endl;
    cin >> fGS;


    int initState[] = {gS, wS, cS, fS};
    int goalState[] = {gGS, wGS, cGS, fGS};

    Node *initNode = new Node(
        "Start",
        0,
        0,
        new State(initState, totalState),
        NULL
    );
    Node *goalNode = new Node(
        "Goal",
        0,
        0,
        new State(goalState, totalState),
        NULL
    );

    vector<Node*> path;
    Node *goalWithPath = manage->findBestPath(initNode, goalNode);
   
    if (goalWithPath == NULL) {
        cout << "No path found!"<< endl;
    } else {
        
        while (goalWithPath != NULL) {
            path.push_back(goalWithPath);
            // 
            goalWithPath = goalWithPath->getP();
        }

        cout << "Best Path is: "<< endl;
        reverse(path.begin(), path.end());
        for (int i =0; i< path.size(); i++) {
            cout << i << ". " << path[i]->getA() << " State: " << endl 
            << manage->formatedStateString(path[i]->getState()) << endl;
        }
    }
    
    return 0;
}