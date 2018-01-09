#include <iostream>

using std::cin;
using std::cout;

template<typename T>
struct node {
    T key;
    node *next;
    node(T n) {
        key = n;
        next = nullptr;
    }
};

template<typename T>
node<T>* merge_lists(node<T> *root1, node<T> *root2) {
    node<T> *start;
    if (root1->key <= root2->key) {
        start = root1;
        root1 = root1->next;
    } else {
        start = root2;
        root2 = root2->next;
    }
    node<T> *cur = start;
    while (root1 != nullptr && root2 != nullptr) {
        if (root1->key <= root2->key) {
            cur->next = root1;
            root1 = root1->next;
        } else {
            cur->next = root2;
            root2 = root2->next;
        }
        cur = cur->next;
    }
    while (root1 != nullptr) {
        cur->next = root1;
        root1 = root1->next;
        cur = cur->next;
    }
    while (root2 != nullptr) {
        cur->next = root2;
        root2 = root2->next;
        cur = cur->next;
    }
    return start;
}

template<typename T>
node<T>* merge_sort(node<T> *root, size_t sz) {
    if (sz == 1)
        return root;
    size_t m = sz / 2;
    node<T> *median = root;
    for (size_t i = 0; i < m - 1; ++i) {
        median = median->next;
    }
    node<T> *median2 = median->next;
    median->next = nullptr;
    return merge_lists(merge_sort(root, m), merge_sort(median2, sz - m));
}

int main() {
    size_t n = 0;
    int a = 0;
    cin >> n >> a;
    node<int> *root = new node<int>(a);
    node<int> *last = root;
    for (size_t i = 1; i < n; ++i) {
        cin >> a;
        node<int> *new_node = new node<int>(a);
        last->next = new_node;
        last = new_node;
    }
    node<int> *ans = merge_sort(root, n);
    while (ans != nullptr) {
        cout << ans->key << " ";
        node<int> *next = ans->next;
        delete ans;
        ans = next;
    }
}
