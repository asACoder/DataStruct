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
 *  1 节点是黑色 或者 红色
 *  2 树根是黑色的
 *  3 外部节点均为黑色 //
 *  4 其余节点若为红色，则其孩子节点必须为黑色 // 注: 红节点的孩子和父亲都是 黑节点
 *  5 从任一外部节点到根节点，黑节点的数目相等 // 或者说  黑深度 相等
 */


template <typename DataType>
class RedBlackTree: public BinarySearchTree<DataType>
{
protected:
    int updateHeight(BinaryNode<DataType>* node); // 更新节点 黑高度
    void doubleRedFix(BinaryNode<DataType>* node); // 双红修正
    void doubleBlackFix(BinaryNode<DataType>* node); // 双黑修正
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
    
//    cout<< "RedBlackTree updataHeight called" << endl;
    
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
    
    // 插入节点 性质3 未必能保持(double red )
    
    doubleRedFix(curNode);
    
    return curNode;
}

template <typename DataType>
bool RedBlackTree<DataType>::remove(DataType& data)
{
    return true;
}

/*
 *RedBlackTree doubleRedFix
 */

template <typename DataType>
void RedBlackTree<DataType>::doubleRedFix(BinaryNode<DataType>*v) {
    
    BinaryNode<DataType> *p = NULL; // v 的 父亲
    BinaryNode<DataType> *g = NULL; // v 的 祖父 p的父亲
    BinaryNode<DataType> *pBrother = NULL; // p 的 兄弟
    
    while (isRed(v->parent)) { // 双红
        p = v->parent;
        g = p->parent; // g 一定是黑色
        
        if (g->lChild == p) { // p 是 g的左孩子
            pBrother = g->rChild;
            if (isBlack(pBrother)) { // pBrother 是黑色
                if (p->lChild == v) { // p v 同侧
                    p->color  = BLACKCOLOR;
                    this->rightRotation(p);
                }else{
                    v->color  = BLACKCOLOR;
                    this->leftRotation(v);
                    this->rightRotation(v);
                }
                g->color = REDCOLOR;
                break;
            }else{// pBrother 是红色
                p->color = BLACKCOLOR;  p->height++;
                pBrother->color = BLACKCOLOR; pBrother->height++;
                g->color =REDCOLOR;
                
                v = g;
            }
        }else{ // p 是 g的右孩子
            pBrother = g->lChild;
            if (isBlack(pBrother)) {
                if (p->rChild == v) { // p v 同侧
                    p->color = BLACKCOLOR;
                    this->leftRotation(p);
                }else{
                    v->color = BLACKCOLOR;
                    this->rightRotation(v);
                    this->leftRotation(v);
                }
                g->color = REDCOLOR;
                break;
            }else{// pBrother 是红色
                p->color = BLACKCOLOR;  p->height++;
                pBrother->color = BLACKCOLOR; pBrother->height++;
                g->color =REDCOLOR;
                
                v = g;
            }
        }
    }
    this->_root->color = BLACKCOLOR;
    
}

#endif /* defined(__BinaryTree__RedBlackTree__) */
