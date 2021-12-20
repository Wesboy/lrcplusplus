# Given the root of a binary tree, return the preorder traversal of its nodes' values.

## Example 1:

![](inorder_1.jpg)

```
Input: root = [1,null,2,3]
Output: [1,2,3]
```

## Example 2:
```
Input: root = []
Output: []
```

## Example 3:
```
Input: root = [1]
Output: [1]
```

## Constraints:

- The number of nodes in the tree is in the range [0, 100].
- -100 <= Node.val <= 100


## My First Ans

- 采用递归的方式

```
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void searchTree(struct TreeNode* p, int *len)
{
    int ret;
    if(p != NULL)
    {
        ret = p->val;
        *len+=1;
    }
    if(p->left != NULL)
    {
        searchTree(p->left, len);
    }
    if(p->right != NULL)
    {
        searchTree(p->right, len);
    }

}

void searchTreeVal(struct TreeNode* p, int *dat, int *index)
{
    if(p != NULL)
    {
        dat[*index] = p->val;
        *index += 1;
    }
    if(p->left != NULL)
    {
        searchTreeVal(p->left, dat, index);
    }
    if(p->right != NULL)
    {
        searchTreeVal(p->right, dat, index);
    }

}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int *result = NULL;
    *returnSize = 0;
    if(root == NULL)
        return result;

    int nodeLen = 0, index = 0;
    struct TreeNode *p = root;

    searchTree(p, &nodeLen);

    *returnSize = nodeLen;

    result = (int *)malloc(nodeLen*sizeof(int));
    if(result)
    {
        p = root;
        searchTreeVal(p, result, &index);
    }

    return result;


}
```

修改精简
```

void searchTreeVal(struct TreeNode* p, int *dat, int *index)
{
    if(p != NULL)
    {
        dat[*index] = p->val;
        *index += 1;
		searchTreeVal(p->left, dat, index);
		searchTreeVal(p->right, dat, index);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int *result = NULL;
    *returnSize = 0;
    if(root == NULL)
        return result;

    struct TreeNode *p = root;

    result = (int *)malloc(100*sizeof(int));
    if(result)
    {
        p = root;
        searchTreeVal(p, result, returnSize);
    }

    return result;
}
```

- 采用迭代的方式

```
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int *result = NULL;
    *returnSize = 0;
    if(root == NULL)
        return result;

    struct TreeNode *p = root;

    result = (int *)malloc(100*sizeof(int));
    struct TreeNode *stackNode[100]; //栈 
    int top = -1; //栈顶

    if(result)
    {
        p = root;
        while(top > -1 || p!= NULL)
        {
            while(p != NULL)
            {
                result[(*returnSize)++] = p->val;
                stackNode[++top] = p;
                p = p->left;
            }
            p = stackNode[top--];
            p = p->right;
        }
    }

    return result;

}
```