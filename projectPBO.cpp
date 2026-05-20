#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ================= CLASS SAMPAH =================
class Sampah {
protected:
    string jenis;
    float berat;
    float poin;

public:
    Sampah(string jenis, float berat, float poin) {
        this->jenis = jenis;
        this->berat = berat;
        this->poin = poin;
    }

    virtual void tampilInfo() {
        cout << "Jenis Sampah : " << jenis << endl;
        cout << "Berat        : " << berat << " kg" << endl;
        cout << "Poin         : " << poin << endl;
    }

    float getPoin() {
        return poin;
    }

    float getBerat() {
        return berat;
    }
};

// ================= INHERITANCE =================
class Plastik : public Sampah {
public:
    Plastik(float berat)
        : Sampah("Plastik", berat, berat * 10) {}
};

class Organik : public Sampah {
public:
    Organik(float berat)
        : Sampah("Organik", berat, berat * 5) {}
};

class Logam : public Sampah {
public:
    Logam(float berat)
        : Sampah("Logam", berat, berat * 15) {}
};

// ================= CLASS USER =================
class User {
private:
    string nama;

    // poin aktif untuk ditukar
    float totalPoin;

    // poin total untuk ranking
    float totalPoinRanking;

    float totalBerat;

    vector<Sampah*> daftarSampah;

public:
    User(string nama) {
        this->nama = nama;
        totalPoin = 0;
        totalPoinRanking = 0;
        totalBerat = 0;
    }

    string getNama() {
        return nama;
    }

    float getPoin() {
        return totalPoin;
    }

    float getPoinRanking() {
        return totalPoinRanking;
    }

    float getBerat() {
        return totalBerat;
    }

    // ================= LEVEL USER =================
    string getLevel() {

        if (totalPoinRanking >= 0 && totalPoinRanking <= 100) {
            return "Bronze";
        }
        else if (totalPoinRanking >= 101 && totalPoinRanking <= 500) {
            return "Silver";
        }
        else {
            return "Gold";
        }
    }

    // ================= TAMBAH SAMPAH =================
    void tambahSampah(Sampah* s) {

        daftarSampah.push_back(s);

        totalPoin += s->getPoin();

        // untuk ranking
        totalPoinRanking += s->getPoin();

        totalBerat += s->getBerat();

        cout << "\nSampah berhasil ditambahkan!" << endl;
        cout << "Poin didapat : " << s->getPoin() << endl;
        cout << "Level anda sekarang : " << getLevel() << endl;
    }

    // ================= LIHAT DATA SAMPAH =================
    void lihatDataSampah() {

        cout << "\n===== DATA SAMPAH =====" << endl;

        if (daftarSampah.empty()) {
            cout << "Belum ada data sampah.\n";
            return;
        }

        for (int i = 0; i < daftarSampah.size(); i++) {

            cout << "\nData ke-" << i + 1 << endl;
            daftarSampah[i]->tampilInfo();
        }

        cout << "\n==========================" << endl;
        cout << "Total Berat : " << totalBerat << " kg" << endl;
        cout << "Total Poin  : " << totalPoin << endl;
    }

    // ================= LIHAT DATA USER =================
    void lihatDataUser() {

        cout << "\n===== DATA USER =====" << endl;
        cout << "Nama User        : " << nama << endl;
        cout << "Poin Aktif       : " << totalPoin << endl;
        cout << "Total Poin Rank  : " << totalPoinRanking << endl;
        cout << "Total Berat      : " << totalBerat << " kg" << endl;
        cout << "Level User       : " << getLevel() << endl;
    }

    // ================= TUKAR POIN =================
    void tukarPoin() {

        if (totalPoin == 0) {

            cout << "\nAnda belum menyetorkan sampah." << endl;
            cout << "Poin anda : 0\n";
            return;
        }

        float poin;

        cout << "\n===== TUKAR POIN =====" << endl;
        cout << "10 poin = 1.000 rupiah" << endl;
        cout << "Total poin anda : " << totalPoin << endl;

        cout << "Masukkan poin yang ingin ditukar : ";
        cin >> poin;

        if (poin > totalPoin) {

            cout << "Poin tidak mencukupi!\n";
        }
        else {

            float uang = (poin / 10) * 1000;

            totalPoin -= poin;

            cout << "\nPoin berhasil ditukar!" << endl;
            cout << "Uang didapat : Rp" << uang << endl;
            cout << "Sisa poin aktif : " << totalPoin << endl;
        }
    }
};

// ================= VALIDASI INPUT =================
bool validasiInput(string input) {

    if (input.find(',') != string::npos) {

        cout << "Anda salah menggunakan angka desimal, harus pakai titik (.)\n";
        return false;
    }

    if (input.find('/') != string::npos) {

        cout << "Input tidak valid! Harus menggunakan titik (.)\n";
        return false;
    }

    int titik = 0;

    for (char c : input) {

        if (c == '.') {
            titik++;
        }

        else if (!isdigit(c)) {

            cout << "Input tidak valid!\n";
            return false;
        }
    }

    if (titik > 1) {

        cout << "Format desimal salah!\n";
        return false;
    }

    return true;
}

