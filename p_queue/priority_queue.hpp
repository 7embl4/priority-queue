#pragma once

namespace pq {
	template <typename T>
	class priority_queue {
	private:
		using Priority = int;

		struct Node {
			T value;
			Priority pr;
			Node* parent;
			Node* left;
			Node* right;

			Node(const T& value_, Priority pr_)
				: value(value_)
				, pr(pr_)
				, parent(nullptr)
				, left(nullptr)
				, right(nullptr) {}
		};

		Node* head;
		size_t sz;

		void clear_the_queue(Node* iter) {
			if (iter->left) {
				clear_the_queue(iter->left);
			}
			if (iter->right) {
				clear_the_queue(iter->right);
			}
			delete iter;
		}

	public:
		priority_queue() : head(nullptr), sz(0) {}

		// add an element to the queue
		void push(const T& value, Priority pr) {
			Node* iter = head;
			if (0 == sz) {
				head = new Node(value, pr);
			}
			else {
				while (true) {
					if (pr < iter->pr) {
						if (!iter->left) {
							Node* new_node = new Node(value, pr);
							iter->left = new_node;
							new_node->parent = iter;
							break;
						}
						iter = iter->left;
					}
					else if (pr == iter->pr) {
						Node* iter_node = new Node(iter->value, iter->pr);
						iter->left = iter_node;
						iter_node->parent = iter;
						iter->value = value;
						break;
					}
					else {
						if (!iter->right) {
							Node* new_node = new Node(value, pr);
							iter->right = new_node;
							new_node->parent = iter;
							break;
						}
						iter = iter->right;
					}
				}
			}
			++sz;
		}

		// delete and return element with the lowest priority
		T pop() {
			Node* iter = head;
			while (iter->left) {
				iter = iter->left;
			}
			T val = iter->value; // value to return
			
			// if head is element with the lowest priority, than move head on the right child, 
			// otherwise check if element has right child or not
			if (iter == head) {
				head = iter->right;
			}
			else {
				if (iter->right) {
					iter->parent->left = iter->right;
				}
				else {
					iter->parent->left = nullptr;
				}
			}
			
			delete iter;
			--sz;
			return val;
		}

		// return element and it's priority
		Node peek() const noexcept {
			Node* iter = head;
			while (iter->left) {
				iter = iter->left;
			}
			return *iter;
		}
		
		// return the number of elements in the queue
		size_t getCount() const noexcept {
			return sz;
		}

		~priority_queue() noexcept {
			clear_the_queue(head);
		}
	};
}
