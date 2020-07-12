# 典型ライブラリ

## データ構造編

### meldable heap (leftist heap)

```c++
template <class T,class Compare=function<bool(T,T)>>
struct Heap {
    struct Node {
        T key;
        Node *l, *r;
        int s;
        Node(T &key, Node *lt = NULL, Node *rt = NULL, int s = 0) {
            this->key = key;
            r = rt;
            l = lt;
            this->s = s;
        }
    };
    Node *root;
    Node *l, *r;
    Compare com;
    int size_;
    Heap(Compare comp = greater<T>()) : com(comp) {
        root = NULL;
        size_=0;
    }
    void meld(Heap &rhs) {
        if (this == &rhs) return;
        root = meld(root, rhs.root);
        size_+=rhs.size_;
        rhs.root = NULL;
    }
    Node *meld(Node *a, Node *b) {
        if (a == NULL) return b;
        if (b == NULL) return a;
        if (!com(a->key, b->key)) swap(a, b);
        if (a->l == NULL)
            a->l = b;
        else {
            a->r = meld(a->r, b);
            if (a->l->s < a->r->s) {
                swapChildren(a);
            }
            a->s = a->r->s + 1;
        }
        return a;
    }
    void swapChildren(Node *h) {
        Node *tmp = h->l;
        h->l = h->r;
        h->r = tmp;
    }
    void push(T x) {
        root = meld(new Node(x), root);
        size_++;
    }
    T top() {
        return root->key;
    }
    void pop() {
        Node *oldroot = root;
        root = meld(root->l, root->r);
        if(size_>0)size_--;
        delete oldroot;
    }
    bool empty() {
        return root == NULL;
    }
    int size(){
        return size_;
    }
};
```
### Union-Find Tree
```c++
struct uftree{
    int cou;
    vector<int> parent;
    vector<int> rank;
    vector<int> _size;
    uftree(int n){
        parent=vector<int>(n);
        rank=vector<int>(n,0);
        _size=vector<int>(n,1);
        cou=n;
        rep(i,n){
            parent[i]=i;
        }
    }
    int root(int i){
        return parent[i]==i?i:parent[i]=root(parent[i]);
    } 
    bool same(int i,int j){
        return root(i)==root(j);
    }
    void merge(int i,int j){
        i=root(i);j=root(j);
        if(i==j)return;
        cou--;
        if(rank[i]>=rank[j]){
            parent[j]=i;
            _size[i]+=_size[j];
        }else{
            parent[i]=j;
            _size[j]+=_size[i];
        }
        if(rank[i]==rank[j])rank[i]++;
        return;
    }
    int count(){
        return cou;
    }
    int unitsize(int i){
        return _size[root(i)];
    }
};
```
### 重みつきUnion-Find
```c++
template<class Abel>
struct ufwithw{
    int cou;
    vector<int> parent;
    vector<int> rank;
    vector<Abel> diff_weight;
    vector<int> _size;
    uftree(int n,Abel SUM_UNITY=0){
        parent.resize(n);
        rank=vector<int>(n,0);
        _size=vector<int>(n,1);
        diff_weight=vector<int>(n,SUM_UNITY);
        cou=n;
        rep(i,n){
            parent[i]=i;
        }
    }
    int root(int i){
        if(parent[i]==i){
            return i;
        }else{
            int r=root(parent[i]);
            diff_weight[i]+=diff_weight[parent[i]];
            return parent[i]=r;
        }
    } 
    bool same(int i,int j){
        return root(i)==root(j);
    }
    bool merge(int i,int j,int w){
        int ri=root(i),rj=root(j);
        if(ri==rj){
            //ここは問題によってさまざま
            return weight(i)+w==weight(j);
        }
        cou--;
        w+=weight(i);w-=weight(j);
        if(rank[ri]>=rank[rj]){
            diff_weight[rj]=w;
            parent[rj]=ri;
            _size[ri]+=_size[rj];
        }else{
            diff_weight[ri]=-w;
            parent[ri]=rj;
            _size[rj]+=_size[ri];
        }
        if(rank[ri]==rank[rj])rank[ri]++;
        return true;
    }
    int count(){
        return cou;
    }
    int unitsize(int i){
        return _size[root(i)];
    }
    Abel weight(int i){
        root(i);
        return diff_weight[i];
    }
    Abel diff(int i,int j){
        //ここも問題によってさまざま
        if(!same(i,j))return 0;
        return weight(j)-weight(i);
    }
};
```
## 典型実装編
### 典型bfs
```c++

const int Height=50,Width=50;
int h,w,sx,sy,gx,gy;\\入力待ち    
int mem[Height][Width],dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
char d[R][C];//'#'','で書かれていることを想定
int bfs(){
    for(int i=0;i<=h+1;i++){
        for(int j=0;j<=w+1;j++){
            mem[i][j]=INF10;
        }
    }
    queue<pint> que;
    pint a,next;
    que.push({sy,sx});
    mem[sy][sx]=0;
    while(que.size()){
        a=que.front();que.pop();
        if(a.first==gy&&a.second==gx)break;
        rep(i,4){
            n=p(a.first+dy[i],a.second+dx[i]);
            if(0<=next.first&&next.first<h&&0<=next.second&&next.second<w&&d[next.first][next.second]!='#'&&mem[next.first][next.second]==INF10){
                mem[next.first][next.second]=mem[a.first][a.second]+1;
                que.push(next);
            }
        }
    }
    return mem[gy][gx];
}
```
### minmax法
```c++
struct node{
    //ゲームの盤面の情報
    int game;
    node(){
        memset(s,0,sizeof(s));
    }
    void setvalue(){
    }
    bool empty(int x,int y){
    }
    //ゲーム木の次のノード
    node nextNode(int x,int y,int tof){
    }
    //評価値の計算
    int getscore(){
        int score=0;
        return score;
    }
};
//minmax
int minmax(node s,int depth){
    //depth_maxなんて先の評価値から逆算するか
    if(depth==depth_max){
        return s.getscore();
    }
    int res;
    if(相手の番なら){
        rep(i,9){
            int x=i%3,y=i/3;
            if(s.empty(x,y)){
                node ns=s.nextNode(x,y,dep);
                res=min(res,minmax(ns,depth+1));
            }
        }
    }else{
        res*=-1;
        rep(i,9){
            int x=i%3,y=i/3;
            if(s.empty(x,y)){
                node ns=s.nextNode(x,y,dep);
                res=max(res,minmax(ns,depth+1));
            }
        }
    }
    return res;
}
```
## 有名アルゴリズム編
### FFT
```c++
struct FFT{
    struct mycomplex{   
        double real;
        double imag;
        mycomplex(double a=0.0,double b=0.0):real(a),imag(b){}
        mycomplex operator-() const {return mycomplex(-real,-imag);}
        mycomplex &operator+=(const mycomplex &a){real+=a.real;imag+=a.imag;return *this;}
        mycomplex &operator-=(const mycomplex &a){real-=a.real;imag-=a.imag;return *this;}
        mycomplex &operator*=(const mycomplex &a){double nr=real*a.real-imag*a.imag;double ni=real*a.imag+imag*a.real;real=nr;imag=ni;return *this;}
        mycomplex &operator/=(const mycomplex &a){double nr=(real*a.real+imag*a.imag)/(a.real*a.real+a.imag*a.imag);double ni=(imag*a.real-real*a.imag)/(a.real*a.real+a.imag*a.imag);real=nr;imag=ni;return *this;}
        mycomplex &operator*=(const double &a){real*=a;imag*=a;return *this;}
        mycomplex &operator/=(const double &a){real/=a;imag/=a;return *this;}
        mycomplex operator+(const mycomplex &a) const {return mycomplex(*this)+=a;}
        mycomplex operator-(const mycomplex &a) const {return mycomplex(*this)-=a;}
        mycomplex operator*(const mycomplex &a) const {return mycomplex(*this)*=a;}
        mycomplex operator/(const mycomplex &a) const {return mycomplex(*this)/=a;}
        mycomplex operator*(const double &a) const {return mycomplex(*this)*=a;}
        mycomplex operator/(const double &a) const {return mycomplex(*this)/=a;}
        mycomplex conj() const {return mycomplex(real,-imag);}
        mycomplex polar(double r,double q) const {return mycomplex(r*cos(q),r*sin(q));}
    };
    
    typedef mycomplex clx;

    vector<clx> dft(vector<clx> f,int n,bool inverse=false){
        if(n==1)return f;
        vector<clx> a0,a1;
        rep(i,n)i%2==0?a0.push_back(f[i]):a1.push_back(f[i]);
        a0=dft(a0,n/2,inverse);
        a1=dft(a1,n/2,inverse);
        clx zeta(cos(2*pi/n),sin(2*pi/n));
        if(inverse)zeta=zeta.conj();
        clx x=clx(1);
        rep(i,n){
            f[i]=a0[i%(n/2)]+x*a1[i%(n/2)];
            x*=zeta;
        }
        return f;
    }
    vector<double> operator()(vector<double> a,vector<double> b){
        int ma=a.size(),mb=b.size();
        ll N=1;
        for(N;N<=ma+mb+1;N*=2);
        //0を詰める
        vector<clx> aa(N,clx()),bb(N,clx());
        for(int i=0;i<ma;i++)aa[i]=clx(a[i]);
        for(int i=0;i<mb;i++)bb[i]=clx(b[i]);

        aa=dft(aa,N);
        bb=dft(bb,N);

        vector<clx> res;
        rep(i,N+1)res.push_back(aa[i]*bb[i]);

        res=dft(res,N,true);

        vector<double> ans;
        rep(i,N+1)ans.push_back(res[i].real/N);
        return ans;
    }
};
```

