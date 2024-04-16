#include <iostream>
#include <Windows.h>
using namespace std;
template <class T>
class BST {
public:
    class treeNode {
    public:
        T data;
        treeNode* left;
        treeNode* right;
        treeNode* parent;
    };
    treeNode* root;
    BST() {
        root = nullptr;
    }
    void insert(T val) {
        treeNode* tempNode = createTreeNode(val);
        insertHelper(root, tempNode);
    }
    void insertHelper(treeNode* y, treeNode* x) {
        root = y;
        if (y == nullptr) {
            y = x;
            root = y;
        }
        else {
            treeNode* w = nullptr;
            while (y) {
                w = y;
                if (x->data < y->data)
                    y = y->left;
                else
                    y = y->right;
            }
            if (w->data > x->data)
                w->left = x;
            else
                w->right = x;
            x->parent = w;
        }
    }
    bool DeleteNode(T d) {
        treeNode* temp = root;
        while (temp != nullptr) {
            if (temp->data == d) {
                if (temp->left == nullptr && temp->right == nullptr) {
                    if (temp->parent->left == temp) {
                        temp->parent->left = nullptr;
                    }
                    else {
                        temp->parent->right = nullptr;
                    }
                    delete temp;
                    cout << "Deleted." << endl;
                    return true;
                }
                else if (temp->left == nullptr) {
                    if (temp->parent->left == temp) {
                        temp->parent->left = temp->right;
                    }
                    else {
                        temp->parent->right = temp->right;
                    }
                    delete temp;
                    cout << "Deleted." << endl;
                    return true;
                }
                else if (temp->right == nullptr) {
                    if (temp->parent->left == temp) {
                        temp->parent->left = temp->left;
                    }
                    else {
                        temp->parent->right = temp->left;
                    }
                    delete temp;
                    cout << "Deleted." << endl;
                    return true;
                }
                else {
                    treeNode* temp2 = temp->right;
                    while (temp2->left != nullptr) {
                        temp2 = temp2->left;
                    }
                    temp->data = temp2->data;
                    if (temp2->parent->left == temp2) {
                        temp2->parent->left = temp2->right;
                    }
                    else {
                        temp2->parent->right = temp2->right;
                    }
                    delete temp2;
                    cout << "Deleted." << endl;
                    return true;
                }
            }
            else if (temp->data > d) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }
        cout << "Not Deleted." << endl;
        return false;
    }
    void inorder(treeNode* root){
        if (root == nullptr) {
            return;
        }
        inorder(root->left);
        cout << " -> " << root->data;
        inorder(root->right);
    }
    int KthSmallestElement(int k) {
        int count = 0;
        treeNode* temp = root;
        while (temp != nullptr) {
            if (temp->left == nullptr) {
                count++;
                if (count == k) {
                    return temp->data;
                }
                temp = temp->right;
            }
            else {
                treeNode* pre = temp->left;
                while (pre->right != nullptr && pre->right != temp) {
                    pre = pre->right;
                }
                if (pre->right == nullptr) {
                    pre->right = temp;
                    temp = temp->left;
                }
                else {
                    pre->right = nullptr;
                    count++;
                    if (count == k) {
                        return temp->data;
                    }
                    temp = temp->right;
                }
            }
        }
        return -1;
    }
    treeNode* createTreeNode(T Dat) {
        treeNode* ptr = new treeNode();
        ptr->data = Dat;
        ptr->left = nullptr;
        ptr->right = nullptr;
        ptr->parent = nullptr;
        return ptr;
    }
    int CountNodes(treeNode* r) {
        if (r == NULL)
            return 0;

        int res = 0;
        if (r->left && r->right)
            res++;

        res += (CountNodes(r->left) + CountNodes(r->right));
        return res;
    }
    void Preorder(treeNode* r){
        if (r == NULL)
            return;
        cout << " -> " << r->data;
        Preorder(r->left);
        Preorder(r->right);
    }
    void PrintPreOrder() {
        cout << "PreOrder " << endl;
        cout << "Data";
        Preorder(root);
    }
    bool printLevel(treeNode* root, int level){
        if (root == nullptr) {
            return false;
        }
        if (level == 1)
        {
            cout << " -> " << root->data;
            return true;
        }
        bool left = printLevel(root->left, level - 1);
        bool right = printLevel(root->right, level - 1);
        return left || right;
    }
    void levelOrderTraversal(treeNode* root){
        int level = 1;
        while (printLevel(root, level)) {
            level++;
        }
    }
    int Height(treeNode* root) {
        if (root == NULL) {
            return 0;
        }
        else {
            int l = Height(root->left);
            int r = Height(root->right);
            if (l > r)
                return (l + 1);
            else
                return (r + 1);
        }
    }
    void Print() {
        if (root == nullptr) {
            cout << endl;
            return;
        }
        cout << endl;
        cout << "Tree Nodes Before Deletion";
        cout << endl << endl;
        cout << "Data";
        inorder(root);
        cout << endl;
        cout << endl;
        cout << "Level Order Traversal";
        levelOrderTraversal(root);
        cout << endl;
        cout << "Total Nodes : ";
        cout << CountNodes(root);
        cout << endl;
        cout << "Height Of Tree : " << Height(root);
        cout << endl;
    }
    void PrintInorder() {
        cout << "Data";
        inorder(root);
    }
};

int main() {
    BST<int> l;
    l.insert(4);
    l.insert(1);
    l.insert(9);
    l.insert(7);
    l.insert(2);
    l.insert(8);
    l.insert(6);
    l.insert(3);
    l.insert(5);
    l.Print();
    cout << "Kth Smallest Element : ";
    cout << l.KthSmallestElement(7) << endl << endl;
    cout << "Tree Nodes After Deletion : ";
    cout << l.DeleteNode(3);
    cout << endl;
    cout << endl;
    cout << endl;
    //l.PrintInorder();
    cout << endl << endl;
    cout << endl;
    return 0;
}