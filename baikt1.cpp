// Đặng Phú Thành
// MSSV: 3124411275
// Lớp: DCT1247C7
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream file;
    file.open ("test.txt"); // Mở file đầu vào

    if (!file) { // Kiểm tra nếu file không mở được
        cout << "Khong the mo file!" << endl;
        return 1;
    }

    int m, n;
    file >> m >> n; // Đọc số dòng (m) và số cột (n)
    cout << "So dong (m): " << m << ", So cot (n): " << n << endl;

    // Cấp phát động mảng 2 chiều
    int** a = new int*[m]; 
    for (int i = 0; i < m; i++) {
        a[i] = new int[n]; // Cấp phát động từng hàng
    }

    // Đọc dữ liệu từ file vào mảng động
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            file >> a[i][j];
        }
    }

    file.close(); // Đóng file

    // Xuất dữ liệu đã đọc được
    cout << "Cac so nguyen doc duoc tu file:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    // Tìm giá trị lớn nhất trong mảng
    int max = a[0][0]; // Khởi tạo giá trị lớn nhất là phần tử đầu tiên
    int max2;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] > max) {
                max2=max;
                max = a[i][j];
            }
            else if(a[i][j]>max2 && a[i][j]<max){
                max2=a[i][j];
            }
        }
    }

    cout << "Gia tri lon nhat trong mang: " << max<< endl;
    cout << "Gia tri lon thu 2 trong mang: " << max2<< endl;
    //tính tổng các phần tử trên mỗi cột
    
    for (int i=0;i<n;i++){
        int sum=0;
        for (int j=0;j<m;j++){
            sum+=a[j][i];
        }
        cout<<"Tong cua cot "<<i+1<<" la: "<<sum<<endl;
    }
    
//tạo mảnng C từ mảng A sao cho  cij = aij * ki với ki là số nhỏ nhất trong dòng i.
  // Cấp phát động cho mảng 2 chiều c với kích thước m x n
int** c = new int*[m]; // Tạo một mảng con chứa m con trỏ, mỗi con trỏ đại diện cho một hàng của ma trận c
for (int i = 0; i < m; i++) {
    c[i] = new int[n]; // Cấp phát động cho từng hàng, mỗi hàng có n phần tử
}

// Duyệt qua từng hàng trong ma trận a
for (int i = 0; i < m; i++) {
    int min = a[i][0]; // Giả sử phần tử đầu tiên của hàng là phần tử nhỏ nhất (min) ban đầu
    for (int j = 0; j < n; j++) {
        if (a[i][j] < min) { // Kiểm tra xem có phần tử nào nhỏ hơn min không
            min = a[i][j]; // Cập nhật min nếu tìm thấy phần tử nhỏ hơn
        }
    }

    // Sau khi có min, nhân tất cả các phần tử của hàng với min
    for (int j = 0; j < n; j++) {
        c[i][j] = a[i][j] * min; // Lưu kết quả vào mảng c
    }
}

// In ra ma trận c sau khi xử lý
cout << "Mang C la: " << endl;
for (int i = 0; i < m; i++) { // Duyệt qua từng hàng của mảng c
    for (int j = 0; j < n; j++) { // Duyệt qua từng phần tử trong hàng
        cout << c[i][j] << " "; // In phần tử tại vị trí (i, j) của ma trận c
    }
    cout << endl; // Xuống dòng sau mỗi hàng
}
    // Ghi dữ liệu vào file output.txt
    ofstream outFile("output.txt"); 
    outFile << m << " " << n << endl; // Ghi số dòng và cột
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            outFile << a[i][j] << " ";
        }
        outFile << endl;
    }
    outFile << "Gia tri lon nhat: " << max<< endl;
    outFile << "Gia tri lon thu 2: " << max2<< endl;
    outFile << "Tong cac phan tu tren moi cot: "<<endl;
    outFile.close(); // Đóng file output

    // Giải phóng bộ nhớ đã cấp phát động
    for (int i = 0; i < m; i++) {
        delete[] a[i]; // Giải phóng từng hàng
    }
    delete[] a; // Giải phóng mảng chính

    return 0;
}
