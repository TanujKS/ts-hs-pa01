// card.cpp
// Author: Tanuj Siripurapu & Hursh Shah
// Implementation of the classes defined in card.h

#include "card.h"
#include <ostream>
#include <sstream>

Card::Card() : suit('c'), value(1) {}

Card::Card(char suit, int value) : suit(suit), value(value) {}

char Card::getSuit() const {
    return suit;
}

int Card::getValue() const {
    return value;
}

int Card::suitOrder(char s) {
    if (s == 'c') return 0;
    if (s == 'd') return 1;
    if (s == 's') return 2;
    if (s == 'h') return 3;
    return -1;
}

bool Card::operator==(const Card& other) const {
    return suit == other.suit && value == other.value;
}

bool Card::operator<(const Card& other) const {
    int mySuitOrder = suitOrder(suit);
    int otherSuitOrder = suitOrder(other.suit);
    if (mySuitOrder != otherSuitOrder) {
        return mySuitOrder < otherSuitOrder;
    }
    return value < other.value;
}

bool Card::operator>(const Card& other) const {
    return other < *this;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.suit << " ";
    if (card.value == 1) {
        os << "a";
    }
    else if (card.value == 11) {
        os << "j";
    }
    else if (card.value == 12) {
        os << "q";
    }
    else if (card.value == 13) {
        os << "k";
    }
    else {
        os << card.value;
    }
    return os;
}

Card Card::parse(const std::string& line) {
    if (line.empty()) return Card('c', 1);
    char suit = line[0];
    std::string valueStr = line.substr(2);
    int value;
    if (valueStr == "a") value = 1;
    else if (valueStr == "j") {
        value = 11;
    }
    else if (valueStr == "q") {
        value = 12;
    }
    else if (valueStr == "k") {
        value = 13;
    }
    else value = std::stoi(valueStr);
    return Card(suit, value);
}
