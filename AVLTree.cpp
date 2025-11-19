#include "AVLTree.h"

#include <string>
bool AVLTree::insert(const std::string& key, size_t value) {

    AVLNode* current = toInsert(root, key);
    current = new AVLNode(key,value);
   if (root==nullptr) {
        root=current;
     }

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
AVLTree::AVLNode* AVLTree::toInsert(AVLNode *current,std::string key) {
    if (current==nullptr) {
        return current;
    }
    if (key>current->key) {
        return toInsert(current->right, key);
    }
    if (key<current->key) {
        return toInsert(current->left, key);
    }


    return current;
}
void AVLTree::CurrentHeight(AVLNode*& current) {
    int LHeight;
    int RHeight;
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