// ===================================================================================
// 1. LIBRARIES & OS INCLUDES
// ===================================================================================
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>
#include <fstream>
#include <limits>
#include <ctime>
#include <cstdlib>

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
#endif

using namespace std;

// ===================================================================================
// 2. MACROS WARNA TERMINAL
// ===================================================================================
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

#if defined(_WIN32) || defined(_WIN64)
    #ifndef kbhit
        #define kbhit _kbhit
    #endif
    #ifndef getch
        #define getch _getch
    #endif
#endif

// ===================================================================================
// 3. STRUCTS & GLOBAL VARIABLES
// ===================================================================================
struct Barang {
    string id;
    string nama;
    int harga;
    int stok;
    string penambah;
};

struct Hadiah {
    string namaHadiah;
    string rarity;
};

const int MAKS_DATA = 100;
Barang daftar_menu[MAKS_DATA];
int jumlah_barang = 0;

Hadiah daftar_hadiah[MAKS_DATA];
int jumlah_hadiah = 0;
int totalPoin = 0;
int transaksi[100];
int jumlahTransaksi = 0;
int sisa_buff_draw = 0;
string nama_admin_aktif = "System";

// Data init Gacha
Hadiah hadiahR[50] = {{"Voucher Diskon 5%", "R"}, {"Permen", "R"}, {"Stiker Toko", "R"}};
Hadiah hadiahSR[50] = {{"Tumbler", "SR"}, {"Kopi Ireng", "SR"}};
Hadiah hadiahSSR[50] = {{"Earphone", "SSR"}};

int stokR = 3;   
int stokSR = 2;  
int stokSSR = 1; 

// ===================================================================================
// 4. PROTOTIPE FUNGSI (Untuk mencegah error "not declared in this scope")
// ===================================================================================
void cls();
void cetakTengah(string teks);
void cetak_opsi_tengah(string teks_menu);
void cetak_input_tengah(string teks_menu);
void pause();
void cetak_banner();
void grafik_stok(Barang arr[], int jumlah);
void cetak_invoice_digital(string nama_barang, int harga_satuan, int jumlah_beli, int total_poin_didapat);
void simpan_stok_ke_file(Barang daftar[], int jumlah);
void muat_stok_dari_file(Barang daftar[], int &jumlah);

void editBarang(Barang daftarBarang[], int &jumlahBarang);
void hapusBarang(Barang daftarBarang[], int &jumlahBarang);

void prosesTransaksi(int totalHarga);
void lihatPoin();
void riwayatTransaksi();

void lihatInventori(Hadiah tas[], int jumlah);
void menuGacha(int* poinUser, Hadiah tas[], int* isiTas);
void tambah_hadiah_admin(int* batasR, int* batasSR, int* batasSSR);

void beliBarang(Barang arr[], int jumlah);
void menu_pembeli(Barang daftar_menu[], int jumlah_barang, int &total_poin, Hadiah inventori_hadiah[], int &jumlah_di_tas);

bool mainkan_game_maneki_catch();

void simpan_txt(string nama, string nim);
bool cek_apakah_atmint_ada(string nama_cari, string nim_cari);
bool cek_duplikat_registrasi(string nama_daftar, string nim_daftar);
bool cek_file_kosong();
bool validasi_nim_atmint(string nim);
bool jalankan_captcha_simpel();
bool proses_autentikasi_atmint();
void tambahmenubaru(Barang arr[], int *jumlah, int kapasitas);
void lihatsemuamenu(Barang arr[], int jumlah);
void menuadmin(Barang arr[], int *jumlah, int kapasitas);


