**Link Git Repository:** https://github.com/pietrismarioa2q/multiprocess-prime-pipes

## 1. Obiectivul Proiectului
Implementarea unui program C++ care caută numere prime până la 10.000 folosind 10 procese paralele, comunicând intervalele de lucru și rezultatele prin pipe-uri IPC.

## 2. Diferențe de Implementare (Linux vs Windows)
- **Linux (POSIX):** S-a folosit `fork()` pentru duplicarea procesului și `pipe()` cu descriptori de fișiere standard.
- **Windows (Win32 API):** Deoarece `fork()` nu există nativ, procesul copil este creat re-executând binarul cu `--child` prin `CreateProcessA`, redirecționând `STDIN`/`STDOUT` prin pipe-uri anonime.

## 3. Rezultate
Programul a identificat corect **1.229 numere prime** în intervalul 1 - 10.000 pe ambele sisteme de operare.
EOF**Link Git Repository:** https://github.com/pietrismarioa2q/multiprocess-prime-pipes

## 1. Obiectivul Proiectului
Implementarea unui program C++ care caută numere prime până la 10.000 folosind 10 procese paralele, comunicând intervalele de lucru și rezultatele prin pipe-uri IPC.

## 2. Diferențe de Implementare (Linux vs Windows)
- **Linux (POSIX):** S-a folosit `fork()` pentru duplicarea procesului și `pipe()` cu descriptori de fișiere standard.
- **Windows (Win32 API):** Deoarece `fork()` nu există nativ, procesul copil este creat re-executând binarul cu `--child` prin `CreateProcessA`, redirecționând `STDIN`/`STDOUT` prin pipe-uri anonime.

## 3. Rezultate
Programul a identificat corect **1.229 numere prime** în intervalul 1 - 10.000 pe ambele sisteme de operare.
