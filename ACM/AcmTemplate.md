## C++模版

```c++
#include <iostream>
#include <vector>
using namespace std;
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define per(i,a,b) for (int i=(b);i>=(a);i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef long long ll;
typedef vector<int> VI;
typedef pair<int,int> PII;

const ll mod=998244353 ;
const int maxn=2e5+7;

int main() {

  return 0;
} 
```



## java模版

```java
import java.math.BigInteger;
import java.util.Scanner;
import java.math.BigDecimal;
public class Main{
  public static void main(String[] args){
    Scanner cin=new Scanner(System.in);
  }
}
public static void add(){
}
```



# 字符串

## String类的基本用法

substring(a,b) 	将字符串取出[a,b),组成新的字符串

indexOf(ch) 		返回字符串ch第一次出现的位置，没有则-1



## 马拉车

```C++
void manacher(){
  int len=strlen(word1+1);
  int cnt=0;
  word2[++cnt]='#';
  rep(i,1,len){
    word2[++cnt]=word1[i];
   	word2[++cnt]='#';
	}
  len=cnt;
  int maxx=0,id=1;
  rep(i,1,len){
    if(i<maxx){
      p[i]=min(p[2*id-i],maxx-i);
  	}else{
      p[i]=0;
    }
    while(i-p[i]-1>=1&&i+p[i]+1<=len&&word2[i+p[i]+1]==word2[i-p[i]-1])p[i]++;
    if(i+p[i]>maxx){
      id=i;
      maxx=i+p[i];
    }
  }
}
```



## 后缀自动机

```C++
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
typedef long long ll;
char S[N/2];
char ans[N/2];
int fla,k,top;
struct suffixautomation{
  int mp[N][30];int fa[N];int ed;int ct;int len[N];int siz[N];
  ll weight[N];
  int z[N],A[N];
  suffixautomation(){ed=ct=1;}
  inline void ins(int c,int pos){
    int p=ed;siz[ed=++ct]=1;len[ed]=pos;//先初始化size和len
    for(;p&&mp[p][c]==0;p=fa[p]){mp[p][c]=ed;}//然后顺着parent树的路径向上找
    if(p==0){fa[ed]=1;return;}int q=mp[p][c];//case1
    if(len[p]+1==len[q]){fa[ed]=q;return;}//case2
    len[++ct]=len[p]+1;//case 3
    for(int i=1;i<=26;i++){mp[ct][i]=mp[q][i];}
    fa[ct]=fa[q];fa[q]=ct;fa[ed]=ct;
    for(int i=p;mp[i][c]==q;i=fa[i]){mp[i][c]=ct;}
  }

  void solve(){
    //sort
    for(int i=1;i<=ct;i++)z[len[i]]++;
    for(int i=1;i<=ct;i++)z[i]+=z[i-1];
    for(int i=1;i<=ct;i++)A[z[len[i]]--]=i;
    for(int i=ct;i>=1;i--){
      if(fla)siz[fa[A[i]]]+=siz[A[i]];
      else siz[fa[A[i]]]=1;
    }
    for(int i=ct;i>=1;i--){
      //   cout<<A[i]<<endl;
      int v=A[i];
      weight[v]=siz[v];
      for(int j=1;j<=26;j++)
        if(mp[v][j])weight[v]+=weight[mp[v][j]];
    }
    weight[1]-=siz[1];
    if(k>weight[1]){
      printf("-1\n");
      return ;
    }
    int now=1;
    while(1){
      for(int i=1;i<=26;i++)
        if(k>weight[mp[now][i]]){
          k-=weight[mp[now][i]];
        }else{
          now=mp[now][i];
          ans[++top]='a'+i-1;
          break;
        }
      if(k<=siz[now])break;
      else k-=siz[now];
    }
    ans[++top]=0;
    printf("%s\n",ans+1);
  }
}sam;

int main(){
  scanf("%s",S+1);
  scanf("%d %d",&fla,&k);
  int len=strlen(S+1);
  for(int i=1;i<=len;i++)sam.ins(S[i]-'a'+1,i);
  sam.solve();
  return 0;
}
```



# 数据结构

## 线段树

