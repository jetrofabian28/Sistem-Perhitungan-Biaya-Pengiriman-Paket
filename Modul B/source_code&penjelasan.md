**Penanggung jawab:** Aning Dwi Setyowati / 322610002

## Modul B: Rekapitulasi Pengiriman

### 1. Deskripsi Singkat

Modul B bertugas merangkum seluruh paket yang sudah dihitung biayanya oleh Modul A. Setiap kali satu paket selesai diproses, datanya langsung dimasukkan ke catatan rekapitulasi, dan setelah semua paket selesai catatan itu ditampilkan sebagai laporan akhir.

Data yang direkap meliputi jumlah paket per zona, jumlah paket reguler dan prioritas, total berat aktual dan berat tagihan, jumlah paket yang memakai berat volumetrik, total asuransi, total pendapatan, serta paket dengan biaya tertinggi.

Program ditulis dalam bahasa C++ dengan memakai variabel, percabangan, perulangan, `struct`, dan fungsi sederhana.

---

### 2. Source Code Modul B

Berkas: `modul_b.cpp`. Modul B diwujudkan dalam struct `RekapPengiriman` serta fungsi `perbaruiRekap()` dan `tampilkanRekapitulasi()`.

```cpp
// Studi Kasus 04 - Sistem Perhitungan Biaya Pengiriman Paket
// Modul B: Rekapitulasi Pengiriman
// Penanggung jawab: Aning Dwi Setyowati / 322610002

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Data rekapitulasi (Modul B)
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

// Hasil perhitungan satu paket (keluaran Modul A)
struct HasilPaket {
    string nomorPaket;
    char zona;
    int jenisPelayanan;
    double beratAktual;
    double beratVolumetrik;
    double beratTagihan;
    double biayaAsuransi;
    double totalBiaya;
};

// Memperbarui rekapitulasi dengan data satu paket
void perbaruiRekap(RekapPengiriman &rekap, const HasilPaket &paket) {
    if (paket.zona == 'A') ++rekap.zonaA;
    else if (paket.zona == 'B') ++rekap.zonaB;
    else ++rekap.zonaC;

    if (paket.jenisPelayanan == 1) ++rekap.reguler;
    else ++rekap.prioritas;

    if (paket.beratVolumetrik > paket.beratAktual) {
        ++rekap.menggunakanBeratVolumetrik;
    }

    rekap.totalBeratAktual += paket.beratAktual;
    rekap.totalBeratTagihan += paket.beratTagihan;
    rekap.totalAsuransi += paket.biayaAsuransi;
    rekap.totalPendapatan += paket.totalBiaya;

    if (paket.totalBiaya > rekap.biayaTertinggi) {
        rekap.biayaTertinggi = paket.totalBiaya;
        rekap.nomorPaketBiayaTertinggi = paket.nomorPaket;
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

int main() {
    int jumlah_paket;
    cout << "Masukkan jumlah paket: ";
    if (!(cin >> jumlah_paket) || jumlah_paket <= 0) {
        cerr << "Jumlah paket harus berupa bilangan bulat lebih dari 0." << endl;
        return 1;
    }

    RekapPengiriman rekap;
    const double tarifZonaA = 8000;
    const double tarifZonaB = 12000;
    const double tarifZonaC = 18000;

    cout << fixed << setprecision(2);

    for (int i = 1; i <= jumlah_paket; ++i) {
        string nomor_paket;
        double nilai_barang, berat_aktual, panjang, lebar, tinggi;
        char zona_tujuan, pilihan_asuransi;
        int jenis_pelayanan;

        cout << "\n=== Data Paket " << i << " ===" << endl;

        cout << "Masukkan Nomor Paket: ";
        if (!(cin >> nomor_paket)) {
            cerr << "Nomor paket tidak valid." << endl;
            return 1;
        }

        cout << "Masukkan nilai Barang (Rp): ";
        if (!(cin >> nilai_barang) || !isfinite(nilai_barang) || nilai_barang < 0) {
            cerr << "Nilai barang harus berupa angka yang tidak negatif." << endl;
            return 1;
        }

        cout << "Masukkan Berat Aktual (kg): ";
        if (!(cin >> berat_aktual) || !isfinite(berat_aktual) || berat_aktual <= 0) {
            cerr << "Berat aktual harus berupa angka lebih dari 0." << endl;
            return 1;
        }

        cout << "Masukkan Panjang (cm): ";
        if (!(cin >> panjang) || !isfinite(panjang) || panjang <= 0) {
            cerr << "Panjang harus berupa angka lebih dari 0." << endl;
            return 1;
        }

        cout << "Masukkan Lebar (cm): ";
        if (!(cin >> lebar) || !isfinite(lebar) || lebar <= 0) {
            cerr << "Lebar harus berupa angka lebih dari 0." << endl;
            return 1;
        }

        cout << "Masukkan Tinggi (cm): ";
        if (!(cin >> tinggi) || !isfinite(tinggi) || tinggi <= 0) {
            cerr << "Tinggi harus berupa angka lebih dari 0." << endl;
            return 1;
        }

        cout << "Masukkan Zona Tujuan (A/B/C): ";
        if (!(cin >> zona_tujuan)) {
            cerr << "Zona tujuan tidak valid." << endl;
            return 1;
        }
        zona_tujuan = static_cast<char>(toupper(static_cast<unsigned char>(zona_tujuan)));

        double tarif_per_kg;
        if (zona_tujuan == 'A') tarif_per_kg = tarifZonaA;
        else if (zona_tujuan == 'B') tarif_per_kg = tarifZonaB;
        else if (zona_tujuan == 'C') tarif_per_kg = tarifZonaC;
        else {
            cerr << "Zona tujuan harus A, B, atau C." << endl;
            return 1;
        }

        cout << "Jenis Pelayanan (1. Reguler, 2. Prioritas): ";
        if (!(cin >> jenis_pelayanan) ||
            (jenis_pelayanan != 1 && jenis_pelayanan != 2)) {
            cerr << "Jenis pelayanan harus 1 (Reguler) atau 2 (Prioritas)." << endl;
            return 1;
        }

        cout << "Apakah ingin menggunakan asuransi? (Y/N): ";
        if (!(cin >> pilihan_asuransi)) {
            cerr << "Pilihan asuransi tidak valid." << endl;
            return 1;
        }
        pilihan_asuransi = static_cast<char>(toupper(static_cast<unsigned char>(pilihan_asuransi)));
        if (pilihan_asuransi != 'Y' && pilihan_asuransi != 'N') {
            cerr << "Pilihan asuransi harus Y atau N." << endl;
            return 1;
        }

        // Modul A: perhitungan biaya
        const double berat_volumetrik = (panjang * lebar * tinggi) / 6000;
        const double berat_tagihan = ceil(max(berat_aktual, berat_volumetrik) - 1e-9);
        const double biaya_dasar = berat_tagihan * tarif_per_kg;
        const double biaya_tambahan = (jenis_pelayanan == 2) ? 0.40 * biaya_dasar : 0;
        double biaya_asuransi = 0;
        if (pilihan_asuransi == 'Y') {
            biaya_asuransi = max(0.01 * nilai_barang, 5000.0);
        }
        const double total_biaya = biaya_dasar + biaya_tambahan + biaya_asuransi;

        // Modul B: perbarui rekapitulasi
        HasilPaket paket = {nomor_paket, zona_tujuan, jenis_pelayanan,
                            berat_aktual, berat_volumetrik, berat_tagihan,
                            biaya_asuransi, total_biaya};
        perbaruiRekap(rekap, paket);

        cout << "\n--- Rincian Biaya Paket " << nomor_paket << " ---" << endl;
        cout << "Zona tujuan: " << zona_tujuan << endl;
        cout << "Berat volumetrik: " << berat_volumetrik << " kg" << endl;
        cout << "Berat tagihan: " << berat_tagihan << " kg" << endl;
        cout << "Biaya dasar: Rp " << biaya_dasar << endl;
        cout << "Biaya tambahan pelayanan: Rp " << biaya_tambahan << endl;
        cout << "Biaya asuransi: Rp " << biaya_asuransi << endl;
        cout << "Total biaya: Rp " << total_biaya << endl;
    }

    // Modul B: tampilkan hasil akhir
    tampilkanRekapitulasi(rekap);

    return 0;
}
```

