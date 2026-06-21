string nama_admin_aktif = "System";

// ===================================================================================
// FUNGSI ENKRIPSI AMAN (ANTI CARRIAGE RETURN / EOF BUGS)
// ===================================================================================
string proses_enkripsi_aman(string data_asli) {
    char kunci = 'C';
    string hasil = "";
    for (size_t i = 0; i < data_asli.length(); i++) {
        int cipher = data_asli[i] ^ kunci;
        // Mengubah karakter ASCII aneh menjadi string angka teks agar aman di file .txt
        hasil += to_string(cipher) + " "; 
    }
    return hasil;
}

// ===================================================================================
// FUNGSI DEKRIPSI AMAN
// ===================================================================================
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
        } else {
            temp_angka += data_terenkripsi[i];
        }
    }
    return hasil;
}

void simpan_txt(string nama, string nim) {
    // Mode file normal (ios::app) karena isi data kini dipastikan berupa karakter angka aman
    ofstream file_atmint("data_atmint.txt", ios::app);
    if (file_atmint.is_open()) {
        string nama_terenkripsi = proses_enkripsi_aman(nama);
        string nim_terenkripsi = proses_enkripsi_aman(nim);

        file_atmint << nama_terenkripsi << "\n";
        file_atmint << nim_terenkripsi << "\n";
        file_atmint.close();
    }
}

