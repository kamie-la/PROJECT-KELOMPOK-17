#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;

struct Barang {
    string id;
    string nama;
    int harga;
    int stok;
    string penambah;
};

struct Hadiah{
    string namaHadiah;
    string rarity;
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
int sisa_buff_draw = 0;
bool mainkan_game_maneki_catch();
void tambah_hadiah_admin(int* batasR, int* batasSR, int* batasSSR);
//PANGGIL FILE MODUL KERJAAN ANGGOTA
#include "minigame.cpp" // (Arizona)
#include "undian.cpp" // Modul Gacha (Rizka)
#include "poin.cpp"             // Modul Loyalty & History (Krisna)
#include "AdminBagian2cpp.cpp"  // Modul Admin Bagian 2 (Hari)
#include "admin 1.cpp"          // Modul Admin Bagian 1 (Widya)
#include "customerTransaction.cpp" // Modul Transaksi Pembeli (Kamila)

int main() {
    #if defined(_WIN32) || defined(_WIN64)
        system("chcp 65001 > nul");
    #endif
    muat_stok_dari_file(daftar_menu, jumlah_barang);
    if (jumlah_barang == 0) {
        daftar_menu[0] = {"K1", "Kopi Ireng", 10000, 20, "Rezeki Tuhan"};
        daftar_menu[1] = {"E1", "Es teh hangat", 15000, 15, "Rezeki Tuhan"};
        jumlah_barang = 2;
        simpan_stok_ke_file(daftar_menu, jumlah_barang);
    }
    Hadiah inventori[100];
    int pilihan_role;
    int jumlahDiTas = 0;
    do {
        cls();
        cetak_banner();
        cetakTengah("============================================");
        cetakTengah("WELCOME TO SMART CAFE LOYALTY");
        cetakTengah("============================================");
        
        cetak_opsi_tengah("    1. Masuk Sebagai Admin");
        cetak_opsi_tengah("    2. Masuk Sebagai Pembeli (Customer)");
        cetak_opsi_tengah("    0. Keluar Aplikasi");
        cetakTengah("--------------------------------------------");
        cetak_input_tengah("    Pilihan Role: ");
        cin >> pilihan_role;

        switch (pilihan_role) {
            case 1:
                menuadmin(daftar_menu, &jumlah_barang, MAKS_DATA);
                break;
            case 2:
                menu_pembeli(daftar_menu, jumlah_barang, totalPoin, inventori, jumlahDiTas);
                break;
            case 0:
                cetakTengah("============================================");
                cetakTengah("GOOD BYE");
                cetakTengah("============================================");
                cetak_opsi_tengah("Terima kasih telah berkunjung di Smart Cafe!");
                break;
            default:
                cetak_opsi_tengah(MERAH "    [!] Pilihan role tidak valid! Silakan coba lagi." RESET);
                pause();
        }
    } while (pilihan_role != 0);

    return 0;
}