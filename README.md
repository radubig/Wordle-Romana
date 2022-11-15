# Wordle-Romana

### Proiect ASC 2022-2023
#### Facultatea de Matematica si Informatica

### Autori:
- [Coltos Radu-Mihai](https://github.com/radubig) (Grupa 151)
- [Mera Jean-Robert](https://github.com/MeraJean) (Grupa 151)

## Introducere

_TBA_

## Compilare
Compilarea se face folosind CMake. <br />
Este necesara instalarea bibliotecii `Boost` pentru a putea compila programul; aceasta se poate instala folosind comanda `sudo apt-get install libboost-all-dev` . <br />
Programul a fost testat pe o distributie de Linux Debian-Based (Linux Mint 21).

## Executare
Proiectul nostru utilizeaza libraria boost pentru a rula [**WordleGame**](#wordlegame) ca un subproces al procesului [**WordlePlayer**](#wordleplayer) pentru a permite comunicarea intre programe.

- Pentru a executa proiectul nostru si a juca in mod automat un joc, ruleaza `./WordlePlayer -auto` pentru un singur cuvant aleator sau `./WordlePlayer -auto n` pentru n cuvinte aleatorii.
- Pentru a executa jocul Wordle in mod traditional folosind consola pentru input si output, ruleaza `./WordleGame`
- Pentru a executa jucatorul Wordle in mod traditional folosind consola pentru input si output, ruleaza `./WordlePlayer`

## Programe

### WordleGame

Acest program contine implementarea propriu-zisa a jocului Wordle.

Acest program necesita fisierul [`cuvinte.txt`](data/cuvinte.txt) pentru a rula.

### WordlePlayer

Acest program contine implementarea propiu-zisa a jucatorului Wordle ce gaseste solutia in cat mai putine incercari.

Acest program necesita fisierele [`cuvinte.txt`](data/cuvinte.txt) si [`second_guess_cache.txt`](data/second_guess_cache.txt) pentru a rula.

### StatisticsGenerator

Acest program a fost folosit de catre noi pentru a automatiza si a genera diverse statistici, precum: 
[`best_first_guess.txt`](data/best_first_guess.txt), unde au fost calculate entropiile initiale pentru fiecare cuvant, astfel putand sa facem prima incercare fixa pentru a economisi timp de executie;
[`second_guess_cache.txt`](data/second_guess_cache.txt), unde sunt precalculate toate posibilitatile pentru a doua incercare in functie de informatia oferita de prima incercare; acestea sunt cache-uite pentru a evita recalcularea entropiilor in al doilea pas;
[`solutii.txt`](data/solutii.txt), unde sunt afisate toate jocurile posibile cu raspunsurile incercate si 
[`stats.txt`](data/stats.txt), de unde am extras numarul medii de incercari per joc (4.00).

