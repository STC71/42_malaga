#pragma once
#include "extra_class/searchable_bag.hpp"
#include "extra_class/tree_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag {

	public:

		searchable_tree_bag() : tree_bag() {}
		searchable_tree_bag(const searchable_tree_bag &other) : tree_bag(other) {}
		searchable_tree_bag &operator=(const searchable_tree_bag &other) {
			if (this != &other)
				tree_bag::operator=(other);
			return *this;
		}
		~searchable_tree_bag() {}

		bool has(int item) const {
			node *current = tree;
			while (current) {
				if (item == current->value)
					return true;
				else if (item > current->value)
					current = current->r;
				else
					current = current->l;
			}
			return false;
		}
};
