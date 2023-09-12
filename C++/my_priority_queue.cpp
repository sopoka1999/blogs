#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
constexpr int maxn = 1e3+7;
constexpr int mod = 1e9+7;
class PrioQueue{
public:
    int len = 0;
    int num[maxn];
    void add(int x){
        num[++len] =  x;
        int now = len;
        while(now!=1){
            int fa = (now + 1) / 2;
            if(num[fa] < num[now]){
                swap(num[fa] , num[now]);
                now = fa;
            }else{
                break;
            }
        }
    }

    int top(){
        if(len){
            int res = num[1];
            swap(num[1], num[len]);
            len --;
            int now = 1;
            while(now*2+1<=len){
                int left = now*2, right = now*2+1;
                if(num[left]>=num[right]&&num[left]>=num[now]){
                    swap(num[left],num[now]);
                    now = left;
                }else if(num[right]>=num[left]&&num[right]>=num[now]){
                    swap(num[right],num[now]);
                    now = right;
                }else{
                    break;
                }
            }

            if(now*2<=len){
                if(num[now*2]>=num[now]){
                    swap(num[now*2],num[now]);
                    now = now * 2;
                }
            }
            return res;
        }else{
            return -1;
        }
    }
};


int main(){
    PrioQueue queue1;
    queue1.add(1);
    
    queue1.add(3);
    queue1.add(1);
    queue1.add(9);
    queue1.add(8);
   
    cout<<queue1.top()<<endl;
    cout<<queue1.top()<<endl;
    cout<<queue1.top()<<endl;
    cout<<queue1.top()<<endl;
    cout<<queue1.top()<<endl;

    return 0;
}
