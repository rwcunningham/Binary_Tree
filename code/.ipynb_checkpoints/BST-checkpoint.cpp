/* Note: refer to the header file (BST.h) for documentation of each method. */

#include "BST.h"

BST::BST() {
  // Here is one way to implement the constructor. Keep or change it, up to you.
  root = new bst_node*;
  *root = NULL;
}

BST::~BST() {} // I guess we're going to have to traverse the node and "delete" the heap memory?

bst_node* BST::init_node(int data) { 
  bst_node* ret = new bst_node;
  
  ret->data = data;
  ret->left = nullptr;
  ret->right = nullptr;
  
  return ret;
  
  //why is this return statement in the original cpp file?
 // return NULL; // idk what this is for tbh

}

void BST::insert(bst_node* new_node) {
  // Your code here
  
  
  // if our root isn't pointing to a pointer, there's no data yet
  if (*root == nullptr)
  {
    *root = new_node;  // *root dereferences root down to a single pointer, and new_node is a single pointer
  }
  
  
  else if (new_node->data < (*root)->data) // compare our data with data the pointer *root points to (root just points to a pointer)
  {
    if ( (*root)->left == nullptr )
    {
      (*root)->left = new_node;
    }
    
    else //not a nullptr
    {
      // call recursively
      recursive_insert(*root, new_node);
    }
  }
  
  else if (new_node->data > (*root)->data) 
  {
    if ( (*root)->right == nullptr )
    {
      (*root)->right = new_node;
    }
    
    else //not a nullptr
    {
      // call recursively
      recursive_insert(*root, new_node);
    }
  }
  
           
    
    else // there is a right child node
    {
      recursive_insert(*root, new_node);
    }
        
}


void BST::recursive_insert(bst_node* parent, bst_node* new_node)
{
  if (new_node->data < parent->data)
  {
    if (parent->left == nullptr)
    {
      parent->left = new_node;
    }
    else
    {
      recursive_insert(parent->left, new_node);
    }
  }
  
  else if (new_node->data > parent->data)
    {
    
      if (parent->right == nullptr)
      {
        parent->right = new_node;
      }
      else
      {
        recursive_insert(parent->right, new_node);
      }
    
  }
}

  
  
  //next step I guess is to traverse the tree and check > or < and choose left or right


void BST::insert_data(int data) {
  
  bst_node* new_node = init_node(data); // create a new node
 
  insert(new_node); // insert new_node into insert
  
}

bst_node* BST::get_predecessor(bst_node* node_to_find_buddy)
{
 
  // if there's no left child
  if (node_to_find_buddy->left == nullptr)
  {
    return node_to_find_buddy;
  }

  // start the checknode to the left of the starting node, and move right
  bst_node* check_node = node_to_find_buddy->left;
  
  
    
  // otherwise keep going right until we hit a null right-poiner, then we return the node we stopped on
  while (check_node->right != nullptr)
  {
    check_node = check_node->right;
  }
  // if we're at the end, return our check node
  return check_node;
}

bst_node* BST::get_parent(bst_node* current_node, bst_node* child_node)
{
  //if the data is not in our tree
  if (contains((*root), child_node->data) == false) // 
  {
    return nullptr;
  }
  
  // if it is in our tree
  else
  {
    if ( (*root)->data == child_node->data) // if our root is the node, it has no parent
    {
      return nullptr;
    }

    else if ((current_node->left == child_node) || (current_node->right == child_node)) // left or right child is a match
    {
      return current_node;
    }
  
    else if (child_node->data < current_node->data)
    {
   
        return get_parent(current_node->left, child_node);
    }
    
    else if (child_node->data > current_node->data)
    {
        return get_parent(current_node->right, child_node);
    }
  }
  
  return nullptr;
}
      
