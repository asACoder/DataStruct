//
//  BinaryTree.h
//  BinaryTree
//
//  Created by 付世健 on 14-6-7.
//  Copyright (c) 2014年 fsj. All rights reserved.
//

#ifndef __BinaryTree__BinaryTree__
#define __BinaryTree__BinaryTree__

#include <stack>
using namespace std;



#define Height(x) ((x) ? (x)->height : - 1) 
/*
 *定义二叉树的节点
 */
template <typename DataType>
struct BinaryNode {
    DataType value;
    BinaryNode *parent;
    BinaryNode *lChild;
    BinaryNode *rChild;
    int height; // 高度 空树高度为-1
public:
    BinaryNode():parent(NULL),lChild(NULL),rChild(NULL),height(0){}
    BinaryNode(DataType d,BinaryNode * p = NULL,BinaryNode *l = NULL,BinaryNode*r = NULL,int h = 0):value(d),parent(p),lChild(l),rChild(r),height(h){}
   
    int size();
    BinaryNode* insertAsLChild(DataType const &data);
    BinaryNode* insertAsRChild(DataType const &data);
    
    
};

template <typename DataType>
int BinaryNode<DataType>::size() {
    return 0;
}


template <typename DataType>
BinaryNode<DataType>* BinaryNode<DataType>::insertAsLChild(DataType const &data) {
    lChild = new BinaryNode<DataType>(data,this);
    return lChild;
}


template <typename DataType>
BinaryNode<DataType>* BinaryNode<DataType>::insertAsRChild(DataType const &data){
    rChild = new BinaryNode<DataType>(data,this);
    return rChild;
}

/*
 *定义二叉树
 *
 */
template <typename DataType>
class BinaryTree
{
protected:
    int _size;// 节点个数
    BinaryNode<DataType>* _root;// 根节点
    
    virtual int  updateHeight(BinaryNode<DataType>* node);// 更新节点node的高度
    void updateHeightAbove(BinaryNode<DataType>* node);// 更新节点node及其祖先节点
    

    
//    BinaryNode<DataType>* minValue(BinaryNode<DataType> *node);//查找以node为根的树最小的节点
public:
    BinaryTree():_size(0),_root(NULL){}
    ~BinaryTree(){destroyTree(_root);}
    
    int size() const {return _size;}
    bool empty() const { return !_root;}
    BinaryNode<DataType>* root(){return _root;}
    int height() {return Height(_root);}
    
    BinaryNode<DataType>* insertAsRoot(DataType const &data);
    BinaryNode<DataType>* insertAsLChild(BinaryNode<DataType>* node,DataType const &l);
    BinaryNode<DataType>* insertAsRChild(BinaryNode<DataType>* node,DataType const &r);
    
    //中序遍历下的后继
    BinaryNode<DataType>* successor(BinaryNode<DataType>* node);
    
    // 递归版本遍历
    void preorderTraverseRecursive(BinaryNode<DataType>*node,void (*)(BinaryNode<DataType>*));
    void inorderTraverseRecursive(BinaryNode<DataType>* node,void(*)(BinaryNode<DataType>*));
    void postorderTraverseRecursive(BinaryNode<DataType>* node,void(*)(BinaryNode<DataType>*));
   
    // 非递归版本遍历
    void preorderTraverseIteration(BinaryNode<DataType>*node,void(*)(BinaryNode<DataType>*));
    void inorderTraverseIteration(BinaryNode<DataType>*node,void(*)(BinaryNode<DataType>*));
    void postorderTraverseIteration(BinaryNode<DataType>*node,void(*)(BinaryNode<DataType>*));

private:
    static void deleteNode(BinaryNode<DataType>* node){delete node;}
    void destroyTree(BinaryNode<DataType>* bn);

};

/*
 *计算树的高度
 */
template <typename DataType>
int BinaryTree<DataType>::updateHeight(BinaryNode<DataType>* node) {
    
    if (!node) {
        return -1;
    }
//    
//    int leftSubTreeHeight = node->lChild ? node->lChild->height : -1;
//    int rightSubTreeHeight = node->rChild ? node->rChild->height : -1;
    int leftSubTreeHeight = Height(node->lChild);
    int rightSubTreeHeight = Height(node->rChild);
    return node->height = 1 + (leftSubTreeHeight > rightSubTreeHeight ? leftSubTreeHeight:rightSubTreeHeight);
}

/*
 *沿着节点的parent 向上更新（计算）树的高度
 */
template <typename DataType>
void BinaryTree<DataType>::updateHeightAbove(BinaryNode<DataType> *node) {
    
    if(!node)return;
    int currentHeight  = 0;
    int updatHeight = 0;
    while (node) {
        currentHeight = node->height;
        updatHeight =  updateHeight(node);
        
        if (currentHeight == updatHeight) { // 高度没有发生改变，停止向上更新
            break;
        }
        node = node->parent;
    }
}


template <typename DataType>
BinaryNode<DataType>* BinaryTree<DataType>::insertAsRoot(DataType const &data) {
    _size++;
    _root = new BinaryNode<DataType>(data);
    return _root;
}

