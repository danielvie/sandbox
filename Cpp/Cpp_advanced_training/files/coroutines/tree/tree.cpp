#include "libcoro/include/coro/generator.hpp"
#include <iostream>
#include <optional>

template <typename T>
class BinTree
{
private:
    std::optional<BinTree*> left;
    T value;
    std::optional<BinTree*> right;

public:
    BinTree(std::optional<BinTree*> left, T value, std::optional<BinTree*> right) : left(left), value(value), right(right) {}

    coro::generator<T> traverse()
    {
        for (auto value : inorder(std::optional<BinTree*>(this)))
        {
            co_yield value;
        }
    }
    
    void add(T newValue)
    {
        add_helper(newValue, this);
    }

private:
    void add_helper(T newValue, std::optional<BinTree *> node)
    {
        if (!node.has_value()) { return; }

        if (newValue < node.value()->value)
        {
            if (node.value()->left)
            {
                add_helper(newValue, node.value()->left);
            }
            else
            {
                node.value()->left = new BinTree<T>(std::nullopt, newValue, std::nullopt);
            }
        }
        else if (newValue > node.value()->value)
        {
            if (node.value()->right)
            {
                add_helper(newValue, node.value()->right);
            }
            else
            {
                node.value()->right = new BinTree<T>(std::nullopt, newValue, std::nullopt);
            }
        }
    }

    coro::generator<T> inorder(std::optional<BinTree*> node)
    {
        if (node.has_value())
        {
            for (auto v : inorder(node.value()->left))
            {
                co_yield v;
            }

            co_yield node.value()->value;

            for (auto v : inorder(node.value()->right))
            {
                co_yield v;
            }
        }
    }
};

int main()
{
    BinTree<int> tree = BinTree<int>(std::nullopt, 10, std::nullopt);

    tree.add(1);
    tree.add(4);
    tree.add(9);
    tree.add(10);
    tree.add(12);
    tree.add(2);
    tree.add(20);
    tree.add(11);
    tree.add(81);
    tree.add(48);
    tree.add(33);

    for (auto v : tree.traverse())
    {
        std::cout << v << std::endl;
    }

    // delete tree;
    return 0;
}
