#include "tree.h"
#include "../request/request.h"
#include <QVector>
#include "node.h"

tree::tree() {
    root = NULL;
}

tree::~tree() {
    destroy_tree();
}

void tree::destroy_tree(node *leaf){
    if(leaf!=NULL){
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void tree::insert(QString name, node *leaf)
{
      //leaf->left=new node;
      //leaf->left->key_value=key;
      //leaf->left->left=NULL;    //Sets the left child of the child node to null
      //leaf->left->right=NULL;   //Sets the right child of the child node to null
}

node *tree::search(QString name, node *leaf)
{
  if(leaf!=NULL)
  {
    if(name==leaf->name)
      return leaf;
    if(name<leaf->name)
      return search(name, leaf->left);
    else
      return search(name, leaf->right);
  }
  else return NULL;
}

node *tree::search(QString name)
{
  return search(name, root);
}

void tree::insert(QString name)
{
  if(root!=NULL)
    insert(name, root);
  else
  {
    root=new node;
    root->name = name;
    root->left=NULL;
    root->right=NULL;
  }
}

void tree::destroy_tree()
{
  destroy_tree(root);
}
