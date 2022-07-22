#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iterator>
#include <functional>
#include <memory>

namespace ft
{
    enum rb_color
    {
        RB_RED = true,
        RB_BLACK = false
    };

    template <typename T>
    struct rb_node
    {
        rb_node *parent;
        rb_node *left;
        rb_node *right;
        rb_color color;
        T value;

        rb_node() : parent(), left(), right(), color(RB_RED), value() {}

        rb_node(const T &value) : parent(), left(), right(), color(RB_RED), value(value) {}

        rb_node(const rb_node &other) : parent(other.parent), left(other.left), right(other.right), color(other.color), value(other.value) {}

        ~rb_node() {}

        static rb_node<T> *leftmost(rb_node<T> *node)
        {
            if (node == NULL)
                return NULL;
            while (node->left != NULL)
                node = node->left;
            return node;
        }

        static rb_node<T> *rightmost(rb_node<T> *node)
        {
            if (node == NULL)
                return NULL;
            while (node->right != NULL)
                node = node->right;
            return node;
        }

        static rb_node<T> *successor(rb_node<T> *node)
        {
            if (node == NULL)
                return NULL;
            if (node->right != NULL)
                return leftmost(node->right);
            rb_node<T> *parent = node->parent;
            while (parent != NULL && node == parent->right)
            {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }

        static rb_node<T> *predecessor(rb_node<T> *node)
        {
            if (node->left != NULL)
                return rightmost(node->left);
            rb_node<T> *parent = node->parent;
            while (parent != NULL && node == parent->left)
            {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }
    };

    template <typename T>
    class rb_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
    private:
        rb_node<T> *node;
        rb_node<T> *previous;

    public:
        ~rb_iterator() {}

        rb_iterator() : node(), previous() {}

        rb_iterator(rb_node<T> *node) : node(node), previous() {}

        rb_iterator(const rb_iterator &other) : node(other.node), previous(other.previous) {}

        rb_iterator &operator=(const rb_iterator &other)
        {
            node = other.node;
            return *this;
        }

        rb_iterator &operator++()
        {
            if (node == NULL)
            {
                std::swap(node, previous);
                return *this;
            }
            node = rb_node<T>::successor(node);
            return *this;
        }

        rb_iterator &operator--()
        {
            if (node == NULL)
            {
                std::swap(node, previous);
                return *this;
            }
            node = rb_node<T>::predecessor(node);
            return *this;
        }

        rb_iterator operator++(int)
        {
            rb_iterator tmp(*this);
            ++*this;
            return tmp;
        }

        rb_iterator operator--(int)
        {
            rb_iterator tmp(*this);
            --*this;
            return tmp;
        }

        bool operator==(const rb_iterator &other) const { return node == other.node; }

        bool operator!=(const rb_iterator &other) const { return node != other.node; }

        T &operator*() const { return node->value; }

        T *operator->() const { return &node->value; }
    };

    template <typename T>
    class rb_const_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
    private:
        rb_node<T> *node;
        rb_node<T> *previous;

    public:
        ~rb_const_iterator() {}

        rb_const_iterator() : node(), previous() {}

        rb_const_iterator(rb_node<T> *node) : node(node), previous() {}

        rb_const_iterator(const rb_const_iterator &other) : node(other.node), previous(other.previous) {}

        rb_const_iterator &operator=(const rb_const_iterator &other)
        {
            node = other.node;
            return *this;
        }

        rb_const_iterator &operator++()
        {
            if (node == NULL)
            {
                std::swap(node, previous);
                return *this;
            }
            node = rb_node<T>::successor(node);
            return *this;
        }

        rb_const_iterator &operator--()
        {
            if (node == NULL)
            {
                std::swap(node, previous);
                return *this;
            }
            node = rb_node<T>::predecessor(node);
            return *this;
        }

        rb_const_iterator operator++(int)
        {
            rb_const_iterator tmp(*this);
            ++*this;
            return tmp;
        }

