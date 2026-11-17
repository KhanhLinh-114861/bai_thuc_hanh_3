#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;
int nhapSoNguyen(const string& thongBao, int thapNhat, int caoNhat) {
    int giaTri;
    while (true) {
        cout << thongBao;
        cin >> giaTri;
        if (cin.fail()) {
            if (cin.eof()) exit(0);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [Loi] Vui long nhap vao mot SO nguyen hop le!\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (giaTri < thapNhat || giaTri > caoNhat) {
            cout << "  [Loi] Gia tri phai nam trong khoan tu " << thapNhat << " den " << caoNhat << "!\n";
            continue;
        }
        return giaTri;
    }
}
char nhapKichThuoc() {
    string chuoi;
    while (true) {
        cout << "Kich thuoc bai (S/M/L): ";
        cin >> chuoi;
        if (cin.eof()) exit(0);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (chuoi.size() == 1) {
            char kyTu = toupper(chuoi[0]);
            if (kyTu == 'S' || kyTu == 'M' || kyTu == 'L') return kyTu;
        }
        cout << "  [Loi] Chi chap nhan cac ky tu S, M hoac L!\n";
    }
}

string chuanHoaLoaiXe(string chuoi) {
    for (size_t i = 0; i < chuoi.size(); ++i) chuoi[i] = tolower(chuoi[i]);
    if (chuoi == "car") return "O to";
    if (chuoi == "motorcycle") return "Xe may";
    if (chuoi == "bicycle") return "Xe dap";
    return "";
}

string nhapLoaiXe() {
    string nhapVao, ketQua;
    while (true) {
        cout << "Loai xe (Car/Motorcycle/Bicycle): ";
        cin >> nhapVao;
        if (cin.eof()) exit(0);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        ketQua = chuanHoaLoaiXe(nhapVao);
        if (ketQua != "") return ketQua;
        cout << "  [Loi] Loai xe khong hop le! Vui long nhap dung (Car/Motorcycle/Bicycle).\n";
    }
}
///////////////////////////////
class Vehicle {
private:
    int maXe;
    string loaiXe;
    int gioVao;
    int thoiLuongDo;
    double phiDoXe;

public:
    Vehicle();
    Vehicle(int id, const string& type, int entry, int duration);

    int getMaXe() const;
    string getLoaiXe() const;
    int getGioVao() const;
    int getThoiLuongDo() const;
    double getPhiDoXe() const;

    void setMaXe(int id);
    void setLoaiXe(const string& type);
    void setGioVao(int entry);
    void setThoiLuongDo(int duration);

    double tinhPhiDoXe();
    void hienThi() const;
};

Vehicle::Vehicle()
    : maXe(0), loaiXe(""), gioVao(0), thoiLuongDo(0), phiDoXe(0.0) {}

Vehicle::Vehicle(int id, const string& type, int entry, int duration)
    : maXe(id), loaiXe(type), gioVao(entry), thoiLuongDo(duration), phiDoXe(0.0) {
    tinhPhiDoXe();
}

int Vehicle::getMaXe() const { return maXe; }
string Vehicle::getLoaiXe() const { return loaiXe; }
int Vehicle::getGioVao() const { return gioVao; }
int Vehicle::getThoiLuongDo() const { return thoiLuongDo; }
double Vehicle::getPhiDoXe() const { return phiDoXe; }

void Vehicle::setMaXe(int id) { maXe = id; }
void Vehicle::setLoaiXe(const string& type) { loaiXe = type; tinhPhiDoXe(); }
void Vehicle::setGioVao(int entry) { gioVao = entry; tinhPhiDoXe(); }
void Vehicle::setThoiLuongDo(int duration) { thoiLuongDo = duration; tinhPhiDoXe(); }

double Vehicle::tinhPhiDoXe() {
    double mucGia = (loaiXe == "O to") ? 6.0 : (loaiXe == "Xe may") ? 4.0 : 2.0;
    bool gioCaoDiem = (gioVao >= 6 && gioVao <= 9) || (gioVao >= 15 && gioVao <= 18);
    double tongTien = 0;
    for (int h = 0; h < thoiLuongDo; ++h) {
        if (h < 2) tongTien += mucGia * (gioCaoDiem ? 1.30 : 0.95);   
        else       tongTien += mucGia * 0.90;                       
    }
    phiDoXe = tongTien;
    return phiDoXe;
}

void Vehicle::hienThi() const {
    cout << "  Ma xe: " << maXe << " | " << loaiXe
         << " | Gio vao: " << gioVao << "h | Thoi luong: " << thoiLuongDo << "h"
         << " | Phi: $" << fixed << setprecision(2) << phiDoXe << "\n";
}
///////////////////////////////////////////////////////////////
class ParkingLot {
private:
    int maBaiDo;
    char kichThuocBai;
    int sucChua;
    int soLuongXeHienTai;
    Vehicle** danhSachXe;          
    void thayDoiKichCo(int sucChuaMoi);

public:
    ParkingLot();
    ParkingLot(int id, char sz);
    ParkingLot(const ParkingLot& other);              
    ParkingLot& operator=(const ParkingLot& other);   
    ~ParkingLot();                                   

    int getMaBaiDo() const;
    char getKichThuocBai() const;
    int getSucChua() const;
    int getSoLuongXeHienTai() const;
    const Vehicle& getXeTaiViTri(int index) const;

    bool laBaiDay() const;
    bool themXe(const Vehicle& v);
    bool xoaXe(int maXeCanXoa);
    int timViTriXe(int maXeCanTim) const;
    void hienThiThongTinBai() const;
};

ParkingLot::ParkingLot() : maBaiDo(0), kichThuocBai('S'), sucChua(1), soLuongXeHienTai(0) {
    danhSachXe = new Vehicle*[sucChua];
    for (int i = 0; i < sucChua; ++i) danhSachXe[i] = nullptr;
}

ParkingLot::ParkingLot(int id, char sz) : maBaiDo(id), kichThuocBai(sz), soLuongXeHienTai(0) {
    sucChua = (sz == 'S') ? 1 : (sz == 'M') ? 2 : 3;
    danhSachXe = new Vehicle*[sucChua];
    for (int i = 0; i < sucChua; ++i) danhSachXe[i] = nullptr;
}
//////////////////////////////////////
ParkingLot::ParkingLot(const ParkingLot& other)
    : maBaiDo(other.maBaiDo), kichThuocBai(other.kichThuocBai), sucChua(other.sucChua),
      soLuongXeHienTai(other.soLuongXeHienTai) {
    danhSachXe = new Vehicle*[sucChua];
    for (int i = 0; i < sucChua; ++i) danhSachXe[i] = nullptr;
    for (int i = 0; i < soLuongXeHienTai; ++i)
        danhSachXe[i] = new Vehicle(*other.danhSachXe[i]);
}

ParkingLot& ParkingLot::operator=(const ParkingLot& other) {
    if (this == &other) return *this;    

    for (int i = 0; i < soLuongXeHienTai; ++i) {
        delete danhSachXe[i];
        danhSachXe[i] = nullptr;
    }
    delete[] danhSachXe;

 
    maBaiDo = other.maBaiDo;
    kichThuocBai = other.kichThuocBai;
    sucChua = other.sucChua;
    soLuongXeHienTai = other.soLuongXeHienTai;
    danhSachXe = new Vehicle*[sucChua];
    for (int i = 0; i < sucChua; ++i) danhSachXe[i] = nullptr;
    for (int i = 0; i < soLuongXeHienTai; ++i)
        danhSachXe[i] = new Vehicle(*other.danhSachXe[i]);
    return *this;
}

ParkingLot::~ParkingLot() {
    for (int i = 0; i < soLuongXeHienTai; ++i) {
        delete danhSachXe[i];
        danhSachXe[i] = nullptr;
    }
    delete[] danhSachXe;
    danhSachXe = nullptr;
}

void ParkingLot::thayDoiKichCo(int sucChuaMoi) {
    Vehicle** mangMoi = new Vehicle*[sucChuaMoi];
    for (int i = 0; i < sucChuaMoi; ++i) mangMoi[i] = nullptr;
    for (int i = 0; i < soLuongXeHienTai; ++i) mangMoi[i] = danhSachXe[i];
    delete[] danhSachXe;                 
    sucChua = sucChuaMoi;
}

int ParkingLot::getMaBaiDo() const { return maBaiDo; }
char ParkingLot::getKichThuocBai() const { return kichThuocBai; }
int ParkingLot::getSucChua() const { return sucChua; }
int ParkingLot::getSoLuongXeHienTai() const { return soLuongXeHienTai; }
const Vehicle& ParkingLot::getXeTaiViTri(int index) const { return *danhSachXe[index]; }

bool ParkingLot::laBaiDay() const {
    return soLuongXeHienTai >= sucChua;
}

bool ParkingLot::themXe(const Vehicle& v) {
    if (laBaiDay()) thayDoiKichCo(sucChua * 2);     
    danhSachXe[soLuongXeHienTai] = new Vehicle(v);
    ++soLuongXeHienTai;
    return true;
}

int ParkingLot::timViTriXe(int maXeCanTim) const {
    for (int i = 0; i < soLuongXeHienTai; ++i)
        if (danhSachXe[i]->getMaXe() == maXeCanTim) return i;
    return -1;
}

bool ParkingLot::xoaXe(int maXeCanXoa) {
    int idx = timViTriXe(maXeCanXoa);
    if (idx == -1) return false;
    delete danhSachXe[idx];                  
    for (int i = idx; i < soLuongXeHienTai - 1; ++i)
        danhSachXe[i] = danhSachXe[i + 1];
    danhSachXe[soLuongXeHienTai - 1] = nullptr;        
    --soLuongXeHienTai;
    return true;
}

void ParkingLot::hienThiThongTinBai() const {
    cout << "Bai do " << maBaiDo << " [" << kichThuocBai << "] "
         << soLuongXeHienTai << "/" << getSucChua() << " xe\n";
    for (int i = 0; i < soLuongXeHienTai; ++i)
        danhSachXe[i]->hienThi();
}

//////////////////////////////////////
class SystemInterface {
private:
    static const int MAX_BAI_DO = 10;
    ParkingLot danhSachBaiDo[MAX_BAI_DO];
    int soLuongBaiDoHienTai;

    int timViTriBaiDo(int pID) const;

public:
    SystemInterface();
    void chayMenu();
    bool kiemTraTonTaiMaBai(int pID) const;
    bool kiemTraTonTaiMaXe(int vID) const;
    int taoMaNgauNhien();
};

SystemInterface::SystemInterface() : soLuongBaiDoHienTai(0) {}

int SystemInterface::timViTriBaiDo(int pID) const {
    for (int i = 0; i < soLuongBaiDoHienTai; ++i)
        if (danhSachBaiDo[i].getMaBaiDo() == pID) return i;
    return -1;
}

bool SystemInterface::kiemTraTonTaiMaBai(int pID) const {
    return timViTriBaiDo(pID) != -1;
}

bool SystemInterface::kiemTraTonTaiMaXe(int vID) const {
    for (int i = 0; i < soLuongBaiDoHienTai; ++i)
        if (danhSachBaiDo[i].timViTriXe(vID) != -1) return true;
    return false;
}

int SystemInterface::taoMaNgauNhien() {
    return 1000 + rand() % 9000;
}

void SystemInterface::chayMenu() {
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do xe moi\n";
        cout << "2. Them xe vao bai do\n";
        cout << "3. Xoa mot bai do xe\n";
        cout << "4. Lay xe ra khoi bai do\n";
        cout << "5. Hien thi tat ca bai do xe\n";
        cout << "6. Hien thi xe theo bai cu the\n";
        cout << "7. Liet ke xe theo loai phuong tien\n";
        cout << "8. Tom tat phi do xe trung binh\n";
        cout << "9. Thoat chuong trinh\n";
        int luaChon = nhapSoNguyen("Lua chon cua ban (1-9): ", 1, 9);

        switch (luaChon) {
            case 1: {
                if (soLuongBaiDoHienTai >= MAX_BAI_DO) {
                    cout << "He thong da dat toi da gioi han " << MAX_BAI_DO << " bai do!\n";
                    break;
                }
                int maBai = nhapSoNguyen("Nhap ma bai (so nguyen duong): ", 1, 999999);
                char kichThoc = nhapKichThuoc();
                if (kiemTraTonTaiMaBai(maBai)) {
                    cout << "  [Canh bao] Ma bai " << maBai << " da ton tai trong he thong!\n";
                    do { maBai = taoMaNgauNhien(); } while (kiemTraTonTaiMaBai(maBai));
                    cout << "  => He thong da tu dong gan ma ngau nhien moi: " << maBai << "\n";
                }
                danhSachBaiDo[soLuongBaiDoHienTai] = ParkingLot(maBai, kichThoc);
                ++soLuongBaiDoHienTai;
                cout << "Da tao thanh cong bai do ma: " << maBai << "\n";
                break;
            }
            case 2: {
                if (soLuongBaiDoHienTai == 0) {
                    cout << "Chua co bai do nao trong he thong, vui long tao bai truoc!\n";
                    break;
                }
                int maXe = nhapSoNguyen("Nhap ma xe (so nguyen duong): ", 1, 999999);
                string loaiXe = nhapLoaiXe();
                int gioVao = nhapSoNguyen("Nhap gio vao (0-23): ", 0, 23);
                int thoiLuong = nhapSoNguyen("Nhap thoi luong do (1-23 gio): ", 1, 23);
                if (kiemTraTonTaiMaXe(maXe)) {
                    cout << "  [Canh bao] Ma xe " << maXe << " da ton tai trong he thong!\n";
                    do { maXe = taoMaNgauNhien(); } while (kiemTraTonTaiMaXe(maXe));
                    cout << "  => He thong da tu dong gan ma xe ngau nhien moi: " << maXe << "\n";
                }
                Vehicle v(maXe, loaiXe, gioVao, thoiLuong);
                bool daDatCho = false;
                for (int i = 0; i < soLuongBaiDoHienTai && !daDatCho; ++i) {
                    if (!danhSachBaiDo[i].laBaiDay()) {
                        danhSachBaiDo[i].themXe(v);
                        daDatCho = true;
                        cout << "Da them xe " << maXe << " vao bai "
                             << danhSachBaiDo[i].getMaBaiDo()
                             << " | Phi: $" << fixed << setprecision(2) << v.getPhiDoXe() << "\n";
                    }
                }
                if (!daDatCho) {   
                    danhSachBaiDo[0].themXe(v);
                    cout << "Tat ca cac bai da day, he thong da tu mo rong bai " << danhSachBaiDo[0].getMaBaiDo()
                         << " (suc chua moi: " << danhSachBaiDo[0].getSucChua() << ") va them xe " << maXe
                         << " | Phi: $" << fixed << setprecision(2) << v.getPhiDoXe() << "\n";
                }
                break;
            }
            case 3: {
                int maBai = nhapSoNguyen("Nhap ma bai can xoa: ", 1, 999999);
                int idx = timViTriBaiDo(maBai);
                if (idx == -1) {
                    cout << "Khong tim thay bai do co ma " << maBai << "\n";
                    break;
                }
                for (int i = idx; i < soLuongBaiDoHienTai - 1; ++i)
                    danhSachBaiDo[i] = danhSachBaiDo[i + 1];
                danhSachBaiDo[soLuongBaiDoHienTai - 1] = ParkingLot(); // Reset bai cuoi
                --soLuongBaiDoHienTai;
                cout << "Da xoa thanh cong bai " << maBai << "\n";
                break;
            }
            case 4: {
                int maXe = nhapSoNguyen("Nhap ma xe can lay ra: ", 1, 999999);
                bool daXoa = false;
                for (int i = 0; i < soLuongBaiDoHienTai && !daXoa; ++i)
                    daXoa = danhSachBaiDo[i].xoaXe(maXe);
                if (daXoa) cout << "Da lay xe ra khoi bai thanh cong!\n";
                else cout << "Khong tim thay xe co ma " << maXe << " trong he thong!\n";
                break;
            }
            case 5: {
                if (soLuongBaiDoHienTai == 0) cout << "Chua co bai do nao duoc tao.\n";
                for (int i = 0; i < soLuongBaiDoHienTai; ++i)
                    danhSachBaiDo[i].hienThiThongTinBai();
                break;
            }
            case 6: {
                int maBai = nhapSoNguyen("Nhap ma bai can xem: ", 1, 999999);
                int idx = timViTriBaiDo(maBai);
                if (idx == -1) cout << "Khong tim thay bai do " << maBai << "\n";
                else danhSachBaiDo[idx].hienThiThongTinBai();
                break;
            }
            case 7: {
                string loaiXe = nhapLoaiXe();
                bool timThay = false;
                for (int i = 0; i < soLuongBaiDoHienTai; ++i) {
                    for (int j = 0; j < danhSachBaiDo[i].getSoLuongXeHienTai(); ++j) {
                        const Vehicle& v = danhSachBaiDo[i].getXeTaiViTri(j);
                        if (v.getLoaiXe() == loaiXe) {
                            if (!timThay) cout << "Danh sach cac xe loai [" << loaiXe << "]:\n";
                            cout << "Bai " << danhSachBaiDo[i].getMaBaiDo() << ":";
                            v.hienThi();
                            timThay = true;
                        }
                    }
                }
                if (!timThay) cout << "Khong co xe nao thuoc loai " << loaiXe << "\n";
                break;
            }
            case 8: {
                string danhSachLoai[3] = {"O to", "Xe may", "Xe dap"};

                cout << "--- TONG KET TOAN HE THONG ---\n";
                for (int t = 0; t < 3; ++t) {
                    int dem = 0;
                    double tongTien = 0;
                    for (int i = 0; i < soLuongBaiDoHienTai; ++i) {
                        for (int j = 0; j < danhSachBaiDo[i].getSoLuongXeHienTai(); ++j) {
                            const Vehicle& v = danhSachBaiDo[i].getXeTaiViTri(j);
                            if (v.getLoaiXe() == danhSachLoai[t]) {
                                ++dem;
                                tongTien += v.getPhiDoXe();
                            }
                        }
                    }
                    cout << danhSachLoai[t] << ": ";
                    if (dem == 0) cout << "khong co xe\n";
                    else cout << dem << " xe | Trung binh: $" << fixed << setprecision(2) << tongTien / dem << "\n";
                }

                for (int i = 0; i < soLuongBaiDoHienTai; ++i) {
                    cout << "--- Bai do " << danhSachBaiDo[i].getMaBaiDo() << " ---\n";
                    for (int t = 0; t < 3; ++t) {
                        int dem = 0;
                        double tongTien = 0;
                        for (int j = 0; j < danhSachBaiDo[i].getSoLuongXeHienTai(); ++j) {
                            const Vehicle& v = danhSachBaiDo[i].getXeTaiViTri(j);
                            if (v.getLoaiXe() == danhSachLoai[t]) {
                                ++dem;
                                tongTien += v.getPhiDoXe();
                            }
                        }
                        cout << danhSachLoai[t] << ": ";
                        if (dem == 0) cout << "khong co xe\n";
                        else cout << dem << " xe | Trung binh: $" << fixed << setprecision(2) << tongTien / dem << "\n";
                    }
                }
                break;
            }
            case 9:
                cout << "Cam on ban da su dung chuong trinh. Tam biet!\n";
                return;
        }
    }
}

int main() {
    srand((unsigned)time(NULL));
    SystemInterface heThong;
    heThong.chayMenu();
    return 0;
}
