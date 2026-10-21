PROGRAM RekapitulasiPengirimanPaket

KAMUS
    // Input dan variabel proses setiap paket
    n, i : INTEGER
    nomor_paket : STRING
    zona_tujuan, pilihan_asuransi : CHARACTER
    jenis_pelayanan : INTEGER
    nilai_barang, berat_aktual : REAL
    panjang, lebar, tinggi : REAL
    berat_volumetrik, berat_tagihan : REAL
    tarif_per_kg : REAL
    biaya_dasar, biaya_tambahan, biaya_asuransi, total_biaya : REAL
    menggunakan_berat_volumetrik : BOOLEAN

    // Akumulator rekapitulasi
    jumlah_zona_a, jumlah_zona_b, jumlah_zona_c : INTEGER
    jumlah_reguler, jumlah_prioritas : INTEGER
    jumlah_menggunakan_volumetrik : INTEGER
    total_berat_aktual, total_berat_tagihan : REAL
    total_asuransi, total_pendapatan : REAL

    // Data paket dengan biaya tertinggi
    biaya_tertinggi : REAL
    nomor_paket_tertinggi : STRING

ALGORITMA
    // 1. Inisialisasi rekapitulasi
    jumlah_zona_a <- 0
    jumlah_zona_b <- 0
    jumlah_zona_c <- 0
    jumlah_reguler <- 0
    jumlah_prioritas <- 0
    jumlah_menggunakan_volumetrik <- 0
    total_berat_aktual <- 0
    total_berat_tagihan <- 0
    total_asuransi <- 0
    total_pendapatan <- 0
    biaya_tertinggi <- -1
    nomor_paket_tertinggi <- ""

    // 2. Input jumlah paket
    TAMPILKAN "Masukkan jumlah paket: "
    BACA(n)

    JIKA n <= 0 MAKA
        TAMPILKAN "Jumlah paket harus lebih dari 0."
        HENTIKAN PROGRAM
    AKHIR JIKA

    // 3. Input dan hitung biaya setiap paket
    UNTUK i <- 1 SAMPAI n LAKUKAN
        TAMPILKAN "=== Data Paket ke-", i, " ==="

        TAMPILKAN "Masukkan Nomor Paket: "
        BACA(nomor_paket)

        TAMPILKAN "Masukkan nilai Barang (Rp): "
        BACA(nilai_barang)

        TAMPILKAN "Masukkan Berat Aktual (kg): "
        BACA(berat_aktual)

        TAMPILKAN "Masukkan Panjang (cm): "
        BACA(panjang)

        TAMPILKAN "Masukkan Lebar (cm): "
        BACA(lebar)

        TAMPILKAN "Masukkan Tinggi (cm): "
        BACA(tinggi)

        TAMPILKAN "Masukkan Zona Tujuan (A/B/C): "
        BACA(zona_tujuan)
        zona_tujuan <- HURUF_BESAR(zona_tujuan)

        TAMPILKAN "Jenis Pelayanan (1. Reguler, 2. Prioritas): "
        BACA(jenis_pelayanan)

        TAMPILKAN "Apakah ingin menggunakan asuransi? (Y/N): "
        BACA(pilihan_asuransi)
        pilihan_asuransi <- HURUF_BESAR(pilihan_asuransi)

        // 4. Validasi data paket
        JIKA nilai_barang < 0 ATAU berat_aktual <= 0
            ATAU panjang <= 0 ATAU lebar <= 0 ATAU tinggi <= 0 MAKA
            TAMPILKAN "Nilai barang, berat, atau dimensi tidak valid."
            HENTIKAN PROGRAM
        AKHIR JIKA

        JIKA jenis_pelayanan != 1 DAN jenis_pelayanan != 2 MAKA
            TAMPILKAN "Jenis pelayanan harus 1 atau 2."
            HENTIKAN PROGRAM
        AKHIR JIKA

        JIKA pilihan_asuransi != 'Y' DAN pilihan_asuransi != 'N' MAKA
            TAMPILKAN "Pilihan asuransi harus Y atau N."
            HENTIKAN PROGRAM
        AKHIR JIKA

        // 5. Tentukan tarif zona dan hitung jumlah paket per zona
        JIKA zona_tujuan == 'A' MAKA
            tarif_per_kg <- 8000
            jumlah_zona_a <- jumlah_zona_a + 1
        SEBALIKNYA JIKA zona_tujuan == 'B' MAKA
            tarif_per_kg <- 12000
            jumlah_zona_b <- jumlah_zona_b + 1
        SEBALIKNYA JIKA zona_tujuan == 'C' MAKA
            tarif_per_kg <- 18000
            jumlah_zona_c <- jumlah_zona_c + 1
        SEBALIKNYA
            TAMPILKAN "Zona tujuan harus A, B, atau C."
            HENTIKAN PROGRAM
        AKHIR JIKA

        // 6. Hitung berat volumetrik dan berat tagihan
        berat_volumetrik <- (panjang * lebar * tinggi) / 6000
        menggunakan_berat_volumetrik <- (berat_volumetrik > berat_aktual)

        JIKA menggunakan_berat_volumetrik MAKA
            jumlah_menggunakan_volumetrik <- jumlah_menggunakan_volumetrik + 1
        AKHIR JIKA

        berat_tagihan <- PEMBULATAN_KE_ATAS(
            MAKSIMUM(berat_aktual, berat_volumetrik)
        )

        // 7. Hitung biaya dasar dan tambahan pelayanan
        biaya_dasar <- berat_tagihan * tarif_per_kg

        JIKA jenis_pelayanan == 2 MAKA
            biaya_tambahan <- 0.40 * biaya_dasar
            jumlah_prioritas <- jumlah_prioritas + 1
        SEBALIKNYA
            biaya_tambahan <- 0
            jumlah_reguler <- jumlah_reguler + 1
        AKHIR JIKA

        // 8. Hitung asuransi dan total biaya
        biaya_asuransi <- 0
        JIKA pilihan_asuransi == 'Y' MAKA
            biaya_asuransi <- MAKSIMUM(0.01 * nilai_barang, 5000)
        AKHIR JIKA

        total_biaya <- biaya_dasar + biaya_tambahan + biaya_asuransi

        // 9. Akumulasi berat, asuransi, dan pendapatan
        total_berat_aktual <- total_berat_aktual + berat_aktual
        total_berat_tagihan <- total_berat_tagihan + berat_tagihan
        total_asuransi <- total_asuransi + biaya_asuransi
        total_pendapatan <- total_pendapatan + total_biaya

        // 10. Simpan paket dengan biaya tertinggi
        JIKA total_biaya > biaya_tertinggi MAKA
            biaya_tertinggi <- total_biaya
            nomor_paket_tertinggi <- nomor_paket
        AKHIR JIKA

        // 11. Tampilkan rincian biaya paket
        TAMPILKAN "--- Rincian Biaya Paket ", nomor_paket, " ---"
        TAMPILKAN "Zona tujuan: ", zona_tujuan
        TAMPILKAN "Berat volumetrik: ", berat_volumetrik, " kg"
        TAMPILKAN "Berat tagihan: ", berat_tagihan, " kg"
        TAMPILKAN "Biaya dasar: Rp ", biaya_dasar
        TAMPILKAN "Biaya tambahan pelayanan: Rp ", biaya_tambahan
        TAMPILKAN "Biaya asuransi: Rp ", biaya_asuransi
        TAMPILKAN "Total biaya: Rp ", total_biaya
    AKHIR UNTUK

    // 12. Tampilkan rekapitulasi seluruh paket
    TAMPILKAN "========================================="
    TAMPILKAN "       HASIL REKAPITULASI PENGIRIMAN"
    TAMPILKAN "========================================="
    TAMPILKAN "Jumlah paket zona A: ", jumlah_zona_a
    TAMPILKAN "Jumlah paket zona B: ", jumlah_zona_b
    TAMPILKAN "Jumlah paket zona C: ", jumlah_zona_c
    TAMPILKAN "Jumlah paket reguler: ", jumlah_reguler
    TAMPILKAN "Jumlah paket prioritas: ", jumlah_prioritas
    TAMPILKAN "Total berat aktual: ", total_berat_aktual, " kg"
    TAMPILKAN "Total berat tagihan: ", total_berat_tagihan, " kg"
    TAMPILKAN "Jumlah paket menggunakan berat volumetrik: ",
        jumlah_menggunakan_volumetrik
    TAMPILKAN "Total asuransi: Rp ", total_asuransi
    TAMPILKAN "Total pendapatan: Rp ", total_pendapatan
    TAMPILKAN "Paket dengan biaya tertinggi: ", nomor_paket_tertinggi,
        " (Rp ", biaya_tertinggi, ")"
    TAMPILKAN "========================================="
AKHIR PROGRAM
