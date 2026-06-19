#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <ctime>
using namespace std;
#define RESET   "\033[0m"
#define MERAH   "\033[31m"
#define HIJAU   "\033[32m"
#define KUNING  "\033[33m"
#define BIRU    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
void cls() {
    cout << "\033[2J\033[H";
}

void pause() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.get();
}
void cetakTengah(string teks) {
    const int LEBAR_TOTAL = 44;
    int panjang_teks = teks.length();
    
    if (panjang_teks >= LEBAR_TOTAL) {
        cout << teks << endl;
        return;
    }

    int sisa_spasi = LEBAR_TOTAL - panjang_teks;
    int spasi_kiri = sisa_spasi / 2;
    
    for (int i = 0; i < spasi_kiri; i++) {
        cout << " ";
    }
    cout << teks << endl;
}
void grafik_stok(Barang arr[], int jumlah) {
    cls();
    cout << "=====================================================\n";
    cetakTengah("MONITORING GRAFIK STOK KAFE (LIVE)");
    cout << "=====================================================\n\n";

    if (jumlah == 0) {
        cout << "[!] Belum ada data barang untuk dibuatkan grafik.\n";
        return;
    }
    for (int i = 0; i < jumlah; i++) {
        cout << left << setw(15) << arr[i].nama << " : [";
        
        int panjangBatang = arr[i].stok / 2;
        if (panjangBatang > 25) panjangBatang = 25;
        if (arr[i].stok > 0 && panjangBatang == 0) panjangBatang = 1;

        for (int j = 0; j < panjangBatang; j++) {
            cout <<HIJAU<< "█"<<RESET;
        }

        int sisaSpasi = 25 - panjangBatang;
        for (int j = 0; j < sisaSpasi; j++) {
            cout << " ";
        }
        cout << "] " << arr[i].stok << " item";
        if (arr[i].stok <= 5) {
            cout <<MERAH<< "  <-- [KRITIS!]"<<RESET;
        }
        cout << "\n";
    }
    cout << "\n-----------------------------------------------------\n";
    cout << "Keterangan: Satuan skala batang (1 blok '"<<HIJAU "█"<<RESET"' = 2 item stok)\n";
}

void cetak_invoice_digital(string nama_barang, int harga_satuan, int jumlah_beli, int total_poin_didapat) {
    cls();
    
    time_t waktu_sekarang = time(0);
    tm *waktu_lokal = localtime(&waktu_sekarang);
    
    int tanggal_aktif = waktu_lokal->tm_mday;
    int bulan_aktif = waktu_lokal->tm_mon + 1;
    int tahun_aktif = waktu_lokal->tm_year + 1900;

    double sub_total = harga_satuan * jumlah_beli;
    double kalkulasi_pajak = sub_total * 0.11; 
    double biaya_servis = 2000;      
    double total_akhir = sub_total + kalkulasi_pajak + biaya_servis;

    cout << "\a" << KUNING << "*klontoooong*\n" << RESET; 
    
    cout << BOLD << CYAN << "=====================================================\n" << RESET;
    cetakTengah("SMART CAFE - NOTA PEMBAYARAN DIGITAL");
    cout << BOLD << CYAN << "=====================================================\n" << RESET;
    
    cout << left << setw(18) << "Tanggal Nota" << ": " 
         << setfill('0') << setw(2) << tanggal_aktif << "/" 
         << setw(2) << bulan_aktif << "/" 
         << tahun_aktif << setfill(' ') << "\n";
         
    cout << left << setw(18) << "Status" << ": " << HIJAU << "LUNAS (Cashless)\n" << RESET;
    cout << "-----------------------------------------------------\n";

    cout << left << setw(25) << "Item" 
         << right << setw(7) << "Qty" 
         << right << setw(18) << "Total" << "\n";
    cout << "-----------------------------------------------------\n";
    
    cout << left << setw(25) << nama_barang 
         << right << setw(7) << jumlah_beli 
         << right << setw(15) << "Rp " << sub_total << "\n";
         
    cout << "-----------------------------------------------------\n";
    
    cout << left << setw(32) << "Subtotal" << right << setw(15) << "Rp " << sub_total << "\n";
    cout << left << setw(32) << "Pajak Restoran (11%)" << right << setw(15) << "Rp " << kalkulasi_pajak << "\n";
    cout << left << setw(32) << "Biaya Layanan/Service" << right << setw(15) << "Rp " << biaya_servis << "\n";
    cout << "-----------------------------------------------------\n";
    
    cout << BOLD << left << setw(32) << "TOTAL PEMBAYARAN" 
         << HIJAU << right << setw(15) << "Rp " << total_akhir << RESET << "\n";
    cout << "=====================================================\n";
    
    cout << KUNING << "[+] Poin Loyalty yang didapat dari item ini: " << total_poin_didapat << " Poin\n" << RESET;
    cout << "=====================================================\n";
    cetakTengah("Terima kasih atas kunjungan Anda!");
    cout << BOLD << CYAN << "=====================================================\n" << RESET;
}