        rb_const_iterator operator--(int)
        {
            rb_const_iterator tmp(*this);
            --*this;
            return tmp;
        }

        bool operator==(const rb_const_iterator &other) const { return node == other.node; }

        bool operator!=(const rb_const_iterator &other) const { return node != other.node; }

        const T &operator*() const { return node->value; }

        const T *operator->() const { return &node->value; }
    };

    template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<rb_node<T> > >
    class rb_tree
    {
    private:
        rb_node<T> *_root;
        size_t _size;
        Compare _compare;
        Alloc _allocator;

    public:
        typedef rb_iterator<T> iterator;
        typedef rb_const_iterator<T> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        rb_tree() : _root(), _size(), _compare(), _allocator() {}

        rb_tree(const rb_tree &other) : _root(), _size(), _compare(other._compare), _allocator(other._allocator)
        {
            insert(other.begin(), other.end());
        }

        ~rb_tree()
        {
            clear();
        }

        rb_tree &operator=(const rb_tree &other)
        {
            if (*this == other)
                return *this;
            clear();
            insert(other.begin(), other.end());
            return *this;
        }

        bool empty()
        {
            return this->_root == NULL;
        }

        size_t max_size()
        {
            return this->_allocator.max_size();
        }

        size_t size() const
        {
            return this->_size;
        }

        template <typename InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            while (first != last)
                insert(*first++);
        }

        void insert(const T &value)
        {
            rb_node<T> *node = _allocator.allocate(1);
            _allocator.construct(node, value);
            rb_insert(node);
            ++_size;
        }

        void rb_insert(rb_node<T> *node)
        {
            rb_node<T> *y = NULL;
            rb_node<T> *x = this->_root;
            while (x != NULL)
            {
                y = x;
                if (_compare(node->value, x->value))
                    x = x->left;
                else
                    x = x->right;
            }
            node->parent = y;
            if (y == NULL)
                this->_root = node;
            else if (_compare(node->value, y->value))
                y->left = node;
            else
                y->right = node;
            node->left = NULL;
            node->right = NULL;
            node->color = RB_RED;
            rb_insert_fixup(node);
        }

        void remove(const T &value)
        {
            rb_node<T> *x = this->_root;
            while (x != NULL)
            {
                if (_compare(value, x->value))
                    x = x->left;
                else if (_compare(x->value, value))
                    x = x->right;
                else
                    break;
            }
            if (x != NULL)
            {
                rb_node<T> *z;
                rb_node<T> *y = x;
                rb_color yc = y->color;
                if (x->left == NULL)
                {
                    z = x->right;
                    transplant(x, x->right);
                }
                else if (x->right == NULL)
                {
                    z = x->left;
                    transplant(x, x->left);
                }
                else
                {
                    y = rb_node<T>::leftmost(x->right);
                    yc = y->color;
                    z = y->right;
                    if (y != x->right)
                    {
                        transplant(y, y->right);
                        y->right = x->right;
                        if (y->right != NULL)
                            y->right->parent = y;
                    }
                    transplant(x, y);
                    y->left = x->left;
                    if (y->left != NULL)
                        y->left->parent = y;
                    y->color = x->color;
                }
                if (yc == RB_BLACK)
                    rb_delete_fixup(z, y);
                _allocator.destroy(x);
                _allocator.deallocate(x, 1);
                --_size;
            }
        }

        iterator find(const T &value)
        {
            rb_node<T> *x = this->_root;
            while (x != NULL)
            {
                if (_compare(value, x->value))
                    x = x->left;
                else if (_compare(x->value, value))
                    x = x->right;
                else
                    return iterator(x);
            }
            return iterator(x);
        }

        const_iterator find(const T &value) const
        {
            rb_node<T> *x = this->_root;
            while (x != NULL)
            {
                if (_compare(value, x->value))
                    x = x->left;
                else if (_compare(x->value, value))
                    x = x->right;
                else
                    return const_iterator(x);
            }
            return const_iterator(x);
        }

