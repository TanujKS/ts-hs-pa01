// card_list.cpp
// Author: Tanuj Siripurapu & Hursh Shah
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include <iostream>

CardBST::CardBST() : root(nullptr) {}

CardBST::CardBST(const CardBST& other) : root(nullptr) {
    if (other.root) {
        root = copyTree(other.root, nullptr);
    }
}

CardBST& CardBST::operator=(const CardBST& other) {
    if (this != &other) {
        clear(root);
        root = nullptr;
        if (other.root) {
            root = copyTree(other.root, nullptr);
        }
    }
    return *this;
}

CardBST::~CardBST() {
    clear(root);
}

CardBST::Node* CardBST::copyTree(Node* node, Node* parent) const {
    if (!node) return nullptr;
    Node* newNode = new Node(node->card);
    newNode->parent = parent;
    newNode->left = copyTree(node->left, newNode);
    newNode->right = copyTree(node->right, newNode);
    return newNode;
}

void CardBST::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void CardBST::insert(const Card& card) {
    root = insertHelper(root, nullptr, card);
}

CardBST::Node* CardBST::insertHelper(Node* node, Node* parent, const Card& card) {
    if (!node) {
        Node* newNode = new Node(card);
        newNode->parent = parent;
        return newNode;
    }
    if (card < node->card) {
        node->left = insertHelper(node->left, node, card);
    } else if (card > node->card) {
        node->right = insertHelper(node->right, node, card);
    }
    return node;
}

void CardBST::remove(const Card& card) {
    root = removeHelper(root, card);
}

CardBST::Node* CardBST::removeHelper(Node* node, const Card& card) {
    if (!node) return nullptr;
    if (card < node->card) {
        node->left = removeHelper(node->left, card);
    } else if (card > node->card) {
        node->right = removeHelper(node->right, card);
    } else {
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }
        if (!node->left) {
            Node* rightChild = node->right;
            rightChild->parent = node->parent;
            delete node;
            return rightChild;
        }
        if (!node->right) {
            Node* leftChild = node->left;
            leftChild->parent = node->parent;
            delete node;
            return leftChild;
        }
        Node* minRight = findMinNode(node->right);
        node->card = minRight->card;
        node->right = removeHelper(node->right, minRight->card);
    }
    return node;
}

