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
#define NEON_PINK    "\033[38;2;255;0;127m"
#define HOT_MAGENTA  "\033[38;2;225;0;255m"
#define NEON_PURPLE  "\033[38;2;150;0;255m"
#define DEEP_BLUE    "\033[38;2;0;100;255m"
#define CYBER_CYAN   "\033[38;2;0;240;255m"
void cls() {
    cout << "\033[2J\033[H";
}

void cetakTengah(string teks) {
    const int LEBAR_TOTAL = 122;
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
void cetak_opsi_tengah(string teks_menu) {
    int lebar_terminal = 112;
    int lebar_konten = 40;
    int s = (lebar_terminal - lebar_konten) / 2;
    string pad(s > 0 ? s : 0, ' ');
    cout << pad << teks_menu << "\n";
}
void cetak_input_tengah(string teks_menu) {
    int lebar_terminal = 112;
    int lebar_konten = 40;
    int s = (lebar_terminal - lebar_konten) / 2;
    string pad(s > 0 ? s : 0, ' ');
    cout << pad << teks_menu;
}
void pause() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cetak_input_tengah("\nTekan ENTER untuk melanjutkan...");
    cin.get();
}
void cetak_banner() {
    int lebar_terminal = 128;
    int lebar_ascii = 66;
    int s = (lebar_terminal - lebar_ascii) / 2;
    string pad(s > 0 ? s : 0, ' ');
    cout << BOLD;

    // Baris 1: Didominasi Pink di kiri, Cyan baru muncul di ujung kanan
    cout << pad 
         << NEON_PINK   << "  ____  __  __    _    ____ "
         << HOT_MAGENTA << "_____    "
         << NEON_PURPLE << "____    _     "
         << CYBER_CYAN  << "_____ _____ \n";

    // Baris 2: Magenta dan Purple mulai bergeser maju ke kiri
    cout << pad 
         << NEON_PINK   << " / ___||  \\/  |  / \\  |"
         << HOT_MAGENTA << "  _ \\_   _|  "
         << NEON_PURPLE << "/ ___|  / \\   "
         << CYBER_CYAN  << "|  ___| ____|\n";

    // Baris 3: Tengah-tengah didominasi Purple, Cyan semakin maju
    cout << pad 
         << NEON_PINK   << " \\___ \\| |\\/| | / "
         << HOT_MAGENTA << "_ \\ | |_) || |    "
         << NEON_PURPLE << "| |    / _ \\  "
         << CYBER_CYAN  << "| |_  |  _|  \n";

    // Baris 4: Pink semakin sedikit di ujung kiri, didominasi Purple & Cyan
    cout << pad 
         << NEON_PINK   << "  ___) | | "
         << HOT_MAGENTA << " | |/ ___ \\|  _ < | |    "
         << NEON_PURPLE << "| |___ "
         << CYBER_CYAN  << "/ ___ \\ |  _| | |___ \n";

    // Baris 5: Pojok kiri bawah sudah berubah menjadi Magenta/Purple, Cyan menguasai kanan
    cout << pad 
         << NEON_PINK   << " |____/"
         << HOT_MAGENTA << "|_|  |_/_/   \\_\\_| \\_\\|_|    "
         << NEON_PURPLE << "\\____/"
         << CYBER_CYAN  << "_/   \\_\\|_|   |_____|\n";

    // Baris Pembatas
    cout << pad 
         << NEON_PINK   << "================" 
         << HOT_MAGENTA << "=================" 
         << NEON_PURPLE << "=================" 
         << CYBER_CYAN  << "================\n";

    cout << RESET;
}
void grafik_stok(Barang arr[], int jumlah) {
    cls();
    cetak_banner();
    cetakTengah("=====================================================");
    cetakTengah("MONITORING GRAFIK STOK KAFE (LIVE)");
    cetakTengah("=====================================================");
    cout << "\n";

    if (jumlah == 0) {
        cetak_opsi_tengah("[!] Belum ada data barang untuk dibuatkan grafik.");
        return;
    }
    for (int i = 0; i < jumlah; i++) {
        // Bagian visualisasi bar di bawah dicetak lurus untuk menjaga keutuhan grafik horizontal
        cout << left << setw(15) << arr[i].nama << " : [";
        
        int panjangBatang = arr[i].stok / 2;
        if (panjangBatang > 25) panjangBatang = 25;
        if (arr[i].stok > 0 && panjangBatang == 0) panjangBatang = 1;

        for (int j = 0; j < panjangBatang; j++) {
            cout << HIJAU << "█" << RESET;
        }

        int sisaSpasi = 25 - panjangBatang;
        for (int j = 0; j < sisaSpasi; j++) {
            cout << " ";
        }
        cout << "] " << arr[i].stok << " item";
        if (arr[i].stok <= 5) {
            cout << MERAH << "  <-- [KRITIS!]" << RESET;
        }
        cout << "\n";
    }
    cout << "\n-----------------------------------------------------\n";
    cetak_input_tengah("Keterangan: Satuan skala batang (1 blok '");
    cout << HIJAU "█" << RESET << "' = 2 item stok)\n";
}

