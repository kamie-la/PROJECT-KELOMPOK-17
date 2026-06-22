
<div align="center">
  
# ☕ SMART CAFE LOYALTY SYSTEM
**Advanced CLI Management & Gamification Platform**

Aplikasi Management & Loyalty Program Retail Modern Berbasis Command Line Interface (CLI)
*Tugas Besar Mata Kuliah Algoritma dan Pemrograman — Informatika Universitas Mataram (UNRAM)*

[![C++](https://img.shields.io/badge/C++-Traditional-00599C?style=for-the-badge&logo=c%2B%2B)](https://cplusplus.com/)
[![CLI](https://img.shields.io/badge/Interface-CLI_Terminal-4D4D4D?style=for-the-badge&logo=windows-terminal)](https://github.com/)
[![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)](#)

</div>

---

## 📖 1. Tentang Proyek

Aplikasi **Smart Cafe Loyalty System** adalah platform retail cafe virtual berbasis terminal murni yang dikembangkan dengan bahasa C++ tradisional menggunakan paradigma *Modular Programming* (Tapi boong). 

Proyek ini dirancang untuk mengatasi batasan-batasan standar aplikasi CLI biasa. Tidak hanya sekadar melakukan operasi Input/Output data barang, sistem ini menyatukan manajemen basis data inventaris di sisi **Admin** dengan simulasi transaksi retail, manajemen loyalitas konsumen, serta interaksi visual grafis dan animasi *mini-game arcade* di sisi **Pembeli (Customer)**.

---

## 🚀 2. Fitur Utama & Inovasi Teknis

Aplikasi ini mengimplementasikan beberapa teknik pemrograman dan manipulasi terminal tingkat lanjut, di antaranya:

* 🔐 **Secure Admin Gate (Integer Token Encryption):** Sistem pendaftaran (*Sign Up*) dan masuk (*Sign In*) Admin yang dilengkapi CAPTCHA matematika. Guna menghindari kerentanan algoritma enkripsi biner terhadap penanda akhir file pada OS Windows atau karakter *Enter* (`\n`, `\r`) yang dapat memotong baris teks database secara sepihak, sistem ini mengubah hasil operasi biner XOR **`'C'`** langsung menjadi deretan string angka indeks tekstual terpisah yang $100\%$ aman di dalam file `data_atmint.txt`.
* 🖥️ **Seamless UI Erase (Anti-Ghosting Buffer):** Sistem penanganan kesalahan input teks dan angka tidak lagi menggunakan pembersihan layar total (`cls()`) yang membuat layar berkedip (*flickering*). Memanfaatkan perintah manipulasi kursor ANSI Escape Codes `\033[5A\033[J`, sistem akan melompat naik ke atas dan menghapus baris pesan error secara spesifik, sehingga menu utama di atasnya tetap diam dan stabil.
* 📦 **Data Persistence Dua Arah (CSV File Handling):** Perekaman data stok barang kafe menggunakan pustaka `<fstream>` ke dalam file `stok_barang.txt`. Setiap perubahan data akibat transaksi pembeli atau pembaruan oleh admin akan langsung tersinkronisasi secara otomatis.
* 🎰 **Gacha Engine & Jaminan Pity Rate:** Mekanisme penukaran poin hasil belanja menjadi tiket undian berhadiah kustom. Peluang acak dihitung menggunakan fungsi matematika *Pseudo-Random Number Generator* (RNG) yang dibagi menjadi tiga tier kelangkaan (*R, SR, SSR*) serta dilengkapi jaminan garansi item langka (*Pity System*) pada penukaran paket tertentu.
* 🎮 **Maneki Neko Engine (20FPS Arcade):** Game interaktif penangkap koin emas yang dirender langsung menggunakan teknik pemformatan string tunggal tunggal (*Double Buffering Text*) serta penyembunyian kursor (`\033[?25l`), menghasilkan pergerakan animasi koin yang mulus tanpa kedipan terminal.
* 📊 **Live Stock Bar Chart Visualizer:** Representasi kondisi stok barang kritis (stok $\le 5$) menggunakan diagram batang live horizontal warna-warni yang memanfaatkan karakter Unicode (█) serta penawaran restok otomatis bagi admin.

---

## 🗂️ 3. Arsitektur Kode & Pembagian Kerja

Proyek ini dibangun secara terfragmentasi agar kode tetap bersih, mudah didebug, dan mempermudah kolaborasi antar anggota kelompok.

```text
📁 Smart-Cafe-Project
├── 📄 main.cpp                 # Root controller & Gerbang Utama Pemilihan Peran
├── 📄 utilitas.cpp             # Macro Warna ANSI, Input Sterilization, & Fungsi Pendukung
├── 📄 admin 1.cpp              # Autentikasi Admin Gate & Fitur Input Tambah Barang Baru
├── 📄 AdminBagian2cpp.cpp      # Logika Manipulasi Data Array Barang & Live Bar Chart
├── 📄 customerTransaction.cpp  # Alur Belanja Customer, Hitung Pajak 11%, & Nota Digital
├── 📄 poin.cpp                 # Ledger Saldo Loyalty Poin & Manajemen Riwayat Omzet
├── 📄 undian.cpp               # RNG Gacha Database, Rarity Rate, & Manajemen Hadiah
├── 📄 minigame.cpp             # Engine Sinkronisasi Frame Animasi Game Maneki Neko
├── 📄 data_atmint.txt          # Database Akun Admin (Secure Integer Token)
└── 📄 stok_barang.txt          # Database Stok Barang (Format CSV)

```

**Kontributor Proyek & Tanggung Jawab (Informatika UNRAM):**

| Nama Kontributor | Modul / Berkas | Tanggung Jawab Utama |
| :--- | :--- | :--- |
| **Tim Kelompok** | `main.cpp`, `utilitas.cpp` | Arsitektur utama program, standardisasi fungsi pembantu, visualisasi UI cyberpunk, dan manajemen *error handling* global. |
| **Ni Ketut Intan Ayu Widyastuti** | `admin 1.cpp` | Logika gerbang masuk admin, validasi struktur format NIM, dan pembuatan fungsi input penambahan menu baru. |
| **Hari Fitratullah** | `AdminBagian2cpp.cpp` | Logika manipulasi pointer data array barang untuk proses pencarian, penyuntingan (*Edit*), penghapusan (*Delete*), serta pembuatan grafik stok *live*. |
| **Baiq Nur Saqinah Kamila** | `customerTransaction.cpp` | Alur antarmuka transaksi pembeli, kalkulasi total belanja ditambah pajak restoran 11% + biaya layanan, dan format visual nota digital. |
| **Rizka Dzuliyatun Ni'mah** | `undian.cpp` | Manajemen struktur data hadiah gacha global, penentuan persentase acak probabilitas hadiah, dan menu penukaran *loyalty* poin. |
| **I Dewa Made Krinayana Wicaksana** | `poin.cpp` | Modul perhitungan penambahan poin *loyalty* (tiap kelipatan Rp 10.000) serta pencatatan akumulasi pendapatan omzet kafe harian. |
| **M. Pradifta Arizona** | `minigame.cpp` | Perancangan sistem input *keyboard* instan tanpa *enter* (`kbhit`), *pre-rendering* string animasi koin, dan sinkronisasi kuota *Buff Draw* SSR. |

---

## 💻 4. Panduan Git & Kompilasi (Untuk Pemula / Orang Awam)

Bagi anggota kelompok atau penguji yang belum terbiasa menggunakan Git dan Terminal, ikuti panduan langkah demi langkah di bawah ini dengan seksama.

### A. Persiapan Awal (Hanya Dilakukan Sekali)

Sebelum menjalankan perintah, pastikan komputer Anda sudah terinstal berkas **Git** dan compiler C++ (**g++ / MinGW**).

### B. Mengambil Salinan Kode dari GitHub (Clone)

Proses ini digunakan untuk mendownload seluruh folder proyek dari internet ke komputer Anda untuk pertama kali.

1. Buka aplikasi **Command Prompt (CMD)** atau **PowerShell** di laptop Anda.
2. Ketik perintah di bawah ini untuk berpindah tempat ke lokasi folder yang Anda inginkan (misal: folder *Cihuy*):
```bash
cd Cihuy

```
3. Salin dan jalankan perintah di bawah ini untuk mendownload folder proyek:
```bash
git clone [https://github.com/username-kalian/nama-repo-kafe.git](https://github.com/username-kalian/nama-repo-kafe.git)

```
4. Masuk ke dalam folder proyek yang berhasil didownload dengan mengetik:
```bash
cd nama-repo-kafe

```
### C. Mengambil Pembaruan Kode Terbaru (Pull)

Jika ada anggota kelompok lain yang melakukan pembaruan kode atau perbaikan bug di GitHub, Anda tidak perlu mendownload ulang dari awal. Cukup sinkronkan folder Anda dengan langkah berikut:

1. Buka CMD/PowerShell tepat di dalam folder proyek Anda.
2. Ketik perintah ajaib ini lalu tekan enter:
```bash
git pull origin main

```
3. Secara otomatis, Git akan mendownload baris kode yang berubah saja dan menggabungkannya ke komputer Anda tanpa merusak file yang lain.

### D. Melakukan Kompilasi (Compile Program)

Bahasa C++ adalah bahasa pemrograman tradisional yang kodenya harus diubah menjadi file aplikasi (`.exe`) terlebih dahulu agar bisa dijalankan oleh sistem operasi.

1. Pastikan posisi CMD/PowerShell Anda berada di dalam folder tempat file `main.cpp` berada.
2. Jalankan perintah kompilasi di bawah ini:
```bash
g++ main.cpp -o SmartCafeApp

```
*Keterangan:* Perintah ini menyuruh compiler `g++` untuk membaca file pusat `main.cpp` (yang otomatis akan menarik file `.cpp` modular lainnya) dan membungkusnya menjadi satu file aplikasi utuh bernama `SmartCafeApp`.

### E. Menjalankan Aplikasi (Run)

Setelah proses kompilasi selesai tanpa memunculkan pesan error, jalankan aplikasinya dengan perintah berikut:

* **Di OS Windows (PowerShell / CMD):**
```bash
.\SmartCafeApp.exe

```


* **Di OS Linux / MacOS (Terminal):**
```bash
./SmartCafeApp

```
---

## 📢 5. Catatan Penting Pengujian UI Terminal

Aplikasi ini memanfaatkan visualisasi modern berbasis grafis teks biner. Agar program dapat merender warna dan karakter balok secara sempurna di sistem operasi **Windows**, kode program telah disuntikkan fungsi `system("chcp 65001 > nul")` secara otomatis di baris awal fungsi `main()`.

Fungsi ini memaksa jendela terminal Windows (CMD/PowerShell) untuk langsung beralih ke mode encoding **UTF-8**, sehingga:

1. Karakter grafik diagram batang stok `█` tidak akan berubah menjadi karakter kotak hancur atau tanda tanya (`?`).
2. Gradien warna diagonal cyberpunk *True Color 24-bit* dapat menyala dengan tajam, rapi, dan presisi di layar monitor penguji.

---

## 🦅 RESTRICTED AREA 

<details>
<summary><b>👉 YANG KLIK DAPAT NILAI E 👈</b></summary>
<br>

**SYSTEM OVERRIDE ACCEPTED...** Selamat! Anda telah mengaktifkan *Easter Egg* (yang sama sekali tidak rahasia) di dalam repositori ini. 

Sebagai bentuk transparansi, berikut adalah *Developer Logs* yang sesungguhnya di balik pembuatan Smart Cafe ini:

1. **Kutukan Terbesar :** Terjebak *bug* enkripsi biner XOR di OS Windows selama berjam jam karena nama inisial "C" menghasilkan *End-Of-File* (`\x1A`), dan inisial "A" memicu tombol *Enter* gaib (***asli ngeselin banget bagian ni, Dipakein AI pun tambah ngebug cok***). 
2. **Pesan Sponsor :** *"May The Emperor Protects this Source Code."*

Jika Anda tersenyum membaca ini, kami sangat mengapresiasi waktu Anda memeriksa kode kami. Sebuah nilai **A** akan sangat membantu menyembuhkan trauma kami terhadap manipulasi *string* di C++. 

*Only in death does duty end....🦅⚜️*
</details>
