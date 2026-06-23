// ===================================================================================
// 1. LIBRARIES & OS INCLUDES (Cross-Platform Dynamic Width)
// ===================================================================================
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>
#include <fstream>
#include <limits>
#include <ctime>
#include <cstdlib>

// Deteksi OS untuk kompatibilitas Program
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

// Data Dummy Undian
Hadiah hadiahR[50] = {{"Voucher Diskon 5%", "R"}, {"Permen", "R"}, {"Stiker Toko", "R"}};
Hadiah hadiahSR[50] = {{"Tumbler", "SR"}, {"Kopi Ireng", "SR"}};
Hadiah hadiahSSR[50] = {{"Earphone", "SSR"}};

int stokR = 3;   
int stokSR = 2;  
int stokSSR = 1; 

// ===================================================================================
// 5. PROTOTIPE FUNGSI
// ===================================================================================
void cls();
void cetakTengah(string teks);
void cetak_opsi_tengah(string teks_menu);
void cetak_input_tengah(string teks_menu);
void pause();
void cetak_banner();
int ambil_input_angka(string teks_panduan);
string ambil_input_teks(string teks_panduan, bool boleh_kosong);

void grafik_stok(Barang arr[], int jumlah);
void cetak_invoice_digital(string nama_barang, int harga_satuan, int jumlah_beli, int total_poin_didapat);
void simpan_stok_ke_file(Barang daftar[], int jumlah);
void muat_stok_dari_file(Barang daftar[], int &jumlah);

void editBarang(Barang daftarBarang[], int &jumlahBarang);
void hapusBarang(Barang daftarBarang[], int &jumlahBarang);

void prosesTransaksi(int totalHarga);
void lihatPoin();

void lihatInventori(Hadiah tas[], int jumlah);
void menuGacha(int* poinUser, Hadiah tas[], int* isiTas);
void tambah_hadiah_admin(int* batasR, int* batasSR, int* batasSSR);

void beliBarang(Barang arr[], int jumlah);
void menu_pembeli(Barang daftar_menu[], int jumlah_barang, int &total_poin, Hadiah inventori_hadiah[], int &jumlah_di_tas);

bool mainkan_game_maneki_catch();

string proses_enkripsi_aman(string data_asli);
string proses_dekripsi_aman(string data_terenkripsi);
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
// 6. MODUL: utilitas.cpp (Team)
// ===================================================================================
void cls() {
    cout << "\033[2J\033[H";
}

void cetakTengah(string teks) {
    int lebar_total = 122;
    int panjang_teks = teks.length();
    if (panjang_teks >= lebar_total) {
        cout << teks << endl;
        return;
    }
    int sisa_spasi = lebar_total - panjang_teks;
    int spasi_kiri = sisa_spasi / 2;
    for (int i = 0; i < spasi_kiri; i++) {
        cout << " ";
    }
    cout << teks << endl;
}

void cetak_opsi_tengah(string teks_menu) {
    int lebar_terminal = 122;
    int lebar_konten = 48;
    int s = (lebar_terminal - lebar_konten) / 2;
    string pad(s > 0 ? s : 0, ' ');
    cout << pad << teks_menu << "\n";
}

void cetak_input_tengah(string teks_menu) {
    int lebar_terminal = 122;
    int lebar_konten = 48; 
    int s = (lebar_terminal - lebar_konten) / 2;
    string pad(s > 0 ? s : 0, ' ');
    cout << pad << teks_menu;
}

