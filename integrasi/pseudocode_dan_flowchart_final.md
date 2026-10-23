**Penanggung jawab:**
- Fabian Jethro Falah Kalangi - 322610015
- Aning Dwi Setyowati - 322610002

## Pseudocode dan Flowchart Final Program Terintegrasi

Studi Kasus 04: Sistem Perhitungan Biaya Pengiriman Paket (Modul A dan Modul B)

### 1. Tujuan dan Ruang Lingkup

Dokumen ini memuat rancangan akhir program terintegrasi, yaitu pseudocode dan flowchart yang sesuai dengan source code `integrasi.cpp`. Rancangan disusun dalam dua tingkat:

1. **Tingkat program utama:** alur keseluruhan dari membaca jumlah paket sampai menampilkan rekapitulasi.
2. **Tingkat fungsi:** rincian isi fungsi `bacaDataPaket`, `hitungBiaya`, dan `perbaruiRekap`.

---

### 2. Kamus Data

#### 2.1 Konstanta

| Nama | Nilai | Keterangan |
|------|-------|------------|
| `TARIF_ZONA_A` | 8000 | Tarif per kg zona A (Rp) |
| `TARIF_ZONA_B` | 12000 | Tarif per kg zona B (Rp) |
| `TARIF_ZONA_C` | 18000 | Tarif per kg zona C (Rp) |

#### 2.2 Tipe Data Bentukan

| Tipe | Anggota | Peran |
|------|---------|-------|
| `DataPaket` (masukan Modul A) | nomorPaket, nilaiBarang, beratAktual, panjang, lebar, tinggi, zona, jenisPelayanan, asuransi | Menampung data satu paket dari pengguna |
| `HasilPaket` (keluaran Modul A, masukan Modul B) | nomorPaket, zona, jenisPelayanan, beratAktual, beratVolumetrik, beratTagihan, biayaDasar, biayaTambahan, biayaAsuransi, totalBiaya | Menampung hasil hitung satu paket |
| `RekapPengiriman` (Modul B) | zonaA, zonaB, zonaC, reguler, prioritas, paketVolumetrik, totalBeratAktual, totalBeratTagihan, totalAsuransi, totalPendapatan, biayaTertinggi (awal -1), nomorPaketTertinggi (awal "-") | Menampung seluruh data rekapitulasi |

---

### 3. Pseudocode Final

#### 3.1 Algoritma Utama

```text
ALGORITMA ProgramTerintegrasi
KAMUS
  jumlahPaket, i : integer
  data           : DataPaket
  hasil          : HasilPaket
  rekap          : RekapPengiriman

DESKRIPSI
  TAMPILKAN "Masukkan jumlah paket"
  BACA jumlahPaket
  JIKA jumlahPaket tidak valid ATAU jumlahPaket <= 0 MAKA
    TAMPILKAN "Jumlah paket harus berupa bilangan bulat lebih dari 0."
    SELESAI
  AKHIR JIKA

  rekap ← RekapPengiriman kosong      // semua pencacah dan total 0, biayaTertinggi = -1
  i ← 1

  ULANGI SELAMA i <= jumlahPaket
    TAMPILKAN "Data Paket ke-i"

    // ----- MODUL A -----
    JIKA bacaDataPaket(data) = SALAH MAKA
      SELESAI                          // pesan kesalahan sudah ditampilkan
    AKHIR JIKA
    hasil ← hitungBiaya(data)
    tampilkanRincian(hasil)

    // ----- MODUL B -----
    perbaruiRekap(rekap, hasil)

    i ← i + 1
  AKHIR ULANGI

  tampilkanRekapitulasi(rekap)         // MODUL B
SELESAI
```

#### 3.2 Fungsi `bacaDataPaket` (Modul A)

