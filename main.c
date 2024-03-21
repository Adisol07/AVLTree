#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Neodolal jsem

typedef struct Node {
  int data;
  int height;
  struct Node *left;
  struct Node *right;
} Node;

int height(Node *node) { return (node == NULL) ? 0 : node->height; }
int max(int a, int b) { return (a > b) ? a : b; }
int abs(int x) { return (x >= 0) ? x : x * -1; } // Z mínusu na plus GG

Node *NewNode(int data) { // Stvoření
  Node *node = (Node *)malloc(sizeof(Node)); // Fuj
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

Node *RightRotate(Node *y) {
  Node *x = y->left;
  Node *o = x->right;

  x->right = y;
  y->left = o;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}
Node *LeftRotate(Node *x) {
  Node *y = x->right;
  Node *o = y->left;

  y->left = x;
  x->right = o;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

int GetBalance(Node *node) {
  if (node == NULL)
    return 0;
  return height(node->left) - height(node->right);
}

Node *Insert(Node *node, int data) {
  if (node == NULL)
    return NewNode(data);

  if (data < node->data)
    node->left = Insert(node->left, data);
  else if (data > node->data)
    node->right = Insert(node->right, data);
  else
    return node;

  node->height = max(height(node->left), height(node->right)) + 1;

  int balance = GetBalance(node);

  if (balance > 1 && data < node->left->data)
    return RightRotate(node);

  if (balance < -1 && data > node->right->data)
    return LeftRotate(node);

  if (balance > 1 && data > node->left->data) {
    node->left = LeftRotate(node->left);
    return RightRotate(node);
  }

  if (balance < -1 && data < node->right->data) {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
  }

  return node;
}

void PrintSpaces(int number) {
  for (int i = 0; i < number; i++)
    printf(" ");
}
void RenderLevel(Node *root, int level) {
  if (root == NULL)
    return;

  if (level == 1) {
    printf("%d ", root->data);
  } else if (level > 1) {
    RenderLevel(root->left, level - 1);
    PrintSpaces(height(root->left) * height(root->right)); // Idk ono to začalo fungovat při hovoru XD
    RenderLevel(root->right, level - 1);
  }
}
void Render(Node *root) {
  int maxHeight = height(root);
  for (int i = 1; i <= maxHeight; i++) {
    PrintSpaces(abs(i - maxHeight));
    RenderLevel(root, i);
    printf("\n");
  }
}
int Find(Node *node, int number){
    if (node == NULL)
        return 0;

    if (node->data == number)
        return 1;
    else if (node->data > number)
        return Find(node->left, number);
    else if (node->data < number)
        return Find(node->right, number);
    else
        return 0;
}

void InsertDefaults(Node **root) { // Až moc pointerů na můj vkus
  *root = Insert(*root, 10);
  *root = Insert(*root, 20);
  *root = Insert(*root, 30);
  *root = Insert(*root, 40);
  *root = Insert(*root, 50);
  *root = Insert(*root, 25);
}

int main() {
  Node *root = NULL;

  // InsertDefaults(&root); // Pokud chcete tak si dejte default
  while (1/* Tohle asi radši změnim aby nebyla katastrofa */) {
    Render(root);
    char op;
    printf("\n\nSelect operation: ('f' = Find, 'a' = Add) ");
    scanf(" %c", &op);
    int x;
    printf("Enter number: ");
    scanf("%d", &x);

    if (op == 'a')
        root = Insert(root, x);
    else if (op == 'f'){
        int found = Find(root, x);
        printf("Is the number in the tree? %s\n", (found == 1) ? "Yes" : "No");
    }
  }

  return 0;
}
