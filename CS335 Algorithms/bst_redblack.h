/*
name: Jake Wong


could not figure out what is wrong with it but it took me a long while to just get it to compile properly.
*/

#include <string.h>
//#include <string>
#include <list>




#include "queue.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include "queue.h"
#include "utils.h"
#include <iomanip>

template<typename Key, typename Value>
class bst_red_black
{

private:
	static const bool RED = true;
	static const bool BLACK = false;

	 // root of the BST

	// BST helper node data type
private:
	struct Node
	{

		Key key; // key
		Value val; // associated data
		Node *left, *right; // links to left and right subtrees
		bool color = false; // color of parent link
		int size = 0; // subtree count
		Node(Key key, Value val, bool color, int size)
		{
			this->key = key;
			this->val = val;
			this->color = color;
			this->size = size;
			this->left=nullptr;
			this->right=nullptr;
		}
	};
	friend std::ostream& operator<<(std::ostream& os, const Node& no) {
      return os << no.left << " <-- "
                << "(" << no.key << "," << no.val << " (" << &no << ")) --> "
                << no.right << "\n";
    }
	Node *root;
	/// <summary>
	/// Initializes an empty symbol table.
	/// </summary>
public:
	bst_red_black() : root(nullptr)
	{
	}
	
   /// <summary>
   ///*************************************************************************
   ///  Node helper methods.
   /// **************************************************************************
   /// </summary>
	// is node x red; false if x is null ?
private:
	bool isRed(Node *x)
	{
		if (x == nullptr)
		{
			return false;
		}
		return x->color == RED;
	}

	// number of node in subtree rooted at x; 0 if x is null
	int size(Node *x)
	{
		if (x == nullptr)
		{
			return 0;
		}
		return x->size;
	}


	/// <summary>
	/// Returns the number of key-value pairs in this symbol table. </summary>
	/// <returns> the number of key-value pairs in this symbol table </returns>
public:
	virtual int size()
	{
		return size(root);
	}

   /// <summary>
   /// Is this symbol table empty? </summary>
   /// <returns> {@code true} if this symbol table is empty and {@code false} otherwise </returns>
	virtual bool isEmpty()
	{
		return root == nullptr;
	}


   /// <summary>
   ///*************************************************************************
   ///  Standard BST search.
   /// **************************************************************************
   /// </summary>

	/// <summary>
	/// Returns the value associated with the given key. </summary>
	/// <param name="key"> the key </param>
	/// <returns> the value associated with the given key if the key is in the symbol table
	///     and {@code null} if the key is not in the symbol table </returns>
	/// <exception cref="new std::invalid_argument"> if {@code key} is {@code null} </exception>
	virtual Value get(Key key)
	{
		if (&key == nullptr)
		{
			throw new std::invalid_argument("argument to get() is null");
		}
		return get(root, key);
	}

	// value associated with the given key in subtree rooted at x; null if no such key
private:
	Value get(Node *x, Key key)
	{
		while (x != nullptr)
		{
			int cmp = key.compare(x->key);
			if (cmp < 0)
			{
				x = x->left;
			}
			else if (cmp > 0)
			{
				x = x->right;
			}
			else
			{
				return x->val;
			}
		}
		return 0;
	}

	/// <summary>
	/// Does this symbol table contain the given key? </summary>
	/// <param name="key"> the key </param>
	/// <returns> {@code true} if this symbol table contains {@code key} and
	///     {@code false} otherwise </returns>
	/// <exception cref="new std::invalid_argument"> if {@code key} is {@code null} </exception>
public:
	virtual bool contains(Key key)
	{
		return get(key) != 0;
	}

   /// <summary>
   ///*************************************************************************
   ///  Red-black tree insertion.
   /// **************************************************************************
   /// </summary>

