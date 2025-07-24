#include<bits/stdc++.h>
using namespace std;

class SGTree{
    private:
    vector<int>seg;
    public:
    SGTree(int n){
        seg.resize(4*n);
    }
    void build(int low,int high,vector<int>&arr,int ind){
        if(low == high){
            seg[ind] = arr[low];
            return ;
        }

        int mid = (low + high)/2;
        build(low,mid,arr,2*ind+1);
        build(mid+1,high,arr,2*ind+2);
        seg[ind] = min(seg[2*ind+1],seg[2*ind+2]);
    }
    int query(int ind,int low,int high,int l,int r){
        // low,high not in rage of l r
        if(r < low || l > high) return 1e9;
        // low high subset of l r
        if(low >= l && high <= r) return seg[ind];

        else{
            int mid = (low+high)/2;
            int left = query(2*ind+1,low,mid,l,r);
            int right = query(2*ind+2,mid+1,high,l,r);
            return min(left,right);
        }
    }
    void update(int ind,int low,int high,int i,int val,vector<int>&arr){
        if(low == high){
            if(i == low){
                arr[i] = val;
            }
            return ;
        }
        int mid = (low + high)/2;
        if(i <= mid){
            update(2*ind+1,low,mid,i,val,arr);
            seg[ind] = min(seg[2*ind+1],seg[2*ind+2]);
        }
        else{
            update(2*ind+2,mid+1,high,i,val,arr);
            seg[ind] = min(seg[2*ind+1],seg[2*ind+2]);
        }
    }

};


void solve(){
    int n,q;
    cin>>n>>q;
    vector<int>arr(n);
    for(int i=0;i<n;i++) cin>>arr[i];
    SGTree* sgt = new SGTree(n);
    sgt->build(0,n-1,arr,0);
    while(q--){
       int l,r;
       cin>>l>>r;
       cout<<sgt->query(0,0,n-1,l,r)<<endl;
    }
}
int main(){

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    
    solve();
}