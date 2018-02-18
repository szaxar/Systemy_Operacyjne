Zadania - Zestaw 7
IPC - pamie� wsp�lna, semafory


Problem synchronizacyjny �pi�cego golibrody z kolejk�
W ramach �wiczenia 7 nale�y zaimplementowa� prawid�owe rozwi�zanie problemu �pi�cego golibrody z kolejk�. Golibroda prowadzi zak�ad fryzjerski z jednym krzes�em w gabinecie (na kt�rym strzy�e klient�w) i N krzes�ami w poczekalni. Zak�ad dzia�a wed�ug nast�puj�cego schematu:

Po przyj�ciu do zak�adu klient sprawdza co robi golibroda. Je�li golibroda �pi, klient budzi go, siada na krze�le w gabinecie i jest strzy�ony. Je�li golibroda strzy�e innego klienta, nowy klient sprawdza, czy w poczekalni jest wolne krzes�o. Je�li tak, to klient siada w poczekalni. W przeciwnym razie klient opuszcza zak�ad.
Golibroda sprawdza, czy w poczekalni oczekuj� klienci. Je�li w poczekalni nie ma klient�w, golibroda zasypia. W przeciwnym razie golibroda zaprasza do strzy�enia klienta, kt�ry czeka� najd�u�ej. Gdy golibroda sko�czy strzy�enie, klient opuszcza zak�ad. Golibroda ponownie sprawdza poczekalni�.
Zak�adamy, �e golibroda oraz ka�dy klient to osobne procesy. Liczba krzese� w poczekalni jest podawana w argumencie wywo�ania golibrody. Proces golibrody pracuje do momentu otrzymania wybranego sygna�u (np. SIGINT).
Klienci s� tworzeni przez jeden proces macierzysty (funkcj� fork). Ka�dy klient posiada identyfikator � mo�e to by� np. jego numer PID. Proces tworz�cy klient�w przyjmuje dwa argumenty: liczb� klient�w do stworzenia oraz liczb� strzy�e� S. Ka�dy klient w p�tli odwiedza zak�ad fryzjerski. Gdy klient zostanie ostrzy�ony S razy, proces klienta ko�czy prac�. Proces macierzysty ko�czy prac� po zako�czeniu wszystkich proces�w klient�w (mo�na w�wczas uruchomi� w konsoli kolejn� parti� klient�w).

Program golibrody wypisuje na ekranie komunikaty o nast�puj�cych zdarzeniach:

za�ni�cie golibrody,
rozpocz�cie strzy�enia (w komunikacie tym podawany identyfikator strzy�onego klienta),
zako�czenie strzy�enia (r�wnie� z identyfikatorem strzy�onego klienta).
Ka�dy klient wypisuje na ekranie komunikaty o nast�puj�cych zdarzeniach:

obudzenie golibrody,
zaj�cie miejsca w poczekalni,
opuszczenie zak�adu z powodu braku wolnych miejsc w poczekalni,
opuszczenie zak�adu po zako�czeniu strzy�enia.
Ka�dy komunikat golibrody lub klienta powinien zawiera� znacznik czasowy z dok�adno�ci� do mikrosekund (mo�na tu wykorzysta� funkcj� clock_gettime z flag� CLOCK_MONOTONIC). Ka�dy komunikat klienta powinien ponadto zawiera� jego identyfikator.

Synchronizacja proces�w musi wyklucza� zakleszczenia i gwarantowa� sekwencj� zdarze� zgodn� ze schematem dzia�ania zak�adu. Niedopuszczalne jest zasypianie proces�w klient�w lub golibrody funkcjami z rodziny sleep. Szeregowanie klient�w do strzy�enia nale�y zaimplementowa� w postaci kolejki FIFO w pami�ci wsp�lnej. W pami�ci wsp�lnej mo�na r�wnie� przechowywa� zmienn� zliczaj�c� klient�w oczekuj�cych w poczekalni. Odpowiednie zasoby do synchronizacji i komunikacji powinny by� tworzone przez proces golibrody. Proces ten jest r�wnie� odpowiedzialny za usuni�cie tych zasob�w z systemu (przed zako�czeniem pracy).

Zadanie 1
Zaimplementuj opisany powy�ej problem synchronizacyjny wykorzystuj�c semafory i pami�� wsp�ln� z IPC Systemu V.

Zadanie 2.
Zaimplementuj opisany powy�ej problem synchronizacyjny wykorzystuj�c semafory i pami�� wsp�ln� z IPC POSIX.