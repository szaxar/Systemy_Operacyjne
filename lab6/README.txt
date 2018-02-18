Zadanie 1. System V
Napisz prosty program typu klient-serwer, w kt�rym komunikacja zrealizowana jest za pomoc� kolejek komunikat�w - jedna, na zlecenia klient�w dla serwera, druga, prywatna, na odpowiedzi.

Serwer po uruchomieniu tworzy now� kolejk� komunikat�w systemu V. Za pomoc� tej kolejki klienci b�d� wysy�a� komunikaty do serwera. Wysy�ane zlecenia maj� zawiera� rodzaj zlecenia jako rodzaj komunikatu oraz informacj� od kt�rego klienta zosta�y wys�ane (PID procesu klienta), w odpowiedzi rodzajem komunikatu ma by� informacja identyfikuj�ca czekaj�cego na ni� klienta.

Klient bezpo�rednio po uruchomieniu tworzy kolejk� z unikalnym kluczem IPC  i wysy�a jej klucz komunikatem do serwera. Po otrzymaniu takiego komunikatu, serwer otwiera kolejk� klienta, przydziela klientowi identyfikator (np. numer w kolejno�ci zg�osze�) i odsy�a ten identyfikator do klienta (komunikacja w kierunku serwer->klient odbywa si� za pomoc� kolejki klienta). Po otrzymaniu identyfikatora, klient rozpoczyna wysy�anie zlece� do serwera (w p�tli).


Rodzaje zlece�
Us�uga echa:
Klient wysy�a ci�g znak�w. Serwer odsy�a ten sam ci�g z powrotem. Klient po odebraniu wysy�a go na standardowe wyj�cie.
Us�uga wersalik�w:
Klient wysy�a ci�g znak�w. Serwer zamienia ma�e litery na du�e i odsy�a zmieniony ci�g z powrotem. Klient po odebraniu wysy�a go na standardowe wyj�cie.
Us�uga czasu:
Po odebraniu takiego zlecenia serwer wysy�a do klienta dat� i godzin� w postaci �a�cucha znak�w. Klient po odebraniu informacji wysy�a j� na standardowe wyj�cie.
Nakaz zako�czenia:
Po odebraniu takiego zlecenia serwer zako�czy dzia�anie, jak tylko opr�ni si� kolejka zlece� (zostan� wykonane wszystkie pozosta�e zlecenia).
Klient nie czeka na odpowied�.
Poszczeg�lne rodzaje komunikat�w nale�y identyfikowa� za pomoc� typ�w komunikat�w systemu V. Klucze dla kolejek maj� by� generowane na podstawie �cie�ki $HOME. Ma�e liczby do wygenerowania kluczy oraz rodzaje komunikat�w maj� by� zdefiniowane we wsp�lnym pliku nag��wkowym. Dla uproszczenia mo�na za�o�y�, �e d�ugo�� komunikatu (lub maksymalna d�ugo�� �a�cucha znak�w przy us�udze echa) jest ograniczona pewn� sta�� (jej definicja powinna znale�� si� w pliku nag��wkowym).
Klient i serwer nale�y napisa� w postaci osobnych program�w (nie korzystamy z funkcji fork). Serwer musi by� w stanie pracowa� z wieloma klientami naraz. Przed zako�czeniem pracy ka�dy proces powinien usun�� kolejk� kt�r� utworzy� (patrz IPC_RMID oraz funkcja atexit). Dla uproszczenia mo�na przyj��, �e serwer przechowuje informacje o klientach w statycznej tablicy (rozmiar tablicy ogranicza liczb� klient�w, kt�rzy mog� si� zg�osi� do serwera).

Zadanie 2. POSIX
Zrealizuj zadanie alogiczne do Zadania 1 wykorzystuj�c kolejki komunikat�w POSIX.

Kolejka klienta powinna mie� losow� nazw� zgodn� z wymaganiami stawianymi przez POSIX. Na typ komunikatu mo�na zarezerwowa� pierwszy bajt jego tre�ci. Przed zako�czeniem pracy klient wysy�a do serwera komunikat informuj�cy, �e serwer powinien zamkn�� po swojej stronie kolejk� klienta. Nast�pnie klient zamyka i usuwa swoj� kolejk�. Serwer przed zako�czeniem pracy zamyka wszystkie otwarte kolejki i usuwa kolejk�, kt�r� utworzy�.