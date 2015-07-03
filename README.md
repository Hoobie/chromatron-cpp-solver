# Hubert Słojewski
### Projekt z przedmiotu Algorytmy dla Problemów Trudnych Obliczeniowo
### Program rozwiązujący zadania oparte na grze Chromatron (C++ 11)
![AGH](http://eurostudy.info/images/content/agh_logo_agh.jpg)
### Rok akademicki: 2014/2015

###Spis treści:
1. Zarys algorytmu.
2. Pomysły optymalizacji algorytmu.
3. Możliwości dalszego rozwoju.

###Ad. 1. Zarys algorytmu:
Zastosowałem algorytm typu brute-force z optymalizacjami, które biorą pod uwagę tylko "sensowne" stawianie luster.
Do opisu algorytmu użyłem pseudokodu, przypominającego język C.
```C++
// board - 2-wymiarowa plansza zawierająca obiekty typu Cell
// Cell - obiekt posiadający pola, takie jak: x, y, kierunek, kolor, lista promieni wraz z ich kierunkami i kolorami
// mirrorsSnapshots - mapa zawierająca hashcode'y wykorzystanych ułożeń luster
bool solve(Cell board[][], int width, int height, Cell allMirrors[], Cell mirrorsToUse[], map mirrorsSnapshots, Cell lasers[], bool reverse) {
    // wyczyść planszę z promieni
    clearRaysFromTheBoard(board, width, height); 
    
    // przerysuj promienie
    addRaysToTheBoard(board, width, height);
    
    if (isBoardCompleted(board, width, height)) {
        // jeśli plansza jest rozwiązana, zakończ sukcesem
        return true; 
    }
    
    if (mirrorsToUse.empty()) {
        // jeśli nie ma już luster do użycia, to zakończ porażką
        return false; 
    }
    
    // ustaw początkowe wartości do przeglądania planszy
    int x, y, step = getSteps(revers); 
    
    for (y; y > 0 && y < height; y += step) {
        for (x; x > 0 && x < width; x += step) {
            // pobierz komórkę
            Cell cell = board[x][y];
            if (cell->hasType(NONE) && cell->hasRays()) {
                // jeśli komórka nie jest urządzeniem optycznym oraz ma w sobie promienie
                for (mirror : mirrorsToUse) {
                    // dla wszystkich luster do użycia
                    int mirrorDirections = getMirrorDirections(mirror->getType());
                    for (int mirrorDirection = 0; mirrorDirection < mirrorDirections; mirrorDirection++) {
                        // dla każdego kierunku
                        if (isMirrorDirectionReasonable(mirrorDirection) { 
                            // jeśli warto postawić lustro w tym kierunku    
                            
                             // wylicz hashcode ułożenia luster
                            long mirrorsHashcode = calculateHashcodeForMirrors(allMirrors, mirror);
                            if (mirrorsSnapshots[mirrorsHashcode]) {
                                // jeśli już sprawdzono takie ułożenie luster to omiń ten obieg pętli
                                continue; 
                            }
                            mirrorsSnapshots[mirrorsHashcode] = true;
                            
                            // postaw lustro na planszy
                            putMirror(board, width, height, x, y, mirror, mirrorDirection); 
                            
                            mirrorsToUse.erase(mirror);
                            
                            if (solve(board, width, height, allMirrors, mirrorsCopy, mirrorsSnapshots, lasers, reverse)) {
                                // jeśli z postawionym lustrem udało się rozwiązać zadanie, to zakończ sukcesem
                                return true; 
                            }
                            
                            // przywróć komórkę zamiast lustra
                            board[x][y] = cell; 
                             // przywróć lustro do ponownego użycia
                            mirror->reset();
                        }
                    }
                    // następnym razem przeglądaj planszę w odwrotnym kierunku
                    reverse = !reverse;
                    if (solve(board, width, height, allMirrors, mirrorsToUse, mirrorsSnapshots, lasers, reverse)) {
                        // jeśli bez stawiania lustra udało się rozwiązać zadanie, to zakończ sukcesem
                        return true; 
                    }
                }
            }
        }
    }
    // jeśli nie udało się znaleźć rozwiązania, to zakończ porażką
    return false;
}
```

Do sporządzenia dokumentacji zastosowano język Markdown.
