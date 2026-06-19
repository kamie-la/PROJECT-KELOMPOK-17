//#include <iostream>
//#include <iomanip>
//#include <string>
//using namespace std;


void tambahmenubaru(Barang arr[], int *jumlah, int kapasitas) {
    if (*jumlah >= kapasitas) {
        cout << "\n[!] Array penuh! Tidak bisa menambah menu baru.\n";
        return;
    }

    cout << "\n====== TAMBAH MENU BARU ======\n";

    cout << "Masukkan ID Menu   : ";
    cin >> arr[*jumlah].id;
    cin.ignore();

    cout << "Masukkan Nama Menu : ";
    getline(cin, arr[*jumlah].nama);

    cout << "Masukkan Harga     : Rp ";
    cin >> arr[*jumlah].harga;

    cout << "Masukkan Stok      : ";
    cin >> arr[*jumlah].stok;

    (*jumlah)++;

    cout << "\n[✔] Menu berhasil ditambahkan!\n";
}

void lihatsemuamenu(Barang arr[], int jumlah) {
    cout << "\n====== DAFTAR SEMUA MENU KAFE ======\n";

    if (jumlah == 0) {
        cout << "[!] Belum ada menu yang tersedia.\n";
        return;
    }

    cout << left
         << setw(6)  << "ID"
         << setw(25) << "Nama Menu"
         << setw(15) << "Harga (Rp)"
         << setw(8)  << "Stok"
         << "\n";

    cout << string(54, '-') << "\n";

    for (int i = 0; i < jumlah; i++) {
        cout << left
             << setw(6)  << arr[i].id
             << setw(25) << arr[i].nama
             << setw(15) << fixed << setprecision(0) << arr[i].harga
             << setw(8)  << arr[i].stok
             << "\n";
    }

    cout << string(54, '-') << "\n";
    cout << "Total menu: " << jumlah << " item\n";
}


void menuadmin(Barang arr[], int *jumlah, int kapasitas) {
    int pilihan;

    do {
        cout << "\n==================================\n";
        cout << "      MENU ADMIN - SMART KAFE      \n";
        cout << "==================================\n";
        cout << "1. Tambah Menu Baru\n";
        cout << "2. Lihat Semua Menu\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "-----------------------------\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahmenubaru(arr, jumlah, kapasitas);
                break;
            case 2:
                lihatsemuamenu(arr, *jumlah);
                break;
            case 0:
                cout << "[✓] Kembali ke menu utama...\n";
                break;
            default:
                cout << "[!] Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);
}
