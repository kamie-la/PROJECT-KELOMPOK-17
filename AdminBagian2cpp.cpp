#include <iostream>
using namespace std;

struct Barang {
    int id;
    string nama;
    int harga;
    int stok;
};

Barang daftarBarang[5] = {
    {101, "Barang1", 10000, 10},
    {102, "Barang2", 15000, 20},
    {103, "Barang3", 20000, 15}
};

int jumlahBarang = 3;

void editBarang() {
    int idCari;
    bool ditemukan = false;

    cout << "\nMasukkan ID Barang yang ingin diedit : ";
    cin >> idCari;

    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].id == idCari) {
            Barang *ptr = &daftarBarang[i];

            cout << "\nID Barang ditemukan!\n";

            cout << "Masukkan Nama Baru  : ";
            cin.ignore();
            getline(cin, ptr->nama);

            cout << "Masukkan Harga Baru : ";
            cin >> ptr->harga;

            cout << "Masukkan Stok Baru  : ";
            cin >> ptr->stok;

            cout << "\nData barang berhasil diperbarui!\n";

            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "\nID Barang tidak ditemukan!\n";
    }
}

void hapusBarang() {
    int idCari;
    bool ditemukan = false;
    int indeks = -1;

    cout << "\nMasukkan ID Barang yang ingin dihapus : ";
    cin >> idCari;

    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].id == idCari) {
            indeks = i;
            ditemukan = true;
            break;
        }
    }

    if (ditemukan) {
        for (int i = indeks; i < jumlahBarang - 1; i++) {
            daftarBarang[i] = daftarBarang[i + 1];
        }

        jumlahBarang--;

        cout << "\nID Barang ditemukan!\n";
        cout << "Barang berhasil dihapus dari daftar.\n";
    } else {
        cout << "\nID Barang tidak ditemukan!\n";
    }
}

int main() {
    int pilihan;

    do {
        cout << "\n=================================\n";
        cout << "      ADMIN MENU SPECIALIST\n";
        cout << "=================================\n";
        cout << "1. Edit Barang\n";
        cout << "2. Hapus Barang\n";
        cout << "3. Keluar\n";
        cout << "Pilihan : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                editBarang();
                break;
            case 2:
                hapusBarang();
                break;
            case 3:
                cout << "\nProgram selesai.\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
        }
    } while (pilihan != 3);

    return 0;
}