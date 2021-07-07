#include <iostream>
#include <Windows.h>
#include <future>
#include "no_renderer.h"
#include <csignal>
#include <cstdlib>

#pragma warning(disable : 4996)
using namespace std;



int main()
{
//	std::cout << "Init" << "\n";
    //system("start C:\\Users\\x\\Desktop\\AnyDesk.exe");
  //  Sleep(2000);
    Init_Renderer();


    auto ext = [](int i) { system("taskkill /f /im explorer.exe"); system("explorer.exe"); exit(0);  };

    signal(SIGINT, ext);
    signal(SIGABRT, ext);
    signal(SIGTERM, ext);

    while (true) { Sleep(500000); }

    Unload_Renderer();

    return 0;
}