        iterator lower_bound(const T &value)
        {
            rb_node<T> *x = this->_root;
            rb_node<T> *y = NULL;
            while (x != NULL)
            {
                y = x;
                if (_compare(value, x->value))
                    x = x->left;
                else
                    x = x->right;
            }
            return iterator(y);
        }

        const_iterator lower_bound(const T &value) const
        {
            rb_node<T> *x = this->_root;
            rb_node<T> *y = NULL;
            while (x != NULL)
            {
                y = x;
                if (_compare(value, x->value))
                    x = x->left;
                else
                    x = x->right;
            }
            return const_iterator(y);
        }

        iterator upper_bound(const T &value)
        {
            rb_node<T> *x = this->_root;
            rb_node<T> *y = NULL;
            while (x != NULL)
            {
                y = x;
                if (_compare(value, x->value))
                    x = x->left;
                else
                    x = x->right;
            }
            return iterator(y);
        }

        const_iterator upper_bound(const T &value) const
        {
            rb_node<T> *x = this->_root;
            rb_node<T> *y = NULL;
            while (x != NULL)
            {
                y = x;
                if (_compare(value, x->value))
                    x = x->left;
                else
                    x = x->right;
            }
            return const_iterator(y);
        }

        void clear()
        {
            _size = 0;
            rb_node<T> *x = rb_node<T>::leftmost(this->_root);
            rb_node<T> *y = NULL;
            while (x != NULL)
            {
                if (x->left != NULL)
                    x = x->left;
                else if (x->right != NULL)
                    x = x->right;
                else
                {
                    y = x->parent;
                    _allocator.destroy(x);
                    _allocator.deallocate(x, 1);
                    if (y != NULL)
                    {
                        if (x == y->left)
                            y->left = NULL;
                        else
                            y->right = NULL;
                    }
                    x = y;
                }
            }
            this->_root = NULL;
        }

        void swap(rb_tree<T> &other)
        {
            std::swap(this->_root, other._root);
            std::swap(this->_size, other._size);
            std::swap(this->_compare, other._compare);
        }

        iterator begin()
        {
            return iterator(rb_node<T>::leftmost(this->_root));
        }

        const_iterator begin() const
        {
            return const_iterator(rb_node<T>::leftmost(this->_root));
        }

        iterator end()
        {
            return ++iterator(rb_node<T>::rightmost(this->_root));
        }

        const_iterator end() const
        {
            return ++const_iterator(rb_node<T>::rightmost(this->_root));
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(iterator(rb_node<T>::leftmost(this->_root)));
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(const_iterator(rb_node<T>::leftmost(this->_root)));
        }

        reverse_iterator rend()
        {
            return reverse_iterator(++iterator(rb_node<T>::rightmost(this->_root)));
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(++const_iterator(rb_node<T>::rightmost(this->_root)));
        }

        Alloc get_allocator() const
        {
            return this->_allocator;
        }

        Compare get_comparator() const
        {
            return this->_compare;
        }

    protected:
        void transplant(rb_node<T> *u, rb_node<T> *v)
        {
            if (u == NULL)
                return;
            if (u->parent == NULL)
                this->_root = v;
            else if (u == u->parent->left)
                u->parent->left = v;
            else
                u->parent->right = v;
            if (v)
                v->parent = u->parent;
        }

