VG.h styr om det �r VG eller G som det siktas p� (GBETYG eller VGBETYG)(g�ller b�de i l�sningen och testprogrammet).

bservera att testprogrammet �r ofullst�ndigt, bl.a. s� ska VG klara att hantera "kompatibla" pekare till ShardePtr vilket inte kollas.

Main.cpp antar att koden finns i "SharedPtr.h" (och "WeakPtr.h")
