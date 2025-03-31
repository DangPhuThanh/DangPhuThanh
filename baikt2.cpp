// Đặng Phú Thành
// MSSV: 3124411275
// Lớp: DCT1247C7
#include <iostream>
#include <cctype>   // Thư viện dùng để xử lý các ký tự (ví dụ: toupper)
#include <cstring>  // Thư viện dùng để xử lý chuỗi (ví dụ: strtok, strcmp, strcpy)
#include <cstdio>   // Thư viện dùng cho các hàm nhập xuất kiểu C (ví dụ: fgets)
using namespace std;

// Hàm đếm nguyên âm và phụ âm trong chuỗi
void Dem(const char* st, int &ng_a, int &ph_a) {
    for (int i = 0; i < strlen(st); i++) {
        char ch = st[i];
        ch = toupper(ch); // Chuyển ký tự thành chữ hoa để so sánh dễ dàng hơn

        // Kiểm tra xem ký tự có phải là nguyên âm không
        if (ch == 'A' || ch == 'U' || ch == 'O' || ch == 'E' || ch == 'I') {
            ng_a++; // Tăng số nguyên âm lên nếu ký tự là nguyên âm
        } else if (isalpha(ch)) { // Kiểm tra nếu là ký tự chữ cái, thì coi là phụ âm
            ph_a++; // Tăng số phụ âm lên
        }
    }
}

// Hàm tách chuỗi thành các từ và hiển thị các từ
void tachChuoiThanhTu(const char* st) {
    char temp[1000]; // Sao chép chuỗi để tránh thay đổi chuỗi ban đầu
    strcpy(temp, st);
    
    char* token = strtok(temp, " "); // Tách chuỗi bằng dấu cách
    int count = 0;
    // Duyệt qua các từ tách được
    while (token != NULL) {
        cout << "Từ: " << token << endl; // In từng từ ra
        count++; // Đếm số từ
        token = strtok(NULL, " "); // Tiếp tục tách chuỗi từ phần còn lại
    }
    cout << "Số từ trong chuỗi là: " << count << endl; // In ra tổng số từ trong chuỗi
}

// Hàm đếm tần suất xuất hiện của các từ trong chuỗi
void demTanSuat(const char* st) {
    char temp[1000];
    strcpy(temp, st);

    char a[20][50]; // Mảng 2 chiều lưu trữ các từ
    int n = 0;
    
    // Tokenize (tách chuỗi) theo dấu cách và dấu xuống dòng
    char *token = strtok(temp, " \n");  
    while (token != NULL) {
        strcpy(a[n], token); // Sao chép từ vào mảng
        n++;
        token = strtok(NULL, " \n"); // Tiếp tục tách chuỗi
    }
    
    int b[n] = {0};  // Mảng lưu trữ trạng thái đã đếm của từ, ban đầu là 0 (chưa đếm)

    // Đếm tần suất xuất hiện của mỗi từ
    for (int i = 0; i < n; i++) {
        if (b[i] == 0) {  // Nếu từ chưa được đếm
            int cnt = 1;  // Khởi tạo đếm số lần xuất hiện của từ
            for (int j = i + 1; j < n; j++) {
                if (strcmp(a[i], a[j]) == 0) {  // So sánh hai từ xem có giống nhau không
                    cnt++;  // Nếu giống nhau, tăng số lần xuất hiện
                    b[j] = 1;  // Đánh dấu rằng từ này đã được đếm
                }
            }
            // In ra từ và số lần xuất hiện của nó
            cout << a[i] << " xuat hien " << cnt << " lan" << endl;
        }
    }
}

// Hàm chính
int main() {
    char c[1000]; // Chuỗi có thể chứa tối đa 1000 ký tự
    char w[10];   // Từ cần loại bỏ
    int ng_a = 0;  // Biến đếm nguyên âm
    int ph_a = 0;  // Biến đếm phụ âm

    // Nhập chuỗi từ người dùng
    cout << "Nhap chuoi: ";
    fgets(c, sizeof(c), stdin);  

    // Nhập từ cần loại bỏ
    cout << "Nhập tu can bo: ";
    scanf("%s", w);  // Đọc từ cần loại bỏ

    // Tách chuỗi thành các từ và in ra các từ không phải là từ cần loại bỏ
    char *token = strtok(c, " ");
    char a[20][50];  // Mảng để lưu các từ đã loại bỏ từ c
    int n = 0;
    while (token != NULL) {
        if (strcmp(token, w) != 0) {  // Nếu từ không phải là từ cần loại bỏ
            strcpy(a[n], token);
            n++;
        }
        token = strtok(NULL, " ");  // Tiếp tục tách chuỗi
    }

    // In ra các từ sau khi đã loại bỏ từ cần loại bỏ
    cout << "Chuoi sau khi bo tu \"" << w << "\" la: ";
    for (int i = 0; i < n; i++) {
        printf("%s ", a[i]);
    }
    cout << endl;

    // Đếm số ký tự trong chuỗi
    int i = 0;
    while (c[i] != '\0') {  // Duyệt qua từng ký tự trong chuỗi
        i++;  // Tăng biến đếm lên
    }
    cout << "So ki tu cua chuoi la: " << i << endl; // In số ký tự trong chuỗi

    // Gọi hàm để đếm nguyên âm và phụ âm trong toàn bộ chuỗi
    Dem(c, ng_a, ph_a);

    // Hiển thị kết quả đếm nguyên âm và phụ âm
    cout << "So chu nguyen am trong toan bo chuoi la: " << ng_a << endl;
    cout << "So chu phu am trong toan bo chuoi la: " << ph_a << endl;

    // Đếm tần suất xuất hiện các từ trong chuỗi
    demTanSuat(c);

    cout << "Chuoi vua nhap: " << c << endl;

    return 0;
}