// ===================================================================================
// 5. IMPLEMENTASI MODUL: utilitas.cpp (Team)
// ===================================================================================
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

    cout << pad << NEON_PINK   << "  ____  __  __    _    ____ " << HOT_MAGENTA << "_____    " << NEON_PURPLE << "____    _     " << CYBER_CYAN  << "_____ _____ \n";
    cout << pad << NEON_PINK   << " / ___||  \\/  |  / \\  |" << HOT_MAGENTA << "  _ \\_   _|  " << NEON_PURPLE << "/ ___|  / \\   " << CYBER_CYAN  << "|  ___| ____|\n";
    cout << pad << NEON_PINK   << " \\___ \\| |\\/| | / " << HOT_MAGENTA << "_ \\ | |_) || |    " << NEON_PURPLE << "| |    / _ \\  " << CYBER_CYAN  << "| |_  |  _|  \n";
    cout << pad << NEON_PINK   << "  ___) | | " << HOT_MAGENTA << " | |/ ___ \\|  _ < | |    " << NEON_PURPLE << "| |___ " << CYBER_CYAN  << "/ ___ \\ |  _| | |___ \n";
    cout << pad << NEON_PINK   << " |____/" << HOT_MAGENTA << "|_|  |_/_/   \\_\\_| \\_\\|_|    " << NEON_PURPLE << "\\____/" << CYBER_CYAN  << "_/   \\_\\|_|   |_____|\n";
    cout << pad << NEON_PINK   << "================" << HOT_MAGENTA << "=================" << NEON_PURPLE << "=================" << CYBER_CYAN  << "================\n";
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
    
    string s_item = nama_barang;
    if (s_item.length() < 25) s_item.append(25 - s_item.length(), ' ');
    
    string s_qty = to_string(jumlah_beli);
    if (s_qty.length() < 7) s_qty.append(7 - s_qty.length(), ' ');
    
    string s_harga = "Rp " + to_string((int)sub_total);
    if (s_harga.length() < 21) s_harga.insert(0, 21 - s_harga.length(), ' ');
    
    cetakTengah(s_item + s_qty + s_harga);
    cetakTengah("-----------------------------------------------------");
    
    string b_sub = "Subtotal";
    if (b_sub.length() < 35) b_sub.append(35 - b_sub.length(), ' ');
    string v_sub = "Rp " + to_string((int)sub_total);
    if (v_sub.length() < 18) v_sub.insert(0, 18 - v_sub.length(), ' ');
    cetakTengah(b_sub + v_sub);

    string b_pajak = "Pajak Restoran (11%)";
    if (b_pajak.length() < 35) b_pajak.append(35 - b_pajak.length(), ' ');
    string v_pajak = "Rp " + to_string((int)kalkulasi_pajak);
    if (v_pajak.length() < 18) v_pajak.insert(0, 18 - v_pajak.length(), ' ');
    cetakTengah(b_pajak + v_pajak);

    string b_servis = "Biaya Layanan/Service";
    if (b_servis.length() < 35) b_servis.append(35 - b_servis.length(), ' ');
    string v_servis = "Rp " + to_string((int)biaya_servis);
    if (v_servis.length() < 18) v_servis.insert(0, 18 - v_servis.length(), ' ');
    cetakTengah(b_servis + v_servis);
    
    cetakTengah("-----------------------------------------------------");
    
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


// ===================================================================================
// 6. IMPLEMENTASI MODUL: AdminBagian2cpp.cpp (Hari)
// ===================================================================================
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


// ===================================================================================
// 7. IMPLEMENTASI MODUL: poin.cpp (Krisna)
// ===================================================================================
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


// ===================================================================================
// 8. IMPLEMENTASI MODUL: undian.cpp (Rizka)
// ===================================================================================
void lihatInventori(Hadiah tas[], int jumlah) {
    cls();
    cetak_banner();
    cetakTengah("=====================================================");
    cetakTengah("INVENTORI HADIAH ANDA");
    cetakTengah("=====================================================");
    cout << "\n";

    if(jumlah == 0) {
        cetak_opsi_tengah("Belum ada hadiah di dalam tas Anda.");
        pause();
        return;
    }

    int baris_maksimal = 10;
    int lebar_terminal = 112;
    int lebar_konten = 60;
    int s = (lebar_terminal - lebar_konten) / 2;
    string pad(s > 0 ? s : 0, ' ');

    for (int i = 0; i < baris_maksimal && i < jumlah; i++) {
        string item_kiri = to_string(i + 1) + ". " + tas[i].namaHadiah + " (" + tas[i].rarity + ")";
        
        cout << pad << left << setw(35) << item_kiri;

        if (i + baris_maksimal < jumlah) {
            int idx_kanan = i + baris_maksimal;
            string item_kanan = to_string(idx_kanan + 1) + ". " + tas[idx_kanan].namaHadiah + " (" + tas[idx_kanan].rarity + ")";
            cout << left << item_kanan;
        }
        
        cout << "\n";
    }   
    cout << "\n";
    cetakTengah("-----------------------------------------------------");
    pause();
}