// ================= MAIN =================
int main() {

    vector<User> daftarUser;

    int menuAwal;

    do {

        cout << "\n======================================" << endl;
        cout << " SMART WASTE MANAGEMENT SYSTEM " << endl;
        cout << "======================================" << endl;

        cout << "1. Tambah User" << endl;
        cout << "2. Login User" << endl;
        cout << "3. Lihat Ranking" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih menu : ";
        cin >> menuAwal;

        // ================= TAMBAH USER =================
        if (menuAwal == 1) {

            string nama;

            cout << "Masukkan username : ";
            cin >> nama;

            daftarUser.push_back(User(nama));

            cout << "User berhasil ditambahkan!\n";
        }

        // ================= LOGIN USER =================
        else if (menuAwal == 2) {

            string nama;
            bool ditemukan = false;

            cout << "Masukkan username : ";
            cin >> nama;

            for (int i = 0; i < daftarUser.size(); i++) {

                if (daftarUser[i].getNama() == nama) {

                    ditemukan = true;

                    int pilihan;
                    string inputBerat;
                    float berat;

                    do {

                        cout << "\n===== MENU USER =====" << endl;
                        cout << "1. Input Sampah Plastik (10 poin/kg)" << endl;
                        cout << "2. Input Sampah Organik (5 poin/kg)" << endl;
                        cout << "3. Input Sampah Logam (15 poin/kg)" << endl;
                        cout << "4. Lihat Data Sampah" << endl;
                        cout << "5. Lihat Data User" << endl;
                        cout << "6. Tukar Poin" << endl;
                        cout << "7. Logout" << endl;
                        cout << "Pilih menu : ";
                        cin >> pilihan;

                        switch (pilihan) {

                        // ================= PLASTIK =================
                        case 1:

                            cout << "\n=== Sampah Plastik ===" << endl;
                            cout << "Setiap 1 kg mendapatkan 10 poin" << endl;

                            cout << "\n===== LEVEL USER =====" << endl;
                            cout << "0 - 100 poin   : Bronze" << endl;
                            cout << "101 - 500 poin : Silver" << endl;
                            cout << "501++ poin     : Gold" << endl;

                            cout << "\nMasukkan berat sampah plastik : ";
                            cin >> inputBerat;

                            if (!validasiInput(inputBerat))
                                break;

                            berat = stof(inputBerat);

                            if (berat <= 0) {

                                cout << "Berat tidak valid!\n";
                                break;
                            }

                            daftarUser[i].tambahSampah(new Plastik(berat));
                            break;

                        // ================= ORGANIK =================
                        case 2:

                            cout << "\n=== Sampah Organik ===" << endl;
                            cout << "Setiap 1 kg mendapatkan 5 poin" << endl;

                            cout << "\n===== LEVEL USER =====" << endl;
                            cout << "0 - 100 poin   : Bronze" << endl;
                            cout << "101 - 500 poin : Silver" << endl;
                            cout << "501++ poin     : Gold" << endl;

                            cout << "\nMasukkan berat sampah organik : ";
                            cin >> inputBerat;

                            if (!validasiInput(inputBerat))
                                break;

                            berat = stof(inputBerat);

                            if (berat <= 0) {

                                cout << "Berat tidak valid!\n";
                                break;
                            }

                            daftarUser[i].tambahSampah(new Organik(berat));
                            break;

                        // ================= LOGAM =================
                        case 3:

                            cout << "\n=== Sampah Logam ===" << endl;
                            cout << "Setiap 1 kg mendapatkan 15 poin" << endl;

                            cout << "\n===== LEVEL USER =====" << endl;
                            cout << "0 - 100 poin   : Bronze" << endl;
                            cout << "101 - 500 poin : Silver" << endl;
                            cout << "501++ poin     : Gold" << endl;

                            cout << "\nMasukkan berat sampah logam : ";
                            cin >> inputBerat;

                            if (!validasiInput(inputBerat))
                                break;

                            berat = stof(inputBerat);

                            if (berat <= 0) {

                                cout << "Berat tidak valid!\n";
                                break;
                            }

                            daftarUser[i].tambahSampah(new Logam(berat));
                            break;

                        // ================= DATA SAMPAH =================
                        case 4:
                            daftarUser[i].lihatDataSampah();
                            break;

                        // ================= DATA USER =================
                        case 5:
                            daftarUser[i].lihatDataUser();
                            break;

                        // ================= TUKAR POIN =================
                        case 6:
                            daftarUser[i].tukarPoin();
                            break;

                        // ================= LOGOUT =================
                        case 7:
                            cout << "\nLogout berhasil.\n";
                            break;

                        default:
                            cout << "Pilihan tidak valid!\n";
                        }

                    } while (pilihan != 7);
                }
            }

            if (!ditemukan) {
                cout << "User tidak ditemukan!\n";
            }
        }

        // ================= RANKING =================
        else if (menuAwal == 3) {

            if (daftarUser.empty()) {

                cout << "\nBelum ada user.\n";
            }
            else {

                sort(daftarUser.begin(), daftarUser.end(),
                    [](User a, User b) {
                        return a.getPoinRanking() > b.getPoinRanking();
                    });

                cout << "\n===== RANKING USER =====" << endl;

                for (int i = 0; i < daftarUser.size(); i++) {

                    cout << i + 1 << ". "
                         << daftarUser[i].getNama()
                         << " | Total Poin : "
                         << daftarUser[i].getPoinRanking()
                         << " | Level : "
                         << daftarUser[i].getLevel()
                         << endl;
                }
            }
        }

        // ================= KELUAR =================
        else if (menuAwal == 4) {

            cout << "\nTerima kasih telah menggunakan program.\n";
        }

        else {

            cout << "Pilihan tidak valid!\n";
        }

    } while (menuAwal != 4);

    return 0;
}