/*

Given two binary trees, write a function to check if they are equal or not.
Two binary trees are considered equal if they are structurally identical and the nodes have the same value.

*/
class Solution {
public:
    bool LeftVisit(TreeNode *p, TreeNode *q){
        if((p && !q)||(!p && q)){
            return false;
        }else if(p && q){
            if(p->val != q->val){
                return false;
            }
            if(!LeftVisit(p->left, q->left)){
                return false;
            }
            if(!LeftVisit(p->right, q->right)){
                return false;
            }
        }
        return true;
    } 
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if(LeftVisit(p, q)){
            return true;
        }else{
            return false;
        }
    }
};