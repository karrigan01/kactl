/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * License: CC0
 * Source: My head
 * Description: Basic operations on square matrices.
 * Usage: Matrix<int, 3> A;
 *  A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}};
 *  vector<int> vec = {1,2,3};
 *  vec = (A^N) * vec;
 * Status: tested
 */
struct matrix{
vector<vector<long long>>a;
int m,n;
void resz(int _m,int _n){
m=_m;
n=_n;
a.resize(m);
for1(i,0,m-1)a[i].resize(n);
}
matrix bs(int n1){
matrix res;
res.resz(n1,n1);
for1(i,0,n1-1){
res.a[i][i]=1;
}
return res;
}
matrix operator * (const matrix &r)const{
matrix res;
res.resz(m,r.n);
for1(i,0,m-1){
for1(j,0,n-1){
for1(k,0,r.n-1){
res.a[i][k]=res.a[i][k]+1ll*a[i][j]*r.a[j][k];
}
}
}
return res;
}
void operator = (const matrix &r) {
m=r.m;
n=r.n;
a=r.a;
}
matrix pw(long long n1) {
matrix res=bs(n);
matrix tmp;
tmp.a=a;
tmp.m=m;
tmp.n=n;
if (n1==0)return res;
while (n1>0){
    if (n1%2==1)res=(res*tmp);
    n1/=2;
    tmp=(tmp*tmp);
}
return res;
}
void print(){
for1(i,0,m-1){
    for1(j,0,n-1){
    cout<<a[i][j]<<" ";
    }
    cout<<'\n';
}
}
};
