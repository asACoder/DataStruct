//
//  main.cpp
//  BinaryTree
//
//  Created by 付世健 on 14-6-7.
//  Copyright (c) 2014年 fsj. All rights reserved.
//

#include <iostream>
#include <string>
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "AVL.h"
#include "RedBlackTree.h"
using namespace std;

template <typename DataType>
void visit(BinaryNode<DataType>*node) {
    cout << node->value << endl;
}

template <typename DataType>
void visitWithColor(BinaryNode<DataType>*node){
    
    string s;
    
    node->color ? s = "black" : s = "red";
    cout << "value: "<< node->value << "   color:" << s << endl;
}

int main(int argc, const char * argv[])
{
    
    cout << "===============RedBlackTree ==============="<<endl;
    
    RedBlackTree<int> rbt;
    
    int rbtArr[] = {12,1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17};
    // test 对比 http://blog.csdn.net/v_july_v/article/details/6284050
    for (int i = 0; i < 15; i++) {
        rbt.insert(rbtArr[i]);
    }
    cout << "===============RBT==============="<<endl;
    cout << "rbt height = "<< rbt.height() << endl;
    cout << "rbt size = " << rbt.size() << endl;
    //        //
    //        cout << "===============RBT 中序==============="<< endl;
    //        rbt.inorderTraverseIteration(rbt.root(), visitWithColor);
    //
    cout << "===============RBT 先序==============="<< endl;
    rbt.preorderTraverseIteration(rbt.root(), visitWithColor);

    
//    for (int j = 4; j < 20; j++) {
//        RedBlackTree<int> rbt;
//        for (int i = 0; i < j; i++) {
//            rbt.insert(rbtArr[i]);
//        }
//        cout << "===============RBT==============="<<endl;
//        cout << "rbt height = "<< rbt.height() << endl;
//        cout << "rbt size = " << rbt.size() << endl;
////        //
////        cout << "===============RBT 中序==============="<< endl;
////        rbt.inorderTraverseIteration(rbt.root(), visitWithColor);
////        
//        cout << "===============RBT 先序==============="<< endl;
//        rbt.preorderTraverseIteration(rbt.root(), visitWithColor);
//    }

    

    AVL<int> avl;
//    int avlDataArr[] = {1,2,3,4,5,6};
//    for (int i = 0; i < 6; i++) {
//        avl.insert(avlDataArr[i]);
//    }
    
//    int avlDataArr[] = {50,25,75,65,68};
//    for (int i = 0; i < 5; i++) {
//        avl.insert(avlDataArr[i]);
//    }
//    
//
//    
//    cout << "===============AVL==============="<<endl;
//    cout << "avl height = "<< avl.height() << endl;
//    cout << "avl size = " << avl.size() << endl;
//    
//    cout << "===============AVL 中序==============="<< endl;
//    avl.inorderTraverseIteration(avl.root(), visit);
//    
//    cout << "===============AVL 先序==============="<< endl;
//    avl.preorderTraverseIteration(avl.root(), visit);
//    
//    int data = 25;
//    avl.remove(data);
//    cout << "===============AVL after remove==============="<<endl;
//    cout << "avl height = "<< avl.height() << endl;
//    cout << "avl size = " << avl.size() << endl;
//    
//    cout << "===============AVL 中序==============="<< endl;
//    avl.inorderTraverseIteration(avl.root(), visit);
//    
//    cout << "===============AVL 先序==============="<< endl;
//    avl.preorderTraverseIteration(avl.root(), visit);
    
//    cout << "===============二叉搜索树================"<<endl;
//
//    
//    int arr[] = {20,12,32,6,4,8,16,18,28,64,127};
//    
//    BinarySearchTree<int> bst;
//    
//    for (int i = 0; i < 11; i++) {
//        bst.insert(arr[i]);
//    }
//    
//    cout << "============二叉搜索树 中序遍历(递归)============" << endl;
//    bst.inorderTraverseRecursive(bst.root(), visit);
//    cout << "============二叉搜索树 中序遍历(迭代)============" << endl;
//    bst.inorderTraverseIteration(bst.root(), visit);
//    
//    
//    
//    cout << "============二叉搜索树 后序遍历(递归)============" << endl;
//    bst.postorderTraverseRecursive(bst.root(), visit);
//    cout << "============二叉搜索树 后序遍历(迭代)============" << endl;
//    bst.postorderTraverseIteration(bst.root(), visit);
//    
//    int data = 20;
//    bst.remove(data);
//    
//    cout << "============reomve 中序遍历====================" << endl;
//    bst.inorderTraverseIteration(bst.root(), visit);
//    cout << "after remove : bst.height = " << bst.height() << endl;
//    cout << "after remove : bst.size = " << bst.size() << endl;
//
//    
//    // 二叉树
//    cout << "============二叉树============"<<endl;
//    stack<int> s;
//    
//    s.push(124);
//    
//    BinaryTree<int> bt;
//    BinaryNode<int> *root = bt.insertAsRoot(5);
//    bt.insertAsLChild(root, 3);
//    
//    BinaryNode<int> *rChild =  bt.insertAsRChild(root, 7);
//    
//    bt.insertAsLChild(rChild, 6);
//    
//    std::cout<<"树的规模"<< bt.size() << std::endl;
//    std::cout<<"书的高度"<< bt.height()<<std::endl;
//
//    // 先序遍历
//    cout << "先序遍历 递归"<< endl;
//    bt.preorderTraverseRecursive(root,visit);
//    
//    cout << "先序遍历 迭代"<< endl;
//    bt.preorderTraverseIteration(root, visit);
//    
//    cout << "============================"<<endl<<endl;
//    
//    // 中序遍历
//    cout << "中序遍历 递归"<< endl;
//    bt.inorderTraverseRecursive(root, visit);
//     cout << "中序遍历 迭代"<< endl;
//    bt.inorderTraverseIteration(root, visit);
//    cout << "============================"<<endl<<endl;
//
//    // 后序遍历
//    cout << "后序遍历 递归"<< endl;
//    bt.postorderTraverseRecursive(root, visit);
//    cout << "后序遍历 迭代"<< endl;
//    bt.postorderTraverseIteration(root, visit);
//    cout << "============================"<<endl<<endl;
    return 0;
}

