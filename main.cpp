#include <iostream>
#include <iomanip>
using namespace std;

// === BAGIAN 1: STRUCT & ARRAY MENU ===
// Oleh: Fatah (UI Designer & Master Data)

struct Menu {
    int id;
    string nama;
    int harga;
};

// Array Menu (Database Menu Cafe)
Menu daftarMenu[10] = {
    {1, "Americano", 15000},
    {2, "Cappuccino", 18000},
    {3, "Latte", 20000},
    {4, "Matcha", 22000},
    {5, "Chocolate", 21000},
    {6, "Croissant", 12000},
    {7, "Donat", 10000},
    {8, "Sandwich", 17000},
    {9, "French Fries", 15000},
    {10, "Cheesecake", 25000}
};

// Fungsi untuk menampilkan menu
void tampilkanMenu(Menu menu[], int size) {
    cout << "\n=====================================\n";
    cout << "           MENU CAFE\n";
    cout << "=====================================\n";
    cout << left << setw(5) << "ID"
         << setw(20) << "Nama"
         << setw(10) << "Harga" << endl;
    cout << "-------------------------------------\n";

    for(int i = 0; i < size; i++) {
        cout << left << setw(5) << menu[i].id
             << setw(20) << menu[i].nama
             << "Rp" << menu[i].harga << endl;
    }

    cout << "=====================================\n";
}

// === MAIN MENU (CLI) ===
int main() {
    int pilihan;

    do {
        cout << "\n=====================================\n";
        cout << "     SISTEM POINT OF SALE CAFE\n";
        cout << "=====================================\n";
        cout << "1. Lihat Menu\n";
        cout << "2. Tambah ke Keranjang\n";
        cout << "3. Lihat Keranjang\n";
        cout << "4. Checkout\n";
        cout << "5. Keluar\n";
        cout << "-------------------------------------\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                tampilkanMenu(daftarMenu, 10);
                break;
            case 2:
                cout << "\n[INFO] Fitur tambah ke keranjang (Anggota 2)\n";
                break;
            case 3:
                cout << "\n[INFO] Fitur lihat keranjang (Anggota 2 & 3)\n";
                break;
            case 4:
                cout << "\n[INFO] Fitur checkout (Anggota 5)\n";
                break;
            case 5:
                cout << "\nTerima kasih telah menggunakan sistem!\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
        }

    } while(pilihan != 5);

    return 0;
}