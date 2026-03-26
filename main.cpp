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

//STRUCT KERANJANG
struct CartNode {
    int idMenu;
    string namaMenu;
    int hargaSatuan;
    int qty;
    int subtotal;
    
    CartNode* prev;
    CartNode* next;
};

CartNode* headCart = NULL;
CartNode* tailCart = NULL;

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

// FUNGSI MEMASUKKAN PESANAN
void insertLastDLL(int id, string nama, int harga, int qty) {
    CartNode* newNode = new CartNode;
    newNode->idMenu = id;
    newNode->namaMenu = nama;
    newNode->hargaSatuan = harga;
    newNode->qty = qty;
    newNode->subtotal = harga * qty;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (headCart == NULL) {
        headCart = newNode;
        tailCart = newNode;
    } 
    else {
        tailCart->next = newNode;
        newNode->prev = tailCart;
        tailCart = newNode;
    }
    
    cout << "\n[SUCCESS] " << qty << " " << nama << " berhasil ditambahkan ke keranjang!" << endl;
}

// FUNGSI MENAMPILKAN ISI KERANJANG
void cetakCart() {
    if (headCart == NULL) {
        cout << "\nKeranjang masih kosong! Yuk pesan dulu." << endl;
        return;
    }

    CartNode* current = headCart;
    int totalHarga = 0;
    int nomor = 1;

    cout << "\n===== ISI KERANJANG =====" << endl;
    while (current != NULL) {
        cout << nomor << ". " << current->namaMenu 
             << " (" << current->qty << ") = Rp" << current->subtotal << endl;
        
        totalHarga += current->subtotal;
        current = current->next;
        nomor++;
    }
    cout << "-------------------------" << endl;
    cout << "Total Belanja Sementara: Rp" << totalHarga << endl;
}

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

    do {
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
            case 1: {
                tampilkanMenu(daftarMenu, 10);
                int idPesanan, jumlah;
                cout << "\nMasukkan Nomor Menu yang ingin dipesan: ";
                cin >> idPesanan;
                
                if(idPesanan >= 1 && idPesanan <= 10) {
                    cout << "Masukkan jumlah pesanan: ";
                    cin >> jumlah;
                    int index = idPesanan - 1;
                    insertLastDLL(daftarMenu[index].id, daftarMenu[index].nama, daftarMenu[index].harga, jumlah);
                } else {
                    cout << "Maaf, nomor menu tidak ditemukan!" << endl;
                }
                break;
            }

            case 2:
                cetakCart();
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
    } while(pilihan != 5);

    return 0;
}