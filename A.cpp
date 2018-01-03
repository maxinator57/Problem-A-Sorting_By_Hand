#include <iostream>

using std::cin;
using std::cout;

struct node {
    int key;
    node *next;
    node(int n) {
        key = n;
        next = nullptr;
    }
};

node* merge_lists(node *root1, node *root2) {
    node *start;
    if (root1->key <= root2->key) {
        start = root1;
        root1 = root1->next;
    } else {
        start = root2;
        root2 = root2->next;
    }
    node *cur = start;
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

node* merge_sort(node *root, int sz) {
    if (sz == 1)
        return root;
    int m = sz / 2;
    node *median = root;
    for (int i = 0; i < m - 1; ++i) {
        median = median->next;
    }
    node *median2 = median->next;
    median->next = nullptr;
    return merge_lists(merge_sort(root, m), merge_sort(median2, sz - m));
}

int main() {
    size_t n;
    int a;
    cin >> n >> a;
    node *root = new node(a);
    node *last = root;
    for (size_t i = 1; i < n; ++i) {
        cin >> a;
        node *new_node = new node(a);
        last->next = new_node;
        last = new_node;
    }
    node *ans = merge_sort(root, n);
    while (ans != nullptr) {
        cout << ans->key << " ";
        node *next = ans->next;
        delete ans;
        ans = ans->next;
    }
}
