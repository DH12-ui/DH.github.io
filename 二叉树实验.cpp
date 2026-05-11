#include<bits/stdc++.h>
#define Maxsize 1000
using namespace std;
class BinTreeNode{//二叉树链表节点类 
	public:
		char id[10];
		double grade;
		int age;
		char sex[4];
	    BinTreeNode *lchild,*rchild;
	    BinTreeNode* operator=(BinTreeNode* p){
	    	int i=strlen(p->id);
	    	int statics=0;
	    	for(int u=0;u<i;u++){
	    		this->id[u]=p->id[u];
			}
	    	return this;
		}
		friend bool operator ==(BinTreeNode *p,BinTreeNode q);//重载运算符“==”，使其变成我们所需的运算符功能 
		friend ostream& operator<<(ostream& out,BinTreeNode *m);//重载输出流 
		friend istream& operator>>(istream& in,BinTreeNode *m); 
};
istream& operator>>(istream& in,BinTreeNode *m)
{
	in>>m->id>>m->age>>m->sex>>m->grade;
	return in;
	
}
class SqStack{//定义栈 
	public:
		BinTreeNode *node[Maxsize];
		int top;
};
class SqQueue{//定义队列 
	public:
		BinTreeNode *node[Maxsize];
		int front,rear;
};
/*
定义了一个类模板，它包含了BinTreeNode类,SqStack类,SqQueue类的实现。 
*/ 
template <class T,class Q,class R> 
class BinTree{
	public:
		T  *CreatBinTree()//按照编号输入节点数据类型 
        { 
            T *T1,*p,*s[Maxsize];
            char ch ;
            int i,j;
            while (1)
            { 
                scanf("%d", &i);
                if (i==0)  break ;   /*  以编号0作为输入结束  */
                else{
                    p=new T ;
                    cin>>p;
                    p->lchild=p->rchild=NULL ; 
					s[i]=p ;
					if (i==1)  T1=p ;
                    else
                    { 
                    j=i/2 ;    /*    j是i的双亲结点编号  */
                    if (i%2==0)  s[j]->lchild=p ;
                    else  s[j]->rchild=p ;
                    }
                }
           } 
           return(T1) ;
        } 
		void DispBTree(T *p)//将该树中所有的节点值输出即可。 
		{
			if(p!=NULL){
				cout<<p;//重载运算符，将T类型的数据输出即可； 
			    if(p->lchild!=NULL||p->rchild!=NULL){
				    printf("(");
				    DispBTree(p->lchild);//深度优先搜索 
				    if(p->rchild!=NULL) printf(",");
				        DispBTree(p->rchild);
				    printf(")");
			    }
			}
		}
		int BTHeight(T *b){//求得二叉树链表的高度； 
			int lchildh=0,rchildh=0;
			if(b==NULL){
				return 0;
			}
			else{
				lchildh=BTHeight(b->lchild);
				rchildh=BTHeight(b->rchild);
				return (lchildh>rchildh)?(lchildh+1):(rchildh+1);
			}
		}
		int FindSpecialHeight(T *b,T p,int &n,int mark)//寻找某个结点所在的层次 
		{
			if(b==NULL)
			return 0;
			if(b){
				mark++;
				if(b==p){
					n=mark;
				}
				FindSpecialHeight(b->lchild,p,n,mark);
				FindSpecialHeight(b->rchild,p,n,mark);
			}
			
		}
		int StaticsNodeNumber(T *b)//统计结点的数量 
		{
			static int n;
			if(b){
			    n++;
				StaticsNodeNumber(b->lchild);
				StaticsNodeNumber(b->rchild);
			}
			return n;
		}
		int StaticsLeavesNodeNumber(T *b)//统计叶结点的数量 
		{
			int n1,n2;
			if(!b){
				return 0;
			}
			else if(!b->lchild&&!b->rchild){
				return 1;
			}
			else{
				n1=StaticsLeavesNodeNumber(b->lchild);
				n2=StaticsLeavesNodeNumber(b->rchild);
				return n1+n2;
			}
		}
		T* FindNode(T *b,T p)//寻找该节点，并且将该节点的地址返回，便于查找度和父亲节点； 
		{
			T *n;
			if(b==NULL){
				return NULL;
			}
			else if(b==p){
				return b;
			}
			else{
				n=FindNode(b->lchild,p);
				if(n!=NULL){
					return n;
				}
				else{
					return FindNode(b->rchild,p);
				}
			}
		}
		T* findFatherNode(T* b,T *p)//寻找父亲节点 
		{
			if(b==NULL){
				return NULL;
			}
			if(b->lchild!=NULL&&b->lchild==p){
				return b;
			}
			if(b->rchild!=NULL&&b->rchild==p){
				return b;
			}
			if(findFatherNode(b->lchild,p)!=NULL){
				return findFatherNode(b->lchild,p);
			}
			return findFatherNode(b->rchild,p);
		}
		void FirstLook(T *b)//先序遍历(递归) 
		{
			if(b!=NULL){
				cout<<b;
			    FirstLook(b->lchild);
			    FirstLook(b->rchild);
		    }
		}
		void MiddleLook(T *p){//中序遍历 (递归)
			if(p!=NULL){
				MiddleLook(p->lchild);
				cout<<p;
				MiddleLook(p->rchild);
			}
		}
		void BehindLook(T *p){//后序遍历 (递归)
			if(p!=NULL){
				BehindLook(p->lchild);
				BehindLook(p->rchild);
				cout<<p;
			}
		}
		
