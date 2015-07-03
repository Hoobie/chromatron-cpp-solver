# Hubert Słojewski
## Projekt z przedmiotu Algorytmy dla Problemów Trudnych Obliczeniowo
### Program rozwiązujący zadania oparte na grze Chromatron


![AGH](http://eurostudy.info/images/content/agh_logo_agh.jpg)
### Rok akademicki: 2014/2015


###Spis treści:
1. Zarys algorytmu.
2. Zastosowane pomysły optymalizacji algorytmu.
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
    addRaysToTheBoard(board, width, height, lasers);
    
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


### Ad. 2. Zastosowane pomysły optymalizacji algorytmu:
1.  Stawianie luster tylko tam, gdzie jest to opłacalne.
    * Po pierwsze lustra stawiane są tylko na promieniach.
    * Po drugie musi istnieć odbicie jakiegokolwiek promienia w kierunku środka planszy (odbicia poza planszę nie mają sensu).
    * Aby szybko sprawdzić, czy ułożenie luster się nie powtórzyło, dla każdego ułożenia wyliczany jest jego hashcode zgodnie ze wzorem:
    ```C++
    long mirrorsHashcode = 17;
    for (mirror : allMirrors) {
        mirrorsHashcode = mirrorsHashcode * 31 + mirror->getCellType();
        mirrorsHashcode = mirrorsHashcode * 31 + mirror->getX();
        mirrorsHashcode = mirrorsHashcode * 31 + mirror->getY();
        mirrorsHashcode = mirrorsHashcode * 31 + mirror->getDirection();
    }
    ```
2. Każde lustro stawiam od różnych stron planszy, co znacznie przyspiesza znalezienie rozwiązania.
3. Do sprawdzenia, czy plansza jest rozwiązana, stosuję arytmetykę kolorów - kolor jest typem wyliczeniowym - na zasadzie:
```C++
for (ray : cell->getRays()) {
    colorSum += ray.color;
}
```
    
    
### Ad. 3. Możliwości dalszego rozwoju.
Przede wszystkim należałoby uniknąć całkowitego przerysowywania planszy. 
W kodzie źródłowym wykomentowane zostały fragmenty odpowiedzialne za dorysowanie promieni po postawieniu lustra
oraz zmazywanie niepotrzebnych promieni, jednak nie udało mi się w pełni doprowadzić tego do działania.

Do sporządzenia dokumentacji zastosowano język Markdown.
