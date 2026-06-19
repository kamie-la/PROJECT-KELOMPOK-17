#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Barang {
    string id;
    string nama;
    int harga;
    int stok;
};

struct Hadiah {
    string id_hadiah;
    string nama_hadiah;
    int poin_dibutuhkan;
};
#include "utilitas.cpp"
const int MAKS_DATA = 100;
Barang daftar_menu[MAKS_DATA];
int jumlah_barang = 0;

Hadiah daftar_hadiah[MAKS_DATA];
int jumlah_hadiah = 0;

int totalPoin = 0;
int transaksi[100];
int jumlahTransaksi = 0;
//    PANGGIL FILE MODUL KERJAAN ANGGOTA
#include "admin 1.cpp" //Widya

void cetakTengah(string teks) {
    const int LEBAR_TOTAL = 44;
    int panjang_teks = teks.length();
    
    if (panjang_teks >= LEBAR_TOTAL) {
        cout << teks << endl;
        return;
    }

    int sisa_spasi = LEBAR_TOTAL - panjang_teks;
    int spasi_kiri = sisa_spasi / 2;
    
    for (int i = 0; i < spasi_kiri; i++) {
        cout << " ";
    }

    cout << teks << endl;
}

int main() {
    daftar_menu[0] = {"K01", "Kopi Ireng", 10000, 20};
    daftar_menu[1] = {"R01", "Es teh hangat", 15000, 15};
    jumlah_barang = 2;

    int pilihan_role;

    do {
        cls();
        cout << "\n============================================\n";
        cetakTengah("WELCOME TO SMART CAFE LOYALTY"); 
        cout << "============================================\n";
        cout << "1. Masuk Sebagai Admin\n";
        cout << "2. Masuk Sebagai Pembeli (Customer)\n";
        cout << "0. Keluar Aplikasi\n";
        cout << "--------------------------------------------\n";
        cout << "Pilihan Role: ";
        cin >> pilihan_role;

        switch (pilihan_role) {
            case 1:
                menuadmin(daftar_menu, &jumlah_barang, MAKS_DATA);
                break;
            case 2:
                cout << "\n============================================\n";
                cetakTengah("MENU UTAMA PEMBELI");
                cout << "============================================\n";
                cout << "[!] Fitur pembeli sedang disiapkan oleh Kamila.\n";
                break;
            case 0:
                cout << "\n============================================\n";
                cetakTengah("GOOD BYE");
                cout << "============================================\n";
                cout << "Terima kasih telah berkunjung di Smart Cafe!\n";
                break;
            default:
                cout << "\n[!] Pilihan role tidak valid! Silakan coba lagi.\n";
        }
    } while (pilihan_role != 0);

    return 0;
}