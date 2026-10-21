# Modul B: Rekapitulasi Pengiriman

Program Modul B memproses beberapa paket dalam satu kali menjalankan program.
Setiap paket dihitung menggunakan aturan biaya Modul A, kemudian hasilnya
ditampilkan sebagai rincian biaya per paket dan rekapitulasi seluruh pengiriman.

## Perhitungan

- Berat volumetrik = panjang x lebar x tinggi / 6000.
- Berat tagihan = nilai yang lebih besar antara berat aktual dan berat volumetrik,
  dibulatkan ke atas.
- Tarif zona A: Rp8.000/kg; zona B: Rp12.000/kg; zona C: Rp18.000/kg.
- Layanan prioritas menambahkan 40% dari biaya dasar.
- Asuransi sebesar 1% dari nilai barang, dengan minimum Rp5.000.

Paket dihitung menggunakan berat volumetrik jika berat volumetriknya lebih besar
dari berat aktual, sehingga berat volumetrik menjadi dasar berat tagihan.

## Hasil rekapitulasi

Program menampilkan jumlah paket per zona, jumlah paket reguler dan prioritas,
total berat aktual dan berat tagihan, jumlah paket yang menggunakan berat
volumetrik, total asuransi, total pendapatan, serta paket dengan total biaya
tertinggi.

## Menjalankan program

Kompilasi file `Modul B/Sistem_perhitungan_biaya_pengiriman_paket.cpp` dengan
compiler C++ yang mendukung C++11 atau lebih baru, misalnya:

```text
g++ -std=c++11 "Modul B/Sistem_perhitungan_biaya_pengiriman_paket.cpp" -o modul_b
```

Jalankan program, masukkan jumlah paket, lalu masukkan data setiap paket sesuai
prompt. Berat dan dimensi harus lebih dari 0; nilai barang tidak boleh negatif.