template <typename DataType>
BinaryNode<DataType>* BinaryTree<DataType>::insertAsLChild(BinaryNode<DataType>* node,DataType const &l)
{
    node->insertAsLChild(l);
    _size++;
    updateHeightAbove(node);
    return node->lChild;
    

}

template<typename DataType>
BinaryNode<DataType>* BinaryTree<DataType>::insertAsRChild(BinaryNode<DataType>* node, const DataType &r)
{
    node->insertAsRChild(r);
    _size++;
    updateHeightAbove(node);
    return node->rChild;
}



template <typename DataType>
void BinaryTree<DataType>::destroyTree(BinaryNode<DataType>* node) {
    
    inorderTraverseIteration(node, deleteNode);
    _size = 0;
    _root = NULL;
}




///*
// *查找以node为根的树 最小的节点
// */
//template <typename DataType>
//BinaryNode<DataType>* BinaryTree<DataType>::minValue(BinaryNode<DataType>* node) {
//    
//    while (node->lChild) {
//        node = node->lChild;
//    }
//    
//    return node;
//}

/*
 *中序遍历下的后继
 */

template <typename DataType>
BinaryNode<DataType>* BinaryTree<DataType>::successor(BinaryNode<DataType> *node) {
    
    if(!node) return NULL;
    
    BinaryNode<DataType> *succ = NULL;
    
    if (node->rChild) {// 如果有右孩子
        BinaryNode<DataType>* deepestLeftChild = node->rChild;
        // 查找该右子树的最左孩子
        while (deepestLeftChild->lChild) {
            deepestLeftChild = deepestLeftChild->lChild;
        }
        succ = deepestLeftChild;
    }else{
        BinaryNode<DataType> *parentOfNode = node->parent;
        
        while (parentOfNode && parentOfNode->rChild == node) {// 该节点是父亲节点的右孩子
            node = parentOfNode;
            parentOfNode = node->parent;
        }
        succ = parentOfNode;
    }
    
    return succ;
}




// 先序遍历 递归
template<typename DataType>
void BinaryTree<DataType>::preorderTraverseRecursive(BinaryNode<DataType>*node,void (*visit)(BinaryNode<DataType>* node))
{
    if (!node) return;
    visit(node);
    preorderTraverseRecursive(node->lChild,visit);
    preorderTraverseRecursive(node->rChild, visit);
}
 //先序遍历 迭代
template <typename DataType>
void BinaryTree<DataType>::preorderTraverseIteration(BinaryNode<DataType>*node,void(*visit)(BinaryNode<DataType>*node)) {
    
    stack< BinaryNode<DataType>* > s;
    while (true) {
        if (node) { // 一直向左依次遍历病入栈，直到遇到NULL停止
            s.push(node);
            visit(node);
            node = node->lChild;
        }else{
            if (s.empty()) break;
            node = s.top(); // 遍历 最左节点的右子树
            s.pop();
            node = node->rChild;
        }
    }
}

// 中序遍历 递归
template <typename DataType>
void BinaryTree<DataType>::inorderTraverseRecursive(BinaryNode <DataType>*node,void (*visit)(BinaryNode<DataType>*node)) {

    if (! node) return;
    
    inorderTraverseRecursive(node->lChild, visit);
    visit(node);
    inorderTraverseRecursive(node->rChild, visit);
}


//中序遍历 迭代
template <typename DataType>
void BinaryTree<DataType>::inorderTraverseIteration(BinaryNode<DataType>*node,void(*visit)(BinaryNode<DataType>*)) {
    
    stack<BinaryNode<DataType>* > s;
    
    while (true) {
        if (node) {
            s.push(node);
            node = node->lChild;
        }else{
            if (s.empty()) break;
                node = s.top();
                s.pop();
                visit(node);
                node = node->rChild;
        }
    }
}


// 后序遍历 递归
template <typename DataType>
void BinaryTree<DataType>::postorderTraverseRecursive(BinaryNode<DataType>*node, void (*visit)(BinaryNode<DataType> *node)) {
    
    if (!node)return;
    
    postorderTraverseRecursive(node->lChild, visit);
    postorderTraverseRecursive(node->rChild, visit);
    visit(node);
}

// 后序遍历 迭代
template <typename DataType>
void BinaryTree<DataType>::postorderTraverseIteration(BinaryNode<DataType>*node,void (*visit)(BinaryNode<DataType>*root)) {
    
    if(node == NULL)return;
    
    stack<BinaryNode<DataType>* > s;
    
    while (true) {
        if (node->lChild) { // 依次向左遍历，直到最左
            s.push(node);
            node = node->lChild;
        }else if(node->rChild){ // 转向右
            s.push(node);
            node = node->rChild;
        }else{ // 叶子节点
            visit(node);
            while (!s.empty()) {
                
                BinaryNode<DataType>* parentNode = s.top();
                
                if (parentNode->rChild == node || parentNode->rChild == NULL) { // 右子树已经遍历ok
                    visit(parentNode);// 访问跟根节点
                    s.pop();
                    node = parentNode;
                }else if(parentNode->rChild){
                    node = parentNode->rChild;
                    break;
                }
            }
            
            if (s.empty()) {
                return;
            }
        }
    }
}









#endif /* defined(__BinaryTree__BinaryTree__) */
