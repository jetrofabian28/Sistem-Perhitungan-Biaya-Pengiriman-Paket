#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct RekapPengiriman {
    int zonaA = 0;
    int zonaB = 0;
    int zonaC = 0;
    int reguler = 0;
    int prioritas = 0;
    int menggunakanBeratVolumetrik = 0;
    double totalBeratAktual = 0;
    double totalBeratTagihan = 0;
    double totalAsuransi = 0;
    double totalPendapatan = 0;
    double biayaTertinggi = -1;
    string nomorPaketBiayaTertinggi;
};

int main() {
    int jumlah_paket;
    cout << "Masukkan jumlah paket: ";
    if (!(cin >> jumlah_paket) || jumlah_paket <= 0) {
        cerr << "Jumlah paket harus berupa bilangan bulat lebih dari 0." << endl;
        return 1;
    }

    RekapPengiriman rekap;
    const double tarifZonaA = 8000;
    const double tarifZonaB = 12000;
    const double tarifZonaC = 18000;

    cout << fixed << setprecision(2);

    for (int i = 1; i <= jumlah_paket; ++i) {
        string nomor_paket;
        double nilai_barang;
        double berat_aktual;
        double panjang;
        double lebar;
        double tinggi;
        char zona_tujuan;
        char pilihan_asuransi;
        int jenis_pelayanan;

        cout << "\n=== Data Paket " << i << " ===" << endl;
        cout << "Masukkan Nomor Paket: ";
        if (!(cin >> nomor_paket)) {
            cerr << "Nomor paket tidak valid." << endl;
            return 1;
        }

        cout << "Masukkan nilai Barang (Rp): ";
        if (!(cin >> nilai_barang) || !isfinite(nilai_barang) || nilai_barang < 0) {
            cerr << "Nilai barang harus berupa angka yang tidak negatif." << endl;
            return 1;
        }

        cout << "Masukkan Berat Aktual (kg): ";
        if (!(cin >> berat_aktual) || !isfinite(berat_aktual) || berat_aktual <= 0) {
            cerr << "Berat aktual harus berupa angka lebih dari 0." << endl;
            return 1;
        }

        cout << "Masukkan Panjang (cm): ";
        if (!(cin >> panjang) || !isfinite(panjang) || panjang <= 0) {
            cerr << "Panjang harus berupa angka lebih dari 0." << endl;
            return 1;
        }

        cout << "Masukkan Lebar (cm): ";
        if (!(cin >> lebar) || !isfinite(lebar) || lebar <= 0) {
            cerr << "Lebar harus berupa angka lebih dari 0." << endl;
            return 1;
        }

        cout << "Masukkan Tinggi (cm): ";
        if (!(cin >> tinggi) || !isfinite(tinggi) || tinggi <= 0) {
            cerr << "Tinggi harus berupa angka lebih dari 0." << endl;
            return 1;
        }

        cout << "Masukkan Zona Tujuan (A/B/C): ";
        if (!(cin >> zona_tujuan)) {
            cerr << "Zona tujuan tidak valid." << endl;
            return 1;
        }
        zona_tujuan = static_cast<char>(
            toupper(static_cast<unsigned char>(zona_tujuan)));

        double tarif_per_kg;
        if (zona_tujuan == 'A') {
            tarif_per_kg = tarifZonaA;
            ++rekap.zonaA;
        } else if (zona_tujuan == 'B') {
            tarif_per_kg = tarifZonaB;
            ++rekap.zonaB;
        } else if (zona_tujuan == 'C') {
            tarif_per_kg = tarifZonaC;
            ++rekap.zonaC;
        } else {
            cerr << "Zona tujuan harus A, B, atau C." << endl;
            return 1;
        }

        cout << "Jenis Pelayanan (1. Reguler, 2. Prioritas): ";
        if (!(cin >> jenis_pelayanan) ||
            (jenis_pelayanan != 1 && jenis_pelayanan != 2)) {
            cerr << "Jenis pelayanan harus 1 (Reguler) atau 2 (Prioritas)." << endl;
            return 1;
        }

        cout << "Apakah ingin menggunakan asuransi? (Y/N): ";
        if (!(cin >> pilihan_asuransi)) {
            cerr << "Pilihan asuransi tidak valid." << endl;
            return 1;
        }
        pilihan_asuransi = static_cast<char>(
            toupper(static_cast<unsigned char>(pilihan_asuransi)));
        if (pilihan_asuransi != 'Y' && pilihan_asuransi != 'N') {
            cerr << "Pilihan asuransi harus Y atau N." << endl;
            return 1;
        }

        const double berat_volumetrik = (panjang * lebar * tinggi) / 6000;
        const bool menggunakanBeratVolumetrik = berat_volumetrik > berat_aktual;
        const double berat_tagihan =
            ceil(max(berat_aktual, berat_volumetrik));
        const double biaya_dasar = berat_tagihan * tarif_per_kg;
        const double biaya_tambahan =
            jenis_pelayanan == 2 ? 0.40 * biaya_dasar : 0;
        double biaya_asuransi = 0;

        if (pilihan_asuransi == 'Y') {
            biaya_asuransi = max(0.01 * nilai_barang, 5000.0);
        }

        const double total_biaya =
            biaya_dasar + biaya_tambahan + biaya_asuransi;

        if (jenis_pelayanan == 1) {
            ++rekap.reguler;
        } else {
            ++rekap.prioritas;
        }
        if (menggunakanBeratVolumetrik) {
            ++rekap.menggunakanBeratVolumetrik;
        }

        rekap.totalBeratAktual += berat_aktual;
        rekap.totalBeratTagihan += berat_tagihan;
        rekap.totalAsuransi += biaya_asuransi;
        rekap.totalPendapatan += total_biaya;

        if (total_biaya > rekap.biayaTertinggi) {
            rekap.biayaTertinggi = total_biaya;
            rekap.nomorPaketBiayaTertinggi = nomor_paket;
        }

        cout << "\n--- Rincian Biaya Paket " << nomor_paket << " ---" << endl;
        cout << "Zona tujuan: " << zona_tujuan << endl;
        cout << "Berat volumetrik: " << berat_volumetrik << " kg" << endl;
        cout << "Berat tagihan: " << berat_tagihan << " kg" << endl;
        cout << "Biaya dasar: Rp " << biaya_dasar << endl;
        cout << "Biaya tambahan pelayanan: Rp " << biaya_tambahan << endl;
        cout << "Biaya asuransi: Rp " << biaya_asuransi << endl;
        cout << "Total biaya: Rp " << total_biaya << endl;
    }

    cout << "\n========== REKAPITULASI PENGIRIMAN ==========" << endl;
    cout << "Jumlah paket zona A: " << rekap.zonaA << endl;
    cout << "Jumlah paket zona B: " << rekap.zonaB << endl;
    cout << "Jumlah paket zona C: " << rekap.zonaC << endl;
    cout << "Jumlah paket reguler: " << rekap.reguler << endl;
    cout << "Jumlah paket prioritas: " << rekap.prioritas << endl;
    cout << "Total berat aktual: " << rekap.totalBeratAktual << " kg" << endl;
    cout << "Total berat tagihan: " << rekap.totalBeratTagihan << " kg" << endl;
    cout << "Paket menggunakan berat volumetrik: "
         << rekap.menggunakanBeratVolumetrik << endl;
    cout << "Total asuransi: Rp " << rekap.totalAsuransi << endl;
    cout << "Total pendapatan: Rp " << rekap.totalPendapatan << endl;
    cout << "Paket dengan biaya tertinggi: "
         << rekap.nomorPaketBiayaTertinggi << " (Rp "
         << rekap.biayaTertinggi << ")" << endl;

    return 0;
}
