#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template <class T>
struct AVL_node
{
  T data;
  int height;
  AVL_node<T> * lchild, * rchild;
  AVL_node<T>(const T &a,AVL_node<T> * b,AVL_node<T> * c):data(a),height(1),lchild(b),rchild(c){}
};

template <class T>
class AVL_TREE
{
private:
    AVL_node<T> * root;
    int HEIGHT;
public:
    AVL_TREE(){root=NULL,HEIGHT=0;}
    ~AVL_TREE(){destroy();}
    void insert_node(const T &add);
    void delete_node(const T &del);
    void preorder()const;
    void inorder()const;
    void postorder()const;
    void postorder1()const;
    void levelorder()const;
    int max(const T &a,const T &b)const;
    T find_max()const;
    T find_min()const;
    int getheight();
    bool exist(const T &a)const;
    AVL_node<T>* Lrotate(AVL_node<T>* t);
    AVL_node<T>* LRrotate(AVL_node<T>* t);
    AVL_node<T>* Rrotate(AVL_node<T>* t);
    AVL_node<T>* RLrotate(AVL_node<T>* t);
    void print()const;
    void destroy();
private:
    AVL_node<T>* insert_node(const T & add,AVL_node<T>* t);
    AVL_node<T>* delete_node(const T & del,AVL_node<T>* t);
    void preorder(AVL_node<T> * t)const;
    void inorder(AVL_node<T> * t)const;
    void postorder(AVL_node<T> *t)const;
    void postorder1(AVL_node<T> * t)const;
    void levelorder(AVL_node<T> * t)const;
    AVL_node<T>* find_max(AVL_node<T>* t)const;
    AVL_node<T>* find_min(AVL_node<T>* t)const;
    int getheight(AVL_node<T>* t)const;
    bool exist(const T &a,AVL_node<T>* t)const;
    void destroy(AVL_node<T>* t);
    void print(AVL_node<T> * t, T a,int direction)const;
};

template<class T>
AVL_node<T>* AVL_TREE<T>::insert_node(const T & add,AVL_node<T>* t)
{
    if(t==NULL)
      {t=new AVL_node<T>(add,NULL,NULL);
       return t;}
    if(add>t->data)
       {
         t->rchild=insert_node(add,t->rchild);
         if(getheight(t->rchild)-getheight(t->lchild)==2)
            {if(getheight(t->rchild->rchild)>getheight(t->rchild->lchild))
               t=Rrotate(t);
             else
               t=RLrotate(t);}
       }
    else if(add<t->data)
    {
      t->lchild=insert_node(add,t->lchild);
      if(getheight(t->lchild)-getheight(t->rchild)==2)
      {
          if(getheight(t->lchild->lchild)>getheight(t->lchild->rchild))
             t=Lrotate(t);
          else
             t=LRrotate(t);
      }
    }
    else
    {
        cout<<"已有该数据!"<<endl;
    }
    t->height=max(getheight(t->lchild),getheight(t->rchild))+1;
     return t;
}

template <class T>
void AVL_TREE<T>::insert_node(const T &add)
{
    root=insert_node(add,root);
}

template <class T>
AVL_node<T>* AVL_TREE<T>::delete_node(const T &del,AVL_node<T>* t)
{
    if(t==NULL)
        return NULL;
    else if(del>t->data)
    {
        t->rchild=delete_node(del,t->rchild);
        if(getheight(t->lchild)-getheight(t->rchild)==2)
        {
            if(getheight(t->lchild->lchild)>getheight(t->lchild->rchild))
                t=Lrotate(t);
            else
                t=LRrotate(t);
        }
    }
    else if(del<t->data)
    {
        t->lchild=delete_node(del,t->lchild);
        if(getheight(t->rchild)-getheight(t->lchild)==2)
        {
            if(getheight(t->rchild->rchild)>getheight(t->rchild->lchild))
                 t=Rrotate(t);
            else
                 t=RLrotate(t);
        }
    }
    else
    {
        if(t->lchild!=NULL && t->rchild!=NULL)
        {
         if(t->lchild->height<t->rchild->height)
          {t->data=find_min(t->rchild)->data;
          t->rchild=delete_node(find_min(t->rchild)->data,t->rchild);}
          else{t->data=find_max(t->lchild)->data;
          t->lchild=delete_node(find_max(t->lchild)->data,t->lchild);}
          }
        else
        {
            AVL_node<T> * OldNode=t;
            t=(t->lchild!=NULL)?t->lchild:t->rchild;
            delete OldNode;
        }
    }
    if(t!=NULL)
    t->height=max(getheight(t->lchild),getheight(t->rchild))+1;
    return t;
}


