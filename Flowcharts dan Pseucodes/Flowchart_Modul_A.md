# Flowchart Modul A: Perhitungan Biaya Pengiriman

Dokumen ini berisi flowchart proses perhitungan biaya pengiriman paket, beserta penjelasan setiap langkah dan aturan bisnisnya.

## Flowchart

```mermaid
flowchart TD
    start([Mulai])
    input[/"Input Data:<br/>• Nomor Paket<br/>• Berat Aktual (kg)<br/>• Panjang, Lebar, Tinggi (cm)<br/>• Zona Tujuan (A/B/C)<br/>• Jenis Layanan<br/>• Nilai Barang<br/>• Pilihan Asuransi (Ya/Tidak)"/]
    volumetrik["Hitung Berat Volumetrik<br/>= (P × L × T) / 6000"]
    tagihan["Tentukan Berat Tagihan<br/>= CEIL( MAX(Berat Aktual, Berat Volumetrik) )"]
    zona{"Zona Tujuan?"}
    tarifA["Tarif = Rp 8.000 / kg"]
    tarifB["Tarif = Rp 12.000 / kg"]
    tarifC["Tarif = Rp 18.000 / kg"]
    biayaDasar["Hitung Biaya Dasar<br/>= Berat Tagihan × Tarif"]
    prioritas{"Jenis Layanan<br/>= Prioritas?"}
    prioritasYa["Biaya Dasar = Biaya Dasar × 1,4"]
    prioritasTidak["Biaya Dasar tetap"]
    asuransi{"Pilih Asuransi?"}
    asuransiYa["Biaya Asuransi =<br/>MAX(Nilai Barang × 1%, Rp 5.000)"]
    asuransiTidak["Biaya Asuransi = 0"]
    total["Total Biaya =<br/>Biaya Dasar + Biaya Asuransi"]
    output[/"Output:<br/>• Nomor Paket<br/>• Berat Tagihan<br/>• Biaya Dasar<br/>• Biaya Asuransi<br/>• Total Biaya"/]
    selesai([Selesai])

    start --> input
    input --> volumetrik
    volumetrik --> tagihan
    tagihan --> zona
    zona -->|A| tarifA
    zona -->|B| tarifB
    zona -->|C| tarifC
    tarifA --> biayaDasar
    tarifB --> biayaDasar
    tarifC --> biayaDasar
    biayaDasar --> prioritas
    prioritas -->|Ya| prioritasYa
    prioritas -->|Tidak| prioritasTidak
    prioritasYa --> asuransi
    prioritasTidak --> asuransi
    asuransi -->|Ya| asuransiYa
    asuransi -->|Tidak| asuransiTidak
    asuransiYa --> total
    asuransiTidak --> total
    total --> output
    output --> selesai

    classDef terminal fill:#d5e8d4,stroke:#82b366,color:#000
    classDef decision fill:#fff2cc,stroke:#d6b656,color:#000
    classDef io fill:#dae8fc,stroke:#6c8ebf,color:#000
    class start,selesai terminal
    class zona,prioritas,asuransi decision
    class input,output io
```

## Penjelasan Langkah

| No | Langkah | Keterangan |
|----|---------|------------|
| 1 | **Input Data** | Nomor paket, berat aktual (kg), dimensi P × L × T (cm), zona tujuan (A/B/C), jenis layanan, nilai barang, dan pilihan asuransi. |
| 2 | **Berat Volumetrik** | `(Panjang × Lebar × Tinggi) / 6000` |
| 3 | **Berat Tagihan** | `CEIL( MAX(Berat Aktual, Berat Volumetrik) )`, diambil yang terbesar lalu dibulatkan ke atas. |
| 4 | **Tentukan Tarif** | Berdasarkan zona tujuan (lihat tabel tarif). |
| 5 | **Biaya Dasar** | `Berat Tagihan × Tarif` |
| 6 | **Cek Layanan Prioritas** | Jika Prioritas, Biaya Dasar dikalikan 1,4. Jika tidak, tetap. |
| 7 | **Cek Asuransi** | Jika dipilih: `MAX(Nilai Barang × 1%, Rp 5.000)`. Jika tidak: Rp 0. |
| 8 | **Total Biaya** | `Biaya Dasar + Biaya Asuransi` |
| 9 | **Output** | Nomor paket, berat tagihan, biaya dasar, biaya asuransi, dan total biaya. |

## Tabel Tarif per Zona

| Zona | Tarif per kg |
|------|--------------|
| A | Rp 8.000 |
| B | Rp 12.000 |
| C | Rp 18.000 |

## Aturan Bisnis

- **Pembagi volumetrik:** 6000
- **Pembulatan:** berat tagihan selalu dibulatkan ke atas (`CEIL`) ke kilogram penuh.
- **Layanan Prioritas:** pengali 1,4 pada biaya dasar.
- **Asuransi:** 1% dari nilai barang, dengan minimum Rp 5.000.
- **Catatan:** asuransi tidak ikut dikalikan faktor Prioritas, karena pengali hanya diterapkan pada Biaya Dasar.

## Contoh Perhitungan

**Data:** berat aktual 2 kg, dimensi 40 × 30 × 20 cm, Zona B, layanan Prioritas, nilai barang Rp 1.000.000, asuransi Ya.

1. Berat volumetrik = (40 × 30 × 20) / 6000 = 24.000 / 6000 = **4 kg**
2. Berat tagihan = CEIL(MAX(2, 4)) = **4 kg**
3. Tarif Zona B = **Rp 12.000/kg**
4. Biaya dasar = 4 × 12.000 = **Rp 48.000**
5. Prioritas: 48.000 × 1,4 = **Rp 67.200**
6. Asuransi = MAX(1.000.000 × 1%, 5.000) = MAX(10.000, 5.000) = **Rp 10.000**
7. Total biaya = 67.200 + 10.000 = **Rp 77.200**
