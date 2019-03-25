#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1

typedef struct node {
    int value;
    int color;
    int countLeftChild;
    int countRightChild;
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
        node->countRightChild += 1;
    }
    else {
        node->left = insertNodeInBST(node->left, newNode);
        node->left->parent = node; 
        node->countLeftChild += 1;
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
                    if(nodeParent->right)
                        nodeGrandParent->countLeftChild = nodeParent->right->countLeftChild + nodeParent->right->countRightChild + 1;
                    else
                        nodeGrandParent->countLeftChild = 0;
                    nodeParent->right = nodeGrandParent;
                    nodeParent->countRightChild = nodeGrandParent->countRightChild +
                                                                nodeGrandParent->countLeftChild + 1;
                    nodeGrandParent->color = RED;
                    nodeParent->color = BLACK;
                    
                    if(nodeGrandParent == root) {
                        root = nodeParent;
                        nodeGrandParent->parent = root;
                        root->parent = NULL;
                    }
                    else {
                        Node *temp = nodeGrandParent->parent;
                        if(nodeGrandParent->parent->left == nodeGrandParent) {
                            temp->left = nodeParent;
                            temp->countLeftChild = nodeParent->countLeftChild + nodeParent->countRightChild + 1;
                        }
                        else {
                            temp->right = nodeParent;
                            temp->countRightChild = nodeParent->countLeftChild + nodeParent->countRightChild + 1;
                        }
                        nodeGrandParent->parent = nodeParent;
                        nodeParent->parent = temp;
                    }
                }
                //When uncle is not RED and the case is left right
                else {
                    nodeParent->right = newNode->left;
                    if(newNode->left)
                        nodeParent->countRightChild = newNode->left->countRightChild + newNode->left->countLeftChild+1;
                    else
                        nodeParent->countRightChild=0;
                    newNode->left = nodeParent;
                    newNode->countLeftChild = nodeParent->countRightChild + nodeParent->countLeftChild+1;
                    nodeGrandParent->left = newNode;
                    nodeGrandParent->countLeftChild = newNode->countLeftChild + newNode->countRightChild+1;
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
                    if(nodeParent->left)
                        nodeGrandParent->countRightChild = nodeParent->left->countLeftChild + nodeParent->left->countRightChild + 1;
                    else
                        nodeGrandParent->countRightChild = 0;
                    nodeParent->left = nodeGrandParent;
                    nodeParent->countLeftChild = nodeGrandParent->countRightChild +
                                                                nodeGrandParent->countLeftChild+1;
                    nodeGrandParent->color = RED;
                    nodeParent->color = BLACK;
                    if(nodeGrandParent == root) {
                        root = nodeParent;
                        nodeGrandParent->parent = root;
                        root->parent = NULL;
                    }
                    else {
                        Node *temp = nodeGrandParent->parent;
                        if(nodeGrandParent->parent->left == nodeGrandParent) {
                            temp->left = nodeParent;
                            temp->countLeftChild = nodeParent->countLeftChild + nodeParent->countRightChild + 1;
                        }
                        else {
                            temp->right = nodeParent;
                            temp->countRightChild = nodeParent->countLeftChild + nodeParent->countRightChild + 1;
                        }
                        nodeGrandParent->parent = nodeParent;
                        nodeParent->parent = temp;
                    }
                }
                //When uncle is not RED and the case is right left
                else {
                    nodeParent->left = newNode->right;
                    if(newNode->right)
                        nodeParent->countLeftChild = newNode->right->countRightChild + newNode->right->countLeftChild+1;
                    else
                        nodeParent->countLeftChild=0;
                    newNode->right = nodeParent;
                    newNode->countRightChild = nodeParent->countRightChild + nodeParent->countLeftChild+1;
                    nodeGrandParent->right = newNode;
                    nodeGrandParent->countRightChild = newNode->countLeftChild + newNode->countRightChild+1;
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

/*void preorderTraversal(Node *node) {
    if(node != NULL) {
        printf("%d ", node->value);
        printf("%d %d", node->countLeftChild, node->countRightChild);
        printf("\n");
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}*/

int findNodeAtGivenIndex(Node *root, int index, int before) {
    if(root) {
        if(before + root->countLeftChild < index)
            return findNodeAtGivenIndex(root->right, index, before+root->countLeftChild+1);
        else if(before + root->countLeftChild > index)
            return findNodeAtGivenIndex(root->left, index, before);
        else
            return root->value;
    }
    else
        return -1;
}

Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->color = RED;
    newNode->countLeftChild = 0;
    newNode->countRightChild = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

int main(void) {
	int val,n,count;
	Node *temp;
	scanf("%d", &n);
	count=0;
	for(int i=0;i<n;i++) {
	    scanf("%d", &val);
	    temp = createNode(val);
	    insertNodeInRedBlackTree(root, temp);
	    count++;
	    if(count%2)
	        printf("%d\n", findNodeAtGivenIndex(root, count/2, 0));
	    else {
	       int val1 = findNodeAtGivenIndex(root, count/2-1, 0);
	       int val2 = findNodeAtGivenIndex(root, count/2, 0);
	       printf("%d\n", (val1+val2)/2);
	    }
	}
	//preorderTraversal(root);
	return 0;
}
