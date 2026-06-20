string nama_admin_aktif = "System";

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
//====================================================================
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