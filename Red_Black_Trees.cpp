//C++ Program to implement red black tree

#include <iostream>
using namespace std;

enum redBlack {red, black};

struct node
{
    int data;
    redBlack colour;
    node* parent;
    node* left;
    node* right;
};

class RedBlackTree
{
protected:
    node* root;
    RedBlackTree() : root(NULL) {}
    bool isLeftChild (node* n)
    {
        return n->parent->left == n;
    }
};

class Rotation : virtual public RedBlackTree
{
protected:
    node* leftRotation(node* A)
    {
        node* B = A->right;
        node* B_left = B->left;
        B->left = A;
        A->parent = B;
        A->right = B_left;
        if (B_left) B_left->parent = A;
        return B;
    }

    node* rightRotation(node* A)
    {
        node* B = A->left;
        node* B_right = B->right;
        B->right = A;
        A->parent = B;
        A->left = B_right;
        if (B_right) B_right->parent = A;
        return B;
    }

    node* leftRightRotation(node*A)
    {
        A->left = leftRotation(A->left);
        A->left->parent = A;
        return rightRotation(A);
    }

    node* rightLeftRotation(node*A)
    {
        A->right->parent = A;
        A->right = rightRotation(A->right);
        return leftRotation(A);
    }
};

class Insertion : public Rotation
{
    node* balanceNode(node* n)
    {
        if (isLeftChild(n))
            if (isLeftChild(n->parent))
                return rightRotation(n->parent->parent);
            else
                return rightLeftRotation(n->parent->parent);
        else
            if (isLeftChild(n->parent))
                return leftRightRotation(n->parent->parent);
            else
                return leftRotation(n->parent->parent);
    }

    node* getNode (int data, node* parent)
    {
        node* newnode = new node;
        newnode->data = data;
        newnode->colour = parent ? red : black;
        newnode->parent = parent;
        newnode->left = newnode->right = NULL;
        return newnode;
    }
    
    void insertionFix (node* n)
    {
        node* parent = n->parent;
        if (!parent || n->parent->colour == black)     return;
        
        node* grandparent = parent->parent;
        node* uncle = (isLeftChild(parent)) ? grandparent->right : grandparent->left;
        if (!uncle || uncle->colour == black)
        {
            if (grandparent == root)
            {
                root = balanceNode(n);
                root->parent = NULL;
                root->colour = black;
                root->left->colour = root->right->colour = red;
                return;
            }
            node* greatgrandparent = grandparent->parent;
            if (isLeftChild(grandparent)) 
            {
                greatgrandparent->left = balanceNode(n);
                greatgrandparent->left->parent = greatgrandparent;
                greatgrandparent->left->colour = black;
                greatgrandparent->left->left->colour = greatgrandparent->left->right->colour = red;
            }
            else
            {
                greatgrandparent->right = balanceNode(n);
                greatgrandparent->right->parent = greatgrandparent;
                greatgrandparent->right->colour = black;
                greatgrandparent->right->left->colour = greatgrandparent->right->right->colour = red;
            }
        }
        else
        {
            parent->colour = uncle->colour = black;
            if (grandparent != root)
            {
                grandparent->colour = red;
                insertionFix (grandparent);
            }
        }
    }

protected:
    void insertNode (node* parent, node* grandparent, int data, bool isLeft = true)
    {
        if (!parent)
        {
            node* newnode = getNode (data, grandparent);
            if (grandparent)
                if (isLeft) grandparent->left = newnode;
                else    grandparent->right = newnode;
            else    root = newnode;
            insertionFix (newnode);
            cout << data << " is successfully inserted\n";
        }
        else if (parent->data > data)
            insertNode (parent->left, parent, data, true);
        else if (parent->data < data)
            insertNode (parent->right, parent, data, false);
        else
            cout << "Node already exist!!\n";
    }
};

class Deletion : public Rotation
{
    void swapColour (node* A, node* B)
    {
        redBlack temp = A->colour;
        A->colour = B->colour;
        B->colour = temp;
    }

    void rotateParentTowardsDoubleBlack (node *n, node *sibling)
    {
        swapColour(n->parent, sibling);
        node* grandparent = n->parent->parent;
        if (isLeftChild(n->parent)) 
        {
            grandparent->left = isLeftChild(n) ? leftRotation (n->parent) : rightRotation(n->parent);
            grandparent->left->parent = grandparent;
        }
        else
        {
            grandparent->right = isLeftChild(n) ? leftRotation (n->parent) : rightRotation(n->parent);
            grandparent->right->parent = grandparent;
        }
    }

