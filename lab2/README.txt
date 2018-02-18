Zadania - zestaw 2
Zapoznaj si� ze sk�adni� i operacjami wykonywanymi przez poni�sze funkcje:

funkcje operuj�ce na plikach i katalogach: open, close, read, write, fcntl, stat, fstat, lstat, mkdir, rmdir, opendir, closedir, readdir, rewinddir, nftw, fopen, fclose, getc, putc,
funkcje i zmienne do obs�ugi b��d�w: perror, errno.
Zadanie 1. Por�wnanie wydajno�ci systemowych i bibliotecznych funkcji we/wy
Celem zadania jest napisanie programu por�wnuj�cego wydajno�� systemowych i bibliotecznych funkcji wej�cia/wyj�cia. Program operowa� b�dzie na przechowywanej w pliku tablicy rekord�w. Pojedynczy rekord b�dzie tablic� bajt�w o sta�ej wielko�ci. Nazwa pliku, wielko�� oraz ilo�� rekord�w stanowi� b�d� argumenty wywo�ania programu.

Program udost�pnia� powinien 3 operacje:

generate - tworzenie plik z rekordami wype�nionego losow� zawarto�ci� wygenerowan� poprzez odczyt pliku /dev/random
shuffle - losowo permutuje rekordy w pliku (mo�na wykorzysta� np. algorytm Fishera-Yates'a)
sort - sortuje rekordy w pliku u�ywaj�c sortowania b�belkowego. Kluczem do sortowania niech b�dzie warto�� pierwszego bajtu rekordu (interpretowanego jako liczba bez znaku - unsigned char)
Sortowanie i permutacja powinny by� zaimplementowane w dw�ch wariantach:

sys - przy u�yciu funkcji systemowych: read i write
lib - przy u�yciu funkcji biblioteki C: fread i fwrite
(do generowania danych wystarczy jedna wersja).

Rodzaj operacji oraz spos�b dost�pu do plik�w ma by� wybierany na podstawie argumentu wywo�ania - np. ./program sys shuffle datafile 100 512 powinno losowo permutowa� dane w pliku datafile przy u�yciu funkcji systemowych, zak�adaj�c �e zawiera on 100 rekord�w wielko�ci 512 bajt�w.

Program powinien by� zaimplementowany tak, by podczas permutowania i sortowania w pami�ci przechowywane by�y jednocze�nie najwy�ej dwa rekordy (obie operacje sprowadzaj� si� do zamieniania miejscami i/lub por�wnywania dw�ch rekord�w).

Dla obu wariant�w implementacji przeprowad� pomiary czasu u�ytkownika i czasu systemowego operacji sortowania i permutowania. Testy wykonaj dla nast�puj�cych rozmiar�w rekordu: 4, 512, 4096 i 8192 bajty. Dla ka�dego rozmiaru rekordu wykonaj dwa testy r�ni�ce si� liczb� rekord�w w sortowanym pliku. Liczby rekord�w dobierz tak, by czas sortowania mie�ci� si� w przedziale od kilku do kilkudziesi�ciu sekund. Por�wnuj�c dwa warianty implementacji nale�y korzysta� z identycznego pliku do sortowania (po wygenerowaniu, a przed sortowaniem, utw�rz jego kopi�). Zmierzone czasy sortowania zestaw w pliku wyniki.txt. Do pliku dodaj komentarz podsumowuj�cy wnioski z test�w.

Zadanie 2. Operacje na strukturze katalog�w
Napisz program przyjmuj�cy dwa argumenty wywo�ania: �cie�k� do katalogu w systemie plik�w, oraz liczb� ca�kowit� oznaczaj�c� rozmiar pliku w bajtach. Po uruchomieniu program przeszukuje drzewo katalog�w zakorzenione w �cie�ce przekazanej w pierwszym argumencie i szuka w nim plik�w zwyczajnych o rozmiarze nie wi�kszym ni� wielko�� podana jako drugi argument. Dla ka�dego znalezionego pliku wypisywane s� nast�puj�ce informacje:

�cie�ka bezwzgl�dna pliku
rozmiar w bajtach
prawa dost�pu do pliku (w formacie u�ywanym przez ls -l, np. r--r--rw- oznacza prawa odczytu dla wszystkich i zapisu dla w�a�ciciela)
dat� ostatniej modyfikacji
�cie�ka podana jako argument wywo�ania mo�e by� wzgl�dna lub bezwzgl�dna. Program powinien wyszukiwa� tylko pliki zwyczajne (bez dowi�za�, urz�dze� blokowych, itp). Program nie powinien pod��a� za dowi�zaniami symbolicznymi do katalog�w.

Program nale�y zaimplementowa� w dw�ch wariantach:

Korzystaj�c z funkcji opendir, readdir oraz funkcji z rodziny stat
Korzystaj�c z funkcji nftw
Zadanie 3. Ryglowanie plik�w
Napisz program umo�liwiaj�cy w trybie interaktywnym (tekstowym) wykonanie nast�puj�cych operacji dla pliku b�d�cego jego argumentem:

ustawienie rygla do odczytu na wybrany znak pliku,
ustawienie rygla do zapisu na wybrany znak pliku,
wy�wietlenie listy zaryglowanych znak�w pliku (z informacj� o numerze PID procesu b�d�cego w�a�cicielem rygla oraz jego typie - odczyt/zapis),
zwolnienie wybranego rygla,
odczyt (funkcj� read) wybranego znaku pliku,
zmiana (funkcj� write) wybranego znaku pliku.
Operacje 1 oraz 2 powinny by� dost�pne w dw�ch wariantach, r�ni�cych si� zachowaniem w przypadku, gdy ustawienie rygla jest niemo�liwe ze wzgl�du na rygle za�o�one przez inne procesy:

wersja nieblokuj�ca - pr�ba ustawienia rygla ko�czy si� wypisaniem informacji o b��dzie
wersja blokuj�ca - program czeka, a� ustawienie rygla b�dzie mo�liwe
Wyb�r znaku we wszystkich przypadkach polega na podaniu numeru bajtu w pliku. Do ryglowania nale�y wykorzysta� funkcj� fcntl i struktur� flock. Wykonaj eksperymenty uruchamiaj�c program jednocze�nie w dw�ch terminalach dla tego samego pliku. Pr�buj ryglowa� (do odczytu lub do zapisu) te same znaki pliku i modyfikowa� (lub odczytywa�) wybrane znaki pliku wykorzystuj�c zar�wno blokuj�ce, jak i nieblokuj�ce wersje operacji. Zwr�� uwag�, �e domy�lnie ryglowanie dzia�a w trybie rygli zalecanych (advisory), a nie rygli wymuszanych (mandatory).