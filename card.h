#ifndef CARD_H
#define CARD_H

#include <ostream>
#include <string>

class Card {
public:
    Card();
    Card(char suit, int value);

    char getSuit() const;
    int getValue() const;

    bool operator==(const Card& other) const;
    bool operator<(const Card& other) const;
    bool operator>(const Card& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Card& card);

    static Card parse(const std::string& line);

private:
    char suit;
    int value;

    static int suitOrder(char s);
};

#endif