```C++
lazy和tree数组都需要开四倍空间

//建树
void build(int st,int en,int rt){
  int md=(st+en)/2;
  lazy[rt]=0;
  if(st==en){
    tree[rt]=num[st];
    return ;
  }
  build(st,md,rt*2);
  build(md+1,en,rt*2+1);
  tree[rt]=max(tree[rt*2],tree[rt*2+1]);
}


//[l,r]区间加x
void update(int l,int r,int x,int st,int en,int rt){
  int md=(st+en)/2;
  //if(rt==1)cout<<l<<" "<<r<<" "<<x<<endl;
  if(l>r||l>en||r<st)return ;
  if(l<=st&&r>=en){
    tree[rt]+=x;
    lazy[rt]+=x;
    return ;
  }
  if(lazy[rt]){
    tree[rt*2]+=lazy[rt];
    lazy[rt*2]+=lazy[rt];
    tree[rt*2+1]+=lazy[rt];
    lazy[rt*2+1]+=lazy[rt];
    lazy[rt]=0;
  }
  update(l,r,x,st,md,rt*2);
  update(l,r,x,md+1,en,rt*2+1);
  tree[rt]=max(tree[rt*2],tree[rt*2+1]);
}

//查询区间[l,r]的最大值
int quer(int l,int r,int st,int en,int rt){
  int md=(st+en)/2;
  if(l>en||r<st)return -1e9;
  if(l<=st&&r>=en)return tree[rt];
  if(lazy[rt]){
    tree[rt*2]+=lazy[rt];
    lazy[rt*2]+=lazy[rt];
    tree[rt*2+1]+=lazy[rt];
    lazy[rt*2+1]+=lazy[rt];
    lazy[rt]=0;
  }
  int res=max(quer(l,r,st,md,rt*2),quer(l,r,md+1,en,rt*2+1));
  tree[rt]=max(tree[rt*2],tree[rt*2+1]);
  return res;
}
```



## 主席树

```c++
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=1e5+5;
struct Tree{
     int L,R,num;
}tree[maxn*20];
int root[maxn];
int cnt;
void updata(int x,int &rt,int a,int b){
  tree[cnt++]=tree[rt];
  rt=cnt-1;
  tree[rt].num++;
  if(a==b)return;
  int mid=(a+b)/2;
  if(x>=mid+1)
    updata(x,tree[rt].R,mid+1,b);
  else
    updata(x,tree[rt].L,a,mid);
}
int quer(int a,int b,int k,int s,int o){
  if(s==o)return s;
  int d=tree[tree[b].L].num-tree[tree[a].L].num;
  int mid=(s+o)/2;
  if(k<=d)
    return quer(tree[a].L,tree[b].L,k,s,mid);
  else
    return quer(tree[a].R,tree[b].R,k-d,mid+1,o);
}
int main(){
  int n,m;
  while(cin>>n>>m){
    cnt=1;
    for(int i=1;i<=n;i++){
      root[i]=root[i-1];
      int num;
      scanf("%d",&num);
      updata(num,root[i],1,n);
    }
    for(int i=1;i<=m;i++){
      int l,r;
      scanf("%d %d",&l,&r);
      int b=r-l+1,a=1;
      int mid=(a+b)/2;
      while(a!=b){
        if(quer(root[l-1],root[r],r-l+1-mid,1,n)>=mid+1)
          a=mid+1;
        else
          b=mid;
        mid=(a+b)/2;
      }
      printf("%d\n",a);
    }
  }
   return 0;
}
```



# 数论

## 快速幂

```c++
普通
ll mypow(ll x,ll n){
    ll res=1;
    while(n){
        if(n&1)res=res*x%mod;
        x=x*x%mod;
        n/=2;
    }
    return res;
}

矩阵
struct matrix {
   ll num[2][2];
}one;
matrix mul(matrix a,matrix b){
    matrix res;
    rep(i,0,1){
        rep(j,0,1){
            res.num[i][j]=0;
            rep(k,0,1)res.num[i][j]=(res.num[i][j]+a.num[i][k]*b.num[k][j]%mod)%mod;
        }
    }
    return res;
}
matrix mypow(matrix x,ll n){
    mat res=one;
    while(n){
        if(n&1)res=mul(res,x);
        x=mul(x,x);
        n/=2;
    }
    return res;
}
```


## 欧拉函数

用途：求1到n-1中与n互质的个数

