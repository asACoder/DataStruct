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
    BinaryNode<DataType>* _hot;// 查找节点的父亲节点(search 返回NULL 假想 _hot 为NULL的父节点)
    
    void leftRotation(BinaryNode<DataType> *node); // 左旋
    void rightRotation(BinaryNode<DataType> *node);// 右旋
    
    void removeAt(BinaryNode<DataType>* node);
    
public:
    virtual BinaryNode<DataType>* search(DataType& data);
    virtual BinaryNode<DataType>* insert(DataType& data);
    virtual bool remove(DataType& data);
private:
    void swap(DataType& val, DataType& data);
};

template <typename DataType>
void BinarySearchTree<DataType>::swap(DataType& val,  DataType& data) {
    DataType temp = val;
    val = data;
    data = temp;
}



/*
 *BST search
 * 存在，返回指向给节点的指针
 * 不存在，返回 NULL
 */
template <typename DataType>
BinaryNode<DataType>* BinarySearchTree<DataType>::search(DataType& data) {
    

    _hot = NULL;
    BinaryNode<DataType>* curNode = BinaryTree<DataType>::_root;
    
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
//    this->updataHeightAbove(curNode); insertAsLChild 和 insertAsRChild 内部调用
    return curNode;
}

/*
 *BST remove
 */
template <typename DataType>
bool BinarySearchTree<DataType>::remove(DataType& data) {
    BinaryNode<DataType> * curNode = search(data);
    if(!curNode) return false; // 不存在，直接返回

//    if (curNode->lChild && curNode->rChild) {
//        BinaryNode<DataType>*succ = this->successor(curNode);
//        swap(succ->value, curNode->value);
//        curNode = succ;
//        _hot = succ->parent;
//    }
//    
//    if (curNode->lChild) { // 只有左孩子
//        swap(curNode->value, curNode->lChild->value);
//        delete curNode->lChild;
//        curNode->lChild = NULL;
//    }else if(curNode->rChild){// 只有右孩子(交换value,删除孩子节点)
//        swap(curNode->value, curNode->rChild->value);
//        delete curNode->rChild;
//        curNode->rChild = NULL;
//    }else{ // 没有孩子 叶子节点 直接删除
//        if (_hot) {
//            _hot->lChild == curNode ? _hot->lChild = NULL : _hot->rChild = NULL;
//        }else{ // 只有根节点
//            BinaryTree<DataType>::_root = NULL;
//        }
//        delete curNode;
//    }
//    BinaryTree<DataType>::_size--;
    
    removeAt(curNode);
    
    BinaryTree<DataType>::_size--;
    this->updateHeightAbove(_hot);

    return true;
}


template <typename DataType>
void BinarySearchTree<DataType>::removeAt(BinaryNode<DataType>* curNode) {
    
    if (curNode->lChild && curNode->rChild) {
        BinaryNode<DataType>*succ = this->successor(curNode);
        swap(succ->value, curNode->value);
        curNode = succ;
        _hot = succ->parent;
    }

    if (_hot == NULL) { // 删除根节点
        if (curNode->lChild) {
            this->_root = curNode->lChild;
            curNode->lChild->parent = NULL;
        }else if(curNode->rChild){
            this->_root = curNode->rChild;
            curNode->rChild->parent = NULL;
        }else{
            this->_root = NULL;
        }
    }else{
        if (curNode->lChild) { // 只有左孩子
            _hot->lChild = curNode->lChild;
            curNode->lChild->parent = _hot;
        }else if(curNode->rChild){ // 只有右孩子
            _hot->rChild = curNode->rChild;
            curNode->rChild->parent = _hot;
        }else{                  //  叶子节点
            if (_hot->lChild == curNode) {
                _hot->lChild = NULL;
            }else{
                _hot->rChild = NULL;
            }
        }
    }
    
    delete curNode;
}


// 左旋
template <typename DataType>
void BinarySearchTree<DataType>::leftRotation(BinaryNode<DataType> *node) {
    
    BinaryNode<DataType> *nodeParent = node->parent;// 旋转节点父亲节点
    BinaryNode<DataType> *nodeGrandFather = nodeParent->parent;//旋转节点祖父节点 为NULL 说明nodeParent是根节点
    
    nodeParent->rChild = node->lChild;
    
    nodeParent->parent = node;
    
    if (node->lChild) {
        node->lChild->parent = nodeParent;
    }
    node->lChild = nodeParent;

    
    if (nodeGrandFather) {
        node->parent = nodeGrandFather;
        if (nodeGrandFather->lChild == nodeParent) {
            nodeGrandFather->lChild = node;
        }else{
            nodeGrandFather->rChild = node;
        }
    }else{
        BinaryTree<DataType>::_root = node;
        node->parent = NULL;
    }
    this->updateHeightAbove(nodeParent); // 旋转操作 需要更新全树

}

// 右旋
template <typename DataType>
void BinarySearchTree<DataType>::rightRotation(BinaryNode<DataType> *node) {
    BinaryNode<DataType> *nodeParent = node->parent;// 旋转节点父亲节点
    BinaryNode<DataType> *nodeGrandFather = nodeParent->parent;//旋转节点祖父节点 为NULL 说明nodeParent是根节点
    
    nodeParent->lChild = node->rChild;
    
    nodeParent->parent = node;
    
    if (node->rChild) {
        node->rChild->parent = nodeParent;
    }
    node->rChild = nodeParent;

    if (nodeGrandFather) {
        node->parent = nodeGrandFather;
        if (nodeGrandFather->lChild == nodeParent) {
            nodeGrandFather->lChild = node;
        }else{
            nodeGrandFather->rChild = node;
        }
    }else{
        BinaryTree<DataType>::_root = node;
        node->parent = NULL;
    }
    
    this->updateHeightAbove(nodeParent);
    
}

#endif /* defined(__BinaryTree__BinarySearchTree__) */