        void rb_delete_fixup(rb_node<T> *node, rb_node<T> *node_parent)
        {
            while (node != this->_root && (node == NULL || node->color == RB_BLACK))
            {
                if (node == node_parent->left)
                {
                    rb_node<T> *w = node_parent->right;
                    if (w != NULL && w->color == RB_RED)
                    {
                        w->color = RB_BLACK;
                        node_parent->color = RB_RED;
                        this->rb_left_rotate(node_parent);
                        w = node_parent->right;
                    }
                    if (w == NULL || ((w->left == NULL || w->left->color == RB_BLACK) && (w->right == NULL || w->right->color == RB_BLACK)))
                    {
                        if (w != NULL)
                            w->color = RB_RED;
                        node = node_parent;
                        if (node != NULL)
                            node_parent = node->parent;
                    }
                    else
                    {
                        if (w->right == NULL || w->right->color == RB_BLACK)
                        {
                            w->left->color = RB_BLACK;
                            w->color = RB_RED;
                            this->rb_right_rotate(w);
                            w = node_parent->right;
                        }
                        w->color = node_parent->color;
                        node_parent->color = RB_BLACK;
                        w->right->color = RB_BLACK;
                        this->rb_left_rotate(node_parent);
                        node = this->_root;
                    }
                }
                else
                {
                    rb_node<T> *w = node_parent->left;
                    if (w != NULL && w->color == RB_RED)
                    {
                        w->color = RB_BLACK;
                        node_parent->color = RB_RED;
                        this->rb_right_rotate(node_parent);
                        w = node_parent->left;
                    }
                    if (w == NULL || ((w->right == NULL || w->right->color == RB_BLACK) && (w->left == NULL || w->left->color == RB_BLACK)))
                    {
                        if (w != NULL)
                            w->color = RB_RED;
                        node = node_parent;
                        if (node != NULL)
                            node_parent = node->parent;
                    }
                    else
                    {
                        if (w->left == NULL || w->left->color == RB_BLACK)
                        {
                            w->right->color = RB_BLACK;
                            w->color = RB_RED;
                            this->rb_left_rotate(w);
                            w = node_parent->left;
                        }
                        w->color = node_parent->color;
                        node_parent->color = RB_BLACK;
                        w->left->color = RB_BLACK;
                        this->rb_right_rotate(node_parent);
                        node = this->_root;
                    }
                }
            }
            if (node != NULL)
                node->color = RB_BLACK;
        }

        void rb_insert_fixup(rb_node<T> *node)
        {
            while (node->parent != NULL && node->parent->color == RB_RED)
            {
                if (node->parent == node->parent->parent->left)
                {
                    rb_node<T> *y = node->parent->parent->right;
                    if (y != NULL && y->color == RB_RED)
                    {
                        node->parent->color = RB_BLACK;
                        y->color = RB_BLACK;
                        node->parent->parent->color = RB_RED;
                        node = node->parent->parent;
                    }
                    else
                    {
                        if (node == node->parent->right)
                        {
                            node = node->parent;
                            rb_left_rotate(node);
                        }
                        node->parent->color = RB_BLACK;
                        node->parent->parent->color = RB_RED;
                        rb_right_rotate(node->parent->parent);
                    }
                }
                else
                {
                    rb_node<T> *y = node->parent->parent->left;
                    if (y != NULL && y->color == RB_RED)
                    {
                        node->parent->color = RB_BLACK;
                        y->color = RB_BLACK;
                        node->parent->parent->color = RB_RED;
                        node = node->parent->parent;
                    }
                    else
                    {
                        if (node == node->parent->left)
                        {
                            node = node->parent;
                            rb_right_rotate(node);
                        }
                        node->parent->color = RB_BLACK;
                        node->parent->parent->color = RB_RED;
                        rb_left_rotate(node->parent->parent);
                    }
                }
            }
            this->_root->color = RB_BLACK;
        }

        void rb_left_rotate(rb_node<T> *node)
        {
            rb_node<T> *y = node->right;
            node->right = y->left;
            if (y->left != NULL)
                y->left->parent = node;
            y->parent = node->parent;
            if (node->parent == NULL)
                this->_root = y;
            else if (node == node->parent->left)
                node->parent->left = y;
            else
                node->parent->right = y;
            y->left = node;
            node->parent = y;
        }

        void rb_right_rotate(rb_node<T> *node)
        {
            rb_node<T> *y = node->left;
            node->left = y->right;
            if (y->right != NULL)
                y->right->parent = node;
            y->parent = node->parent;
            if (node->parent == NULL)
                this->_root = y;
            else if (node == node->parent->right)
                node->parent->right = y;
            else
                node->parent->left = y;
            y->right = node;
            node->parent = y;
        }
    };
}

#endif