void cetak_invoice_digital(string nama_barang, int harga_satuan, int jumlah_beli, int total_poin_didapat) {
    cls();
    cetak_banner();
    time_t waktu_sekarang = time(0);
    tm *waktu_lokal = localtime(&waktu_sekarang);
    
    int tanggal_aktif = waktu_lokal->tm_mday;
    int bulan_aktif = waktu_lokal->tm_mon + 1;
    int tahun_aktif = waktu_lokal->tm_year + 1900;

    double sub_total = harga_satuan * jumlah_beli;
    double kalkulasi_pajak = sub_total * 0.11; 
    double biaya_servis = 2000;      
    double total_akhir = sub_total + kalkulasi_pajak + biaya_servis;

    cout << "\a" << KUNING;
    cetakTengah("*klontoooong*");
    cout << RESET; 
    
    cout << BOLD << CYAN;
    cetakTengah("=====================================================");
    cout << RESET;
    cetakTengah("SMART CAFE - NOTA PEMBAYARAN DIGITAL");
    cout << BOLD << CYAN;
    cetakTengah("=====================================================");
    cout << RESET;
    
    string s_tanggal = "Tanggal Nota      : " + to_string(tanggal_aktif) + "/" + to_string(bulan_aktif) + "/" + to_string(tahun_aktif);
    string s_status  = "Status            : LUNAS (Cashless)";
    
    cetakTengah(s_tanggal);
    cetakTengah(s_status);
    cetakTengah("-----------------------------------------------------");

    cetakTengah("Item                     Qty                 Total");
    cetakTengah("-----------------------------------------------------");
    
    // 1. Format Baris Item
    string s_item = nama_barang;
    if (s_item.length() < 25) s_item.append(25 - s_item.length(), ' ');
    
    string s_qty = to_string(jumlah_beli);
    if (s_qty.length() < 7) s_qty.append(7 - s_qty.length(), ' ');
    
    string s_harga = "Rp " + to_string((int)sub_total);
    if (s_harga.length() < 21) s_harga.insert(0, 21 - s_harga.length(), ' ');
    
    cetakTengah(s_item + s_qty + s_harga);
    cetakTengah("-----------------------------------------------------");
    
    // 2. Format Baris Subtotal
    string b_sub = "Subtotal";
    if (b_sub.length() < 35) b_sub.append(35 - b_sub.length(), ' ');
    string v_sub = "Rp " + to_string((int)sub_total);
    if (v_sub.length() < 18) v_sub.insert(0, 18 - v_sub.length(), ' ');
    cetakTengah(b_sub + v_sub);

    // 3. Format Baris Pajak
    string b_pajak = "Pajak Restoran (11%)";
    if (b_pajak.length() < 35) b_pajak.append(35 - b_pajak.length(), ' ');
    string v_pajak = "Rp " + to_string((int)kalkulasi_pajak);
    if (v_pajak.length() < 18) v_pajak.insert(0, 18 - v_pajak.length(), ' ');
    cetakTengah(b_pajak + v_pajak);

    // 4. Format Baris Biaya Layanan
    string b_servis = "Biaya Layanan/Service";
    if (b_servis.length() < 35) b_servis.append(35 - b_servis.length(), ' ');
    string v_servis = "Rp " + to_string((int)biaya_servis);
    if (v_servis.length() < 18) v_servis.insert(0, 18 - v_servis.length(), ' ');
    cetakTengah(b_servis + v_servis);
    
    cetakTengah("-----------------------------------------------------");
    
    // 5. Format Baris Total Akhir
    string b_total = "TOTAL PEMBAYARAN";
    if (b_total.length() < 35) b_total.append(35 - b_total.length(), ' ');
    string v_total = "Rp " + to_string((int)total_akhir);
    if (v_total.length() < 18) v_total.insert(0, 18 - v_total.length(), ' ');
    cetakTengah(b_total + v_total);
    
    cetakTengah("=====================================================");
    
    string s_poin = "[+] Poin Loyalty yang didapat dari item ini: " + to_string(total_poin_didapat) + " Poin";
    cout << KUNING;
    cetakTengah(s_poin);
    cout << RESET;
    
    cetakTengah("=====================================================");
    cetakTengah("Terima kasih atas kunjungan Anda!");
    cout << BOLD << CYAN;
    cetakTengah("=====================================================");
    cout << RESET;
}
void simpan_stok_ke_file(Barang daftar[], int jumlah) {
    ofstream file("stok_barang.txt");
    if (file.is_open()) {
        for (int i = 0; i < jumlah; i++) {
            file << daftar[i].id << ","
                 << daftar[i].nama << ","
                 << daftar[i].harga << ","
                 << daftar[i].stok << ","
                 << daftar[i].penambah << "\n";
        }
        file.close();
    }
}

void muat_stok_dari_file(Barang daftar[], int &jumlah) {
    ifstream file("stok_barang.txt");
    if (!file.is_open()) {
        return; 
    }
    
    jumlah = 0;
    string harga_str, stok_str;
    
    while (getline(file, daftar[jumlah].id, ',') &&
           getline(file, daftar[jumlah].nama, ',') &&
           getline(file, harga_str, ',') &&
           getline(file, stok_str, ',') &&
           getline(file, daftar[jumlah].penambah)) {
        
        daftar[jumlah].harga = stoi(harga_str);
        daftar[jumlah].stok = stoi(stok_str);
        jumlah++;
    }
    file.close();
}