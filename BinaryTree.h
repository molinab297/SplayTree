

#ifndef BSTPRACTICE_BINARYTREE_H
#define BSTPRACTICE_BINARYTREE_H

#include <iostream>
#include <queue>


template <class T>
struct node{T data; node<T> *left, *right, *parent;};

template <class T>
class BinaryTree {

public:
    BinaryTree(); virtual ~BinaryTree();
    virtual void insert(T key) { }
    virtual bool remove(T key) { }
    void preorder();
    void postorder();
    void inorder();
    void bfs();
    bool isEmpty();

protected:
    node<T> *root;
    void preorderPrivate(node<T> *current);
    void postorderPrivate(node<T> *current);
    void inorderPrivate(node<T> *current);
};


template <class T>
BinaryTree<T>::BinaryTree() { root = nullptr; }

template <class T>
BinaryTree<T>::~BinaryTree() {
    if(!this->isEmpty()){
        std::queue<node<T>*> q;
        q.push(this->root);
        while(!q.empty()){
            node<T> *temp = q.front();
            q.pop();
            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);

            delete temp;
        }
    }
}

template <class T>
bool BinaryTree<T>::isEmpty() {
    if(!root)
        return true;
    return false;
}

template <class T>
void BinaryTree<T>::inorder() {
    if(!isEmpty())
        inorderPrivate(root);
}

template <class T>
void BinaryTree<T>::postorder() {
    if(!isEmpty())
        postorderPrivate(root);
}

template <class T>
void BinaryTree<T>::preorder() {
    if(!isEmpty())
        preorderPrivate(root);
}

// vists parent before children
template <class T>
void BinaryTree<T>::preorderPrivate(node<T> *current) {
    if(current){
        std::cout << current->data << " ";
        preorderPrivate(current->left);
        preorderPrivate(current->right);
    }
}

// visits children before parent
template <class T>
void BinaryTree<T>::postorderPrivate(node<T> *current) {
    if(current){
        preorderPrivate(current->left);
        preorderPrivate(current->right);
        std::cout << current->data << " ";
    }
}

template <class T>
void BinaryTree<T>::inorderPrivate(node<T> *current) {
    if(current){
        inorderPrivate(current->left);
        std::cout << current->data << " ";
        inorderPrivate(current->right);
    }
}

template <class T>
void BinaryTree<T>::bfs() {
    if(!isEmpty()) {
        std::queue<node<T> *> queue;
        queue.push(root);
        while (!queue.empty()) {
            node<T> *temp = queue.front();
            queue.pop();

            if (temp->left)
                queue.push(temp->left);
            if (temp->right)
                queue.push(temp->right);

            std::cout << temp->data << " ";
        }
    }
}










#endif //BSTPRACTICE_BINARYTREE_H