void pause() {
    cetak_input_tengah("\nTekan ENTER untuk melanjutkan...");
    cin.get();
}
string sapaan_waktu() {
    time_t waktu_sekarang = time(0);
    tm *waktu_lokal = localtime(&waktu_sekarang);
    int jam = waktu_lokal->tm_hour;

    if (jam >= 5 && jam < 11) return "Selamat Pagi";
    else if (jam >= 11 && jam < 15) return "Selamat Siang";
    else if (jam >= 15 && jam < 18) return "Selamat Sore";
    else return "Selamat Malam";
}
void cetak_ketik(string teks, int delay_ms = 15) {
    int lebar_terminal = 122;
    int s = (lebar_terminal - teks.length()) / 2;
    string pad(s > 0 ? s : 0, ' ');
    
    cout << pad;
    for (char c : teks) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
    }
    cout << "\n";
}
void cetak_banner() {
    int lebar_terminal = 122;
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

int ambil_input_angka(string teks_panduan) {
    int input_user;
    while (true) {
        cetak_input_tengah(teks_panduan);
        if (cin >> input_user) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return input_user;
        } else {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Input harus berupa angka murni!" RESET);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            cout << "\033[5A\033[J"; 
        }
    }
}

string ambil_input_teks(string teks_panduan, bool boleh_kosong) {
    string input_user;
    while (true) {
        cetak_input_tengah(teks_panduan);
        getline(cin >> ws, input_user); 
        if (!input_user.empty() && input_user.back() == '\r') { input_user.pop_back(); }

        if (!boleh_kosong && (input_user.empty() || input_user == " " || input_user == "\t")) {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Input ini tidak boleh kosong atau spasi saja!" RESET);
            pause();
            cout << "\033[5A\033[J"; 
            continue;
        }
        return input_user;
    }
}

void grafik_stok(Barang arr[], int jumlah) {
    while (true) {
        cls();
        cetak_banner();
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << BOLD << NEON_PINK;
        cetakTengah("MONITORING GRAFIK STOK KAFE (LIVE)");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << RESET << "\n";

        if (jumlah == 0) {
            cout << BOLD << KUNING;
            cetak_opsi_tengah("[!] Belum ada data barang untuk dibuatkan grafik.");
            cout << RESET;
            pause();
            return;
        }
        
        int lebar_terminal = 122;
        int lebar_grafik = 60;
        int s_grafik = (lebar_terminal - lebar_grafik) / 2;
        string pad_grafik(s_grafik > 0 ? s_grafik : 0, ' ');
        
        bool ada_kritis = false;

        for (int i = 0; i < jumlah; i++) {
            string warna_batang = (arr[i].stok <= 5) ? string(BOLD) + MERAH : string(HIJAU);

            cout << pad_grafik << BOLD << CYAN << left << setw(15) << arr[i].nama << RESET 
                 << " : " << BOLD << NEON_PURPLE << "[" << RESET;
            
            int panjangBatang = arr[i].stok / 2;
            if (panjangBatang > 25) panjangBatang = 25;
            if (arr[i].stok > 0 && panjangBatang == 0) panjangBatang = 1;

            for (int j = 0; j < panjangBatang; j++) {
                cout << warna_batang << "█" << RESET;
            }
            
            int sisaSpasi = 25 - panjangBatang;
            for (int j = 0; j < sisaSpasi; j++) {
                cout << " ";
            }
            
            cout << BOLD << NEON_PURPLE << "] " << RESET;
            cout << BOLD << KUNING << arr[i].stok << " item" << RESET;
            
            if (arr[i].stok <= 5) {
                cout << BOLD << MERAH << "  <-- [KRITIS!]" << RESET;
                ada_kritis = true;
            }
            cout << "\n";
        }
        cout << "\n";
        
        cout << BOLD << NEON_PURPLE;
        cetakTengah("-----------------------------------------------------");
        cout << RESET;
        
        cetak_input_tengah("Keterangan: 1 blok '");
        cout << BOLD << HIJAU "█" << RESET << "' = 2 Stok Normal | '";
        cout << BOLD << MERAH "█" << RESET << "' = Stok Kritis\n";

        if (ada_kritis) {
            cout << "\n";
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << BOLD << MERAH;
            cetak_opsi_tengah("[!] SISTEM MENDETEKSI STOK KRITIS (<= 5)");
            cout << BOLD << CYBER_CYAN;
            cetak_opsi_tengah("    1. Jalankan Protokol Refill Stok");
            cout << BOLD << MERAH;
            cetak_opsi_tengah("    0. Kembali ke Menu Admin");
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << RESET;

            int pilihan = ambil_input_angka("    Pilihan: ");

            if (pilihan == 1) {
                cout << BOLD << CYBER_CYAN;
                string nama_refill = ambil_input_teks("Masukkan Nama Barang yang akan di-refill: ", false);
                cout << RESET;

                int index_ketemu = -1;
                for (int i = 0; i < jumlah; i++) {
                    if (arr[i].nama == nama_refill) {
                        index_ketemu = i;
                        break;
                    }
                }

                if (index_ketemu != -1) {
                    cout << BOLD << KUNING;
                    int jumlah_tambah = ambil_input_angka("Masukkan jumlah refill     : ");
                    cout << RESET;

                    if (jumlah_tambah > 0) {
                        arr[index_ketemu].stok += jumlah_tambah;
                        simpan_stok_ke_file(arr, jumlah);
                        
                        cout << BOLD << NEON_PURPLE;
                        cetakTengah("-----------------------------------------------------");
                        cout << BOLD << HIJAU;
                        cetak_opsi_tengah("[✓] Stok berhasil diperbarui! Sisa stok: " + to_string(arr[index_ketemu].stok));
                        cout << BOLD << NEON_PURPLE;
                        cetakTengah("-----------------------------------------------------");
                        cout << RESET;
                        pause();
                    } else {
                        cout << BOLD << NEON_PURPLE;
                        cetakTengah("-----------------------------------------------------");
                        cout << BOLD << MERAH;
                        cetak_opsi_tengah("[!] Error: Jumlah refill harus lebih besar dari 0!");
                        cout << BOLD << NEON_PURPLE;
                        cetakTengah("-----------------------------------------------------");
                        cout << RESET;
                        pause();
                    }
                } else {
                    cout << BOLD << NEON_PURPLE;
                    cetakTengah("-----------------------------------------------------");
                    cout << BOLD << MERAH;
                    cetak_opsi_tengah("[!] Akses Ditolak: ID Barang tidak ditemukan.");
                    cout << BOLD << NEON_PURPLE;
                    cetakTengah("-----------------------------------------------------");
                    cout << RESET;
                    pause();
                }
            } else if (pilihan == 0) {
                break;
            } else {
                cout << BOLD << MERAH;
                cetak_opsi_tengah("\n[!] Pilihan tidak valid!");
                cout << RESET;
                pause();
            }
        } else {
            break;
        }
    }
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

    cout << "\a" << BOLD << KUNING;
    cetakTengah("*klontoooong*");
    cout << RESET; 
    
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << BOLD << NEON_PINK;
    cetakTengah("SMART CAFE - NOTA PEMBAYARAN DIGITAL");
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    
    string s_tanggal = "Tanggal Nota      : " + to_string(tanggal_aktif) + "/" + to_string(bulan_aktif) + "/" + to_string(tahun_aktif);
    string s_status  = "Status            : LUNAS";
    
    cout << CYAN;
    cetakTengah(s_tanggal);
    cout << HIJAU;
    cetakTengah(s_status);
    
    cout << BOLD << NEON_PURPLE;
    cetakTengah("-----------------------------------------------------");
    cout << BOLD << CYBER_CYAN;
    cetakTengah("Item                     Qty                 Total");
    cout << BOLD << NEON_PURPLE;
    cetakTengah("-----------------------------------------------------");
    cout << RESET;
    
    string s_item = nama_barang;
    if (s_item.length() < 25) s_item.append(25 - s_item.length(), ' ');
    string s_qty = to_string(jumlah_beli);
    if (s_qty.length() < 7) s_qty.append(7 - s_qty.length(), ' ');
    string s_harga = "Rp " + to_string((int)sub_total);
    if (s_harga.length() < 21) s_harga.insert(0, 21 - s_harga.length(), ' ');
    
    cetakTengah(s_item + s_qty + s_harga);
    
    cout << BOLD << NEON_PURPLE;
    cetakTengah("-----------------------------------------------------");
    
    string b_sub = "Subtotal";
    if (b_sub.length() < 35) b_sub.append(35 - b_sub.length(), ' ');
    string v_sub = "Rp " + to_string((int)sub_total);
    if (v_sub.length() < 18) v_sub.insert(0, 18 - v_sub.length(), ' ');
    cout << RESET;
    cetakTengah(b_sub + v_sub);

    string b_pajak = "Pajak Restoran (11%)";
    if (b_pajak.length() < 35) b_pajak.append(35 - b_pajak.length(), ' ');
    string v_pajak = "Rp " + to_string((int)kalkulasi_pajak);
    if (v_pajak.length() < 18) v_pajak.insert(0, 18 - v_pajak.length(), ' ');
    cout << KUNING; // Warna kuning untuk biaya tambahan
    cetakTengah(b_pajak + v_pajak);

    string b_servis = "Biaya Layanan/Service";
    if (b_servis.length() < 35) b_servis.append(35 - b_servis.length(), ' ');
    string v_servis = "Rp " + to_string((int)biaya_servis);
    if (v_servis.length() < 18) v_servis.insert(0, 18 - v_servis.length(), ' ');
    cetakTengah(b_servis + v_servis);
    
    cout << BOLD << NEON_PURPLE;
    cetakTengah("-----------------------------------------------------");
    
    string b_total = "TOTAL PEMBAYARAN";
    if (b_total.length() < 35) b_total.append(35 - b_total.length(), ' ');
    string v_total = "Rp " + to_string((int)total_akhir);
    if (v_total.length() < 18) v_total.insert(0, 18 - v_total.length(), ' ');
    cout << BOLD << HIJAU; // Total akhir berwarna hijau terang
    cetakTengah(b_total + v_total);
    
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    
    string s_poin = "[+] Poin Loyalty yang didapat dari item ini: " + to_string(total_poin_didapat) + " Poin";
    cout << BOLD << KUNING;
    cetakTengah(s_poin);
    
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << BOLD << HOT_MAGENTA;
    cetakTengah("Terima kasih atas kunjungan Anda!");
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << RESET;
}

void simpan_stok_ke_file(Barang daftar[], int jumlah) {
    ofstream file("stok_barang.txt");
    if (file.is_open()) {
        for (int i = 0; i < jumlah; i++) {
            file << daftar[i].id << "," << daftar[i].nama << "," << daftar[i].harga << "," << daftar[i].stok << "," << daftar[i].penambah << "\n";
        }
        file.close();
    }
}

void muat_stok_dari_file(Barang daftar[], int &jumlah) {
    ifstream file("stok_barang.txt");
    if (!file.is_open()) return; 
    
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
// 7. MODUL: AdminBagian2cpp.cpp (Hari)
// ===================================================================================
void editBarang(Barang daftarBarang[], int &jumlahBarang) {
    string idCari;
    bool ditemukan = false;
    idCari = ambil_input_teks("\nMasukkan ID Barang yang ingin diedit : ", false);

    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].id == idCari) {
            Barang *ptr = &daftarBarang[i];
            cetak_opsi_tengah("\nID Barang ditemukan!");
            
            ptr->nama = ambil_input_teks("Masukkan Nama Baru  : ", false);
            ptr->harga = ambil_input_angka("Masukkan Harga Baru : ");
            ptr->stok = ambil_input_angka("Masukkan Stok Baru  : ");

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
        cetak_opsi_tengah("\nID Barang ditemukan!");
        cetak_opsi_tengah("Barang berhasil dihapus dari daftar.");
        pause();
    } else {
        cetak_opsi_tengah("\n[!] ID Barang tidak ditemukan!");
        pause();
    }
}


// ===================================================================================
// 8. MODUL: poin.cpp (Krisna)
// ===================================================================================
void prosesTransaksi(int totalHarga){
    int dapatPoin = totalHarga / 10000;
    totalPoin += dapatPoin;

    if (jumlahTransaksi < 100) {
        transaksi[jumlahTransaksi] = totalHarga;
        jumlahTransaksi++;
    } else {
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
}

void lihatPoin() {
    cetakTengah("============================================");
    cetakTengah("TOTAL POIN");
    cetakTengah("============================================");
    cetak_input_tengah("Total Poin Anda : ");
    cout << totalPoin << " poin\n";
    cetakTengah("--------------------------------------------");
}


// ===================================================================================
// 9. MODUL: undian.cpp (Rizka)
// ===================================================================================
void lihatInventori(Hadiah tas[], int jumlah) {
    cls();
    cetak_banner();
    
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << BOLD << NEON_PINK;
    cetakTengah("INVENTORI HADIAH ANDA");
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << RESET << "\n";
    if(jumlah == 0) {
        cout << BOLD << KUNING;
        cetak_opsi_tengah("[!] Belum ada hadiah di dalam tas Anda.");
        cout << RESET;
        return;
    }
    int total_baris = (jumlah + 1) / 2;
    int lebar_terminal = 122; 
    int lebar_konten = 70; 
    int s = (lebar_terminal - lebar_konten) / 2;
    string pad(s > 0 ? s : 0, ' ');
    for (int i = 0; i < total_baris; i++) {
        string warna_kiri = (tas[i].rarity == "SSR") ? string(BOLD) + KUNING : 
                            (tas[i].rarity == "SR") ? string(BOLD) + NEON_PURPLE : string(BOLD) + HIJAU;
        
        string item_kiri = to_string(i + 1) + ". " + tas[i].namaHadiah + " (" + tas[i].rarity + ")";
        
        cout << pad << warna_kiri << left << setw(35) << item_kiri << RESET;

        int idx_kanan = i + total_baris;
        if (idx_kanan < jumlah) {
            string warna_kanan = (tas[idx_kanan].rarity == "SSR") ? string(BOLD) + KUNING : 
                                 (tas[idx_kanan].rarity == "SR") ? string(BOLD) + NEON_PURPLE : string(BOLD) + HIJAU;
            
            string item_kanan = to_string(idx_kanan + 1) + ". " + tas[idx_kanan].namaHadiah + " (" + tas[idx_kanan].rarity + ")";
            cout << warna_kanan << left << item_kanan << RESET;
        }
        cout << "\n";
    }   
    cout << "\n";
    cout << BOLD << NEON_PURPLE;
    cetakTengah("-----------------------------------------------------");
    cout << BOLD << CYBER_CYAN;
    cetak_input_tengah("Total Item: ");
    cout << BOLD << KUNING << jumlah << " Hadiah\n" << RESET;
}

void menuGacha(int* poinUser, Hadiah tas[], int* isiTas){
    int pilihanMenu;
    int jumlahUndi = 0;     
    while(true){
        cls();
        cetak_banner();
        
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << BOLD << NEON_PINK;
        cetakTengah("==== TERMINAL UNDIAN GACHA ====");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << RESET << "\n";
        
        cetak_input_tengah("Poin Anda: ");
        cout << BOLD << KUNING << *poinUser << " Poin\n" << RESET;
        
        cout << BOLD << CYAN;
        cetak_opsi_tengah("1. Undi x1 (1 Poin)");
        cetak_opsi_tengah("2. Undi x5 (5 Poin)");
        cout << BOLD << MERAH;
        cetak_opsi_tengah("0. Keluar");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("-----------------------------------------------------");
        cout << RESET;
        
        pilihanMenu = ambil_input_angka("Pilih: ");
    
        if (pilihanMenu == 1){
            jumlahUndi = 1;
        } else if (pilihanMenu == 2){
            jumlahUndi = 5;
        } else if (pilihanMenu == 0){
            break;
        } else {
            cout << BOLD << MERAH;
            cetak_opsi_tengah("[!] Pilihan salah!");
            cout << RESET;
            pause();
            continue;
        }
        
        if (*poinUser < jumlahUndi){
            cout << BOLD << MERAH;
            cetak_opsi_tengah("[!] Poin tidak cukup!");
            cout << RESET;
            pause();
            continue;
        }
        
        *poinUser -= jumlahUndi;
        
        cout << BOLD << CYBER_CYAN;
        cetak_input_tengah("\n>> MENGUNDI HADIAH");
        for (int i = 0; i < 3; i++) {
            this_thread::sleep_for(chrono::milliseconds(500));
            cout << ".";
            cout.flush();
        }
        cout << RESET << "\n\n";
        
        bool dapatSRatauSSR = false;
        bool animasi_ssr = false;
        string nama_ssr_didapat = "";
        
        for (int i = 1; i <= jumlahUndi; i++) {
            string rarity;
            Hadiah hadiahTerpilih; 
            
            if (jumlahUndi == 5 && i == 5 && !dapatSRatauSSR){
                rarity = "SR";
            } else {
                int angka = (rand() % 100) + 1; 
                if (sisa_buff_draw > 0) {
                    if (angka <= 6) { 
                        rarity = "SSR"; dapatSRatauSSR = true;
                    } else if (angka <= 15) { 
                        rarity = "SR"; dapatSRatauSSR = true;
                    } else {
                        rarity = "R";
                    }
                    sisa_buff_draw--; 
                } else {
                    if (angka == 1) { 
                        rarity = "SSR"; dapatSRatauSSR = true;
                    } else if (angka <= 10) { 
                        rarity = "SR"; dapatSRatauSSR = true;
                    } else { 
                        rarity = "R";
                    }
                }
            }
            if(rarity == "R") {
                int pilih = rand() % stokR; hadiahTerpilih = hadiahR[pilih];
            } else if(rarity == "SR") {
                int pilih = rand() % stokSR; hadiahTerpilih = hadiahSR[pilih]; dapatSRatauSSR = true; 
            } else {
                int pilih = rand() % stokSSR; hadiahTerpilih = hadiahSSR[pilih]; dapatSRatauSSR = true;
                animasi_ssr = true;
                nama_ssr_didapat = hadiahTerpilih.namaHadiah;
            }
            cetak_input_tengah("Undian " + to_string(i) + " : ");
            
            if (hadiahTerpilih.rarity == "R") {
                cout << BOLD << HIJAU << hadiahTerpilih.namaHadiah << " (R)\n" << RESET;
            } else if (hadiahTerpilih.rarity == "SR") {
                cout << BOLD << NEON_PURPLE << hadiahTerpilih.namaHadiah << " (SR)\n" << RESET;
            } else {
                cout << BOLD << KUNING << hadiahTerpilih.namaHadiah << " (SSR)\n" << RESET;
            }
            
            tas[*isiTas] = hadiahTerpilih;
            (*isiTas)++;                   
        }
        if (animasi_ssr) {
            cls();
            
            cout << "\a";
            cout << BOLD << KUNING;
            // Tambahan Animasi
            cout << "\n\n\n";
            cetakTengah("      . * + * . * + * . * + * .      ");
            cetakTengah("     +                     _   +     ");
            cetakTengah("    * /\\____/\\    //     * ");
            cetakTengah("    .       / ^    ^ \\  //      .    ");
            cetakTengah("     +     |  > w <   |//      +     ");
            cetakTengah("    * \\  ___   / /        * ");
            cetakTengah("    .     ___| [$$] |___        .    ");
            cetakTengah("     +   /    \\___/      \\     +     ");
            cetakTengah("    * /  /         \\  \\ \\     * ");
            cetakTengah("    .  (__(___________)__) )    .    ");
            cetakTengah("      . * + * . * + * . * + * .      ");
            cout << "\n";
            
            cout << BOLD << CYBER_CYAN;
            cetakTengah("=====================================================");
            cout << BOLD << NEON_PINK;
            cetakTengah("G A C O O O R R R R R R");
            cout << BOLD << KUNING;
            cetakTengah("Berkat Maneki Neko, Anda mendapatkan item Legendaris:");
            cout << BOLD << NEON_PINK;
            cetakTengah("[[ " + nama_ssr_didapat + " (SSR) ]]");
            cout << BOLD << CYBER_CYAN;
            cetakTengah("=====================================================");
            cout << RESET << "\n";
        }
        
        cout << BOLD << CYBER_CYAN;
        cetak_input_tengah("\nSisa poin: ");
        cout << BOLD << KUNING << *poinUser << "\n" << RESET;
        pause();
    }
}
void tambah_hadiah_admin(int* batasR, int* batasSR, int* batasSSR) {
    cls();
    cetak_banner();
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << BOLD << NEON_PINK;
    cetakTengah("MENU ADMIN - REWARD MANAGER");
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << RESET << "\n";
    
    string namaBaru;
    int pilihanTier;
    
    namaBaru = ambil_input_teks("Masukkan Nama Hadiah Baru: ", false);
    
    cout << BOLD << CYBER_CYAN;
    cetak_opsi_tengah("\nPilih Tingkat Kelangkaan (Rarity Tier):");
    
    cout << BOLD << HIJAU;
    cetak_opsi_tengah("1. R   (Common)");
    cout << BOLD << NEON_PURPLE;
    cetak_opsi_tengah("2. SR  (Rare)");
    cout << BOLD << KUNING;
    cetak_opsi_tengah("3. SSR (Epic/Legendary)");
    cout << RESET;
    
    pilihanTier = ambil_input_angka("Pilihan: ");
    
    if (pilihanTier == 1) {
        if (*batasR >= 50) {
            cout << BOLD << MERAH;
            cetak_opsi_tengah("\n[!] Kapasitas inventori hadiah R penuh!");
            cout << RESET;
            pause(); return;
        }
        hadiahR[*batasR].namaHadiah = namaBaru; hadiahR[*batasR].rarity = "R"; (*batasR)++;
        cout << BOLD << HIJAU;
        cetak_opsi_tengah("\n[✓] Hadiah \"" + namaBaru + "\" berhasil ditambahkan ke Tier R!");
        cout << RESET;
        
    } else if (pilihanTier == 2) {
        if (*batasSR >= 50) {
            cout << BOLD << MERAH;
            cetak_opsi_tengah("\n[!] Kapasitas inventori hadiah SR penuh!");
            cout << RESET;
            pause(); return;
        }
        hadiahSR[*batasSR].namaHadiah = namaBaru; hadiahSR[*batasSR].rarity = "SR"; (*batasSR)++;
        cout << BOLD << NEON_PURPLE;
        cetak_opsi_tengah("\n[✓] Hadiah \"" + namaBaru + "\" berhasil ditambahkan ke Tier SR!");
        cout << RESET;
        
    } else if (pilihanTier == 3) {
        if (*batasSSR >= 50) {
            cout << BOLD << MERAH;
            cetak_opsi_tengah("\n[!] Kapasitas inventori hadiah SSR penuh!");
            cout << RESET;
            pause(); return;
        }
        hadiahSSR[*batasSSR].namaHadiah = namaBaru; hadiahSSR[*batasSSR].rarity = "SSR"; (*batasSSR)++;
        cout << BOLD << KUNING;
        cetak_opsi_tengah("\n[✓] Hadiah \"" + namaBaru + "\" berhasil ditambahkan ke Tier SSR!");
        cout << RESET;
        
    } else {
        cout << BOLD << MERAH;
        cetak_opsi_tengah("\n[!] Pilihan tier tidak valid!");
        cout << RESET;
    }
    pause();
}


// ===================================================================================
// 10. MODUL: admin 1.cpp (Widya ft Arizona)
// ===================================================================================
string proses_enkripsi_aman(string data_asli) {
    char kunci = 'C';
    string hasil = "";
    for (size_t i = 0; i < data_asli.length(); i++) {
        int cipher = data_asli[i] ^ kunci;
        hasil += to_string(cipher) + " "; 
    }
    return hasil;
}

string proses_dekripsi_aman(string data_terenkripsi) {
    char kunci = 'C';
    string hasil = "";
    string temp_angka = "";
    for (size_t i = 0; i < data_terenkripsi.length(); i++) {
        if (data_terenkripsi[i] == ' ') {
            if (!temp_angka.empty()) {
                int cipher = stoi(temp_angka);
                char asli = cipher ^ kunci;
                hasil += asli;
                temp_angka = "";
            }
        } else { temp_angka += data_terenkripsi[i]; }
    }
    return hasil;
}

void simpan_txt(string nama, string nim) {
    ofstream file_atmint("data_atmint.txt", ios::app);
    if (file_atmint.is_open()) {
        file_atmint << proses_enkripsi_aman(nama) << "\n";
        file_atmint << proses_enkripsi_aman(nim) << "\n";
        file_atmint.close();
    }
}

bool cek_apakah_atmint_ada(string nama_cari, string nim_cari) {
    ifstream file_atmint("data_atmint.txt");
    if (file_atmint.is_open()) {
        string nama_file_terenkripsi, nim_file_terenkripsi;
        while (getline(file_atmint, nama_file_terenkripsi) && getline(file_atmint, nim_file_terenkripsi)) {
            if (!nama_file_terenkripsi.empty() && nama_file_terenkripsi.back() == '\r') nama_file_terenkripsi.pop_back();
            if (!nim_file_terenkripsi.empty() && nim_file_terenkripsi.back() == '\r') nim_file_terenkripsi.pop_back();
            if (proses_dekripsi_aman(nama_file_terenkripsi) == nama_cari && proses_dekripsi_aman(nim_file_terenkripsi) == nim_cari) {
                file_atmint.close(); return true;
            }
        }
        file_atmint.close();
    }
    return false;
}

bool cek_duplikat_registrasi(string nama_daftar, string nim_daftar) {
    ifstream file_atmint("data_atmint.txt");
    if (file_atmint.is_open()) {
        string nama_file_terenkripsi, nim_file_terenkripsi;
        while (getline(file_atmint, nama_file_terenkripsi) && getline(file_atmint, nim_file_terenkripsi)) {
            if (!nama_file_terenkripsi.empty() && nama_file_terenkripsi.back() == '\r') nama_file_terenkripsi.pop_back();
            if (!nim_file_terenkripsi.empty() && nim_file_terenkripsi.back() == '\r') nim_file_terenkripsi.pop_back();
            if (proses_dekripsi_aman(nama_file_terenkripsi) == nama_daftar || proses_dekripsi_aman(nim_file_terenkripsi) == nim_daftar) {
                file_atmint.close(); return true;
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
            file_atmint.close(); return false;
        }
        file_atmint.close();
    }
    return true;
}

bool validasi_nim_atmint(string nim) {
    if (nim.length() != 11) return false;
    if (nim.substr(0, 5) != "F1D02") return false;
    for (int i = 5; i < 11; i++) {
        if (nim[i] < '0' || nim[i] > '9') return false;
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
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << BOLD << NEON_PINK;
        cetakTengah("SECURITY VERIFICATION (CAPTCHA)");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << RESET << "\n";
        
        cout << BOLD << CYBER_CYAN;
        cetak_opsi_tengah("Selesaikan operasi matematika berikut untuk verifikasi:");
        cout << RESET;
        
        cout << BOLD << KUNING;
        jawaban_user = ambil_input_angka("Berapakah hasil dari " + to_string(a) + " + " + to_string(b) + " = ");
        cout << RESET;

        if (jawaban_user == hasil_benar) {
            return true;
        } else {
            salah_hitung++;
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << BOLD << MERAH;
            cetak_opsi_tengah("[!] AKSES DITOLAK: Kalkulasi salah!");
            cout << BOLD << KUNING;
            cetak_opsi_tengah("Peringatan: Toleransi kesalahan " + to_string(salah_hitung) + "/3");
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << RESET;
            
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
        
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << BOLD << NEON_PINK;
        cetakTengah("ADMIN GATE AUTHENTICATION SYSTEM");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << RESET;
        
        cout << BOLD << CYBER_CYAN;
        cetak_opsi_tengah("     1. Sign In (Masuk Log)");
        cetak_opsi_tengah("     2. Sign Up (Daftar Akun Admin Baru)");
        cout << BOLD << MERAH;
        cetak_opsi_tengah("     0. Kembali");
        
        cout << BOLD << NEON_PURPLE;
        cetakTengah("-----------------------------------------------------");
        cout << RESET;
        
        opsi_auth = ambil_input_angka("    Pilihan Anda: ");

        if (opsi_auth == 0) return false;
        if (opsi_auth != 1 && opsi_auth != 2) {
            cout << BOLD << MERAH;
            cetak_opsi_tengah("\n[!] Pilihan tidak valid!");
            cout << RESET;
            pause(); return false;
        }
    } else {
        opsi_auth = 2;
    }

    if (opsi_auth == 2) {
        while (true) {
            cls();
            cetak_banner();
            cout << BOLD << NEON_PURPLE;
            cetakTengah("=====================================================");
            cout << BOLD << NEON_PINK;
            cetakTengah("REGISTRASI AKUN ADMIN BARU (SIGN UP)");
            cout << BOLD << NEON_PURPLE;
            cetakTengah("=====================================================");
            cout << RESET;
            
            cout << BOLD << CYBER_CYAN;
            nama_data = ambil_input_teks("Daftarkan Nama Admin  (0 untuk keluar): ", false);
            cout << RESET;
            if (nama_data == "0"){
                return false;
            }
            
            cout << BOLD << CYBER_CYAN;
            nim_data = ambil_input_teks("Daftarkan NIM Admin (0 untuk keluar): ", false); 
            cout << RESET;
            if (nim_data == "0"){
                return false;
            }
            
            if (!validasi_nim_atmint(nim_data)) {
                cout << BOLD << MERAH;
                cetak_opsi_tengah("\n[!] REGISTRASI GAGAL: NIM harus 11 digit dan diawali 'F1D02'!");
                cout << RESET;
                pause(); continue;
            }

            if (cek_duplikat_registrasi(nama_data, nim_data)) {
                cout << BOLD << MERAH;
                cetak_opsi_tengah("\n[!] REGISTRASI GAGAL: Nama atau NIM sudah terdaftar oleh Admin lain!");
                cout << RESET;
                pause(); continue;
            }

            if (!jalankan_captcha_simpel()) {
                cls();
                cetak_banner();
                cout << BOLD << NEON_PURPLE;
                cetakTengah("=====================================================");
                cout << BOLD << MERAH;
                cetak_opsi_tengah("\n[!] AKSES DIKUNCI: Anda salah mengisi CAPTCHA sebanyak 3 kali!");
                cout << BOLD << NEON_PURPLE;
                cetakTengah("=====================================================");
                cout << RESET;
                pause(); return false;
            }

            simpan_txt(nama_data, nim_data);
            cls();
            cetak_banner();
            cout << BOLD << NEON_PURPLE;
            cetakTengah("=====================================================");
            cout << BOLD << HIJAU;
            cetak_opsi_tengah("\n[✓] SIGN UP BERHASIL! Data tersimpan.");
            cout << BOLD << NEON_PURPLE;
            cetakTengah("=====================================================");
            cout << RESET;
            pause(); break;
        }
    }

    while (opsi_auth == 1) {
        string nama_masuk, nim_masuk;
        cls();
        cetak_banner();
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << BOLD << NEON_PINK;
        cetakTengah("SISTEM MASUK ADMIN (SIGN IN)");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << RESET;
        
        cout << BOLD << CYBER_CYAN;
        nama_masuk = ambil_input_teks("Masukkan Nama Anda (0 untuk batal) : ", false);
        cout << RESET;
        if (nama_masuk == "0"){
            return false;
        }
        
        cout << BOLD << CYBER_CYAN;
        nim_masuk = ambil_input_teks("Masukkan NIM Anda  (0 untuk batal): ", false);
        cout << RESET;
        if (nim_masuk == "0"){
            return false;
        }
        else if (!cek_apakah_atmint_ada(nama_masuk, nim_masuk)) {
            cls();
            cetak_banner();
            cout << BOLD << NEON_PURPLE;
            cetakTengah("=====================================================");
            cout << BOLD << MERAH;
            cetak_opsi_tengah("\n[!] AKSES DITOLAK: Nama atau NIM tidak cocok dengan akun terdaftar manapun!");
            cout << BOLD << NEON_PURPLE;
            cetakTengah("=====================================================");
            cout << RESET;
            pause(); continue;
        }

        nama_admin_aktif = nama_masuk;
        cls();
        cetak_banner();
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        string sapaan = sapaan_waktu() + ", Admin " + nama_admin_aktif + "!";
        cout << BOLD << HIJAU; 
        cetakTengah(sapaan); 
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << RESET << "\n";
        pause();
        break;
    }
    return true;
}

void tambahmenubaru(Barang arr[], int *jumlah, int kapasitas) {
    if (*jumlah >= kapasitas) {
        cls();
        cetak_banner();
        cout << BOLD << MERAH;
        cetak_opsi_tengah("\n[!] Akses Ditolak: Array penuh! Tidak bisa menambah menu baru.");
        cout << RESET;
        pause();
        return;
    }

    string id_input, nama_input;
    int harga_input, stok_input;
    
    while (true) {
        cls();
        cetak_banner();
        
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << BOLD << NEON_PINK;
        cetakTengah("TAMBAH MENU BARU");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << RESET << "\n";

        cout << BOLD << CYBER_CYAN;
        id_input = ambil_input_teks("Masukkan ID Menu   : ", false);
        cout << RESET;

        if (id_input == "0") {
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << BOLD << MERAH;
            cetak_opsi_tengah("[!] Error: ID \"0\" tidak boleh digunakan!");
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << RESET;
            pause(); continue;
        }

        bool id_duplikat = false;
        for (int i = 0; i < *jumlah; i++) {
            if (arr[i].id == id_input) {
                id_duplikat = true; break;
            }
        }

        if (id_duplikat) {
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << BOLD << MERAH;
            cetak_opsi_tengah("[!] Error: ID Menu sudah terdaftar sebelumnya!");
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << RESET;
            pause(); continue;
        }

        cout << BOLD << CYBER_CYAN;
        nama_input = ambil_input_teks("Masukkan Nama Menu : ", false);
        cout << RESET;
        
        cout << BOLD << KUNING;
        harga_input = ambil_input_angka("Masukkan Harga     : Rp ");
        cout << RESET;
        
        if (harga_input <= 0) {
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << BOLD << MERAH;
            cetak_opsi_tengah("[!] Error: Harga harus lebih besar dari 0!");
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << RESET;
            pause(); continue;
        }

        cout << BOLD << KUNING;
        stok_input = ambil_input_angka("Masukkan Stok      : ");
        cout << RESET;

        if (stok_input < 0) {
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << BOLD << MERAH;
            cetak_opsi_tengah("[!] Error: Stok tidak boleh bernilai negatif!");
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << RESET;
            pause(); continue;
        }

        arr[*jumlah].id = id_input;
        arr[*jumlah].nama = nama_input;
        arr[*jumlah].harga = harga_input;
        arr[*jumlah].stok = stok_input;
        arr[*jumlah].penambah = nama_admin_aktif;
        (*jumlah)++;

        simpan_stok_ke_file(arr, *jumlah);

        cout << BOLD << NEON_PURPLE;
        cetakTengah("-----------------------------------------------------");
        cout << BOLD << HIJAU;
        cetak_opsi_tengah("[✓] Menu berhasil ditambahkan!");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("-----------------------------------------------------");
        cout << RESET;
        pause(); break;
    }
}

void lihatsemuamenu(Barang arr[], int jumlah) {
    cls();
    cetak_banner();
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << BOLD << NEON_PINK;
    cetakTengah("DAFTAR SEMUA MENU KAFE");
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << RESET << "\n";

    if (jumlah == 0) {
        cout << BOLD << KUNING;
        cetak_opsi_tengah("[!] Belum ada menu yang tersedia.");
        cout << RESET;
        return;
    }
    
    int lebar_terminal = 122;
    int lebar_tabel = 69;
    int s_tabel = (lebar_terminal - lebar_tabel) / 2;
    string pad(s_tabel > 0 ? s_tabel : 0, ' ');
    
    cout << pad << BOLD << CYBER_CYAN 
         << left << setw(6)  << "ID" 
         << setw(25) << "Nama Menu" 
         << setw(15) << "Harga (Rp)" 
         << setw(8)  << "Stok" 
         << setw(15) << "Penambah" << RESET << "\n";
         
    cout << pad << BOLD << NEON_PURPLE << string(69, '-') << RESET << "\n";
    
    for (int i = 0; i < jumlah; i++) {
        string warna_stok = (arr[i].stok <= 5) ? string(BOLD) + MERAH : string(RESET) + CYAN;
        
        cout << pad 
             << BOLD << KUNING << left << setw(6)  << arr[i].id             
             << RESET << CYAN << setw(25) << arr[i].nama                    
             << BOLD << HIJAU << setw(15) << fixed << setprecision(0) << arr[i].harga 
             << warna_stok << setw(8)  << arr[i].stok                       
             << BOLD << NEON_PURPLE << setw(15) << arr[i].penambah          
             << RESET << "\n";
    }

    cout << pad << BOLD << NEON_PURPLE << string(69, '-') << RESET << "\n";
    cout << pad << BOLD << CYBER_CYAN << "Total menu: " 
         << BOLD << KUNING << jumlah << " item\n" << RESET;
}

void menuadmin(Barang arr[], int *jumlah, int kapasitas) {
    if (!proses_autentikasi_atmint()) {
        return; 
    }
    int pilihan;
    do {
        cls();
        cetak_banner();
        
        string sapaan = sapaan_waktu() + ", Admin " + nama_admin_aktif + "!";
        cout << BOLD << HIJAU;
        cetakTengah(sapaan);
        cout << RESET << "\n";
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << BOLD << NEON_PINK;
        cetakTengah("MENU UTAMA ADMIN MANAGEMENT");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << RESET;
        
        cout << BOLD << CYBER_CYAN;
        cetak_opsi_tengah("     1. Tambah Menu Baru");
        cetak_opsi_tengah("     2. Lihat Semua Menu");
        cetak_opsi_tengah("     3. Edit Data Barang");
        cetak_opsi_tengah("     4. Hapus Data Barang");
        cetak_opsi_tengah("     5. Lihat Grafik Stok Visual");
        cetak_opsi_tengah("     6. Kelola & Tambah Hadiah Gacha");
        
        cout << BOLD << MERAH;
        cetak_opsi_tengah("     0. Kembali ke Role Selection");
        
        cout << BOLD << NEON_PURPLE;
        cetakTengah("-----------------------------------------------------");
        cout << RESET;
        
        pilihan = ambil_input_angka("    Pilihan: ");
        
        switch (pilihan) {
            case 1: tambahmenubaru(arr, jumlah, kapasitas); break;
            case 2: lihatsemuamenu(arr, *jumlah); pause(); break;
            case 3: editBarang(daftar_menu, jumlah_barang); simpan_stok_ke_file(arr, *jumlah); break;
            case 4: hapusBarang(daftar_menu, jumlah_barang); simpan_stok_ke_file(arr, *jumlah); break;
            case 5: grafik_stok(arr, *jumlah); pause(); break;
            case 6: tambah_hadiah_admin(&stokR, &stokSR, &stokSSR); break;
            case 0: 
                cout << BOLD << HIJAU;
                cetak_opsi_tengah("\n[✓] Logging out... Kembali ke menu utama.");
                cout << RESET;
                pause(); 
                break;
            default: 
                cout << BOLD << MERAH;
                cetak_opsi_tengah("\n[!] Protokol ditolak: Pilihan tidak valid!");
                cout << RESET;
                pause();
        }
    } while (pilihan != 0);
}
// ===================================================================================
// 11. MODUL: minigame.cpp (Arizona)
// ===================================================================================
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
                skor_koin++; kecepatan -= 18; posisi_koin = 0; 
            } else {
                nyawa--; posisi_koin = 0;
            }
        }
        posisi_koin++;
        if (posisi_koin >= batas_lebar) {
            posisi_koin = 0; nyawa--; 
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
        pause(); return true;
    } else {
        cetak_opsi_tengah(MERAH "[!] GAGAL! Koin berjatuhan berserakan di lantai kafe." RESET);
        cetak_opsi_tengah("Gagal menyelaraskan ritme.");
        pause(); return false;
    }
}


// ===================================================================================
// 12. MODUL: customerTransaction.cpp (Kamila)
// ===================================================================================
void beliBarang(Barang arr[], int jumlah) {
    while(true){
        cls();
        lihatsemuamenu(arr, jumlah);
        
        if (jumlah == 0) {
            cout << BOLD << KUNING;
            cetak_opsi_tengah("[!] Tidak Ada Barang");
            cout << RESET;
            pause(); return;
        }
        
        cout << BOLD << CYBER_CYAN;
        string idPilihan = ambil_input_teks("\nMasukkan ID Menu yang ingin dibeli (Tekan 0 untuk keluar): ", false);
        cout << RESET;
        
        if (idPilihan == "0") break;
    
        int indexDitemukan = -1;
        for (int i = 0; i < jumlah; i++) {
            if (arr[i].id == idPilihan) {
                indexDitemukan = i; break;
            }
        }
    
        if (indexDitemukan == -1) {
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << BOLD << MERAH;
            cetak_opsi_tengah("[!] Akses Ditolak: Menu dengan ID " + idPilihan + " tidak ditemukan.");
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << RESET;
            pause(); continue;
        }
    
        Barang *itemDipilih = &arr[indexDitemukan];
    
        cout << "\n";
        cout << BOLD << NEON_PURPLE;
        cetakTengah("-----------------------------------------------------");
        cout << BOLD << NEON_PINK;
        cetak_opsi_tengah("[+] Menu dipilih : " + itemDipilih->nama);
        
        cout << BOLD << CYBER_CYAN;
        cetak_input_tengah("[+] Harga satuan : Rp ");
        cout << BOLD << HIJAU << fixed << setprecision(0) << itemDipilih->harga << "\n";
        
        cout << BOLD << CYBER_CYAN;
        cetak_input_tengah("[+] Stok tersedia: ");
        cout << BOLD << KUNING << itemDipilih->stok << "\n";
        
        cout << BOLD << NEON_PURPLE;
        cetakTengah("-----------------------------------------------------");
        cout << RESET << "\n";
    
        cout << BOLD << KUNING;
        int jumlahBeli = ambil_input_angka("Masukkan jumlah beli: ");
        cout << RESET;
        
        if (jumlahBeli <= 0) {
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << BOLD << MERAH;
            cetak_opsi_tengah("[!] Error: Jumlah beli harus lebih besar dari 0!");
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << RESET;
            pause(); continue;
        }
        
        if (jumlahBeli > itemDipilih->stok) {
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << BOLD << MERAH;
            cetak_input_tengah("[!] Stok tidak cukup! Stok tersedia hanya ");
            cout << BOLD << KUNING << itemDipilih->stok << BOLD << MERAH << " item.\n";
            cout << BOLD << NEON_PURPLE;
            cetakTengah("-----------------------------------------------------");
            cout << RESET;
            pause(); continue;
        }
    
        double totalHarga = itemDipilih->harga * jumlahBeli;
        itemDipilih->stok -= jumlahBeli;
        simpan_stok_ke_file(arr, jumlah);
    
        cout << BOLD << NEON_PURPLE;
        cetakTengah("-----------------------------------------------------");
        cout << BOLD << HIJAU;
        cetak_input_tengah("[✓] Pembelian berhasil! Sisa stok \"");
        cout << BOLD << CYBER_CYAN << itemDipilih->nama << BOLD << HIJAU << "\": ";
        cout << BOLD << KUNING << itemDipilih->stok << "\n";
        cout << BOLD << NEON_PURPLE;
        cetakTengah("-----------------------------------------------------");
        cout << RESET;
    
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
        
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << BOLD << NEON_PINK;
        cetakTengah("MENU UTAMA PEMBELI (CUSTOMER)");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << RESET;
        
        cout << BOLD << CYBER_CYAN;
        cetak_opsi_tengah("     1. Lihat Daftar Menu & Beli Barang");
        cetak_opsi_tengah("     2. Lihat Sisa Loyalty Poin Anda");
        cetak_opsi_tengah("     3. Tukar Poin (Gacha Hadiah)");
        cetak_opsi_tengah("     4. Lihat Inventori Hadiah Anda");
        cout << BOLD << KUNING;
        cetak_opsi_tengah("     5. Ritual Maneki Neko (Buff SSR)");
        
        cout << BOLD << MERAH;
        cetak_opsi_tengah("     0. Keluar dari Menu Pembeli");
        
        cout << BOLD << NEON_PURPLE;
        cetakTengah("-----------------------------------------------------");
        cout << RESET;
        
        pilihan_pembeli = ambil_input_angka("    Pilihan: ");
        
        switch (pilihan_pembeli) {
            case 1: beliBarang(daftar_menu, jumlah_barang); break;
            case 2: lihatPoin(); pause(); break;
            case 3: menuGacha(&total_poin, inventori_hadiah, &jumlah_di_tas); break;
            case 4: lihatInventori(inventori_hadiah, jumlah_di_tas); pause(); break;
            case 5:
                if (sisa_buff_draw != 0) {
                    cls();
                    cetak_banner();
                    
                    cout << BOLD << NEON_PURPLE;
                    cetakTengah("=====================================================");
                    cout << BOLD << KUNING;
                    cetakTengah("PERINGATAN: BERKAT MANEKI NEKO MASIH AKTIF!");
                    cout << BOLD << NEON_PURPLE;
                    cetakTengah("=====================================================");
                    cout << RESET << "\n";
                    
                    if (sisa_buff_draw < 0) sisa_buff_draw = 0;
                    
                    cout << BOLD << MERAH;
                    cetak_opsi_tengah("[!] Anda masih memiliki kuota gacha beruntung.");
                    cout << BOLD << CYBER_CYAN;
                    cetak_opsi_tengah("Silakan gunakan sisa buff Anda di menu gacha terlebih dahulu!");
                    cout << RESET << "\n";
                    
                    cout << BOLD << NEON_PURPLE;
                    cetakTengah("=====================================================");
                    cout << RESET;
                    pause();
                } else {
                    if (mainkan_game_maneki_catch()) { sisa_buff_draw = 3; }
                }
                break;
            case 0: 
                cls();
                cetak_banner();
                cout << BOLD << NEON_PURPLE;
                cetakTengah("=====================================================");
                cout << BOLD << NEON_PINK;
                cetakTengah("S T A T U S   L O G O U T   P E M B E L I");
                cout << BOLD << NEON_PURPLE;
                cetakTengah("=====================================================");
                cout << RESET << "\n";

                if (jumlahTransaksi == 0) {
                    cout << BOLD << KUNING;
                    cetak_opsi_tengah("[-] Anda belum melakukan transaksi apapun.");
                    cout << RESET;
                } else {
                    cout << BOLD << CYBER_CYAN;
                    cetak_opsi_tengah("[ RIWAYAT PENGELUARAN ]");
                    cout << RESET;
                    
                    int total_belanja_sesi = 0;
                    int s_pad = (122 - 48) / 2;
                    string pad_hist(s_pad > 0 ? s_pad : 0, ' ');
                    
                    for (int i = 0; i < jumlahTransaksi; i++) {
                        total_belanja_sesi += transaksi[i];
                        cout << pad_hist << "  " << (i + 1) << ". Rp " << transaksi[i] << "\n";
                    }
                    cout << pad_hist << BOLD << HIJAU << ">> Total Belanja : Rp " << total_belanja_sesi << RESET << "\n";
                }

                cout << "\n";

                if (jumlah_di_tas == 0) {
                    cout << BOLD << KUNING;
                    cetak_opsi_tengah("[-] Anda belum menukarkan hadiah gacha.");
                    cout << RESET;
                } else {
                    cout << BOLD << HOT_MAGENTA;
                    cetak_opsi_tengah("[ RIWAYAT HADIAH GACHA ]");
                    cout << RESET;
                    
                    int s_pad = (122 - 48) / 2;
                    string pad_hist(s_pad > 0 ? s_pad : 0, ' ');
                    
                    for (int i = 0; i < jumlah_di_tas; i++) {
                        cout << pad_hist << "  " << (i + 1) << ". ";
                        if (inventori_hadiah[i].rarity == "SSR") cout << BOLD << KUNING;
                        else if (inventori_hadiah[i].rarity == "SR") cout << BOLD << NEON_PURPLE;
                        else cout << BOLD << HIJAU;
                        
                        cout << inventori_hadiah[i].namaHadiah << " (" << inventori_hadiah[i].rarity << ")" << RESET << "\n";
                    }
                }

                cout << "\n";
                cout << BOLD << NEON_PURPLE;
                cetakTengah("-----------------------------------------------------");
                cout << BOLD << CYBER_CYAN;
                cetakTengah("Terima kasih telah mengunjungi Smart Cafe!");
                cout << BOLD << NEON_PURPLE;
                cetakTengah("=====================================================");
                cout << RESET;
                
                pause(); 
                break;
            default: 
                cout << BOLD << MERAH;
                cetak_opsi_tengah("\n[!] Pilihan tidak valid!");
                cout << RESET;
                pause();
        }
    } while (pilihan_pembeli != 0);
}

// ===================================================================================
// 13. ROOT CONTROLLER: main.cpp (Team)
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
        cetakTengah("=====================================================");
        cout << BOLD << NEON_PINK;
        cetakTengah("WELCOME TO SMART CAFE LOYALTY");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("=====================================================");
        cout << RESET;
        
        cout << BOLD << CYBER_CYAN;
        cetak_opsi_tengah("    1. Masuk Sebagai Admin");
        cetak_opsi_tengah("    2. Masuk Sebagai Pembeli (Customer)");
        
        cout << BOLD << MERAH;
        cetak_opsi_tengah("    0. Keluar Aplikasi");
        
        cout << BOLD << NEON_PURPLE;
        cetakTengah("-----------------------------------------------------");
        cout << RESET;
        
        pilihan_role = ambil_input_angka("    Pilihan Role: ");

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
                cetakTengah("=====================================================");
                cout << BOLD << CYBER_CYAN;
                cetak_ketik("SYSTEM SHUTDOWN INITIATED", 75);
                cout << BOLD << NEON_PURPLE;
                cetakTengah("=====================================================");
                cout << RESET;
                
                cout << BOLD << KUNING;
                cetakTengah("- The Emperor Protects -");
                cout << RESET << "\n\n\n";
                break;
            default:
                cout << BOLD << MERAH;
                cetak_opsi_tengah("    [!] Pilihan role tidak valid! Silakan coba lagi.");
                cout << RESET;
                pause();
        }
    } while (pilihan_role != 0);

    return 0;
}