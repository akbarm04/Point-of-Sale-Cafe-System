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
    
    cout << "\n[BERHASIL] " << qty << " " << nama << " berhasil ditambahkan ke keranjang!" << endl;
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

    cout << "\n[BERHASIL] Pesanan " << hapus->namaMenu << " telah dihapus dari keranjang" << endl;
    delete hapus; 
}

// FUNGSI MENAMPILKAN ISI KERANJANG
void cetakCart() {
    if (headCart == NULL) {
        cout << "\nKeranjang masih kosong." << endl;
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
    cout << "=========================" << endl;
    cout << "Total Belanja Sementara: Rp" << totalHarga << endl;
}

// ANTREAN DAPUR
struct AntreanDapur {
    string kodePesanan;
    string daftarPesanan;
    AntreanDapur* next;
};

AntreanDapur* headDapur = NULL;
AntreanDapur* tailDapur = NULL;

int counterAntrean = 1;

// TAMBAH ANTREAN
void inputPesananDapur(string kode, string pesanan) {
    AntreanDapur* pesananBaru = new AntreanDapur;
    pesananBaru->kodePesanan = kode;
    pesananBaru->daftarPesanan = pesanan;
    pesananBaru->next = NULL;

    if (headDapur == NULL) {
        headDapur = tailDapur = pesananBaru;
    } else {
        tailDapur->next = pesananBaru;
        tailDapur = pesananBaru;
    }

    cout << "Pesanan " << kode << " masuk ke dapur\n";
}

// HAPUS ANTREAN DEPAN
void removeFirstSLL() {
    if (headDapur == NULL) {
        cout << "Antrean kosong!\n";
        return;
    }

    AntreanDapur* temp = headDapur;
    cout << endl << "Pesanan selesai: " << temp->kodePesanan << endl;

    headDapur = headDapur->next;

    if (headDapur == NULL) {
        tailDapur = NULL;
    }

    delete temp;
    temp = NULL;
}

// CETAK ANTREAN
void cetakAntreanDapur() {
    if (headDapur == NULL) {
        cout << "Antrean kosong!\n";
        return;
    }

    AntreanDapur* current = headDapur;

    while (current != NULL) {
        cout << "[->] Antrean No-" << current->kodePesanan << endl;
        cout << "     Pesanan: " << current->daftarPesanan << endl;
        cout << "\n";
        current = current->next;
    }
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
        
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[ERROR] Input harus angka, Silakan coba lagi.\n";
            pilihan = 0;
            continue;
        }

        switch(pilihan) {
            case 1: {
                tampilkanMenu(daftarMenu, 10);
                int idPesanan, jumlah;
                cout << "\nMasukkan Nomor Menu yang ingin dipesan: ";
                if (!(cin >> idPesanan)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[ERROR] ID Menu harus angka\n";
                    break;
                }
                
                if(idPesanan >= 1 && idPesanan <= 10) {
                    cout << "Masukkan jumlah pesanan: ";
                    if (!(cin >> jumlah)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "[ERROR] Jumlah pesanan harus angka\n";
                        break; 
                    }
                    int index = idPesanan - 1;
                    insertLastDLL(daftarMenu[index].id, daftarMenu[index].nama, daftarMenu[index].harga, jumlah);
                } else {
                    cout << "Maaf, nomor menu tidak ditemukan" << endl;
                }
                break;
            }

            case 2: {
                cetakCart();
                if (headCart != NULL) {
                    int pilihanHapus;
                    int pilihanAksi;
                    cout << "\n0. Kembali ke menu utama." << endl;
                    cout << "1. Hapus Item Tertentu" << endl;
                    cout << "Pilih Aksi: ";
                    if (!(cin >> pilihanAksi)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "[ERROR] Pilihan aksi harus angka\n";
                        break;
                    }
                    
                    if (pilihanAksi == 1) {
                        cout << "\nKetik Nomor Pesanan (1, 2, 3...) yang ingin dihapus: ";
                        if (!(cin >> pilihanHapus)) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "[ERROR] Nomor pesanan harus angka!\n";
                            break;
                        }

                        if (pilihanHapus > 0) {
                            CartNode* target = findCartItem(pilihanHapus); 
                            
                            if (target != NULL) {
                                removeCartItem(target); 
                            } else {
                                cout << "[ERROR] Nomor pesanan tidak ditemukan di keranjang" << endl;
                            }
                        }
                    }
                }
                break;
            }

            case 3: {
                if (headCart == NULL) {
                    cout << "\n[ERROR] Keranjang kosong!\n";
                } else {
                    string daftarPesananFinal = "";
                    CartNode* temp = headCart;
                    int totalBayar = 0;

                    while (temp != NULL) {
                        daftarPesananFinal += to_string(temp->qty) + "x " + temp->namaMenu;
                        totalBayar += temp->subtotal;
                        if (temp->next != NULL) daftarPesananFinal += ", ";
                        temp = temp->next;
                    }

                    cout << "\n===== PROSES PEMBAYARAN =====" << endl;
                    cout << "Detail: " << daftarPesananFinal << endl;
                    cout << "Total : Rp" << totalBayar << endl;
                    
                    int nominalBayar;
                    bool batalTransaksi = false;

                    while (true) {
                        cout << "Bayar (Ketik 0 untuk batal) : Rp";
                        if (!(cin >> nominalBayar)) {
                            cin.clear(); cin.ignore(10000, '\n');
                            cout << "[ERROR] Masukkan angka!\n"; continue;
                        }
                        
                        if (nominalBayar == 0) {
                            cout << "\n[INFO] Pembayaran dibatalkan. Kembali ke menu utama.\n";
                            batalTransaksi = true; 
                            break;
                        }

                        if (nominalBayar < totalBayar) {
                            cout << "[!] Kurang Rp" << (totalBayar - nominalBayar) << "\n";
                        } else break;
                    }

                    if (batalTransaksi) {
                        break; 
                    }

                    cout << "\n===== STRUK PEMBAYARAN =====" << endl;
                    cout << "Total     : Rp" << totalBayar << endl;
                    cout << "Bayar     : Rp" << nominalBayar << endl;
                    cout << "Kembalian : Rp" << (nominalBayar - totalBayar) << endl;
                    cout << "============================" << endl;

                    string idAntrean = "A";
                    if (counterAntrean < 10) idAntrean += "00" + to_string(counterAntrean);
                    else if (counterAntrean < 100) idAntrean += "0" + to_string(counterAntrean);
                    else idAntrean += to_string(counterAntrean);
                    counterAntrean++;

                    inputPesananDapur(idAntrean, daftarPesananFinal); 
                    
                    while (headCart != NULL) {
                        CartNode* hapus = headCart;
                        headCart = headCart->next;
                        delete hapus;
                    }
                    tailCart = NULL; 
                    cout << "[SUKSES] Pesanan LUNAS (ID: " << idAntrean << ")\n" << endl ;
                }
                break;
            }

            case 4: {
                int pilihDapur;
                do {
                    cout << endl << "===========================" << endl;
                    cout << "     ANTREAN DAPUR" << endl;
                    cout << "===========================" << endl;
                    cetakAntreanDapur();
                    cout << "===========================" << endl;
                    cout << "0. Kembali ke menu utama\n";
                    cout << "1. Selesaikan pesanan paling depan\n";
                    cout << "Pilih: ";
                    if (!(cin >> pilihDapur)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "[ERROR] Pilihan harus angka\n";
                        pilihDapur = 0;
                        continue;
                    }

                    if (pilihDapur == 1) {
                        removeFirstSLL();
                    } else if (pilihDapur != 1 && pilihDapur != 0){
                        cout << "Pilihan tidak valid\n";
                    }
                } while (pilihDapur != 0);
                break;
            }

            case 5:
                cout << "Terima kasih" << endl;
                break;

            default:
                cout << "Pilihan tidak valid" << endl;
        }
    } while (pilihan != 5);
    
    return 0;
}