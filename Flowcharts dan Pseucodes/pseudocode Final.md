# Pseudocode: Sistem Perhitungan Biaya Pengiriman Paket (Modul B)

## Konstanta

```
TARIF_ZONA_A       ← 8000     // Rp per kg
TARIF_ZONA_B       ← 12000
TARIF_ZONA_C       ← 18000
PEMBAGI_VOLUMETRIK ← 6000
PERSEN_PRIORITAS   ← 40%      // biaya tambahan layanan prioritas
PERSEN_ASURANSI    ← 1%       // dari nilai barang
ASURANSI_MINIMUM   ← 5000
```

## Struktur Data

```
RekapPengiriman:
    zonaA, zonaB, zonaC                   : integer ← 0
    reguler, prioritas                    : integer ← 0
    menggunakanBeratVolumetrik            : integer ← 0
    totalBeratAktual, totalBeratTagihan   : real    ← 0
    totalAsuransi, totalPendapatan        : real    ← 0
    biayaTertinggi                        : real    ← -1
    nomorPaketBiayaTertinggi              : string  ← ""
```

## Algoritma Utama

```
ALGORITMA HitungBiayaPengiriman

    TAMPILKAN "Masukkan jumlah paket: "
    BACA jumlah_paket
    JIKA jumlah_paket tidak valid ATAU jumlah_paket <= 0 MAKA
        TAMPILKAN "Jumlah paket harus berupa bilangan bulat lebih dari 0."
        SELESAI (kode error 1)
    AKHIR JIKA

    rekap ← RekapPengiriman baru (nilai awal sesuai struktur di atas)

    UNTUK i ← 1 SAMPAI jumlah_paket LAKUKAN

        // ---------- 1. Input data paket ----------
        BACA nomor_paket
        BACA nilai_barang
        BACA berat_aktual
        BACA panjang, lebar, tinggi
        BACA zona_tujuan
        zona_tujuan ← HURUF_KAPITAL(zona_tujuan)

        // ---------- 2. Validasi input numerik ----------
        JIKA nilai_barang bukan angka valid ATAU nilai_barang < 0 MAKA
            TAMPILKAN pesan error; SELESAI (kode error 1)
        JIKA berat_aktual, panjang, lebar, atau tinggi
             bukan angka valid ATAU <= 0 MAKA
            TAMPILKAN pesan error; SELESAI (kode error 1)

        // ---------- 3. Tentukan tarif berdasarkan zona ----------
        JIKA zona_tujuan = 'A' MAKA
            tarif_per_kg ← TARIF_ZONA_A;  rekap.zonaA ← rekap.zonaA + 1
        JIKA TIDAK, JIKA zona_tujuan = 'B' MAKA
            tarif_per_kg ← TARIF_ZONA_B;  rekap.zonaB ← rekap.zonaB + 1
        JIKA TIDAK, JIKA zona_tujuan = 'C' MAKA
            tarif_per_kg ← TARIF_ZONA_C;  rekap.zonaC ← rekap.zonaC + 1
        JIKA TIDAK
            TAMPILKAN "Zona tujuan harus A, B, atau C."; SELESAI (kode error 1)
        AKHIR JIKA

        // ---------- 4. Input layanan & asuransi ----------
        BACA jenis_pelayanan          // 1 = Reguler, 2 = Prioritas
        JIKA jenis_pelayanan bukan 1 dan bukan 2 MAKA
            TAMPILKAN pesan error; SELESAI (kode error 1)

        BACA pilihan_asuransi
        pilihan_asuransi ← HURUF_KAPITAL(pilihan_asuransi)
        JIKA pilihan_asuransi bukan 'Y' dan bukan 'N' MAKA
            TAMPILKAN pesan error; SELESAI (kode error 1)

        // ---------- 5. Perhitungan biaya ----------
        berat_volumetrik ← (panjang × lebar × tinggi) / PEMBAGI_VOLUMETRIK
        pakaiVolumetrik  ← (berat_volumetrik > berat_aktual)
        berat_tagihan    ← PEMBULATAN_KE_ATAS( MAKSIMUM(berat_aktual, berat_volumetrik) )
        biaya_dasar      ← berat_tagihan × tarif_per_kg

        JIKA jenis_pelayanan = 2 MAKA
            biaya_tambahan ← PERSEN_PRIORITAS × biaya_dasar
        JIKA TIDAK
            biaya_tambahan ← 0
        AKHIR JIKA

        JIKA pilihan_asuransi = 'Y' MAKA
            biaya_asuransi ← MAKSIMUM(PERSEN_ASURANSI × nilai_barang, ASURANSI_MINIMUM)
        JIKA TIDAK
            biaya_asuransi ← 0
        AKHIR JIKA

        total_biaya ← biaya_dasar + biaya_tambahan + biaya_asuransi

        // ---------- 6. Update rekapitulasi ----------
        JIKA jenis_pelayanan = 1 MAKA rekap.reguler   ← rekap.reguler + 1
        JIKA TIDAK                    rekap.prioritas ← rekap.prioritas + 1

        JIKA pakaiVolumetrik MAKA
            rekap.menggunakanBeratVolumetrik ← rekap.menggunakanBeratVolumetrik + 1

        rekap.totalBeratAktual  ← rekap.totalBeratAktual  + berat_aktual
        rekap.totalBeratTagihan ← rekap.totalBeratTagihan + berat_tagihan
        rekap.totalAsuransi     ← rekap.totalAsuransi     + biaya_asuransi
        rekap.totalPendapatan   ← rekap.totalPendapatan   + total_biaya

        JIKA total_biaya > rekap.biayaTertinggi MAKA
            rekap.biayaTertinggi           ← total_biaya
            rekap.nomorPaketBiayaTertinggi ← nomor_paket
        AKHIR JIKA

        // ---------- 7. Output rincian paket ----------
        TAMPILKAN zona_tujuan, berat_volumetrik, berat_tagihan,
                  biaya_dasar, biaya_tambahan, biaya_asuransi, total_biaya

    AKHIR UNTUK

    // ---------- Output rekapitulasi ----------
    TAMPILKAN rekap.zonaA, rekap.zonaB, rekap.zonaC
    TAMPILKAN rekap.reguler, rekap.prioritas
    TAMPILKAN rekap.totalBeratAktual, rekap.totalBeratTagihan
    TAMPILKAN rekap.menggunakanBeratVolumetrik
    TAMPILKAN rekap.totalAsuransi, rekap.totalPendapatan
    TAMPILKAN rekap.nomorPaketBiayaTertinggi, rekap.biayaTertinggi

AKHIR ALGORITMA
```

## Ringkasan Rumus

| Komponen | Rumus |
|---|---|
| Berat volumetrik | `(panjang × lebar × tinggi) / 6000` |
| Berat tagihan | `ceil(max(berat aktual, berat volumetrik))` |
| Biaya dasar | `berat tagihan × tarif zona` |
| Biaya tambahan (Prioritas) | `40% × biaya dasar` |
| Biaya asuransi | `max(1% × nilai barang, 5000)` jika memilih asuransi |
| Total biaya | `biaya dasar + biaya tambahan + biaya asuransi` |

## Flowchart

![Flowchart](flowchart.png)
