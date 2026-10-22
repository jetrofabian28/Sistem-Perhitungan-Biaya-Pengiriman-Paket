**Penanggung jawab:** Aning Dwi Setyowati / 322610002

## Flowchart

### Gambar Diagram Alir 

> - Garis pada diagram dibuat lurus (siku-siku). Kode Mermaid di bawah memakai `curve: linear` agar garisnya juga lurus; salin ke [mermaid.live](https://mermaid.live) untuk diekspor sebagai **SVG** atau **PNG**.

---

### Kode Sumber Diagram Alir (Mermaid)

```mermaid
%%{init: {"flowchart": {"curve": "linear"}}}%%
flowchart TD
    S1([Mulai]) --> S2["Siapkan rekap:<br>zonaA = 0, zonaB = 0, zonaC = 0<br>paketReguler = 0, paketPrioritas = 0<br>paketVolumetrik = 0<br>sumBeratAktual = 0, sumBeratTagihan = 0<br>sumAsuransi = 0, sumPendapatan = 0<br>biayaMaks = -1, paketMaks = '-'"]

    S2 --> S3[/"Input jumlahPaket"/]
    S3 --> S4{"jumlahPaket <= 0?"}
    S4 -- Ya --> S5[/"Tampilkan pesan kesalahan"/]
    S5 --> S99([Selesai])
    S4 -- Tidak --> S6["i = 1"]

    S6 --> S7{"i <= jumlahPaket?"}
    S7 -- Tidak --> S30

    S7 -- Ya --> S8[/"Input data paket ke-i dari Modul A"/]
    S8 --> S9["Hitung dari Modul A:<br>beratVolumetrik, beratTagihan,<br>biayaAsuransi, totalBiaya"]

    S9 --> S10{"zona = A?"}
    S10 -- Ya --> S11["zonaA = zonaA + 1"]
    S10 -- Tidak --> S12{"zona = B?"}
    S12 -- Ya --> S13["zonaB = zonaB + 1"]
    S12 -- Tidak --> S14["zonaC = zonaC + 1"]

    S11 --> S15{"layanan = Reguler?"}
    S13 --> S15
    S14 --> S15
    S15 -- Ya --> S16["paketReguler = paketReguler + 1"]
    S15 -- Tidak --> S17["paketPrioritas = paketPrioritas + 1"]

    S16 --> S18{"beratVolumetrik > beratAktual?"}
    S17 --> S18
    S18 -- Ya --> S19["paketVolumetrik = paketVolumetrik + 1"]
    S18 -- Tidak --> S20
    S19 --> S20["sumBeratAktual = sumBeratAktual + beratAktual<br>sumBeratTagihan = sumBeratTagihan + beratTagihan<br>sumAsuransi = sumAsuransi + biayaAsuransi<br>sumPendapatan = sumPendapatan + totalBiaya"]

    S20 --> S21{"totalBiaya > biayaMaks?"}
    S21 -- Ya --> S22["biayaMaks = totalBiaya<br>paketMaks = nomorPaket"]
    S21 -- Tidak --> S23
    S22 --> S23["i = i + 1"]
    S23 --> S7

    S30[/"Tampilkan Rekapitulasi Pengiriman:<br>Jumlah paket per zona A, B, C<br>Jumlah paket reguler dan prioritas<br>Total berat aktual dan berat tagihan<br>Jumlah paket berat volumetrik<br>Total asuransi dan total pendapatan<br>Paket dengan biaya tertinggi"/]
    S30 --> S99
```
