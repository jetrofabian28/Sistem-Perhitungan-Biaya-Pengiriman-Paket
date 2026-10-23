# Proses Integrasi Program

**Mata Kuliah:** Algoritma dan Pengantar Pemrograman (SSI1144)
**Program Studi:** Sistem Informasi - Universitas Ma Chung
**Studi Kasus 04:** Sistem Perhitungan Biaya Pengiriman Paket
**Penanggung jawab:**
- Fabian Jethro Falah Kalangi - 322610015
- Aning Dwi Setyowati - 322610002

---

## 1. Gambaran Singkat

Program dibangun dari dua bagian yang awalnya ditulis terpisah:

- **Modul A (Proses Utama):** menerima data satu paket, memeriksa kebenarannya, lalu menghitung berat tagihan, biaya dasar, tambahan layanan prioritas, biaya asuransi, dan total biaya.
- **Modul B (Rekapitulasi):** mengumpulkan hasil dari seluruh paket menjadi laporan akhir, yaitu jumlah paket per zona dan layanan, total berat, total asuransi, total pendapatan, jumlah paket berat volumetrik, dan paket dengan biaya tertinggi.

Proses integrasi menyatukan keduanya menjadi satu program: setiap paket yang selesai dihitung oleh Modul A langsung diserahkan kepada Modul B, dan laporan akhir dicetak setelah paket terakhir diproses. Dengan begitu, pengguna melihat rincian biaya setiap paket sekaligus mendapat ringkasan keseluruhan tanpa perlu menjalankan dua program.

---

## 2. Titik Temu Kedua Modul

Kedua modul bertemu pada satu paket data bernama `HasilPaket`. Modul A mengisinya, Modul B hanya membacanya. Karena itu, Modul B tidak perlu mengetahui tarif, rumus berat volumetrik, ataupun aturan asuransi.

| Isi `HasilPaket` | Diisi oleh | Dipakai Modul B untuk |
|------------------|------------|-----------------------|
| `nomorPaket` | Modul A | Mencatat paket dengan biaya tertinggi |
| `zona` | Modul A | Menambah pencacah zona A, B, atau C |
| `jenisPelayanan` | Modul A | Menambah pencacah reguler atau prioritas |
| `beratAktual` dan `beratVolumetrik` | Modul A | Menentukan apakah paket memakai berat volumetrik, dan menjumlahkan berat aktual |
| `beratTagihan` | Modul A | Menjumlahkan total berat tagihan |
| `biayaAsuransi` | Modul A | Menjumlahkan total asuransi |
| `totalBiaya` | Modul A | Menjumlahkan total pendapatan dan mencari biaya tertinggi |

Jalur data satu paket:

`Pengguna` → `DataPaket` → `hitungBiaya()` → `HasilPaket` → `perbaruiRekap()` → `RekapPengiriman` → laporan akhir

---

## 3. Tahapan Penggabungan

| Tahap | Kegiatan | Hasil |
|-------|----------|-------|
| 1 | Menentukan data yang berpindah antarmodul | Struct `HasilPaket` sebagai satu-satunya jembatan |
| 2 | Memecah Modul A menjadi bagian-bagian kecil | Fungsi `bacaDataPaket()`, `tarifZona()`, `hitungBiaya()`, dan `tampilkanRincian()` |
| 3 | Memecah Modul B menjadi bagian-bagian kecil | Struct `RekapPengiriman` serta fungsi `perbaruiRekap()` dan `tampilkanRekapitulasi()` |
| 4 | Menyusun program utama | `main()` hanya mengatur urutan pemanggilan, tanpa rumus perhitungan |
| 5 | Menyelaraskan aturan validasi | Rekap hanya diperbarui jika data paket lolos pemeriksaan |
| 6 | Membandingkan hasil sebelum dan sesudah digabung | Keluaran program gabungan sama dengan hasil kedua modul yang dijalankan terpisah |

---

## 4. Urutan Eksekusi dalam Program Gabungan

Program membaca jumlah paket lebih dulu. Setelah itu, setiap putaran perulangan memproses satu paket dengan urutan tetap:

