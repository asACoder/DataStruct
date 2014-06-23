//
//  BinarySearchTree.h
//  BinaryTree
//
//  Created by fushijian on 14-6-23.
//  Copyright (c) 2014年 fsj. All rights reserved.
//

#ifndef __BinaryTree__BinarySearchTree__
#define __BinaryTree__BinarySearchTree__


#include "BinaryTree.h"

template <typename DataType>
class BinarySearchTree :public BinaryTree<DataType>
{
protected:
    BinaryNode<DataType>* _hot;
public:
    BinaryNode<DataType>* search(DataType& data);
    BinaryNode<DataType>* insert(DataType& data);
    BinaryNode<DataType>* remove(DataType& data);
};

/*
 *BST search
 */
template <typename DataType>
BinaryNode<DataType>* BinarySearchTree<DataType>::search(DataType& data) {
    
    BinaryNode<DataType>* curNode = _hot = BinaryTree<DataType>::_root;
    
    while (curNode) {
        if (data < curNode->value) {
            _hot = curNode;
            curNode = curNode->lChild;
        }else if(curNode->value < data){
            _hot = curNode;
            curNode = curNode->rChild;
        }else{
    
            return curNode;
        }
    }
    return curNode;
}


/*
 *BST insert
 */
template <typename DataType>
BinaryNode<DataType>* BinarySearchTree<DataType>::insert(DataType& data) {
    
    BinaryNode<DataType>* curNode = search(data);
    if(curNode) return curNode; // 存在，直接返回
    
    
    
    if (BinaryTree<DataType>::_root == NULL) return this->insertAsRoot(data);
    
    if (data < _hot->value) {
        curNode = this->insertAsLChild(_hot,data);
    }else{
        curNode = this->insertAsRChild(_hot,data);
    }
    this->updataHeightAbove(curNode);
    return curNode;
}




#endif /* defined(__BinaryTree__BinarySearchTree__) */
