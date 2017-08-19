//splaytreeee

#ifndef BSTPRACTICE_SPLAYTREE_H
#define BSTPRACTICE_SPLAYTREE_H
#include "BinaryTree.h"

template <class T>
class SplayTree : public BinaryTree<T>
{
public:
    SplayTree(){this->root = nullptr;}
    virtual ~SplayTree(){}

    virtual void insert(T data);
    virtual bool remove(T data);
    node<T>* searchForNode(T data);

private:

    /* helper functions */
    node<T> *createLeaf(T key);
    node<T> *normalBSTinsert(T key);
    node<T> *inorderPredecessor(node<T> *removenode);
    bool isLeaf(node<T> *current) const;
    void removeLeafPrivate(node<T> *leafnode);
    void removeRootPrivate(node<T> *rootnode);

    /* Restructuring methods */
    void splayNode(node<T>* currentNode);
    void zigRight(node<T> *current, node<T> *parent);
    void zigzigRight(node<T> *current, node<T> *parent, node<T> *grandparent);
    void zigzagRight(node<T> *current, node<T> *parent, node<T> *grandparent);
    void zigLeft(node<T> *current, node<T> *parent);
    void zigzigLeft(node<T> *current, node<T> *parent, node<T> *grandparent);
    void zigzagLeft(node<T> *current, node<T> *parent, node<T> *grandparent);

};

template <class T>
node<T>* SplayTree<T>::createLeaf(T key){
    node<T> *newnode = new node<T>;
    newnode->left = nullptr;
    newnode->right = nullptr;
    newnode->parent = nullptr;
    newnode->data = key;
    return newnode;
}

template <class T>
node<T>* SplayTree<T>::normalBSTinsert(T key){
    node<T> * curr{this->root};
    node<T> * trail{nullptr};
    // find location to insert node
    while (curr) {
        trail = curr;
        // move left
        if (key < curr->data)
            curr = curr->left;
            // move right
        else
            curr = curr->right;
    }
    // insert the node
    node<T> *newNode{nullptr};
    if (key < trail->data) {
        trail->left = createLeaf(key);
        trail->left->parent = trail;
        newNode = trail->left;
    }
    else {
        trail->right = createLeaf(key);
        trail->right->parent = trail;
        newNode = trail->right;
    }

    return newNode;
}

/* This function is called each time an insertion, deletion, or search operation is performed. */
template <class T>
void SplayTree<T>::splayNode(node<T>* currentNode){

    if(!currentNode->parent){
        this->root = currentNode;
        return;
    }
    else{
        node<T>*parent = currentNode->parent;
        if(parent == this->root){
            if(parent->right == currentNode)
                zigLeft(currentNode, parent);
            else
                zigRight(currentNode, parent);
        }
        else{
            node<T>*grandparent = parent->parent;

            if(grandparent->left == parent && parent->left == currentNode)
                zigzigRight(currentNode, parent, grandparent);

            else if(grandparent->right == parent && parent->right == currentNode)
                zigzigLeft(currentNode, parent, grandparent);

            else if(grandparent->left == parent && parent->right == currentNode)
                zigzagRight(currentNode, parent, grandparent);

            else
                zigzagLeft(currentNode, parent, grandparent);
        }
    }
    splayNode(currentNode);
}

template <class T>
void SplayTree<T>::insert(T data) {
    if(!this->root)
        this->root = createLeaf(data);
    else{
        node<T> *newNode = normalBSTinsert(data);
        splayNode(newNode);
    }
}

template <class T>
bool SplayTree<T>::remove(T key) {
    node<T> *removenode = searchForNode(key);
    node<T> *parent{nullptr};
    if(!removenode)
        return false;
    else if(isLeaf(removenode)){
        parent = removenode->parent;
        removeLeafPrivate(removenode);
    }
    else{
        parent = removenode->parent;
        removeRootPrivate(removenode);
    }

    if(parent)
        splayNode(parent);

    return true;
}

