//
// Created by Jonathan on 12/9/2017.
//

#include <iostream>
#include "tree.h"

/// Public Methods ///
////////////////////////////////////////////////////////////////

Tree::Tree()
{
    start = nullptr;
}

Tree::~Tree()
{
    Clear();
}

// Added this because the overloaded destructor isn't working for some reason and I've spent too long trying to get it to work
// It has the same code, no idea why it works like this
void Tree::DeleteTree()
{
    Clear();
}

Tree::Tree(const Tree& other)
{
    if (&other == this)
        return;
    Clear();
    CopyOther(other);
}

Tree& Tree::operator=(const Tree& other)
{
    if (&other == this)
        return *this;
    Clear();
    CopyOther(other);
    return *this;
}

void Tree::Push(int value)
{
    auto _newNode = new TreeNode();
    _newNode->value = value;

    Tree::PushFrom(start, _newNode);
}

TreeNode* Tree::Find(int value) const
{
    return FindFrom(start, value);
}

void Tree::Print() const
{
    if (nullptr == start)
    {
        std::cout << "Tree is empty." << std::endl;
        return;
    }

    Tree::PrintFrom(start, 0);
}

void Tree::DeleteNode(int value)
{
    DeleteFrom(start, value);
}

/// Private Methods ///
////////////////////////////////////////////////////////////////

void Tree::CopyOther(const Tree& other)
{
    Tree::CopyFrom(other.start);
}

void Tree::Clear()
{
    ClearFrom(start);
    start = nullptr;
}

void Tree::CopyFrom(TreeNode* startingPoint)
{
    if (startingPoint == nullptr)
        return;

    auto _newNode = new TreeNode();
    _newNode->value = startingPoint->value;
    PushFrom(start, _newNode);

    CopyFrom(startingPoint->left);
    CopyFrom(startingPoint->right);
}

void Tree::PushFrom(TreeNode* startingPoint, TreeNode* nodeToPush)
{
    if (start == nullptr)
    {
        start = nodeToPush;
        return;
    }

    if (nodeToPush->value == startingPoint->value)
        return;

    if (nodeToPush->value < startingPoint->value)
    {
        if (startingPoint->left == nullptr)
        {
            startingPoint->left = nodeToPush;
            return;
        }
        else
        {
            PushFrom(startingPoint->left, nodeToPush);
        }
    }
    else
    {
        if (startingPoint->right == nullptr)
        {
            startingPoint->right = nodeToPush;
            return;
        }
        else
        {
            PushFrom(startingPoint->right, nodeToPush);
        }
    }
}

TreeNode* Tree::FindFrom(TreeNode* startingPoint, int value) const
{
    if (nullptr == startingPoint)
        return nullptr;

    if (value == startingPoint->value)
        return startingPoint;

    if (value < startingPoint->value)
    {
        return FindFrom(startingPoint->left, value);
    }
    else
    {
        return FindFrom(startingPoint->right, value);
    }
}

void Tree::PrintFrom(TreeNode* startingPoint, int numSpaces) const
{
    if (startingPoint != nullptr)
    {
        for (int i=0; i<numSpaces; i++)
            std::cout << " ";

        std::cout << startingPoint->value << std::endl;

        PrintFrom(startingPoint->left, numSpaces+1);
        PrintFrom(startingPoint->right, numSpaces+1);
    }
}

void Tree::DeleteFrom(TreeNode* startingPoint, int value)
{
    if (value < startingPoint->value)
    {
        if (value == startingPoint->left->value)
        {
            startingPoint->left = RemoveAndReplaceNode(startingPoint->left);
            return;
        }

        DeleteFrom(startingPoint->left, value);
    }
    else
    {
        if (value == startingPoint->right->value)
        {
            startingPoint->right = RemoveAndReplaceNode(startingPoint->right);
            return;
        }

        DeleteFrom(startingPoint->right, value);
    }
}

void Tree::ClearFrom(TreeNode* startingPoint)
{
    if (nullptr == startingPoint)
        return;

    ClearFrom(startingPoint->left);
    ClearFrom(startingPoint->right);

    delete startingPoint;
}

TreeNode* Tree::RemoveAndReplaceNode(TreeNode* nodeToRemove)
{

    if (nodeToRemove->left)
    {
        if (nodeToRemove->right)
        {
            PushFrom(nodeToRemove->left, nodeToRemove->right);
        }

        return nodeToRemove->left;
    }
    else if (nodeToRemove->right)
    {
        return nodeToRemove->right;
    }

    delete nodeToRemove;
    return nullptr;
}