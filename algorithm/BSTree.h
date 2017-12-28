#pragma once
#include <algorithm>
#include <iostream>

struct Node
{
    int value;
    Node* left;
    Node* right;

    Node(int v, Node* l = nullptr, Node* r = nullptr):
        value(v),
        left(l),
        right(r)
    {
    }
};

class BSTree
{
public:
    BSTree():root_(nullptr)
    {

    }
    ~BSTree()
    {

    }

    Node* insert(int val)
    {
        return insert(root_, val);
    }

    bool remove(int val)
    {
        return remove(root_, val);
    }

    bool find(int val) const
    {
        return find(root_, val);
    }

    int size() const
    {
        int count = 0;
        size(root_, count);
        return count;
    }

    int height() const
    {
        return height(root_);
    }

    //节点最大距离
    int maxDistance() const
    {
        return maxDistance(root_);
    }

    //最大路径和
    int maxPathSum() const
    {
        if(root_ == nullptr) return 0;

        int maxSum = root_->value;
        maxPathSum(root_, maxSum);

        return maxSum;
    }

    //翻转二叉树
    void invert()
    {
        invert(root_);
    }

    void print() const
    {
        print(root_);
    }

private:
    //递归插入
    Node* insert(Node* root, int val)
    {
        if(root == nullptr)
        {
            root = new Node(val);
        }
        else if(val < root->value )
        {
            insert(root->left, val);
        }
        else if(val > root->value)
        {
            insert(root->right, val);
        }

        return root;
    }

    //递归删除
    bool remove(Node* root, int val)
    {
        if(root == nullptr) return false;

        //等于当前节点的值,则删除该节点
        if(val == root->value)
        {
            //无左右孩子节点
            if(root->left == nullptr && root->right == nullptr)
            {
                delete root;
                root = nullptr;
            }
            //无左子节点
            else if(root->left == nullptr)
            {
                Node* t = root->right;
                root->value = t->value;
                root->left = t->left;
                root->right = t->right;

                delete t;
                t = nullptr;
            }
            //无右子节点
            else if(root->right == nullptr)
            {
                Node* t = root->left;
                root->value = t->value;
                root->left = t->left;
                root->right = t->right;

                delete t;
                t = nullptr;
            }
            //有左右子节点
            else
            {
                //找到左边值最大的节点
                Node* cur = root->left;
                Node* parent = root;
                while(cur->right)
                {
                    parent = cur;
                    cur = cur->right;
                }

                //若找到的节点是叶子节点
                if(cur->left == nullptr)
                {
                    root->value = cur->value;
                    delete cur;
                    cur = nullptr;
                }
                else//不是叶子节点
                {
                    //该节点是其父节点的左子节点
                    if(cur = parent->left)
                    {
                        parent->left = cur->left;
                        delete cur;
                        cur = nullptr;
                    }
                    //该节点是其父节点的右子节点
                    else if(cur = parent->right)
                    {
                        parent->right = cur->left;
                        delete cur;
                        cur = nullptr;
                    }
                }
            }

            return true;
        }
        //小于当前节点的值，从左边查找
        else if(val < root->value)
        {
            return remove(root->left, val);
        }
        //大于当前节点的值，从右边查找
        else
        {
            return remove(root->right, val);
        }
    }

    //递归查找
    bool find(Node* root, int val) const
    {
        if(root == nullptr) return false;

        if(val < root->value)
        {
            return find(root->left, val);
        }
        else if(val > root->value)
        {
            return find(root->right, val);
        }
        else if(val == root->value)
        {
            return true;
        }
    }

    //递归遍历统计个数
    void size(Node* root, int& count) const
    {
        if(root == nullptr) return ;
        count++;
        size(root->left, count);
        size(root->right, count);
    }

    //递归遍历统计树的高度
    int height(Node* root) const
    {
        if(root == nullptr) return 0;

        return std::max(height(root->left), height(root->right)) + 1;
    }

    int maxDistance(Node* root) const
    {
        if(root == nullptr) return 0;

        int leftDistance = maxDistance(root->left);
        int rightDistance = maxDistance(root->right);

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        return std::max(std::max(leftDistance, rightDistance), leftHeight + rightHeight);
    }

    //返回以root为终点的单路径最大和
    int maxPathSum(Node* root, int& maxSum) const
    {
        if(root == nullptr) return 0;

        int leftSum = maxPathSum(root->left);
        if(leftSum < 0) leftSum = 0;

        int rightSum = maxPathSum(root->right);
        if(rightSum < 0) rightSum = 0;

        if(leftSum + rightSum + root->value > maxSum)
        {
            maxSum = leftSum + rightSum + root->value;
        }

        return std::max(leftSum, rightSum) + root->value;
    }

    //先序遍历二叉树交换左右子节点
    void invert(Node* root)
    {
        if(root == nullptr) return;

        Node* t = root->left;
        root->left = root->right;
        root->right = t;

        invert(root->left);
        invert(root->right);
    }

    //中序遍历打印所有节点数据
    void print(Node* root) const
    {
        if(root == nullptr) return;

        print(root->left);

        std::cout << root->value << std::endl;

        print(root->right);
    }
private:
    Node* root_;
};