	/// <summary>
	/// Inserts the specified key-value pair into the symbol table, overwriting the old 
	/// value with the new value if the symbol table already contains the specified key.
	/// Deletes the specified key (and its associated value) from this symbol table
	/// if the specified value is {@code null}.
	/// </summary>
	/// <param name="key"> the key </param>
	/// <param name="val"> the value </param>
	/// <exception cref="new std::invalid_argument"> if {@code key} is {@code null} </exception>
	virtual void put(Key key, Value val)
	{
		if (key == "")
		{
			throw new std::invalid_argument("first argument to put() is null");
		}
		/*if (val == 0)
		{
			//delete(key);
			return;
		}*/

		root = put(root, key, val);
		root->color = BLACK;
		// assert check();
	}

	// insert the key-value pair in the subtree rooted at h
private:
	Node *put(Node *h, Key key, Value val)
	{
		if (h == nullptr)
		{
			return new Node(key, val, RED, 1);
		}

		if (less(key,h->key))
		{
			h->left = put(h->left, key, val);
		}
		else if (less(h->key,key))
		{
			h->right = put(h->right, key, val);
		}
		else
		{
			h->val = val;
		}

		// fix-up any right-leaning links
		if (isRed(h->right) && !isRed(h->left))
		{
			h = rotateLeft(h);
		}
		if (isRed(h->left) && isRed(h->left->left))
		{
			h = rotateRight(h);
		}
		if (isRed(h->left) && isRed(h->right))
		{
			flipColors(h);
		}
		h->size = size(h->left) + size(h->right) + 1;

		return h;
	}

   /// <summary>
   ///*************************************************************************
   ///  Red-black tree deletion.
   /// **************************************************************************
   /// </summary>

	/// <summary>
	/// Removes the smallest key and associated value from the symbol table. </summary>
	/// <exception cref="new std::invalid_argument"> if the symbol table is empty </exception>
public:
	virtual void deleteMin()
	{
		if (isEmpty())
		{
			throw new std::invalid_argument("BST underflow");
		}

		// if both children of root are black, set root to red
		if (!isRed(root->left) && !isRed(root->right))
		{
			root->color = RED;
		}

		root = deleteMin(root);
		if (!isEmpty())
		{
			root->color = BLACK;
		}
		// assert check();
	}

	// delete the key-value pair with the minimum key rooted at h
private:
	Node *deleteMin(Node *h)
	{
		if (h->left == nullptr)
		{
			return nullptr;
		}

		if (!isRed(h->left) && !isRed(h->left->left))
		{
			h = moveRedLeft(h);
		}

		h->left = deleteMin(h->left);
		return balance(h);
	}


	/// <summary>
	/// Removes the largest key and associated value from the symbol table. </summary>
	/// <exception cref="new std::invalid_argument"> if the symbol table is empty </exception>
public:
	virtual void deleteMax()
	{
		if (isEmpty())
		{
			throw new std::invalid_argument("BST underflow");
		}

		// if both children of root are black, set root to red
		if (!isRed(root->left) && !isRed(root->right))
		{
			root->color = RED;
		}

		root = deleteMax(root);
		if (!isEmpty())
		{
			root->color = BLACK;
		}
		// assert check();
	}

	// delete the key-value pair with the maximum key rooted at h
private:
	Node *deleteMax(Node *h)
	{
		if (isRed(h->left))
		{
			h = rotateRight(h);
		}

		if (h->right == nullptr)
		{
			return nullptr;
		}

		if (!isRed(h->right) && !isRed(h->right->left))
		{
			h = moveRedRight(h);
		}

		h->right = deleteMax(h->right);

		return balance(h);
	}

	/// <summary>
	/// Removes the specified key and its associated value from this symbol table     
	/// (if the key is in this symbol table).    
	/// </summary>
	/// <param name="key"> the key </param>
	/// <exception cref="new std::invalid_argument"> if {@code key} is {@code null} </exception>
public:
	virtual void delete_Renamed(Key key)
	{
		if (&key == nullptr)
		{
			throw new std::invalid_argument("argument to delete() is null");
		}
		if (!contains(key))
		{
			return;
		}

		// if both children of root are black, set root to red
		if (!isRed(root->left) && !isRed(root->right))
		{
			root->color = RED;
		}

		delete(&root, &key);
		if (!isEmpty())
		{
			root->color = BLACK;
		}
		// assert check();
	}

