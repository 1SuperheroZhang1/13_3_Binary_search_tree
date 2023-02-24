#include <stdio.h>
#include <stdlib.h>
/*
 * 【二叉排序树原理解析】
 *    二叉排序树(也称二叉查找树)或者是一棵空树，或者是具有下列特性的二叉树：
 *    1) 若左子树非空，则左子树上所有结点的值均小于根节点的值。
 *    2) 若右子树非空，则右子树上所有结点的值均大于根节点的值。
 *    3) 左、右子树也分别是一棵二叉排序树。
 * */
typedef int KeyType;
typedef struct BSTNode{
    KeyType key;
    struct BSTNode *left,*right;
}BSTNode,*BiTree;

//非递归实现 54,20,66,40,28,79,58
int BST_Insert(BiTree& T,KeyType k){
    BiTree tree_new=(BiTree)calloc(1,sizeof(BSTNode));//为新插入的树结点申请空间
    tree_new->key=k;//把值放入
    if(NULL==T){//树为空，新节点作为树的根
        T=tree_new;
        return 0;
    }
    BiTree p=T,parent;//p用来查找树，开始时指向树根
    //修改指针
    while(p){
        parent=p;//parent用来存放p的父节点
        if(k>p->key){
            p=p->right;
        }else if(k<p->key){
            p=p->left;
        }else{
            return -1;//相等的元素不可以放入二叉查找树
        }
    }
    //接下来要判断放入父亲的左边还是右边
    if(k>parent->key){//放到父亲右边
        parent->right=tree_new;
    }else{//放到父亲左边
        parent->left=tree_new;
    }
    return 0;
}
//递归实现
int BST_Insert1(BiTree& T,KeyType k){
   if(NULL==T){
     //为新结点申请空间，第一个结点作为树根，后面递归再进入的不是树根，是为叶子结点
     BiTree tree_new=(BiTree)calloc(1,sizeof(BSTNode));//为新结点申请空间
     T->key=k;
     T->left=NULL;
     T->right=NULL;
     return 1;//代表插入成功
   }else if(k==T->key){
       return 0;//发现相同元素，就不插入
   }else if(k<T->key){//如果要插入的结点，小于当前的结点
       //函数调用结束后，左孩子和原来的父亲会关联起来，巧妙利用了引用机制
       //T=T->left
       return BST_Insert1(T->left,k);
   }else{
       return BST_Insert1(T->right,k);
   }
}
//二叉排序树的建树
void Create_BST(BiTree &T,KeyType* str,int len){
    int i;
    for(i=0;i<len;i++){
        BST_Insert(T,str[i]);//把某一个结点放入二叉查找树
    }
}
//中序遍历
void InOrder(BiTree T){
    if(T!=NULL){
        InOrder(T->left);//打印左子树
        printf("%3d",T->key);//打印当前结点
        InOrder(T->right);//打印右子树
    }
}
//查找
BiTree BST_Search(BiTree T,KeyType k,BiTree& parent){
    parent=NULL;//存储要找的结点的父亲
    while(T!=NULL&&T->key!=k){
        parent=T;
        if(k<T->key){
            T=T->left;//比当前结点小，就左边找
        }else{
            T=T->right;//比当前结点大，就右边找
        }
    }
    return T;
}
//二叉排序树的建树，中序遍历，查找
int main() {
    BiTree T=NULL;//树根
    KeyType str[7]={54,20,66,40,28,79,58};//将要进入二叉排序树的元素值
    Create_BST(T,str,7);
    InOrder(T);
    printf("\n");
    BiTree search,parent;
    search=BST_Search(T,41,parent);
    if(search){
        printf("find key %d",search->key);
    }else{
        printf("not find");
    }
    return 0;
}
