#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
using namespace std;
#define N 200005
int TOBALANCE=1; // TOBALANCE is 1 when the condition is Perfectly balanced, 0 otherwise. By changing this constant you can change balance condition.
int NEARLY_BALANCED = 0;
int PERFECTLY_BALANCED = 1;
double BALANCE_RATIO = 0.75; //You may change this ratio.



/* structure of a node of the binary tree.
val: value at the node
size: size of subtree rooted at node
left,right:pointers to right and left sub tree 
*/
struct Node{
  int val;
  int size;
  struct Node *left,*right;  
};

/*
This function takes a value and initialises and returns a new node whose value is set to the given parameter.
*/
Node* init(int val){
  Node *curr = (Node *)malloc(sizeof(Node));
  curr->val=val;
  curr->size=1;
  curr->left=curr->right=NULL;
  return curr;
}


/*
SortedArrayFromBST: This function takes as input a node, pointer to an array, and an integer that denotes the next free position in the array.
This function fills in the array all the values in the tree whose root is the given node i.e. output array finally contains the elements in 
increasing order.
This function must return the number of array positions it has filled. i.e. if initial value of parameter fst = p, then after returning from the function the final value must increase by the size of subtree i.e p+curr->size.
*/
int SortedArrayFromBST(Node *curr,int output[],int fst){
  int l1=0,l2=0;
  if (curr == NULL) 
    return 0;  
    
  l1=SortedArrayFromBST(curr->left,output,fst);
  fst=fst+l1; 
  
  output[fst]=curr->val; 
  fst++;
  
  l2=SortedArrayFromBST(curr->right,output,fst);
  fst=fst+l2;
  
  return (l1+l2+1);

}

/*
This function creates a BST from an array. It takes as parameters input array and the length of array. It returns the root of the BST
that is formed by the array
*/

Node *BSTFromSortedArray(int input[], int len){
  int i=len/2;
  Node *root;
  
  if(len==1){
   root=init(input[0]);
    return root;
  }
  
  if (len==2){
    root=init(input[0]);
    Node *temp=init(input[1]);
    root->size=2;
    root->right=temp;
    return root;
  }
  
  root=init(input[i]);
  root->size=len;
  
  root->left= BSTFromSortedArray(input,i);

  root->right= BSTFromSortedArray(input+i+1,len-i-1);

  return root;
 }

/*
This function recursively deletes all the nodes in the tree whose root in pointed by curr
*/

void deleteNode(Node *curr){
  if(curr==NULL) return;
  deleteNode(curr->left); 
  deleteNode(curr->right);
  free(curr) ;
}
/*
This function returns true if the current node satisfies the nearly balanced condition and false otherwise
*/
bool checkNearBalance(Node *curr){
  int s1, s2;
  
  if(curr->left==NULL){
    s1=0;
  }
  else s1=curr->left->size;

  if(curr->right==NULL){
    s2=0;
  }
  else s2=curr->right->size;


  if(s1< BALANCE_RATIO*curr->size && s2 < BALANCE_RATIO*curr->size ){
    return true;
  }
  
  return false;
}

/*
This function returns true if the current node satisfies the perfectly balanced condition and false otherwise
*/
bool checkPerfectBalance(Node *curr){
  int s1, s2;
  if(curr->left==NULL){
    s1=0;
  }
  else s1=curr->left->size;

  if(curr->right==NULL){
    s2=0;
  }
  else s2=curr->right->size;
  
  if( abs( s1 - s2) <= 1 ){
    return true;
  }
  return false;
}

/*
This function takes as input a pointer to a node and inserts a node in the subtree of the node depending on the value.
out[] array is used as a helper array which will be used when the BST does not satisfy the balanced condition.

-when the insert returns then the tree must satisfy the balanced condition
*/
void insert(Node *&curr,int val,int out[]){
  if(curr->val > val){
    
    if(curr->left==NULL){
      curr->left=init(val);
    }
    else insert(curr->left,val,out);
  }
  else {
    
    if(curr->right==NULL){
      curr->right=init(val);
    }
    else insert(curr->right,val,out);
  }

                
   if (!checkPerfectBalance(curr) ){ 
    
    int l=SortedArrayFromBST(curr,out,0);
    deleteNode(curr);
    
    
    
    curr=BSTFromSortedArray(out,l); 
    
  }
}

/*
This function takes as input a node pointer and a val and searches for a node which has value val in the subtree of node.
It returns true if the value is found, false otherwise.
*/
bool search(Node *curr,int val){
Node *temp = curr;
  while(temp != NULL){
    if(temp->val == val){
      return true;
    }
    else if(temp->val > val){
      temp=temp->left;
    }
    else if(temp->val < val){
      temp=temp->right;
    }
    

  } 
  return false;
}

int main(){
  Node *root = NULL;
  int out[N];
  int queries; scanf("%d",&queries);
  for(int x=0;x<queries;x++){
    int c=1,val; scanf("%d",&val);

    if(c==1){
      //insert
      if(root){
        clock_t start,end;
        start= clock();
        insert(root,val,out);
        end = clock();
        cout<< x <<" "<<(float)(end-start)/CLOCKS_PER_SEC<<endl;
      }else{
        root = init(val);
      

      }
    }else{ 
      //search query
      if(search(root,val)) printf("Yes\n"); else printf("No\n");
    }
  }
  cout<<root->size;
  return 0;
}