```text
FUNGSI bacaDataPaket(data : DataPaket) → boolean
DESKRIPSI
  BACA data.nomorPaket
  JIKA gagal dibaca MAKA
    TAMPILKAN "Nomor paket tidak valid."; KEMBALIKAN SALAH

  BACA data.nilaiBarang
  JIKA bukan angka valid ATAU nilaiBarang < 0 MAKA
    TAMPILKAN "Nilai barang harus berupa angka yang tidak negatif."; KEMBALIKAN SALAH

  BACA data.beratAktual
  JIKA bukan angka valid ATAU beratAktual <= 0 MAKA
    TAMPILKAN "Berat aktual harus berupa angka lebih dari 0."; KEMBALIKAN SALAH

  BACA data.panjang
  JIKA bukan angka valid ATAU panjang <= 0 MAKA
    TAMPILKAN "Panjang harus berupa angka lebih dari 0."; KEMBALIKAN SALAH

  BACA data.lebar
  JIKA bukan angka valid ATAU lebar <= 0 MAKA
    TAMPILKAN "Lebar harus berupa angka lebih dari 0."; KEMBALIKAN SALAH

  BACA data.tinggi
  JIKA bukan angka valid ATAU tinggi <= 0 MAKA
    TAMPILKAN "Tinggi harus berupa angka lebih dari 0."; KEMBALIKAN SALAH

  BACA data.zona
  data.zona ← HURUF BESAR(data.zona)
  JIKA data.zona BUKAN "A", "B", atau "C" MAKA
    TAMPILKAN "Zona tujuan harus A, B, atau C."; KEMBALIKAN SALAH

  BACA data.jenisPelayanan
  JIKA jenisPelayanan BUKAN 1 atau 2 MAKA
    TAMPILKAN "Jenis pelayanan harus 1 (Reguler) atau 2 (Prioritas)."; KEMBALIKAN SALAH

  BACA data.asuransi
  data.asuransi ← HURUF BESAR(data.asuransi)
  JIKA data.asuransi BUKAN "Y" atau "N" MAKA
    TAMPILKAN "Pilihan asuransi harus Y atau N."; KEMBALIKAN SALAH

  KEMBALIKAN BENAR
```

#### 3.3 Fungsi `tarifZona` (Modul A)

```text
FUNGSI tarifZona(zona : char) → real
DESKRIPSI
  JIKA zona = "A" MAKA KEMBALIKAN TARIF_ZONA_A
  JIKA zona = "B" MAKA KEMBALIKAN TARIF_ZONA_B
  KEMBALIKAN TARIF_ZONA_C
```

#### 3.4 Fungsi `hitungBiaya` (Modul A)

```text
FUNGSI hitungBiaya(data : DataPaket) → HasilPaket
KAMUS
  hasil : HasilPaket
DESKRIPSI
  hasil.nomorPaket      ← data.nomorPaket
  hasil.zona            ← data.zona
  hasil.jenisPelayanan  ← data.jenisPelayanan
  hasil.beratAktual     ← data.beratAktual
  hasil.beratVolumetrik ← (data.panjang x data.lebar x data.tinggi) / 6000
  hasil.beratTagihan    ← BULATKAN KE ATAS(MAKS(hasil.beratAktual, hasil.beratVolumetrik) - 1e-9)
  hasil.biayaDasar      ← hasil.beratTagihan x tarifZona(data.zona)

  JIKA data.jenisPelayanan = 2 MAKA
    hasil.biayaTambahan ← 0,40 x hasil.biayaDasar
  SELAIN ITU
    hasil.biayaTambahan ← 0
  AKHIR JIKA

  JIKA data.asuransi = "Y" MAKA
    hasil.biayaAsuransi ← MAKS(0,01 x data.nilaiBarang, 5000)
  SELAIN ITU
    hasil.biayaAsuransi ← 0
  AKHIR JIKA

  hasil.totalBiaya ← hasil.biayaDasar + hasil.biayaTambahan + hasil.biayaAsuransi
  KEMBALIKAN hasil
```