	// delete the key-value pair with the given key rooted at h
private:
	Node *delete_Renamed(Node *h, Key key)
	{
		// assert get(h, key) != null;

		if (key->compare(h->key) < 0)
		{
			if (!isRed(h->left) && !isRed(h->left.left))
			{
				h = moveRedLeft(h);
			}
			h->left = delete(h->left, key);
		}
		else
		{
			if (isRed(h->left))
			{
				h = rotateRight(h);
			}
			if (key->compare(h->key) == 0 && (h->right == nullptr))
			{
				return nullptr;
			}
			if (!isRed(h->right) && !isRed(h->right.left))
			{
				h = moveRedRight(h);
			}
			if (key->compare(h->key) == 0)
			{
				Node *x = min(h->right);
				h->key = x->key;
				h->val = x->val;
				// h.val = get(h.right, min(h.right).key);
				// h.key = min(h.right).key;
				h->right = deleteMin(h->right);
			}
			else
			{
				h->right = delete(h->right, key);
			}
		}
		return balance(h);
	}

   /// <summary>
   ///*************************************************************************
   ///  Red-black tree helper functions.
   /// **************************************************************************
   /// </summary>

	// make a left-leaning link lean to the right
	Node *rotateRight(Node *h)
	{
		// assert (h != null) && isRed(h.left);
		Node *x = h->left;
		h->left = x->right;
		x->right = h;
		x->color = x->right->color;
		x->right->color = RED;
		x->size = h->size;
		h->size = size(h->left) + size(h->right) + 1;
		return x;
	}

	// make a right-leaning link lean to the left
	Node *rotateLeft(Node *h)
	{
		// assert (h != null) && isRed(h.right);
		Node *x = h->right;
		h->right = x->left;
		x->left = h;
		x->color = x->left->color;
		x->left->color = RED;
		x->size = h->size;
		h->size = size(h->left) + size(h->right) + 1;
		return x;
	}

	// flip the colors of a node and its two children
	void flipColors(Node *h)
	{
		// h must have opposite color of its two children
		// assert (h != null) && (h.left != null) && (h.right != null);
		// assert (!isRed(h) &&  isRed(h.left) &&  isRed(h.right))
		//    || (isRed(h)  && !isRed(h.left) && !isRed(h.right));
		h->color = !h->color;
		h->left->color = !h->left->color;
		h->right->color = !h->right->color;
	}

	// Assuming that h is red and both h.left and h.left.left
	// are black, make h.left or one of its children red.
	Node *moveRedLeft(Node *h)
	{
		// assert (h != null);
		// assert isRed(h) && !isRed(h.left) && !isRed(h.left.left);

		flipColors(h);
		if (isRed(h->right->left))
		{
			h->right = rotateRight(h->right);
			h = rotateLeft(h);
			flipColors(h);
		}
		return h;
	}

	// Assuming that h is red and both h.right and h.right.left
	// are black, make h.right or one of its children red.
	Node *moveRedRight(Node *h)
	{
		// assert (h != null);
		// assert isRed(h) && !isRed(h.right) && !isRed(h.right.left);
		flipColors(h);
		if (isRed(h->left->left))
		{
			h = rotateRight(h);
			flipColors(h);
		}
		return h;
	}

	// restore red-black tree invariant
	Node *balance(Node *h)
	{
		// assert (h != null);

		if (isRed(h->right))
		{
			h = rotateLeft(h);
		}
		if (isRed(h->left) && isRed(h->left->left))
		{
			h = rotateRight(h);
		}
		if (isRed(h->left) && isRed(h->right))
		{
			flipColors(h);
		}

		h->size = size(h->left) + size(h->right) + 1;
		return h;
	}


