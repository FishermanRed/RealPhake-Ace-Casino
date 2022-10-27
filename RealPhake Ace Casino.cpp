//Red here. Making my own poker/casino program so I can feed my addiction without having to open any games or gamble real money online or whatever.

#include <iostream>
#include <windows.h>

#include "menutext.h"

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK UserInfoProc(HWND, UINT, WPARAM, LPARAM);
HMENU hMenu, hTutorialMenu; //Menu bar categories
HWND hMainWnd, hUserInfo; //Unique window handlers

int alreadyOpen = 0; //The thing that prevents you opening more than one menu

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){ //Main

  //Register for main window
  WNDCLASSW wc = {0};

  wc.hbrBackground		= (HBRUSH)COLOR_WINDOW;
  wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
  wc.hInstance			= hInst;
  wc.lpszClassName	 	= L"mainWindowClass";
  wc.lpfnWndProc		= MainWndProc;

  if(!RegisterClassW(&wc))
	return -1;

  hMainWnd = CreateWindowW(L"mainWindowClass", L"RealPhake Ace Casino", WS_VISIBLE | WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX, 640, 10, 640, 480, NULL, NULL, NULL, NULL); //Make main window

  //Register for User Info window
  WNDCLASSW mui = {0};

  mui.hbrBackground		= (HBRUSH)COLOR_WINDOW;
  mui.hCursor			= LoadCursor(NULL, IDC_ARROW);
  mui.hInstance			= hInst;
  mui.lpszClassName	 	= L"userInfoClass";
  mui.lpfnWndProc		= UserInfoProc;

  if(!RegisterClassW(&mui))
	return -1;

  MSG msg = {0};

  while(GetMessage(&msg, NULL, NULL, NULL)){
	TranslateMessage(&msg);
	DispatchMessage(&msg);
  } return 0;
} //End of Main

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){ //Main window interactables
  switch(msg){
	case WM_CREATE:
	  hMenu = CreateMenu();
	  hTutorialMenu = CreateMenu();
  
	  //Primary menu bar
	  AppendMenu(hMenu, MF_STRING, 1, L"User Info");
	  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hTutorialMenu, L"How to Play");
	  AppendMenu(hMenu, MF_STRING, 2, L"Card Skins");
	  AppendMenu(hMenu, MF_STRING, 3, L"About");
      AppendMenu(hMenu, MF_STRING, 500, L"❡"); //To do: dynamic phake counter

	  //Tutorial menus
	  AppendMenu(hTutorialMenu, MF_STRING, 4, L"How to Play: RealPhake Ace Casino");
	  AppendMenu(hTutorialMenu, MF_SEPARATOR, NULL, NULL);
	  AppendMenu(hTutorialMenu, MF_STRING, 5, L"How to Play: Poker");
	  AppendMenu(hTutorialMenu, MF_STRING, 6, L"How to Play: Blackjack");
	  AppendMenu(hTutorialMenu, MF_STRING, 7, L"How to Play: Tycoon");
	  AppendMenu(hTutorialMenu, MF_STRING, 8, L"How to Play: War");
	  AppendMenu(hTutorialMenu, MF_SEPARATOR, NULL, NULL);
	  AppendMenu(hTutorialMenu, MF_STRING, 9, L"How to Play: Roulette");
	  AppendMenu(hTutorialMenu, MF_STRING, 10, L"How to Play: Craps");
	  AppendMenu(hTutorialMenu, MF_STRING, 11, L"How to Play: Slots");
	  SetMenu(hWnd, hMenu);

	  //Buttons
	  CreateWindow(L"BUTTON", L"Play Poker!", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 25, 25, 125, 25, hWnd, (HMENU)NULL, NULL, NULL);
	  CreateWindow(L"BUTTON", L"Play Blackjack!", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 152, 25, 125, 25, hWnd, (HMENU)NULL, NULL, NULL);
	  CreateWindow(L"BUTTON", L"Play Tycoon!", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 279, 25, 125, 25, hWnd, (HMENU)NULL, NULL, NULL);
	  CreateWindow(L"BUTTON", L"Play War!", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 406, 25, 125, 25, hWnd, (HMENU)NULL, NULL, NULL);
	  CreateWindow(L"BUTTON", L"Play Roulette!", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 75, 75, 125, 25, hWnd, (HMENU)NULL, NULL, NULL);
	  CreateWindow(L"BUTTON", L"Play Craps!", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 202, 75, 125, 25, hWnd, (HMENU)NULL, NULL, NULL);
	  CreateWindow(L"BUTTON", L"Play Slots!", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 329, 75, 125, 25, hWnd, (HMENU)NULL, NULL, NULL);
	  break;
	case WM_DESTROY:
	  PostQuitMessage(0);
	  break;
	case WM_COMMAND:
	  switch(wp){
		case 500:
		  MessageBeep(MB_OK);
		  break;

		case 1: //Make User Info page
		  if (alreadyOpen == 0){
			hUserInfo = CreateWindowW(L"userInfoClass", L"User Info", WS_VISIBLE | WS_BORDER | !WS_SIZEBOX, 710, 75, 500, 600, hMainWnd, NULL, NULL, NULL);
			ShowWindow(hMainWnd, 0);
			alreadyOpen ++;
		  }
		  break;
		case 2: //Card Skins page
		  //To do: Card skins page
		  break;
		case 3: //3-11 Tutorial textboxes
		  MessageBox(hWnd, ABOUT_MENUTEXT, L"About", MB_OK);
		  break;
		case 4:
		  MessageBox(hWnd, RPAC_MENUTEXT, L"How to play RealPhake Ace Casino", MB_OK);
		  break;
		case 5:
		  MessageBox(hWnd, POKER_MENUTEXT, L"Poker Tutorial", MB_OK);
		  break;
		case 6:
		  MessageBox(hWnd, PLACEHOLDER, L"Blackjack Tutorial", MB_OK);
		  break;
		case 7:
		  MessageBox(hWnd, PLACEHOLDER, L"Tycoon Tutorial", MB_OK);
		  break;
		case 8:
		  MessageBox(hWnd, PLACEHOLDER, L"War Tutorial", MB_OK);
		  break;
		case 9:
		  MessageBox(hWnd, PLACEHOLDER, L"Roulette Tutorial", MB_OK);
		  break;
		case 10:
		  MessageBox(hWnd, PLACEHOLDER, L"Craps Tutorial", MB_OK);
		  break;
		case 11:
		  MessageBox(hWnd, PLACEHOLDER, L"Slots Tutorial", MB_OK);
		  break;
	  }
	  break;
	default:
	  return DefWindowProcW(hWnd, msg, wp, lp);
  }
}

LRESULT CALLBACK UserInfoProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){ //User Info window interactables
  switch(msg){
	case WM_CREATE:
	  //Buttons
	  CreateWindow(L"BUTTON", L"Done", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 25, 25, 50, 25, hWnd, (HMENU)1, NULL, NULL);
	  break;
	case WM_DESTROY:
	  break;
	case WM_COMMAND:
	  switch(wp){
		case 1:
		  alreadyOpen --;
		  ShowWindow(hMainWnd, 1);
		  DestroyWindow(hWnd);
		  break;
	  }
	  break;
	default:
	  return DefWindowProcW(hWnd, msg, wp, lp);
  }
}