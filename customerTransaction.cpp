// #include <iostream>
// #include <iomanip>
// #include <string>
// using namespace std;

void beliBarang(Barang arr[], int jumlah) {
    while(true){
        cls();
        lihatsemuamenu(arr, jumlah);
        if (jumlah == 0) {
            cetak_opsi_tengah("[!] Tidak Ada Barang");
            pause();
        }
        string idPilihan;
        cetak_input_tengah("\nMasukkan ID Menu yang ingin dibeli (Tekan 0 untuk keluar): ");
        cin >> idPilihan;
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
            cetak_opsi_tengah("\n[!] Menu dengan ID " + idPilihan + " tidak ditemukan.");
            pause();
            continue;
        }
    
        Barang *itemDipilih = &arr[indexDitemukan];
    
        cetak_opsi_tengah("\n[+] Menu dipilih : " + itemDipilih->nama);
        
        cetak_input_tengah("[+] Harga satuan : Rp ");
        cout << fixed << setprecision(0) << itemDipilih->harga << "\n";
        
        cetak_input_tengah("[+] Stok tersedia: ");
        cout << itemDipilih->stok << "\n";
    
        int jumlahBeli;
        cetak_input_tengah("\nMasukkan jumlah beli: ");
        cin >> jumlahBeli;
    
        if (jumlahBeli <= 0) {
            cetak_opsi_tengah("\n[!] Jumlah beli tidak valid.");
            pause();
            continue;
        }
        
        if (jumlahBeli > itemDipilih->stok) {
            cetak_input_tengah("\n[!] Stok tidak cukup! Stok tersedia hanya ");
            cout << itemDipilih->stok << " item.\n";
            pause();
            continue;
        }
    
        double totalHarga = itemDipilih->harga * jumlahBeli;
    
        itemDipilih->stok -= jumlahBeli;
    
        cetak_input_tengah("\n[✓] Pembelian berhasil! Sisa stok \"");
        cout << itemDipilih->nama << "\": " << itemDipilih->stok << "\n";
    
        prosesTransaksi((int)totalHarga);
        int kalkulasi_poin = (int)totalHarga / 10000;
        cetak_invoice_digital(itemDipilih->nama, itemDipilih->harga, jumlahBeli, kalkulasi_poin);
        pause();
    }
}

void menu_pembeli(Barang daftar_menu[], int jumlah_barang, int &total_poin, Hadiah inventori_hadiah[], int &jumlah_di_tas) {
    int pilihan_pembeli;
    do {
        cls();
        cetak_banner();
        cetakTengah("============================================");
        cetakTengah("MENU UTAMA PEMBELI (CUSTOMER)");
        cetakTengah("============================================");
        
        cetak_opsi_tengah("     1.Lihat Daftar Menu & Beli Barang");
        cetak_opsi_tengah("     2.Lihat Sisa Loyalty Poin Anda");
        cetak_opsi_tengah("     3.Tukar Poin (Gacha Hadiah)");
        cetak_opsi_tengah("     4.Lihat Inventori Hadiah Anda");
        cetak_opsi_tengah("     5.Ritual Maneki Neko (Buff SSR)");
        cetak_opsi_tengah("     0.Kembali ke Role Selection");
        
        cetakTengah("--------------------------------------------");
        cetak_input_tengah("    Pilihan: ");
        cin >> pilihan_pembeli;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                if (sisa_buff_draw > 0) {
                        cls();
                        cetak_banner();
                        cetakTengah("=====================================================");
                        cetakTengah("PERINGATAN: BERKAT MANEKI NEKO MASIH GACOR!");
                        cetakTengah("=====================================================");
                        cout << "\n";
                        cetak_opsi_tengah(MERAH "[!] Anda masih memiliki kuota " + to_string(sisa_buff_draw) + " kali gacha beruntung." RESET);
                        cetak_opsi_tengah("Silakan gunakan sisa buff Anda di menu gacha terlebih dahulu!");
                        cout << "\n";
                        cetakTengah("=====================================================");
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