		void InitStack(Q *&s){//初始化栈 
			s=new Q;
			s->top=-1;
		}
		bool Push(Q *&s,T *b){//进站操作 
			if(s->top==Maxsize-1){
				return false;
			}
			s->top++;
			s->node[s->top]=b;
			return true;
		}
		bool Pop(Q *&s,T *&b){//出栈操作 
			if(s->top==-1){
				return false;
			}
			b=s->node[s->top];
			s->top--;
			return true;
		}
		bool StackEmpty(Q *s){//判断栈是不是满的 
			return (s->top==-1);
		}
		bool GetTop(Q *s,T *&p){
			if(s->top==-1)
			return false;
			p=s->node[s->top];
			return true;
		} 
		void DestroyStack(Q *&s){//销毁栈 
			free(s);
		}
		void preorder(T *b){//先序遍历(非递归) 
			T *p;
			Q *st;
			InitStack(st);
			p=b;
			while(!StackEmpty(st)||p!=NULL){
				while(p!=NULL){
					cout<<p;
					Push(st,p);
					p=p->lchild;
				}
				if(!StackEmpty(st)){
					Pop(st,p);
					p=p->rchild;
				}
			}
			DestroyStack(st); 
		}
		void Inorder(T *b){//中序遍历(非递归)
			T *p;
			Q *st;
			InitStack(st);
			p=b;
			while(!StackEmpty(st)||p!=NULL){
				while(p!=NULL){
					Push(st,p);
					p=p->lchild;
				}
				if(!StackEmpty(st)){
					Pop(st,p);
					cout<<p;
					p=p->rchild;
				}
			}
			DestroyStack(st);
		}
		void Postorder(T *b){//后序遍历（非递归） 
			T *p,*r;
			bool flag;
			Q *st;
			InitStack(st);
			p=b;
			do{
				while(p!=NULL){
					Push(st,p);
					p=p->lchild;
				}
				r=NULL;
				flag=true;
				while(!StackEmpty(st)&&flag){
					GetTop(st,p);
					if(p->rchild==r){
						cout<<p;
						Pop(st,p);
						r=p;
					}
					else{
						p=p->rchild;
						flag=false;
						
					}
				}
			}while(!StackEmpty(st));
			DestroyStack(st);
		}
		void InitQueue(R *&q){//初始化队列
		    q=new R;
			q->front=q->rear=-1; 
			
		}
		void DestroyQueue(R *&q){//销毁队列； 
			free(q);
		} 
		bool QueueEmpty(R *q){//判断队列是否为空 
			return (q->rear==q->front);
		} 
		bool enQueue(R *&q,T *p){//进队列 
			if(q->rear==Maxsize-1){
				return false;
			}
			q->rear++;
			q->node[q->rear]=p;
			return true;
		}
		bool deQueue(R *&q,T *&p){//出队列 
			if(q->rear==q->front)
			return false;
			q->front++;
			p=q->node[q->front];
			return true;
		} 
		void LevelOrder(T *b){//层次遍历 
			T *p;
			R *qu;
			InitQueue(qu);
			enQueue(qu,b);
			while(!QueueEmpty(qu)){
				deQueue(qu,p);
				cout<<p;
				if(p->lchild!=NULL){
					enQueue(qu,p->lchild);
				}
				if(p->rchild!=NULL){
					enQueue(qu,p->rchild);
				}
			}
			DestroyQueue(qu);
		}
		void copy(T *p,T *&q)
		{
			if(p==NULL){
				q=NULL;
				return;
			}
			else{
				q=new T;
				q=p;
				copy(p->lchild,q->lchild);
				copy(p->rchild,q->rchild);
			}
		}
}; 
bool operator==(BinTreeNode *p,BinTreeNode q)//重载“==”的运算符 
{
	int i=strlen(p->id);
	int statics=0;
	for(int u=0;u<i;u++){
		if(p->id[u]==q.id[u]){
			statics++;
		}
	}
	if(statics==i){
		return true;
	}
	else{
		return false;
	}
}
ostream& operator<<(ostream& out,BinTreeNode *m)//重载输出流 
{
    out<<m->id<<" "<<m->age<<" "<<m->grade<<" "<<m->sex<<endl; 
	return out;
}
int main()
{
	BinTree<BinTreeNode,SqStack,SqQueue> tree;
	BinTreeNode *virtualnode;
	virtualnode=NULL;
	char a[100];
	cout<<"请按照编号顺序依次输入学生的姓名，年龄，性别，成绩"<<endl;
	virtualnode=tree.CreatBinTree();//创建一个二叉树 
    cout<<"建立二叉树链表成功"<<endl; 
	while(1){
		cout<<"-----------------------------------"<<endl;
		cout<<"1.输出二叉树中的所有节点"<<endl;
		cout<<"2.输出二叉树的高度"<<endl;
		cout<<"3.查询特定节点的层次"<<endl;
		cout<<"4.输出二叉树节点的数量"<<endl;
		cout<<"5.输出二叉树所有叶结点"<<endl;
		cout<<"6.查询特定节点的度以及该节点的孩子节点和父节点"<<endl;
		cout<<"7.输出二叉链表的先序遍历的递归实现"<<endl;
		cout<<"8.输出二叉链表的先序遍历的非递归实现"<<endl;
		cout<<"9.输出二叉链表的中序遍历的递归实现"<<endl;
		cout<<"10.输出二叉链表的中序遍历的非递归实现"<<endl;
		cout<<"11.输出二叉链表的后序遍历的递归实现"<<endl;
		cout<<"12.输出二叉链表的后序遍历的非递归实现"<<endl;
		cout<<"13.输出二叉链表的层次遍历"<<endl;
		cout<<"14.输出复制后的二叉链表"<<endl;
		cout<<"0.退出系统"<<endl;
		cout<<"------------------------------------"<<endl;
		int m;
		cin>>m; 
		if(m==1){
			cout<<"二叉树遍历："<<endl; 
			tree.DispBTree(virtualnode);//输出这个二叉树所有的数值；
			cout<<endl;
		}
		if(m==2){
			cout<<"二叉树的高度："<<endl;
			cout<<tree.BTHeight(virtualnode);//输出这个二叉树的高度；
			cout<<endl; 
		}
		if(m==3){
			BinTreeNode findnode,*studyNode;//输入一个需要寻找的节点值 
	        cout<<"请输入你所要寻找的节点"<<endl; 
	        cin>>findnode.id;
	        int depth=1,mark=0; 
	        studyNode=tree.FindNode(virtualnode,findnode);
            tree.FindSpecialHeight(virtualnode,findnode,depth,mark);
	        if(studyNode!=NULL)
	            cout<<"该节点所在层次是："<<depth<<endl;//输出所需求节点的所在的层次
	        else{
		       cout<<"没有该节点的存在"<<endl;
	        }
		}
		if(m==4){
			cout<<"二叉链表所有的节点数量："<<tree.StaticsNodeNumber(virtualnode)<<endl;//统计所有结点的数量 
		}
		if(m==5){
			cout<<"二叉链表所有叶子节点数量："<<tree.StaticsLeavesNodeNumber(virtualnode)<<endl;//统计所有叶结点的数量
		}
		if(m==6){
			cout<<"请输入所求节点的值"<<endl;
			BinTreeNode DuNode,*virtualDu;
	        cin>>DuNode.id;//输入要求得的节点的值，然后再去求得度
	        virtualDu=tree.FindNode(virtualnode,DuNode);//找到该节点并且返回该节点的地址；
	/*
	找到该节点的地址后进行判断，输出该节点的度和他的子女节点 
	*/
	        if(virtualDu!=NULL){
		        if(virtualDu->lchild==NULL&&virtualDu->rchild==NULL){
		            cout<<"结点的度："<<0<<endl;
	  	            cout<<"无孩子结点"<<endl; 
	            }
	            else if(virtualDu->lchild==NULL&&virtualDu->rchild!=NULL){
		            cout<<"结点的度："<<1<<endl;
		            cout<<"孩子节点是:"<< virtualDu->rchild<<endl;
	            } 
	            else if(virtualDu->lchild!=NULL&&virtualDu->rchild==NULL){
		            cout<<"结点的度："<<1<<endl;
		            cout<<"孩子节点是:"<<virtualDu->lchild<<endl;
	            }
	            else if(virtualDu->lchild!=NULL&&virtualDu->rchild!=NULL){
		            cout<<"结点的度："<<2<<endl;
		            cout<<"孩子节点是:"<< virtualDu->lchild<<" "<<virtualDu->rchild<<endl;
	            }
	            BinTreeNode *virtualFather;
	            virtualFather=tree.findFatherNode(virtualnode,virtualDu);
	            if(virtualFather!=NULL) 
	            cout<<"该节点的父亲节点是："<<virtualFather<<endl;
	            else
	            cout<<"该节点为根节点，无双亲结点"<<endl; 
	       } 
	       else{
		        cout<<"无此节点信息"<<endl; 
	        }
		}
		if(m==7){
			cout<<"递归算法的先序遍历：";
	        tree.FirstLook(virtualnode);//先序遍历 
	        cout<<endl;
		}
		if(m==8){
			cout<<"非递归算法的先序遍历：";
	        tree.preorder(virtualnode);//先序遍历
			cout<<endl; 
		}
		if(m==9){
		    cout<<"递归算法的中序遍历：";
	        tree.MiddleLook(virtualnode);//中序遍历 
	        cout<<endl;
		}
		if(m==10){
			cout<<"非递归算法的中序遍历："; 
	        tree.Inorder(virtualnode);//中序遍历
	        cout<<endl;
		}
		if(m==11){
			cout<<"递归算法的后序遍历：";
	        tree.BehindLook(virtualnode);//后序遍历 
	        cout<<endl; 
		}
		if(m==12){
			cout<<"非递归算法的后序遍历："; 
	        tree.Postorder(virtualnode);//后序遍历 
	        cout<<endl;
		}
		if(m==13){
			/*
	       层次遍历 
	        */
            cout<<"层次遍历的顺序:" ;
	        tree.LevelOrder(virtualnode);//层次遍历 
	        cout<<endl ;
		}
		if(m==14){
			/*
	        二叉树的复制 
	        */
	        cout<<"复制后的二叉树为：";
	        BinTreeNode *copyTree;
	        tree.copy(virtualnode,copyTree);
	        tree.DispBTree(copyTree);
	        cout<<endl; 
		}
		if(m==0){
			cout<<"欢迎使用"<<endl; 
			break;
		}
    }
}
