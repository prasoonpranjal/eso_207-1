#include <bits/stdc++.h>
using namespace std;
#define N 200005
int TOBALANCE=1; // TOBALANCE is 1 when the condition is Perfectly balanced, 0 otherwise. By changing this constant you can change balance condition.
int NEARLY_BALANCED = 0;
int PERFECTLY_BALANCED = 1;
double BALANCE_RATIO = 0.75; //You may change this ratio.
int t;
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
  //int j=0;
int SortedArrayFromBST(Node *curr,int output[],int fst){
  if (curr->left == NULL ){
    return 0;
  }
  if(curr->right==NULL) return 0;

  int n=0;
  n= SortedArrayFromBST(curr->left,output,fst);
  fst+=n;
  output[fst] =curr->val;
  fst++;
  n++;

  n+=SortedArrayFromBST(curr->right,output,fst);

  return n;
  
} 

/*
This function creates a BST from an array. It takes as parameter2. It returns the root of the BST
that is formed by the array
*/
//I have changed the function below ,instead of passing array , I have passed a pointer to the array

Node *BSTFromSortedArray(int* input, int len){
  
  int mid=len/2;
  Node* head=init(input[mid]);
  if(len<1){
    head->size=0; 
    return head;
  }
  head->left=BSTFromSortedArray(input,mid);
  head->right=BSTFromSortedArray(input+mid+1,len-mid-1);
  head->size=head->left->size + head->right->size+1;
  return head;
  
}

/*
This function recursively deletes all the nodes in the tree whose root in pointed by curr
*/
void deleteNode(Node *curr){
  if(curr==NULL) return;
  deleteNode(curr->left); 
  deleteNode(curr->right);
  free(curr);

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
-when the insert returns then the tree must satisfy the balanced condition2
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

                
   if (!checkPerfectBalance(curr) || !checkNearBalance(curr)){ 
    int l=SortedArrayFromBST(curr,out,t);
    int A[N];
    for(int i=0;i<l;i++){
      
      A[i]=out[t+i];
      
    }
    curr=BSTFromSortedArray(A,l); 
    t=t+l;


  
}
}
/*
This function takes as input a node pointer and a val and searches for a node which has value val in the subtree of node.
It returns true if the value is found, false otherwise.
*/
bool search(Node *curr,int val){
  Node *iter = curr;
  while(iter != NULL){
    if(iter->val == val){
      //iter=iter->left;
      return true;
    }
    else if(iter->val > val){
      //cout<<iter->val<<endl;
      iter=iter->left;
    }
    else if(iter->val < val){
      //cout<<iter->val<<endl;
      iter=iter->right;
    }
    

  } 
  return false;
}

// int main(){
//   Node *root = NULL;
//   int out[N];
//   int queries; scanf("%d",&queries);   //no of queries
//   while(queries--){
//     int c,val; scanf("%d%d",&c,&val);
//     if(c==1){        // query type 1: insertion
//       //insert
//       if(root){      //if root is not NULL
//         insert(root,val,out);
//       }else{     // If root is NULL
//         root = init(val);
//       }
//     }else{
//       //search query
//       if(search(root,val)) printf("Yes\n"); else printf("No\n");
//     }
//   }
//   return 0;
// }

void print_bst(Node * head){
  Node* iter = head;
  while(iter!=NULL){
    //cout<<iter->val;
    iter=iter->left;
  }
}
int main(){
  int arr[N],b[N];
  int t;
  cin>>t;
  for(int i=0;i<t;i++){
    cin>>arr[i];
  }
  Node* root=BSTFromSortedArray(arr,t);
  //delete root->right;
  cout<<root->size<<" ";
  long long k=SortedArrayFromBST(root,b,0);
  for(int i=0;i<k;i++){
    cout<<b[i]<<" ";
  }
  //cout<<k<<" ";
  //cout<<root->size;
  if(search(root,3)==true){
    cout<<"Yes"<<endl;
  }
  //print_bst(root);
}
