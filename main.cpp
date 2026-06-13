#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    #define CLEAR_SCREEN "cls"
    char ambilInput() { return _getch(); }
#else
    #include <unistd.h>
    #include <termios.h>
    #define CLEAR_SCREEN "clear"
    char ambilInput() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ~ICANON");
        if (read(0, &buf, 1) < 0) perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADOW, &old) < 0) perror ("tcsetattr ICANON");
        return (buf);
    }
#endif

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

const int MAKS_DATA = 100;
Barang daftar_menu[MAKS_DATA];
int jumlah_barang = 0;

Hadiah daftar_hadiah[MAKS_DATA];
int jumlah_hadiah = 0;

int poin_pembeli = 0;

void hapusLayar() {
    system(CLEAR_SCREEN);
}

// Fungsi Padding Tengah Otomatis (Menerima parameter string teks banner)
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

    int posisi_kursor = 1; 
    char tombol;

    while (true) {
        hapusLayar();
        cout << "============================================\n";
        cetakTengah("WELCOME TO SMART CAFE LOYALTY TUI"); 
        cout << "============================================\n";
        cout << " Gunakan tombol W/S atau Panah Atas/Bawah\n";
        cout << " Tekan ENTER untuk konfirmasi pilihan\n";
        cout << "--------------------------------------------\n\n";

        // Cetak Pilihan Menu Berdasarkan Posisi Kursor Navigasi
        if (posisi_kursor == 1) cout << " -> [1] Masuk Sebagai Admin\n";
        else                    cout << "    [1] Masuk Sebagai Admin\n";

        if (posisi_kursor == 2) cout << " -> [2] Masuk Sebagai Pembeli\n";
        else                    cout << "    [2] Masuk Sebagai Pembeli\n";

        if (posisi_kursor == 3) cout << " -> [3] Keluar Aplikasi\n";
        else                    cout << "    [3] Keluar Aplikasi\n";

        tombol = ambilInput();

        // Navigasi Naik (W / Panah Atas)
        if (tombol == 'w' || tombol == 'W' || tombol == 72) { 
            posisi_kursor--;
            if (posisi_kursor < 1) posisi_kursor = 3; 
        }
        // Navigasi Turun (S / Panah Bawah)
        else if (tombol == 's' || tombol == 'S' || tombol == 80) { 
            posisi_kursor++;
            if (posisi_kursor > 3) posisi_kursor = 1; 
        }
        else if (tombol == 13 || tombol == 10) {
            hapusLayar();
            
            if (posisi_kursor == 1) {
                cout << "============================================\n";
                cetakTengah("MENU UTAMA ADMIN");
                cout << "============================================\n";
                cout << "\ncihuy\n";
                cout << "\nTekan tombol apa saja untuk kembali...";
                ambilInput();
            } 
            else if (posisi_kursor == 2) {
                cout << "============================================\n";
                cetakTengah("MENU UTAMA PEMBELI");
                cout << "============================================\n";
                cout << "\ncihuy\n";
                cout << "\nTekan tombol apa saja untuk kembali...";
                ambilInput();
            } 
            else if (posisi_kursor == 3) {
                cout << "============================================\n";
                cetakTengah("GOOD BYE");
                cout << "============================================\n";
                cout << "\nTerima kasih telah berkunjung di Smart Cafe!\n";
                break;
            }
        }
    }
    return 0;
}