### dijkstra
```c++
const int N_MAX=100;
int n;
vector<edge> v[N_MAX];
int d[N_MAX];

void dijkstra(int s) {
    priority_queue<pint, vector<pint>, greater<pint> > que;
    fill(d, d+n, INF);
    d[s] = 0;
    que.push(pint(0, s));

    while (!que.empty()) {
        pint p = que.top();
        que.pop();
        int w = p.second;
        if (d[w] < p.first) continue;

        for (int i=0; i<v[w].size(); ++i) {
            edge e = v[w][i];
            if (d[e.to] > d[w] + e.cost) {
                d[e.to] = d[w] + e.cost;
                que.push(pint(d[e.to], e.to));
            }
        }
    }
}
```
### kitamasa法

```c++
struct kitamasa{
    ll n;//次数
    vector<mint> a;//漸化式の係数
    vector<vector<mint>> mem;//a_n+i = \sum a_j mem[i][n-1-j]
    //kitamasa(漸化式の係数,次数)
    kitamasa(vector<mint> c,ll N) : a(c),n(N){
        vector<mint> r(2*n,0);
        rep(i,n)r[i]=c[i];
        mem.push_back(r);
        rep(i,n+1){
            mem.push_back(oneplass(mem[i]));
        }
    }
    //畳み込み
    vector<mint> closs(vector<mint> b){
        vector<mint> res(2*n,0);  
        vrep(i,2*n-2+1){
            mint a=0;
            rep(j,i+1){
                a+=b[j]*b[i-j];
            }
            res[i]=a;
        }
        return res;
    }
    //a_l の係数-> a_l+1 の係数
    vector<mint> oneplass(vector<mint> b){
        vector<mint> res(2*n,0);
        rep(i,n-1){
            res[i]=b[i+1]+b[0]*a[i];
        }
        res[n-1]=b[0]*a[n-1];
        return res;
    }
    //a_l の係数-> a_2*l の係数
    vector<mint> twotimes(vector<mint> b){
        vector<mint> res(2*n,0);
        auto bb=closs(b);
        rep(i,n-1){
            rep(j,n){
                bb[2*n-2-j]+=bb[n-2-i]*mem[i][n-1-j];
            }
            bb[n-2-i]=0;
        }
        rep(i,n){
            res[n-1-i]=bb[2*n-2-i];
        }
        return res;
    }
    //calculate(n)=a_nの係数
    vector<mint> calculate(int m){
        vector<mint> res(2*n,0);
        if(m<n){
            res[m]=a[m];
            return res;
        }
        if(m<=2*n){
            return mem[m-n];
        }else{
            if(m%2==0){
                auto b=calculate(m/2);
                res=twotimes(b);
            }else{
                auto b=calculate((m-1)/2);
                res=twotimes(b);
                res=oneplass(res);
            }
        }
        return res;
    }
};
```
 
