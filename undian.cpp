// Data Dummy (Global Array of Struct)
Hadiah hadiahR[50] = {{"Voucher Diskon 5%", "R"}, {"Permen", "R"}, {"Stiker Toko", "R"}};
Hadiah hadiahSR[50] = {{"Tumbler", "SR"}, {"Kopi Ireng", "SR"}};
Hadiah hadiahSSR[50] = {{"Earphone", "SSR"}};

int stokR = 3;   
int stokSR = 2;  
int stokSSR = 1; 

void lihatInventori(Hadiah tas[], int jumlah) {
    cls();
    cetak_banner();
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << CYBER_CYAN;
    cetakTengah("INVENTORI HADIAH ANDA");
    cout << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << RESET << "\n";

    if(jumlah == 0) {
        cetak_opsi_tengah("Belum ada hadiah di dalam tas Anda.");
        pause();
        return;
    }

    int total_baris = jumlah / 2;
    if (jumlah % 2 != 0) {
        total_baris++;
    }

    int lebar_terminal = 112;
    int lebar_konten = 60;
    int s = (lebar_terminal - lebar_konten) / 2;
    string pad(s > 0 ? s : 0, ' ');

    for (int i = 0; i < total_baris; i++) {
        string item_kiri = to_string(i + 1) + ". " + tas[i].namaHadiah + " (" + tas[i].rarity + ")";
        cout << pad << left << setw(35) << item_kiri;
        int idx_kanan = i + total_baris;
        if (idx_kanan < jumlah) {
            string item_kanan = to_string(idx_kanan + 1) + ". " + tas[idx_kanan].namaHadiah + " (" + tas[idx_kanan].rarity + ")";
            cout << left << item_kanan;
        }
        
        cout << "\n";
    }   
    cout << "\n";
    cetak_opsi_tengah(NEON_PURPLE "--------------------------------------------" RESET);
    pause();
}

void menuGacha(int* poinUser, Hadiah tas[], int* isiTas){
    int pilihanMenu;
    int jumlahUndi = 0;     
    while(true){
        cls();
        cetak_banner();
        cout << BOLD << NEON_PURPLE;
        cetakTengah("==== MENU UNDIAN ====");
        cout << RESET;
        
        cetak_input_tengah("Poin Anda: ");
        cout << BOLD << HIJAU << *poinUser << RESET << " Poin\n";
        
        cetak_opsi_tengah("1. Undi x1 (" KUNING "1 Poin" RESET ")");
        cetak_opsi_tengah("2. Undi x5 (" KUNING "5 Poin" RESET ")");
        cetak_opsi_tengah("0. Keluar");
        cetakTengah(NEON_PURPLE "--------------------------------------------" RESET);
        
        pilihanMenu = ambil_input_angka("Pilih: ");
    
        if (pilihanMenu == 1){
            jumlahUndi = 1;
        } else if (pilihanMenu == 2){
            jumlahUndi = 5;
        } else if (pilihanMenu == 0){
            break;
        } else {
            cetak_opsi_tengah(MERAH "[!] Pilihan salah!" RESET);
            pause();
            continue;
        }
        
        if (*poinUser < jumlahUndi){
            cetak_opsi_tengah(MERAH "[!] Poin tidak cukup!" RESET);
            pause();
            continue;
        }
        
        *poinUser -= jumlahUndi;
        
        cetak_input_tengah(CYBER_CYAN ">> MENGUNDI HADIAH" RESET);
        for (int i = 0; i < 3; i++) {
            this_thread::sleep_for(chrono::milliseconds(400));
            cout << CYBER_CYAN << "." << RESET;
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

                cout << "\a"; 
                for (int splash = 0; splash < 2; splash++) {
                    cls();
                    cout << BOLD << (splash == 0 ? KUNING : NEON_PINK);
                    cetakTengah("        /\\_/\\      =================================== ");
                    cetakTengah("       ( >.< )     !!!  G A C O O O O R R R R  !!!     ");
                    cetakTengah("       =========   =================================== ");
                    cetakTengah("     /  |     |  \\                                     ");
                    cetakTengah("    |   | [O] |   |   HOKI BANGET LOH YA! ");
                    cetakTengah("     \\_ |_____| _/                                     ");
                    cout << RESET;
                    this_thread::sleep_for(chrono::milliseconds(250));
                }
                this_thread::sleep_for(chrono::milliseconds(400));
                cout << "\n\n";
            }
            
            cetak_input_tengah("Undian ");
            cout << i << " : " << hadiahTerpilih.namaHadiah << " ";
            
            if (hadiahTerpilih.rarity == "SSR") {
                cout << BOLD << KUNING << "[ " << hadiahTerpilih.rarity << " ]" << RESET << "\n";
            } else if (hadiahTerpilih.rarity == "SR") {
                cout << BOLD << CYBER_CYAN << "[ " << hadiahTerpilih.rarity << " ]" << RESET << "\n";
            } else {
                cout << "\033[2m[ " << hadiahTerpilih.rarity << " ]\033[0m" << "\n";
            }
            
            tas[*isiTas] = hadiahTerpilih; 
            (*isiTas)++;                   
        }
        
        cetak_input_tengah("\nSisa poin: ");
        cout << BOLD << HIJAU << *poinUser << RESET << "\n";
        pause();
    }
}

