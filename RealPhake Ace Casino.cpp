// Red here. Making my own poker/casino program so I can feed my addiction without having to open any games or gamble real money online or whatever.

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

#include "menutext.h"

using namespace std;

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK UserInfoProc(HWND, UINT, WPARAM, LPARAM);
// Handlers
HBITMAP hMainBG, hMemberBG;
HMENU	hMenu, hTutorialMenu;
HWND	hMainWnd, hUserInfo, hFirstname, hLastname, hMx, hMainBGWnd, hMemberBGWnd;

int alreadyOpen = 0; // The thing that prevents you opening more than one menu

wchar_t userFirstname[50] = L"";
wchar_t userLastname[50] = L"";
wchar_t userMx[5] = L"Mx.";

// To do: Dialogue and pronouns(?)

// FINALLY GOT THE ID MAKER WORKING!! To do: Implement save function properly now that it works, also make the first time user setup
string gen_random(const int len){
  static const char alphanum[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  string tmp_s;
  tmp_s.reserve(21);
  for (int i = 0; i < 21; ++i){
    tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
  }  
  return tmp_s;
}

void mymomma(){
  srand((unsigned)time(0));
  wofstream fileout("UserInfo.txt", ios::out);
  char* ID = new char[gen_random(21).length() + 1];
  if(fileout.is_open()){
	for(int i = 0; i < gen_random(21).length(); i++)
	  ID[i] = gen_random(21)[i];
    for(int i = 0; ID[i] != 0; i++)
      fileout.put(ID[i]);
    fileout.close();
  }
}

void yomomma(){
  wifstream test("UserInfo.txt", ios::in);
  wstring line;
  if(test.is_open()){
	getline(test, line);
	MessageBox(hMainWnd, line.c_str(), L"Test message", MB_OK);
	test.close();
  }
}
// End of ID maker

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd){ // Main
  // Register for main window
  WNDCLASSW wc = {0};

  wc.hbrBackground		= (HBRUSH)COLOR_WINDOW;
  wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
  wc.hInstance			= hInstance;
  wc.lpszClassName		= L"mainWindowClass";
  wc.lpfnWndProc		= MainWndProc;

  if(!RegisterClassW(&wc))
	return -1;

  // Make main window
  hMainWnd = CreateWindowW(L"mainWindowClass", L"RealPhake Ace Casino", WS_VISIBLE | WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX, 640, 275, 640, 479, NULL, NULL, NULL, NULL);

  // Register for User Info window
  WNDCLASSW mui = {0};

  mui.hbrBackground		= (HBRUSH)COLOR_WINDOW;
  mui.hCursor			= LoadCursor(NULL, IDC_ARROW);
  mui.hInstance			= hInstance;
  mui.lpszClassName		= L"userInfoClass";
  mui.lpfnWndProc		= UserInfoProc;

  if(!RegisterClassW(&mui))
	return -1;

  MSG msg = {0};

  while(GetMessage(&msg, NULL, NULL, NULL)){
	TranslateMessage(&msg);
	DispatchMessage(&msg);
  } return 0;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){ // Main window interactables
  switch(msg){
	case WM_CREATE:
	  hMenu			= CreateMenu();
	  hTutorialMenu	= CreateMenu();
  
	  // Bitmap shit(map)
	  hMainBG = (HBITMAP) LoadImageW(NULL, L"Assets\\Backgrounds\\testimage2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	  hMainBGWnd = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, CW_DEFAULT, CW_DEFAULT, hWnd, NULL, NULL, NULL);
	  SendMessageW(hMainBGWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hMainBG);

	  // Main window menu bar
	  AppendMenu(hMenu, MF_STRING,	1, L"User Info");
	  AppendMenu(hMenu, MF_STRING,	2, L"Card Skins");
	  AppendMenu(hMenu, MF_POPUP,	(UINT_PTR)hTutorialMenu, L"How to Play");
	  AppendMenu(hMenu, MF_STRING,	11, L"About");
	  AppendMenu(hMenu, MF_STRING,	12, L"❡"); // To do: dynamic phake counter

	  // Tutorial options
	  AppendMenu(hTutorialMenu, MF_STRING, 3,	L"How to Play: RealPhake Ace Casino");
	  AppendMenu(hTutorialMenu, MF_SEPARATOR,	NULL, NULL);
	  AppendMenu(hTutorialMenu, MF_STRING, 4,	L"How to Play: Poker");
	  AppendMenu(hTutorialMenu, MF_STRING, 5,	L"How to Play: Blackjack");
	  AppendMenu(hTutorialMenu, MF_STRING, 6,	L"How to Play: Tycoon");
	  AppendMenu(hTutorialMenu, MF_STRING, 7,	L"How to Play: War");
	  AppendMenu(hTutorialMenu, MF_SEPARATOR,	NULL, NULL);
	  AppendMenu(hTutorialMenu, MF_STRING, 8,	L"How to Play: Roulette");
	  AppendMenu(hTutorialMenu, MF_STRING, 9,	L"How to Play: Craps");
	  AppendMenu(hTutorialMenu, MF_STRING, 10,	L"How to Play: Slots");
	  SetMenu(hWnd, hMenu);

	  // Buttons
	  CreateWindow(L"BUTTON", L"Play Poker!",		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 47,  300, 125, 25, hWnd, (HMENU)13, NULL, NULL);
	  CreateWindow(L"BUTTON", L"Play Blackjack!",	WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 182, 300, 125, 25, hWnd, (HMENU)14, NULL, NULL);
	  CreateWindow(L"BUTTON", L"Play Tycoon!",		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 317, 300, 125, 25, hWnd, (HMENU)15, NULL, NULL);
	  CreateWindow(L"BUTTON", L"Play War!",			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 452, 300, 125, 25, hWnd, (HMENU)16, NULL, NULL);
	  CreateWindow(L"BUTTON", L"Play Roulette!",	WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 115, 335, 125, 25, hWnd, (HMENU)17, NULL, NULL);
	  CreateWindow(L"BUTTON", L"Play Craps!",		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 250, 335, 124, 25, hWnd, (HMENU)18, NULL, NULL);
	  CreateWindow(L"BUTTON", L"Play Slots!",		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 384, 335, 125, 25, hWnd, (HMENU)19, NULL, NULL);
	  break;

	case WM_COMMAND:
	  switch(wp){
		// Make User Info window
		case 1:
		  if (alreadyOpen == 0){
			hUserInfo = CreateWindowW(L"userInfoClass", L"User Info", WS_VISIBLE | WS_BORDER | !WS_SIZEBOX, 615, 300, 691, 439, hMainWnd, NULL, NULL, NULL);
			//ShowWindow(hMainWnd, 0); // Uncomment for functioning hide/show
			alreadyOpen ++;
		  }
		  break;

		// Card skins page
		case 2:
		  // To do: Card skins page
		  break;

		// Tutorial pages
		case 3:
		  MessageBox(hWnd, RPAC_MENUTEXT, L"How to play RealPhake Ace Casino", MB_OK);
		  break;
		case 4:
		  MessageBox(hWnd, POKER_MENUTEXT, L"Poker Tutorial", MB_OK);
		  break;
		case 5:
		  MessageBox(hWnd, PLACEHOLDER, L"Blackjack Tutorial", MB_OK);
		  break;
		case 6:
		  MessageBox(hWnd, PLACEHOLDER, L"Tycoon Tutorial", MB_OK);
		  break;
		case 7:
		  MessageBox(hWnd, PLACEHOLDER, L"War Tutorial", MB_OK);
		  break;
		case 8:
		  MessageBox(hWnd, PLACEHOLDER, L"Roulette Tutorial", MB_OK);
		  break;
		case 9:
		  MessageBox(hWnd, PLACEHOLDER, L"Craps Tutorial", MB_OK);
		  break;
		case 10:
		  MessageBox(hWnd, PLACEHOLDER, L"Slots Tutorial", MB_OK);
		  break;

		// About page
		case 11:
		  MessageBox(hWnd, ABOUT_MENUTEXT, L"About", MB_OK);
		  break;

		// Phake
		case 12:
		  MessageBeep(MB_OK);
		  break;

		// The games
		case 13:
		  // To do: Add Poker
		  mymomma(); // ID maker is being temporarily put on the poker button for testing purposes
		  yomomma();
		  break;
		case 14:
		  // To do: Add Blackjack
		  break;
		case 15:
		  // To do: Add Tycoon
		  break;
		case 16:
		  // To do: Add War
		  break;
		case 17:
		  // To do: Add Roulette
		  break;
		case 18:
		  // To do: Add Craps
		  break;
		case 19:
		  // To do: Add Slots
		  break;
	  }
	  break;
	default:
	  return DefWindowProcW(hWnd, msg, wp, lp);

	case WM_DESTROY:
	  PostQuitMessage(0);
	  break;
  }
  return 0;
}

LRESULT CALLBACK UserInfoProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){ // User Info window interactables
  switch(msg){
	case WM_CREATE:
	  // Bitmap shit(map)
	  hMemberBG = (HBITMAP) LoadImageW(NULL, L"Assets\\Backgrounds\\MemberCard.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	  hMemberBGWnd = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, CW_DEFAULT, CW_DEFAULT, hWnd, NULL, NULL, NULL);
	  SendMessageW(hMemberBGWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hMemberBG);
	  
	  // Buttons
	  CreateWindow(L"BUTTON", L"Save", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 555, 345, 50, 25, hWnd, (HMENU)1, NULL, NULL);
	  CreateWindow(L"BUTTON", L"Done", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 615, 345, 50, 25, hWnd, (HMENU)2, NULL, NULL);

	  // Controls
	  CreateWindowW(L"STATIC", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 37, 304, 231, 20, hWnd, NULL, NULL, NULL);
	  CreateWindowW(L"STATIC", L"Testing!!!", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 37, 354, 231, 20, hWnd, NULL, NULL, NULL);
	  hMx			= CreateWindowW(L"EDIT", userMx, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 37, 250, 35, 20, hWnd, NULL, NULL, NULL);
	  hFirstname	= CreateWindowW(L"EDIT", userFirstname, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 74, 250, 96, 20, hWnd, NULL, NULL, NULL);
	  hLastname		= CreateWindowW(L"EDIT", userLastname, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 172, 250, 96, 20, hWnd, NULL, NULL, NULL);
	  break;

	case WM_COMMAND:
	  switch(wp){
		case 1:
		  // To do: Fully implemented save function
		  GetWindowTextW(hMx, userMx, 5);
		  GetWindowTextW(hFirstname, userFirstname, 50);
		  GetWindowTextW(hLastname, userLastname, 50);
		  break;
		case 2:
		  alreadyOpen --;
		  //ShowWindow(hMainWnd, 1); // Uncomment for functioning hide/show
		  DestroyWindow(hWnd);
		  break;
	  }
	  break;
	default:
	  return DefWindowProcW(hWnd, msg, wp, lp);
  }
  return 0;
}