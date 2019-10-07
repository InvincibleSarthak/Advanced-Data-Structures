//AVL TREES (insertion and deletion)

#include <iostream>
using namespace std;
struct Node{
    int key;
    Node* left;
    Node* right;
    int height;
};

int height (Node* node){
    if(node == NULL){
        return 0;
    }
    return node->height;
}

int getBalanceFactor( Node* node){
    if (node == NULL){
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node* leftRotate(Node* node){
    Node* y = node->right;
    Node* z = y->left;

    y->left = node;
    node->right = z;

    y->height = 1 + max(height(y->left),height(y->right));
    node->height = 1 + max(height(node->left) , height(node->right));

    return y;
}

Node* rightRotate(Node* node){
    Node* y = node->left;
    Node* z = y->right;

    y->right = node;
    node->left = z;

    y->height = 1 + max(height(y->left),height(y->right));
    node->height = 1 + max(height(node->left) , height(node->right));

    return y;
}

Node* insertNode( Node* node, int a ){
    if(node == NULL){
        Node* root = new Node();
        root->key = a;
        root->right = NULL;
        root->left = NULL;
        root->height = 1;
        return root;
    }
    if( a < node->key ) node->left = insertNode(node->left,a);
    else if( a > node->key )    node->right = insertNode(node->right,a);
    else return node;
    node->height = 1 + max(height(node->right), height(node->left));
    int balFactor = getBalanceFactor(node);
    if (balFactor > 1 && a < node->left->key){ //right rotation
        cout<<node->key<<'\n';
        return rightRotate(node);
    }
    else if (balFactor > 1 && a > node->left->key){ // right left rotation
        cout<<node->key<<'\n';
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    else if (balFactor < -1 && a < node->right->key){ // left right rotation
        cout<<node->key<<'\n';
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    else if(balFactor < -1 && a > node->right->key){ // left rotation
        cout<<node->key<<'\n';
        return leftRotate(node);
    }
    return node;
}

Node* inOrderSuccessor(Node* node) {
    Node* current = node;
    while(current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node* deleteNode(Node* node, int a) {
    if(node == NULL) return node;
    if(a < node->key){
        node->left = deleteNode(node->left,a);
    }
    else if(a > node->key) {
        node->right = deleteNode(node->right,a);
    }
    else {
        if(node->left == NULL || node->right == NULL) {
            if(node->left == NULL && node->right == NULL) {
                delete(node);
            }
            else {
                Node* temp = node;
                if(node->left) {
                    temp = node->left;
                }
                else {
                    temp = node->right;
                }
                node = temp;
                delete(temp);
            } 
        }
        else {
            Node* temp = inOrderSuccessor(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right,temp->key);
        }
    }
    if(node == NULL) return node;
    node->height = 1 + max(height(node->left),height(node->right));
    int balFactor = getBalanceFactor(node);
    if(balFactor > 1 && getBalanceFactor(node->left)  < 0) {
        cout<<node->key<<'\n';
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    else if(balFactor > 1 && getBalanceFactor(node->left) >= 0) {
        cout<<node->key<<'\n';
        return rightRotate(node);
    }
    else if(balFactor < -1 && getBalanceFactor(node->right) > 0) {
        cout<<node->key<<'\n';
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    else if(balFactor < -1 && getBalanceFactor(node->right) <= 0) {
        cout<<node->key<<'\n';
        return leftRotate(node);
    }
    return node;
}

void preOrder(Node* node){
    if(node != NULL){
        cout<<node->key<<' ';
        preOrder(node->left);
        preOrder(node->right);
    }
}

void inOrder(Node* node){
    if(node != NULL){
        inOrder(node->left);
        cout<<node->key<<' ';
        inOrder(node->right);
    }
}

void postOrder(Node* node){
    if(node != NULL){
        postOrder(node->left);
        postOrder(node->right);
        cout<<node->key<<' ';
    }
}
int main() {
    int n;
    cin>>n;
    Node* root = NULL;
    while(n--){
        char c;
        int a;
        cin>>c>>a;
        if (c == 'i'){
            root = insertNode(root,a);
        }
        else if (c == 'd'){
            root = deleteNode(root,a);
        }
    }
    preOrder(root);
    cout<<'\n';
    inOrder(root);
    cout<<'\n';
    postOrder(root);
    cout<<'\n';

}
