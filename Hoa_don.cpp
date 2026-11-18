#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

class Mh{
	private:
		string ten;
		double ma;
		int sl;
		double giaban, gianhap;
		static string dv;
	public:
		Mh();
		void Nhap();
		void In();
};
string Mh::dv = "VND"; 
Mh::Mh(){
	ten = "";
	ma = 0;
	sl = 0;
	giaban = 0;
	gianhap = 0;
}
void Mh::Nhap(){
	cout << "Nhap ten mat hang: ";
	getline(cin >> ws, ten);
	cout << "Nhap ma mat hang: ";
	cin >> ma;
	cout << "Nhap so luong: ";
	cin >> sl;
	cout << "Nhap gia nhap: ";
	cin >> gianhap;
	cout << "Nhap gia ban: ";
	cin >> giaban;
}
void Mh::In(){
	cout << "--- Mat hang ---" << endl;
	cout << "Ten: " << ten << endl;
	cout << "Ma: " << ma << endl;
	cout << "So luong: " << sl << endl;
	cout << "Gia nhap: " << gianhap << " " << dv << endl;
	cout << "Gia ban: " << giaban << " " << dv << endl;
	cout << "Loi nhuan 1 san pham: " << giaban - gianhap << " " << dv << endl;
}

class Kh{
	private:
		string tenKh;
		string sdt;
		string dc;
	public:
		Kh();
		void Nhap();
		void In();
};

Kh::Kh(){
	tenKh = "";
	sdt = "";
	dc = "";
}
void Kh::Nhap(){
	cout << "Nhap ten khach hang: ";
	getline(cin >> ws, tenKh);
	cout << "Nhap so dien thoai: ";
	getline(cin >> ws, sdt);
	cout << "Nhap dia chi: ";
	getline(cin >> ws, dc);
}
void Kh::In(){
	cout << "--- Khach hang ---" << endl;
	cout << "Ten: " << tenKh << endl;
	cout << "SDT: " << sdt << endl;
	cout << "Dia chi: " << dc << endl;
}

class Dn{
	private:
		string tenDn;
		string mathue;
		string sdt;
		string email;
	public:
		Dn();
		void Nhap();
		void In();
};

Dn::Dn(){
	tenDn = "";
	mathue = "";
	sdt = "";
	email = "";
}
void Dn::Nhap(){
	cout << "Nhap ten doanh nghiep: ";
	getline(cin >> ws, tenDn);
	cout << "Nhap ma so thue: ";
	getline(cin >> ws, mathue);
	cout << "Nhap so dien thoai: ";
	getline(cin >> ws, sdt);
	cout << "Nhap email: ";
	getline(cin >> ws, email);
}
void Dn::In(){
	cout << "--- Doanh nghiep ---" << endl;
	cout << "Ten: " << tenDn << endl;
	cout << "Ma so thue: " << mathue << endl;
	cout << "SDT: " << sdt << endl;
	cout << "Email: " << email << endl;
}
int main(){
	Mh a;
	Kh b;
	Dn c;
	cout << "== NHAP MAT HANG ==" << endl;
	a.Nhap();
	cout << "\n== NHAP KHACH HANG ==" << endl;
	b.Nhap();
	cout << "\n== NHAP DOANH NGHIEP ==" << endl;
	c.Nhap();
	cout << "\n====== THONG TIN ======" << endl;
	a.In();
	b.In();
	c.In();
	return 0;
}
