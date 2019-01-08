
#include "VectorTestHelp.h"

#include <iostream>
using std::cout;

void TestVector();
void TestIter();

int main() {
#ifdef DBG_NEW
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	std::locale::global(std::locale("swedish"));

	std::cout <<
		"Control G and VG by changing in VectorTestHelp.h\n"
		"Change the includes of Vector.hpp and VectIter.hhp to your files\n\n"
		;
	TestVector();
	//TestIter();
	//TestIterInAlg(); // Utkommenterad by default

	new int;
	cout << "det finns en minnesl�cka i main, avsiktligt!\n s� ni kan se att er minnesl�ckstest fungerar\n";
	std::cin.get();
}
