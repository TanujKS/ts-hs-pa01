#include "card.h"
#include "card_list.h"
#include <cassert>
#include <sstream>
#include <iostream>

void testInsert1() {
    CardBST tree;
    assert(tree.empty());
    tree.insert(Card('c', 1));
    assert(!tree.empty());
    assert(tree.contains(Card('c', 1)));
}

void testInsert2() {
    CardBST tree;
    tree.insert(Card('h', 10));
    assert(tree.contains(Card('h', 10)));
}

void testInsert3() {
    CardBST tree;
    tree.insert(Card('c', 3));
    tree.insert(Card('c', 1));
    tree.insert(Card('h', 10));
    assert(tree.contains(Card('c', 1)));
    assert(tree.contains(Card('c', 3)));
    assert(tree.contains(Card('h', 10)));
}

void testInsert4() {
    CardBST tree;
    tree.insert(Card('c', 5));
    tree.insert(Card('c', 5));
    assert(tree.contains(Card('c', 5)));
}

void testInsert5() {
    CardBST tree;
    for (int i = 1; i <= 13; i++) {
        tree.insert(Card('c', i));
    }
    for (int i = 1; i <= 13; i++) {
        tree.remove(Card('c', i));
    }
    assert(tree.empty());
}

void testRemove1() {
    CardBST tree;
    tree.remove(Card('c', 1));
    assert(tree.empty());
}

void testRemove2() {
    CardBST tree;
    tree.insert(Card('d', 7));
    tree.remove(Card('d', 7));
    assert(!tree.contains(Card('d', 7)));
    assert(tree.empty());
}

void testRemove3() {
    CardBST tree;
    tree.insert(Card('c', 1));
    tree.insert(Card('c', 13));
    tree.insert(Card('h', 5));
    tree.remove(Card('c', 13));
    assert(tree.contains(Card('c', 1)));
    assert(!tree.contains(Card('c', 13)));
}

void testRemove4() {
    CardBST tree;
    tree.insert(Card('s', 2));
    tree.remove(Card('s', 3));
    assert(tree.contains(Card('s', 2)));
}

void testRemove5() {
    CardBST tree;
    tree.insert(Card('c', 5));
    tree.insert(Card('c', 2));
    tree.insert(Card('c', 8));
    tree.remove(Card('c', 5));
    assert(!tree.contains(Card('c', 5)));
    assert(tree.contains(Card('c', 2)));
    assert(tree.contains(Card('c', 8)));
}

void testContains1() {
    CardBST tree;
    assert(!tree.contains(Card('c', 1)));
}

void testContains2() {
    CardBST tree;
    tree.insert(Card('h', 12));
    assert(tree.contains(Card('h', 12)));
    assert(!tree.contains(Card('h', 11)));
}

void testContains3() {
    CardBST tree;
    tree.insert(Card('c', 1));
    tree.insert(Card('d', 5));
    tree.insert(Card('s', 10));
    assert(tree.contains(Card('c', 1)));
    assert(tree.contains(Card('d', 5)));
    assert(tree.contains(Card('s', 10)));
}

void testContains4() {
    CardBST tree;
    tree.insert(Card('c', 3));
    tree.remove(Card('c', 3));
    assert(!tree.contains(Card('c', 3)));
}

void testContains5() {
    CardBST tree;
    tree.insert(Card('c', 1));
    tree.insert(Card('d', 1));
    tree.insert(Card('s', 1));
    tree.insert(Card('h', 1));
    assert(tree.contains(Card('c', 1)));
    assert(tree.contains(Card('h', 1)));
}

void testPrintInOrder1() {
    CardBST tree;
    std::ostringstream oss;
    tree.printInOrder(oss);
    assert(oss.str() == "");
}

void testPrintInOrder2() {
    CardBST tree;
    tree.insert(Card('c', 1));
    std::ostringstream oss;
    tree.printInOrder(oss);
    assert(oss.str() == "c a\n");
}

void testPrintInOrder3() {
    CardBST tree;
    tree.insert(Card('c', 3));
    tree.insert(Card('c', 1));
    tree.insert(Card('d', 2));
    std::ostringstream oss;
    tree.printInOrder(oss);
    assert(oss.str() == "c a\nc 3\nd 2\n");
}