    void doubleBlackFix (node* n)
    {
        if (n == root)  return;

        node *sibling, *sibling_far_child, *sibling_near_child;
        if (isLeftChild(n))
        {
            sibling = n->parent->right;
            sibling_far_child = sibling->right;
            sibling_near_child = sibling->left;
        }
        else
        {
            sibling = n->parent->left;
            sibling_far_child = sibling->left;
            sibling_near_child = sibling->right;
        }

        if (sibling->colour == red)
        {
            rotateParentTowardsDoubleBlack(n, sibling);
            doubleBlackFix(n);
        }
        else if ((!sibling_far_child || sibling_far_child->colour == black) && (!sibling_near_child || sibling_near_child->colour == black))
        {
            sibling->colour = red;
            if (n->parent->colour == red)
                n->parent->colour = black;
            else    doubleBlackFix(n->parent);
        }
        else if (!sibling_far_child || sibling_far_child->colour == black)
        {
            swapColour(sibling, sibling_near_child);
            if (isLeftChild(sibling)) 
            {
                n->parent->left = isLeftChild(n) ? rightRotation (sibling) : leftRotation(sibling);
                n->parent->left->parent = n->parent;
            }
            else
            {
                n->parent->right = isLeftChild(n) ? rightRotation (sibling) : leftRotation(sibling);
                n->parent->right->parent = n->parent;
            }
            doubleBlackFix(n);
        }
        else
        {
            rotateParentTowardsDoubleBlack(n, sibling);
            sibling_far_child->colour = black;
        }
    }

protected:
    void deleteNode (node* parent, int data)
    {
        if (!parent)
            cout << "Node does not exist!!\n";

        else if (parent->data > data)
            deleteNode (parent->left, data);
        else if (parent->data < data)
            deleteNode (parent->right, data);
        else
        {
            // Delete node with no child
            if (!parent->left && !parent->right)
            {
                if (parent->colour == black)
                    doubleBlackFix (parent);
                if (parent == root)
                    root = NULL;
                else
                    isLeftChild(parent) ? parent->parent->left = NULL : parent->parent->right = NULL;
                delete parent;
                cout << "Node is successfully deleted\n";
            }

            // Delete node with one child       parent -> black, child -> red
            else if (!parent->left)
            {
                parent->data = parent->right->data;
                delete parent->right;
                parent->right = NULL;
                cout << "Node is successfully deleted\n";
            }
            else if (!parent->right)
            {
                parent->data = parent->left->data;
                delete parent->left;
                parent->left = NULL;
                cout << "Node is successfully deleted\n";
            }

            // Delete node with two children using inorder successor
            else
            {
                node* temp = parent->right;
                while (temp->left != NULL)
                    temp = temp->left;
                parent->data = temp->data;
                deleteNode (parent->right, parent->data);
            }
        }
    }
};

class Display : virtual public RedBlackTree
{
    int twoPowerX (int x)
    {
        int result = 1;
        for (int i = 1; i <= x; i++)
            result *= 2;
        return result;
    }

    int getHeight (node* A)
    {
        if (A == NULL)
            return 0;
        int l_height = getHeight (A->left);
        int r_height = getHeight (A->right);
        return 1 + (l_height > r_height ? l_height : r_height);
    }

    void printColour (node* n)
    {
        if (n->colour == red) cout << 'R';
        else if (n->colour == black) cout << 'B';
    }

    void printCurrentLevel (node* parent, int level, int space)
    {
        if (!parent)
        {
            int n = twoPowerX(level - 1);
            for (int i = 0; i < n; i++)
            {
                cout << " * ";
                for (int i = 1; i < space; i++)
                    cout<< "   ";
            }
        }
        else if (level == 1)
        {
            printColour (parent);
            if (parent->data >= 0 && parent->data / 10 == 0) cout << 0;
            cout << parent->data;
            for (int i = 1; i < space; i++)
                cout<< "   ";
        }
        else if (level > 1)
        {
            printCurrentLevel (parent->left, level - 1, space);
            printCurrentLevel (parent->right, level - 1, space);
        }
    }

protected:
    void display()
    {
        if (!root)
        {
            cout << "Tree is Empty!!\n";
            return;
        }

        int height = getHeight (root);
        int space = twoPowerX (height);
        for (int level = 1; level <= height; level++)
        {
            for (int i = 1; i < space/2; i++)
                cout << "   ";
            printCurrentLevel (root, level, space);
            cout << endl;
            space /= 2;
        }
    }
};

class SearchAndTraversal : virtual public RedBlackTree
{
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

protected:
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

class Menu : public Insertion, public Deletion, public Display, public SearchAndTraversal
{
public:
    Menu()
    {
        while(true)
        {
            int choice = 0;
            cout << "\nSelect any operation in the Red Black Tree-\n";
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
                    insertNode(root, NULL, data);
                    break;
                }
                case 2:
                {
                    int data;
                    cout << "Enter the data value to be deleted: ";
                    cin >> data;
                    deleteNode(root, data);
                    break;
                }
                case 3:
                {
                    int data;
                    cout << "Enter the data value to be searched: ";
                    cin >> data;
                    searchNode(root, data);
                    break;
                }
                case 4:
                {
                    display();
                    break;
                }
                case 5:
                {
                    traverse();
                    break;
                }
                default:
                {
                    cout << "Invalid Number!!\nEnter numbers from 1 to 6\n";
                    break;
                }
            }
        }
    }
};

int main()
{
    Menu red_black_tree;
    return 0;
}