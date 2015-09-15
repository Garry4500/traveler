/*
 * File: tree_base.hpp
 *
 * Copyright (C) 2015 Richard Eliáš <richard.elias@matfyz.cz>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#ifndef TREE_BASE_HPP
#define TREE_BASE_HPP

#include "tree.hh"
#include "types.hpp"

//
// only declarations of classes/functions
//

template <typename label_type>
class tree_base
{
private:
    typedef tree<label_type>                        tree_type;
    typedef tree_node_<label_type>                  tree_node_type;
    class                                           _pre_post_order_iterator;
    struct                                          _iterator_hash;

public:
    typedef typename tree_type::iterator_base       base_iterator;
    typedef typename tree_type::iterator            iterator;
    typedef typename tree_type::sibling_iterator    sibling_iterator;
    typedef typename tree_type::post_order_iterator post_order_iterator;
    typedef _pre_post_order_iterator                pre_post_order_iterator;
    typedef _iterator_hash                          iterator_hash;

protected:
    tree_base() = default;

public:
    virtual ~tree_base() = default;
    template <typename labels_array>
        tree_base(
                const std::string& brackets,
                const labels_array& labels);

public:
    inline size_t id() const;
    inline size_t size() const;

public:
    static std::string print_subtree(
                const iterator& root,
                bool debug_output = true);
    inline std::string print_tree(
                bool debug_output = true) const;

public:
    /* .begin(), .end() functions from tree<> */
    inline iterator begin();
    inline iterator end();
    inline post_order_iterator begin_post();
    inline post_order_iterator end_post();
    /* + pre_post_order iterators */
    inline pre_post_order_iterator begin_pre_post();
    inline pre_post_order_iterator end_pre_post();

public:
    /* STATIC functions: */
    /* !!! RETURN same type as tree<> returns, or as parameter */

    template <typename iter>
        static iter parent(
                const iter& it);
    template <typename iter>
        static iter first_child(
                const iter& it);
    template <typename iter>
        static iter last_child(
                const iter& it);

    static bool is_first_child(
                const base_iterator& it);
    static bool is_last_child(
                const base_iterator& it);
    static bool is_leaf(
                const base_iterator& it);
    static bool is_only_child(
                const base_iterator& it);
    static bool is_root(
                const base_iterator& it);

private:
    static size_t ID;

protected:
    const size_t _id = ID++;
    tree_type _tree;
    size_t _size;
};


/* global, declaration */
template <typename iter>
inline size_t id(
                const iter& it);

/* global, declaration */
template <typename iter>
inline std::string label(
                const iter& it);

#define clabel(iter) (label(iter).c_str())


#include "tree_base_iter.hpp"
#include "tree_base_utils.hpp"

#endif /* !TREE_BASE_HPP */
