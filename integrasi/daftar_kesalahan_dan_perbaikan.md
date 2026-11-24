**Penanggung jawab:**
- Fabian Jethro Falah Kalangi - 322610015
- Aning Dwi Setyowati - 322610002

## Daftar Kesalahan dan Perbaikan

Studi Kasus 04: Sistem Perhitungan Biaya Pengiriman Paket (Modul A dan Modul B)

### 1. Ringkasan

Selama penyusunan dan integrasi, ditemukan beberapa kesalahan dan potensi kesalahan pada kode dan dokumentasi. Seluruhnya dicatat di bawah ini beserta penyebab, perbaikan, dan statusnya. Satu keterbatasan (nomor 8) belum diperbaiki dan dicatat sebagai rencana pengembangan.

| Jenis | Jumlah |
|-------|--------|
| Kesalahan yang menyebabkan program gagal dikompilasi | 1 |
| Kesalahan struktur dan susunan kode | 3 |
| Potensi kesalahan perhitungan | 1 |
| Kekurangan pengujian | 1 |
| Keterbatasan yang belum diperbaiki | 1 |
| **Total** | **7** |

### 2. Tabel Kesalahan dan Perbaikan

| No | Kesalahan / gejala | Penyebab | Perbaikan | Status |
|----|--------------------|----------|-----------|--------|
| 1 | Berkas `.cpp` gagal dikompilasi | Teks Markdown (penanggung jawab, judul "Algoritma Deskriptif", daftar langkah bernomor) tertulis langsung di dalam berkas kode | Seluruh teks dipindah menjadi komentar `//` di bagian atas berkas | Selesai |
| 2 | Struct `RekapPengiriman` terselip di tengah teks algoritma | Struct ditulis di bawah langkah "inisialisasi" pada algoritma deskriptif, bukan di bagian atas program | Struct dipindah ke bagian atas program, sebelum fungsi dan `main()` | Selesai |
| 3 | Pencacah rekap dapat berubah sebelum seluruh data paket selesai diperiksa | Pencacah zona dinaikkan di dalam percabangan tarif, sebelum jenis pelayanan dan pilihan asuransi divalidasi | Pembaruan rekap dipindah ke fungsi `perbaruiRekap()`, hanya dipanggil setelah data valid dan biaya selesai dihitung | Selesai |
| 4 | Berat tagihan berisiko naik 1 kg dari seharusnya | Hasil pembagian bilangan desimal (misalnya 5,0000000001 akibat ketelitian floating point) dibulatkan ke atas oleh `ceil` | Ditambahkan pengurang kecil: `ceil(max(...) - 1e-9)` | Selesai |
| 5 | Logika Modul A dan Modul B tercampur di dalam `main()` | Seluruh proses (masukan, hitung, rekap, tampil) ditulis dalam satu fungsi | Dipisah menjadi fungsi Modul A (`bacaDataPaket`, `hitungBiaya`, `tampilkanRincian`) dan Modul B (`perbaruiRekap`, `tampilkanRekapitulasi`) yang dihubungkan struct `HasilPaket` | Selesai |
| 6 | Pengujian awal hanya mencakup data umum | Kasus nilai batas (pembulatan, berat volumetrik sama dengan berat aktual, asuransi minimum, biaya tertinggi sama) belum diuji | Ditambahkan 8 kasus nilai batas sehingga total 19 kasus pengujian, seluruhnya lulus | Selesai |
| 7 | Nama `menggunakanBeratVolumetrik` dipakai untuk dua hal berbeda | Satu nama dipakai untuk variabel lokal bertipe `bool` di `main()` dan anggota pencacah di struct rekap, sehingga membingungkan dibaca | Variabel lokal dihapus; pemeriksaan `beratVolumetrik > beratAktual` dilakukan langsung di `perbaruiRekap()` | Selesai |
| 8 | Program berhenti seluruhnya jika ada satu masukan tidak valid | Setiap kegagalan validasi langsung `return`, tanpa meminta pengguna mengetik ulang | Belum diperbaiki. Dicatat sebagai pengembangan: memakai perulangan masukan sampai valid | Rencana pengembangan |

### 3. Rincian Perbaikan Utama

#### 3.1 Kesalahan 1: Teks Markdown di dalam berkas kode

