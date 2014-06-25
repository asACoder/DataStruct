//
//  RedBlackTree.h
//  BinaryTree
//
//  Created by fushijian on 14-6-25.
//  Copyright (c) 2014年 fsj. All rights reserved.
//

#ifndef __BinaryTree__RedBlackTree__
#define __BinaryTree__RedBlackTree__


#include "BinarySearchTree.h"

#include <iostream>
using namespace std;

#define RBHeight(x) ((x) ? (x)->height : 0)

/*
 * 红黑树性质:
 *
 *  1 树根是黑色的
 *  2 外部节点均为黑色 //
 *  3 其余节点若为红色，则其孩子节点必须为黑色 // 注: 红节点的孩子和父亲都是 黑节点
 *  4 从任一外部节点到根节点，黑节点的数目相等 // 或者说  黑深度 相等
 */


template <typename DataType>
class RedBlackTree: public BinarySearchTree<DataType>
{
    int updateHeight(BinaryNode<DataType>* node); // 更新节点 黑高度
    
public:
    BinaryNode<DataType>* insert(DataType& data);
    bool remove(DataType& data);
private:
    
    // 外部节点也视为黑色节点(外部节点为NULL)
    inline bool isBlack(BinaryNode<DataType>*node){return (!node || node->color == BLACKCOLOR);}
    inline bool isRed(BinaryNode<DataType>*node){return !isBlack(node);}
};

/*
 *重写父类的updataHeight方法
 *
 */
template <typename DataType>
int RedBlackTree<DataType>::updateHeight(BinaryNode<DataType>* node) {
    
    cout<< "RedBlackTree updataHeight called" << endl;
    
    int leftHeight = RBHeight(node->lChild);
    int rightHeight = RBHeight(node->rChild);
    
    node->height = leftHeight > rightHeight ? leftHeight : rightHeight;
    
    return isBlack(node) ? node->height++ : node->height;
}


/*
 *RedBlackTree insert
 */
template <typename DataType>
BinaryNode<DataType>* RedBlackTree<DataType>::insert(DataType& data) {
    BinaryNode<DataType> *curNode = this->search(data);
    if (curNode) return curNode;
    
    //根节点为黑色
    if (BinaryTree<DataType>::_root == NULL) return this->insertAsRoot(data);
    // 插入其他节点时 均着 红色
    if (data < this->_hot->value) {
        curNode = this->insertAsLChild(this->_hot,data);
    }else{
        curNode = this->insertAsRChild(this->_hot,data);
    }
    
    
    
    
    return curNode;
}

template <typename DataType>
bool RedBlackTree<DataType>::remove(DataType& data)
{
    return true;
}



#endif /* defined(__BinaryTree__RedBlackTree__) */