void testPrintInOrder4() {
    CardBST tree;
    tree.insert(Card('c', 1));
    tree.insert(Card('c', 2));
    tree.insert(Card('c', 3));
    tree.remove(Card('c', 2));
    std::ostringstream oss;
    tree.printInOrder(oss);
    assert(oss.str() == "c a\nc 3\n");
}

void testPrintInOrder5() {
    CardBST tree;
    tree.insert(Card('h', 9));
    tree.insert(Card('c', 13));
    tree.insert(Card('c', 1));
    tree.insert(Card('d', 3));
    std::ostringstream oss;
    tree.printInOrder(oss);
    assert(oss.str() == "c a\nc k\nd 3\nh 9\n");
}




void testIterator1() {
    CardBST tree;
    assert(tree.begin() == tree.end());
    assert(tree.rbegin() == tree.rend());
}

void testIterator2() {
    CardBST tree;
    tree.insert(Card('d', 5));
    auto it = tree.begin();
    assert(*it == Card('d', 5));
    ++it;
    assert(it == tree.end());
    --it;
    assert(*it == Card('d', 5));
}

void testIterator3() {
    CardBST tree;
    tree.insert(Card('c', 3));
    tree.insert(Card('c', 1));
    tree.insert(Card('h', 10));
    auto it = tree.begin();
    assert(*it == Card('c', 1));
    ++it;
    assert(*it == Card('c', 3));
    ++it;
    assert(*it == Card('h', 10));
    it = tree.rbegin();
    assert(*it == Card('h', 10));
    --it;
    assert(*it == Card('c', 3));
    --it;
    assert(*it == Card('c', 1));
}

void testIterator4() {
    CardBST tree;
    tree.insert(Card('c', 1));
    auto it = tree.begin();
    ++it;
    assert(it == tree.end());
    ++it;
    assert(it == tree.end());
    it = tree.rbegin();
    --it;
    assert(it == tree.rend());
    --it;
    assert(it == tree.rend());
}

void testIterator5() {
    CardBST tree;
    tree.insert(Card('c', 1));
    tree.insert(Card('c', 2));
    auto it1 = tree.begin();
    auto it2 = tree.begin();
    assert(it1 == it2);
    ++it1;
    assert(it1 != it2);
}




void testPlayGame1() {
    CardBST alice;
    alice.insert(Card('c', 3));
    alice.insert(Card('c', 1));
    alice.insert(Card('d', 1));
    CardBST bob;
    bob.insert(Card('c', 3));
    bob.insert(Card('d', 1));
    bob.insert(Card('h', 5));
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    playGame(alice, bob);
    std::cout.rdbuf(old);
    assert(oss.str().find("Alice picked matching card c 3") != std::string::npos);
    assert(oss.str().find("Bob picked matching card d a") != std::string::npos);
}

void testPlayGame2() {
    CardBST alice;
    CardBST bob;
    bob.insert(Card('c', 1));
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    playGame(alice, bob);
    std::cout.rdbuf(old);
    assert(oss.str().find("Alice's cards:") != std::string::npos);
}

void testPlayGame3() {
    CardBST alice;
    alice.insert(Card('c', 1));
    alice.insert(Card('c', 2));
    CardBST bob;
    bob.insert(Card('h', 1));
    bob.insert(Card('h', 2));
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    playGame(alice, bob);
    std::cout.rdbuf(old);
    assert(oss.str().find("Alice picked") == std::string::npos);
    assert(oss.str().find("Bob picked") == std::string::npos);
}



int main() {
    testInsert1();
    testInsert2();
    testInsert3();
    testInsert4();
    testInsert5();
    testRemove1();
    testRemove2();
    testRemove3();
    testRemove4();
    testRemove5();
    testContains1();
    testContains2();
    testContains3();
    testContains4();
    testContains5();
    testPrintInOrder1();
    testPrintInOrder2();
    testPrintInOrder3();
    testPrintInOrder4();
    testPrintInOrder5();
    testIterator1();
    testIterator2();
    testIterator3();
    testIterator4();
    testIterator5();
    testPlayGame1();
    testPlayGame2();
    testPlayGame3();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