void menuGacha(int* poinUser, Hadiah tas[], int* isiTas){
    int pilihanMenu;
    int jumlahUndi = 0;     
    while(true){
        cls();
        cetak_banner();
        cetakTengah("==== MENU UNDIAN ====");
        
        cetak_input_tengah("Poin Anda: ");
        cout << *poinUser << "\n";
        
        cetak_opsi_tengah("1. Undi x1 (1 Poin)");
        cetak_opsi_tengah("2. Undi x5 (5 Poin)");
        cetak_opsi_tengah("0. Keluar");
        cetakTengah("--------------------------------------------");
        
        cetak_input_tengah("Pilih: ");
        cin >> pilihanMenu;
    
        if (pilihanMenu == 1){
            jumlahUndi = 1;
        } else if (pilihanMenu == 2){
            jumlahUndi = 5;
        } else if (pilihanMenu == 0){
            break;
        } else {
            cetak_opsi_tengah("[!] Pilihan salah!");
            pause();
            continue;
        }
        
        if (*poinUser < jumlahUndi){
            cetak_opsi_tengah("[!] Poin tidak cukup!");
            pause();
            continue;
        }
        
        *poinUser -= jumlahUndi;
        
        cetak_input_tengah(">> MENGUNDI HADIAH");
        for (int i = 0; i < 3; i++) {
            this_thread::sleep_for(chrono::milliseconds(500));
            cout << ".";
            cout.flush();
        }
        cout << endl << endl;
        
        bool dapatSRatauSSR = false;
        
        for (int i = 1; i <= jumlahUndi; i++) {
            string rarity;
            Hadiah hadiahTerpilih; 
            
            if (jumlahUndi == 5 && i == 5 && !dapatSRatauSSR){
                rarity = "SR";
            } else {
                int angka = (rand() % 100) + 1; 
                if (sisa_buff_draw > 0) {
                    if (angka <= 6) { 
                        rarity = "SSR";
                        dapatSRatauSSR = true;
                    } else if (angka <= 15) { 
                        rarity = "SR";
                        dapatSRatauSSR = true;
                    } else {
                        rarity = "R";
                    }
                    sisa_buff_draw--; 
                } else {
                    if (angka == 1) { 
                        rarity = "SSR";
                        dapatSRatauSSR = true;
                    } else if (angka <= 10) { 
                        rarity = "SR";
                        dapatSRatauSSR = true;
                    } else { 
                        rarity = "R";
                    }
                }
            }
            
            if(rarity == "R") {
                int pilih = rand() % stokR;
                hadiahTerpilih = hadiahR[pilih];
            } 
            else if(rarity == "SR") {
                int pilih = rand() % stokSR;
                hadiahTerpilih = hadiahSR[pilih];
                dapatSRatauSSR = true; 
            } 
            else {
                int pilih = rand() % stokSSR;
                hadiahTerpilih = hadiahSSR[pilih];
                dapatSRatauSSR = true;
            }
            
            cetak_input_tengah("Undian ");
            cout << i << " : " << hadiahTerpilih.namaHadiah << " (" << hadiahTerpilih.rarity << ")" << endl;
            
            tas[*isiTas] = hadiahTerpilih;
            (*isiTas)++;                   
        }
        
        cetak_input_tengah("\nSisa poin: ");
        cout << *poinUser << "\n";
        pause();
    }
}

void tambah_hadiah_admin(int* batasR, int* batasSR, int* batasSSR) {
    cls();
    cetak_banner();
    cetakTengah("=====================================================");
    cetakTengah("MENU ADMIN - REWARD MANAGER");
    cetakTengah("=====================================================");
    
    string namaBaru;
    int pilihanTier;
    
    cetak_input_tengah("Masukkan Nama Hadiah Baru: ");
    cin.ignore();
    getline(cin, namaBaru);
    
    cetak_opsi_tengah("\nPilih Tingkat Kelangkaan (Rarity Tier):");
    cetak_opsi_tengah("1. R   (Common)");
    cetak_opsi_tengah("2. SR  (Rare)");
    cetak_opsi_tengah("3. SSR (Epic/Legendary)");
    
    cetak_input_tengah("Pilihan: ");
    cin >> pilihanTier;
    
    if (pilihanTier == 1) {
        if (*batasR >= 50) {
            cetak_opsi_tengah("\n[!] Kapasitas inventori hadiah R penuh!");
            pause();
            return;
        }
        hadiahR[*batasR].namaHadiah = namaBaru;
        hadiahR[*batasR].rarity = "R";
        (*batasR)++;
        cetak_opsi_tengah("\n[✓] Hadiah \"" + namaBaru + "\" berhasil ditambahkan ke Tier R!");
    } 
    else if (pilihanTier == 2) {
        if (*batasSR >= 50) {
            cetak_opsi_tengah("\n[!] Kapasitas inventori hadiah SR penuh!");
            pause();
            return;
        }
        hadiahSR[*batasSR].namaHadiah = namaBaru;
        hadiahSR[*batasSR].rarity = "SR";
        (*batasSR)++;
        cetak_opsi_tengah("\n[✓] Hadiah \"" + namaBaru + "\" berhasil ditambahkan ke Tier SR!");
    } 
    else if (pilihanTier == 3) {
        if (*batasSSR >= 50) {
            cetak_opsi_tengah("\n[!] Kapasitas inventori hadiah SSR penuh!");
            pause();
            return;
        }
        hadiahSSR[*batasSSR].namaHadiah = namaBaru;
        hadiahSSR[*batasSSR].rarity = "SSR";
        (*batasSSR)++;
        cetak_opsi_tengah("\n[✓] Hadiah \"" + namaBaru + "\" berhasil ditambahkan ke Tier SSR!");
    } 
    else {
        cetak_opsi_tengah("\n[!] Pilihan tier tidak valid!");
    }
    pause();
}


