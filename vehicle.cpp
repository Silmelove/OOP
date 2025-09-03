/*
Reflection:

Khi làm bài tập này, mình bắt đầu từ việc đọc kỹ yêu cầu của thầy: phải xây dựng một
lớp Vehicle với các thuộc tính cơ bản như loại xe và tốc độ, sau đó mở rộng thêm một
thuộc tính mới (fuelType) và viết thêm một phương thức để hiển thị thông tin. Lúc phân
tích mình hình dung thực tế ngoài đời: xe nào cũng có loại, có tốc độ tối đa và cần
nhiên liệu để chạy. Từ đó mình thấy việc gom các thông tin này vào một class là hợp lý.

Khó khăn mình gặp là chỗ xử lý đầu vào. Nếu người dùng nhập tốc độ bằng 0 hoặc âm
thì chương trình sẽ in ra kết quả khá vô lý, ví dụ như “xe tăng tốc đến 0 km/h”.
Ban đầu mình không nghĩ tới tình huống này, nhưng sau khi test thử thì mới thấy cần
phải kiểm tra dữ liệu và in cảnh báo rõ ràng. Mình cũng gặp chút khó khăn trong việc
giữ cho code gọn gàng, dễ đọc, nên mình cố gắng đặt tên biến, hàm theo kiểu CamelCase
và chia hàm rõ ràng.

Qua bài này mình thấy OOP khá hữu ích. Nhờ có tính đóng gói mà mình gom thuộc tính
và hành vi của xe vào cùng một lớp, dễ quản lý hơn. Constructor giúp khởi tạo dữ liệu
ngay từ đầu, còn các getter thì đảm bảo truy cập có kiểm soát.Làm xong
mình cảm thấy hiểu hơn cách OOP gắn với bài toán thực tế.
*/


#include <iostream>
#include <string>
using namespace std;

// Định nghĩa
class Vehicle {
private:
    string type;
    int maxSpeed;
    string fuelType;

public:
    // Constructor
    Vehicle(string t, int speed, string fuel) {
        type = t;
        // Kiểm tra giá trị speed
        if (speed < 0) {
            cout << "Warning: Toc do khong the am. Dat mac dinh = 0.\n";
            maxSpeed = 0;
        }
        else {
            maxSpeed = speed;
        }
        fuelType = fuel;
    }

    // Getter
    string getType() {
        return type;
    }

    int getMaxSpeed() {
        return maxSpeed;
    }

    string getFuelType() {
        return fuelType;
    }

    // Phương thức accelerate
    void accelerate() {
        if (maxSpeed == 0) {
            cout << "The " << type << " cannot accelerate because maxSpeed = 0.\n";
        }
        else {
            cout << "The " << type << " is accelerating to "
                << maxSpeed << " km/h." << endl;
        }
    }

    // Phương thức displayInfo
    void displayInfo() {
        cout << "Vehicle: " << type
            << ", Max Speed: " << maxSpeed << " km/h"
            << ", Fuel Type: " << fuelType << endl;
    }
};


int main() {
    // Test case 1: Bình thường
    Vehicle car("Car", 200, "Gasoline");
    Vehicle truck("Truck", 150, "Diesel");
    Vehicle motorcycle("Motorcycle", 180, "Gasoline");

    car.accelerate();
    truck.accelerate();
    motorcycle.accelerate();

    cout << "\n--- Display Info ---\n";
    car.displayInfo();
    truck.displayInfo();
    motorcycle.displayInfo();

    cout << "\n--- Test Cases ---\n";

    // Test case 2: maxSpeed = 0
    Vehicle bike("Bicycle", 0, "Human Power");
    bike.accelerate();
    bike.displayInfo();

    // Test case 3: maxSpeed âm
    Vehicle brokenCar("BrokenCar", -50, "Diesel");
    brokenCar.accelerate();
    brokenCar.displayInfo();

    cout << "\n--- User Input ---\n";

    // Người dùng tự nhập
    string userType, userFuel;
    int userSpeed;

    cout << "Nhap loai phuong tien: ";
    cin >> userType;
    cout << "Nhap toc do toi da (km/h): ";
    cin >> userSpeed;
    cout << "Nhap loai nhien lieu: ";
    cin >> userFuel;

    Vehicle userVehicle(userType, userSpeed, userFuel);
    userVehicle.accelerate();
    userVehicle.displayInfo();

    return 0;
}