   /// <summary>
   ///*************************************************************************
   ///  Utility functions.
   /// **************************************************************************
   /// </summary>

	/// <summary>
	/// Returns the height of the BST (for debugging). </summary>
	/// <returns> the height of the BST (a 1-node tree has height 0) </returns>
public:
	virtual int height()
	{
		return height(root);
	}
private:
	int height(Node *x)
	{
		if (x == nullptr)
		{
			return -1;
		}
		return 1 + std::max(height(x->left), height(x->right));
	}

   /// <summary>
   ///*************************************************************************
   ///  Ordered symbol table methods.
   /// **************************************************************************
   /// </summary>

	/// <summary>
	/// Returns the smallest key in the symbol table. </summary>
	/// <returns> the smallest key in the symbol table </returns>
	/// <exception cref="new std::invalid_argument"> if the symbol table is empty </exception>
public:
	virtual Key min()
	{
		if (isEmpty())
		{
			throw new std::invalid_argument("calls min() with empty symbol table");
		}
		return min(root)->key;
	}

	// the smallest key in subtree rooted at x; null if no such key
private:
	Node *min(Node *x)
	{
		// assert x != null;
		if (x->left == nullptr)
		{
			return x;
		}
		else
		{
			return min(x->left);
		}
	}

	/// <summary>
	/// Returns the largest key in the symbol table. </summary>
	/// <returns> the largest key in the symbol table </returns>
	/// <exception cref="new std::invalid_argument"> if the symbol table is empty </exception>
public:
	virtual Key max()
	{
		if (isEmpty())
		{
			throw new std::invalid_argument("calls max() with empty symbol table");
		}
		return max(root)->key;
	}

	// the largest key in the subtree rooted at x; null if no such key
private:
	Node *max(Node *x)
	{
		// assert x != null;
		if (x->right == nullptr)
		{
			return x;
		}
		else
		{
			return max(x->right);
		}
	}


	/// <summary>
	/// Returns the largest key in the symbol table less than or equal to {@code key}. </summary>
	/// <param name="key"> the key </param>
	/// <returns> the largest key in the symbol table less than or equal to {@code key} </returns>
	/// <exception cref="new std::invalid_argument"> if there is no such key </exception>
	/// <exception cref="new std::invalid_argument"> if {@code key} is {@code null} </exception>
public:
	virtual Key floor(Key key)
	{
		if (&key == nullptr)
		{
			throw new std::invalid_argument("argument to floor() is null");
		}
		if (isEmpty())
		{
			throw new std::invalid_argument("calls floor() with empty symbol table");
		}
		Node *x = floor(root, key);
		if (x == nullptr)
		{
			throw new std::invalid_argument("argument to floor() is too small");
		}
		else
		{
			return x->key;
		}
	}

	// the largest key in the subtree rooted at x less than or equal to the given key
private:
	Node *floor(Node *x, Key key)
	{
		if (x == nullptr)
		{
			return nullptr;
		}
		int cmp = key.compare(x->key);
		if (cmp == 0)
		{
			return x;
		}
		if (cmp < 0)
		{
			return floor(x->left, key);
		}
		Node *t = floor(x->right, key);
		if (t != nullptr)
		{
			return t;
		}
		else
		{
			return x;
		}
	}

	/// <summary>
	/// Returns the smallest key in the symbol table greater than or equal to {@code key}. </summary>
	/// <param name="key"> the key </param>
	/// <returns> the smallest key in the symbol table greater than or equal to {@code key} </returns>
	/// <exception cref="new std::invalid_argument"> if there is no such key </exception>
	/// <exception cref="new std::invalid_argument"> if {@code key} is {@code null} </exception>
public:
	virtual Key ceiling(Key key)
	{
		if (&key == nullptr)
		{
			throw new std::invalid_argument("argument to ceiling() is null");
		}
		if (isEmpty())
		{
			throw new std::invalid_argument("calls ceiling() with empty symbol table");
		}
		Node *x = ceiling(root, key);
		if (x == nullptr)
		{
			throw new std::invalid_argument("argument to ceiling() is too small");
		}
		else
		{
			return x->key;
		}
	}

