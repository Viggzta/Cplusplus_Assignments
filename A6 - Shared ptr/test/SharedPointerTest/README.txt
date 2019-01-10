VG.h styr om det är VG eller G som det siktas på (GBETYG eller VGBETYG)(gäller både i läsningen och testprogrammet).

bservera att testprogrammet är ofullständigt, bl.a. så ska VG klara att hantera "kompatibla" pekare till ShardePtr vilket inte kollas.

Main.cpp antar att koden finns i "SharedPtr.h" (och "WeakPtr.h")
