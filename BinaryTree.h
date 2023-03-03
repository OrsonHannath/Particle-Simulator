//
// Created by User on 3/03/2023.
//

#ifndef PARTICLESIMULATOR_BINARYTREE_H
#define PARTICLESIMULATOR_BINARYTREE_H

#include "Vector4.h"
#include "Particle.h"
#include <vector>

struct BoundingBoxNode {

    Vector4 boundingBox;
    std::vector<Particle*> boxedParticles;
    BoundingBoxNode* left;
    BoundingBoxNode* right;

    BoundingBoxNode(Vector4 boundingBox_) {
        this->boundingBox = boundingBox_;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class BoundingBoxBinaryTree {
public:
    BoundingBoxNode* root;
    BoundingBoxBinaryTree();
    void AddNode(Vector4 boundingBox, BoundingBoxNode* root_);
};


#endif //PARTICLESIMULATOR_BINARYTREE_H
