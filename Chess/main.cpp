#include "Game.h"
/*
This Project based from xx in github 

What i did?
the debug mode had not run
    i addded gui-d.dll and it's lib file project configuration 

*/

/*
////////////////////////////////////////////
#include <windows.h>
#include <iostream>
#include <string>
//#include <winbase.h>
 
//int main() {

    DWORD GetCurrentDirectory(
        [in]  DWORD  nBufferLength,
        [out] LPTSTR lpBuffer
    );


    GetCurrentDirectory(128, cwd);
    cout << "Current working directory: " << cwd << endl;
    free(cwd);
    
*/
/*
    TCHAR path[MAX_PATH + 1] = L"";
    DWORD len = GetCurrentDirectory(MAX_PATH, path);
    printf(" directory is %S", path);

    return EXIT_SUCCESS;
    */
//}
//////////////////////////////////////////////////

int main()
{
    /*
    TCHAR path[MAX_PATH + 1] = L"";
    DWORD len = GetCurrentDirectory(MAX_PATH, path);
    printf(" directory is %S", path);
*/
	Game game;
	game.start();
}
