**Penanggung jawab:**
- Fabian Jethro Falah Kalangi - 322610015
- Aning Dwi Setyowati - 322610002

## Source Code Program Terintegrasi

Studi Kasus 04: Sistem Perhitungan Biaya Pengiriman Paket (Modul A dan Modul B)

Repository: [Sistem-Perhitungan-Biaya-Pengiriman-Paket](https://github.com/jetrofabian28/Sistem-Perhitungan-Biaya-Pengiriman-Paket)

### 1. Source Code Lengkap

Berkas: `main.cpp` (bahasa C++).

```cpp
// Studi Kasus 04 - Sistem Perhitungan Biaya Pengiriman Paket
// Source Code Final: Modul A (Proses Utama) + Modul B (Rekapitulasi)
// Repository: https://github.com/jetrofabian28/Sistem-Perhitungan-Biaya-Pengiriman-Paket
// Penanggung jawab: Fabian Jethro Falah Kalangi - 322610015
//                   Aning Dwi Setyowati - 322610002

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// ======================= ANTARMUKA DATA =======================

// Masukan Modul A: data satu paket yang dibaca dari pengguna
struct DataPaket {
    string nomorPaket;
    double nilaiBarang;
    double beratAktual;
    double panjang;
    double lebar;
    double tinggi;
    char zona;
    int jenisPelayanan;
    char asuransi;
};

// Keluaran Modul A sekaligus masukan Modul B: hasil hitung satu paket
struct HasilPaket {
    string nomorPaket;
    char zona;
    int jenisPelayanan;
    double beratAktual;
    double beratVolumetrik;
    double beratTagihan;
    double biayaDasar;
    double biayaTambahan;
    double biayaAsuransi;
    double totalBiaya;
};

// Data rekapitulasi milik Modul B
struct RekapPengiriman {
    int zonaA = 0;
    int zonaB = 0;
    int zonaC = 0;
    int reguler = 0;
    int prioritas = 0;
    int menggunakanBeratVolumetrik = 0;
    double totalBeratAktual = 0;
    double totalBeratTagihan = 0;
    double totalAsuransi = 0;
    double totalPendapatan = 0;
    double biayaTertinggi = -1;
    string nomorPaketBiayaTertinggi = "-";
};

// ======================= MODUL A: PROSES UTAMA =======================

const double TARIF_ZONA_A = 8000;
const double TARIF_ZONA_B = 12000;
const double TARIF_ZONA_C = 18000;

// Membaca dan memvalidasi data satu paket.
// Mengembalikan false (disertai pesan kesalahan) bila ada masukan tidak valid.
bool bacaDataPaket(DataPaket &data) {
    cout << "Masukkan Nomor Paket: ";
    if (!(cin >> data.nomorPaket)) {
        cerr << "Nomor paket tidak valid." << endl;
        return false;
    }

    cout << "Masukkan nilai Barang (Rp): ";
    if (!(cin >> data.nilaiBarang) || !isfinite(data.nilaiBarang) || data.nilaiBarang < 0) {
        cerr << "Nilai barang harus berupa angka yang tidak negatif." << endl;
        return false;
    }

    cout << "Masukkan Berat Aktual (kg): ";
    if (!(cin >> data.beratAktual) || !isfinite(data.beratAktual) || data.beratAktual <= 0) {
        cerr << "Berat aktual harus berupa angka lebih dari 0." << endl;
        return false;
    }

    cout << "Masukkan Panjang (cm): ";
    if (!(cin >> data.panjang) || !isfinite(data.panjang) || data.panjang <= 0) {
        cerr << "Panjang harus berupa angka lebih dari 0." << endl;
        return false;
    }

    cout << "Masukkan Lebar (cm): ";
    if (!(cin >> data.lebar) || !isfinite(data.lebar) || data.lebar <= 0) {
        cerr << "Lebar harus berupa angka lebih dari 0." << endl;
        return false;
    }

    cout << "Masukkan Tinggi (cm): ";
    if (!(cin >> data.tinggi) || !isfinite(data.tinggi) || data.tinggi <= 0) {
        cerr << "Tinggi harus berupa angka lebih dari 0." << endl;
        return false;
    }

    cout << "Masukkan Zona Tujuan (A/B/C): ";
    if (!(cin >> data.zona)) {
        cerr << "Zona tujuan tidak valid." << endl;
        return false;
    }
    data.zona = static_cast<char>(toupper(static_cast<unsigned char>(data.zona)));
    if (data.zona != 'A' && data.zona != 'B' && data.zona != 'C') {
        cerr << "Zona tujuan harus A, B, atau C." << endl;
        return false;
    }

    cout << "Jenis Pelayanan (1. Reguler, 2. Prioritas): ";
    if (!(cin >> data.jenisPelayanan) ||
        (data.jenisPelayanan != 1 && data.jenisPelayanan != 2)) {
        cerr << "Jenis pelayanan harus 1 (Reguler) atau 2 (Prioritas)." << endl;
        return false;
    }

    cout << "Apakah ingin menggunakan asuransi? (Y/N): ";
    if (!(cin >> data.asuransi)) {
        cerr << "Pilihan asuransi tidak valid." << endl;
        return false;
    }
    data.asuransi = static_cast<char>(toupper(static_cast<unsigned char>(data.asuransi)));
    if (data.asuransi != 'Y' && data.asuransi != 'N') {
        cerr << "Pilihan asuransi harus Y atau N." << endl;
        return false;
    }

    return true;
}

// Menentukan tarif per kg berdasarkan zona tujuan
double tarifZona(char zona) {
    if (zona == 'A') return TARIF_ZONA_A;
    if (zona == 'B') return TARIF_ZONA_B;
    return TARIF_ZONA_C;
}

// Menghitung seluruh komponen biaya satu paket
HasilPaket hitungBiaya(const DataPaket &data) {
    HasilPaket hasil;
    hasil.nomorPaket = data.nomorPaket;
    hasil.zona = data.zona;
    hasil.jenisPelayanan = data.jenisPelayanan;
    hasil.beratAktual = data.beratAktual;
    hasil.beratVolumetrik = (data.panjang * data.lebar * data.tinggi) / 6000;
    // 1e-9 mencegah kesalahan pembulatan floating point (mis. 5.0000000001 -> 6)
    hasil.beratTagihan = ceil(max(hasil.beratAktual, hasil.beratVolumetrik) - 1e-9);
    hasil.biayaDasar = hasil.beratTagihan * tarifZona(data.zona);
    hasil.biayaTambahan = (data.jenisPelayanan == 2) ? 0.40 * hasil.biayaDasar : 0;
    hasil.biayaAsuransi = (data.asuransi == 'Y') ? max(0.01 * data.nilaiBarang, 5000.0) : 0;
    hasil.totalBiaya = hasil.biayaDasar + hasil.biayaTambahan + hasil.biayaAsuransi;
    return hasil;
}

// Menampilkan rincian biaya satu paket
void tampilkanRincian(const HasilPaket &hasil) {
    cout << "\n--- Rincian Biaya Paket " << hasil.nomorPaket << " ---" << endl;
    cout << "Zona tujuan: " << hasil.zona << endl;
    cout << "Berat volumetrik: " << hasil.beratVolumetrik << " kg" << endl;
    cout << "Berat tagihan: " << hasil.beratTagihan << " kg" << endl;
    cout << "Biaya dasar: Rp " << hasil.biayaDasar << endl;
    cout << "Biaya tambahan pelayanan: Rp " << hasil.biayaTambahan << endl;
    cout << "Biaya asuransi: Rp " << hasil.biayaAsuransi << endl;
    cout << "Total biaya: Rp " << hasil.totalBiaya << endl;
}

// ======================= MODUL B: REKAPITULASI =======================

// Memperbarui rekapitulasi dengan hasil satu paket
void perbaruiRekap(RekapPengiriman &rekap, const HasilPaket &hasil) {
    if (hasil.zona == 'A') ++rekap.zonaA;
    else if (hasil.zona == 'B') ++rekap.zonaB;
    else ++rekap.zonaC;

    if (hasil.jenisPelayanan == 1) ++rekap.reguler;
    else ++rekap.prioritas;

    if (hasil.beratVolumetrik > hasil.beratAktual) {
        ++rekap.menggunakanBeratVolumetrik;
    }

    rekap.totalBeratAktual += hasil.beratAktual;
    rekap.totalBeratTagihan += hasil.beratTagihan;
    rekap.totalAsuransi += hasil.biayaAsuransi;
    rekap.totalPendapatan += hasil.totalBiaya;

    if (hasil.totalBiaya > rekap.biayaTertinggi) {
        rekap.biayaTertinggi = hasil.totalBiaya;
        rekap.nomorPaketBiayaTertinggi = hasil.nomorPaket;
    }
}

// Menampilkan laporan rekapitulasi
void tampilkanRekapitulasi(const RekapPengiriman &rekap) {
    cout << "\n========== REKAPITULASI PENGIRIMAN ==========" << endl;
    cout << "Jumlah paket zona A: " << rekap.zonaA << endl;
    cout << "Jumlah paket zona B: " << rekap.zonaB << endl;
    cout << "Jumlah paket zona C: " << rekap.zonaC << endl;
    cout << "Jumlah paket reguler: " << rekap.reguler << endl;
    cout << "Jumlah paket prioritas: " << rekap.prioritas << endl;
    cout << "Total berat aktual: " << rekap.totalBeratAktual << " kg" << endl;
    cout << "Total berat tagihan: " << rekap.totalBeratTagihan << " kg" << endl;
    cout << "Paket menggunakan berat volumetrik: "
         << rekap.menggunakanBeratVolumetrik << endl;
    cout << "Total asuransi: Rp " << rekap.totalAsuransi << endl;
    cout << "Total pendapatan: Rp " << rekap.totalPendapatan << endl;
    cout << "Paket dengan biaya tertinggi: " << rekap.nomorPaketBiayaTertinggi
         << " (Rp " << rekap.biayaTertinggi << ")" << endl;
}

// ======================= PROGRAM UTAMA (INTEGRASI) =======================

int main() {
    int jumlahPaket;
    cout << "Masukkan jumlah paket: ";
    if (!(cin >> jumlahPaket) || jumlahPaket <= 0) {
        cerr << "Jumlah paket harus berupa bilangan bulat lebih dari 0." << endl;
        return 1;
    }

    cout << fixed << setprecision(2);
    RekapPengiriman rekap;

    for (int i = 1; i <= jumlahPaket; ++i) {
        cout << "\n=== Data Paket " << i << " ===" << endl;

        DataPaket data;
        if (!bacaDataPaket(data)) {                // Modul A: masukan + validasi
            return 1;
        }

        HasilPaket hasil = hitungBiaya(data);      // Modul A: perhitungan biaya
        tampilkanRincian(hasil);                   // Modul A: rincian per paket
        perbaruiRekap(rekap, hasil);               // Modul B: akumulasi rekap
    }

    tampilkanRekapitulasi(rekap);                  // Modul B: laporan akhir
    return 0;
}
```

### 2. Penjelasan Struktur Program

Program disusun dalam empat lapisan dari atas ke bawah.

| Lapisan | Isi | Penjelasan |
|---------|-----|------------|
| 1. Antarmuka data | `DataPaket`, `HasilPaket`, `RekapPengiriman` | Tiga struct yang menampung masukan, hasil hitung satu paket, dan rekapitulasi |
| 2. Modul A | `bacaDataPaket()`, `tarifZona()`, `hitungBiaya()`, `tampilkanRincian()` | Membaca dan memvalidasi data, menentukan tarif, menghitung biaya, dan menampilkan rincian per paket |
| 3. Modul B | `perbaruiRekap()`, `tampilkanRekapitulasi()` | Mengakumulasi hasil tiap paket dan menampilkan laporan akhir |
| 4. Program utama | `main()` | Membaca jumlah paket, mengulang proses tiap paket, lalu mencetak rekapitulasi |

#### 2.1 Antarmuka Data

- `DataPaket`: nomor paket, nilai barang, berat aktual, panjang, lebar, tinggi, zona, jenis pelayanan, dan pilihan asuransi. Diisi oleh `bacaDataPaket()`.
- `HasilPaket`: nomor paket, zona, jenis pelayanan, berat aktual, berat volumetrik, berat tagihan, biaya dasar, biaya tambahan, biaya asuransi, dan total biaya. Diisi oleh `hitungBiaya()` dan dibaca oleh `perbaruiRekap()`.
- `RekapPengiriman`: pencacah zona dan layanan, jumlah paket berat volumetrik, total berat aktual dan tagihan, total asuransi, total pendapatan, serta biaya tertinggi beserta nomor paketnya. Nilai awal `biayaTertinggi` adalah -1 agar paket pertama pasti tercatat sebagai yang tertinggi.

#### 2.2 Modul A: Proses Utama

- `bacaDataPaket()` membaca sembilan masukan dan memeriksa tiap masukan (angka valid, batas nilai, zona A/B/C, layanan 1 atau 2, asuransi Y atau N). Fungsi mengembalikan `false` disertai pesan kesalahan jika ada yang tidak valid.
- `tarifZona()` mengembalikan tarif per kg: zona A Rp8.000, zona B Rp12.000, zona C Rp18.000.
- `hitungBiaya()` menghitung berat volumetrik = (panjang x lebar x tinggi) / 6000, berat tagihan = nilai terbesar antara berat aktual dan volumetrik dibulatkan ke atas, biaya dasar = berat tagihan x tarif, tambahan layanan prioritas 40% dari biaya dasar, asuransi 1% dari nilai barang dengan minimum Rp5.000, lalu total biaya.
- `tampilkanRincian()` mencetak rincian biaya satu paket.

#### 2.3 Modul B: Rekapitulasi

- `perbaruiRekap()` menambah pencacah zona dan layanan, menambah pencacah paket berat volumetrik bila berat volumetrik melebihi berat aktual, menjumlahkan berat, asuransi, dan pendapatan, lalu memperbarui paket dengan biaya tertinggi.
- `tampilkanRekapitulasi()` mencetak seluruh isi rekap sebagai laporan akhir.

#### 2.4 Program Utama

`main()` membaca jumlah paket (harus bilangan bulat lebih dari 0), menyiapkan rekap kosong, lalu mengulang untuk setiap paket: baca data, hitung biaya, tampilkan rincian, dan perbarui rekap. Setelah perulangan selesai, `main()` memanggil `tampilkanRekapitulasi()`. Jika ada masukan tidak valid, program berhenti dengan pesan kesalahan.

### 3. Hubungan Modul A dengan Modul B

Modul A dan Modul B tidak saling memanggil. Keduanya dihubungkan oleh `main()` melalui struct `HasilPaket`.

| Langkah | Modul | Data yang bergerak |
|---------|-------|--------------------|
| 1 | A | Pengguna mengisi `DataPaket` melalui `bacaDataPaket()` |
| 2 | A | `hitungBiaya()` mengubah `DataPaket` menjadi `HasilPaket` |
| 3 | A | `tampilkanRincian()` menampilkan `HasilPaket` kepada pengguna |
| 4 | B | `perbaruiRekap()` membaca `HasilPaket` dan menambahkannya ke `RekapPengiriman` |
| 5 | B | Setelah semua paket selesai, `tampilkanRekapitulasi()` menampilkan `RekapPengiriman` |

Karena Modul B hanya membaca `HasilPaket`, ia tidak perlu mengetahui tarif, rumus berat volumetrik, atau aturan asuransi. Perubahan aturan biaya cukup dilakukan di Modul A tanpa mengubah Modul B.

### 4. Cara Menjalankan

```bash
g++ -o main main.cpp
./main
```
