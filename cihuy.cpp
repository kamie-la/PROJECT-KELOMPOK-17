#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdint>

using namespace std;

struct LabelAudio {
    int32_t ukuran_total_file;
    int32_t ukuran_fmt_header = 16;
    int16_t format_audio = 1;
    int16_t jumlah_channel = 1;
    int32_t sample_rate = 44100;
    int32_t byte_per_detik;
    int16_t blok_align;
    int16_t bit_per_sampel = 16;
    int32_t ukuran_isi_suara;
};

struct NotaMusik {
    float frekuensi;
    float durasi;
};

int main() {
    const int SAMPLE_RATE = 44100;
    const float PI = 3.14159265f;
    const int VOLUME = 16000;

    vector<NotaMusik> lagu = {
        {659.25f, 0.25f}, // E5
        {622.25f, 0.25f}, // D#5
        {659.25f, 0.25f}, // E5
        {622.25f, 0.25f}, // D#5
        {659.25f, 0.25f}, // E5
        {493.88f, 0.25f}, // B4
        {587.33f, 0.25f}, // D5
        {523.25f, 0.25f}, // C5
        {440.00f, 0.50f}, // A4 (Agak panjang)
        
        {0.00f,   0.10f}, // Jeda
        
        {261.63f, 0.25f}, // C4
        {329.63f, 0.25f}, // E4
        {440.00f, 0.25f}, // A4
        {493.88f, 0.50f}, // B4 (Agak panjang)
        
        {0.00f,   0.10f}, // Jeda
        
        {329.63f, 0.25f}, // E4
        {415.30f, 0.25f}, // G#4
        {493.88f, 0.25f}, // B4
        {523.25f, 0.50f}  // C5 (Nada penutup bagian pertama)
    };

    float total_durasi_lagu = 0;
    for (int i = 0; i < lagu.size(); i++) {
        total_durasi_lagu += lagu[i].durasi;
    }
    int total_sampel = SAMPLE_RATE * total_durasi_lagu;

    vector<int16_t> wadah_suara;

    for (int n = 0; n < lagu.size(); n++) {
        float freq = lagu[n].frekuensi;
        int sampel_per_nota = SAMPLE_RATE * lagu[n].durasi;

        for (int i = 0; i < sampel_per_nota; i++) {
            float waktu = (float)i / SAMPLE_RATE;
            float gelombang = 0.0f;
            
            if (freq > 0.0f) {
                gelombang = sin(2.0f * PI * freq * waktu);
            }
            
            int16_t nilai_biner = (int16_t)(gelombang * VOLUME);
            wadah_suara.push_back(nilai_biner);
        }
    }

    LabelAudio info;
    info.ukuran_isi_suara = wadah_suara.size() * sizeof(int16_t);
    info.ukuran_total_file = info.ukuran_isi_suara + 36;
    info.byte_per_detik = SAMPLE_RATE * sizeof(int16_t);
    info.blok_align = sizeof(int16_t);

    ofstream file("cihuy.wav", ios::binary);
    if (!file) {
        cerr << "Gagal" << endl;
        return 1;
    }

    file.write("RIFF", 4);
    file.write((char*)&info.ukuran_total_file, 4);
    file.write("WAVE", 4);
    file.write("fmt ", 4);
    
    file.write((char*)&info.ukuran_fmt_header, 4);
    file.write((char*)&info.format_audio, 2);
    file.write((char*)&info.jumlah_channel, 2);
    file.write((char*)&info.sample_rate, 4);
    file.write((char*)&info.byte_per_detik, 4);
    file.write((char*)&info.blok_align, 2);
    file.write((char*)&info.bit_per_sampel, 2);
    
    file.write("data", 4);
    file.write((char*)&info.ukuran_isi_suara, 4);

    file.write((char*)wadah_suara.data(), info.ukuran_isi_suara);
    
    file.close();
    cout << "Sukses!." << endl;
    
    return 0;
}