void tambah_hadiah_admin(int* batasR, int* batasSR, int* batasSSR) {
    cls();
    cetak_banner();
    cout << BOLD << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << CYBER_CYAN;
    cetakTengah("MENU ADMIN - REWARD MANAGER");
    cout << NEON_PURPLE;
    cetakTengah("=====================================================");
    cout << RESET << "\n";
    
    string namaBaru;
    int pilihanTier;
    
    namaBaru = ambil_input_teks("Masukkan Nama Hadiah Baru: ", false);
    
    cetak_opsi_tengah("\nPilih Tingkat Kelangkaan (Rarity Tier):");
    
    // FIX: Tanda kutip diperbaiki agar kode warna ANSI dibaca sebagai string utuh oleh compiler
    cetak_opsi_tengah("1. R   (\033[2mCommon" RESET ")");
    cetak_opsi_tengah("2. SR  (" CYBER_CYAN "Rare" RESET ")");
    cetak_opsi_tengah("3. SSR (" KUNING "Epic/Legendary" RESET ")");
    
    pilihanTier = ambil_input_angka("Pilihan: ");
    
    if (pilihanTier == 1) {
        if (*batasR >= 50) {
            cetak_opsi_tengah("\n" MERAH "[!] Kapasitas inventori hadiah R penuh!" RESET);
            pause();
            return;
        }
        hadiahR[*batasR].namaHadiah = namaBaru;
        hadiahR[*batasR].rarity = "R";
        (*batasR)++;
        cetak_opsi_tengah("\n" HIJAU "[✓] Hadiah \"" + namaBaru + "\" berhasil ditambahkan ke Tier R!" RESET);
    } 
    else if (pilihanTier == 2) {
        if (*batasSR >= 50) {
            cetak_opsi_tengah("\n" MERAH "[!] Kapasitas inventori hadiah SR penuh!" RESET);
            pause();
            return;
        }
        hadiahSR[*batasSR].namaHadiah = namaBaru;
        hadiahSR[*batasSR].rarity = "SR";
        (*batasSR)++;
        cetak_opsi_tengah("\n" HIJAU "[✓] Hadiah \"" + namaBaru + "\" berhasil ditambahkan ke Tier SR!" RESET);
    } 
    else if (pilihanTier == 3) {
        if (*batasSSR >= 50) {
            cetak_opsi_tengah("\n" MERAH "[!] Kapasitas inventori hadiah SSR penuh!" RESET);
            pause();
            return;
        }
        hadiahSSR[*batasSSR].namaHadiah = namaBaru;
        hadiahSSR[*batasSSR].rarity = "SSR";
        (*batasSSR)++;
        cetak_opsi_tengah("\n" HIJAU "[✓] Hadiah \"" + namaBaru + "\" berhasil ditambahkan ke Tier SSR!" RESET);
    } 
    else {
        cetak_opsi_tengah("\n" MERAH "[!] Pilihan tier tidak valid!" RESET);
    }
    pause();
}