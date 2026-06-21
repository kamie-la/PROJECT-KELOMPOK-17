// #include <iostream>
// #include <iostream>
// using namespace std;

void prosesTransaksi(int totalHarga){
    int dapatPoin = totalHarga / 10000;
    totalPoin += dapatPoin;

    if (jumlahTransaksi < 100) {
        transaksi[jumlahTransaksi] = totalHarga;
        jumlahTransaksi++;
    } 
    else {
        cetak_opsi_tengah(MERAH "[LIMIT] Batas Transaksi Harian Telah Penuh!" RESET);
    }

    cout << BOLD << NEON_PURPLE;
    cetakTengah("============================================");
    cout << NEON_PINK;
    cetakTengah("TRANSAKSI SUKSES");
    cout << NEON_PURPLE;
    cetakTengah("============================================");
    cout << RESET;
    
    cetak_input_tengah("Total Belanja : Rp ");
    cout << BOLD << totalHarga << RESET << "\n";
    
    cetak_input_tengah("Poin Didapat  : ");
    cout << BOLD << KUNING << dapatPoin << RESET " poin\n";
    
    cetak_input_tengah("Total Poin    : ");
    cout << BOLD << HIJAU << totalPoin << RESET " poin\n";
    
    cout << NEON_PURPLE;
    cetakTengah("--------------------------------------------");
    cout << RESET;
    pause();
}

void lihatPoin() {
    cout << BOLD << NEON_PURPLE;
    cetakTengah("============================================");
    cout << CYBER_CYAN;
    cetakTengah("TOTAL POIN");
    cout << NEON_PURPLE;
    cetakTengah("============================================");
    cout << RESET;
    
    cetak_input_tengah("Total Poin Anda : ");
    cout << BOLD << HIJAU << totalPoin << RESET " poin\n";
    
    cout << NEON_PURPLE;
    cetakTengah("--------------------------------------------");
    cout << RESET;
}

void riwayatTransaksi() {
    cout << BOLD << NEON_PURPLE;
    cetakTengah("====== RIWAYAT TRANSAKSI HARI INI (MODE ADMIN) ======");
    cout << RESET;
    
    if (jumlahTransaksi == 0) {
        cetak_opsi_tengah("Belum ada transaksi yang terjadi hari ini.");
    } else {
        int totalPendapatan = 0;
        
        for (int i = 0; i < jumlahTransaksi; i++) {
            cetak_input_tengah("Transaksi ke-");
            cout << (i + 1) << "\t: Rp " << BOLD << transaksi[i] << RESET << "\n";
            totalPendapatan += transaksi[i];
        }
        cout << NEON_PURPLE;
        cetakTengah("-----------------------------------------------------");
        cout << RESET;
        
        cetak_input_tengah("Total Pendapatan : Rp ");
        cout << BOLD << HIJAU << totalPendapatan << RESET << "\n";
        
        cetak_input_tengah("Total Transaksi  : ");
        cout << BOLD << CYBER_CYAN << jumlahTransaksi << RESET " kali\n";
    }
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << RESET;
}

// int main () {
//     //TES FUNCTION TRANSAKSI
//     int belanja;
//     cout << "Masukkan total belanja: Rp. "; cin >> belanja;
//     prosesTransaksi(belanja);
//     cout << endl;

//     //TES FUNCTION LIHAT POIN
//     lihatPoin();
//     cout << endl;

//     //TES FUNCTION RIWAYAT TRANSAKSI
//     cout << endl;
//     riwayatTransaksi();
//     return 0;
// }