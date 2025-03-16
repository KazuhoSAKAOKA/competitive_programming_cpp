#pragma once

#include <unordered_map>
#include <string>

namespace competitive_programming {

struct trie_tree {
	struct node {
		size_t count_ = 0;
		std::unordered_map<char, node*> nodes_;
	};
	node root_;

	void add(const std::string& s) {
		node* current = &root_;
		for (int i = 0; i < s.size(); i++) {
			const auto it = current->nodes_.find(s[i]);
			if (it != cend(current->nodes_)) {
				it->second->count_++;
				current = (it->second);
			}
			else {
				auto [itnew, _] = current->nodes_.insert(std::make_pair(s[i], new node()));
				itnew->second->count_++;
				current = (itnew->second);
			}
		}
	}

};
}