#include <iostream>
#include <string>
using namespace std;

//STRUCT
struct Menu {
    int id;
    string nama;
    string kategori;
    int harga;
};

//ARRAY (Database Menu Cafe)
Menu daftarMenu[10] = {
    {1, "Americano", "Minuman", 15000},
    {2, "Cappuccino", "Minuman", 18000},
    {3, "Latte", "Minuman", 20000},
    {4, "Matcha", "Minuman", 22000},
    {5, "Chocolate", "Minuman", 21000},
    {6, "Croissant", "Makanan", 12000},
    {7, "Donat", "Makanan", 10000},
    {8, "Sandwich", "Makanan", 17000},
    {9, "French Fries", "Makanan", 15000},
    {10, "Cheesecake", "Makanan", 25000}
};

//FUNGSI TAMPIL MENU
void tampilkanMenu(Menu menu[], int size) {
    cout << "===== MENU CAFE =====" << endl;

    for(int i = 0; i < size; i++) {
        cout << menu[i].id << ". "
             << menu[i].nama << " - "
             << menu[i].kategori << " - Rp"
             << menu[i].harga << endl;
    }
}

//MAIN (SISTEM KASIR)
int main() {
    int pilihan;

    cout << "===========================" << endl;
    cout << "SISTEM KASIR & ANTREAN CAFE" << endl;
    cout << "===========================" << endl;

    cout << "1. Lihat menu dan pesan" << endl;
    cout << "2. Lihat keranjang pelanggan" << endl;
    cout << "3. Checkout dan bayar" << endl;
    cout << "4. Lihat antrean dapur" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih menu: ";
    cin >> pilihan;

    switch(pilihan) {
        case 1:
            tampilkanMenu(daftarMenu, 10);
            cout << "[INFO] Tambah ke keranjang (rifa)" << endl;
            break;

        case 2:
            cout << "[INFO] Lihat keranjang (rifa & akbar)" << endl;
            break;

        case 3:
            cout << "[INFO] Checkout & pembayaran (iky)" << endl;
            break;

        case 4:
            cout << "[INFO] Antrean dapur (danish)" << endl;
            break;

        case 5:
            cout << "Terima kasih" << endl;
            break;

        default:
            cout << "Pilihan tidak valid" << endl;
    }

    return 0;
}