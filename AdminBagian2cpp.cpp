// #include <iostream>
// using namespace std;

void editBarang(Barang daftarBarang[], int &jumlahBarang) {
    string idCari;
    bool ditemukan = false;

    cetak_input_tengah("\nMasukkan ID Barang yang ingin diedit : ");
    cin >> idCari;

    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].id == idCari) {
            Barang *ptr = &daftarBarang[i];

            cetak_opsi_tengah("\nID Barang ditemukan!");

            cetak_input_tengah("Masukkan Nama Baru  : ");
            cin.ignore();
            getline(cin, ptr->nama);

            cetak_input_tengah("Masukkan Harga Baru : ");
            cin >> ptr->harga;

            cetak_input_tengah("Masukkan Stok Baru  : ");
            cin >> ptr->stok;

            cetak_opsi_tengah("\nData barang berhasil diperbarui!");

            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cetak_opsi_tengah("\n[!] ID Barang tidak ditemukan!");
    }
}

void hapusBarang(Barang daftarBarang[], int &jumlahBarang) {
    string idCari;
    bool ditemukan = false;
    int indeks = -1;

    cetak_input_tengah("\nMasukkan ID Barang yang ingin dihapus : ");
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

        cetak_opsi_tengah("\nID Barang ditemukan!");
        cetak_opsi_tengah("Barang berhasil dihapus dari daftar.");
        pause();
    } else {
        cetak_opsi_tengah("\n[!] ID Barang tidak ditemukan!");
        pause();
    }
}