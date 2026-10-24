**Penanggung jawab:**
- Fabian Jethro Falah Kalangi - 322610015
- Aning Dwi Setyowati - 322610002

## Hasil Eksekusi Program Terintegrasi

Studi Kasus 04: Sistem Perhitungan Biaya Pengiriman Paket (Modul A dan Modul B)

### 1. Tujuan

Bagian ini menunjukkan hasil menjalankan program final `main.cpp`: satu eksekusi dengan data valid yang melewati seluruh alur Modul A dan Modul B, serta eksekusi dengan masukan tidak valid untuk menunjukkan perilaku validasi. Seluruh keluaran di bawah adalah hasil asli program (kompilasi `g++ -Wall -Wextra` tanpa peringatan).

### 2. Daftar Eksekusi

| Kode | Kondisi | Tujuan |
|------|---------|--------|
| E1 | Tiga paket valid (PK001, PK002, PK003) | Menunjukkan alur lengkap Modul A dan Modul B sampai rekapitulasi |
| E2 | Jumlah paket = 0 | Menunjukkan validasi jumlah paket |
| E3 | Paket pertama valid, paket kedua zona D | Menunjukkan paket valid diproses dan program berhenti di data tidak valid |
| E4 | Berat aktual = -2 | Menunjukkan validasi berat aktual |
| E5 | Jenis pelayanan = 3 | Menunjukkan validasi jenis pelayanan |
| E6 | Pilihan asuransi = X | Menunjukkan validasi pilihan asuransi |
| E7 | Nilai barang berupa huruf ("abc") | Menunjukkan validasi masukan yang bukan angka |

Data uji E1:

| Nomor Paket | Nilai Barang (Rp) | Berat Aktual (kg) | P x L x T (cm) | Zona | Layanan | Asuransi |
|-------------|-------------------|-------------------|----------------|------|---------|----------|
| PK001 | 500.000 | 2,5 | 30 x 20 x 10 | A | Reguler | N |
| PK002 | 2.000.000 | 3 | 50 x 40 x 30 | B | Prioritas | Y |
| PK003 | 100.000 | 4,2 | 20 x 20 x 20 | C | Reguler | Y |

---

### 3. Hasil Eksekusi

#### 3.1 E1: Tiga Paket Valid

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

Penjelasan:

- **Modul A** menghasilkan rincian biaya tiap paket: PK001 Rp24.000 (berat tagihan 3 kg), PK002 Rp188.000 (memakai berat volumetrik 10 kg), dan PK003 Rp95.000 (asuransi minimum Rp5.000).
- **Modul B** menampilkan rekapitulasi dari ketiga paket: total pendapatan Rp307.000 (24.000 + 188.000 + 95.000), total asuransi Rp25.000, total berat aktual 9,70 kg, total berat tagihan 18,00 kg, dan biaya tertinggi pada PK002 (Rp188.000).

#### 3.2 E2: Jumlah Paket Tidak Valid

```text
Masukkan jumlah paket: 0
Jumlah paket harus berupa bilangan bulat lebih dari 0.
```

Program menolak jumlah paket 0 dan berhenti sebelum Modul A berjalan.

#### 3.3 E3: Paket Kedua Tidak Valid

```text
Masukkan jumlah paket: 2

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
Masukkan nilai Barang (Rp): 1000
Masukkan Berat Aktual (kg): 2
Masukkan Panjang (cm): 10
Masukkan Lebar (cm): 10
Masukkan Tinggi (cm): 10
Masukkan Zona Tujuan (A/B/C): D
Zona tujuan harus A, B, atau C.
```

Paket pertama selesai diproses dan rinciannya ditampilkan. Pada paket kedua, zona D ditolak sehingga program berhenti tanpa menampilkan rekapitulasi yang tidak lengkap.

#### 3.4 E4: Berat Aktual Tidak Valid

```text
Masukkan jumlah paket: 1

=== Data Paket 1 ===
Masukkan Nomor Paket: PK004
Masukkan nilai Barang (Rp): 1000
Masukkan Berat Aktual (kg): -2
Berat aktual harus berupa angka lebih dari 0.
```

#### 3.5 E5: Jenis Pelayanan Tidak Valid

```text
Masukkan jumlah paket: 1

=== Data Paket 1 ===
Masukkan Nomor Paket: PK005
Masukkan nilai Barang (Rp): 1000
Masukkan Berat Aktual (kg): 2
Masukkan Panjang (cm): 10
Masukkan Lebar (cm): 10
Masukkan Tinggi (cm): 10
Masukkan Zona Tujuan (A/B/C): A
Jenis Pelayanan (1. Reguler, 2. Prioritas): 3
Jenis pelayanan harus 1 (Reguler) atau 2 (Prioritas).
```

#### 3.6 E6: Pilihan Asuransi Tidak Valid

```text
Masukkan jumlah paket: 1

=== Data Paket 1 ===
Masukkan Nomor Paket: PK006
Masukkan nilai Barang (Rp): 1000
Masukkan Berat Aktual (kg): 2
Masukkan Panjang (cm): 10
Masukkan Lebar (cm): 10
Masukkan Tinggi (cm): 10
Masukkan Zona Tujuan (A/B/C): A
Jenis Pelayanan (1. Reguler, 2. Prioritas): 1
Apakah ingin menggunakan asuransi? (Y/N): X
Pilihan asuransi harus Y atau N.
```

#### 3.7 E7: Masukan Bukan Angka

```text
Masukkan jumlah paket: 1

=== Data Paket 1 ===
Masukkan Nomor Paket: PK007
Masukkan nilai Barang (Rp): abc
Nilai barang harus berupa angka yang tidak negatif.
```

---

### 4. Ringkasan Hasil Eksekusi

| Kode | Hasil yang diharapkan | Hasil aktual | Kode keluar | Status |
|------|-----------------------|--------------|-------------|--------|
| E1 | Rincian tiga paket dan rekapitulasi (total Rp307.000, tertinggi PK002) | Sesuai | 0 | Sesuai |
| E2 | Pesan kesalahan jumlah paket, program berhenti | Sesuai | 1 | Sesuai |
| E3 | Rincian PK001 tampil, lalu pesan kesalahan zona, program berhenti | Sesuai | 1 | Sesuai |
| E4 | Pesan kesalahan berat aktual, program berhenti | Sesuai | 1 | Sesuai |
| E5 | Pesan kesalahan jenis pelayanan, program berhenti | Sesuai | 1 | Sesuai |
| E6 | Pesan kesalahan pilihan asuransi, program berhenti | Sesuai | 1 | Sesuai |
| E7 | Pesan kesalahan nilai barang, program berhenti | Sesuai | 1 | Sesuai |

Kode keluar 0 berarti program selesai normal, sedangkan kode keluar 1 berarti program berhenti karena masukan tidak valid.

### 5. Kesimpulan

Program terintegrasi berjalan sesuai rancangan. Pada data valid (E1), Modul A dan Modul B bekerja berurutan dan menghasilkan rincian per paket serta rekapitulasi yang sesuai dengan perhitungan manual. Pada masukan tidak valid (E2 sampai E7), program menampilkan pesan kesalahan yang tepat dan berhenti, sehingga rekapitulasi tidak pernah memuat data yang salah.