template <class T>
node<T>*SplayTree<T>::searchForNode(T key) {
    if(this->isEmpty())
        return nullptr;
    node<T> *curr = this->root;
    bool found = false;
    while(curr && !found){
        if(key > curr->data)
            curr = curr->right;
        else if(key < curr->data)
            curr = curr->left;
        else
            found = true;
    }
    if(found)
        return curr;
    return nullptr;
}

template <class T>
node<T> *SplayTree<T>::inorderPredecessor(node<T> *removenode){
    if(this->isEmpty())
        return nullptr;

    node<T> *curr = removenode->left;
    if(!curr)
        return nullptr;

    while(curr->right){
        curr = curr->right;
    }
    return curr;
}

template <class T>
void SplayTree<T>::zigRight(node<T> *current, node<T> *parent){
    node<T>*grandparent = parent->parent;
    parent->left = current->right;
    if(current->right)
        current->right->parent = parent;
    current->right  = parent;
    current->parent = grandparent;
    if(grandparent){
        grandparent->right == parent ? grandparent->right = current : grandparent->left = current;
    }
    parent->parent  = current;
}

template <class T>
void SplayTree<T>::zigzigRight(node<T> *current, node<T> *parent, node<T> *grandparent){
    zigRight(parent, grandparent);
    zigRight(current, parent);
}

template <class T>
void SplayTree<T>::zigzagRight(node<T> *current, node<T> *parent, node<T> *grandparent){
    zigLeft(current, parent);
    zigRight(current, grandparent);
}

template <class T>
void SplayTree<T>::zigLeft(node<T> *current, node<T> *parent){
    node<T>*grandparent = parent->parent;
    parent->right = current->left;
    if(current->left)
        current->left->parent = parent;
    current->left  = parent;
    current->parent = grandparent;
    if(grandparent){
        grandparent->left == parent ? grandparent->left = current : grandparent->right = current;
    }
    parent->parent  = current;
}

template <class T>
void SplayTree<T>::zigzigLeft(node<T> *current, node<T> *parent, node<T> *grandparent){
    zigLeft(parent, grandparent);
    zigLeft(current, parent);
}

template <class T>
void SplayTree<T>::zigzagLeft(node<T> *current, node<T> *parent, node<T> *grandparent){
    zigRight(current, parent);
    zigLeft(current, grandparent);
}

template <class T>
bool SplayTree<T>::isLeaf(node<T> *current) const{
    if(!current->left && !current->right)
        return true;
    return false;
}\

template <class T>
void SplayTree<T>::removeRootPrivate(node<T> *rootnode) {
    // if the node only has a right child only
    if(rootnode->right && !rootnode->left){
        node<T> *parent = rootnode->parent;
        if(parent){
            parent->right == rootnode ? parent->right = rootnode->right : parent->left = rootnode->right;
            rootnode->right->parent = parent;
            rootnode->right = nullptr;
        }
        else{
            this->root = this->root->right;
            this->root->parent = nullptr;
            rootnode->right = nullptr;
        }
        delete rootnode;
    }

        // if the node has a left child
    else {
        node<T> *replacement = inorderPredecessor(rootnode);
        rootnode->data = replacement->data;

        if(isLeaf(replacement))
            removeLeafPrivate(replacement);
        else{
            node<T> *parent = replacement->parent;
            parent->right == replacement ? parent->right = replacement->left : parent->left = replacement->left;
            replacement->left->parent = parent;
            replacement->left = nullptr;
            replacement->parent = nullptr;
            delete replacement;
        }
    }
}

template <class T>
void SplayTree<T>::removeLeafPrivate(node<T> *leafnode) {
    if(leafnode->parent){
        node<T> *parent = leafnode->parent;
        if(parent->left == leafnode)
            parent->left = nullptr;
        else
            parent->right = nullptr;

        leafnode->parent = nullptr;
        delete leafnode;
    }
    else{
        delete this->root;
        this->root = nullptr;
    }
}


#endif //BSTPRACTICE_SPLAYTREE_H
