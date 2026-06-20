// #include <iostream>
// #include <cstdlib>
// #include <ctime>
// using namespace std;

// Data Dummy (Global Array of Struct)
Hadiah hadiahR[50] = {{"Voucher Diskon 5%", "R"}, {"Permen", "R"}, {"Stiker Toko", "R"}};
Hadiah hadiahSR[50] = {{"Tumbler", "SR"}, {"Kopi Ireng", "SR"}};
Hadiah hadiahSSR[50] = {{"Earphone", "SSR"}};

int stokR = 3;   // Saat ini baru ada 3 barang R
int stokSR = 2;  // Saat ini baru ada 2 barang SR
int stokSSR = 1; // Saat ini baru ada 1 barang SSR

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
        
        // Validasi poin
        if (*poinUser < jumlahUndi){
            cetak_opsi_tengah("[!] Poin tidak cukup!");
            pause();
            continue;
        }
        
        // Potong poin
        *poinUser -= jumlahUndi;
        
        //Tambahan animasi loading
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
            
            tas[*isiTas] = hadiahTerpilih; // Masukkan barang ke array
            (*isiTas)++;                   
        }
        
        cetak_input_tengah("\nSisa poin: ");
        cout << *poinUser << "\n";
        pause();
    }
}

//Fungsi tambahan agar atmin bisa mengisi hadiahnya sendiri
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

// int main() {
//     srand(time(0)); 

//     // Simulasi state pembeli
//     int totalBelanja = 50000;
//     int poin = totalBelanja / 10000; // Dapet 5 Poin
    
//     Hadiah inventori[100];
//     int jumlahDiTas = 0;

//     // Testing panggil fungsi berulang kali
//     menuGacha(&poin, inventori, &jumlahDiTas);
//     lihatInventori(inventori, jumlahDiTas);

//     return 0;
// }