// ===================================================================================
// 9. IMPLEMENTASI MODUL: admin 1.cpp (Widya)
// ===================================================================================
void simpan_txt(string nama, string nim) {
    ofstream file_atmint("data_atmint.txt", ios::app);
    if (file_atmint.is_open()) {
        file_atmint << nama << "\n";
        file_atmint << nim << "\n";
        file_atmint.close();
    }
}

bool cek_apakah_atmint_ada(string nama_cari, string nim_cari) {
    ifstream file_atmint("data_atmint.txt");
    if (file_atmint.is_open()) {
        string nama_file, nim_file;
        while (getline(file_atmint, nama_file) && getline(file_atmint, nim_file)) {
            if (nama_file == nama_cari && nim_file == nim_cari) {
                file_atmint.close();
                return true;
            }
        }
        file_atmint.close();
    }
    return false;
}

bool cek_duplikat_registrasi(string nama_daftar, string nim_daftar) {
    ifstream file_atmint("data_atmint.txt");
    if (file_atmint.is_open()) {
        string nama_file, nim_file;
        while (getline(file_atmint, nama_file) && getline(file_atmint, nim_file)) {
            if (nama_file == nama_daftar || nim_file == nim_daftar) {
                file_atmint.close();
                return true;
            }
        }
        file_atmint.close();
    }
    return false;
}

bool cek_file_kosong() {
    ifstream file_atmint("data_atmint.txt");
    if (file_atmint.is_open()) {
        string baris;
        if (getline(file_atmint, baris)) {
            file_atmint.close();
            return false;
        }
        file_atmint.close();
    }
    return true;
}

bool validasi_nim_atmint(string nim) {
    if (nim.length() != 11) {
        return false;
    }
    if (nim.substr(0, 5) != "F1D02") {
        return false;
    }
    for (int i = 5; i < 11; i++) {
        if (nim[i] < '0' || nim[i] > '9') {
            return false;
        }
    }
    return true;
}

bool jalankan_captcha_simpel() {
    srand(time(0));
    int salah_hitung = 0;
    
    while (salah_hitung < 3) {
        int a = (rand() % 10) + 1;
        int b = (rand() % 10) + 1;
        int hasil_benar = a + b;
        int jawaban_user;

        cls();
        cetak_banner();
        cetakTengah("============================================");
        cetakTengah("SECURITY VERIFICATION (CAPTCHA)");
        cetakTengah("============================================");
        cetak_opsi_tengah("Selesaikan operasi matematika berikut:");
        
        cetak_input_tengah("Berapakah hasil dari " + to_string(a) + " + " + to_string(b) + " = ");
        if (!(cin >> jawaban_user)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            salah_hitung++;
            cetak_opsi_tengah("\n" MERAH "[!] Input harus berupa angka!" RESET);
            cetak_opsi_tengah("Toleransi kesalahan: " + to_string(salah_hitung) + "/3");
            pause();
            continue;
        }

        if (jawaban_user == hasil_benar) {
            return true;
        } else {
            salah_hitung++;
            cetak_opsi_tengah("\n" MERAH "[!] Jawaban salah!" RESET);
            cetak_opsi_tengah("Toleransi kesalahan: " + to_string(salah_hitung) + "/3");
            pause();
        }
    }
    return false;
}

