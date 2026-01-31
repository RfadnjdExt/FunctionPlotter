# FunctionPlotter

**FunctionPlotter** adalah aplikasi C++ sederhana namun *powerful* untuk memvisualisasikan fungsi matematika dalam format 2D dan 3D, serta melakukan operasi kalkulus dasar.

![C++](https://img.shields.io/badge/Language-C++11-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

## Fitur Utama

### 1. Visualisasi 2D
*   Plot fungsi satu variabel `f(x)`.
*   Ekspor grafik ke format **SVG** (Scalable Vector Graphics).
*   Dilengkapi dengan grid dan label sumbu otomatis.

### 2. Visualisasi 3D Surface
*   Plot fungsi dua variabel `f(x, y)`.
*   Ekspor model 3D ke format:
    *   **.OBJ**: Model mesh standar (polos).
    *   **.PLY**: Model dengan **Heatmap Coloring** (warna berdasarkan ketinggian/z-axis), siap dibuka di MeshLab atau Blender.

### 3. Kalkulus Numerik
*   **Diferensial**: Menghitung turunan pertama `f'(x)` di titik tertentu.
*   **Integral Tentu**: Menghitung luas di bawah kurva dalam rentang `[a, b]` menggunakan metode Simpson's Rule.

## Cara Kompilasi

Pastikan Anda memiliki compiler GCC (`g++`) terinstal.

### Menggunakan Makefile (Windows)
```bash
mingw32-make  # atau 'make' jika tersedia
```

### Kompilasi Manual
```bash
g++ -std=c++11 -Wall -O2 -o FunctionPlotter main.cpp FunctionPlotter.cpp
```

## Cara Penggunaan

Jalankan program:
```bash
./FunctionPlotter
```
atau
```bash
FunctionPlotter.exe
```

### Format Penulisan Fungsi
Aplikasi mendukung operasi matematika standar:
*   **Aritmatika**: `+`, `-`, `*`, `/`, `^` (pangkat) atau `**`
*   **Trigonometri**: `sin`, `cos`, `tan`, `asin`, `acos`, `atan`
*   **Lainnya**: `sqrt`, `log`, `ln`, `exp`, `abs`
*   **Konstanta**: `pi`, `e`

**Contoh Input:**
*   2D: `x^2 + 2*x + 1`
*   2D: `sin(x) * x`
*   3D: `sin(x) * cos(y)`
*   3D: `exp(-(x^2 + y^2))`

## Output File

Program akan menghasilkan file berikut di direktori yang sama:
*   `output_2d.svg`: Buka dengan Web Browser (Chrome, Edge, dll) atau Inkscape.
*   `output_3d.obj`: Buka dengan 3D Viewer standar Windows atau Blender.
*   `output_3d.ply`: Buka dengan MeshLab atau Blender (Import PLY) untuk melihat warna gradasi.

## Lisensi
Project ini dibuat untuk tujuan edukasi kalkulus dan pemrograman C++.
