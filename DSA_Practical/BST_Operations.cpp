#include <iostream>
using namespace std;


struct Node {
    int data;
    Node* left;
    Node* right;    
    Node(int item) {
        data = item;
        left = NULL;
        right = NULL;
    }
};

// A utility function to insert a new node with 
// the given data
Node* insert(Node* root, int data) {
  
    // If the tree is empty, return a new node
    if (root == NULL) 
        return new Node(data);    
    
    // If the data is already present in the tree,
    // return the node
    if (root->data == data) 
        return root;
    
    // Otherwise, recur down the tree. If the data
    // to be inserted is greater than the root's data,
    // insert it in the right subtree
    if (root->data < data) 
        root->right = insert(root->right, data);
    
    // If the data to be inserted is smaller than 
    // the root's data, insert it in the left subtree
    else 
        root->left = insert(root->left, data);
    
    // Return the (unchanged) root pointer
    return root;
}

// Function to search a data in a BST
Node* search(Node* root, int data) {
  
    // Base Cases: root is null or data is present at root
    if (root == NULL || root->data == data)
        return root;

    // Data is greater than root's data
    if (root->data < data)
        return search(root->right, data);

    // Data is smaller than root's data
    return search(root->left, data);
}

// Function to find the inorder successor
Node* getSuccessor(Node* curr) {
    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
        curr = curr->left;
    return curr;
}

// Function to delete a data from the BST and return the modified root
Node* delNode(Node* root, int data) {

    // Base case
    if (root == NULL)
        return root;

    // If the data to be deleted is in a subtree
    if (root->data > data)
        root->left = delNode(root->left, data);
    else if (root->data < data)
        root->right = delNode(root->right, data);

    // If root matches with the given data
    else {

        // Case 1: root has 0 or only right child
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // Case 2: root has only left child
        if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: root has both children
        Node* succ = getSuccessor(root);
        root->data = succ->data;
        root->right = delNode(root->right, succ->data);
    }
    return root;
}

// A utility function to do inorder tree traversal
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Driver program to test the above functions
int main() {
    // Creating the following BST
    //      50
    //     /  \
    //    30   70
    //   / \   / \
    //  20 40 60 80

    Node* root = new Node(50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Print inorder traversal of the BST
    cout << "Inorder traversal of the BST: ";
    inorder(root);
    cout << endl;

    // Searching for a node
    cout << "Searching for 40 in the BST: " << endl;
    if(search(root, 40)){
        cout << "Node 40 found in the BST" << endl;
    } else {
        cout << "Node 40 not found in the BST" << endl;
    }

    // Deleting node 70 (node with 2 children)
    root = delNode(root, 70);
    cout << "Inorder traversal after deleting node 70: ";
    inorder(root);
    cout << endl;

    return 0;
}