bool cek_apakah_atmint_ada(string nama_cari, string nim_cari) {
    ifstream file_atmint("data_atmint.txt");
    if (file_atmint.is_open()) {
        string nama_file_terenkripsi, nim_file_terenkripsi;
        while (getline(file_atmint, nama_file_terenkripsi) && getline(file_atmint, nim_file_terenkripsi)) {
            
            // Pembersih \r otomatis jika file dibaca silang antara Linux dan Windows
            if (!nama_file_terenkripsi.empty() && nama_file_terenkripsi.back() == '\r') nama_file_terenkripsi.pop_back();
            if (!nim_file_terenkripsi.empty() && nim_file_terenkripsi.back() == '\r') nim_file_terenkripsi.pop_back();

            string nama_file = proses_dekripsi_aman(nama_file_terenkripsi);
            string nim_file = proses_dekripsi_aman(nim_file_terenkripsi);

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
        string nama_file_terenkripsi, nim_file_terenkripsi;
        while (getline(file_atmint, nama_file_terenkripsi) && getline(file_atmint, nim_file_terenkripsi)) {
            
            if (!nama_file_terenkripsi.empty() && nama_file_terenkripsi.back() == '\r') nama_file_terenkripsi.pop_back();
            if (!nim_file_terenkripsi.empty() && nim_file_terenkripsi.back() == '\r') nim_file_terenkripsi.pop_back();

            string nama_file = proses_dekripsi_aman(nama_file_terenkripsi);
            string nim_file = proses_dekripsi_aman(nim_file_terenkripsi);

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
        cout << BOLD << NEON_PURPLE;
        cetakTengah("============================================");
        cout << NEON_PINK;
        cetakTengah("SECURITY VERIFICATION (CAPTCHA)");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("============================================");
        cout << RESET;
        cetak_opsi_tengah("Selesaikan operasi matematika berikut:");
        
        cetak_input_tengah("Berapakah hasil dari " + to_string(a) + " + " + to_string(b) + " = ");
        if (!(cin >> jawaban_user)) {
            cin.clear();
            cin.ignore(10000, '\n');
            salah_hitung++;
            cetak_opsi_tengah("\n" MERAH "[!] Input harus berupa angka!" RESET);
            cetak_opsi_tengah("Toleransi kesalahan: " + to_string(salah_hitung) + "/3");
            pause();
            continue;
        }

        if (jawaban_user == hasil_benar) {
            cin.ignore(10000, '\n');
            return true;
        } else {
            salah_hitung++;
            cin.ignore(10000, '\n');
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
        cout << BOLD << NEON_PURPLE;
        cetakTengah("============================================");
        cout << CYBER_CYAN;
        cetakTengah("ADMIN GATE AUTHENTICATION SYSTEM");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("============================================");
        cout << RESET;
        cetak_opsi_tengah("1. Sign In (Masuk Log)");
        cetak_opsi_tengah("2. Sign Up (Daftar Akun Admin Baru)");
        cetak_opsi_tengah("0. Kembali");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("----------------------------------------------");
        cout << RESET;
        opsi_auth = ambil_input_angka("Pilihan Anda: ");

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
            cout << BOLD << NEON_PURPLE;
            cetakTengah("============================================");
            cout << NEON_PINK;
            cetakTengah("REGISTRASI AKUN ADMIN BARU (SIGN UP)");
            cout << BOLD << NEON_PURPLE;
            cetakTengah("============================================");
            cout << RESET;
            
            nama_data = ambil_input_teks("Daftarkan Nama Admin(0 Untuk batal)  : ", false);
            if (nama_data == "0"){
                return false;
            }
            
            if (nama_data.empty() || nama_data == " " || nama_data == "\t") {
                cetak_opsi_tengah("\n" MERAH "[!] Error: Nama tidak boleh kosong!" RESET);
                pause();
                cout << "\033[5A\033[J"; 
                continue;
            }

            nim_data = ambil_input_teks("Daftarkan NIM Admin   : ", false);
            if (!validasi_nim_atmint(nim_data)) {
                cetak_opsi_tengah("\n" MERAH "[!] REGISTRASI GAGAL: NIM harus 11 digit dan diawali 'F1D02'!" RESET);
                pause();
                cout << "\033[5A\033[J"; 
                continue;
            }

            if (cek_duplikat_registrasi(nama_data, nim_data)) {
                cetak_opsi_tengah("\n" MERAH "[!] REGISTRASI GAGAL: Nama atau NIM sudah terdaftar oleh Admin lain!" RESET);
                pause();
                cout << "\033[5A\033[J"; 
                continue;
            }

            if (!jalankan_captcha_simpel()) {
                cls();
                cetak_banner();
                cout << BOLD << NEON_PURPLE;
                cetakTengah("============================================");
                cout << RESET;
                cetak_opsi_tengah("\n" MERAH "[!] AKSES DIKUNCI: Anda salah mengisi CAPTCHA sebanyak 3 kali!" RESET);
                pause();
                return false;
            }

            simpan_txt(nama_data, nim_data);
            cls();
            cetak_banner();
            cout << BOLD << NEON_PURPLE;
            cetakTengah("============================================");
            cout << RESET;
            cetak_opsi_tengah("\n" HIJAU "[✓] SIGN UP BERHASIL! Silakan masuk melalui menu Sign In." RESET);
            pause();
            
            opsi_auth = 1; 
            break;
        }
    }

    while (opsi_auth == 1) {
        string nama_masuk, nim_masuk;
        cls();
        cetak_banner();
        cout << BOLD << NEON_PURPLE;
        cetakTengah("============================================");
        cout << CYBER_CYAN;
        cetakTengah("SISTEM MASUK ADMIN (SIGN IN)");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("============================================");
        cout << RESET;
        
        nama_masuk = ambil_input_teks("Masukkan Nama Anda (0 Untuk batal) : ", false);
        if (nama_masuk == "0") {
            return false;
        }
        
        nim_masuk = ambil_input_teks("Masukkan NIM Anda  : ", false);

        if (!cek_apakah_atmint_ada(nama_masuk, nim_masuk)) {
            cls();
            cetak_banner();
            cout << BOLD << NEON_PURPLE;
            cetakTengah("============================================");
            cout << RESET;
            cetak_opsi_tengah("\n" MERAH "[!] AKSES DITOLAK: Nama atau NIM salah / tidak terdaftar!" RESET);
            pause();
            continue; 
        }

        nama_admin_aktif = nama_masuk;

        cls();
        cetak_banner();
        cout << BOLD << NEON_PURPLE;
        cetakTengah("============================================");
        cout << RESET;
        cetak_opsi_tengah("\n" HIJAU "[✓] LOGIN SUKSES: Selamat datang kembali, Admin " + nama_admin_aktif + "!" RESET);
        pause();
        break; 
    }
    
    return true;
}

void tambahmenubaru(Barang arr[], int *jumlah, int kapasitas) {
    if (*jumlah >= kapasitas) {
        cls();
        cetak_banner();
        cetak_opsi_tengah("\n" MERAH "[!] Array penuh! Tidak bisa menambah menu baru." RESET);
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
        cout << BOLD << NEON_PURPLE;
        cetakTengah("====== TAMBAH MENU BARU ======");
        cout << RESET;

        id_input = ambil_input_teks("Masukkan ID Menu   : ", false);

        bool ada_spasi_id = false;
        if (cin.peek() == ' ' || cin.peek() == '\t') {
            ada_spasi_id = true;
        }

        if (id_input == "0") {
            cetak_opsi_tengah("\n" MERAH "[!] Error: ID \"0\" tidak boleh digunakan!" RESET);
            cin.clear();
            cin.ignore(10000, '\n');
            pause();
            continue;
        }

        if (ada_spasi_id) {
            cetak_opsi_tengah("\n" MERAH "[!] Error: ID Menu tidak boleh mengandung spasi!" RESET);
            cin.clear();
            cin.ignore(10000, '\n');
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
            cin.ignore(10000, '\n');
            pause();
            continue;
        }

        nama_input = ambil_input_teks("Masukkan Nama Menu : ", false);
        if (nama_input.empty() || nama_input == " " || nama_input == "\t") {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Nama menu tidak boleh kosong!" RESET);
            pause();
            continue;
        }

        harga_input = ambil_input_angka("Masukkan Harga     : Rp ");
        if (harga_input <= 0) {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Harga harus lebih besar dari 0!" RESET);
            cin.clear();
            cin.ignore(10000, '\n');
            pause();
            continue;
        }

        stok_input = ambil_input_angka("Masukkan Stok      : ");
        if (stok_input < 0) {
            cetak_opsi_tengah("\n" MERAH "[!] Error: Stok tidak boleh bernilai negatif!" RESET);
            cin.clear();
            cin.ignore(10000, '\n');
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
        pause();
        break;
    }
}

void lihatsemuamenu(Barang arr[], int jumlah) {
    cls();
    cetak_banner();
    cout << BOLD << NEON_PURPLE;
    cetakTengah("====== DAFTAR SEMUA MENU KAFE ======");
    cout << RESET;

    if (jumlah == 0) {
        cetak_opsi_tengah(MERAH "[!] Belum ada menu yang tersedia." RESET);
        return;
    }

    cout << left
         << setw(6)  << "ID"
         << setw(25) << "Nama Menu"
         << setw(15) << "Harga (Rp)"
         << setw(8)  << "Stok"
         << setw(15) << "Penambah"
         << "\n";

    cout << NEON_PURPLE << string(69, '-') << RESET << "\n";

    for (int i = 0; i < jumlah; i++) {
        cout << left
             << setw(6)  << arr[i].id
             << setw(25) << arr[i].nama
             << setw(15) << fixed << setprecision(0) << arr[i].harga;
        
        if (arr[i].stok <= 5) {
            cout << MERAH;
        } else {
            cout << CYBER_CYAN;
        }
        cout << left << setw(8) << arr[i].stok << RESET;
        cout << left << setw(15) << arr[i].penambah << "\n";
    }

    cout << NEON_PURPLE << string(69, '-') << RESET << "\n";
    cetak_input_tengah("Total menu: ");
    cout << BOLD << jumlah << RESET << " item\n";
}

void menuadmin(Barang arr[], int *jumlah, int kapasitas) {
    if (!proses_autentikasi_atmint()) {
        return; 
    }
    int pilihan;
    do {
        cls();
        cetak_banner();
        cout << BOLD << NEON_PURPLE;
        cetakTengah("============================================");
        cout << NEON_PINK;
        cetakTengah("MENU UTAMA ADMIN MANAGEMENT");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("============================================");
        cout << RESET;
        
        cetak_opsi_tengah("     1. Tambah Menu Baru");
        cetak_opsi_tengah("     2. Lihat Semua Menu");
        cetak_opsi_tengah("     3. Edit Data Barang");
        cetak_opsi_tengah("     4. Hapus Data Barang");
        cetak_opsi_tengah("     5. Lihat Grafik Stok Visual");
        cetak_opsi_tengah("     6. Kelola & Tambah Hadiah Gacha");
        cetak_opsi_tengah("     0. Kembali ke Role Selection");
        cout << BOLD << NEON_PURPLE;
        cetakTengah("----------------------------------------------");
        cout << RESET;
        
        pilihan = ambil_input_angka("     Pilihan: ");
        
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
                cetak_opsi_tengah(HIJAU "[✓] Kembali ke menu utama...\n" RESET);
                pause();
                break;
            default:
                cetak_opsi_tengah(MERAH "[!] Pilihan tidak valid!\n" RESET);
                pause();
        }
    } while (pilihan != 0);
}