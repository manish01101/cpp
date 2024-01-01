
// approach 1 : using array
void inorder(TreeNode<int> *root, vector<int> &in) {
    if(root == NULL) return;

    inorder(root->left, in);
    in.push_back(root->data);
    inorder(root->right, in);
}

vector<int> mergeArrays(vector<int> a, vector<int> b) {
    vector<int> ans(a.size() + b.size());

    int i=0, j=0;
    int k=0;
    while(i<a.size() && j<b.size()) {
        if(a[i] < b[j]) ans[k++] = a[i++]; 
        else ans[k++] = b[j++];
    }
    while(i<a.size()) ans[k++] = a[i++];
    while(j<b.size()) ans[k++] = b[j++];
    return ans;
}

TreeNode<int>* inorderToBST(int s, int e, vector<int> &in) {
    //base case
    if(s>e) return NULL;

    int mid = (s+e)/2;
    TreeNode<int>* root = new TreeNode<int>(in[mid]);
    root->left = inorderToBST(s, mid-1, in);
    root->right = inoderToBSt(mid+1, e, in);
    return root;
}

TreeNode<int> *mergeBST(TreeNode<int> *root1, TreeNode<int> *root2) {
    
    // step 1: store inorder
    vector<int> bst1, bst2;
    inorder(root1, bst1);
    inorder(root2, bst2);

    //step 2: merge both sorted arrays
    vector<int> mergedArray = mergeArrays(bst1, bst2);

    //step 3: use merged inorder array to build bst
    int s=0, e=mergedArray.size() -1;
    return inorderToBST(s, e, mergedArray);
}





// approach 2: converting it to LinkedList


void convertIntoSortedDLL(TreeNode<int> *root, TreeNode<int> &head) {

    //base case
    if(root == NULL) return NULL;

    convertIntoSortedDLL(root->right, head);

    root->right = head;

    if(head != NULL) head->left = root;

    convertIntoSortedDLL(root->left, head);
}

TreeNode<int> mergeLinkedList(TreeNode<int> *head1, TreeNode<int> *head2) {

    TreeNode<int> *head = NULL;
    TreeNode<int> *tail = NULL;

    while(head1 != NULL && head2 != NULL) {
        if(head1->data < head2->data) {
            if(head == NULL){
                head = head1;
                tail = head1;
                head1 = head1->right;
            }
            else {//insert at end
                tail->right = head1;
                head1->left = tail;
                tail = head1;
                head1 = head1->right;
            }
        }
        else{
            if(head == NULL){
                head = head2;
                tail = head2;
                head1 = head2->right;
            }
            else{
                tail->right = head2;
                head2->left = tail;
                tail = head2;
                head2 = head2->right;
            }
        }
    }
    while(head1 != NULL) {
        tail->right = head1;
        head1->left = tail;
        tail = head1;
        head1 = head1->right;
    }
    while(head2 != NULL) {
        tail->right = head2;
        head2->left = tail;
        tail = head2;
        head2 = head2->right;
    }
    return head;
}


// sorted linkedlist to bst
int countNodes(TreeNode<int> *head) {
    int cnt = 0;
    TreeNode<int> *temp = head;
    while(temp != NULL){
        cnt++;
        temp = temp->right;
    }
    return cnt;
}
TreeNode<in> *sortedLLToBST(TreeNode<int>* &head, int n) {
    // base case
    if(n <= 0 || root == NULL) return NULL;

    TreeNode<int> *left = sortedLLToBST(head, n/2);

    TreeNode<int> *root = head;
    root->left = left;

    head = head->next;

    root->right = sortedLLToBST(head, n-n/2-1);
    return root;
}


// main function
TreeNode<int> *mergeBST(TreeNode<int> *root1, TreeNode<int> *root2) {
     
    // step 1: convert BST into sorted DLL in-place
     TreeNode<int> *head1 = NULL;
     convertIntoSortedDLL(root1, head1);
     head1->left = NULL;

     TreeNode<int> *head2 = NULL;
     convertIntoSortedDLL(root2, head2);
     head2->left = NULL;

    // step 2: merge sorted LL
    TreeNode<int> *head = mergeLinkedList(head1, head2);

    //step 3: convert LL to bst
    return sortedLLToBST(head, countNodes(head));
    
}