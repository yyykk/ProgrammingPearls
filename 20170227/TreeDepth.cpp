/*

Given a binary tree, find its maximum depth.
The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

*/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode *root) {
        if(!root){
            return 0;
        }
        int depth = 0;
        stack<TreeNode *> s;
        TreeNode *p = root;
        p->val = 1;
        while(1){
            if(depth < p->val){
                depth = p->val;
            }
            if(p->right != nullptr){
                p->right->val = p->val + 1;
                s.push(p);
            }
            if(p->left != nullptr){
                p->left->val = p->val + 1;
                p = p->left;
            }else if(!s.empty()){
                p = s.top()->right;
                s.pop();
            }else{
                break;
            }
        }
   		return depth;	
    }
};