# Refleksi Proyek UTS: Sistem Perhitungan Biaya Pengiriman Paket

**Mata Kuliah:** Algoritma dan Pengantar Pemrograman (SSI1144)
**Program Studi:** Sistem Informasi - Universitas Ma Chung
**Studi Kasus 04:** Sistem Perhitungan Biaya Pengiriman Paket
**Repository:** [Sistem-Perhitungan-Biaya-Pengiriman-Paket](https://github.com/jetrofabian28/Sistem-Perhitungan-Biaya-Pengiriman-Paket)

---

## 1. Pembagian Tugas

Proyek dikerjakan berdua. Setiap orang memegang satu modul, lalu keduanya bekerja bersama pada integrasi, pengujian, dan dokumentasi.

| Anggota | NIM | Modul | Tugas pada modul |
|---------|-----|-------|------------------|
| Fabian Jethro Falah Kalangi | 322610015 | Modul A: Proses Utama | Merancang dan menulis bagian membaca data paket, validasi masukan, penentuan tarif zona, serta perhitungan berat tagihan, biaya dasar, tambahan layanan prioritas, dan asuransi |
| Aning Dwi Setyowati | 322610002 | Modul B: Rekapitulasi | Merancang dan menulis bagian pencacahan zona dan layanan, akumulasi berat, asuransi, dan pendapatan, penentuan paket dengan biaya tertinggi, serta laporan rekapitulasi akhir |

Tugas bersama:

- Menyusun antarmuka data antarmodul (struct `HasilPaket`) dan menggabungkan kedua modul menjadi satu program.
- Menyusun algoritma deskriptif, pseudocode, flowchart, tabel pengujian, trace table, dan daftar kesalahan beserta perbaikannya.
- Mengunggah source code dan dokumentasi ke GitHub serta menyusun halaman GitHub Pages.

---

## 2. Alur Kerja Kelompok

Pekerjaan dilakukan dalam urutan berikut:

1. **Memahami soal.** Aturan biaya dibaca bersama dan ditulis ulang sebagai daftar rumus (berat volumetrik, berat tagihan, tarif zona, tambahan 40%, asuransi 1% minimal Rp5.000).
2. **Merancang tiap modul.** Masing-masing anggota membuat algoritma deskriptif dan flowchart modulnya.
3. **Menyepakati titik temu.** Data apa saja yang harus diserahkan Modul A ke Modul B ditentukan lebih dulu, lalu dituangkan dalam struct `HasilPaket`.
4. **Menulis dan menguji kode.** Setiap modul dicoba dengan data sederhana sebelum digabung.
5. **Menggabungkan dan menguji ulang.** Program gabungan dijalankan dengan 19 kasus uji, dan keluarannya dibandingkan dengan hitungan manual.
6. **Menyusun dokumentasi.** Hasil kerja dirapikan ke dalam halaman GitHub Pages.

---

## 3. Tantangan yang Dihadapi

| No | Tantangan | Modul | Cara mengatasi |
|----|-----------|-------|----------------|
| 1 | Satu paket memerlukan sembilan masukan, dan tiap masukan punya aturan sendiri (angka positif, zona A/B/C, layanan 1 atau 2, asuransi Y atau N) | A | Seluruh pemeriksaan dikumpulkan dalam satu fungsi `bacaDataPaket()` yang mengembalikan nilai benar atau salah |
| 2 | Pembulatan berat tagihan ke atas bisa keliru pada bilangan desimal, misalnya 5,0000000001 menjadi 6 | A | Ditambahkan pengurang kecil `1e-9` sebelum `ceil`, lalu diuji pada kasus nilai batas |
| 3 | Menentukan kapan rekapitulasi boleh diperbarui | B | Rekap hanya diperbarui setelah data satu paket valid dan biayanya selesai dihitung |
| 4 | Nilai awal untuk mencari biaya tertinggi | B | Dipakai nilai awal -1 sehingga paket pertama selalu tercatat sebagai yang tertinggi sementara |
| 5 | Menyatukan dua modul tanpa membuatnya saling bergantung | A dan B | Keduanya dihubungkan hanya lewat `HasilPaket`; Modul B tidak perlu mengetahui rumus biaya |
| 6 | Menyajikan flowchart dan dokumen dalam format GitHub Pages | A dan B | Flowchart dibuat dengan Mermaid dan SVG, sedangkan dokumen ditulis dalam Markdown |

---

## 4. Kesalahan dan Perbaikannya

Daftar lengkap kesalahan ada di bagian "Daftar Kesalahan dan Perbaikan". Ringkasannya:

- **Teks dokumentasi tercampur di berkas kode.** Berkas `.cpp` sempat berisi teks Markdown sehingga tidak bisa dikompilasi. Hikmahnya: kode dan dokumentasi harus dipisahkan, dan keterangan di dalam kode cukup berupa komentar.
- **Pencacah rekap berubah terlalu dini.** Pencacah zona sempat dinaikkan sebelum seluruh data paket diperiksa. Hikmahnya: pembaruan data ringkasan sebaiknya dilakukan setelah semua pemeriksaan selesai.
- **Pengujian awal terlalu sempit.** Kasus nilai batas baru diuji belakangan. Hikmahnya: kasus seperti berat tepat bulat, asuransi tepat di batas minimum, atau dua paket dengan biaya sama perlu diuji sejak awal.
- **Logika dua modul tercampur dalam satu fungsi.** Hikmahnya: memecah program menjadi fungsi dengan satu tugas membuat kode lebih mudah dibaca dan diuji.

---

## 5. Pengetahuan dan Keterampilan Baru

1. **Merancang sebelum menulis kode.** Aturan soal diubah menjadi algoritma deskriptif, pseudocode, dan flowchart sebelum diimplementasikan.
2. **Memakai `struct` dan fungsi.** Data yang berkaitan dikelompokkan dalam `struct`, dan tiap tugas dipisah ke fungsi tersendiri.
3. **Validasi masukan.** Memeriksa masukan yang bukan angka, bernilai di luar batas, atau berada di luar pilihan yang diizinkan.
4. **Menelusuri program dengan trace table.** Nilai variabel dicatat langkah demi langkah untuk memastikan hasil program sama dengan hitungan manual.
5. **Merancang pengujian.** Kasus uji dikelompokkan menjadi data valid, nilai batas, masukan tidak valid, dan pengujian integrasi.
6. **Alat bantu dokumentasi.** Menulis Markdown, membuat flowchart dengan Mermaid, dan menyusun halaman GitHub Pages.
7. **Dasar Git dan GitHub.** Mengunggah kode dan dokumen ke repository bersama.

---

## 6. Penilaian terhadap Hasil Akhir

**Yang sudah baik:**

- Perhitungan biaya sesuai aturan soal dan lolos seluruh 19 kasus uji.
- Modul A dan Modul B terpisah jelas dan terhubung lewat satu struct.
- Rekapitulasi hanya memuat paket yang datanya valid.

**Yang masih terbatas:**

- Program berhenti saat ada satu masukan tidak valid, sehingga pengguna harus mengulang dari awal.
- Data setiap paket tidak disimpan, sehingga rekapitulasi hanya berupa angka ringkasan.
- Tarif dan aturan biaya masih tertulis di dalam kode.

---

## 7. Rencana Pengembangan untuk UAS

| No | Rencana | Manfaat |
|----|---------|---------|
| 1 | Mengulang permintaan masukan sampai valid (perulangan dengan `cin.clear()` dan `cin.ignore()`) | Pengguna tidak perlu mengulang dari awal saat salah mengetik |
| 2 | Menyimpan seluruh paket dalam array atau `vector` dari `HasilPaket` | Data tiap paket dapat dilihat kembali setelah rekapitulasi |
| 3 | Menambah fitur pencarian paket dan pengurutan berdasarkan biaya | Memudahkan menelusuri paket tertentu dan membandingkan biaya |
| 4 | Menyimpan laporan ke berkas teks atau CSV | Rekapitulasi dapat diarsipkan dan dibuka di aplikasi lain |
| 5 | Membaca tarif dan aturan biaya dari berkas pengaturan | Tarif dapat diubah tanpa mengubah kode |
| 6 | Membuat tampilan antarmuka yang lebih interaktif | Program lebih mudah digunakan |
