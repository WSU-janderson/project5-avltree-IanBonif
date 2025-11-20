#include "AVLTree.h"

#include <optional>
#include <string>
bool AVLTree::insert(const std::string& key, size_t value) {
    return toInsert(root,key ,value);
}
size_t AVLTree::AVLNode::numChildren() const {
    if (this->isLeaf()) {
        return 0;
    }
    if (this->right!=nullptr&&this->left!=nullptr) {
        return 2;
    }
    return 1;
}

bool AVLTree::AVLNode::isLeaf() const {
    if (this->left == nullptr&&this->right == nullptr) {
        return true;
    }

    return false;
}

size_t AVLTree::AVLNode::getHeight() const {
    return this->height;
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
             current=current->left;;
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
    if (node->right!=nullptr) {
        if (node->balance < -1 && node->right->balance <= 0) {
            AVLNode*temp=node;
            node=node->right;
            node->left=temp;
            temp->right=nullptr;

        }
        if (node->balance < -1 && node->right->balance > 0) {
            AVLNode*temp=node;
            node=node->right;
            node->left=temp;
            temp->right=nullptr;


            AVLNode* temp2=node;
            node=node->left;
            node->right=temp2;
            temp2->left=nullptr;

        }
    }
    if (node->left!=nullptr) {
        if (node->balance > 1 && node->left->balance >= 0) {
            AVLNode* temp2=node;
            node=node->left;
            node->right=temp2;
            temp2->left=nullptr;
        }
        if (node->balance < -1 && node->left->balance < 0) {
            AVLNode*temp3=node;
            node=node->right;
            node->left=temp3;
            temp3->right=nullptr;

            AVLNode* temp4=node;
            node=node->left;
            node->right=temp4;
            temp4->left=nullptr;
        }

    }
}
bool AVLTree::toInsert(AVLNode *&node,std::string key,std::size_t value) {
    if (node==nullptr) {
        node=new AVLNode(key,value);
        this->TreeSize+=1;
        return true;
    }

    if (key==node->key) {
        return false;
    }
    if (key>node->key) {
        toInsert(node->right, key,value);
        CurrentHeight(node);
        node->balance=getBalance(node);
        balanceNode(node);
    }
    if (key<node->key) {
        toInsert(node->left, key,value);
        CurrentHeight(node);
        node->balance=getBalance(node);
        balanceNode(node);
    }
    return false;
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

  bool AVLTree::find(AVLNode *&node, std::string key) {
    if (node==nullptr) {
        return false;
    }
    if (key==node->key) {
        removeNode(node);
        this->TreeSize-=1;
        return true;
    }
    if (key>node->key) {
        find(node->right, key);
        CurrentHeight(node);
        node->balance=getBalance(node);
    }
    if (key<node->key) {
        find(node->left, key);
        CurrentHeight(node);
        node->balance=getBalance(node);
    }
    return false;

}
bool AVLTree::remove(const std::string& key) {
    return find(root,key);
}
int AVLTree::getBalance(AVLNode *&node) {

    if (node->left!=nullptr&&node->right!=nullptr) {
        return node->balance+(static_cast<int>(node->left->height) - static_cast<int>( node->right->height));
    }
    if (node->left==nullptr&&node->right!=nullptr) {
        return node->balance +( -1 - static_cast<int>(node->right->height));
    }
    if (node->left!=nullptr&&node->right==nullptr) {
        return node->balance + (static_cast<int>(node->left->height+1));
    }
    return 0;
}
bool AVLTree::contains(const std::string& key) {
    return findOnly(root,key);
}

bool AVLTree::findOnly(AVLNode *&node, std::string key) {
    if (node==nullptr) {
        return false;
    }
    if (key==node->key) {
        return true;
    }
    if (key>node->key) {
        return findOnly(node->right, key);
    }
    if (key<node->key) {
        return findOnly(node->left, key);
    }
    return false;

}
std::optional<size_t> AVLTree::get(const std::string& key) {
    return ValueGet(root,key);
}

std::optional<size_t> AVLTree::ValueGet(AVLNode *&node, std::string key) {
    if (node==nullptr) {
        return std::nullopt;
    }
    if (key==node->key) {
        return node->value;
    }
    if (key>node->key) {
        return ValueGet(node->right, key);
    }
    if (key<node->key) {
        return ValueGet(node->left, key);
    }
    return std::nullopt;

}
size_t AVLTree::size()const {
    return this->TreeSize;
}
size_t& AVLTree::operator[](const std::string& key) {
    return FORoperator(root,key);
}
size_t& AVLTree::FORoperator(AVLNode *&node, std::string key) {

    if (key==node->key) {
        return node->value;
    }
    if (key>node->key) {
        return FORoperator(node->right, key);
    }
    if (key<node->key) {
        return FORoperator(node->left, key);
    }


}
