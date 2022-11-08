# Wordle-Romana

### Proiect ASC 2022-2023
#### Facultatea de Matematica si Informatica

### Autori:
- [Coltos Radu-Mihai](https://github.com/radubig) (Grupa 151)
- [Mera Jean-Robert](https://github.com/MeraJean) (Grupa 151)

## Introducere

_TBA_

## Compilare
Compilarea se face folosind CMake.

## Executare
Proiectul nostru utilizeaza libraria boost pentru a rula [**WordleGame**](#wordlegame) ca un subproces al procesului [**WordlePlayer**](#wordleplayer) pentru a permite comunicarea intre programe.

- Pentru a executa proiectul nostru si a juca in mod automat un joc folosind un cuvant aleatoriu, ruleaza `./WordlePlayer -auto`
- Pentru a executa jocul Wordle in mod traditional folosind consola pentru input si output, ruleaza `./WordleGame`
- Pentru a executa jucatorul Wordle in mod traditional folosind consola pentru input si output, ruleaza `./WordlePlayer`

## Programe

### FirstGuessAnalyzer

Acest program determina cel mai bun cuvant cu care sa se inceapa. Deoarece acest pas dureaza mult, prima incercare este hard-coded in [**StatisticsGenerator**](#statisticsgenerator) si [**WordlePlayer**](#wordleplayer).

Acest program genereaza fisierul [`best_first_guess.txt`](data/best_first_guess.txt), dar acesta nu este folosit de alte programe.

### SecondGuessAnalyzer

Acest program determina cel mai bun cuvant pentru a doua incercare, in functie de informatia obtinuta dupa prima incercare. Deoarece si acest pas poate dura ceva timp, cele 243 de posibilitati sunt cache-uite.

Acest program genereaza fisierul [`second_guess_cache.txt`](data/second_guess_cache.txt), care este folosit de [**StatisticsGenerator**](#statisticsgenerator) si [**WordlePlayer**](#wordleplayer).

### StatisticsGenerator

Acest program genereaza statistici cu privire la numarul mediu de incercari necesare pentru a gasi orice cuvant din dictionar.

Acest program genereaza fisierele [`solutii.txt`](data/solutii.txt) si [`stats.txt`](data/stats.txt), dar acestea nu sunt folosite de alte programe.

### WordleGame

Acest program contine implementarea propriu-zisa a jocului Wordle.

Acest program necesita fisierul [`cuvinte.txt`](data/cuvinte.txt) pentru a rula.

### WordlePlayer

Acest program contine implementarea propiu-zisa a jucatorului Wordle ce gaseste solutia in cat mai putine incercari.

Acest program necesita fisierele [`cuvinte.txt`](data/cuvinte.txt) si [`second_guess_cache.txt`](data/second_guess_cache.txt) pentru a rula.