| Urutan | Fungsi yang dipanggil | Modul | Keterangan |
|--------|-----------------------|-------|------------|
| 1 | `bacaDataPaket()` | A | Membaca dan memeriksa sembilan masukan. Jika ada yang salah, program berhenti dengan pesan kesalahan |
| 2 | `hitungBiaya()` | A | Menyusun `HasilPaket` berisi seluruh komponen biaya |
| 3 | `tampilkanRincian()` | A | Menampilkan rincian biaya paket kepada pengguna |
| 4 | `perbaruiRekap()` | B | Menambahkan hasil paket ke catatan rekapitulasi |
| 5 | (ulangi ke urutan 1) | - | Berlanjut sampai paket terakhir |
| 6 | `tampilkanRekapitulasi()` | B | Dipanggil satu kali setelah perulangan selesai |

---

## 5. Pembagian Peran Fungsi

| Fungsi | Peran |
|--------|-------|
| `bacaDataPaket` | Pintu masuk data dan penjaga kualitas masukan |
| `tarifZona` | Penentu tarif per kilogram menurut zona (A Rp8.000, B Rp12.000, C Rp18.000) |
| `hitungBiaya` | Pusat seluruh rumus biaya: berat volumetrik, pembulatan berat tagihan, tambahan prioritas 40%, asuransi 1% minimal Rp5.000 |
| `tampilkanRincian` | Penyaji hasil per paket |
| `perbaruiRekap` | Pencatat: menambah pencacah, menjumlahkan total, dan menjaga rekor biaya tertinggi |
| `tampilkanRekapitulasi` | Penyaji laporan akhir |
| `main` | Pengatur alur dari awal sampai akhir |

---

## 6. Penjaga Konsistensi Data

Beberapa aturan dipasang agar hasil rekapitulasi selalu sesuai dengan hasil per paket:

1. **Rekap hanya menerima data yang valid.** `perbaruiRekap()` dipanggil setelah `bacaDataPaket()` berhasil dan biaya selesai dihitung, sehingga data yang salah tidak pernah masuk ke total.
2. **Nilai awal biaya tertinggi -1.** Paket pertama, berapa pun biayanya, pasti tercatat sebagai yang tertinggi sebelum dibandingkan dengan paket berikutnya.
3. **Satu sumber rumus.** Seluruh perhitungan biaya hanya ada di `hitungBiaya()`. Modul B tidak menghitung ulang, sehingga tidak ada selisih antara rincian paket dan total rekap.
4. **Pembulatan aman.** Berat tagihan dihitung dengan `ceil(... - 1e-9)` agar bilangan desimal seperti 5,0000000001 tidak naik menjadi 6.
5. **Berhenti saat masukan salah.** Jika jumlah paket atau data paket tidak valid, program menampilkan pesan kesalahan lalu berhenti sehingga tidak menampilkan rekapitulasi yang tidak lengkap.

---

## 7. Perubahan Sebelum dan Sesudah Integrasi

| Aspek | Sebelum digabung | Sesudah digabung |
|-------|------------------|------------------|
| Bentuk program | Dua bagian terpisah | Satu program yang berjalan sekali jalan |
| Perpindahan data | Dicatat atau dipindahkan manual | Otomatis melalui `HasilPaket` |
| Susunan kode | Logika bercampur di satu fungsi | Dibagi per fungsi dengan peran jelas |
| Hasil bagi pengguna | Rincian dan rekap dilihat terpisah | Rincian tiap paket dan rekap akhir dalam satu eksekusi |
| Keandalan rekap | Bisa terpengaruh data yang belum lengkap | Hanya memuat paket yang valid dan sudah selesai dihitung |

---

## 8. Source Code Program Terintegrasi

Berkas: `integrasi.cpp` (bahasa C++).

```cpp
// Studi Kasus 04 - Sistem Perhitungan Biaya Pengiriman Paket
// Program Terintegrasi: Modul A (Proses Utama) + Modul B (Rekapitulasi)
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

---

## 9. Cara Menjalankan

```bash
g++ -o integrasi integrasi.cpp
./integrasi
```

---

## 10. Contoh Keluaran Akhir

Contoh untuk tiga paket (PK001 reguler zona A, PK002 prioritas zona B, PK003 reguler zona C):

```text
========== REKAPITULASI PENGIRIMAN ==========
Jumlah paket zona A: 1
Jumlah paket zona B: 1
Jumlah paket zona C: 1
Jumlah paket reguler: 2
Jumlah paket prioritas: 1
Total berat aktual: 9.70 kg
Total berat tagihan: 18.00 kg
Paket menggunakan berat volumetrik: 1
Total asuransi: Rp 25000.00
Total pendapatan: Rp 307000.00
Paket dengan biaya tertinggi: PK002 (Rp 188000.00)
```