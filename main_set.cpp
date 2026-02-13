#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argv[1]);
    ifstream cardFile2(argv[2]);
    string line;

    if (cardFile1.fail() || cardFile2.fail()) {
        cout << "Could not open file " << argv[2];
        return 1;
    }

    set<Card> aliceHand;
    set<Card> bobHand;

    while (getline(cardFile1, line) && line.length() > 0) {
        aliceHand.insert(Card::parse(line));
    }
    cardFile1.close();

    while (getline(cardFile2, line) && line.length() > 0) {
        bobHand.insert(Card::parse(line));
    }
    cardFile2.close();

    bool foundMatch = true;
    while (foundMatch) {
        foundMatch = false;

        for (auto it = aliceHand.begin(); it != aliceHand.end(); ++it) {
            if (bobHand.count(*it) > 0) {
                cout << "Alice picked matching card " << *it << endl;
                bobHand.erase(*it);
                aliceHand.erase(it);
                foundMatch = true;
                break;
            }
        }

        if (!foundMatch) break;

        foundMatch = false;
        for (auto it = bobHand.rbegin(); it != bobHand.rend(); ++it) {
            if (aliceHand.count(*it) > 0) {
                cout << "Bob picked matching card " << *it << endl;
                Card cardToRemove = *it;
                aliceHand.erase(cardToRemove);
                bobHand.erase(cardToRemove);
                foundMatch = true;
                break;
            }
        }
    }

    cout << endl;
    cout << "Alice's cards:" << endl;
    for (const Card& card : aliceHand) {
        cout << card << endl;
    }
    cout << endl;
    cout << "Bob's cards:" << endl;
    for (const Card& card : bobHand) {
        cout << card << endl;
    }

    return 0;
}
