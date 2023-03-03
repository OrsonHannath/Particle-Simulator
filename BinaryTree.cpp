//
// Created by User on 3/03/2023.
//

#include "BinaryTree.h"

BoundingBoxBinaryTree::BoundingBoxBinaryTree() {

    root = nullptr;
}

void BoundingBoxBinaryTree::AddNode(Vector4 boundingBox_, BoundingBoxNode* root_) {

    BoundingBoxNode* newNode = new BoundingBoxNode(boundingBox_);

    if (root == nullptr) {

        root = newNode;
    } else {
        root = root_;
    }
}