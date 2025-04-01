// Đặng Phú Thành
// MSSV: 3124411275
// Lớp: DCT1247C7
#include <iostream>
using namespace std;

// Hàm tính x(n) dùng đệ quy
int calculate_xn1(int n) {
    // Trường hợp cơ bản: x0 = 1 và x1 = 1
    if (n == 0 || n == 1) return 1;

    int tong = 0;  // Khởi tạo tổng để tính x(n)

    // Tính tổng x0 + x1 + ... + x(n-1) bằng cách đệ quy
    for (int i = 0; i < n; i++) {
        tong += calculate_xn1(i);  // Gọi đệ quy để tính giá trị của x(i)
    }

    return n * tong;  // Nhân tổng với n để tính giá trị x(n)
}

// Hàm tính x(n) không dùng đệ quy
int calculate_xn2(int n) {
    // Trường hợp cơ bản: x0 = 1 và x1 = 1
    if (n == 0 || n == 1) return 1;

    int xn = 1;  // Giá trị x(n) khởi tạo bằng 1
    int sum = 1;  // Tổng của x0 đến x(n-1) bắt đầu bằng 1 (vì x0 = 1)

    // Tính giá trị x(n) cho các giá trị từ 2 đến n
    for (int i = 2; i <= n; i++) {
        sum += xn;  // Cộng thêm giá trị của x(i) vào tổng
        xn = i * sum;  // Tính giá trị x(n) mới bằng n nhân với tổng
    }

    return xn;  // Trả về giá trị x(n)
}

int main() {
    int n;

    // Yêu cầu người dùng nhập giá trị n
    cout << "Nhập n: ";
    cin >> n;

    // Tính và in giá trị x(n) bằng đệ quy
    cout << "x(" << n << ") (dùng đệ quy) = " << calculate_xn1(n) << endl;

    // Tính và in giá trị x(n) không dùng đệ quy
    cout << "x(" << n << ") (không dùng đệ quy) = " << calculate_xn2(n) << endl;

    return 0;  // Kết thúc chương trình và trả về giá trị 0
}
