#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_
#include <memory>
#include <ostream>

template <class T>
class binary_search_tree
{
public:
    binary_search_tree() : root(nullptr) {}

    template <class T>
    class binary_search_tree_node
    {
    public:
        binary_search_tree_node(T k) : key(std::make_unique<T>(k)), left(nullptr), right(nullptr) {}

        operator const T& () const { return *key; }
        
        friend binary_search_tree<T>;
    private:
        std::unique_ptr<T> key;
        std::unique_ptr<binary_search_tree_node<T>> left, right;
    };

    using node = binary_search_tree_node<T>;
    using node_ptr = std::unique_ptr<node>;

    bool search(T key) { return search(key, root); }

    bool search(T key, const node_ptr& it)
    {
        if (!it)
            return false;
        if (*it == key)
            return true;
        if (key < *it)
            return search(key, it->left);
        else
            return search(key, it->right);
    }

    void insert(T key) { insert(key, root); }

    void insert(T key, node_ptr& it)
    {
        if (!it)
        {
            it = std::make_unique<node>(key);
            return;
        }
        if (key < *it)
            return insert(key, it->left);
        else
            return insert(key, it->right);
    }

    void erase(T key) { erase(find(key)); }

    void erase(node_ptr& it)
    {
        if (!it->left && !it->right)
            it = node_ptr();
        else if (it->left && !it->right)
            it = std::move(it->left);
        else if (!it->left && it->right)
            it = std::move(it->right);
        else
        {
            node_ptr& successor = min(it->right);
            it->key = std::move(successor->key);
            erase(successor);
        }
        
    }

    inline static node_ptr npos{nullptr};

private:

    node_ptr& min(node_ptr& it)
    {
        if (it->left)
            return it->left;
        return it;
    }

    node_ptr& find(T key) { return find(key, root); }

    node_ptr& find(T key, node_ptr& it)
    {
        if (!it)
            return npos;
        if (*it == key)
            return it;
        if (key < *it)
            return find(key, it->left);
        else
            return find(key, it->right);
    }
    std::unique_ptr<node> root;
};

#endif