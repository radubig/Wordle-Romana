# Wordle-Romana

### Proiect ASC 2022-2023
#### Facultatea de Matematica si Informatica

### Autori:
- [Coltos Radu-Mihai](https://github.com/radubig) [\<radu-mihai.coltos@s.unibuc.ro\>](mailto:radu-mihai.coltos@s.unibuc.ro) (Grupa 151)
- [Mera Jean-Robert](https://github.com/MeraJean) [\<jean-robert.mera@s.unibuc.ro\>](mailto:jean-robert.mera@s.unibuc.ro) (Grupa 151)

## Introducere

Acest repertoriu contine codul sursa pentru proiectul Wordle.

Proiectul este scris in 2 versiuni diferite:
- **Versiunea C++** _(codul sursa in [src/](src), programele compilate in [release/](release))_
- **Versiunea x86_32 Assembly** _(codul sura in [src_asm/](src_asm), programele compilate in [release_asm/](release_asm))_

Numarul mediu de incercari este `3.9895`.  
Fisierul de solutii se afla in [data/solutii.txt](data/solutii.txt).  
Mai multe statistici legate de acest proiect se afla in folderul [data/](data).

Fisierul [CMakeLists.txt](CMakeLists.txt) contine target-urile pentru compilarea ambelor versiuni.

## Informatii versiune C++

<details>
<summary>Click pentru a extinde</summary>

### Compilare
Compilarea se face folosind CMake.

Este necesara instalarea bibliotecii `Boost` pentru a putea compila programul; aceasta se poate instala folosind comanda `sudo apt-get install libboost-all-dev`.

Programul a fost testat pe o distributie de Linux Ubuntu-based (Linux Mint 21).

### Executare
Proiectul nostru utilizeaza libraria boost pentru a rula [**WordleGame**](#wordlegame) ca un child process al procesului [**WordlePlayer**](#wordleplayer) pentru a permite comunicarea intre programe.

- Pentru a executa proiectul nostru si a juca in mod automat un joc, ruleaza `./WordlePlayer -auto` pentru un singur cuvant aleator sau `./WordlePlayer -auto n` pentru n cuvinte aleatorii.
- Pentru a executa jocul Wordle in mod traditional folosind consola pentru input si output, ruleaza `./WordleGame`
- Pentru a executa jucatorul Wordle in mod traditional folosind consola pentru input si output, ruleaza `./WordlePlayer`

Recomandam testarea ambelor moduri ale jocului pentru o experienta completa.

### Programe

#### WordleGame

Acest program contine implementarea propriu-zisa a jocului Wordle.

Acest program necesita fisierul [`cuvinte.txt`](data/cuvinte.txt) pentru a rula.

#### WordlePlayer

Acest program contine implementarea propiu-zisa a jucatorului Wordle ce gaseste solutia in cat mai putine incercari.

Acest program necesita fisierele [`cuvinte.txt`](data/cuvinte.txt) si [`second_guess_cache.txt`](data/second_guess_cache.txt) pentru a rula.

#### StatisticsGenerator

Acest program a fost folosit de catre noi pentru a automatiza si a genera diverse statistici, precum:
[`best_first_guess.txt`](data/best_first_guess.txt), unde au fost calculate entropiile initiale pentru fiecare cuvant, astfel putand sa facem prima incercare fixa pentru a economisi timp de executie;
[`second_guess_cache.txt`](data/second_guess_cache.txt), unde sunt precalculate toate posibilitatile pentru a doua incercare in functie de informatia oferita de prima incercare; acestea sunt cache-uite pentru a evita recalcularea entropiilor in al doilea pas;
[`solutii.txt`](data/solutii.txt), unde sunt afisate toate jocurile posibile cu raspunsurile incercate si
[`stats.txt`](data/stats.txt), de unde am extras numarul medii de incercari per joc (3.99).

### Detalii despre implementare

Vom denumi in continuare informatia despre fiecare cuvant incercat (modul in care se "coloreaza" literele) `pattern`.

Pentru a determina care este cea mai optima ghicire, calculam entropia tuturor cuvintelor din dictionar in raport cu cuvintele posibile ramase la un anumit moment de timp.

Cum aceasta metoda este costisitoare ca timp de executie, aplicam cateva eficientizari:
- Prima ghicire este intotdeauna `TAREI` deoarece are cea mai mare entropie; aceasta este hard-coded si astfel salvam cateva secunde ca timp de executie, totodata reducand drastic numarul cuvintelor posibile ramase (in medie de aproximativ 6 ori).
- Cum exista doar 243 de pattern-uri posibile pentru `TAREI` (3^5 sau 3 culori pentru fiecare litera), am precalculat pentru fiecare pattern cel mai optim cuvant care trebuie ghicit in continuare.
  Astfel, la acest pas este din nou evitata calcularea entropiilor si lista de cuvinte posibile ramase devine foarte mica comparativ cu cea initiala.
- In cazul in care doua cuvinte au entropii egale, il prioritizam pe cel care ar putea fi solutie.

Pattern-urile sunt siruri de 5 cifre ce codeaza culoarea unei litere: `0` daca litera este gri, `1` daca litera este verde, respectiv `2` daca litera este galben. Pentru a transmite mai eficient aceste siruri ca date, le consideram ca fiind un numar in baza 3 si le convertim in baza 10 (de exemplu sirul `10201` devine 81 + 0 + 2 * 9 + 0 + 1 = 100).
Numerele astfel convertite sunt pattern-urile transmise de `WordleGame`.

</details>

## Informatii versiune x86 Assembly

<details>
<summary>Click pentru a extinde</summary>

### Compilare
Compilarea se face folosind CMake.

Programul a fost testat pe o distributie de Linux Ubuntu-based (Linux Mint 21).

### Executare
Versiunea de Assembly utilizeaza fisiere pentru a realiza comunicarea intre [**ASM_WordleGame**](#asm_wordlegame) si [**ASM_WordlePlayer**](#asm_wordleplayer).

- Pentru a executa programul, deschide doua instante ale unui terminal si ruleaza `./ASM_WordlePlayer`, respectiv `./ASM_WordleGame`.

Este necesar ca cele doua programe sa se afle in acelasi folder, alaturi de fisierul [**cuvinte.txt**]().

### Programe

#### ASM_WordleGame

Acest program contine implementarea propriu-zisa a jocului Wordle.

Acest program necesita fisierul [`cuvinte.txt`](data/cuvinte.txt) pentru a rula.

#### ASM_WordlePlayer

Acest program contine implementarea propiu-zisa a jucatorului Wordle ce gaseste solutia in cat mai putine incercari.

Acest program necesita fisierul [`cuvinte.txt`](data/cuvinte.txt) pentru a rula.

### Detalii despre implementare
Aceasta versiune a programului foloseste sintaxa AT&T a limbajului Assembly. **NU** au fost folosite apeluri catre functii din C++; toate functiile au fost scrise de noi, inclusiv abstractizarile diferitelor syscall-uri. (Aceste abstractizari se regasesc in folderul [src_asm/_common/syscall/](src_asm/_common/syscall)). De asemnea, tot codul sursa a fost scris manual, fara ajutorul vreunui dezasamblor.

Versiunea de assembly foloseste acelasi algoritm de determinare a ghicirii optime ca versiunea C++, insa nu implementeaza toate optimizarile celeilalte versiuni (singura optimizare implementata este hard-codarea primului guess `TAREI`). Din acest motiv, media de ghicire a cuvantului va fi putin mai mare decat in versiunea C++.

</details>

## Referinte

- [Arhitectura Sistemelor de Calcul - Curs 0x02](https://cs.unibuc.ro/~crusu/asc/Arhitectura%20Sistemelor%20de%20Calcul%20(ASC)%20-%20Curs%200x02.pdf) (Cristian Rusu)
- [Arhitectura Sistemelor de Calcul - Proiect 0x00](https://cs.unibuc.ro/~crusu/asc/Arhitectura%20Sistemelor%20de%20Calcul%20(ASC)%20-%20Proiect%200x00%202022.pdf) (Cristian Rusu)
- [Arhitectura Sistemelor de Calcul Laborator - Partea 0x00](https://cs.unibuc.ro/~crusu/asc/Arhitectura%20Sistemelor%20de%20Calcul%20(ASC)%20-%20Laborator%20Partea%200x00.pdf) (Bogdan Macovei, Ruxandra Balucea, Cristian Rusu)
- [Arhitectura Sistemelor de Calcul Laborator - Partea 0x01](https://cs.unibuc.ro/~crusu/asc/Arhitectura%20Sistemelor%20de%20Calcul%20(ASC)%20-%20Laborator%20Partea%200x01.pdf) (Bogdan Macovei, Ruxandra Balucea, Cristian Rusu)
- [Intel® 64 and IA-32 Architectures Software Developer’s Manual](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html) (Intel)
- [Linux System Call Table](https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86-32_bit) (Chromium OS Docs, compiled from Linux headers)
- [Solving Wordle using information theory](https://www.youtube.com/watch?v=v68zYyaEmEA) (3Blue1Brown)