CardBST::Node* CardBST::findMinNode(Node* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

bool CardBST::contains(const Card& card) const {
    return findNode(root, card) != nullptr;
}

CardBST::Node* CardBST::findNode(Node* node, const Card& card) const {
    if (!node) return nullptr;
    if (card == node->card) return node;
    if (card < node->card) return findNode(node->left, card);
    return findNode(node->right, card);
}

void CardBST::printInOrder(std::ostream& os) const {
    printInOrderHelper(os, root);
}

void CardBST::printInOrderHelper(std::ostream& os, Node* node) const {
    if (!node) return;
    printInOrderHelper(os, node->left);
    os << node->card << std::endl;
    printInOrderHelper(os, node->right);
}

bool CardBST::empty() const {
    return root == nullptr;
}

CardBST::Node* CardBST::getLeftmost(Node* node) const {
    if (!node) return nullptr;
    while (node->left) node = node->left;
    return node;
}

CardBST::Node* CardBST::getRightmost(Node* node) const {
    if (!node) return nullptr;
    while (node->right) node = node->right;
    return node;
}

CardBST::Iterator CardBST::begin() const {
    if (!root) return Iterator(nullptr, this, true, false);
    return Iterator(getLeftmost(root), this);
}

CardBST::Iterator CardBST::end() const {
    return Iterator(nullptr, this, true, false);
}

CardBST::Iterator CardBST::rbegin() const {
    if (!root) return Iterator(nullptr, this, false, true);
    return Iterator(getRightmost(root), this, false, false);
}

CardBST::Iterator CardBST::rend() const {
    return Iterator(nullptr, this, false, true);
}

CardBST::Iterator::Iterator() : current(nullptr), tree(nullptr), isEnd(true), isReverseEnd(false) {}

CardBST::Iterator::Iterator(Node* n, const CardBST* t, bool endFlag, bool reverseEndFlag)
    : current(n), tree(t), isEnd(endFlag), isReverseEnd(reverseEndFlag) {}

CardBST::Iterator::Iterator(const Iterator& other)
    : current(other.current), tree(other.tree), isEnd(other.isEnd), isReverseEnd(other.isReverseEnd) {}

CardBST::Iterator& CardBST::Iterator::operator=(const Iterator& other) {
    current = other.current;
    tree = other.tree;
    isEnd = other.isEnd;
    isReverseEnd = other.isReverseEnd;
    return *this;
}

const Card& CardBST::Iterator::operator*() const {
    if (isEnd || isReverseEnd) {
        static Card dummy('c', 1);
        return dummy;
    }
    return current->card;
}

const Card* CardBST::Iterator::operator->() const {
    return &operator*();
}

CardBST::Node* CardBST::Iterator::findSuccessor(Node* node) const {
    if (!node) return nullptr;
    if (node->right) return tree->getLeftmost(node->right);
    Node* p = node->parent;
    while (p && node == p->right) {
        node = p;
        p = p->parent;
    }
    return p;
}

CardBST::Node* CardBST::Iterator::findPredecessor(Node* node) const {
    if (!node) return nullptr;
    if (node->left) return tree->getRightmost(node->left);
    Node* p = node->parent;
    while (p && node == p->left) {
        node = p;
        p = p->parent;
    }
    return p;
}

CardBST::Iterator& CardBST::Iterator::operator++() {
    if (isReverseEnd) {
        if (tree && tree->root) {
            current = tree->getLeftmost(tree->root);
            isReverseEnd = false;
        }
        return *this;
    }
    if (isEnd) return *this;
    if (current) {
        Node* next = findSuccessor(current);
        if (next) {
            current = next;
        } else {
            current = nullptr;
            isEnd = true;
        }
    }
    return *this;
}

CardBST::Iterator CardBST::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

CardBST::Iterator& CardBST::Iterator::operator--() {
    if (isEnd) {
        if (tree && tree->root) {
            current = tree->getRightmost(tree->root);
            isEnd = false;
        }
        return *this;
    }
    if (isReverseEnd) return *this;
    if (current) {
        Node* prev = findPredecessor(current);
        if (prev) {
            current = prev;
        } else {
            current = nullptr;
            isReverseEnd = true;
        }
    }
    return *this;
}

CardBST::Iterator CardBST::Iterator::operator--(int) {
    Iterator tmp = *this;
    --(*this);
    return tmp;
}

bool CardBST::Iterator::operator==(const Iterator& other) const {
    if (isEnd && other.isEnd) return true;
    if (isReverseEnd && other.isReverseEnd) return true;
    return current == other.current && isEnd == other.isEnd && isReverseEnd == other.isReverseEnd;
}

bool CardBST::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

void playGame(CardBST& aliceHand, CardBST& bobHand) {
    bool foundMatch = true;
    while (foundMatch) {
        foundMatch = false;

        for (auto it = aliceHand.begin(); it != aliceHand.end(); ++it) {
            if (bobHand.contains(*it)) {
                std::cout << "Alice picked matching card " << *it << std::endl;
                Card cardToRemove = *it;
                bobHand.remove(cardToRemove);
                aliceHand.remove(cardToRemove);
                foundMatch = true;
                break;
            }
        }

        if (!foundMatch) break;

        foundMatch = false;
        for (auto it = bobHand.rbegin(); it != bobHand.rend(); --it) {
            if (aliceHand.contains(*it)) {
                std::cout << "Bob picked matching card " << *it << std::endl;
                Card cardToRemove = *it;
                aliceHand.remove(cardToRemove);
                bobHand.remove(cardToRemove);
                foundMatch = true;
                break;
            }
        }
    }

    std::cout << std::endl;
    std::cout << "Alice's cards:" << std::endl;
    for (auto it = aliceHand.begin(); it != aliceHand.end(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Bob's cards:" << std::endl;
    for (auto it = bobHand.begin(); it != bobHand.end(); ++it) {
        std::cout << *it << std::endl;
    }
}