复杂度：O(sqrtn)

```c++
int euler(int n){
  int res=n,a=n;
  for(int i=2;i*i<=a;i++){
    if(a%i==0){
      res=res/i*(i-1);
      while(a%i==0)
        a/=i;
    }
  }
  if(a>1)res=res/a*(a-1);
  return res;
}
```

 

## 扩展欧几里得

用途：求ax+by=gcd（a，b）中的特解（x1，y1），进而根据x=x1+k(b/gcd),y=x1+k(a/gcd)得到通解,当mod不为素数的时候，费马小定理无效，可以用扩展欧几里得算法求逆元

复杂度: $O(lgn)$

```c++
ll gcdd(ll a,ll b,ll &x,ll &y){
  if(b==0){
    x=1;
    y=0;
    return a;
  }
  ll res=gcdd(b,a%b,x,y);
  ll temp=x;
  x=y;
  y=temp-a/b*y;
  return res;
}
```



## 组合数的公式

$C(n,0)^2+C(n,1)^2+C(n,2)^2+...+C(n,n)^2=C(2n,n)$

$C(n,m)=C(n-1,m-1)+C(n-1,m)$

$C(n,m)=n!/[m!(n-m)!]$



## 线性素数筛

用途：在线性时间打出一个素数表和判断某个数是否为素数的表

原理：一个合数肯定可以等于一个素数和另一个比这个素数大的数相乘

复杂度：接近 $O(n)$

 ```C++
 for(int i=2; i<maxn; i++){
 	if(is[i]==0)prim[cnt++]=i;
   for(int j=1; j<=cnt; j++){
     if(prim[j]*i>=maxn)break;
     is[prim[j]*i]=-1;
     //if(i%prim[j]==0)break;//加快一倍左右  
     //i*prim[j+x]可以由prim[j]*num组成，也就是将来我们会将它筛掉
   }
 }
 
 ```



## 莫比乌斯反演

定义 $U(x)$ 函数

当 $x=1$ 时, $U(x)=1$

当 $x=p_1p_2p_3…p_n$ ( $p$ 为不同的质数，且次数dou为1), $U(x)=(-1)^n$ 

其余情况 $U(x)=0$ 



## Burnside引理与Polya定理

$$1=\frac{1}{|G|}[c_1(a_1)+c_2(a_2)+c_3(a_3)+....c_g(a_g)]$$



## 斯特拉公式

$$n!\approx \sqrt {2\pi n}(\frac{n}{e})^{n}$$



## 线性基

```c++
bool insert(int x){ //插入x
  for(int i=63;i>=1;i--){
    if(x&(1ll<<i)){
      if(a[i]==0){
        a[i]=x;//放入线性基，那么可以是插入的了
        return 1;
      }
      else x^=a[i];//否则插入x^a[i]，既然a[i]插入了，并且x^a[i]插入了，那么相当于x也插入了
    }
  }
  return 0;
}
//求最大异或和
for(int i=62;i>=0;i--) if((ans^p[i])>ans) ans=ans^p[i];//从线性基中得到最大值   
```

 

## 数学小常识

### 约数

位数为 $n$ 的数，最多有 $2^{n+1}$ 个约数

$1$ 到 $10^{n}$ 的数平均下来每个数有16个约数



# 图论

## 最短路径

### 迪杰斯特拉

```c++
//堆优化版本，复杂度O(v*lgn)
void dij(int s,int f){
  priority_queue<node> q;
  node t,to;
  mem(dis[f],0x3f);
  mem(flag,0);
  dis[f][s]=0;
  q.push(node(s,0));
  while(!q.empty()){
    t=q.top();
    q.pop();
    if(flag[t.id]) continue;
    flag[t.id]=1;
    for(int i=0;i<sz(mp[t.id]);i++){
      to=mp[t.id][i];
      if(dis[f][to.id]>dis[f][t.id]+to.v){
        dis[f][to.id]=dis[f][t.id]+to.v;
        q.push(node(to.id,dis[f][to.id]));
      }
    }
  }
}
```



