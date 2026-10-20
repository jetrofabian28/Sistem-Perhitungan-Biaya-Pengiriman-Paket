PROGRAM HitungBiayaPengiriman
DEKLARASI
    // Variabel Input
    nomor_paket : STRING
    Berat_aktual, panjang, lebar, tinggi, nilai_barang : REAL
    zona_tujuan, Pilihan_asuransi : CHARACTER
    jenis_pelayanan : INTEGER

    // Variabel Proses dan Output
    berat_volumetrik, berat_maksimal, berat_tagihan : REAL
    tarifperKg, biaya_dasar, biaya_tambahan, biaya_asuransi, total_biaya : REAL

ALGORITMA
    // Input Data Pengguna
    Tampilkan "Masukkan nilai Barang (Rp): "
    Baca(nilai_barang)
    
    Tampilkan "Masukkan Nomor Paket: "
    Baca(nomor_paket)
    
    Tampilkan "Masukkan Berat Aktual (kg): "
    Baca(Berat_aktual)
    
    Tampilkan "Masukkan Panjang (cm): "
    Baca(panjang)

    Tampilkan "Masukkan Lebar (cm): "
    Baca(lebar)

    Tampilkan "Masukkan Tinggi (cm): "
    Baca(tinggi)

    Tampilkan "Masukkan Zona_Tujuan (A/B/C): "
    Baca(zona_tujuan)
    
    Tampilkan "Jenis Pelayanan (1. Reguler, 2. Prioritas): "
    Baca(jenis_pelayanan)
    
    Tampilkan "Apakah ingin menggunakan asuransi? (Y/N): "
    Baca(Pilihan_asuransi)

    // Perhitungan Berat Volumetrik dan Berat Tagihan
    berat_volumetrik <- (panjang * lebar * tinggi) / 6000
    berat_maksimal <- MAX(Berat_aktual, berat_volumetrik)
    berat_tagihan <- CEIL(berat_maksimal)

    // Menentukan Tarif per Kg Berdasarkan Zona Tujuan
    tarifperKg <- 0
    zona_tujuan <- TOUPPER(zona_tujuan)
    
    JIKA zona_tujuan == 'A' MAKA
        tarifperKg <- 8000
    SEBALIKNYA JIKA zona_tujuan == 'B' MAKA
        tarifperKg <- 12000
    SEBALIKNYA JIKA zona_tujuan == 'C' MAKA
        tarifperKg <- 18000
    SEBALIKNYA
        Tampilkan "Zona tujuan tidak valid!"
        KELUAR PROGRAM
    AKHIR JIKA

    biaya_dasar <- berat_tagihan * tarifperKg

    // Menghitung biaya tambahan berdasarkan jenis pelayanan
    biaya_tambahan <- 0
    JIKA jenis_pelayanan == 2 MAKA
        biaya_tambahan <- 0.40 * biaya_dasar
    SEBALIKNYA JIKA jenis_pelayanan == 1 MAKA
        biaya_tambahan <- 0
    SEBALIKNYA
        Tampilkan "Jenis pelayanan tidak valid!"
        KELUAR PROGRAM
    AKHIR JIKA

    // Menghitung biaya asuransi jika dipilih
    biaya_asuransi <- 0
    JIKA TOUPPER(Pilihan_asuransi) == 'Y' MAKA
        biaya_asuransi <- 0.01 * nilai_barang
        JIKA biaya_asuransi < 5000 MAKA
            biaya_asuransi <- 5000
        AKHIR JIKA
    AKHIR JIKA

    // Menghitung dan Menampilkan Total Biaya
    Tampilkan "No. paket: ", nomor_paket
    total_biaya <- biaya_dasar + biaya_tambahan + biaya_asuransi
    Tampilkan "Biaya dasar ", biaya_dasar, " + Biaya tambahan ", biaya_tambahan, " + Biaya asuransi ", biaya_asuransi
    Tampilkan "Total Biaya: Rp ", total_biaya
    
    Tampilkan "Tekan Enter untuk keluar...."