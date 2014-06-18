//
//  main.cpp
//  BinaryTree
//
//  Created by 付世健 on 14-6-7.
//  Copyright (c) 2014年 fsj. All rights reserved.
//

#include <iostream>
#include "BinaryTree.h"

using namespace std;

template <typename DataType>
void visit(BinaryNode<DataType>*node) {
    cout << node->value << endl;
}

int main(int argc, const char * argv[])
{

    // insert code here...
    
//    BinaryNode<int> b;
//
//    b.insertAsLChild(5);
    
    
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

