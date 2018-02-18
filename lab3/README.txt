Zadanie 1. Prosty interpreter zada� wsadowych
W ramach �wiczenia nale�y napisa� prosty interpreter zada� wsadowych. Interpreter przyjmuje w argumencie nazw� pliku zawieraj�cego zadanie wsadowe i wykonuje wszystkie polecenia z tego pliku. Plik z zadaniem wsadowym ma �ci�le okre�lon� posta�:

Linie zaczynaj�ce si� znakiem # oznaczaj� prac� ze zmiennymi �rodowiskowymi. Ka�da taka linia ma jedn� z dw�ch postaci:

#NazwaZmiennej WartoscZmiennej
Oznacza definicj� zmiennej �rodowiskowej. Od momentu jej wyst�pienia, w �rodowisku polece� wykonywanych przez interpreter powinna istnie� zmienna NazwaZmiennej o warto�ci WartoscZmiennej. Je�li taka zmienna istnieje ju� w �rodowisku, jej warto�� powinna zosta� zmieniona na WartoscZmiennej.
Na przyk�ad, linia postaci:
#TestFile ./ala.txt
powinna spowodowa� dodanie do �rodowiska zmiennej TestFile o warto�ci ./ala.txt

Uwaga: zmienne �rodowiskowe, z kt�rymi zosta� uruchomiony interpreter powinny by� dost�pne r�wnie� dla wykonywanych polece�.

#NazwaZmiennej
Oznacza usuni�cie zmiennej NazwaZmiennej ze �rodowiska. Polecenie powinno zako�czy� si� powodzeniem r�wnie� w�wczas, gdy w �rodowisku nie ma zmiennej NazwaZmiennej (w�wczas �rodowisko si� nie zmienia).
Na przyk�ad, linia postaci:
#TestFile
powinna spowodowa� usuni�cie ze �rodowiska zmiennej TestFile (je�li taka zmienna jest w �rodowisku).

Linie zaczynaj�c si� znakiem innym, ni� # oznaczaj� polecenia do wykonania. Ka�de polecenie ma posta�:

NazwaProgramu arg1 arg2 ...

i oznacza, �e nale�y wykona� program o nazwie NazwaProgramu z argumentami: arg1, arg2, ...
Na przyk�ad, linia postaci:
ls -l
powinna spowodowa� wykonanie programu ls z argumentem -l. Lista argument�w mo�e by� pusta - w�wczas program wykonywany jest bez argument�w. W zadaniu mo�na r�wnie� przyj�� g�rne ograniczenie na liczb� argument�w.
Interpreter musi wykonywa� polecenia w osobnych procesach. W tym celu, po odczytaniu polecenia do wykonania interpreter tworzy nowy proces potomny. Proces potomny natychmiast wykonuje odpowiedni� funkcj� z rodziny exec, kt�ra spowoduje uruchomienie wskazanego programu z odpowiednimi argumentami. Uwaga: proces potomny powinien uwzgl�dnia� zawarto�� zmiennej �rodowiskowej PATH - polecenie do wykonania nie musi obejmowa� �cie�ki do uruchamianego programu, je�li program ten znajduje si� w katalogu wymienionym w zmiennej PATH.
Po stworzeniu procesu potomnego, proces interpretera czeka na jego zako�czenie i odczytuje status zako�czenia. Je�li proces zako�czy� si� ze statusem 0 interpreter przyst�puje do wykonania kolejnej linii pliku wsadowego. W przeciwnym wypadku interpreter wy�wietla komunikat o b��dzie i ko�czy prac�. Komunikat ten powinien wskazywa�, kt�re polecenie z pliku wsadowego zako�czy�o si� b��dem. Zak�adamy, �e polecenia z pliku wsadowego nie oczekuj� na �adne wej�cie z klawiatury. Mog� natomiast wypisywa� wyj�cie na ekran.

Na potrzeby demonstracji zadania przygotuj r�wnie� program, kt�ry przyjmuje w argumencie nazw� zmiennej �rodowiskowej a nast�pnie odczytuje ze �rodowiska i wypisuje na ekranie jej aktualn� warto��. Program powinien r�wnie� wypisywa� stosowny komunikat, je�li w �rodowisku nie ma zmiennej o wskazanej nazwie.