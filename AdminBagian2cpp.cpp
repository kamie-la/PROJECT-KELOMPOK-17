// #include <iostream>
// using namespace std;

void editBarang(Barang daftarBarang[], int &jumlahBarang) {
    string idCari;
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

void hapusBarang(Barang daftarBarang[], int &jumlahBarang) {
    string idCari;
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
        pause();
    } else {
        cout << "\nID Barang tidak ditemukan!\n";
        pause();
    }
}
