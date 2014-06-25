//
//  AVL.h
//  BinaryTree
//
//  Created by fushijian on 14-6-24.
//  Copyright (c) 2014年 fsj. All rights reserved.
//

#ifndef __BinaryTree__AVL__
#define __BinaryTree__AVL__


#include "BinarySearchTree.h"

/*
 *AVL树
 *任一节点v的平衡因子的绝对值不超过1: 左右子树的高度差不超过1
 */

template <typename DataType>
class AVL:public BinarySearchTree<DataType>
{

protected:
    void modifyToBalance(BinaryNode<DataType>* curNode);
public:
     BinaryNode<DataType>* insert(DataType& data);
     bool remove(DataType& data);
private:
    inline bool isBalanced(BinaryNode<DataType> *node);
};

/*
 *判断是否满足AVL 平衡条件
 */
template <typename DataType>
bool AVL<DataType>::isBalanced(BinaryNode<DataType> *node) {
    

//    int leftHeight = node->lChild ? node->lChild->height : -1;
//    int rightHeight = node->rChild ? node->rChild->height: -1;
    
    int leftHeight = Height(node->lChild);
    int rightHeight = Height(node->rChild);
    
    int balFactor = leftHeight - rightHeight;
    
    if ( balFactor > -2 && balFactor < 2) {
        return true;
    }
    return false;
}

/*
 *AVL insert
 */
template <typename DataType>
BinaryNode<DataType>* AVL<DataType>::insert(DataType &data) {
    
    BinaryNode<DataType>* curNode = this->search(data);
    if(curNode) return curNode; // 存在，直接返回
    
    if (BinaryTree<DataType>::_root == NULL) return this->insertAsRoot(data);
    
    if (data < BinarySearchTree<DataType>::_hot->value) {
        curNode = this->insertAsLChild(BinarySearchTree<DataType>::_hot,data);
    }else{
        curNode = this->insertAsRChild(BinarySearchTree<DataType>::_hot,data);
    }

    for (BinaryNode<DataType> *g = BinarySearchTree<DataType>::_hot; g; g = g->parent) {

        if (!isBalanced(g)) {
            modifyToBalance(g);
            break;
        }
    }//插入只需要调整一次，整棵树即平衡
    
    return curNode;
}

/*
 *AVL remove
 */
template <typename DataType>
bool AVL<DataType>::remove(DataType& data) {
    BinaryNode<DataType> *curNode = this->search(data);
    if(!curNode) return false;
    
    this->removeAt(curNode);
    BinaryTree<DataType>::_size--;
    this->updateHeightAbove(BinarySearchTree<DataType>::_hot);

    for (BinaryNode<DataType> *g = BinarySearchTree<DataType>::_hot; g; g = g->parent) {
        
        if (!isBalanced(g)) {
            modifyToBalance(g);
        }
    }
    return curNode;

}

/*
 *失衡之后 调整
 */

template <typename DataType>
void AVL<DataType>::modifyToBalance(BinaryNode<DataType> *g) {
    BinaryNode<DataType> *p = NULL;
    BinaryNode<DataType> *v = NULL;

    // g 为 第一个 失衡节点
    // p 为 g的孩子，且 p的高度 > g 的另一个孩子的高度
    // v 为 p 的孩子 且 v的高度 >= p 的另一个孩子的高度
    
    if (Height(g->lChild) > Height(g->rChild)) { // g左子树高，平衡左子树
        p = g->lChild;
        if (Height(p->lChild) >= Height(p->rChild)) { // g->p p->v 方向一致向左 右旋
            v = p->lChild;
            this->rightRotation(p);
        }else{// g->p p->v 方向不一致 先左旋 使 g->p->v 方向一致 然后 右旋
            v = p->rChild;
            this->leftRotation(v);
            this->rightRotation(v);
        }
    }else{// 对称
        p = g->rChild;
        if (Height(p->lChild) <= Height(p->rChild)) {
            v = p->rChild;
            this->leftRotation(p);
        }else{
            v = p->lChild;
            this->rightRotation(v);
            this->leftRotation(v);
        }
    }

}


#endif /* defined(__BinaryTree__AVL__) */