	// the smallest key in the subtree rooted at x greater than or equal to the given key
private:
	Node *ceiling(Node *x, Key key)
	{
		if (x == nullptr)
		{
			return nullptr;
		}
		int cmp = key.compare(x->key);
		if (cmp == 0)
		{
			return x;
		}
		if (cmp > 0)
		{
			return ceiling(x->right, key);
		}
		Node *t = ceiling(x->left, key);
		if (t != nullptr)
		{
			return t;
		}
		else
		{
			return x;
		}
	}

	/// <summary>
	/// Return the key in the symbol table of a given {@code rank}.
	/// This key has the property that there are {@code rank} keys in
	/// the symbol table that are smaller. In other words, this key is the
	/// ({@code rank}+1)st smallest key in the symbol table.
	/// </summary>
	/// <param name="rank"> the order statistic </param>
	/// <returns> the key in the symbol table of given {@code rank} </returns>
	/// <exception cref="new std::invalid_argument"> unless {@code rank} is between 0 and
	///        <em>n</em>–1 </exception>
public:
	virtual Key select(int rank)
	{
		if (rank < 0 || rank >= size())
		{
			throw new std::invalid_argument(std::string("argument to select() is invalid: " + rank));
		}
		return select(root, rank);
	}

	// Return key in BST rooted at x of given rank.
	// Precondition: rank is in legal range.
private:
	Key select(Node *x, int rank)
	{
		if (x == nullptr)
		{
			return nullptr;
		}
		int leftSize = size(x->left);
		if (leftSize > rank)
		{
			return select(x->left, rank);
		}
		else if (leftSize < rank)
		{
			return select(x->right, rank - leftSize - 1);
		}
		else
		{
			return x->key;
		}
	}

	/// <summary>
	/// Return the number of keys in the symbol table strictly less than {@code key}. </summary>
	/// <param name="key"> the key </param>
	/// <returns> the number of keys in the symbol table strictly less than {@code key} </returns>
	/// <exception cref="new std::invalid_argument"> if {@code key} is {@code null} </exception>
public:
	virtual int rank(Key key)
	{
		if (&key == nullptr)
		{
			throw new std::invalid_argument("argument to rank() is null");
		}
		return rank(key, root);
	}

	// number of keys less than key in the subtree rooted at x
private:
	int rank(Key key, Node *x)
	{
		if (x == nullptr)
		{
			return 0;
		}
		int cmp = key.compare(x->key);
		if (cmp < 0)
		{
			return rank(key, x->left);
		}
		else if (cmp > 0)
		{
			return 1 + size(x->left) + rank(key, x->right);
		}
		else
		{
			return size(x->left);
		}
	}

   /// <summary>
   ///*************************************************************************
   ///  Range count and range search.
   /// **************************************************************************
   /// </summary>

	/// <summary>
	/// Returns all keys in the symbol table as an {@code Iterable}.
	/// To iterate over all of the keys in the symbol table named {@code st},
	/// use the foreach notation: {@code for (Key key : st.keys())}. </summary>
	/// <returns> all keys in the symbol table as an {@code Iterable} </returns>
public:
	array_queue<Key> keys()
	{
		if (isEmpty())
		{
			return array_queue<Key>();
		}
		Key min_key = min(), max_key = max();
		return keys(min_key, max_key);
	}

