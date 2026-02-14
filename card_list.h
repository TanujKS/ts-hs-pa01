// card_list.h
// Author: Tanuj Siripurapu & Hursh Shah
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
#include <ostream>

class CardBST {
private:
    struct Node {
        Card card;
        Node* left;
        Node* right;
        Node* parent;
        Node(const Card& c) : card(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };

public:
    class Iterator;

    CardBST();
    CardBST(const CardBST& other);
    CardBST& operator=(const CardBST& other);
    ~CardBST();

    void insert(const Card& card);
    void remove(const Card& card);
    bool contains(const Card& card) const;

    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;

    void printInOrder(std::ostream& os) const;
    bool empty() const;

    class Iterator {
    public:
        Iterator();
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);

        const Card& operator*() const;
        const Card* operator->() const;

        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Node* current;
        const CardBST* tree;
        bool isEnd;
        bool isReverseEnd;

        Iterator(Node* n, const CardBST* t, bool endFlag = false, bool reverseEndFlag = false);
        Node* findSuccessor(Node* node) const;
        Node* findPredecessor(Node* node) const;

        friend class CardBST;
    };

private:
    Node* root;

    Node* insertHelper(Node* node, Node* parent, const Card& card);
    Node* removeHelper(Node* node, const Card& card);
    Node* findMinNode(Node* node) const;
    Node* findNode(Node* node, const Card& card) const;
    Node* getLeftmost(Node* node) const;
    Node* getRightmost(Node* node) const;
    void printInOrderHelper(std::ostream& os, Node* node) const;
    void clear(Node* node);
    Node* copyTree(Node* node, Node* parent) const;

    friend class Iterator;
};

void playGame(CardBST& aliceHand, CardBST& bobHand);

#endif
