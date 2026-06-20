#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
    #ifndef kbhit
        #define kbhit _kbhit
    #endif
    #ifndef getch
        #define getch _getch
    #endif
#endif

#if !defined(_WIN32) && !defined(_WIN64)
int kbhit_posix() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
#endif

bool mainkan_game_maneki_catch() {
    cls();
    cetak_banner();
    cetakTengah("=====================================================");
    cetakTengah("MINI GAME: MANEKI NEKO'S GOLDEN COIN CATCH");
    cetakTengah("=====================================================");
    cout << "\n";
    cetak_opsi_tengah("Tangkap koin emas yang meluncur dari kiri ke kanan!");
    cetak_opsi_tengah("Ketuk [ SPACEBAR ] tepat saat koin 'o' berada di tengah '|'!");
    cout << "\n";
    cetak_opsi_tengah("Tekan [ ENTER ] untuk mengaktifkan mesin koin...");
    cetakTengah("-----------------------------------------------------");
    
    cin.get();

    int nyawa = 3;
    int skor_koin = 0;
    int posisi_koin = 0;
    int batas_lebar = 30;
    int kecepatan = 50;

    int lebar_terminal = 112;
    int s = (lebar_terminal - batas_lebar) / 2;
    string pad(s > 0 ? s : 0, ' ');

    cout << "\n\n\n\n\n\n";

while (nyawa > 0 && skor_koin < 3) {
        cout << "\033[6A";

        // Perbaikan posisi \033[K dipindah ke depan setelah pad
        cout << pad << "\033[K        /\\_/\\     \n";
        cout << pad << "\033[K       ( o.o )    \n";
        cout << pad << "\033[K        \\ _ /     \n";

        cout << pad << "\033[K  [";
        for (int j = 0; j < batas_lebar; j++) {
            if (j == posisi_koin) {
                cout << KUNING << "o" << RESET;
            } else if (j == 15) {
                cout << CYAN << "|" << RESET;
            } else {
                cout << "-";
            }
        }
        cout << "]\n";

        cout << pad << "\033[K   Mangkuk: [   |   ] \n";

        string s_status = "Koin Tertangkap: " + to_string(skor_koin) + " / 3  |  Sisa Kesempatan: " + to_string(nyawa);
        int s_center = (lebar_terminal - s_status.length()) / 2;
        string pad_status(s_center > 0 ? s_center : 0, ' ');
        cout << "\r" << pad_status << "\033[K" << s_status << flush;

        bool tombol_ditekan = false;
#if defined(_WIN32) || defined(_WIN64)
        if (kbhit()) {
            if (getch() == ' ') tombol_ditekan = true;
        }
#else
        if (kbhit_posix()) {
            struct termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            int ch = getchar();
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            if (ch == ' ') tombol_ditekan = true;
        }
#endif

        if (tombol_ditekan) {
            if (posisi_koin >= 14 && posisi_koin <= 16) {
                skor_koin++;
                kecepatan -= 8; 
                posisi_koin = 0; 
            } else {
                nyawa--;
                posisi_koin = 0;
            }
        }

        posisi_koin++;
        if (posisi_koin >= batas_lebar) {
            posisi_koin = 0;
        }

        this_thread::sleep_for(chrono::milliseconds(kecepatan));
    }

    cls();
    cetak_banner();
    cetakTengah("=====================================================");
    cetakTengah("KEPUTUSAN REZEKI MANEKI NEKO");
    cetakTengah("=====================================================");
    cout << "\n";

    if (skor_koin >= 3) {
        cetak_opsi_tengah(HIJAU "[✓] BERHASIL! Mangkuk Anda penuh terisi koin keberuntungan." RESET);
        cetak_opsi_tengah("Maneki Neko mengaktifkan Buff Pity SSR (+5%) untuk 3 Draw!");
        cout << "\n";
        cetakTengah("=====================================================");
        pause();
        return true;
    } else {
        cetak_opsi_tengah(MERAH "[!] GAGAL! Koin berjatuhan berserakan di lantai kafe." RESET);
        cetak_opsi_tengah("Gagal menyelaraskan ritme (Kau orang sial btw).");
        cout << "\n";
        cetakTengah("=====================================================");
        pause();
        return false;
    }
}