void BST::remove(int data) {
  // Your code here
  bool is_in_tree = contains(*root, data); // does this tree contain our value?
  
  if (*root == nullptr)
  {
    return;
  }
  // first see if our value is in the table
  
  if (is_in_tree == false)
  {
    return;
  }
  
  // if it's in the tree
  else
  {
    // now find the node to remove
    bst_node* node_to_rmv = get_node(*root, data);
    
    if (node_to_rmv == nullptr)
    {
      return;
    }
  
  
    // get the parent of the node
    bst_node* parent_node = get_parent((*root), node_to_rmv);
    
    //
    if (parent_node == NULL)
    {
      bst_node* predecessor = get_predecessor(*root);
      (*root)->data = predecessor->data;
      delete predecessor;

    }
    
    // if no children
    
    if (node_to_rmv->right == nullptr && node_to_rmv ->left == nullptr)
    {
      // if our node is the left child of its parent
      if (parent_node->left == node_to_rmv)
      {
        parent_node->left = nullptr;
      }
    
      // if it's the right child of its parent
      if (parent_node->right == node_to_rmv)
      {
        parent_node->right = nullptr;
      }
      // free up the memory
      delete node_to_rmv;
      return;
    }
  
    //if only right child
    else if(node_to_rmv->left == nullptr && node_to_rmv->right != nullptr)
    {
      // if it's the left child of its parent
      if (parent_node->left == node_to_rmv)
      {
        parent_node->left = node_to_rmv->right;
      }
    
      // if it's the right child
      if (parent_node->right == node_to_rmv)
      {
        parent_node->right = node_to_rmv->right;
      }
      delete node_to_rmv;
    }
    
    
    // if only left child
    else if (node_to_rmv->right == nullptr && node_to_rmv->left != nullptr)
    {
      // if it's the left child of its parent
      if (parent_node->left == node_to_rmv)
      {
        parent_node->left = node_to_rmv->left;
      }
    
      // if it's the right child
      if (parent_node->right == node_to_rmv)
      {
        parent_node->right = node_to_rmv->left;
      }
    
      delete node_to_rmv;
    }
  
    // if two children
    else if ((node_to_rmv->left != nullptr) && (node_to_rmv-> right != nullptr)) 
    {
  
      // find the predecessor, and set the new value to it
  
      bst_node* predecessor = get_predecessor(node_to_rmv);
      bst_node* predecessor_parent = get_parent(*root, predecessor);
      
      
       // swap in the predecessor data
      
      if (predecessor_parent == nullptr)
      {
        return;
      }
    
      if(predecessor_parent->left == predecessor)
      {
        predecessor_parent->left = nullptr;
      }
      else if (predecessor_parent->right == predecessor)
      {
        predecessor_parent->right = nullptr;
      }
      
      node_to_rmv->data = predecessor->data;
      delete predecessor; // free up the memory for predecessor
      return;
    }
  }
}
     
  
bool BST::contains(bst_node* subt, int data) {
   // if the value matches, return true
  if ( subt->data == data)
  {
    return true;
  }
  
  // if less than traverse left 
  else if (data < subt->data)
  {
    // if nothing in the left child, then return null, the value is not in the table
    if (subt->left == nullptr)
    {
      return false;
    }
    else // if the subtree left pointer isn't empty
    {
      // otherwise iterate using the left node as the new top of the subtree
      return contains(subt->left, data);
    }
  }
  
  // if greater than, do the same thing
  
  else if (data > subt->data)
  {
    // right subtree, if non-existant, return false
    if (subt->right == nullptr)
    {
      return false;
    }
    // right subtree
    else
    {
    return contains( subt->right, data);
    }
    
  }
  
  return false;
}

bst_node* BST::get_node(bst_node* subt, int data) {
  // Your code here
  //
  
  if (subt == nullptr)
  {
    return NULL;
  }
  // if the value matches, return that node
  if ( subt->data == data)
  {
    return subt;
  }
  
  // if less than traverse left 
  else if (data < subt->data)
  {
    // if nothing in the left child, then return null, the value is not in the table
    if (subt->left == nullptr)
    {
      return NULL;
    }
    else
    {
      // otherwise iterate using the left node as the new top of the subtree
      return get_node(subt->left, data);
    }
  }
  
  // if greater than, do the same thing
  
  else if (data > subt->data)
  {
    // right subtree, if non-existant, return false
    if (subt->right == nullptr)
    {
      return NULL;
    }
    // right subtree
    else
    {
    return get_node( subt->right, data);
    }
    
  }
  return NULL;
}
  

           

int BST::size(bst_node* subt) 
{
  // Your code here
  int count = 0;
  if (subt == nullptr)
  {
  return 0;
  }
  
  else
  {
    count = 1 + size(subt->left) + size(subt->right);
  }
  
  return count;
}

void BST::to_vector(bst_node* subt, vector<int>& vec) {
  // Your code here
  if (subt == nullptr)
  {
    return;
  }
  
  
  
  to_vector(subt->left, vec);
  vec.push_back(subt->data);
  to_vector(subt->right, vec);
  
}

bst_node* BST::get_root() {
  // This function is implemented for you
  if (*root == NULL)
    return NULL;
  return *root;
}

void BST::set_root(bst_node** new_root) {
  // This function is implemented for you
  root = new_root;
}
