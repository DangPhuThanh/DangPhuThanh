#include <iostream>
using namespace std;
void NhapMang(int *a,int n){
    for(int i=0;i<n;i++){
        cout<<"Nhap a["<<i<<"]:";
        cin>>a[i];
    }
}
void XuatMang(int *a,int n){
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
void TimPhanTu(int *a,int n){
    while (n<2)
    {
        cout<<"Mang khong co phan tu lon thu 2"<<endl;
      return;
    }
    int max=a[0];
    int max2;
    for(int i=1;i<n;i++){
        if(a[i]>max){
            max2=max;
            max=a[i];
        }
        else if(a[i]>max2&&a[i]!=max){
            max2=max;
            max=a[i];
        }
    }
    cout<<"Phan tu lon thu nhat la:"<<max<<endl;
    cout<<"Phan tu lon thu 2 la:"<<max2<<endl;
    
}
int main(){
    int n;
    cout<<"Nhap n:";
    cin>>n;
    int *a=new int[n];
    NhapMang(a,n);
    XuatMang(a,n);
    TimPhanTu(a,n);
    delete []a;
    return 0;
}