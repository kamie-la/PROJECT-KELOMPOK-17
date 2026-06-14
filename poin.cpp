#include <iostream>
using namespace std;

int totalPoin=0;
int transaksi [100];
int jumlahTransaksi=0;

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

int main () {
    int belanja;
    cout << "Masukkan total belanja: Rp. "; cin >> belanja;
    prosesTransaksi(belanja);
    return 0;
}