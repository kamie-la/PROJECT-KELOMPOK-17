// #include <iostream>
// #include <iomanip>
// #include <string>
// using namespace std;

void beliBarang(Barang arr[], int jumlah) {

    lihatSemuaMenu(arr, jumlah);
    if (jumlah == 0) return;

    string idPilihan;
    cout << "\nMasukkan ID Menu yang ingin dibeli: ";
    cin >> idPilihan;

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

    Barang *itemDipilih = &arr[indexDitemukan];

    cout << "\n[+] Menu dipilih : " << itemDipilih->nama << "\n";
    cout << "[+] Harga satuan : Rp "
         << fixed << setprecision(0)
         << itemDipilih->harga << "\n";
    cout << "[+] Stok tersedia: "
         << itemDipilih->stok << "\n";

    int jumlahBeli;
    cout << "\nMasukkan jumlah beli: ";
    cin >> jumlahBeli;

    if (jumlahBeli <= 0) {
        cout << "\n[!] Jumlah beli tidak valid.\n";
        return;
    }

    if (jumlahBeli > itemDipilih->stok) {
        cout << "\n[!] Stok tidak cukup! Stok tersedia hanya "
             << itemDipilih->stok << " item.\n";
        return;
    }

    double totalHarga = itemDipilih->harga * jumlahBeli;

    itemDipilih->stok -= jumlahBeli;

    cout << "\n[✓] Pembelian berhasil! Sisa stok \""
         << itemDipilih->nama << "\": "
         << itemDipilih->stok << "\n";

    prosesTransaksi((int)totalHarga);

   // return 0;
}