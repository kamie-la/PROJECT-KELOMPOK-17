#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct HadiahDapat {
    string namaHadiah;
    string rarity;
};


void menuGacha(int* poinUser, HadiahDapat tas[], int* isiTas){
    int pilihanMenu;
    int jumlahRoll = 0;

    cout << "\n--- MENU UNDIAN ---" << endl;
    cout << "Poin Anda: " << *poinUser << endl;
    cout << "1. Undi x1 (1 Poin)" << endl;
    cout << "2. Undi x5 (5 Poin)" << endl;
    cout << "Pilih: ";
    cin >> pilihanMenu;

    if (pilihanMenu == 1){
        jumlahRoll = 1;
    } else if (pilihanMenu == 2){
        jumlahRoll = 5;
    } else {
        cout << "Pilihan salah!" << endl;
        return;
    }

    if (*poinUser < jumlahRoll){
        cout << "Poin kurang! Belanja dulu sana 🗿" << endl;
        return;
    }

    *poinUser -= jumlahRoll;

    cout << "\n>> MENGUNDI HADIAH..." << endl;

    for (int i = 1; i <= jumlahRoll; i++) {
        
        int angka = (rand() % 100) + 1; 
        if (angka == 1) { 
            // 1% Peluang (Angka 1)
            cout << "Roll " << i << ": [SSR] Eeeeeeeeeee dapet Item Premium Toko!" << endl;
            
            // Simpan ke tas (Data Dummy sementara nunggu Admin)
            tas[*isiTas].namaHadiah = "Item Premium Toko";
            tas[*isiTas].rarity = "SSR";
            (*isiTas)++;
            
        } 
        else if (angka <= 10) { 
            // 9% Peluang (Angka 2 sampai 10)
            cout << "Roll " << i << ": [SR] Mantap dapet Cookie Spesial!" << endl;
            
            tas[*isiTas].namaHadiah = "Cookie Spesial";
            tas[*isiTas].rarity = "SR";
            (*isiTas)++;
            
        } 
        else { 
            // 90% Peluang (Angka 11 sampai 100)
            cout << "Roll " << i << ": [R] Kopiko aj 🗿" << endl;
            
            tas[*isiTas].namaHadiah = "Kopiko";
            tas[*isiTas].rarity = "R";
            (*isiTas)++;
        }
    }
}

int main() {
    srand(time(0)); // Taruh di main() cukup 1 kali

    // Simulasi user dapet poin dari total belanja
    int totalBelanja = 50000;
    int poin = totalBelanja / 10000; // Dapet 5 Poin
    
    // Tas user (Array of Struct)
    HadiahDapat inventori[100];
    int jumlahDiTas = 0;

    // Panggil fungsinya
    menuGacha(&poin, inventori, &jumlahDiTas);

    return 0;
}