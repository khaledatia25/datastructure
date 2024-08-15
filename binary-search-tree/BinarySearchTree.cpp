#include <bits/stdc++.h>
using namespace std;

template <class T>
class BST {
   private:
    T data;
    BST* left{};
    BST* right{};
    void clear_tree() {
        if (left) {
            delete left;
            left = nullptr;
        }
        if (right) {
            delete right;
            right = nullptr;
        }
    }

   public:
    BST() {}
    BST(T data) : data(data) {}
    ~BST() {
        clear_tree();
    }

    bool search(T target) {
        if (target == data)
            return true;
        if (target < data)
            return left && left->search(target);
        return right && right->search(target);
    }
    // from O(log(n)) to O(n)
    void insert(T target) {
        if (target < data) {
            if (!left)
                left = new BST(target);
            else
                left->insert(target);
        } else if (target > data) {
            if (!right)
                right = new BST(target);
            else
                right->insert(target);
        }
    }

    T upper_boud(T target) {
        if (target >= data) {
            if (right)
                return right->upper_boud(target);
            else
                return -1;
        } else {
            if (left)
                return left->upper_boud(target);
            else
                return data;
        }
    }
    void print_tree() {
        queue<BST*> qu;
        qu.push(this);
        for (int sz = qu.size(), lvl = 1; !qu.empty(); lvl++, sz = qu.size()) {
            cout << "level " << lvl << ": ";
            while (sz--) {
                BST* cur = qu.front();
                qu.pop();
                cout << cur->data << " ";
                if (cur->left)
                    qu.push(cur->left);
                if (cur->right) qu.push(cur->right);
                cur = nullptr;
            }
            cout << endl;
        }
    }

    /*
     *
     * Home work -1
     *
     */

    /*
     * Problem 1 iterative search
     */
    bool search_iterative(T target) {
        BST* cur = this;
        while (cur->left || cur->right) {
            if (cur->data == target)
                return true;
            else if (cur->data > target) {
                if (cur->right)
                    cur = cur->right;
                else
                    return false;
            } else {
                if (cur->left)
                    cur = cur->left;
                else
                    return false;
            }
        }
        return false;
    }

    /*
     * problem 2 is BST
     */
    bool is_bst() {
        bool ret = true;
        if (left) {
            ret &= (data > left->data) && left->is_bst();
        }
        if (!ret) return ret;
        if (right) {
            ret &= (data < right->data) && right->is_bst();
        }
        return ret;
    }

    /*
     * problem 3 array to balanced bst
     */
    void build(vector<T>& a, int st = 0, int nd = -1) {
        if (nd == -1) nd = a.size() - 1;
        int mid = (st + nd) / 2;
        this->data = a[mid];
        if (st <= mid - 1) {
            this->left = new BST();
            this->left->build(a, st, mid - 1);
        }
        if (mid + 1 <= nd) {
            this->right = new BST();
            this->right->build(a, mid + 1, nd);
        }
    }

    /*
     * problem 4 find kth smallest
     */
    T kth_smallest(int& k) {
        if (k == 0) return -1234;
        if (left) {
            int res = left->kth_smallest(k);
            if (k == 0) return res;
        }
        k--;
        if (k == 0) return data;
        if (right) return right->kth_smallest(k);
        return -1234;
    }

    /*
     * problem 5 lca
     */
    T lca(T x, T y) {
        if (x < data && y < data) {
            return left->lca(x, y);
        }
        if (x > data && y > data) {
            return right->lca(x, y);
        }
        return data;
    }
};

signed main() {
    BST<int>* bt = new BST<int>();
    vector<int> a = {1, 2, 3, 4, 5, 6, 69, 200};
    bt->build(a);
    cout << bt->upper_boud(200) << endl;
    bt->print_tree();
    return 0;
}
