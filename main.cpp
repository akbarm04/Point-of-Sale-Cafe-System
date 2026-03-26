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

// ==================ANTREAN DAPUR ==================
struct AntreanDapur {
    string kodePesanan;
    string daftarPesanan;
    AntreanDapur* next;
};

AntreanDapur* head = NULL;
AntreanDapur* tail = NULL;

// TAMBAH ANTREAN
void inputPesananDapur(string kode, string pesanan) {
    AntreanDapur* pesananBaru = new AntreanDapur;
    pesananBaru->kodePesanan = kode;
    pesananBaru->daftarPesanan = pesanan;
    pesananBaru->next = NULL;

    if (head == NULL) {
        head = tail = pesananBaru;
    } else {
        tail->next = pesananBaru;
        tail = pesananBaru;
    }

    cout << "Pesanan " << kode << " masuk ke dapur\n";
}

// HAPUS ANTREAN DEPAN
void removeFirstSLL() {
    if (head == NULL) {
        cout << "Antrean kosong!\n";
        return;
    }

    AntreanDapur* temp = head;
    cout << "Pesanan selesai: " << temp->kodePesanan << endl;

    head = head->next;

    if (head == NULL) {
        tail = NULL;
    }

    delete temp;
}

// CETAK ANTREAN
void cetakAntreanDapur() {
    if (head == NULL) {
        cout << "Antrean kosong!\n";
        return;
    }

    AntreanDapur* current = head;

    while (current != NULL) {
        cout << "[->] Antrean No-" << current->kodePesanan << endl;
        cout << "     Pesanan: " << current->daftarPesanan << endl;
        cout << "\n";
        current = current->next;
    }
}

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

//Fungsi pencarian urutan node pesanan
CartNode* findCartItem(int nomorTarget) {
    CartNode* current = headCart;
    int nomor = 1; 
    
    while (current != NULL) {
        if (nomor == nomorTarget) {
            return current; 
        }
        current = current->next;
        nomor++;
    }
    return NULL; 
}

//Fungsi Hapus Pesanan dalam keranjang
void removeCartItem(CartNode* hapus) {
    if (hapus == NULL || headCart == NULL) {
        return; 
    }

    if (headCart == hapus) {
        headCart = hapus->next;
    }

    if (tailCart == hapus) {
        tailCart = hapus->prev;
    }

    if (hapus->next != NULL) {
        hapus->next->prev = hapus->prev;
    }

    if (hapus->prev != NULL) {
        hapus->prev->next = hapus->next;
    }

    cout << "\n[BERHASIL] Pesanan " << hapus->namaMenu << " telah dihapus dari keranjang!" << endl;
    delete hapus; 
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
                if (headCart != NULL) {
                    int pilihanHapus;
                    int pilihanAksi;
                    cout << "\n0. Kembali ke menu utama." << endl;
                    cout << "1. Hapus Item Tertentu" << endl;
                    cout << "Pilih Aksi: ";
                    cin >> pilihanAksi;
                    
                    if (pilihanAksi == 1) {
                        cout << "\nKetik Nomor Pesanan (1, 2, 3...) yang ingin dihapus: ";
                        cin >> pilihanHapus;

                        if (pilihanHapus > 0) {
                        CartNode* target = findCartItem(pilihanHapus); 
                        
                        if (target != NULL) {
                            removeCartItem(target); 
                        } else {
                            cout << "[GAGAL] Nomor pesanan tidak ditemukan di keranjang!" << endl;
                        }
                    }
                    }
                    
                }
                break;

            case 3:
                //Contoh masuk ke menu antrean dapur
                inputPesananDapur("A001", "2x Kopi Susu, 1x Burger");
                inputPesananDapur("A002", "1x Espresso");
                cout << "[INFO] Checkout berhasil, pesanan dikirim ke dapur\n";
                break;
            case 4:
                int pilihDapur;
                do {
                    cout << "===========================" << endl;
                    cout << "     ANTREAN DAPUR" << endl;
                    cout << "===========================" << endl;
                    cetakAntreanDapur();
                    cout << "===========================" << endl;
                    cout << "1. Selesaikan pesanan paling depan\n";
                    cout << "2. Kembali ke menu utama\n";
                    cout << "Pilih: ";
                    cin >> pilihDapur;

                    if (pilihDapur == 1) {
                        removeFirstSLL();
                    } else if (pilihDapur !=1 && pilihDapur != 2){
                        cout << "Pilihan tidak valid\n";
                    }
                } while (pilihDapur != 2);
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