**Penanggung jawab:** Aning Dwi Setyowati / 322610002

## Algoritma Deskriptif

### Modul B: Rekapitulasi Pengiriman

1. Mulai.
2. Siapkan variabel rekapitulasi dan beri nilai awal:
   - `zonaA = 0`, `zonaB = 0`, `zonaC = 0` (jumlah paket per zona)
   - `paketReguler = 0`, `paketPrioritas = 0` (jumlah paket per jenis layanan)
   - `paketVolumetrik = 0` (jumlah paket yang memakai berat volumetrik)
   - `sumBeratAktual = 0`, `sumBeratTagihan = 0` (total berat)
   - `sumAsuransi = 0`, `sumPendapatan = 0` (total biaya)
   - `biayaMaks = -1`, `paketMaks = "-"` (paket dengan biaya tertinggi)
3. Baca `jumlahPaket`.
4. Jika `jumlahPaket <= 0`, tampilkan pesan kesalahan, lalu ke langkah 17 (Selesai).
5. Set `i = 1`.
6. Selama `i <= jumlahPaket`, kerjakan langkah 7 sampai 14. Jika tidak, ke langkah 15.
7. Baca data paket ke-`i` dari Modul A (nomor paket, nilai barang, berat aktual, panjang, lebar, tinggi, zona tujuan, jenis layanan, pilihan asuransi).
8. Hitung nilai dari Modul A:
   - `beratVolumetrik = (panjang x lebar x tinggi) / 6000`
   - `beratTagihan` = nilai terbesar antara `beratAktual` dan `beratVolumetrik`, dibulatkan ke atas
   - `biayaAsuransi` = 1% dari nilai barang (minimal Rp5.000) jika memilih asuransi, jika tidak maka 0
   - `totalBiaya = biayaDasar + biayaTambahan + biayaAsuransi`
9. Perbarui jumlah paket per zona:
   - Jika zona = A, maka `zonaA = zonaA + 1`.
   - Jika tidak, jika zona = B, maka `zonaB = zonaB + 1`.
   - Jika tidak, maka `zonaC = zonaC + 1`.
10. Perbarui jumlah paket per layanan:
    - Jika layanan = Reguler, maka `paketReguler = paketReguler + 1`.
    - Jika tidak, maka `paketPrioritas = paketPrioritas + 1`.
11. Jika `beratVolumetrik > beratAktual`, maka `paketVolumetrik = paketVolumetrik + 1`.
12. Tambahkan nilai paket ke total:
    - `sumBeratAktual = sumBeratAktual + beratAktual`
    - `sumBeratTagihan = sumBeratTagihan + beratTagihan`
    - `sumAsuransi = sumAsuransi + biayaAsuransi`
    - `sumPendapatan = sumPendapatan + totalBiaya`
13. Jika `totalBiaya > biayaMaks`, maka `biayaMaks = totalBiaya` dan `paketMaks = nomorPaket`.
14. Naikkan penghitung: `i = i + 1`, lalu kembali ke langkah 6.
15. Tampilkan rekapitulasi pengiriman:
    - Jumlah paket zona A, zona B, dan zona C
    - Jumlah paket reguler dan paket prioritas
    - Total berat aktual dan total berat tagihan
    - Jumlah paket yang menggunakan berat volumetrik
    - Total asuransi dan total pendapatan
    - Paket dengan biaya tertinggi (`paketMaks`) beserta nilainya (`biayaMaks`)
16. Rekapitulasi selesai ditampilkan.
17. Selesai.
