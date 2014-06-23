//
//  main.cpp
//  BinaryTree
//
//  Created by 付世健 on 14-6-7.
//  Copyright (c) 2014年 fsj. All rights reserved.
//

#include <iostream>
#include "BinaryTree.h"
#include "BinarySearchTree.h"

using namespace std;

template <typename DataType>
void visit(BinaryNode<DataType>*node) {
    cout << node->value << endl;
}

int main(int argc, const char * argv[])
{

    cout << "===============二叉搜索树================"<<endl;

    
    int arr[] = {20,12,32,6,4,8,16,18,28,64,127};
    
    BinarySearchTree<int> bst;
    
    for (int i = 0; i < 11; i++) {
        bst.insert(arr[i]);
    }
    
    cout << "============二叉搜索树 中序遍历(递归)============" << endl;
    bst.inorderTraverseRecursive(bst.root(), visit);
    cout << "============二叉搜索树 中序遍历(迭代)============" << endl;
    bst.inorderTraverseIteration(bst.root(), visit);
    
    
    
    cout << "============二叉搜索树 后序遍历(递归)============" << endl;
    bst.postorderTraverseRecursive(bst.root(), visit);
    cout << "============二叉搜索树 后序遍历(迭代)============" << endl;
    bst.postorderTraverseIteration(bst.root(), visit);

    
    // 二叉树
    cout << "============二叉树============"<<endl;
    stack<int> s;
    
    s.push(124);
    
    BinaryTree<int> bt;
    BinaryNode<int> *root = bt.insertAsRoot(5);
    bt.insertAsLChild(root, 3);
    
    BinaryNode<int> *rChild =  bt.insertAsRChild(root, 7);
    
    bt.insertAsLChild(rChild, 6);
    
    std::cout<<"树的规模"<< bt.size() << std::endl;
    std::cout<<"书的高度"<< bt.height()<<std::endl;

    // 先序遍历
    cout << "先序遍历 递归"<< endl;
    bt.preorderTraverseRecursive(root,visit);
    
    cout << "先序遍历 迭代"<< endl;
    bt.preorderTraverseIteration(root, visit);
    
    cout << "============================"<<endl<<endl;
    
    // 中序遍历
    cout << "中序遍历 递归"<< endl;
    bt.inorderTraverseRecursive(root, visit);
     cout << "中序遍历 迭代"<< endl;
    bt.inorderTraverseIteration(root, visit);
    cout << "============================"<<endl<<endl;

    // 后序遍历
    cout << "后序遍历 递归"<< endl;
    bt.postorderTraverseRecursive(root, visit);
    cout << "后序遍历 迭代"<< endl;
    bt.postorderTraverseIteration(root, visit);
    cout << "============================"<<endl<<endl;
    return 0;
}