bool proses_autentikasi_atmint() {
    string nama_data = "", nim_data = "";
    int opsi_auth = 1;

    if (!cek_file_kosong()) {
        cls();
        cetak_banner();
        cetakTengah("============================================");
        cetakTengah("ADMIN GATE AUTHENTICATION SYSTEM");
        cetakTengah("============================================");
        cetak_opsi_tengah("1. Sign In (Masuk Log)");
        cetak_opsi_tengah("2. Sign Up (Daftar Akun Admin Baru)");
        cetak_opsi_tengah("0. Kembali");
        cetakTengah("--------------------------------------------");
        cetak_input_tengah("Pilihan Anda: ");
        cin >> opsi_auth;

        if (opsi_auth == 0) {
            return false;
        }
        if (opsi_auth != 1 && opsi_auth != 2) {
            cetak_opsi_tengah("\n" MERAH "[!] Pilihan tidak valid!" RESET);
            pause();
            return false;
        }
    } else {
        opsi_auth = 2;
    }

    if (opsi_auth == 2) {
        while (true) {
            cls();
            cetak_banner();
            cetakTengah("============================================");
            cetakTengah("REGISTRASI AKUN ADMIN BARU (SIGN UP)");
            cetakTengah("============================================");
            
            cetak_input_tengah("Daftarkan Nama Admin  : ");
            cin.ignore();
            getline(cin, nama_data);
            
            if (nama_data.empty() || nama_data == " " || nama_data == "\t") {
                cetak_opsi_tengah("\n" MERAH "[!] Error: Nama tidak boleh kosong!" RESET);
                pause();
                continue;
            }

            cetak_input_tengah("Daftarkan NIM Admin   : ");
            cin >> nim_data;

            if (!validasi_nim_atmint(nim_data)) {
                cetak_opsi_tengah("\n" MERAH "[!] REGISTRASI GAGAL: NIM harus 11 digit dan diawali 'F1D02'!" RESET);
                pause();
                continue;
            }

            if (cek_duplikat_registrasi(nama_data, nim_data)) {
                cetak_opsi_tengah("\n" MERAH "[!] REGISTRASI GAGAL: Nama atau NIM sudah terdaftar oleh Admin lain!" RESET);
                pause();
                continue;
            }

            if (!jalankan_captcha_simpel()) {
                cls();
                cetak_banner();
                cetakTengah("============================================");
                cetak_opsi_tengah("\n" MERAH "[!] AKSES DIKUNCI: Anda salah mengisi CAPTCHA sebanyak 3 kali!" RESET);
                pause();
                return false;
            }

            simpan_txt(nama_data, nim_data);
            cls();
            cetak_banner();
            cetakTengah("============================================");
            cetak_opsi_tengah("\n" HIJAU "[✓] SIGN UP BERHASIL! Data tersimpan." RESET);
            pause();
            break;
        }
    }

    if (opsi_auth == 1) {
        cin.ignore(); 
    }

    while (true) {
        string nama_masuk, nim_masuk;
        cls();
        cetak_banner();
        cetakTengah("============================================");
        cetakTengah("SISTEM MASUK ADMIN (SIGN IN)");
        cetakTengah("============================================");
        
        cetak_input_tengah("Masukkan Nama Anda : ");
        getline(cin, nama_masuk);
        
        cetak_input_tengah("Masukkan NIM Anda  : ");
        cin >> nim_masuk;

        if (!cek_apakah_atmint_ada(nama_masuk, nim_masuk)) {
            cls();
            cetak_banner();
            cetakTengah("============================================");
            cetak_opsi_tengah("\n" MERAH "[!] AKSES DITOLAK: Nama atau NIM tidak cocok dengan akun terdaftar manapun!" RESET);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }

        nama_admin_aktif = nama_masuk;

        cls();
        cetak_banner();
        cetakTengah("============================================");
        cetak_opsi_tengah("\n" HIJAU "[✓] LOGIN SUKSES: Selamat datang kembali, Admin " + nama_masuk + "!" RESET);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        pause();
        break;
    }
    
    return true;
}