	/// <summary>
	/// Returns all keys in the symbol table in the given range,
	/// as an {@code Iterable}.
	/// </summary>
	/// <param name="lo"> minimum endpoint </param>
	/// <param name="hi"> maximum endpoint </param>
	/// <returns> all keys in the symbol table between {@code lo} 
	///    (inclusive) and {@code hi} (inclusive) as an {@code Iterable} </returns>
	/// <exception cref="new std::invalid_argument"> if either {@code lo} or {@code hi}
	///    is {@code null} </exception>
	array_queue<Key> keys(Key& lo, Key& hi)
	{
		if (lo == "")
		{
			throw new std::invalid_argument("first argument to keys() is null");
		}
		if (hi == "")
		{
			throw new std::invalid_argument("second argument to keys() is null");
		}

		array_queue<Key> queue;
		// if (isEmpty() || lo.compareTo(hi) > 0) return queue;
		keys(root, queue, lo, hi);
		return queue;
	}

	// add the keys between lo and hi in the subtree rooted at x
	// to the queue
private:
	void keys(Node *x, array_queue<Key>& queue, Key lo, Key hi)
	{
		if (x == nullptr)
		{
			return;
		}
		int cmplo = less(lo,x->key);
		int cmphi = less(x->key, hi);
		if (cmplo)
		{
			keys(x->left, queue, lo, hi);
		}
		if (cmplo && cmphi)
		{
			queue.enqueue(x->key);
		}
		if (cmphi)
		{
			keys(x->right, queue, lo, hi);
		}
	}

	/// <summary>
	/// Returns the number of keys in the symbol table in the given range.
	/// </summary>
	/// <param name="lo"> minimum endpoint </param>
	/// <param name="hi"> maximum endpoint </param>
	/// <returns> the number of keys in the symbol table between {@code lo} 
	///    (inclusive) and {@code hi} (inclusive) </returns>
	/// <exception cref="new std::invalid_argument"> if either {@code lo} or {@code hi}
	///    is {@code null} </exception>
public:
	virtual int size(Key lo, Key hi)
	{
		if (&lo == nullptr)
		{
			throw new std::invalid_argument("first argument to size() is null");
		}
		if (&hi == nullptr)
		{
			throw new std::invalid_argument("second argument to size() is null");
		}

		if (lo.compare(hi) > 0)
		{
			return 0;
		}
		if (contains(hi))
		{
			return rank(hi) - rank(lo) + 1;
		}
		else
		{
			return rank(hi) - rank(lo);
		}
	}


   /// <summary>
   ///*************************************************************************
   ///  Check integrity of red-black tree data structure.
   /// **************************************************************************
   /// </summary>
private:
	bool check()
	{
		if (!isBST())
		{
			std::cout<<"Not in symmetric order";
		}
		if (!isSizeConsistent())
		{
			std::cout<<"Subtree counts not consistent";
		}
		if (!isRankConsistent())
		{
			std::cout<<"Ranks not consistent";
		}
		if (!is23())
		{
			std::cout<<"Not a 2-3 tree";
		}
		if (!isBalanced())
		{
			std::cout<<"Not balanced";
		}
		return isBST() && isSizeConsistent() && isRankConsistent() && is23() && isBalanced();
	}

	// does this binary tree satisfy symmetric order?
	// Note: this test also ensures that data structure is a binary tree since order is strict
	bool isBST()
	{
		return isBST(root, nullptr, nullptr);
	}

	// is the tree rooted at x a BST with all keys strictly between min and max
	// (if min or max is null, treat as empty constraint)
	// Credit: Bob Dondero's elegant solution
	bool isBST(Node *x, Key min, Key max)
	{
		if (x == nullptr)
		{
			return true;
		}
		if (min != nullptr && x->key->compare(min) <= 0)
		{
			return false;
		}
		if (max != nullptr && x->key->compare(max) >= 0)
		{
			return false;
		}
		return isBST(x->left, min, x->key) && isBST(x->right, x->key, max);
	}

