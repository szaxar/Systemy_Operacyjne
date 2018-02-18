Zadania - Zestaw 10
Celem zadania jest napisanie prostego systemu pozwalaj�cego na wykonywanie oblicze� na "klastrze obliczeniowym".

Mamy centralny serwer (nas�uchuj�cy jednocze�nie na gnie�dzie sieciowym i gnie�dzie lokalnym), z poziomu kt�rego zlecane s� obliczenia. Klienci po uruchomieniu przesy�aj� do serwera swoj� nazw�, a ten sprawdza czy klient o takiej nazwie ju� istnieje - je�li tak, to odsy�a klientowi komunikat �e nazwa jest ju� w u�yciu; je�li nie, to zapami�tuje klienta. Zlecenia oblicze� s� wpisane bezpo�rednio w konsoli serwera i dotycz� czterech podstawowych dzia�a� matematycznych - dodawania, odejmowania, mno�enia i dzielenia. Serwer tworzy struktur� opisuj�c� zlecenie (dzia�anie, argument 1, argument 2), a nast�pnie przesy�a j� do dowolnie wybranego klienta. Ten oblicza wynik zlecenia i odsy�a go do serwera, kt�ry wy�wietla wynik na standardowym wyj�ciu. Klient przy wy��czeniu Ctrl+C powinien wyrejestrowa� si� z serwera.

W procesie serwera obs�uga wprowadzania zlece� z terminala i obs�uga sieci powinny by� zrealizowane w dw�ch osobnych w�tkach. W�tek obs�uguj�cy sie� powinien obs�ugiwa� gniazdo sieciowe i gniazdo lokalne jednocze�nie, wykorzystuj�c w tym celu funkcje do monitorowania wielu deskryptor�w (epoll/poll/select). Dodatkowo, osobny w�tek powinien cyklicznie "pingowa�" zarejestrowanych klient�w, aby zweryfikowa� �e wci�� odpowiadaj� na ��dania i je�li nie - usuwa� ich z listy klient�w.

Mo�esz przyj��, �e ilo�� klient�w zarejestrowanych na serwerze jest ograniczona do maksymalnie kilkunastu. Zapewnij mo�liwo�� ustalenia dla kt�rego zlecenia wy�wietlony zosta� wynik (np. umie�� w serwerze globalny licznik, wy�wietlany i inkrementowany po dodaniu ka�dego nowego zlecenia i umieszczany jako dodatkowy identyfikator w komunikatach wysy�anych do klient�w i odpowiedziach od nich przychodz�cych) i kt�ry klient go obliczy�.

Serwer przyjmuje jako swoje argumenty:

numer portu TCP/UDP (zale�nie od zadania),
�cie�k� gniazda UNIX.
Klient przyjmuje jako swoje argumenty:

swoj� nazw� (string o z g�ry ograniczonej d�ugo�ci),
spos�b po��czenia z serwerem (sie� lub komunikacja lokalna przez gniazda UNIX),
adres serwera (adres IPv4 i numer portu lub �cie�k� do gniazda UNIX serwera).
Zadanie 1
Komunikacja klient�w i serwera odbywa si� z u�yciem protoko�u strumieniowego.

Wskaz�wka: na ��czu strumieniowym mo�na zasymulowa� komunikacj� datagramow� korzystaj�c z TLV (Type-Length-Value) - najpierw wysy�ana jest sta�ej wielko�ci (np. 1 bajt) warto�� m�wi�c� o typie komunikatu/danych, p�niej sta�ej wielko�ci (np. 2 bajty) warto�� m�wi�c� o d�ugo�ci przesy�anych danych, a� wreszcie przesy�ane s� faktyczne dane w ilo�ci okre�lonej chwil� wcze�niej; mo�na te� np. przechowywa� typ danych jako pierwszy bajt przesy�anej warto�ci - tak jak robi� to struktury opisuj�ce adresy gniazd. U�ycie tych technik nie jest wymagane w zadaniu.

Zadanie 2
Komunikacja klient�w i serwera odbywa si� z u�yciem protoko�u datagramowego.