## Bellman-Ford
```c++
bool BellmanFord(edges  w,int n,int start,vector<ll> &res){
    res.resize(n,INF15);
    
    res[start]=0;
    
    int count=0;
    bool tof=true;
    if(n<=1)return true;
    while(tof){
        count++;
        tof=false;
        arep(i,w){
            if(res[i.from]!=INF15&&minin(res[i.to],res[i.from]+i.cost)){
                tof=true;
            }
        }
        if(count==n)return false;
    }
    return true;
}
```

## 自前のstruct,class
### 複素数class
```c++
struct mycomplex{   
        double real;
        double imag;
        mycomplex(double a=0.0,double b=0.0):real(a),imag(b){}
        mycomplex operator-() const {return mycomplex(-real,-imag);}
        mycomplex &operator+=(const mycomplex &a){real+=a.real;imag+=a.imag;return *this;}
        mycomplex &operator-=(const mycomplex &a){real-=a.real;imag-=a.imag;return *this;}
        mycomplex &operator*=(const mycomplex &a){double nr=real*a.real-imag*a.imag;double ni=real*a.imag+imag*a.real;real=nr;imag=ni;return *this;}
        mycomplex &operator/=(const mycomplex &a){double nr=(real*a.real+imag*a.imag)/(a.real*a.real+a.imag*a.imag);double ni=(imag*a.real-real*a.imag)/(a.real*a.real+a.imag*a.imag);real=nr;imag=ni;return *this;}
        mycomplex &operator*=(const double &a){real*=a;imag*=a;return *this;}
        mycomplex &operator/=(const double &a){real/=a;imag/=a;return *this;}
        mycomplex operator+(const mycomplex &a) const {return mycomplex(*this)+=a;}
        mycomplex operator-(const mycomplex &a) const {return mycomplex(*this)-=a;}
        mycomplex operator*(const mycomplex &a) const {return mycomplex(*this)*=a;}
        mycomplex operator/(const mycomplex &a) const {return mycomplex(*this)/=a;}
        mycomplex operator*(const double &a) const {return mycomplex(*this)*=a;}
        mycomplex operator/(const double &a) const {return mycomplex(*this)/=a;}
        mycomplex conj() const {return mycomplex(real,-imag);}
        mycomplex polar(double r,double q) const {return mycomplex(r*cos(q),r*sin(q));}
    };
```