---

### 3. Penjelasan Program

#### 3.1 Pustaka yang Digunakan

- `<iostream>`: membaca masukan (`cin`) dan menampilkan teks (`cout`, `cerr`).
- `<string>`: menyimpan data teks, yaitu nomor paket.
- `<iomanip>`: `fixed` dan `setprecision(2)` agar angka desimal tampil dengan dua digit di belakang koma.
- `<cmath>`: `ceil` (pembulatan ke atas) dan `isfinite` (memeriksa angka yang valid).
- `<algorithm>`: `max` untuk memilih nilai terbesar dari dua angka.
- `<cctype>`: `toupper` agar huruf kecil dan huruf besar diperlakukan sama.
- `using namespace std;` agar awalan `std::` tidak perlu diulang.

#### 3.2 Struktur Data

Program memakai dua `struct` untuk mengelompokkan data yang saling berkaitan.

**`RekapPengiriman`** adalah wadah seluruh hasil rekapitulasi:

| Anggota | Fungsi | Nilai awal |
|---------|--------|-----------|
| `zonaA`, `zonaB`, `zonaC` | Menghitung jumlah paket di tiap zona | 0 |
| `reguler`, `prioritas` | Menghitung jumlah paket menurut jenis layanan | 0 |
| `menggunakanBeratVolumetrik` | Menghitung paket yang ditagih berdasarkan berat volumetrik | 0 |
| `totalBeratAktual` | Menjumlahkan berat aktual seluruh paket | 0 |
| `totalBeratTagihan` | Menjumlahkan berat tagihan seluruh paket | 0 |
| `totalAsuransi` | Menjumlahkan biaya asuransi | 0 |
| `totalPendapatan` | Menjumlahkan total biaya seluruh paket | 0 |
| `biayaTertinggi` | Menyimpan biaya paket terbesar yang pernah ditemukan | -1 |
| `nomorPaketBiayaTertinggi` | Menyimpan nomor paket pemilik biaya terbesar | "-" |

