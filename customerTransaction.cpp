// #include <iostream>
// #include <iomanip>
// #include <string>
// using namespace std;

void beliBarang(Barang arr[], int jumlah) {
    while(true){
        cls();
        lihatsemuamenu(arr, jumlah);
        if (jumlah == 0) {
            cetak_opsi_tengah(MERAH "[!] Tidak Ada Barang" RESET);
            pause();
            return;
        }
        string idPilihan;
        idPilihan = ambil_input_teks("\nMasukkan ID Menu yang ingin dibeli (Tekan 0 untuk keluar): ", false);
        if (idPilihan == "0"){
            break;
        }
    
        int indexDitemukan = -1;
        for (int i = 0; i < jumlah; i++) {
            if (arr[i].id == idPilihan) {
                indexDitemukan = i;
                break;
            }
        }
    
        if (indexDitemukan == -1) {
            cetak_opsi_tengah("\n" MERAH "[!] Menu dengan ID " + idPilihan + " tidak ditemukan." RESET);
            pause();
            continue;
        }
    
        Barang *itemDipilih = &arr[indexDitemukan];
    
        cetak_opsi_tengah("\n[+] Menu dipilih : " + itemDipilih->nama);
        
        cetak_input_tengah("[+] Harga satuan : Rp ");
        cout << BOLD << fixed << setprecision(0) << itemDipilih->harga << RESET << "\n";
        
        cetak_input_tengah("[+] Stok tersedia: ");
        cout << BOLD << CYBER_CYAN << itemDipilih->stok << RESET << "\n";
    
        int jumlahBeli;
        
        jumlahBeli = ambil_input_angka("\nMasukkan jumlah beli: ");
    
        if (jumlahBeli <= 0) {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Jumlah beli harus lebih besar dari 0!" RESET);
            pause();
            continue;
        }
        
        if (jumlahBeli > itemDipilih->stok) {
            cetak_input_tengah("\n" MERAH "[!] Stok tidak cukup! Stok tersedia hanya " RESET);
            cout << BOLD << itemDipilih->stok << RESET << " item.\n";
            pause();
            continue;
        }
    
        double totalHarga = itemDipilih->harga * jumlahBeli;
    
        itemDipilih->stok -= jumlahBeli;
        
        simpan_stok_ke_file(arr, jumlah);
    
        cetak_input_tengah("\n" HIJAU "[✓] Pembelian berhasil! Sisa stok \"" RESET);
        cout << itemDipilih->nama << "\": " << BOLD << CYBER_CYAN << itemDipilih->stok << RESET << "\n";
    
        prosesTransaksi((int)totalHarga);
        
        int kalkulasi_poin = (int)totalHarga / 10000;
        totalPoin += kalkulasi_poin;
        
        cetak_invoice_digital(itemDipilih->nama, itemDipilih->harga, jumlahBeli, kalkulasi_poin);
        pause();
    }
}

void menu_pembeli(Barang daftar_menu[], int jumlah_barang, int &total_poin, Hadiah inventori_hadiah[], int &jumlah_di_tas) {
    int pilihan_pembeli;
    do {
        cls();
        cetak_banner();
        cout << BOLD << NEON_PURPLE;
        cetakTengah("============================================");
        cout << NEON_PINK;
        cetakTengah("MENU UTAMA PEMBELI (CUSTOMER)");
        cout << NEON_PURPLE;
        cetakTengah("============================================");
        cout << RESET;
        
        cetak_opsi_tengah("     1.Lihat Daftar Menu & Beli Barang");
        cetak_opsi_tengah("     2.Lihat Sisa Loyalty Poin Anda");
        cetak_opsi_tengah("     3.Tukar Poin (Gacha Hadiah)");
        cetak_opsi_tengah("     4.Lihat Inventori Hadiah Anda");
        cetak_opsi_tengah("     5.Ritual Maneki Neko (Buff SSR)");
        cetak_opsi_tengah("     0.Kembali ke Role Selection");
        cetak_opsi_tengah(NEON_PURPLE "--------------------------------------------" RESET);
        pilihan_pembeli = ambil_input_angka("    Pilihan: ");
        switch (pilihan_pembeli) {
            case 1:
                beliBarang(daftar_menu, jumlah_barang);
                break;
            case 2:
                lihatPoin();
                pause();
                break;
            case 3:
                menuGacha(&total_poin, inventori_hadiah, &jumlah_di_tas);
                break;
            case 4:
                lihatInventori(inventori_hadiah, jumlah_di_tas);
                pause();
                break;
            case 5:
                if (sisa_buff_draw != 0) {
                    cls();
                    cetak_banner();
                    cout << BOLD << NEON_PURPLE;
                    cetakTengah("=====================================================");
                    cout << MERAH;
                    cetakTengah("PERINGATAN: BERKAT MANEKI NEKO MASIH AKTIF!");
                    cout << NEON_PURPLE;
                    cetakTengah("=====================================================");
                    cout << RESET << "\n";
                    
                    int kuota_tampil = (sisa_buff_draw < 0) ? 0 : sisa_buff_draw;
                    if (sisa_buff_draw < 0) {
                        sisa_buff_draw = 0;
                    }

                    cetak_opsi_tengah(MERAH "[!] Anda masih memiliki kuota gacha beruntung." RESET);
                    cetak_opsi_tengah("Silakan gunakan sisa buff Anda di menu gacha terlebih dahulu!");
                    cout << "\n";
                    cout << NEON_PURPLE;
                    cetakTengah("=====================================================");
                    cout << RESET;
                    pause();
                } else {
                    if (mainkan_game_maneki_catch()) {
                        sisa_buff_draw = 3;
                    }
                }
                break;
            case 0:
                cetak_opsi_tengah(HIJAU "     Kembali ke Role Selection" RESET);
                pause();
                break;
            default:
                cetak_opsi_tengah(MERAH "     [!] Pilihan tidak valid!" RESET);
                pause();
        }
    } while (pilihan_pembeli != 0);
}