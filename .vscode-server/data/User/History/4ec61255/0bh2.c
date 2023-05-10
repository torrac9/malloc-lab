#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *nil_node = (node_t *)calloc(1, sizeof(node_t));

  nil_node->color = RBTREE_BLACK;
  p->nil = nil_node;
  p->root = nil_node;

  return p;
}
void FreeNode(rbtree *t, node_t *x){
  //후위 순회 방식
  if (x->left != t->nil) 
    FreeNode(t, x->left);
  if (x->right != t->nil)
    FreeNode(t, x->right);
  free(x);
  x = NULL;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  if (t->root != t->nil){
    FreeNode(t, t->root);
  }
  free(t->nil);
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *y = t->nil;
  node_t *x = t->root;
  node_t *z = (node_t *)calloc(1, sizeof(node_t));
  z->key = key;
  while(x != t->nil){
    y = x;
    if (z->key < x->key){
      x = x->left;
    }
    else{
      x = x->right;
    }
  }
  z->parent = y;
  if (y == t->nil){
    t->root = z;
  }
  else if (z->key < y->key){
    y->left = z;
  }
  else{
    y->right = z;
  }
  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;
  
  while (z->parent->color == RBTREE_RED){
    if (z->parent == z->parent->parent->left){
      y = z->parent->parent->right;   
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else {
        if (z == z->parent->right){
        z = z->parent;
        left_rotate(t, z);
      }
      z->parent->color = RBTREE_BLACK;
      z->parent->parent->color = RBTREE_RED;
      right_rotate(t, z->parent->parent);
      }
    }
    else {
      y = z->parent->parent->left;   
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else {
        if (z == z->parent->left){
          z = z->parent;
          right_rotate(t, z);
        }
      z->parent->color = RBTREE_BLACK;
      z->parent->parent->color = RBTREE_RED;
      left_rotate(t, z->parent->parent);
      }
    }
  }
  return z;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *x = t->root;
  while (x != t->nil && key != x->key){
    if (key < x->key){
      x = x->left;
    }
    else {
      x = x->right;
    }
  }
  if (x == t->nil){
    return NULL;
  }
  return x;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *x = t->root;
  while (x->left != t->nil){
    x = x->left;
  }
  return x;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *x = t->root;
  while (x->right != t->nil){
    x = x->right;
  }
  return x;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  node_t *y = p;
  node_t *x;
  color_t y_original_color = y->color;
  if (p->left == t->nil){
    x = p->right;
    rb_transplant(t, p, p->right);
  }
  else if (p->right == t->nil){
    x = p->left;
    rb_transplant(t, p, p->left);
  }
  else {
    y = rbtree_min(t);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == p){
      x->parent = y;
    }
    else {
      rb_transplant(t, y, y->right);
      y->right = p->right;
      y->right->parent = y;
    }
    rb_transplant(t, p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }
  // RB tree 특성 복구
  if (y_original_color == RBTREE_BLACK){
    while (x != t->root && x->color == RBTREE_BLACK){
      if (x == x->parent->left){
        node_t *w = x->parent->right;
        if (w->color == RBTREE_RED){
          w->color = RBTREE_BLACK;
          x->parent->color = RBTREE_RED;
          left_rotate(t, x->parent);
          w = x->parent->right;
        }
        if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
          w->color = RBTREE_RED;
          x = x->parent;
        }
        else {
          if (w->right->color == RBTREE_BLACK){
            w->left->color = RBTREE_BLACK;
            w->color = RBTREE_RED;
            right_rotate(t, w);
            w = x->parent->right;
          }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root;
        }
      }
      else {
        node_t *w = x->parent->left;
        if (w->color == RBTREE_RED){
          w->color = RBTREE_BLACK;
          x->parent->color = RBTREE_RED;
          right_rotate(t, x->parent);
          w = x->parent->left;
        }
        if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK){
          w->color = RBTREE_RED;
          x = x->parent;
        }
        else {
          if (w->left->color == RBTREE_BLACK){
            w->right->color = RBTREE_BLACK;
            w->color = RBTREE_RED;
            left_rotate(t, w);
            w = x->parent->left;
          }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root;
        }
      }
    }
  }
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}

void left_rotate(rbtree *t, node_t *x){
  // y는 target의 right
  node_t *y = x->right;
  // y의 왼쪽 서브트리를 x의 오른쪽 서브트리로
  x->right = y->left;
  // y의 왼쪽 노드가 NIL이 아니라면, y의 왼쪽 노드의 부모가 target
  if (y->left != t->nil){
    y->left->parent = x;
  }
  // y의 부모 노드를 target의 부모 노드로 설정
  y->parent = x->parent;
  // target의 부모 노드가 NIL이라면, y를 root로 설정
  if (x->parent != t->nil){
    t->root = y;
  }
  // target이 target 부모 노드의 왼쪽이라면, target 부모의 왼쪽을 y
  else if (x == x->parent->left){
    x->parent->left = y;
  }
  // target이 target 부모 노드의 오른쪽이라면, target 부모의 오른쪽을 y
  else {
    x->parent->right = y;
  }
  // target을 y의 왼쪽으로 설정
  y->left = x;
  // target의 부모를 y로 설정
  x->parent = y;
}

void right_rotate(rbtree *t, node_t *x){
  node_t *y = x->left;
  x->left = y->right;
  if (y->right != t->nil){
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent != t->nil){
    t->root = y;
  }
  else if (x == x->parent->right){
    x->parent->right = y;
  }
  else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

void rb_transplant(rbtree *t, node_t *u, node_t *v){
  if (u->parent == t->nil){
    t->root = v;
  }
  else if (u == u->parent->left){
    u->parent->left = v;
  }
  else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

node_t *tree_successor(rbtree *t, node_t *x){
  while (x->left != t->nil){
    x = x->left;
  }
  return x;
}