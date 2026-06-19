# Smart Cafe - Terminal Based POS and Loyalty System

Sistem pengelolaan kasir (Point of Sales) dan manajemen loyalitas pelanggan berbasis CLI (Command Line Interface) yang dirancang secara modular menggunakan C++ standar. Proyek ini mengintegrasikan sistem inventaris admin, transaksi penjualan, pencatatan keuangan harian, akuntansi pajak, hingga visualisasi data stok secara real-time.

## Fitur Utama Sistem

1. **Manajemen Inventaris Admin**
   - Penambahan menu baru dengan pembatasan ID navigasi sistem.
   - Pembaruan informasi barang (Nama, Harga, Stok) memanfaatkan operasi pointer.
   - Penghapusan data barang menggunakan algoritma pergeseran array (shifting).

2. **Transaksi Pelanggan & POS**
   - Pemilihan item belanja interaktif berdasarkan ID menu.
   - Validasi otomatis ketersediaan stok barang sebelum transaksi diproses.
   - Pembaruan sisa stok di memori utama secara real-time setelah pembelian berhasil.

3. **Backend Keuangan & Manajemen Poin**
   - Akumulasi poin loyalitas otomatis (kelipatan Rp 10.000) ke akun global pembeli.
   - Pencatatan riwayat pengeluaran belanja harian ke dalam array global.
   - Kalkulasi total pendapatan kotor dan frekuensi transaksi harian untuk laporan admin.

4. **Mesin Nota Digital & Akuntansi (Fitur Advanced)**
   - Perhitungan otomatis Pajak Restoran (PB1) sebesar 11% dan biaya layanan.
   - Cetak struk belanja dengan penataan rata kanan-kiri yang presisi memanfaatkan manipulator `<iomanip>`.
   - Sinkronisasi tanggal dan waktu nota secara real-time berdasarkan jam internal komputer.
   - Efek suara trigger bell terminal (`\a`) saat nota dicetak.

5. **Visualisasi Grafik Stok Dinamis (Fitur Advanced)**
   - Representasi visual jumlah stok barang menggunakan grafik batang tekstual.
   - Sistem pewarnaan dinamis berbasis ANSI Escape Code (Hijau = Aman, Kuning = Sedang, Merah = Kritis).

## Struktur Arsitektur Berkas

Proyek ini menggunakan pendekatan modular di mana setiap komponen fungsional diisolasi ke dalam berkas terpisah untuk menjaga kebersihan kode:

- `main.cpp` : Kompilator pusat program, inisialisasi data, dan handler menu utama pilihan role.
- `utilitas.cpp` : Library pendukung visual, makro warna ANSI, fungsi hapus layar, jeda terminal, penataan teks tengah, grafik stok, dan mesin cetak nota digital.
- `admin 1.cpp` : Modul penambahan menu baru dan fungsi menampilkan seluruh daftar barang di kafe.
- `AdminBagian2cpp.cpp` : Modul pengeditan data barang dan penghapusan menu dari daftar inventaris.
- `poin.cpp` : Modul backend pengolah poin loyalty, array pencatat riwayat omset, dan kalkulator pendapatan admin.
- `customerTransaction.cpp` : Modul antarmuka alur belanja pembeli dan validasi kuantitas stok.

## Prasyarat Sistem

Untuk mengompilasi dan menjalankan program ini, pastikan perangkat Anda telah terpasang:
- GCC Compiler (mendukung standar C++11 atau lebih baru)
- Terminal yang mendukung ANSI Escape Code (VS Code Terminal, Windows Terminal, atau Linux Shell)

## Langkah Kompilasi dan Menjalankan Program

1. Buka terminal pada direktori tempat seluruh berkas `.cpp` proyek disimpan.
2. Jalankan perintah kompilasi dengan merujuk pada berkas utama `main.cpp`:
```bash
g++ main.cpp -o smart_cafe
```
3. Jalankan file biner yang telah berhasil terbentuk:
```bash
./smart_cafe
```
moga dapet A aminnnnnnn
