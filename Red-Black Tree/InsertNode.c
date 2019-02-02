#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1

typedef struct node {
    int value;
    int color;
    struct node *left;
    struct node *right;
    struct node *parent;
} Node;

Node *root = NULL;

Node* insertNodeInBST(Node *node, Node *newNode) {
    if(node == NULL) {
        return newNode;
    }
    else if(node->value < newNode->value) {
        node->right = insertNodeInBST(node->right, newNode);
        node->right->parent = node; 
    }
    else {
        node->left = insertNodeInBST(node->left, newNode);
        node->left->parent = node; 
    }
    
    return node;
}

void insertNodeInRedBlackTree(Node *node, Node *newNode) {
    root = insertNodeInBST(node, newNode);
    if(root == newNode) {
        root->color = BLACK;
        return;
    }
    Node *nodeParent = newNode->parent;
    Node *nodeGrandParent = nodeParent->parent;
    
    while(nodeParent->color != BLACK && newNode != root) {
        if(nodeGrandParent->left == nodeParent) {
            //When uncle's color is RED
            if(nodeGrandParent->right != NULL && nodeGrandParent->right->color == RED) {
                nodeParent->color = BLACK;
                nodeGrandParent->right->color = BLACK;
                nodeGrandParent->color = RED;
                newNode = nodeGrandParent;
            }
            else {
                //When uncle is not RED and the case is left left
                if(nodeParent->left == newNode) {
                    nodeGrandParent->left = nodeParent->right;
                    nodeParent->right = nodeGrandParent;
                    nodeGrandParent->color = RED;
                    nodeParent->color = BLACK;
                    
                    if(nodeGrandParent == root) {
                        root = nodeParent;
                        nodeGrandParent->parent = root;
                        root->parent = NULL;
                    }
                    else {
                        Node *temp = nodeGrandParent->parent;
                        if(nodeGrandParent->parent->left == nodeGrandParent)
                            temp->left = nodeParent;
                        else
                            temp->right = nodeParent;
                        nodeGrandParent->parent = nodeParent;
                        nodeParent->parent = temp;
                    }
                }
                //When uncle is not RED and the case is left right
                else {
                    nodeParent->right = newNode->left;
                    newNode->left = nodeParent;
                    nodeGrandParent->left = newNode;
                    nodeParent->parent = newNode;
                    newNode->parent = nodeGrandParent;
                    newNode = nodeParent;
                }
            }
        }
        else {
            //When uncle's color is RED
            if(nodeGrandParent->left != NULL && nodeGrandParent->left->color == RED) {
                nodeParent->color = BLACK;
                nodeGrandParent->left->color = BLACK;
                nodeGrandParent->color = RED;
                newNode = nodeGrandParent;
            }
            else {
                //When uncle is not RED and the case is right right
                if(nodeParent->right == newNode) {
                    nodeGrandParent->right = nodeParent->left;
                    nodeParent->left = nodeGrandParent;
                    nodeGrandParent->color = RED;
                    nodeParent->color = BLACK;
                    
                    if(nodeGrandParent == root) {
                        root = nodeParent;
                        nodeGrandParent->parent = root;
                        root->parent = NULL;
                    }
                    else {
                        Node *temp = nodeGrandParent->parent;
                        if(nodeGrandParent->parent->left == nodeGrandParent)
                            temp->left = nodeParent;
                        else
                            temp->right = nodeParent;
                        nodeGrandParent->parent = nodeParent;
                        nodeParent->parent = temp;
                    }
                }
                //When uncle is not RED and the case is right left
                else {
                    printf("Inside\n");
                    printf("%d\n", newNode->value);
                    nodeParent->left = newNode->right;
                    newNode->right = nodeParent;
                    nodeGrandParent->right = newNode;
                    nodeParent->parent = newNode;
                    newNode->parent = nodeGrandParent;
                    newNode = nodeParent;
                }
            }
        }
        if(newNode == root) {
            newNode -> color = BLACK;
            break;
        }
        else {
            nodeParent = newNode->parent;
            nodeGrandParent = nodeParent->parent;
        }
    }
}

void preorderTraversal(Node *node) {
    if(node != NULL) {
        printf("%d ", node->value);
        printf("%d ", node->color);
        printf("\n");
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->color = RED;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

int main(void) {
	int val;
	Node *temp;
	for(int i=0;i<11;i++) {
	    printf("Enter node's value\n");
	    scanf("%d", &val);
	    temp = createNode(val);
	    insertNodeInRedBlackTree(root, temp);
	}
	printf("Preorder traversal of generated Red-Black tree\n");
	printf("--------------------------------------------------\n");
	preorderTraversal(root);
	return 0;
}