Nilai awal `biayaTertinggi` sengaja -1 agar paket pertama, berapa pun biayanya, pasti tercatat sebagai yang tertinggi pada awalnya.

**`HasilPaket`** adalah paket data keluaran Modul A untuk satu paket: nomor paket, zona, jenis pelayanan, berat aktual, berat volumetrik, berat tagihan, biaya asuransi, dan total biaya. Struct ini dikirim ke Modul B sebagai bahan rekapitulasi.

#### 3.3 Fungsi `perbaruiRekap`

Fungsi ini menerima catatan rekap dan data satu paket, lalu memperbaruinya:

1. Menambah pencacah zona yang sesuai (A, B, atau C).
2. Menambah pencacah reguler jika layanan bernomor 1, atau pencacah prioritas jika bukan.
3. Menambah pencacah berat volumetrik bila `beratVolumetrik > beratAktual`.
4. Menambahkan berat aktual, berat tagihan, biaya asuransi, dan total biaya ke jumlah keseluruhan.
5. Membandingkan total biaya paket dengan `biayaTertinggi`. Jika lebih besar, nilai dan nomor paket tersebut disimpan sebagai rekor baru.

Rekap dikirim sebagai referensi (`&`) sehingga perubahan di dalam fungsi langsung tersimpan.

#### 3.4 Fungsi `tampilkanRekapitulasi`

Fungsi ini mencetak seluruh isi catatan rekap ke layar (item yang ditampilkan dapat dilihat pada bagian 5.2). Rekap dikirim sebagai `const &` karena fungsi ini hanya membaca, tidak mengubah data.

#### 3.5 Fungsi `main`