void tambahmenubaru(Barang arr[], int *jumlah, int kapasitas) {
    if (*jumlah >= kapasitas) {
        cls();
        cetak_banner();
        cetak_opsi_tengah("\n[!] Array penuh! Tidak bisa menambah menu baru.");
        pause();
        return;
    }

    string id_input;
    string nama_input;
    int harga_input;
    int stok_input;
    
    while (true) {
        cls();
        cetak_banner();
        cetakTengah("====== TAMBAH MENU BARU ======");

        cetak_input_tengah("Masukkan ID Menu   : ");
        cin >> id_input;

        bool ada_spasi_id = false;
        if (cin.peek() == ' ' || cin.peek() == '\t') {
            ada_spasi_id = true;
        }

        if (id_input == "0") {
            cetak_opsi_tengah("\n" MERAH "[!] Error: ID \"0\" tidak boleh digunakan!" RESET);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }

        if (ada_spasi_id) {
            cetak_opsi_tengah("\n" MERAH "[!] Error: ID Menu tidak boleh mengandung spasi!" RESET);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }

        bool id_duplikat = false;
        for (int i = 0; i < *jumlah; i++) {
            if (arr[i].id == id_input) {
                id_duplikat = true;
                break;
            }
        }

        if (id_duplikat) {
            cetak_opsi_tengah("\n" MERAH "[!] Error: ID Menu sudah terdaftar sebelumnya!" RESET);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cetak_input_tengah("Masukkan Nama Menu : ");
        getline(cin, nama_input);

        if (nama_input.empty() || nama_input == " " || nama_input == "\t") {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Nama menu tidak boleh kosong!" RESET);
            pause();
            continue;
        }

        cetak_input_tengah("Masukkan Harga     : Rp ");
        if (!(cin >> harga_input)) {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Harga harus berupa angka dan tidak boleh ada spasi/karakter!" RESET);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }

        if (cin.peek() == ' ' || cin.peek() == '\t') {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Harga tidak boleh mengandung spasi!" RESET);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }

        if (harga_input <= 0) {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Harga harus lebih besar dari 0!" RESET);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }

        cetak_input_tengah("Masukkan Stok      : ");
        if (!(cin >> stok_input)) {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Stok harus berupa angka dan tidak boleh ada spasi/karakter!" RESET);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }

        if (cin.peek() == ' ' || cin.peek() == '\t') {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Stok tidak boleh mengandung spasi!" RESET);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }

        if (stok_input < 0) {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Stok tidak boleh bernilai negatif!" RESET);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }

        arr[*jumlah].id = id_input;
        arr[*jumlah].nama = nama_input;
        arr[*jumlah].harga = harga_input;
        arr[*jumlah].stok = stok_input;
        arr[*jumlah].penambah = nama_admin_aktif;
        (*jumlah)++;

        simpan_stok_ke_file(arr, *jumlah);

        cetak_opsi_tengah("\n" HIJAU "[✓] Menu berhasil ditambahkan!" RESET);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        pause();
        break;
    }
}

void lihatsemuamenu(Barang arr[], int jumlah) {
    cls();
    cetak_banner();
    cetakTengah("====== DAFTAR SEMUA MENU KAFE ======");

    if (jumlah == 0) {
        cetak_opsi_tengah("[!] Belum ada menu yang tersedia.");
        return;
    }

    cout << left
         << setw(6)  << "ID"
         << setw(25) << "Nama Menu"
         << setw(15) << "Harga (Rp)"
         << setw(8)  << "Stok"
         << setw(15) << "Penambah"
         << "\n";

    cout << string(69, '-') << "\n";

    for (int i = 0; i < jumlah; i++) {
        cout << left
             << setw(6)  << arr[i].id
             << setw(25) << arr[i].nama
             << setw(15) << fixed << setprecision(0) << arr[i].harga
             << setw(8)  << arr[i].stok
             << setw(15) << arr[i].penambah
             << "\n";
    }

    cout << string(69, '-') << "\n";
    cetak_input_tengah("Total menu: ");
    cout << jumlah << " item\n";
}

void menuadmin(Barang arr[], int *jumlah, int kapasitas) {
    if (!proses_autentikasi_atmint()) {
        return; 
    }
    int pilihan;
    do {
        cls();
        cetak_banner();
        cetakTengah("============================================");
        cetakTengah("MENU UTAMA ADMIN MANAGEMENT");
        cetakTengah("============================================");
        
        cetak_opsi_tengah("     1. Tambah Menu Baru");
        cetak_opsi_tengah("     2. Lihat Semua Menu");
        cetak_opsi_tengah("     3. Edit Data Barang");
        cetak_opsi_tengah("     4. Hapus Data Barang");
        cetak_opsi_tengah("     5. Lihat Grafik Stok Visual");
        cetak_opsi_tengah("     6. Kelola & Tambah Hadiah Gacha");
        cetak_opsi_tengah("     0. Kembali ke Role Selection");
        cetakTengah("--------------------------------------------");
        
        cetak_input_tengah("    Pilihan: ");
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                tambahmenubaru(arr, jumlah, kapasitas);
                break;
            case 2:
                lihatsemuamenu(arr, *jumlah);
                pause();
                break;
            case 3:
                editBarang(daftar_menu, jumlah_barang);
                simpan_stok_ke_file(arr, *jumlah);
                break;
            case 4:
                hapusBarang(daftar_menu, jumlah_barang);
                simpan_stok_ke_file(arr, *jumlah);
                break;
            case 5:
                grafik_stok(arr, *jumlah);
                pause();
                break;
            case 6:
                tambah_hadiah_admin(&stokR, &stokSR, &stokSSR);
                break;
            case 0:
                cetak_opsi_tengah("[✓] Kembali ke menu utama...\n");
                pause();
                break;
            default:
                cetak_opsi_tengah("[!] Pilihan tidak valid!\n");
                pause();
        }
    } while (pilihan != 0);
}


// ===================================================================================
// 10. IMPLEMENTASI MODUL: minigame.cpp (Arizona)
// ===================================================================================
#if !defined(_WIN32) && !defined(_WIN64)
int kbhit_posix() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
#endif

bool mainkan_game_maneki_catch() {
    cls();
    
    cetak_banner();
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << NEON_PINK;
    cetakTengah("MINI GAME: MANEKI NEKO'S GOLDEN COIN CATCH");
    cout << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << RESET << "\n";
    
    cetak_opsi_tengah("Tangkap koin emas yang meluncur dari kiri ke kanan!");
    cetak_opsi_tengah("Ketuk [ " KUNING "SPACEBAR" RESET " ] tepat saat koin '" KUNING "o" RESET "' berada di tengah '" CYBER_CYAN "|" RESET "'!");
    cout << "\n";
    cetak_opsi_tengah("Tekan [ " HIJAU "ENTER" RESET " ] untuk menyalakan mesin...");
    cetakTengah(NEON_PURPLE "--------------------------------------------" RESET);
    
    cin.get();

    int nyawa = 3;
    int skor_koin = 0;
    int posisi_koin = 0;
    int batas_lebar = 30;
    int kecepatan = 50;

    int lebar_terminal = 122; 
    int s = (lebar_terminal - batas_lebar) / 2;
    string pad(s > 0 ? s : 0, ' ');

    cls(); 
    cout << "\033[?25l"; 

    string header_teks = ">> MANEKI NEKO ARCADE <<";
    int s_head = (lebar_terminal - header_teks.length()) / 2;
    string pad_head(s_head > 0 ? s_head : 0, ' ');
    cout << pad_head << BOLD << NEON_PINK << header_teks << "\n\n" << RESET;

    cout << "\033[s"; 

    while (nyawa > 0 && skor_koin < 3) {
        
        cout << "\033[u"; 

        string lintasan_koin = "";
        for (int j = 0; j < batas_lebar; j++) {
            if (j == posisi_koin) {
                lintasan_koin += string(BOLD) + KUNING + "o" + RESET;
            } else if (j == 15) {
                lintasan_koin += string(BOLD) + CYBER_CYAN + "|" + RESET;
            } else {
                lintasan_koin += "\033[2m-\033[0m";
            }
        }

        string s_status = "Koin Tertangkap: " + to_string(skor_koin) + " / 3  |  Sisa Kesempatan: " + to_string(nyawa);
        int s_center = (lebar_terminal - s_status.length()) / 2;
        string pad_status(s_center > 0 ? s_center : 0, ' ');

        cout << pad << "\033[K        " << BOLD << NEON_PINK << "/\\_/\\" << RESET << "\n"
             << pad << "\033[K       " << BOLD << NEON_PINK << "( " << KUNING << "o" << NEON_PINK << "." << KUNING << "o" << NEON_PINK << " )" << RESET << "\n"
             << pad << "\033[K        " << BOLD << NEON_PINK << "\\ _ /" << RESET << "\n"
             << pad << "\033[K  " << NEON_PURPLE << "[" << RESET << lintasan_koin << NEON_PURPLE << "]\n" << RESET
             << pad << "\033[K   Mangkuk: " << CYBER_CYAN << "[   |   ]" << RESET << "\n"
             << "\033[K" << pad_status << HIJAU << "Koin Tertangkap: " << BOLD << skor_koin << RESET << " / 3  |  "
             << (nyawa == 1 ? MERAH : KUNING) << "Sisa Kesempatan: " << BOLD << nyawa << RESET << flush;

        bool tombol_ditekan = false;
#if defined(_WIN32) || defined(_WIN64)
        if (kbhit()) {
            if (getch() == ' ') tombol_ditekan = true;
        }
#else
        if (kbhit_posix()) {
            struct termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            int ch = getchar();
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            if (ch == ' ') tombol_ditekan = true;
        }
#endif

        if (tombol_ditekan) {
            if (posisi_koin >= 14 && posisi_koin <= 16) {
                skor_koin++;
                kecepatan -= 8; 
                posisi_koin = 0; 
            } else {
                nyawa--;
                posisi_koin = 0;
            }
        }

        posisi_koin++;
        if (posisi_koin >= batas_lebar) {
            posisi_koin = 0;
            nyawa--; 
        }

        this_thread::sleep_for(chrono::milliseconds(kecepatan));
    }
    
    cout << "\033[?25h"; 

    cls();
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << NEON_PINK;
    cetakTengah("KEPUTUSAN REZEKI MANEKI NEKO");
    cout << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << RESET << "\n";

    if (skor_koin >= 3) {
        cetak_opsi_tengah(HIJAU "[✓] BERHASIL! Mangkuk Anda penuh terisi koin keberuntungan." RESET);
        cetak_opsi_tengah("Maneki Neko mengaktifkan Buff Pity SSR (+5%) untuk 3 Draw!");
        cout << "\n";
        pause();
        return true;
    } else {
        cetak_opsi_tengah(MERAH "[!] GAGAL! Koin berjatuhan berserakan di lantai kafe." RESET);
        cetak_opsi_tengah("Gagal menyelaraskan ritme.");
        cout << "\n";
        pause();
        return false;
    }
}


// ===================================================================================
// 11. IMPLEMENTASI MODUL: customerTransaction.cpp (Kamila)
// ===================================================================================
void beliBarang(Barang arr[], int jumlah) {
    while(true){
        cls();
        lihatsemuamenu(arr, jumlah);
        if (jumlah == 0) {
            cetak_opsi_tengah("[!] Tidak Ada Barang");
            pause();
            return;
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
            cetak_opsi_tengah("\n" MERAH "[!] Menu dengan ID " + idPilihan + " tidak ditemukan." RESET);
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
        
        if (!(cin >> jumlahBeli)) {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Input harus berupa angka bulat dan tidak boleh ada karakter/spasi!" RESET);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }

        if (cin.peek() == ' ' || cin.peek() == '\t') {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Input tidak boleh mengandung spasi!" RESET);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }
    
        if (jumlahBeli <= 0) {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Jumlah beli harus lebih besar dari 0!" RESET);
            pause();
            continue;
        }
        
        if (jumlahBeli > itemDipilih->stok) {
            cetak_input_tengah("\n" MERAH "[!] Stok tidak cukup! Stok tersedia hanya " RESET);
            cout << itemDipilih->stok << " item.\n";
            pause();
            continue;
        }
    
        double totalHarga = itemDipilih->harga * jumlahBeli;
    
        itemDipilih->stok -= jumlahBeli;
        
        simpan_stok_ke_file(arr, jumlah);
    
        cetak_input_tengah("\n" HIJAU "[✓] Pembelian berhasil! Sisa stok \"" RESET);
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
                if (sisa_buff_draw != 0) {
                    cls();
                    cetak_banner();
                    cetakTengah("=====================================================");
                    cetakTengah("PERINGATAN: BERKAT MANEKI NEKO MASIH AKTIF!");
                    cetakTengah("=====================================================");
                    cout << "\n";
                    
                    int kuota_tampil = (sisa_buff_draw < 0) ? 0 : sisa_buff_draw;
                    if (sisa_buff_draw < 0) {
                        sisa_buff_draw = 0;
                    }

                    cetak_opsi_tengah(MERAH "[!] Anda masih memiliki kuota gacha beruntung." RESET);
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


// ===================================================================================
// 12. ROOT CONTROLLER: main.cpp
// ===================================================================================
int main() {
    #if defined(_WIN32) || defined(_WIN64)
        system("chcp 65001 > nul");
    #endif
    
    muat_stok_dari_file(daftar_menu, jumlah_barang);
    if (jumlah_barang == 0) {
        daftar_menu[0] = {"K1", "Kopi Ireng", 10000, 20, "Rezeki Tuhan"};
        daftar_menu[1] = {"E1", "Es teh hangat", 15000, 15, "Rezeki Tuhan"};
        jumlah_barang = 2;
        simpan_stok_ke_file(daftar_menu, jumlah_barang);
    }
    
    Hadiah inventori[100];
    int pilihan_role;
    int jumlahDiTas = 0;
    
    do {
        cls();
        cetak_banner();
        cout << BOLD << NEON_PURPLE;
        cetakTengah("============================================");
        cout << NEON_PINK;
        cetakTengah("WELCOME TO SMART CAFE LOYALTY");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("============================================");
        cout << RESET;
        
        cetak_opsi_tengah("    1. Masuk Sebagai Admin");
        cetak_opsi_tengah("    2. Masuk Sebagai Pembeli (Customer)");
        cetak_opsi_tengah("    0. Keluar Aplikasi");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("--------------------------------------------");
        cout << RESET;
        
        cetak_input_tengah("    Pilihan Role: ");
        cin >> pilihan_role;

        switch (pilihan_role) {
            case 1:
                menuadmin(daftar_menu, &jumlah_barang, MAKS_DATA);
                break;
            case 2:
                menu_pembeli(daftar_menu, jumlah_barang, totalPoin, inventori, jumlahDiTas);
                break;
            case 0:
                cls();
                cout << "\n\n\n\n";
                
                // RENDER IMPERIAL AQUILA SHUTDOWN SEQUENCE
                cout << BOLD << KUNING;
                cetakTengah("       ___        ___       ");
                cetakTengah("      / _ \\ /\\ / _ \\      ");
                cetakTengah("     | | \\ V  V / | |     ");
                cetakTengah("     | |_|\\    /|_| |     ");
                cetakTengah("      \\___/|  |\\___/      ");
                cetakTengah("           \\__/           ");
                cout << "\n";
                
                cout << BOLD << MERAH;
                cetakTengah("\"Only in death does duty end.\"");
                cout << RESET << "\n";
                
                cout << BOLD << NEON_PURPLE;
                cetakTengah("============================================");
                cout << CYBER_CYAN;
                cetakTengah("SYSTEM SHUTDOWN INITIATED");
                cout << BOLD << NEON_PURPLE;
                cetakTengah("============================================");
                cout << RESET;
                
                cetakTengah(KUNING "- The Emperor Protects -" RESET);
                cout << "\n\n\n";
                break;
            default:
                cetak_opsi_tengah(MERAH "    [!] Pilihan role tidak valid! Silakan coba lagi." RESET);
                pause();
        }
    } while (pilihan_role != 0);

    return 0;
}