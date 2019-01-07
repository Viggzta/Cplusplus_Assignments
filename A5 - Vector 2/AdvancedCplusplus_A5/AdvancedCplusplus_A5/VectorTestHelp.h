#ifdef _DEBUG
#include <stdlib.h>
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#define GBETYG  //Kommentera bort denna rad för VG test
#ifdef GBETYG
#undef VGBETYG
#else
#define VGBETYG
#endif