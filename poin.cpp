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
        cout << "[LIMIT] Batas Transaksi Harian Telah Penuh!" << endl;
    }

    cout << "\n============================================\n";
    cout << "              TRANSAKSI SUKSES \n";
    cout << "============================================\n";
    cout << "Total Belanja : Rp " << totalHarga << endl;
    cout << "Poin Didapat  : " << dapatPoin << " poin" << endl;
    cout << "Total Poin    : " << totalPoin << " poin" << endl;
    cout << "----------------------------------------------\n" << endl;
}

void lihatPoin() {
    cout << "\n============================================\n";
    cout << "              TOTAL POIN \n";
    cout << "============================================\n";
    cout << "Total Poin Anda : " << totalPoin << " poin" << endl;
    cout << "----------------------------------------------\n" << endl;
}

void riwayatTransaksi() {
    cout << "\n====== RIWAYAT TRANSAKSI HARI INI (MODE ADMIN) ======" << endl;
    
    if (jumlahTransaksi == 0) {
        cout << "Belum ada transaksi yang terjadi hari ini." << endl;
    } else {
        int totalPendapatan = 0;
        
        // Looping untuk membaca isi Array
        for (int i = 0; i < jumlahTransaksi; i++) {
            cout << "Transaksi ke-" << (i + 1) << "\t: Rp " << transaksi[i] << endl;
            totalPendapatan += transaksi[i];
        }
        cout << "-----------------------------------------------------" << endl;
        cout << "Total Pendapatan : Rp " << totalPendapatan << endl;
        cout << "Total Transaksi  : " << jumlahTransaksi << " kali" << endl;
    }
    cout << "=====================================================\n" << endl;
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