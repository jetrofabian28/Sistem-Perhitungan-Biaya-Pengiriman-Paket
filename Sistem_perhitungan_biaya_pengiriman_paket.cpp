#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
    // variabel input
    string nomor_paket;
    double Berat_aktual,panjang,lebar,tinggi,nilai_barang;
    char zona_tujuan,Pilihan_asuransi;
    int jenis_pelayanan;

// Input Data Pengguna

cout << "masukkan nilai Barang (Rp): ";
cin >> nilai_barang;
cout << "Masukkan Nomor Paket: ";
cin >> nomor_paket;
cout << "Masukkan Berat Aktual (kg): ";
cin >> Berat_aktual;
cout << "Masukkan Panjang (cm): "; 
cin >> panjang;

cout << "Masukkan Lebar (cm): "; 
cin >> lebar;

cout << "Masukkan Tinggi (cm): "; 
cin >> tinggi;

cout << "Masukkan Zona_Tujuan (A/B/C): ";
cin >> zona_tujuan;
cout << "jenis Pelayanan (1. Reguler, 2. Prioritas ): ";
cin >> jenis_pelayanan;
cout << "Apakah ingin menggunakan asuransi? (Y/N): ";
cin >> Pilihan_asuransi;
return 0;
}