
# ===================================================================
SMART CAFE LOYALTY SYSTEM - README DOCUMENT

1. DESKRIPSI PROYEK
---
Aplikasi berbasis CLI (Command Line Interface) ini dirancang menggunakan bahasa C++ tradisional untuk memenuhi tugas besar laboratorium Informatika Universitas Mataram (UNRAM). Sistem ini mengintegrasikan manajemen inventaris kafe di sisi Admin dengan simulasi transaksi retail dan mini-game gacha berbasis kesetiaan pelanggan (loyalty points) di sisi Pembeli.

2. FITUR UTAMA SISTEM
---
* Sistem Autentikasi Admin Terbuka: Gerbang masuk ganda (Sign In & Sign Up) menggunakan validasi format NIM mahasiswa Informatika UNRAM, pencegah data duplikat, serta dilengkapi verifikasi keamanan matematika (CAPTCHA) tradisional.
* Data Persistence Berkas (CSV): Rekam data inventaris bersifat kekal menggunakan pustaka . Setiap perubahan stok akibat penambahan oleh admin atau pembelian oleh customer akan langsung diperbarui ke dalam berkas 'stok_barang.txt'.
* Audit Kepemilikan Data: Setiap menu baru yang dimasukkan ke dalam sistem akan mencatat nama Admin yang bertanggung jawab menambahkan item tersebut, menjamin transparansi data.
* Mekanisme Gacha & Pity Rate: Sistem penukaran poin loyalty belanja menjadi kuota undian hadiah acak yang terbagi menjadi tiga tier kelangkaan (R, SR, SSR) serta jaminan garansi kelangkaan (Pity) pada kelipatan paket tertentu.
* Ritual Maneki Neko Mini-Game: Mini-game tangkap koin interaktif yang memberikan berkas peningkatan peluang (Buff SSR) untuk tiga sesi tarikan gacha berikutnya, dikunci dengan sistem validasi anti-leak numerik.
* Visualisasi Grafik & Struk Digital: Representasi kondisi stok kritis menggunakan bar horizontal live di terminal, serta cetakan nota pembayaran digital yang presisi di tengah layar memanfaatkan fungsi pemformatan string tradisional kelompok.

3. ARSITEKTUR KODE DAN PEMBAGIAN KERJA KELOMPOK
---
Proyek ini dibangun menggunakan konsep pemrograman modular tradisional dengan memecah fungsionalitas ke dalam beberapa berkas terpisah yang disatukan melalui berkas utama (main.cpp):

* main.cpp: Pusat kendali aplikasi, inisialisasi awal data dari hardisk, serta manajemen gerbang pemilihan peran (Role Selection).
* utilitas.cpp: Berisi sekumpulan fungsi pembantu bersama (helper functions), fungsi penyehat terminal (cls, pause), algoritma cetakTengah, manajemen simpan-muat file, serta macros warna gradien diagonal cyberpunk.
* minigame.cpp: Logika utama permainan interaktif penangkap koin keberuntungan Maneki Neko (Dikerjakan oleh: M. Pradifta Arizona).
* undian.cpp: Manajemen database hadiah gacha global, penentuan peluang matematika acak, dan pengelolaan menu penukaran loyalty poin (Dikerjakan oleh: Rizka Dzuliyatun Ni'mah).
* admin 1.cpp: Gerbang masuk admin, verifikasi akun menggunakan file teks terpisah, dan fungsionalitas input barang baru (Dikerjakan oleh: Ni Ketut Intan Ayu Widyastuti).
* AdminBagian2cpp.cpp: Logika manipulasi array lanjutan untuk kebutuhan edit data menu, penghapusan item kafe, dan grafik stok visual (Dikerjakan oleh: Hari Fitratullah).
* customerTransaction.cpp: Alur belanja pembeli, kalkulasi pajak restoran 11%, biaya layanan, penanganan error handling input huruf/spasi, dan pencetakan nota pembelian digital (Dikerjakan oleh: Baiq Nur Saqinah Kamila).
* poin.cpp: Modul pelacakan saldo poin kesetiaan pembeli dan perekaman riwayat transaksi (Dikerjakan oleh: I Dewa Made Krisnayana Wicaksana).

4. PETUNJUK KOMPILASI DAN MENJALANKAN APLIKASI
---
Proses kompilasi tradisional wajib dilakukan melalui Terminal (PowerShell/CMD/Bash) dari direktori root proyek tempat seluruh file source code (.cpp) berada:

Step 1 - Perintah Kompilasi (g++ compiler):
```
g++ main.cpp -o SmartCafeApp
```
Step 2 - Perintah Menjalankan Aplikasi:

* Di OS Windows (PowerShell/CMD):
```
.\SmartCafeApp.exe
```
* Di OS Linux / MacOS (Terminal):
```
./SmartCafeApp
```
# Catatan Sistem:
Aplikasi ini sudah dilengkapi konfigurasi pemosisian UTF-8 otomatis (chcp 65001) pada sistem Windows agar karakter grafik balok stok (█) dan warna True Color 24-bit miring diagonal dapat merender secara tajam dan rapi di layar terminal penguji.