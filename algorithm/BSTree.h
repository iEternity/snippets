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

    }

    //最大路径和
    int maxPathSum() const
    {

    }

    //翻转二叉树

    void print() const
    {
        print(root_);
    }

private:
    //递归插入
    Node* insert(Node* p, int val)
    {
        if(p == nullptr)
        {
            p = new Node(val);
        }
        else if(val < p->value )
        {
            insert(p->left, val);
        }
        else if(val > p->value)
        {
            insert(p->right, val);
        }

        return p;
    }

    //递归删除
    bool remove(Node* p, int val)
    {
        if(p == nullptr) return false;

        //等于当前节点的值,则删除该节点
        if(val == p->value)
        {
            //无左右孩子节点
            if(p->left == nullptr && p->right == nullptr)
            {
                delete p;
                p = nullptr;
            }
            //无左子节点
            else if(p->left == nullptr)
            {
                Node* t = p->right;
                p->value = t->value;
                p->left = t->left;
                p->right = t->right;

                delete t;
                t = nullptr;
            }
            //无右子节点
            else if(p->right == nullptr)
            {
                Node* t = p->left;
                p->value = t->value;
                p->left = t->left;
                p->right = t->right;

                delete t;
                t = nullptr;
            }
            //有左右子节点
            else
            {
                //找到左边值最大的节点
                Node* cur = p->left;
                Node* parent = p;
                while(cur->right)
                {
                    parent = cur;
                    cur = cur->right;
                }

                //若找到的节点是叶子节点
                if(cur->left == nullptr)
                {
                    p->value = cur->value;
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
        else if(val < p->value)
        {
            return remove(p->left, val);
        }
        //大于当前节点的值，从右边查找
        else
        {
            return remove(p->right, val);
        }
    }

    //递归查找
    bool find(Node* p, int val) const
    {
        if(p == nullptr) return false;

        if(val < p->value)
        {
            return find(p->left, val);
        }
        else if(val > p->value)
        {
            return find(p->right, val);
        }
        else if(val == p->value)
        {
            return true;
        }
    }

    //递归遍历统计个数
    void size(Node* p, int& count) const
    {
        if(p == nullptr) return ;
        count++;
        size(p->left, count);
        size(p->right, count);
    }

    //递归遍历统计树的高度
    int height(Node* p) const
    {
        if(p == nullptr) return 0;

        return std::max(height(p->left), height(p->right)) + 1;
    }

    //中序遍历打印所有节点数据
    void print(Node* p) const
    {
        if(p == nullptr) return;

        print(p->left);

        std::cout << p->value << std::endl;

        print(p->right);
    }
private:
    Node* root_;
};