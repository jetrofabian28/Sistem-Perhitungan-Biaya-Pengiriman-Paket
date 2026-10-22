**Penanggung jawab:** Aning Dwi Setyowati / 322610002

## Hasil Eksekusi dan Pengujian

### 1. Skenario Pengujian

Pengujian dilakukan dengan mengompilasi dan menjalankan program `biaya_pengiriman.cpp` (C++) menggunakan data uji berikut.

| Kode | Skenario | Tujuan |
|------|----------|--------|
| S1 | Satu paket reguler, zona A, tanpa asuransi, berat aktual lebih besar dari berat volumetrik | Memastikan perhitungan dasar dan pembulatan ke atas |
| S2 | Satu paket prioritas, zona B, dengan asuransi, berat volumetrik lebih besar dari berat aktual | Memastikan pemakaian berat volumetrik, tambahan 40%, dan asuransi 1% |
| S3 | Satu paket reguler, zona C, dengan asuransi pada barang bernilai kecil | Memastikan biaya asuransi minimum Rp5.000 |
| S4 | Tiga paket sekaligus (data S1, S2, dan S3) | Memastikan rekapitulasi (Modul B) dan penentuan biaya tertinggi |
| S5 | Jumlah paket = 0 | Memastikan validasi jumlah paket |
| S6 | Zona tujuan = D | Memastikan validasi zona |
| S7 | Berat aktual = -2 | Memastikan validasi berat aktual |
| S8 | Jenis layanan = 3 | Memastikan validasi jenis layanan |

---

### 2. Tabel Pengujian

**Data masukan**

| Kode | Nomor Paket | Nilai Barang (Rp) | Berat Aktual (kg) | P x L x T (cm) | Zona | Layanan | Asuransi |
|------|-------------|-------------------|-------------------|----------------|------|---------|----------|
| S1 | PK001 | 500.000 | 2,5 | 30 x 20 x 10 | A | Reguler | N |
| S2 | PK002 | 2.000.000 | 3 | 50 x 40 x 30 | B | Prioritas | Y |
| S3 | PK003 | 100.000 | 4,2 | 20 x 20 x 20 | C | Reguler | Y |

**Perbandingan hasil yang diharapkan dan hasil aktual**

| Kode | Perhitungan Manual | Hasil yang Diharapkan | Hasil Aktual | Status |
|------|--------------------|-----------------------|--------------|--------|
| S1 | Volumetrik = 6.000 / 6.000 = 1 kg; berat tagihan = ceil(2,5) = 3 kg; 3 x 8.000 | Total biaya Rp24.000 | Total biaya Rp24.000 | Sesuai |
| S2 | Volumetrik = 60.000 / 6.000 = 10 kg; 10 x 12.000 = 120.000; tambahan 40% = 48.000; asuransi 1% = 20.000 | Total biaya Rp188.000 | Total biaya Rp188.000 | Sesuai |
| S3 | Volumetrik = 1,33 kg; berat tagihan = ceil(4,2) = 5 kg; 5 x 18.000 = 90.000; asuransi 1% = 1.000, dipakai minimum 5.000 | Total biaya Rp95.000 | Total biaya Rp95.000 | Sesuai |
| S4 | 24.000 + 188.000 + 95.000 | Total pendapatan Rp307.000; biaya tertinggi PK002 | Total pendapatan Rp307.000; biaya tertinggi PK002 | Sesuai |
| S5 | Jumlah paket tidak boleh <= 0 | Program menolak dan berhenti | Pesan kesalahan tampil, program berhenti | Sesuai |
| S6 | Zona hanya A, B, atau C | Program menolak dan berhenti | Pesan kesalahan tampil, program berhenti | Sesuai |
| S7 | Berat aktual harus > 0 | Program menolak dan berhenti | Pesan kesalahan tampil, program berhenti | Sesuai |
| S8 | Layanan hanya 1 atau 2 | Program menolak dan berhenti | Pesan kesalahan tampil, program berhenti | Sesuai |

---

### 3. Hasil Eksekusi

**S1 - Paket reguler zona A tanpa asuransi**

```text
Masukkan jumlah paket: 1

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
```

**S2 - Paket prioritas zona B dengan asuransi**

```text
Masukkan jumlah paket: 1

=== Data Paket 1 ===
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
```

**S3 - Paket zona C dengan asuransi minimum**

```text
Masukkan jumlah paket: 1

=== Data Paket 1 ===
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
```

**S4 - Tiga paket sekaligus (rekapitulasi)**

Rincian biaya setiap paket sama dengan S1, S2, dan S3. Rekapitulasi yang ditampilkan:

```text
Masukkan jumlah paket: 3
...
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

**S5 - Jumlah paket tidak valid**

```text
Masukkan jumlah paket: 0
Jumlah paket harus berupa bilangan bulat lebih dari 0.
```

**S6 - Zona tidak valid**

```text
Masukkan Zona Tujuan (A/B/C): D
Zona tujuan harus A, B, atau C.
```

**S7 - Berat aktual tidak valid**

```text
Masukkan Berat Aktual (kg): -2
Berat aktual harus berupa angka lebih dari 0.
```

**S8 - Jenis layanan tidak valid**

```text
Jenis Pelayanan (1. Reguler, 2. Prioritas): 3
Jenis pelayanan harus 1 (Reguler) atau 2 (Prioritas).
```

---

### 4. Kesimpulan Penguji

1. Seluruh 8 skenario pengujian (S1 sampai S8) menghasilkan keluaran yang sama dengan perhitungan manual, sehingga status pengujian **Sesuai** untuk semuanya.
2. **Modul A (Proses Utama)** berjalan benar: berat tagihan diambil dari nilai terbesar antara berat aktual dan berat volumetrik lalu dibulatkan ke atas, tarif per zona sesuai (A Rp8.000, B Rp12.000, C Rp18.000), layanan prioritas menambah 40%, dan asuransi dihitung 1% dari nilai barang dengan minimum Rp5.000.
3. **Modul B (Rekapitulasi)** berjalan benar: jumlah paket per zona dan per layanan, total berat aktual dan berat tagihan, jumlah paket berat volumetrik, total asuransi, total pendapatan, serta paket dengan biaya tertinggi sesuai dengan hasil hitung manual pada S4.
4. **Validasi masukan** berfungsi: program menolak jumlah paket tidak valid, zona di luar A/B/C, berat bukan angka positif, dan jenis layanan di luar 1 atau 2 dengan menampilkan pesan kesalahan.
5. Catatan: ketika masukan tidak valid, program berhenti (tidak meminta masukan ulang). Hal ini sesuai rancangan program saat ini dan dapat dikembangkan menjadi pengulangan masukan.

**Kesimpulan akhir:** program Sistem Perhitungan Biaya Pengiriman Paket berfungsi sesuai spesifikasi Studi Kasus 04 dan layak digunakan.
