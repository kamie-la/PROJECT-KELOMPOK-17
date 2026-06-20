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
        cetak_opsi_tengah("[LIMIT] Batas Transaksi Harian Telah Penuh!");
    }

    cetakTengah("============================================");
    cetakTengah("TRANSAKSI SUKSES");
    cetakTengah("============================================");
    
    cetak_input_tengah("Total Belanja : Rp ");
    cout << totalHarga << "\n";
    
    cetak_input_tengah("Poin Didapat  : ");
    cout << dapatPoin << " poin\n";
    
    cetak_input_tengah("Total Poin    : ");
    cout << totalPoin << " poin\n";
    
    cetakTengah("--------------------------------------------");
    pause();
}

void lihatPoin() {
    cetakTengah("============================================");
    cetakTengah("TOTAL POIN");
    cetakTengah("============================================");
    
    cetak_input_tengah("Total Poin Anda : ");
    cout << totalPoin << " poin\n";
    
    cetakTengah("--------------------------------------------");
}

void riwayatTransaksi() {
    cetakTengah("====== RIWAYAT TRANSAKSI HARI INI (MODE ADMIN) ======");
    
    if (jumlahTransaksi == 0) {
        cetak_opsi_tengah("Belum ada transaksi yang terjadi hari ini.");
    } else {
        int totalPendapatan = 0;
        
        for (int i = 0; i < jumlahTransaksi; i++) {
            cetak_input_tengah("Transaksi ke-");
            cout << (i + 1) << "\t: Rp " << transaksi[i] << "\n";
            totalPendapatan += transaksi[i];
        }
        cetakTengah("-----------------------------------------------------");
        
        cetak_input_tengah("Total Pendapatan : Rp ");
        cout << totalPendapatan << "\n";
        
        cetak_input_tengah("Total Transaksi  : ");
        cout << jumlahTransaksi << " kali\n";
    }
    cetakTengah("=====================================================");
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