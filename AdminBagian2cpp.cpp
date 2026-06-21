// #include <iostream>
// using namespace std;

void editBarang(Barang daftarBarang[], int &jumlahBarang) {
    string idCari;
    bool ditemukan = false;

    cetak_input_tengah("\nMasukkan ID Barang yang ingin diedit : ");
    idCari = ambil_input_teks("\nMasukkan ID Barang yang ingin diedit : ", false);

    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].id == idCari) {
            Barang *ptr = &daftarBarang[i];

            cetak_opsi_tengah("\n" HIJAU "[✓] ID Barang ditemukan!" RESET);

            ptr->nama = ambil_input_teks("Masukkan Nama Baru  : ", false);

            ptr->harga = ambil_input_angka("Masukkan Harga Baru : Rp ");

            ptr->stok = ambil_input_angka("Masukkan Stok Baru  : ");

            cetak_opsi_tengah("\n" HIJAU "[✓] Data barang berhasil diperbarui!" RESET);

            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cetak_opsi_tengah("\n" MERAH "[!] ID Barang tidak ditemukan!" RESET);
    }
}

void hapusBarang(Barang daftarBarang[], int &jumlahBarang) {
    string idCari;
    bool ditemukan = false;
    int indeks = -1;

    idCari = ambil_input_teks("\nMasukkan ID Barang yang ingin dihapus : ", false);

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

        cetak_opsi_tengah("\n" HIJAU "[✓] ID Barang ditemukan!" RESET);
        cetak_opsi_tengah(MERAH "[-] Barang berhasil dihapus dari daftar." RESET);
        pause();
    } else {
        cetak_opsi_tengah("\n" MERAH "[!] ID Barang tidak ditemukan!" RESET);
        pause();
    }
}