	// are the size fields correct?
	bool isSizeConsistent()
	{
		return isSizeConsistent(root);
	}
	bool isSizeConsistent(Node *x)
	{
		if (x == nullptr)
		{
			return true;
		}
		if (x->size != size(x->left) + size(x->right) + 1)
		{
			return false;
		}
		return isSizeConsistent(x->left) && isSizeConsistent(x->right);
	}

	// check that ranks are consistent
	bool isRankConsistent()
	{
		for (int i = 0; i < size(); i++)
		{
			if (i != rank(select(i)))
			{
				return false;
			}
		}
		for (auto key : keys())
		{
			if (key->compare(select(rank(key))) != 0)
			{
				return false;
			}
		}
		return true;
	}

	// Does the tree have no red right links, and at most one (left)
	// red links in a row on any path?
	bool is23()
	{
		return is23(root);
	}
	bool is23(Node *x)
	{
		if (x == nullptr)
		{
			return true;
		}
		if (isRed(x->right))
		{
			return false;
		}
		if (x != root && isRed(x) && isRed(x->left))
		{
			return false;
		}
		return is23(x->left) && is23(x->right);
	}

	// do all paths from root to leaf have same number of black edges?
	bool isBalanced()
	{
		int black = 0; // number of black links on path from root to min
		Node *x = root;
		while (x != nullptr)
		{
			if (!isRed(x))
			{
				black++;
			}
			x = x->left;
		}
		return isBalanced(root, black);
	}

	// does every path from the root to a leaf have the given number of black links?
	bool isBalanced(Node *x, int black)
	{
		if (x == nullptr)
		{
			return black == 0;
		}
		if (!isRed(x))
		{
			black--;
		}
		return isBalanced(x->left, black) && isBalanced(x->right, black);
	}
public:
	array_queue<Key> level_order() {
    array_queue<Key> keys;
    array_queue<Node*> q;

    q.enqueue(root);
    while (!q.empty()) {
      Node* x = q.dequeue();
      if (x == nullptr) { continue; }

      keys.enqueue(x->key);
      q.enqueue(x->left);
      q.enqueue(x->right);
    }
    return keys;
  }
public:
  void print_inorder() {
    std::cout << "========================================================================= printing inorder...\n";
    print_inorder(root);
    std::cout << "========================================================================= end printing inorder...\n\n";
  }
private:
  void print_inorder(Node* x) {
    if (x == nullptr) { return; }
    print_inorder(x->left);
    std::cout << *x;
    print_inorder(x->right);
  }
	/// <summary>
	/// Unit tests the {@code bst_red_black} data type.
	/// </summary>
	/// <param name="args"> the command-line arguments </param>
	/*static void test_bst(const std::string& filename) {
		char buf[BUFSIZ];
    	bst_red_black<std::string, int> st;

    	std::ifstream ifs(filename);
    	if (!ifs.is_open()) {
      		std::cerr << "Could not open file: '" << filename << "'\n";  exit(2);
    	}

    	std::cout << "Building symbol table for file: '" << filename << "'. \n";
    	std::cout << "(punctuation automatically stripped)... \n";
    	int i = 0;
    	std::string s;
   	 	while (ifs >> s) {
      		strcpy(buf, s.c_str());
      		strconvert(buf, tolower);
      		strstrip(buf);
      		std::string key = std::string(buf);
      		if (key != "") { st.put(key, i++); }
//      		st.print_inorder();
    	}
    	std::cout << "\n";

    	std::cout << "\nin level order (root to leaves)...\n";
    	array_queue<Key> keys = st.level_order();
    	for (std::string& key : keys) {
      		std::cout << std::setw(12) << key << "  " << std::setw(2) << st.get(key) << "\n";
    	}

    	std::cout << "\nin alphabetical order...\n";
        array_queue<Key> keys = st.keys();
    	for (std::string& key : keys) {
      		std::cout << std::setw(14) << key << "  " << std::setw(2) << st.get(key) << "\n";
    	}
	}*/	
};
