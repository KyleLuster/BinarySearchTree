#include <iostream>
#include<fstream>

using namespace std;

struct node {
  string data;
  struct node * left;
  struct node * right;
};


struct node * insert(struct node * node, string data) {
  if (node == NULL) {
    struct node * node = new struct node;
    node -> data = data;
    node -> left = NULL;
    node -> right = NULL;
    return node;
  } else {
    //Big-O: Best O(log(n)) splicing data in half
    //       Worst O(n) going through every node
    if (data < node -> data) {
      node -> left = insert(node -> left, data);
    } else {
      node -> right = insert(node -> right, data);
    }
    return node;
  }
}

//search method
int count = 0;
bool search(node * node, string target) {
  count++;
  if (node == NULL) {
    cout<<"Inspected "<< count <<" elements"<<endl;
    cout<< target <<" has not been located"<<endl;
    return false;
  } else {
    if (target == node -> data) {
      cout<<"Inspected "<< count <<" elements"<<endl;
      cout << target << " has been located"<< endl;
      return true;
    } else {
      if (target < node -> data) {
        return (search(node -> left, target));
      } else {
        return (search(node -> right, target));
      }
    }
  }
}

//display method
void display(node * temp) {
  if (temp == NULL) {
    return;
  } else {
//in order
    display(temp -> left);
    cout << temp -> data << " ";
    display(temp -> right);
  }
}

//minimum value; for repair after deletion
node * minVal(struct node * node) {
  struct node * current = node;
  while (current && current -> left != NULL) {
    current = current -> left;
  }
  return current;
}

//deleting the node
    //Big-O: Best O(log(n)) splicing data in half
    //       Worst O(n) going through every node
struct node * deleteNode(struct node * root, string key) {
  if (root == NULL) {
    return root;
  }
  if (key < root -> data) {
    root -> left = deleteNode(root -> left, key);
  } else if (key > root -> data) {
    root -> right = deleteNode(root -> right, key);
  } else {
    //if not < or > it is =
    if (root -> left == NULL) {
      struct node * temp = root -> right;
      delete(root);
      return temp;
    }
     else if(root-> right == NULL){
      struct node * temp = root -> left;
      delete(root);
      return temp;
     }
    struct node* temp = minVal(root -> right);
    root -> data = temp -> data;
    root -> right = deleteNode(root -> right, key);
  }
    return root;
}

int getHeight(struct node* node){
  if(node == NULL){
    return -1;
  }
  else{
    return max(getHeight(node -> left),getHeight(node -> right)) + 1;
  }
}




int main() {

//importing our strings
  fstream myFile;
  string wordArray[10];
  int m = 0;
  myFile.open("text.in");
  while (!myFile.eof()) {
    myFile >> wordArray[m];
    m++;
  }
  myFile.close();

struct node * root = NULL;

//making BST
  int len = sizeof(wordArray)/sizeof(wordArray[0]);
  for(int i = 0; i < len; i++){
    root = insert(root, wordArray[i]);
  }

display(root);
cout<<endl;

  while (true) {
    string input;
    cout << "Enter a word, enter -1 to quit, or enter -2 to delete: ";
    cin >> input;
    if (input == "-1") {
      break;
    } else if(input == "-2"){
      string remove;
      cout << "What word do you want to delete? ";
      cin >> remove;
      deleteNode(root, remove);
      display(root);
      cout<<endl;
    } 
    else {
      count = 0;
      cout<<search(root, input)<<endl;
      
    }
  }
}