```c++

//不优化版本，复杂度O(n*n)
void dij(){
  memset(ins,0,sizeof(ins));
  for(int i=2;i<=n;i++)
    dis[i]=ma[1][i];
  dis[1]=0;
  ins[1]=1;
  while(1){
    int minn=INF,index;
    for(int i=1;i<=n;i++){
      if(ins[i]==0&&dis[i]<minn){
        minn=dis[i];index=i;
      }
    }
    if(minn==INF)break;
    ins[index]=1;
    for(int i=1;i<=n;i++){
      if(ins[i]==0&&ma[index][i]+dis[index]<dis[i])
        dis[i]=ma[index][i]+dis[index];
    }
  }
  printf("%d\n",dis[n]);

}
```



### SPFA

```c++
//复杂度比迪杰斯特拉高，在存在负权边时使用
void spfa(){
  for(int i=1;i<=n;i++)ins[i]=0;
  queue<Node>que;
  for(int i=1;i<=n;i++)
    dis[i]=INF;
  dis[1]=0;
  que.push(Node(1));
  while(que.size()){
    int x=que.front().x;
    que.pop();
    ins[x]=0;
    for(int i=1;i<=n;i++){
      if(dis[i]>dis[x]+ma[x][i]){
        dis[i]=dis[x]+ma[x][i];
        if(ins[i]==0){
          ins[i]=1;
          que.push(Node(i));
        }
      }
    }
  }
  printf("%d\n",dis[n]);
}
```

 

### 弗洛伊德

```c++
//复杂度O(n*n*n)
void floyd()
{
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
      for(int k=1;k<=n;k++)
        ma[j][k]=min(ma[j][k],ma[j][i]+ma[i][k]);
}
```



### 总结

对于边权都为1的图，可以直接用bfs求出最短距离

## 第k短路

用途：求第k短路

原理：先将边取反，再用迪杰斯特拉算出终点到每个点的距离，用优先队列，按照当前长度+g数组构建优先级，从起点开始，每走到一次终点num++，直到num=k

复杂度：$O(n^{2})$

## 网络流

```c++
ll get_path(int s,int t){
  for(int i=0; i<maxn; i++)vis[i]=0,pre[i]=-1;
  queue<int>que;
  que.push(s);
  vis[s]=1;
  ll res=1e9;
  while(que.size()){
    int x=que.front();
    que.pop();
    for(int i=1; i<=n; i++){
      if(vis[i]==0&&ma[x][i]!=0){
        vis[i]=1;
        pre[i]=x;
        res=min(res,ma[x][i]);
        que.push(i);
        if(i==t)return res;//到达终点
      }
    }
  }
  return 0;//无法到达终点
}
void updata(int t,int add)//更新边{
  int i=t;
while(pre[i]!=-1){
  ma[pre[i]][i]-=add;
  ma[i][pre[i]]+=add;
  i=pre[i];
}
}

```



## 二分图

最大独立子集+最小顶点覆盖=$V$

最小顶点覆盖=最大匹配

找独立子集的方法是，从左边所有没有匹配的点出发，去找到一条没匹配，匹配，没匹配，匹配的路径，并且标记路径上的点，选出左边标记点和右边未标记的点作为独立子集

```c++
bool dfs(int x){
  vis[x]=1;
  for(int i=head[x];i;i=edge[i].nex){
    int v=edge[i].to;
    if(vis[v]==0){
      vis[v]=1;
      if(match[v]==0||dfs(match[v])){
        match[v]=x;
        match[x]=v;
        return 1;
      }
    }
  }
  return 0;
}
```



## Bron–Kerbosch（非二分图最大团）

对于二分图求最大团我们可以用匈牙利匹配来求

最大独立子集=补图的最大团

$3^{\frac{n}{3}}$

``` c++
int some[maxn][maxn];//和当前团的每个节点都有边的点
int none[maxn][maxn];//包含这个节点的团已经被搜索过了
int all[maxn][maxn];//当前团
int ma[maxn][maxn];//邻接矩阵

void dfs(int d, int an, int sn, int nn){
  if(!sn && !nn){//找到极大团
    ans=max(ans,an);
    return ;
  }
  int pivot = some[d][1];//轴点
  for(int j = 1; j <=an; ++j)
    all[d+1][j] = all[d][j];
  for(int i = 1; i <= sn; ++i){
    int v = some[d][i];
    //选择轴点的时候肯定尝试过把这个点加入到all数组中
    if(ma[pivot][v]) continue;
    all[d+1][an+1] = v;
    int tsn = 0, tnn = 0;
    for(int j = 1; j <=sn; ++j)
      if(ma[v][some[d][j]])
        some[d+1][++tsn] = some[d][j];
    for(int j = 1; j <=nn; ++j)
      if(ma[v][none[d][j]])
        none[d+1][++tnn] = none[d][j];
    dfs(d+1, an+1, tsn, tnn);
    some[d][i] = 0, none[d][++nn] = v;
  }
}
void maximalcliques(){
  //把每个点都放入some数组
  for(int i = 1; i <= n; ++i) some[1][i] = i;
  dfs(1, 0, n, 0);
}
```

 