Sebelum:

```text
**Penanggung jawab:** Aning Dwi Setyowati / 322610002

## Algoritma Deskriptif
1.mulai
2.inisialisasi seluruh variabel akumulator dan pencacah:
struct RekapPengiriman { ... };
```

Sesudah:

```cpp
// Studi Kasus 04 - Sistem Perhitungan Biaya Pengiriman Paket
// Penanggung jawab: Fabian Jethro Falah Kalangi - 322610015
//                   Aning Dwi Setyowati - 322610002
```

Dampak: berkas sekarang murni kode C++ sehingga dapat dikompilasi tanpa peringatan (`g++ -Wall -Wextra`). Algoritma deskriptif dipindah ke dokumen terpisah.

#### 3.2 Kesalahan 3: Rekap berubah sebelum data lengkap

Sebelum (pencacah naik di tengah proses validasi):

```cpp
if (zona_tujuan == 'A') {
    tarif_per_kg = tarifZonaA;
    ++rekap.zonaA;          // naik sebelum layanan dan asuransi divalidasi
}
```

Sesudah (rekap hanya diperbarui setelah semuanya valid):

```cpp
HasilPaket hasil = hitungBiaya(data);
tampilkanRincian(hasil);
perbaruiRekap(rekap, hasil);   // dipanggil hanya jika bacaDataPaket() berhasil
```

Dampak: pada program saat ini rekap tidak sempat ditampilkan jika terjadi kesalahan, sehingga hasil akhir tidak keliru. Namun jika nanti program diubah agar meminta ulang masukan, kode lama akan menghitung paket yang sama dua kali. Perbaikan ini mencegah hal tersebut.

#### 3.3 Kesalahan 4: Pembulatan bilangan desimal

Sebelum:

```cpp
const double berat_tagihan = ceil(max(berat_aktual, berat_volumetrik));
```

Sesudah:

```cpp
hasil.beratTagihan = ceil(max(hasil.beratAktual, hasil.beratVolumetrik) - 1e-9);
```

Dampak: bilangan yang seharusnya bulat tetapi tersimpan sedikit lebih besar karena ketelitian komputer tidak lagi naik satu kilogram. Kasus pengujian nomor 5 (berat 3 kg tetap 3 kg) dan nomor 6 (berat volumetrik 1,00 kg tetap 1 kg) memeriksa hal ini.

#### 3.4 Kesalahan 5: Modul A dan Modul B tercampur

Sebelum: seluruh proses berada di `main()`.

Sesudah: `main()` hanya mengatur alur.

```cpp
for (int i = 1; i <= jumlahPaket; ++i) {
    DataPaket data;
    if (!bacaDataPaket(data)) return 1;        // Modul A
    HasilPaket hasil = hitungBiaya(data);      // Modul A
    tampilkanRincian(hasil);                   // Modul A
    perbaruiRekap(rekap, hasil);               // Modul B
}
tampilkanRekapitulasi(rekap);                  // Modul B
```

Dampak: setiap bagian dapat dibaca dan diuji sendiri, dan perubahan aturan biaya cukup dilakukan di `hitungBiaya()` tanpa menyentuh Modul B.

### 4. Keterbatasan yang Belum Diperbaiki

| No | Keterbatasan | Dampak | Rencana pengembangan |
|----|--------------|--------|----------------------|
| 8 | Program berhenti jika ada masukan tidak valid | Pengguna harus menjalankan ulang program dan mengisi data dari awal | Membungkus setiap masukan dalam perulangan yang meminta ulang sampai valid, disertai pembersihan buffer masukan (`cin.clear()` dan `cin.ignore()`) |

### 5. Pelajaran dari Perbaikan

1. Berkas kode harus dipisahkan dari dokumentasi. Algoritma dan penjelasan ditulis di dokumen sendiri, sedangkan di dalam kode cukup berupa komentar.
2. Rekapitulasi sebaiknya diperbarui hanya setelah data satu paket benar-benar valid dan selesai dihitung.
3. Bilangan desimal perlu diperlakukan hati-hati pada pembulatan.
4. Pengujian nilai batas menemukan hal yang tidak terlihat pada data umum.
5. Memisahkan program ke fungsi dengan peran jelas memudahkan integrasi Modul A dan Modul B.