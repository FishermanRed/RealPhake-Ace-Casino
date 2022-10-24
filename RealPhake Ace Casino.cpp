//Red here. Making my own poker/casino program so I can feed my addiction without having to open any games or gamble real money online or whatever.

#include <iostream>
#include <windows.h>

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
HMENU hMenu;

void addMenus(HWND hWnd){ //Menu bar options and such
  hMenu = CreateMenu();
  AppendMenu(hMenu, MF_STRING, 1, L"User Info");
  AppendMenu(hMenu, MF_STRING, 2, L"How to Play");
  AppendMenu(hMenu, MF_STRING, 3, L"Card Skins");
  AppendMenu(hMenu, MF_STRING, 4, L"About");
  AppendMenu(hMenu, MF_STRING, NULL, L"❡");  //To do: dynamic phake counter
  SetMenu(hWnd, hMenu);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){

  WNDCLASSW wc = {0};

  wc.hbrBackground		= (HBRUSH) COLOR_WINDOW;
  wc.hCursor			= LoadCursor (NULL, IDC_ARROW);
  wc.hInstance			= hInst;
  wc.lpszClassName	 	= L"windowClass";
  wc.lpfnWndProc		= WinProc;

  if(!RegisterClassW(&wc))
	return -1;

  CreateWindowW(L"windowClass", L"RealPhake Ace Casino", WS_VISIBLE | WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, 640, 10, 640, 480, NULL, NULL, NULL, NULL);	//Main Menu

  MSG msg = {0};

  while(GetMessage(&msg, NULL, NULL, NULL)){
	TranslateMessage(&msg);
	DispatchMessage(&msg);
  }	return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
  switch (msg){
	case WM_CREATE:
	  addMenus(hWnd); //To do: add Roulette, Slots(?), Craps, War(?),
	  CreateWindow(TEXT("BUTTON"), TEXT("Play Poker!"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 25, 25, 100, 25, hWnd, (HMENU)NULL, NULL, NULL);
	  CreateWindow(TEXT("BUTTON"), TEXT("Play Blackjack!"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 135, 25, 120, 25, hWnd, (HMENU)NULL, NULL, NULL);
	  break;
	case WM_DESTROY:
	  PostQuitMessage(0);
	  break;
	case WM_COMMAND:
	  switch(wp){
		case 1:

		  break;
		case 2:

		  break;
		case 3:

		  break;
		case 4:
		  MessageBox(hWnd, L"\t\t            ♠         ♡         ♣         ♢\n\t\t            RealPhake Ace Casino\n\t\t                     Version 1.0\n\t\t            ♤         ♥         ♧         ♦\n\nRealPhake Ace Casino is a personal project made by Red K.\n\nI have not copyrighted anything and I don't plan on charging anyone for this game, so if you paid money for this, I'm sorry but you got ripped off. Everything in this program falls under fair use; no copyrighted material contained in this program belongs to me in any way, it's just for fun and I am not making money off of it.\n\nSpecial Thanks to Professor Seth Reed and The Pentamollis Project.\n\nFeel free to contact me through Discord:\nRed#0681", L"About", MB_OK);
		  break;
	  } break;
	default:
	  return DefWindowProcW(hWnd, msg, wp, lp);
  }
}