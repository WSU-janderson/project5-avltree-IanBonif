#include "AVLTree.h"

#include <string>
bool AVLTree::insert(const std::string& key, size_t value) {
    if (root == NULL) {
        root = new AVLNode(key,value);
        CurrentHeight(root);
        return true;
    }
    return toInsert(root, key, value);
}
size_t AVLTree::AVLNode::numChildren() const {
    return 0;
}

bool AVLTree::AVLNode::isLeaf() const {
    return false;
}

size_t AVLTree::AVLNode::getHeight() const {
    return 0;
}

bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

void AVLTree::balanceNode(AVLNode *&node) {
}
bool AVLTree::toInsert(AVLNode *current,std::string key, size_t value) {
    CurrentHeight(current);
    if (key == current->key) {
    return false;
}if (key < current->key) {
    if (current->right==nullptr) {
        current->right=new AVLNode(key,value);
        CurrentHeight(current->right);
        return true;
    }
    toInsert(current->right, key, value);
}else if (key > current->key) {
    if (current->left==nullptr) {
        current->left =new AVLNode(key,value);
        CurrentHeight(current->left);
        return true;
    }
    toInsert(current->left, key, value);
}

}
void AVLTree::CurrentHeight(AVLNode*& current) {
    size_t LHeight;
    size_t RHeight;
    if (current->left==nullptr) {
        LHeight=-1;
    }
    if (current->right==nullptr) {
        RHeight=-1;
    }
    if (current->left) {
        LHeight=current->left->height;
    }
    if (current->right) {
        RHeight=current->right->height;
    }

    if (LHeight > RHeight||LHeight == RHeight) {
        current->height = LHeight + 1;
    }else if (LHeight < RHeight) {
        current->height = RHeight + 1;
    }

}