## Tarjan缩点算法

```c++
void dfs(int x){
  st.push(x);      //加入栈
  dis[x]=1;        //x点在栈中
  dfn[x]=low[x]=++te;    //dfn用来表示某个点访问过，并且记录初始的low值
  for(int i=f[x]; i; i=nex[i]){
    int v=to[i];
    if(dfn[v]==0){
      dfs(v);
      low[x]=min(low[x],low[v]);   //将一个回路的low改成一样的
    }
    else if(dis[v]==1)low[x]=min(low[x],low[v]);    //下一个点在栈中，那么找到一个回路，但是可能是嵌套回路，所以取最小low
  }
  if(dfn[x]==low[x]){ //表示x点的初始值没有被改变，构成一个强连通分量
    while(st.size()){
      int g=st.top();
      st.pop();
      dis[g]=0;
      id[g]=x;    //用x命名强连通分量
      if(g==x)break;  //代表g是强连通分量的最后一个数
    }
  }
}
```



## lca

```c++
int vis[maxn],fa[maxn][21],dep[maxn];
void dfs(int x,int fx){
  if(vis[x])return ;
  vis[x]=1;
  dep[x]=dep[fx]+1;
  fa[x][0]=fx;
  for(int i=1;(1<<i)<dep[x];i++)
    fa[x][i]=fa[fa[x][i-1]][i-1];
  for(int i=0;i<ve[x].size();i++)
    if(ve[x][i]!=fx)dfs(ve[x][i],x);
}
int lca(int a,int b){
  if(dep[a]>dep[b])swap(a,b);
  for(int i=19;i>=0;i--)
    if(dep[fa[b][i]]>=dep[a])b=fa[b][i];
  if(a==b)return a;
  for(int i=19;i>=0;i--)
    if(fa[a][i]!=fa[b][i])a=fa[a][i],b=fa[b][i];
  return fa[a][0];
}
```



# 计算几何

## 向量叉积

$$A(x_1,y_1)\times B(x_2,y_2)=y_1x_2-x_1y_2=|A|\times |B|\times sin(A,B)$$



## 皮克定理

皮克定理是指一个计算点阵中顶点在格点上的多边形面积公式

该公式可以表示为 $2S=2a+b-2$ ，其中 $a$ 表示多边形内部的点数，  $b$  表示多边形边界上的点数，  $S$ 表示多边形的面积



# 博弈论

## sg函数

若sg值为零则先手必败，sg值为下一步的sg值中没取的最小值



## 斐波拉契博弈

先手不能一次取完，下一个人不能超过上一次的两倍，如果石子数为斐波那契数列那么先手败， $f[0]=f[1]=1$



# 小技巧

## eclipes配置

自动补全：java->editor->content assist

自动缩进：ctrl+shift+F



## java高精度基本操作

valueOf(parament) 将参数转换为指定的类型

add() 				相加

subtract()	 	相减  

multiply()	 	相乘

divide() 			相除

abs()  				绝对值  

negate()			取反数

compareTo()	比较大小	

stripTrailingZeros()		去除后导零

toPlainString()				 将高精度浮点数转换为字符串，防止输出为科学计数法

ROUND_HALF_UP			小学的四舍五入

divide(b,8,BigDecimal.ROUND_HALF_UP)	 保留8位有效数字，四舍五入，遇到5进一位



## 对拍和重定向

```c++
freopen("F:\\in.txt","r",stdin); 
freopen("F:\\out.txt","w",stdout);
//头文件：time.h  stdlib.h
srand((unsigned)time(NULL));
rand();//返回的随机数是1到	32767
```