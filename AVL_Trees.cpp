//C++ Program to perform AVL Rotations

#include <iostream>
using namespace std;

class node
{
private:
    int data;
    node *left, *right;
    friend class AVL_Tree;
};

class AVL_Tree
{
private:
    node* getnode(int data)
    {
        node* newnode = new node;
        newnode->data = data;
        newnode->left = newnode->right = NULL;
        return newnode;
    }

    int getHeight(node* A)
    {
        if (A == NULL)
            return 0;
        int l_height = getHeight (A->left);
        int r_height = getHeight (A->right);
        return 1 + (l_height > r_height ? l_height : r_height);
    }

    int getBalanceFactor(node* A)
    {
        return A ? (getHeight(A->left) - getHeight(A->right)) : 0;
    }

    node* leftRotation(node* A)
    {
        node* B = A->right;
        node* B_left = B->left;
        B->left = A;
        A->right = B_left;
        return B;
    }

    node* rightRotation(node* A)
    {
        node* B = A->left;
        node* B_right = B->right;
        B->right = A;
        A->left = B_right;
        return B;
    }

    node* leftRightRotation(node*A)
    {
        A->left = leftRotation(A->left);
        return rightRotation(A);
    }

    node* rightLeftRotation(node*A)
    {
        A->right = rightRotation(A->right);
        return leftRotation(A);
    }

    node* balanceNode(node* A)
    {
        int balance_factor = getBalanceFactor(A);
        if (balance_factor > 1)
        {
            if (getBalanceFactor(A->left) >= 0)
                return rightRotation(A);
            else
                return leftRightRotation(A);
        }
        else if (balance_factor < -1)
        {
            if (getBalanceFactor(A->right) <= 0)
                return leftRotation(A);
            else
                return rightLeftRotation(A);
        }
        else    return A;
    }

    void printCurrentLevel (node* parent, int level, int space)
    {
        if (parent == NULL)
        {
            int n = twoPowerX(level - 1);
            for (int i = 0; i < n; i++)
            {
                cout << "**";
                for (int i = 1; i < space; i++)
                    cout<< "  ";
            }
        }
        else if (level == 1)
        {
            if (parent->data >= 0 && parent->data / 10 == 0) cout << 0;
            cout << parent->data;
            for (int i = 1; i < space; i++)
                cout<< "  ";
        }
        else if (level > 1)
        {
            printCurrentLevel (parent->left, level - 1, space);
            printCurrentLevel (parent->right, level - 1, space);
        }
    }

    int twoPowerX(int x)
    {
        int result = 1;
        for (int i = 1; i <= x; i++)
            result *= 2;
        return result;
    }

    void preorderTraversal (node* root)
    {
        if (!root)  return;
        cout << root->data << " ";
        preorderTraversal (root->left);
        preorderTraversal (root->right);
    }

    void inorderTraversal (node* root)
    {
        if (!root)  return;
        inorderTraversal (root->left);
        cout << root->data << " ";
        inorderTraversal (root->right);
    }

    void postorderTraversal (node* root)
    {
        if (!root)  return;
        postorderTraversal (root->left);
        postorderTraversal (root->right);
        cout << root->data << " ";
    }

public:
    node* root;
    AVL_Tree() : root(NULL) {}

    node* insertNode (node* parent, int data)
    {
        if (!parent)
        {
            cout << data << " is successfully inserted\n";
            return getnode (data);
        }
        else if (parent->data > data)
            parent->left = insertNode (parent->left, data);
        else if (parent->data < data)
            parent->right = insertNode (parent->right, data);
        else
        {
            cout << "Node already exist!!\n";
            return parent;
        }
        return balanceNode (parent);
    }

    node* deleteNode (node* parent, int data)
    {
        if (!parent)
        {
            cout << "Node does not exist!!\n";
            return NULL;
        }
        else if (parent->data > data)
            parent->left = deleteNode (parent->left, data);
        else if (parent->data < data)
            parent->right = deleteNode (parent->right, data);
        else
        {
            node* temp = parent;
            // Delete node with one or no child
            if (!parent->left || !parent->right)
            {
                parent = !parent->left ? parent->right : parent->left;
                delete temp;
                cout << "Node is successfully deleted\n";
            }

            // Delete node with two children using inorder successor
            else
            {
                temp = parent->right;
                while (temp->left != NULL)
                    temp = temp->left;
                parent->data = temp->data;
                parent->right = deleteNode (parent->right, parent->data);
            }
        }
        return balanceNode (parent);
    }

    void searchNode (node* parent, int data)
    {
        if (!parent)
            cout << data << " is not found!!\n";
        else if (parent->data > data)
            searchNode (parent->left, data);
        else if (parent->data < data)
            searchNode (parent->right, data);
        else
            cout << data << "is found successfully\n";
    }

    void display()
    {
        int height = getHeight (root);
        int space = twoPowerX (height);
        for (int i = 1; i <= height; i++)
        {
            for (int j = 1; j < space/2; j++)
                cout << "  ";
            printCurrentLevel (root, i, space);
            cout << endl;
            space /= 2;
        }
    }

    void traverse()
    {
        cout << "Preorder Traversal - ";
        preorderTraversal (root);
        cout << "\nInorder Traversal - ";
        inorderTraversal (root);
        cout << "\nPostorder Traversal - ";
        postorderTraversal (root);
        cout << endl;
    }
};

int main()
{
    AVL_Tree tree;
    while(true)
    {
        int choice = 0;
        cout << "\nSelect any operation in the AVL Tree-\n";
        cout << "1- Insertion\t2- Deletion\t3- Searhing\t4- Display\t5- Traversal\t6- Exit\n";
        cin >> choice;
        if (choice == 6) break;
        switch(choice)
        {
            case 1:
            {
                int data;
                cout << "Enter the data value to be inserted: ";
                cin >> data;
                tree.root = tree.insertNode(tree.root, data);
                break;
            }
            case 2:
            {
                int data;
                cout << "Enter the data value to be deleted: ";
                cin >> data;
                tree.root = tree.deleteNode(tree.root, data);
                break;
            }
            case 3:
            {
                int data;
                cout << "Enter the data value to be searched: ";
                cin >> data;
                tree.searchNode(tree.root, data);
                break;
            }
            case 4:
            {
                tree.display();
                break;
            }
            case 5:
            {
                tree.traverse();
                break;
            }
            default:
            {
                cout << "Invalid Number!!\nEnter numbers from 1 to 6\n";
                break;
            }
        }
    }
    return 0;
}