template<class T>
void AVL_TREE<T>::delete_node(const T &del)
{
    root=delete_node(del,root);
}

template<class T>
AVL_node<T>* AVL_TREE<T>::Lrotate(AVL_node<T>* t)
{
    AVL_node<T>* tem;
    tem=t->lchild;
    t->lchild=tem->rchild;
    tem->rchild=t;
    t->height=max(getheight(t->lchild),getheight(t->rchild))+1;
    tem->height=max(getheight(tem->rchild),getheight(tem->lchild))+1;
    return tem;
}

template<class T>
AVL_node<T>* AVL_TREE<T>::Rrotate(AVL_node<T>* t)
{
    AVL_node<T>* tem;
    tem=t->rchild;
    t->rchild=tem->lchild;
    tem->lchild=t;
    t->height=max(getheight(t->rchild),getheight(t->lchild))+1;
    tem->height=max(getheight(tem->lchild),getheight(tem->rchild))+1;
    return tem;
}

template<class T>
AVL_node<T>* AVL_TREE<T>::LRrotate(AVL_node<T>* t)
{
    AVL_node<T> *tem;
    t->lchild=Rrotate(t->lchild);
    tem=Lrotate(t);
    return tem;
}

template<class T>
AVL_node<T>* AVL_TREE<T>::RLrotate(AVL_node<T>* t)
{
    AVL_node<T> *tem;
    t->rchild=Lrotate(t->rchild);
    tem=Rrotate(t);
    return tem;
}
template <class T>
int AVL_TREE<T>::getheight(AVL_node<T> * t)const
{
    if(t==NULL)
        return 0;
    else
        return t->height;
}

template <class T>
int AVL_TREE<T>::getheight()
{
    HEIGHT=getheight(root);
    return HEIGHT;
}

template<class T>
AVL_node<T> * AVL_TREE<T>::find_min(AVL_node<T> * t)const
{
    if(t==NULL)
        return NULL;
    else
        while(t->lchild!=NULL)
    {
        t=t->lchild;
    }
    return t;
}

template<class T>
T AVL_TREE<T>::find_min()const
{
    return find_min(root)->data;
}

template<class T>
AVL_node<T> * AVL_TREE<T>::find_max(AVL_node<T> * t)const
{
    if(t==NULL)
        return NULL;
    else
    {
        while(t->rchild!=NULL)
            t=t->rchild;
    }
    return t;
}

template<class T>
T AVL_TREE<T>::find_max()const
{
    return find_max(root)->data;
}

template <class T>
void AVL_TREE<T>::preorder(AVL_node<T> * t)const
{
    if(t==NULL)
        return;
    else
    {
        cout<<t->data<<' ';
        preorder(t->lchild);
        preorder(t->rchild);
    }
}

template <class T>
void AVL_TREE<T>::preorder()const
{
    preorder(root);
    cout<<endl;
}

template <class T>
void AVL_TREE<T>::inorder(AVL_node<T>* t)const
{
    if(t==NULL)
        return ;
    else
    {
         inorder(t->lchild);
         cout<<t->data<<' ';
         inorder(t->rchild);
    }
}

template <class T>
void AVL_TREE<T>::inorder()const
{
    inorder(root);
     cout<<endl;
}

template <class T>
void AVL_TREE<T>::postorder(AVL_node<T> * t)const
{
    if(t==NULL)
         return;
    else
    {
        postorder(t->lchild);
        postorder(t->rchild);
        cout<<t->data<<' ';
    }
}

