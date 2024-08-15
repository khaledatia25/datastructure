#include <bits/stdc++.h>
using namespace std;

template <class T>
class BinaryTree {
   private:
    T data;
    BinaryTree* left{};
    BinaryTree* right{};
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
    BinaryTree(T data) : data(data) {}
    ~BinaryTree() {
        clear_tree();
    }

    bool is_complete() {
        bool ret = true;
        if (right && !left) return false;
        if (right) ret &= right->is_complete();
        if (left) ret &= left->is_complete();
    }
    void print_inorder() {  // left value right
        if (left) left->print_inorder();
        cout << data << " ";
        if (right) right->print_inorder();
    }

    void print_postorder() {  // left right value
        if (left) left->print_postorder();
        if (right) right->print_postorder();
        cout << data << " ";
    }

    void print_preorder() {  // value left right
        cout << data << " ";
        if (left) left->print_preorder();
        if (right) right->print_preorder();
    }
    void print_inorder_interative() {
    }
    void tree_boundry() {
        cout << data << ' ';
        if (left) {
            left->tree_boundry();
            return;
        }
        if (right) right->tree_boundry();
    }
    T tree_max() {
        T ret = data;
        if (left) ret = max(ret, left->tree_max());
        if (right) ret = max(ret, right->tree_max());
        return ret;
    }
    int tree_height() {
        int l = 0, r = 0;
        if (left) l = 1 + left->tree_height();
        if (right) r = 1 + right->tree_height();
        return max(l, r);
    }
    int total_node() {
        int ret = 1;
        if (left) ret += left->total_node();
        if (right) ret += right->total_node();
        return ret;
    }
    bool is_exist(T val) {
        if (data == val) return true;
        if (left && left->is_exist(val)) return true;
        if (right && right->is_exist(val)) return true;
        return false;
    }
    bool is_perfect() {
        int h = tree_height();
        int n = total_node();
        if ((1 << (h + 1)) - 1 == n) return true;
        return false;
    }

    void add(vector<T>& v, string& path, int index = 0) {
        if (index == v.size()) return;
        data = v[index];
        if (index < path.size()) {
            if (path[index] == 'L') {
                if (!left) left = new BinaryTree<T>(v[index]);
                left->add(v, path, index + 1);
            } else {
                if (!right) right = new BinaryTree<T>(v[index]);
                right->add(v, path, index + 1);
            }
        }
    }
};

signed main() {
    return 0;
}