**a. Persiapan awal.** Program meminta jumlah paket. Jika masukan bukan bilangan bulat atau nilainya 0 atau kurang, program menampilkan pesan kesalahan lalu berhenti (`return 1`). Setelah itu dibuat satu catatan rekap kosong, tarif per kilogram tiap zona ditetapkan sebagai konstanta (A Rp8.000, B Rp12.000, C Rp18.000), dan `fixed << setprecision(2)` mengatur format angka.

**b. Perulangan, masukan, dan validasi.** Perulangan `for` berjalan dari paket pertama sampai paket ke-`jumlah_paket`. Di setiap putaran, program membaca nomor paket, nilai barang, berat aktual, panjang, lebar, tinggi, zona tujuan, jenis pelayanan, dan pilihan asuransi. Setiap masukan diperiksa sebelum dipakai:

- Nilai barang tidak boleh negatif.
- Berat aktual, panjang, lebar, dan tinggi harus lebih dari 0.
- Angka harus benar-benar angka (`isfinite`), bukan huruf.
- Zona harus A, B, atau C (huruf kecil otomatis diubah menjadi huruf besar), lalu dicocokkan dengan tarifnya melalui `if ... else if ... else`.
- Jenis pelayanan harus 1 atau 2.
- Pilihan asuransi harus Y atau N.

Bila ada masukan yang salah, program menampilkan pesan yang sesuai lalu berhenti.

**c. Perhitungan biaya (Modul A).** Setelah semua data valid, biaya dihitung dengan urutan berikut:

1. **Berat volumetrik** = (panjang x lebar x tinggi) / 6000.
2. **Berat tagihan** = nilai terbesar antara berat aktual dan berat volumetrik, dibulatkan ke atas dengan `ceil`. Pengurang `1e-9` mencegah kesalahan pembulatan akibat ketelitian bilangan desimal.
3. **Biaya dasar** = berat tagihan x tarif zona.
4. **Biaya tambahan** = 40% dari biaya dasar jika layanan prioritas, atau 0 jika reguler.
5. **Biaya asuransi** = 1% dari nilai barang dengan batas minimum Rp5.000 jika asuransi dipilih, atau 0 jika tidak.
6. **Total biaya** = biaya dasar + biaya tambahan + biaya asuransi.

**d. Pembaruan rekap dan rincian paket.** Hasil perhitungan satu paket dikemas ke dalam `HasilPaket`, lalu diserahkan ke `perbaruiRekap`. Dengan cara ini rekap selalu terbarui tepat setelah setiap paket selesai dihitung, dan hanya berubah untuk paket yang masukannya lolos semua pemeriksaan. Sebelum lanjut ke paket berikutnya, program mencetak rincian biaya paket tersebut: zona tujuan, berat volumetrik, berat tagihan, biaya dasar, biaya tambahan, biaya asuransi, dan total biaya.

**e. Hasil akhir dan penutup.** Setelah perulangan selesai, `tampilkanRekapitulasi` dipanggil untuk mencetak laporan akhir. Program kemudian mengembalikan nilai 0 (`return 0`) sebagai tanda seluruh proses berjalan sampai selesai tanpa kendala.

#### 3.6 Ringkasan Alur

1. Baca jumlah paket dan siapkan rekap kosong.
2. Untuk setiap paket: baca data, validasi, hitung biaya (Modul A), perbarui rekap (Modul B), cetak rincian.
3. Cetak rekapitulasi akhir dan selesai.

---

### 4. Hasil Akhir (Eksekusi Program)

Bagian ini menampilkan hasil menjalankan program `modul_b.cpp` dan menjelaskan bagaimana setiap angka pada layar terbentuk.

#### 4.1 Data Uji

Tiga paket dengan kondisi berbeda dipilih agar seluruh aturan Modul B teruji dalam satu kali eksekusi.

| Nomor Paket | Nilai Barang (Rp) | Berat Aktual (kg) | P x L x T (cm) | Zona | Layanan | Asuransi |
|-------------|-------------------|-------------------|----------------|------|---------|----------|
| PK001 | 500.000 | 2,5 | 30 x 20 x 10 | A | Reguler | N |
| PK002 | 2.000.000 | 3 | 50 x 40 x 30 | B | Prioritas | Y |
| PK003 | 100.000 | 4,2 | 20 x 20 x 20 | C | Reguler | Y |