#### 3.5 Prosedur `tampilkanRincian` (Modul A)

```text
PROSEDUR tampilkanRincian(hasil : HasilPaket)
DESKRIPSI
  TAMPILKAN "Rincian Biaya Paket", hasil.nomorPaket
  TAMPILKAN zona tujuan, berat volumetrik, berat tagihan
  TAMPILKAN biaya dasar, biaya tambahan pelayanan, biaya asuransi
  TAMPILKAN total biaya
```

#### 3.6 Prosedur `perbaruiRekap` (Modul B)

```text
PROSEDUR perbaruiRekap(rekap : RekapPengiriman, hasil : HasilPaket)
DESKRIPSI
  JIKA hasil.zona = "A" MAKA
    rekap.zonaA ← rekap.zonaA + 1
  SELAIN ITU JIKA hasil.zona = "B" MAKA
    rekap.zonaB ← rekap.zonaB + 1
  SELAIN ITU
    rekap.zonaC ← rekap.zonaC + 1
  AKHIR JIKA

  JIKA hasil.jenisPelayanan = 1 MAKA
    rekap.reguler ← rekap.reguler + 1
  SELAIN ITU
    rekap.prioritas ← rekap.prioritas + 1
  AKHIR JIKA

  JIKA hasil.beratVolumetrik > hasil.beratAktual MAKA
    rekap.paketVolumetrik ← rekap.paketVolumetrik + 1
  AKHIR JIKA

  rekap.totalBeratAktual  ← rekap.totalBeratAktual + hasil.beratAktual
  rekap.totalBeratTagihan ← rekap.totalBeratTagihan + hasil.beratTagihan
  rekap.totalAsuransi     ← rekap.totalAsuransi + hasil.biayaAsuransi
  rekap.totalPendapatan   ← rekap.totalPendapatan + hasil.totalBiaya

  JIKA hasil.totalBiaya > rekap.biayaTertinggi MAKA
    rekap.biayaTertinggi      ← hasil.totalBiaya
    rekap.nomorPaketTertinggi ← hasil.nomorPaket
  AKHIR JIKA
```

#### 3.7 Prosedur `tampilkanRekapitulasi` (Modul B)

```text
PROSEDUR tampilkanRekapitulasi(rekap : RekapPengiriman)
DESKRIPSI
  TAMPILKAN "REKAPITULASI PENGIRIMAN"
  TAMPILKAN jumlah paket zona A, zona B, zona C
  TAMPILKAN jumlah paket reguler dan prioritas
  TAMPILKAN total berat aktual dan total berat tagihan
  TAMPILKAN jumlah paket yang menggunakan berat volumetrik
  TAMPILKAN total asuransi dan total pendapatan
  TAMPILKAN paket dengan biaya tertinggi beserta nilainya
```

---

### 4. Keterangan Simbol Flowchart

| Simbol (Mermaid) | Arti |
|------------------|------|
| `([ ... ])` | Awal atau akhir (terminator) |
| `[/ ... /]` | Masukan atau keluaran |
| `[ ... ]` | Proses |
| `{ ... }` | Keputusan |
| `[[ ... ]]` | Pemanggilan fungsi atau prosedur (proses terdefinisi) |

Seluruh flowchart memakai `curve: linear` agar garisnya lurus.

---

### 5. Flowchart Final

#### 5.1 Flowchart Program Utama

![Flowchart Final Program Terintegrasi](gambar/flowchart-integrasi-final.svg)

