#include "ShowCatalog.hpp"

#include <iostream>

#include <string>

#include <fstream>

#include <sstream>

using namespace std;

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::ShowCatalog() {
  root = nullptr;
}

/* Completed functions. DO NOT MODIFY*/
void destroyNode(ShowItem * current) {
  if (current != nullptr) {
    destroyNode(current -> left);
    destroyNode(current -> right);

    delete current;
    current = nullptr;
  }
}

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::~ShowCatalog() {
  destroyNode(root);
}

/* Completed functions. DO NOT MODIFY*/
void printShowHelper(ShowItem * m) {
  if (m != nullptr) {
    cout << "Show: " << m -> title << " " << m -> userRating << endl;
    printShowHelper(m -> left);
    printShowHelper(m -> right);
  }
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::printShowCatalog() {
  if (root == nullptr) {
    cout << "Tree is Empty. Cannot print" << endl;
    return;
  }
  printShowHelper(root);
}

/* Completed functions. DO NOT MODIFY*/
ShowItem * getShowHelper(ShowItem * current, string title) {
  if (current == NULL)
    return NULL;

  if (current -> title == title)
    return current;

  if (current -> title > title)
    return getShowHelper(current -> left, title);

  return getShowHelper(current -> right, title);
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::getShow(string title) {
  ShowItem * node = getShowHelper(root, title);
  if (node != nullptr) {
    cout << "Show Info:" << endl;
    cout << "==================" << endl;
    cout << "Title :" << node -> title << endl;
    cout << "Year :" << node -> year << endl;
    cout << "Show Rating :" << node -> showRating << endl;
    cout << "User Rating :" << node -> userRating << endl;
    return;
  }

  cout << "Show not found." << endl;
}

/* Completed functions. DO NOT MODIFY*/
ShowItem * addNodeHelper(ShowItem * current, ShowItem * newNode) {
  if (current == nullptr) {
    return newNode;
  }

  if (current -> title > newNode -> title) {
    current -> left = addNodeHelper(current -> left, newNode);
  } else {
    current -> right = addNodeHelper(current -> right, newNode);
  }

  return current;
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::addShowItem(string title, int year, string showRating, float userRating) {
  if (root == nullptr) {
    root = new ShowItem(title, year, showRating, userRating);
    return;
  }

  root = addNodeHelper(root, new ShowItem(title, year, showRating, userRating));
}

void reinsertChildren(ShowCatalog * catalog, ShowItem * root, ShowItem * node) {
  if (node == nullptr || root == nullptr) return;
  // Assuming this is removed from the tree
  bool validLeft = (node -> left != NULL);
  bool validRight = (node -> right != NULL);
  ShowItem * ogLeft = node -> left;
  ShowItem * ogRight = node -> right;

  // Reinsert the children into the tree
  if (validLeft) {
    // Need to reinsert entire left subtree
    cout << "Reinserting left child: " << ogLeft -> title << endl;
    catalog -> addShowItem(ogLeft -> title, ogLeft -> year, ogLeft -> showRating, ogLeft -> userRating); // Reinsert the left child
    // If this node is out of the tree, so are all of these child nodes
    reinsertChildren(catalog, root, ogLeft); // Recursively add everything in
  }

  if (validRight) {
    // Need to reinsert entire right subtree
    cout << "Reinserting right child: " << ogRight -> title << endl;
    catalog -> addShowItem(ogRight -> title, ogRight -> year, ogRight -> showRating, ogRight -> userRating); // Reinsert the left child
    reinsertChildren(catalog, root, ogLeft);
  }
  // After this function is called you should destroyNode
  destroyNode(node);
}

/* TODO */
void ShowCatalog::removeShow(std::string title) {
  // Find the node to be removed
  if (root == NULL) {
    // cout << "Tree is empty. Cannot remove show"   << endl;   	
    return;
  }

  ShowItem * node = getShowHelper(root, title);

  if (node != NULL) {

    //cout << "Found show to remove: " << node->title << endl;

    // Store information about the children of the node
    bool validLeft = (node -> left != NULL);
    bool validRight = (node -> right != NULL);

    while (validLeft || validRight) {
      ShowItem * ogLeft = node -> left;
      ShowItem * ogRight = node -> right;

      // Rotate the node down to a leaf and then delete it
      if (validLeft) {
        this -> leftRotate(title); // Rotated down to the left leaf
      } else if (validRight) {
        this -> rightRotate(title);
      } else {
        // No children, a leaf node or root
        destroyNode(node); // Sets node to nullptr
        break; // Probably don't need this
        // destroyNode null's the children
      }
      // node left and right changed by rotate function
      validLeft = (node -> left != NULL);
      validRight = (node -> right != NULL);
    }
  } else {
    cout << "Show not found: " << title << endl;
  }
}


/* TODO */
void ShowCatalog::rightRotate(std::string title) {
    ShowItem *parent = NULL;
  	ShowItem *y = root;
  
    while (y != NULL && y->title != title){
      parent = y;
      if (y->title > title)
        y = y->left;
      else
        y = y-> right;
    }
    if (y == NULL){
      cout << title << " not found." << endl;
      return;
    }
    if (y->left == NULL){
      cout << "can't rotate here" << endl;
      return;
    }
  
    ShowItem *x = y->left; // tmp var
    y->left = x->right;
    x->right = y;
  
    
    if (parent == NULL){
      root = x;
    } else if (parent->left == y){
      parent->left = x;
    } else {
      parent->right = x;
    }
}
  



/* TODO */
void ShowCatalog::leftRotate(std::string title)
{
    ShowItem *parent = NULL;
  	ShowItem *x = root;
    ShowItem* yl;
  
    while (x != NULL) {
        if (x -> title == title) {
            if (x == root) return;
            if (parent-> right == x) {
                if (x -> right == NULL) return;
                yl = x -> right -> left;
                parent->right = x->right;
                x->right->left = x;
                x->right = yl;
            }
            else {
                if (x -> right == NULL) return;
                yl = x -> right -> left;
                parent->left = x->right;
                x->right->left = x;
                x->right = yl;
           }
        }
        else if (x-> title > title) {
            parent = x;
            x = x -> left;
        }
        else {
            parent = x;
            x = x -> right;
        }
        
    }
}
  