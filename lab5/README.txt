Zadania - Zestaw 5
Potoki nazwane i nienazwane
Zadanie 1
Nale�y napisa� interpreter polece� obs�uguj�cy operator pipe - "|". Interpreter czyta kolejne linie z wej�cia standardowego. Ka�da linia ma format

prog1 arg1 ... argn1 | prog2 arg1 ... argn2 | ... | progN arg1 ... argnN

Dla takiej linii interpreter powinien uruchomi� wszystkie N polece� w osobnych procesach, zapewniaj�c przy u�yciu potok�w nienazwanych oraz funkcji dup2, by wyj�cie standardowe procesu k by�o przekierowane do wej�cia standardowego procesu (k+1). Mo�na za�o�y� ograniczenie g�rne na ilo�� obs�ugiwanych argument�w (co najmniej 3) oraz ilo�� po��czonych komend w pojedynczym poleceniu (co najmniej 20). Interpreter powinien umo�liwia� uruchamianie program�w znajduj�cych si� w katalogu na li�cie w zmiennej PATH bez podawania pe�nej �cie�ki. Po uruchomieniu ci�gu program�w sk�adaj�cych si� na pojeczyne polecenie (linijk�) interpreter powinien oczekiwa� na zako�czenie wszystkich tych program�w.

Uwaga: nale�y u�y� pipe/fork/exec, nie popen


Zadanie 2
W ramach tego zadania stworzony zostanie wizualizator zbioru Mandelbrota. Zbi�r ten sk�ada si� z liczb zespolonych c takich, �e ci�g {zn} zdefiniowany poprzez

           z0 = 0, zn+1 = fc(zn),      gdzie fc(z) = z2

ma modu� ograniczony przez 2, tj. |zn| <= 2 dla ka�dego n. W praktyce wizualizacja polega na tym, �e dla zadanego punktu c sprawdzamy, czy po pewnej ustalonej ilo�ci iteracji K ten warunek jest spe�niony i kolorujemy punkt c na podstawie tego, po ilu iteracjach warunek przestaje by� prawd� - nazwijmy t� liczb� iters(c). Je�li np. K = 100 i dla danego c dopiero w 30 iteracji dostajemy zn takie, �e |zn| > 2, to iters(c) = 30. Je�li po K iteracjach warunek pozostaje spe�niony, to przyjmujemy iters(c) = K.

Wizualizacj� b�dziemy wykonywa� dla punkt�w w prostok�tnym obszarze D = { c: -2 < Re(c) < 1, -1 < Im(c) < 1 }

Nale�y napisa� dwa programy - master oraz slave - kt�re b�d� komunikowa� si� poprzez potok nazwany (kolejk� FIFO), do kt�rej �cie�k� b�d� dostawa� jako argument wywo�ania. Do potoku pisa� b�dzie wiele proces�w wykonuj�cych program slave, a czyta� b�dzie z niej jeden proces master.

Slave
Slave przyjmuje trzy argumenty - �cie�k� do potoku nazwanego i liczby ca�kowite N oraz K. Wykonuje nast�puj�ce akcje:

otwiera potok nazwany
generuje N losowych punkt�w w obszarze D, dla ka�dego punktu c oblicza warto�� iters(c) oraz zapisuje do potoku jedn� linijk� zawieraj�c� cz�� rzeczywist� oraz urojon� punktu c oraz obliczon� warto�� iters(c)
zamyka potok nazwany
Master
Master przyjmuje dwa argumenty - �cie�k� do potoku nazwanego i liczb� ca�kowit� R. Tworzy on potok o podanej nazwie. Master przechowuje zainicjalizowan� zerami tablic� dwuwymiarow� T o rozmiarze R x R reprezentuj�c� obraz obszaru D - ka�dy element tablicy to jeden "piksel" i odpowiada w naturalny spos�b pewnemu kawa�kowi obszaru D.

Master czyta z potoku nazwanego kolejne linijki a� do momentu gdy zostanie on zamkni�ty przez wszystkie procesy do niego pisz�ce. Ka�da linijka to informacja o punkcie c = x + iy oraz warto�ci iters(c). Dla ka�dej oczytanej linijki master zapisuje w tablicy T warto�� iters(c) w miejscu odpowiadaj�cym pikselowi reprezentuj�cemu kawa�ek D w kt�rym le�y punkt c.

Po zako�czeniu czytania master zapisuje zawarto�� tablicy T do pliku o nazwie data tak, �e w ka�dej linijce znajduj� si� oddzielone bia�ymi znakami warto�ci indeks�w i, j oraz warto�� T[i][j], w kolejno�ci takiej jak w poni�szym przyk�adzie:

0 0 10
0 1 35
0 2 11
1 0 5
1 1 77

itd. Nast�pnie master uruchamia program Gnuplot przy u�yciu funkcji popen, i przekazuje na jego wej�cie standardowe nast�puj�ce polecenia:

set view map
set xrange [0:X]
set yrange [0:X]
plot 'data' with image

gdzie za X wstawiona ma by� warto�� argumentu R. W efekcie powinna powsta� wizualizacja zbioru Mandelbrota podobna do poni�szej:



(R = 600, K = 100, 10 000 000 losowych punkt�w)

Uwaga: aby okno z wizualizacj� nie znika�o od razu, po przes�aniu polece� do Gnuplota nale�y

wyczy�ci� bufor potoku przez kt�ry przekazujemy polecenia do Gnuplota
np. oczekiwa� na znak z klawiatury
