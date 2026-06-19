#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// === MODUL 5: STRUCT ===
struct Hadiah{
    string namaHadiah;
    string rarity;
};

// Data Dummy (Global Array of Struct)
Hadiah hadiahR[50] = {{"Voucher Diskon 5%", "R"}, {"Permen", "R"}, {"Stiker Toko", "R"}};
Hadiah hadiahSR[50] = {{"Tumbler", "SR"}, {"Kopi Ireng", "SR"}};
Hadiah hadiahSSR[50] = {{"Earphone", "SSR"}};

int stokR = 3;   // Saat ini baru ada 3 barang R
int stokSR = 2;  // Saat ini baru ada 2 barang SR
int stokSSR = 1; // Saat ini baru ada 1 barang SSR

void lihatInventori(Hadiah tas[], int jumlah) {
    cout << "\n===== INVENTORI =====\n";

    if(jumlah == 0) {
        cout << "Belum ada hadiah.\n";
        return;
    }

    for(int i = 0; i < jumlah; i++) {
        cout << i + 1 << ". " << tas[i].namaHadiah << " (" << tas[i].rarity << ")" << endl;
    }
}

void menuGacha(int* poinUser, Hadiah tas[], int* isiTas){
    int pilihanMenu;
    int jumlahUndi = 0;     

    cout << "\n==== MENU UNDIAN ====" << endl;
    cout << "Poin Anda: " << *poinUser << endl;
    cout << "1. Undi x1 (1 Poin)" << endl;
    cout << "2. Undi x5 (5 Poin)" << endl;
    cout << "Pilih: ";
    cin >> pilihanMenu;

    if (pilihanMenu == 1){
        jumlahUndi = 1;
    } else if (pilihanMenu == 2){
        jumlahUndi = 5;
    } else {
        cout << "Pilihan salah!" << endl;
        return;
    }

    // Validasi poin
    if (*poinUser < jumlahUndi){
        cout << "Poin tidak cukup!" << endl;
        return;
    }

    // Potong poin
    *poinUser -= jumlahUndi;

    cout << "\n>> MENGUNDI HADIAH..." << endl;

    bool dapatSRatauSSR = false;

    for (int i = 1; i <= jumlahUndi; i++) {
        string rarity;
        Hadiah hadiahTerpilih; 

        if (jumlahUndi == 5 && i == 5 && !dapatSRatauSSR){
            rarity = "SR";
        } else {
            int angka = (rand() % 100) + 1; 
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

        if(rarity == "R") {
            // Nggak usah pakai sizeof lagi, langsung pakai variabel counter stokR
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

        cout << "Undian " << i << " : " << hadiahTerpilih.namaHadiah << " (" << hadiahTerpilih.rarity << ")" << endl;
        
        tas[*isiTas] = hadiahTerpilih; // Masukkan barang ke array
        (*isiTas)++;                   
    }

    cout << "\nSisa poin: " << *poinUser << endl;
}

int main() {
    srand(time(0)); 

    // Simulasi state pembeli
    int totalBelanja = 50000;
    int poin = totalBelanja / 10000; // Dapet 5 Poin
    
    Hadiah inventori[100];
    int jumlahDiTas = 0;

    // Testing panggil fungsi berulang kali
    menuGacha(&poin, inventori, &jumlahDiTas);
    lihatInventori(inventori, jumlahDiTas);

    return 0;
}