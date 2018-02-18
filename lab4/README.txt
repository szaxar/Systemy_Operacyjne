Zadania - Zestaw 4
Zestaw 4. Sygna�y
Rodzaje sygna��w: SIGINT, SIGQUIT, SIGKILL, SIGTSTP, SIGSTOP, SIGTERM, SIGSEGV, SIGHUP, SIGALARM, SIGCHLD, SIGUSR1, SIGUSR2
Sygna�y czasu rzeczywistego: SIGRTMIN, SIGRTMIN+n, SIGRTMAX
Przydatne polecenia Unix: kill, ps
Przydatne funkcje systemowe: kill, raise, sigqueue, signal, sigaction, sigemptyset, sigfillset, sigaddset, sigdelset, sigismember, sigprocmask, sigpending, pause, sigsuspend

Zadanie 1
Napisz program wypisuj�cy kolejn� liter� alfabetu od A do Z. Po odebraniu sygna�u SIGTSTP program zaczyna wypisywa� litery wstecz. Po ponownym wys�aniu SIGTSTP program powraca do pierwotnego wypisywania. Program powinien umo�liwia� wielokrotne przechodzenie przez powy�szy cykl (sygna�em SIGTSTP).

Program powinien r�wnie� obs�ugiwa� sygna� SIGINT. Po jego odebraniu program wypisuje komunikat "Odebrano sygna� SIGINT" i ko�czy dzia�anie. W kodzie programu, do przechwycenia sygna��w u�yj zar�wno funkcji signal, jak i sigaction (np. SIGINT odbierz za pomoc� signal, a SIGTSTP za pomoc� sigaction).

Zadanie 2
Napisz program, kt�ry tworzy N potomk�w i oczekuje na ich pro�by na przej�cie (sygna�y SIGUSR1). Po uzyskaniu K pr�b, proces powinien pozwoli� kontynuowa� dzia�anie wszystkim procesom, kt�re poprosi�y o przej�cie (wys�a� im sygna� pozwolenia na rozpocz�cie pracy) i niezw�ocznie akceptowa� ka�d� kolejn� pro�b�. Program powinien wypisa� list� wszystkich otrzymanych sygna��w wraz numerem PID potomka oraz kodem zako�czenia procesu (w przypadku otrzymania sygna�u zako�czenia pracy potomka).

Program ko�czy dzia�anie po zako�czeniu pracy ostatniego potomka albo po otrzymaniu sygna�u SIGINT (w tym wypadku nale�y zako�czy� wszystkie dzia�aj�ce procesy potomne).

N i M s� argumentami programu.

Zachowanie dzieci powinno by� nast�puj�ce. Ka�de dziecko najpierw symuluje prac� (u�nie na 0-10 sekund). Nast�pnie wysy�a sygna� SIGUSR1 pro�by o przej�cie, a po uzyskaniu pozwolenia losuje jeden z 32 sygna��w czasu rzeczywistego  (SIGRTMIN,SIGRTMAX), wysy�a go do rodzica i ko�czy dzia�anie, zwracaj�c wypisan� r�nic� czasu mi�dzy wys�aniem pro�by a wys�aniem sygna�u jako kod zako�czenia procesu.

Zadanie 3
Napisz program kt�ry tworzy proces potomnych i wysy�a do niego L sygna��w SIGUSR1, a nast�pnie sygna� zako�czenia wysy�ania SIGUSR2. Potomek po otrzymaniu sygna��w SIGUSR1 od rodzica zaczyna je odsy�a� do procesu macierzystego, a po otrzymaniu SIGUSR2 ko�czy prac�.

Proces macierzysty w zale�no�ci od argumentu Type (1,2,3) programu wysy�a sygna�y na trzy r�ne sposoby:

SIGUSR1, SIGUSR2 za pomoc� funkcji kill
SIGUSR1, SIGUSR2 za pomoc� funkcji sigqueue
wybrane 2 sygna�y czasu rzeczywistego za pomoc� kill
Program powinien wypisywa� informacje o:

liczbie wys�anych sygna��w do potomka
liczbie odebranych sygna��w przez potomka
liczbie odebranych sygna��w od potomka
Program ko�czy dzia�anie po zako�czeniu pracy potomka albo po otrzymaniu sygna�u SIGINT (w tym wypadku nale�y zako�czy� proces potomny).

L i Type s� argumentami programu.

(*) Zamiast podstawowego wariantu program tworzy w p�tli N proces�w potomnych, a nast�pnie wysy�a sygna�y do losowo wybranego potomka (do ka�dego z nich w inny spos�b) Przeanalizuj wyniki z wykorzystaniem funkcji sleep pomi�dzy losowaniem kolejnego potomka, warto�� funkcji sleep jest ostatnim argumentem programu, domy�lna warto�� T=0 oznacza jego brak. Argumenty programu N, L, T=0.