#### 4.2 Tampilan Eksekusi

```text
Masukkan jumlah paket: 3

=== Data Paket 1 ===
Masukkan Nomor Paket: PK001
Masukkan nilai Barang (Rp): 500000
Masukkan Berat Aktual (kg): 2.5
Masukkan Panjang (cm): 30
Masukkan Lebar (cm): 20
Masukkan Tinggi (cm): 10
Masukkan Zona Tujuan (A/B/C): A
Jenis Pelayanan (1. Reguler, 2. Prioritas): 1
Apakah ingin menggunakan asuransi? (Y/N): N

--- Rincian Biaya Paket PK001 ---
Zona tujuan: A
Berat volumetrik: 1.00 kg
Berat tagihan: 3.00 kg
Biaya dasar: Rp 24000.00
Biaya tambahan pelayanan: Rp 0.00
Biaya asuransi: Rp 0.00
Total biaya: Rp 24000.00

=== Data Paket 2 ===
Masukkan Nomor Paket: PK002
Masukkan nilai Barang (Rp): 2000000
Masukkan Berat Aktual (kg): 3
Masukkan Panjang (cm): 50
Masukkan Lebar (cm): 40
Masukkan Tinggi (cm): 30
Masukkan Zona Tujuan (A/B/C): B
Jenis Pelayanan (1. Reguler, 2. Prioritas): 2
Apakah ingin menggunakan asuransi? (Y/N): Y

--- Rincian Biaya Paket PK002 ---
Zona tujuan: B
Berat volumetrik: 10.00 kg
Berat tagihan: 10.00 kg
Biaya dasar: Rp 120000.00
Biaya tambahan pelayanan: Rp 48000.00
Biaya asuransi: Rp 20000.00
Total biaya: Rp 188000.00

=== Data Paket 3 ===
Masukkan Nomor Paket: PK003
Masukkan nilai Barang (Rp): 100000
Masukkan Berat Aktual (kg): 4.2
Masukkan Panjang (cm): 20
Masukkan Lebar (cm): 20
Masukkan Tinggi (cm): 20
Masukkan Zona Tujuan (A/B/C): C
Jenis Pelayanan (1. Reguler, 2. Prioritas): 1
Apakah ingin menggunakan asuransi? (Y/N): Y

--- Rincian Biaya Paket PK003 ---
Zona tujuan: C
Berat volumetrik: 1.33 kg
Berat tagihan: 5.00 kg
Biaya dasar: Rp 90000.00
Biaya tambahan pelayanan: Rp 0.00
Biaya asuransi: Rp 5000.00
Total biaya: Rp 95000.00

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

#### 4.3 Penjelasan Hasil Eksekusi

Tampilan di atas terdiri atas tiga bagian rincian biaya (satu per paket) dan satu rekapitulasi akhir. Berikut cara setiap bagian terbentuk.

**a. Paket PK001 (zona A, reguler, tanpa asuransi)**

- Berat volumetrik = (30 x 20 x 10) / 6000 = 1,00 kg, lebih kecil daripada berat aktual 2,5 kg, sehingga yang dipakai adalah berat aktual.
- Berat tagihan = 2,5 kg dibulatkan ke atas menjadi 3 kg.
- Biaya dasar = 3 x Rp8.000 = Rp24.000.
- Layanan reguler tidak ada tambahan, dan asuransi tidak dipilih, sehingga total biaya Rp24.000.

**b. Paket PK002 (zona B, prioritas, dengan asuransi)**

- Berat volumetrik = (50 x 40 x 30) / 6000 = 10,00 kg, lebih besar daripada berat aktual 3 kg, sehingga yang dipakai adalah berat volumetrik.
- Berat tagihan = 10 kg (sudah bulat).
- Biaya dasar = 10 x Rp12.000 = Rp120.000.
- Tambahan layanan prioritas = 40% x Rp120.000 = Rp48.000.
- Asuransi = 1% x Rp2.000.000 = Rp20.000 (di atas minimum Rp5.000).
- Total biaya = 120.000 + 48.000 + 20.000 = Rp188.000.

**c. Paket PK003 (zona C, reguler, dengan asuransi)**

- Berat volumetrik = (20 x 20 x 20) / 6000 = 1,33 kg, lebih kecil daripada berat aktual 4,2 kg, sehingga yang dipakai adalah berat aktual.
- Berat tagihan = 4,2 kg dibulatkan ke atas menjadi 5 kg.
- Biaya dasar = 5 x Rp18.000 = Rp90.000.
- Asuransi = 1% x Rp100.000 = Rp1.000, kurang dari minimum, sehingga dikenakan Rp5.000.
- Total biaya = 90.000 + 0 + 5.000 = Rp95.000.

**d. Terbentuknya rekapitulasi**

Rekapitulasi tidak dihitung sekaligus di akhir, melainkan diperbarui oleh `perbaruiRekap` setiap kali satu paket selesai dihitung. Tabel berikut menunjukkan isi rekap setelah tiap paket.

| Item Rekap | Awal | Setelah PK001 | Setelah PK002 | Setelah PK003 |
|------------|------|---------------|---------------|---------------|
| Paket zona A / B / C | 0 / 0 / 0 | 1 / 0 / 0 | 1 / 1 / 0 | 1 / 1 / 1 |
| Paket reguler / prioritas | 0 / 0 | 1 / 0 | 1 / 1 | 2 / 1 |
| Paket berat volumetrik | 0 | 0 | 1 | 1 |
| Total berat aktual (kg) | 0 | 2,5 | 5,5 | 9,7 |
| Total berat tagihan (kg) | 0 | 3 | 13 | 18 |
| Total asuransi (Rp) | 0 | 0 | 20.000 | 25.000 |
| Total pendapatan (Rp) | 0 | 24.000 | 212.000 | 307.000 |
| Biaya tertinggi | -1 (belum ada) | PK001 (24.000) | PK002 (188.000) | PK002 (188.000) |

Pada PK001, biaya tertinggi langsung terisi karena nilai awalnya -1. PK002 menggantikannya karena Rp188.000 lebih besar daripada Rp24.000. PK003 (Rp95.000) tidak menggantikan PK002 sehingga catatan tertinggi tidak berubah. Setelah paket ketiga selesai, isi rekap dicetak oleh `tampilkanRekapitulasi` sebagai bagian "REKAPITULASI PENGIRIMAN" pada layar.

---

### 5. Laporan Hasil Akhir

Bagian ini menyajikan hasil eksekusi dalam bentuk tabel, lalu menganalisis, memverifikasi, dan menyimpulkannya.

#### 5.1 Rincian Biaya per Paket

Setiap baris adalah satu paket. Kolom total biaya merupakan penjumlahan biaya dasar, tambahan layanan, dan asuransi pada baris yang sama. Baris terakhir adalah jumlah seluruh paket.

| Nomor Paket | Zona | Layanan | Berat Aktual (kg) | Berat Volumetrik (kg) | Berat Tagihan (kg) | Biaya Dasar (Rp) | Tambahan Layanan (Rp) | Asuransi (Rp) | Total Biaya (Rp) |
|-------------|------|---------|-------------------|-----------------------|--------------------|------------------|-----------------------|---------------|------------------|
| PK001 | A | Reguler | 2,5 | 1,00 | 3 | 24.000 | 0 | 0 | 24.000 |
| PK002 | B | Prioritas | 3 | 10,00 | 10 | 120.000 | 48.000 | 20.000 | 188.000 |
| PK003 | C | Reguler | 4,2 | 1,33 | 5 | 90.000 | 0 | 5.000 | 95.000 |
| **Total** | | | **9,7** | | **18** | **234.000** | **48.000** | **25.000** | **307.000** |

#### 5.2 Hasil Rekapitulasi

Tabel ini sama dengan bagian "REKAPITULASI PENGIRIMAN" pada layar, dilengkapi keterangan arti tiap item.

| No | Item Rekapitulasi | Hasil | Keterangan |
|----|-------------------|-------|------------|
| 1 | Jumlah paket zona A | 1 | Paket tujuan zona A: PK001 |
| 2 | Jumlah paket zona B | 1 | Paket tujuan zona B: PK002 |
| 3 | Jumlah paket zona C | 1 | Paket tujuan zona C: PK003 |
| 4 | Jumlah paket reguler | 2 | PK001 dan PK003 |
| 5 | Jumlah paket prioritas | 1 | PK002 |
| 6 | Total berat aktual | 9,70 kg | 2,5 + 3 + 4,2 |
| 7 | Total berat tagihan | 18,00 kg | 3 + 10 + 5 |
| 8 | Jumlah paket yang menggunakan berat volumetrik | 1 | PK002, karena berat volumetrik melebihi berat aktual |
| 9 | Total asuransi | Rp25.000 | 0 + 20.000 + 5.000 |
| 10 | Total pendapatan | Rp307.000 | 24.000 + 188.000 + 95.000 |
| 11 | Paket dengan biaya tertinggi | PK002 (Rp188.000) | Biaya terbesar di antara ketiga paket |

#### 5.3 Analisis

1. Ketiga zona masing-masing menerima satu paket, sedangkan layanan reguler (2 paket) lebih banyak dipakai daripada layanan prioritas (1 paket).
2. Hanya PK002 yang ditagih berdasarkan berat volumetrik karena ukurannya besar (50 x 40 x 30 cm) tetapi beratnya ringan (3 kg). Hal ini menunjukkan bahwa barang yang ringan namun besar tetap dikenai biaya sesuai ruang yang dipakainya.
3. Total berat tagihan (18 kg) hampir dua kali total berat aktual (9,7 kg) karena kombinasi pembulatan ke atas dan penggunaan berat volumetrik.
4. Asuransi PK003 dikenai Rp5.000, bukan Rp1.000 (1% nilai barang), karena berlaku biaya minimum Rp5.000. Asuransi PK001 nol karena tidak dipilih.
5. PK002 memiliki biaya tertinggi karena gabungan zona B, layanan prioritas (tambahan 40%), berat tagihan terbesar, dan asuransi.
6. Layanan prioritas menyumbang Rp48.000 (sekitar 15,6% dari total pendapatan Rp307.000), dan asuransi menyumbang Rp25.000 (sekitar 8,1%).

#### 5.4 Verifikasi Hasil

Hasil rekapitulasi diperiksa silang agar konsisten satu sama lain.

| No | Pemeriksaan | Perhitungan | Hasil |
|----|-------------|-------------|-------|
| 1 | Jumlah paket per zona sama dengan jumlah paket yang diproses | 1 + 1 + 1 = 3 | Sesuai |
| 2 | Jumlah paket reguler dan prioritas sama dengan jumlah paket yang diproses | 2 + 1 = 3 | Sesuai |
| 3 | Total berat aktual sama dengan jumlah berat aktual tiap paket | 2,5 + 3 + 4,2 = 9,7 | Sesuai |
| 4 | Total berat tagihan sama dengan jumlah berat tagihan tiap paket | 3 + 10 + 5 = 18 | Sesuai |
| 5 | Total pendapatan sama dengan jumlah total biaya tiap paket | 24.000 + 188.000 + 95.000 = 307.000 | Sesuai |
| 6 | Total pendapatan sama dengan biaya dasar + tambahan layanan + asuransi | 234.000 + 48.000 + 25.000 = 307.000 | Sesuai |
| 7 | Biaya tertinggi benar-benar yang terbesar | 188.000 > 95.000 > 24.000 | Sesuai |

#### 5.5 Kesimpulan

Modul B berhasil menghitung dan menampilkan seluruh data rekapitulasi pengiriman sesuai spesifikasi Studi Kasus 04. Seluruh angka pada rekapitulasi sama dengan perhitungan manual dan lolos pemeriksaan silang pada bagian 5.4, sehingga Modul B dinyatakan berfungsi dengan benar dan dapat digunakan bersama Modul A untuk memproses beberapa paket sekaligus.
