/*

Given a binary tree containing digits from0-9only, each root-to-leaf path could represent a number.
An example is the root-to-leaf path1->2->3which represents the number123.
Find the total sum of all root-to-leaf numbers.
For example,
    1
   / \
  2   3

The root-to-leaf path1->2represents the number12.
The root-to-leaf path1->3represents the number13.
Return the sum = 12 + 13 =25.

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
    int sum = 0;
    void VisitTree(TreeNode *root){
        if (root != nullptr){
            if (root->left != nullptr){
                root->left->val = root->val * 10 + root->left->val;
                VisitTree(root->left);
            }
            if(root->right != nullptr){
                root->right->val = root->val * 10 + root->right->val;
                VisitTree(root->right);
            }
            if(root->left == nullptr && root->right == nullptr){
                sum += root->val;
            }
        }
    }
    int sumNumbers(TreeNode *root) {
        VisitTree(root);
        return sum;
    }
};