# Program Kalkulator Tarif Pengiriman Paket (C++)

Program berbasis konsol (CLI) yang ditulis dalam bahasa C++ untuk menghitung total biaya pengiriman paket secara otomatis berdasarkan berat aktual, dimensi volume, zona tujuan, jenis pelayanan, dan opsi asuransi barang.

---

## Fitur Utama

1. **Perhitungan Berat Volumetrik:** Menghitung volume paket menggunakan rumus standar logistik $(Panjang \times Lebar \times Tinggi) / 6000$ dan membandingkannya dengan berat aktual untuk menentukan berat tagihan yang dibulatkan ke atas.
2. **Tarif Berdasarkan Zona Tujuan:** Mendukung 3 zona pengiriman dengan tarif per kilogram yang berbeda (Zona A, B, dan C).
3. **Pilihan Jenis Pelayanan:**
* **Reguler (1):** Biaya dasar normal tanpa tambahan biaya.
* **Prioritas (2):** Layanan cepat dengan tambahan biaya sebesar 40% dari biaya dasar.


4. **Opsi Asuransi Barang:** Menghitung premi asuransi sebesar 1% dari nilai barang dengan ketentuan biaya minimum sebesar Rp 5.000 jika pengguna memilih opsi asuransi.

---

## Logika Perhitungan

* **Berat Volumetrik:**

$$\text{Berat Volumetrik} = \frac{\text{Panjang} \times \text{Lebar} \times \text{Tinggi}}{6000}$$


* **Berat Tagihan:** Mengambil nilai maksimum antara *Berat Aktual* dan *Berat Volumetrik*, kemudian dibulatkan ke atas (`ceil`).
* **Tarif Zona:**
* Zona A: Rp 8.000 / kg
* Zona B: Rp 12.000 / kg
* Zona C: Rp 18.000 / kg


* **Total Biaya:**

$$\text{Total Biaya} = \text{Biaya Dasar} + \text{Biaya Tambahan Pelayanan} + \text{Biaya Asuransi}$$



---

## Cara Menjalankan Program

1. Pastikan Anda sudah menginstal compiler C++ (seperti `g++` atau IDE seperti Dev-C++ / Code::Blocks).
2. Simpan kode program ke dalam file berformat `.cpp`, misalnya `Sistem_perhitungan_biaya_pengiriman_paket.cpp`.
3. Kompilasi program melalui terminal/command prompt:
```bash
g++ Sistem_perhitungan_biaya_pengiriman_paket.cpp -o Sistem_perhitungan_biaya_pengiriman_paket

```


4. Jalankan program:
* **Windows:** `Sistem_perhitungan_biaya_pengiriman_paket.exe`
* **Linux/macOS:** `./Sistem_perhitungan_biaya_pengiriman_paket`



---

## 📋 Contoh Alur Penggunaan (Input & Output)

**Contoh Input:**

```text
Masukkan nilai Barang (Rp): 1500000
Masukkan Nomor Paket: PKT-001
Masukkan Berat Aktual (kg): 2.5
Masukkan Panjang (cm): 30
Masukkan Lebar (cm): 20
Masukkan Tinggi (cm): 20
Masukkan Zona_Tujuan (A/B/C): A
jenis Pelayanan (1. Reguler, 2. Prioritas ): 2
Apakah ingin menggunakan asuransi? (Y/N): Y

```

**Contoh Output:**

```text
No.paket PKT-001
Biaya dasar 24000 + Biaya tambahan 9600 + Biaya asuransi 15000
Total Biaya: Rp 48600
tekan Enter untuk keluar....

```