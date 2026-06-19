# Will They Survive - How to Run

## Requirement

Program ditulis dalam C dan memakai `windows.h`

Pastikan compiler C seperti GCC/MinGW sudah tersedia.

```powershell
gcc --version
```

## Cara Compile

Dari folder yang berisi `program.c`, jalankan:

```powershell
gcc program.c -o program.exe
```

Jika compiler meminta library matematika untuk `fmod`, gunakan:

```powershell
gcc program.c -o program.exe -lm
```

## Cara Run

Jalankan program:

```powershell
.\program.exe
```

Program akan meminta input secara interaktif:

```text
Masukkan dimensi layout!
Masukkan panjang layout:
Masukkan lebar layout:
Masukkan MAP!
```

## Format Input

Urutan input adalah:

```text
<jumlah_baris>
<jumlah_kolom>
<isi_peta_baris_1>
<isi_peta_baris_2>
...
<isi_peta_baris_n>
```

Keterangan:

- `jumlah_baris` adalah panjang layout, yaitu banyaknya baris pada peta.
- `jumlah_kolom` adalah lebar layout, yaitu banyaknya kolom pada peta.
- Nilai baris dan kolom harus berada pada rentang `1` sampai `100`.
- Setelah dimensi, masukkan tepat `jumlah_baris * jumlah_kolom` karakter peta.
- Karakter boleh dipisahkan dengan spasi atau baris baru karena program membaca input dengan `scanf(" %c", &val)`.

## Simbol Peta

| Simbol | Arti                                        |
| ------ | ------------------------------------------- |
| `W`    | Warga yang harus bergerak menuju titik aman |
| `S`    | Titik aman atau tujuan warga                |
| `F`    | Sumber api                                  |
| `0`    | Sel kosong yang dapat dilewati              |
| `X`    | Sel terbakar, muncul saat simulasi berjalan |

BFS hanya menganggap `0`, `W`, dan `S` sebagai sel yang bisa dilewati. Simbol lain, termasuk `F` dan `X`, tidak dianggap sebagai jalur valid.

## Contoh Input

```text
9
9
W 0 0 0 X 0 0 0 S
0 0 0 0 X X 0 0 0
0 0 0 0 X 0 0 0 0
0 0 0 0 0 0 X 0 0
0 0 W 0 0 X X 0 0
0 0 0 0 0 0 0 X X
0 0 0 0 0 0 0 0 W
F 0 0 0 0 0 0 0 0
0 0 0 0 F 0 X 0 0
```

Penjelasan contoh:

- Peta berukuran `9 x 9`.
- Warga berada pada koordinat `(0,0)`, `(4,2)`, dan `(6,8)`.
- Titik aman berada di kanan atas, yaitu koordinat `(0,8)`.
- Api berada pada koordinat `(7,0)` dan `(8,4)`.
- Simbol `X` berperan sebagai penghalang atau area terbakar yang tidak dapat dilewati BFS.
- BFS akan mencari jalur terpendek dari setiap `W` menuju `S` dengan menghindari `X` dan `F`.
- Pada implementasi `program.c` saat ini, posisi api yang dipakai untuk penyebaran adalah posisi `F` terakhir yang terbaca saat scan peta, yaitu `(8,4)`.

## Menjalankan dengan File Input

Program juga bisa menyimpan input ke file, misalnya `input.txt`:

```text
9
9
W 0 0 0 X 0 0 0 S
0 0 0 0 X X 0 0 0
0 0 0 0 X 0 0 0 0
0 0 0 0 0 0 X 0 0
0 0 W 0 0 X X 0 0
0 0 0 0 0 0 0 X X
0 0 0 0 0 0 0 0 W
F 0 0 0 0 0 0 0 0
0 0 0 0 F 0 X 0 0
```

Lalu jalankan:

```powershell
.\program.exe < input.txt
```

## Ringkasan Alur Program

1. Program membaca ukuran peta.
2. Program membaca isi peta.
3. Untuk setiap `W`, program menjalankan BFS menuju `S`.
4. Jalur hasil BFS disimpan sebagai urutan koordinat.
5. Simulasi berjalan per langkah waktu.
6. Warga bergerak mengikuti jalur BFS.
7. Api menyebar dari titik `F`.
8. Program menghitung jumlah warga yang selamat dan terbakar.

## Catatan Input

Gunakan peta yang memiliki minimal:

- satu `W`,
- satu `S`,
- satu `F`.

Pastikan setiap warga memiliki jalur menuju `S`. Program ini belum menangani kasus gagal menemukan jalur secara eksplisit, sehingga input yang tidak memiliki jalur aman dapat membuat hasil simulasi tidak valid.
