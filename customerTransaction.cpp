#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Menu {
    int id;
    string nama;
    double harga;
    int stok;
};

int totalPoin       = 0;
int transaksi[100];
int jumlahTransaksi = 0;

void tambahMenuBaru(Menu arr[], int *jumlah, int kapasitas) {
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
    cout << "\n[+] Menu berhasil ditambahkan!\n";
}

void lihatSemuaMenu(Menu arr[], int jumlah) {
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

void prosesTransaksi(int totalHarga) {
    int dapatPoin = totalHarga / 10000;
    totalPoin += dapatPoin;

    if (jumlahTransaksi < 100) {
        transaksi[jumlahTransaksi] = totalHarga;
        jumlahTransaksi++;
    } else {
        cout << "[LIMIT] Batas Transaksi Harian Telah Penuh!" << endl;
    }

    cout << "\n============================================\n";
    cout << "              TRANSAKSI SUKSES              \n";
    cout << "============================================\n";
    cout << "Total Belanja : Rp " << totalHarga          << endl;
    cout << "Poin Didapat  : "    << dapatPoin << " poin" << endl;
    cout << "Total Poin    : "    << totalPoin << " poin" << endl;
    cout << "--------------------------------------------\n" << endl;
}

// ============================================================
//  FUNCTION: Beli Barang  [KAMILA – Customer Transaction]
//  Modul Alpro: Variabel & Operator | Percabangan | Pointer
// ============================================================
void beliBarang(Menu arr[], int jumlah) {

    // --- Tampilkan daftar menu ---
    lihatSemuaMenu(arr, jumlah);
    if (jumlah == 0) return;

    // --- Variabel: input ID pilihan ---
    int idPilihan;
    cout << "\nMasukkan ID Menu yang ingin dibeli: ";
    cin >> idPilihan;

    // --- Cari ID barang di dalam array ---
    int indexDitemukan = -1;
    for (int i = 0; i < jumlah; i++) {
        if (arr[i].id == idPilihan) {
            indexDitemukan = i;
            break;
        }
    }

    if (indexDitemukan == -1) {
        cout << "\n[!] Menu dengan ID " << idPilihan << " tidak ditemukan.\n";
        return;
    }

    // --- Pointer ke item yang dipilih (akses & ubah stok asli di memori) ---
    Menu *itemDipilih = &arr[indexDitemukan];

    cout << "\n[+] Menu dipilih : " << itemDipilih->nama                                       << "\n";
    cout << "[+] Harga satuan : Rp " << fixed << setprecision(0) << itemDipilih->harga         << "\n";
    cout << "[+] Stok tersedia: "    << itemDipilih->stok                                      << "\n";

    // --- Variabel: input jumlah beli ---
    int jumlahBeli;
    cout << "\nMasukkan jumlah beli: ";
    cin >> jumlahBeli;

    // --- Percabangan: validasi jumlah beli ---
    if (jumlahBeli <= 0) {
        cout << "\n[!] Jumlah beli tidak valid.\n";
        return;
    }

    // --- Percabangan: cek apakah stok cukup ---
    if (jumlahBeli > itemDipilih->stok) {
        cout << "\n[!] Stok tidak cukup! Stok tersedia hanya "
             << itemDipilih->stok << " item.\n";
        return;
    }

    // --- Variabel & Operator: hitung total harga ---
    double totalHarga = itemDipilih->harga * jumlahBeli;

    // --- Pointer: kurangi stok asli di memori ---
    itemDipilih->stok -= jumlahBeli;

    cout << "\n[✓] Pembelian berhasil! Sisa stok \"" << itemDipilih->nama
         << "\": " << itemDipilih->stok << "\n";

    // --- Panggil prosesTransaksi() yang sudah ada ---
    prosesTransaksi((int)totalHarga);
}

int main() {
    const int KAPASITAS = 50;
    Menu menuKafe[KAPASITAS];
    int  jumlahMenu = 0;
    int  pilihan;

    do {
        cout << "\n========== MENU UTAMA KAFE ==========\n";
        cout << "1. Tambah Menu Baru\n";
        cout << "2. Lihat Semua Menu\n";
        cout << "3. Beli Barang (Customer Transaction)\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin  >> pilihan;

        switch (pilihan) {
            case 1: tambahMenuBaru(menuKafe, &jumlahMenu, KAPASITAS); break;
            case 2: lihatSemuaMenu(menuKafe, jumlahMenu);             break;
            case 3: beliBarang(menuKafe, jumlahMenu);                 break;
            case 0: cout << "\n[✓] Terima kasih! Program selesai.\n"; break;
            default: cout << "\n[!] Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}