> Salin kode Mermaid di bawah ke [mermaid.live](https://mermaid.live), lalu ekspor sebagai **SVG** dengan nama `gambar/flowchart-integrasi-final.svg`.

```mermaid
%%{init: {"flowchart": {"curve": "linear"}}}%%
flowchart TD
    M1([Mulai]) --> M2[/"Input jumlahPaket"/]
    M2 --> M3{"jumlahPaket tidak valid<br>atau <= 0?"}
    M3 -- Ya --> M4[/"Tampilkan pesan kesalahan"/]
    M4 --> M99([Selesai])
    M3 -- Tidak --> M5["rekap ← kosong<br>i ← 1"]
    M5 --> M6{"i <= jumlahPaket?"}

    M6 -- Ya --> M7[["bacaDataPaket(data)<br>MODUL A"]]
    M7 --> M8{"Data valid?"}
    M8 -- Tidak --> M99
    M8 -- Ya --> M9[["hitungBiaya(data)<br>MODUL A"]]
    M9 --> M10[["tampilkanRincian(hasil)<br>MODUL A"]]
    M10 --> M11[["perbaruiRekap(rekap, hasil)<br>MODUL B"]]
    M11 --> M12["i ← i + 1"]
    M12 --> M6

    M6 -- Tidak --> M13[["tampilkanRekapitulasi(rekap)<br>MODUL B"]]
    M13 --> M99
```

#### 5.2 Flowchart Fungsi `bacaDataPaket` (Modul A)

```mermaid
%%{init: {"flowchart": {"curve": "linear"}}}%%
flowchart TD
    R1([Mulai bacaDataPaket]) --> R2[/"Input nomorPaket"/]
    R2 --> R3{"Berhasil dibaca?"}
    R3 -- Tidak --> RF[/"Tampilkan pesan kesalahan"/]
    R3 -- Ya --> R4[/"Input nilaiBarang"/]
    R4 --> R5{"Angka valid<br>dan >= 0?"}
    R5 -- Tidak --> RF
    R5 -- Ya --> R6[/"Input beratAktual"/]
    R6 --> R7{"Angka valid<br>dan > 0?"}
    R7 -- Tidak --> RF
    R7 -- Ya --> R8[/"Input panjang, lebar, tinggi"/]
    R8 --> R9{"Ketiganya angka valid<br>dan > 0?"}
    R9 -- Tidak --> RF
    R9 -- Ya --> R10[/"Input zona"/]
    R10 --> R11["zona ← huruf besar(zona)"]
    R11 --> R12{"zona = A, B, atau C?"}
    R12 -- Tidak --> RF
    R12 -- Ya --> R13[/"Input jenisPelayanan"/]
    R13 --> R14{"jenisPelayanan = 1 atau 2?"}
    R14 -- Tidak --> RF
    R14 -- Ya --> R15[/"Input asuransi"/]
    R15 --> R16["asuransi ← huruf besar(asuransi)"]
    R16 --> R17{"asuransi = Y atau N?"}
    R17 -- Tidak --> RF
    R17 -- Ya --> RB([Kembalikan BENAR])
    RF --> RS([Kembalikan SALAH])
```

#### 5.3 Flowchart Fungsi `hitungBiaya` (Modul A)

```mermaid
%%{init: {"flowchart": {"curve": "linear"}}}%%
flowchart TD
    H1([Mulai hitungBiaya]) --> H2["beratVolumetrik ← (panjang x lebar x tinggi) / 6000"]
    H2 --> H3["beratTagihan ← bulatkan ke atas(<br>maks(beratAktual, beratVolumetrik) - 1e-9)"]
    H3 --> H4[["tarifZona(zona)"]]
    H4 --> H5["biayaDasar ← beratTagihan x tarif"]
    H5 --> H6{"jenisPelayanan = 2<br>(Prioritas)?"}
    H6 -- Ya --> H7["biayaTambahan ← 0,40 x biayaDasar"]
    H6 -- Tidak --> H8["biayaTambahan ← 0"]
    H7 --> H9{"asuransi = Y?"}
    H8 --> H9
    H9 -- Ya --> H10["biayaAsuransi ← maks(0,01 x nilaiBarang, 5000)"]
    H9 -- Tidak --> H11["biayaAsuransi ← 0"]
    H10 --> H12["totalBiaya ← biayaDasar + biayaTambahan + biayaAsuransi"]
    H11 --> H12
    H12 --> H13([Kembalikan HasilPaket])
```

#### 5.4 Flowchart Prosedur `perbaruiRekap` (Modul B)

```mermaid
%%{init: {"flowchart": {"curve": "linear"}}}%%
flowchart TD
    P1([Mulai perbaruiRekap]) --> P2{"zona = A?"}
    P2 -- Ya --> P3["zonaA ← zonaA + 1"]
    P2 -- Tidak --> P4{"zona = B?"}
    P4 -- Ya --> P5["zonaB ← zonaB + 1"]
    P4 -- Tidak --> P6["zonaC ← zonaC + 1"]

    P3 --> P7{"jenisPelayanan = 1<br>(Reguler)?"}
    P5 --> P7
    P6 --> P7
    P7 -- Ya --> P8["reguler ← reguler + 1"]
    P7 -- Tidak --> P9["prioritas ← prioritas + 1"]

    P8 --> P10{"beratVolumetrik ><br>beratAktual?"}
    P9 --> P10
    P10 -- Ya --> P11["paketVolumetrik ← paketVolumetrik + 1"]
    P10 -- Tidak --> P12
    P11 --> P12["totalBeratAktual ← totalBeratAktual + beratAktual<br>totalBeratTagihan ← totalBeratTagihan + beratTagihan<br>totalAsuransi ← totalAsuransi + biayaAsuransi<br>totalPendapatan ← totalPendapatan + totalBiaya"]

    P12 --> P13{"totalBiaya ><br>biayaTertinggi?"}
    P13 -- Ya --> P14["biayaTertinggi ← totalBiaya<br>nomorPaketTertinggi ← nomorPaket"]
    P13 -- Tidak --> P15([Selesai perbaruiRekap])
    P14 --> P15
```

---

### 6. Kesesuaian Pseudocode, Flowchart, dan Source Code

| No | Bagian | Modul | Pseudocode | Flowchart | Source code (`integrasi.cpp`) |
|----|--------|-------|------------|-----------|-------------------------------|
| 1 | Alur program utama | Integrasi | 3.1 | 5.1 | `main()` |
| 2 | Membaca dan validasi masukan | A | 3.2 | 5.2 | `bacaDataPaket()` |
| 3 | Penentuan tarif zona | A | 3.3 | Dipanggil pada 5.3 | `tarifZona()` |
| 4 | Perhitungan biaya | A | 3.4 | 5.3 | `hitungBiaya()` |
| 5 | Tampil rincian paket | A | 3.5 | Dipanggil pada 5.1 | `tampilkanRincian()` |
| 6 | Pembaruan rekap | B | 3.6 | 5.4 | `perbaruiRekap()` |
| 7 | Tampil rekapitulasi | B | 3.7 | Dipanggil pada 5.1 | `tampilkanRekapitulasi()` |

### 7. Catatan

1. Pada `bacaDataPaket`, berat aktual diperiksa lebih dulu, lalu panjang, lebar, dan tinggi satu per satu. Pada flowchart 5.2, pemeriksaan panjang, lebar, dan tinggi digabung dalam satu langkah agar diagram tetap ringkas. Di source code ketiganya diperiksa terpisah dengan pesan kesalahan masing-masing.
2. Setiap kegagalan validasi menampilkan pesan lalu mengembalikan nilai salah, sehingga `main()` menghentikan program dan `perbaruiRekap()` tidak pernah dipanggil untuk data yang tidak valid.
3. Nilai awal `biayaTertinggi = -1` memastikan paket pertama selalu tercatat sebagai biaya tertinggi sementara.
4. Dua nama anggota rekap pada pseudocode dipersingkat agar mudah dibaca: `paketVolumetrik` di source code bernama `menggunakanBeratVolumetrik`, dan `nomorPaketTertinggi` di source code bernama `nomorPaketBiayaTertinggi`. Fungsinya sama.