template <class T>
void AVL_TREE<T>::postorder()const
{
    postorder(root);
     cout<<endl;
}

template <class T>
void AVL_TREE<T>::postorder1(AVL_node<T>* t)const
{
    if(t==NULL)
        return ;

        AVL_node<T> * p, * r;
        p=t;
        r=NULL;
        stack<AVL_node<T> *> my_stack;
        while(p!=NULL || !my_stack.empty())
        {
         if(!p)
        {
            my_stack.push(p);
            p=p->lchild;
        }
        else
        {
            p=my_stack.top();
            if(p->rchild!=NULL  && p->rchild!=r)
            {
                my_stack.push(p->rchild);
                p=p->rchild->lchild;
            }
            else
            {
                my_stack.pop();
                cout<<p->data<<' ';
                r=p;
                p=NULL;
            }
        }
    }
}


template <class T>
void AVL_TREE<T>::postorder1()const
{
    postorder(root);
     cout<<endl;
}

template<class T>
void AVL_TREE<T>::levelorder(AVL_node<T> * t)const
{
    if(t==NULL)
       return ;
    else
    {
        AVL_node<T> * p;
        p=t;
        queue<AVL_node<T> *> my_queue;
        my_queue.push(p);
        while(!my_queue.empty())
        {
            p=my_queue.front();
            my_queue.pop();
            if(p!=NULL)
            {
                cout<<p->data<<' ';
                my_queue.push(p->lchild);
                my_queue.push(p->rchild);
            }
        }
    }
}

template<class T>
void AVL_TREE<T>::levelorder()const
{
    levelorder(root);
     cout<<endl;
}

template <class T>
bool AVL_TREE<T>::exist(const T & a,AVL_node<T>* t)const
{  bool flag;
    if(t==NULL)
        return false;
    else if(a<t->data) flag=exist(a,t->lchild);
    else if(a>t->data) flag=exist(a,t->rchild);
    else flag=true;

    return flag;
}

template <class T>
bool AVL_TREE<T>::exist(const T & a)const
{
    return exist(a,root);
}

template <class T>
void AVL_TREE<T>::destroy(AVL_node<T>* t)
{
    if(t==NULL)
        return ;
    else
    {
        destroy(t->lchild);
        destroy(t->rchild);
        delete t;
    }
}

template <class T>
int AVL_TREE<T>::max(const T &a,const T &b)const
{
    return (a>b)?a:b;
}


template <class T>
void AVL_TREE<T>::destroy()
{
    destroy(root);
    root=NULL;
}

template <class T>
void AVL_TREE<T>::print(AVL_node<T> * t, T a,int direction)const
{
    if(t==NULL)
        return ;
    else
    {
        if(direction==0)
            cout<<t->data<<"is the root key"<<endl;
        else
        {
            cout<<t->data<<"is "<<a<<"'s "<<((direction==-1)?"left child":"right child")<<endl;
        }
        print(t->lchild,t->data,-1);
        print(t->rchild,t->data,1);
    }
}

template <class T>
void AVL_TREE<T>::print()const
{
    print(root,root->data,0);
}

int main()
{
    AVL_TREE<int> b;
    int a[16]={3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
    for(int i=0;i<16;i++)
        b.insert_node(a[i]);
    cout<<"前序遍历："<<endl;
    b.preorder();
    cout<<"中序遍历："<<endl;
    b.inorder();
    cout<<"后序遍历："<<endl;
    b.postorder();
    cout<<"后序遍历1："<<endl;
    b.postorder1();
    cout<<"层序遍历："<<endl;
    b.levelorder();
    cout<<"树高："<<endl;
    cout<<b.getheight()<<endl;
    cout<<b.find_max()<<' '<<b.find_min()<<endl;
    cout<<"2是否存在："<<endl;
    cout<<b.exist(2)<<endl;
    b.print();
    cout<<endl;
    cout<<"删除节点8："<<endl;
    b.delete_node(8);
    cout<<"前序遍历:"<<endl;
    b.levelorder();
    b.insert_node(8);
    b.inorder();
    b.destroy();
    b.inorder();
    return 0;
}
