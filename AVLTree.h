/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>

using namespace std;

class AVLTree {
public:
    using KeyType = std::string;
    using ValueType = size_t;

protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;
        int balance;


        AVLNode *left;
        AVLNode *right;

        // 0, 1 or 2
        size_t numChildren() const;

        // true or false
        bool isLeaf() const;

        // number of hops to deepest leaf node
        size_t getHeight() const;
    };

public:
    bool insert(const std::string &key, std::size_t value);

    void CurrentHeight(AVLNode *&current);

    bool remove(const std::string &key);

    int getBalance(AVLNode *&node);

    bool contains(const std::string &key);

    bool findOnly(AVLNode *&node, std::string key);

    std::optional<size_t> get(const std::string &key);

    std::optional<size_t> ValueGet(AVLNode *&node, std::string key);

    bool find(AVLNode *&node, std::string key);

    size_t size() const;

    size_t &operator[](const std::string &key);

    size_t &FORoperator(AVLNode *&node, std::string key);

private:
    AVLNode *root = nullptr;
    size_t TreeSize;
    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode *&current, KeyType key);


    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode *&current);

    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode *&node);

    bool toInsert(AVLNode *&node, string key, size_t value);
};

#endif //AVLTREE_H
