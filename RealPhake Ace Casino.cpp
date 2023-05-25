// Red here. Making my own poker/casino program so I can feed my addiction without having to open any games or gamble real money online or whatever.

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "menutext.h"

using namespace std;

// Window procedures
LRESULT CALLBACK MainWndProc   (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK UserInfoProc  (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK FTUSproc      (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CardTableProc (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK RoulTableProc (HWND, UINT, WPARAM, LPARAM);

// Handlers
HBITMAP hMainBG, hMemberBG, hFTUSbg, hCrdTblBG, hRltTblBG; // Bitmap backgrounds
HMENU   hMenu, hTutorialMenu, hCrdTblMenu, hRltTblMenu;    // Menus
HWND    hMainWnd, hUserInfo, hFTUS, hCrdTbl, hRltTbl,      // Windows
        hMx, hFirstname, hLastname,                        // Saveable Text
        hMemberBGWnd, hFTUSbgWnd, hMainBGWnd,              // "Windows" of the BGs
        hCrdTblBGWnd, hRltTblBGWnd;

int screenWidth  = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);
int alreadyOpen  = 0,          // The function that prevents you opening more than one menu
    unsaved,                   // The function that warns the player before exiting a game
    windowWidth, windowHeight; // The functions that allow automatic screen centering

// Strings containing the user info
wstring userID, userJoinDateString, userMxString, userFirstnameString, userLastnameString;

wchar_t userJoinDate[50], userMx[5], userFirstname[50], userLastname[50]; // To do: Dialogue and pronouns

void makeTimestamp(){ // The function that makes the join timestamp and fixes the ID during FTUS
  time_t today;
  time(&today);
  string timeGrab = ctime(&today); // To do: Fix ctime warning??
  string timestamp;
  timestamp.append(timeGrab, 4, 3);
  timestamp.append(timeGrab, 8, 2);
  timestamp.append(timeGrab, 20, 4);
  timestamp.insert(3, "/");
  timestamp.insert(6, "/");
  size_t spc = timestamp.find(' ');   if(spc != string::npos){timestamp.replace(4, 0, "0" ); timestamp.erase(5, 1);}
  size_t jan = timestamp.find("Jan"); if(jan != string::npos){timestamp.replace(0, 2, "01");}
  size_t feb = timestamp.find("Feb"); if(feb != string::npos){timestamp.replace(0, 2, "02");}
  size_t mar = timestamp.find("Mar"); if(mar != string::npos){timestamp.replace(0, 2, "03");}
  size_t apr = timestamp.find("Apr"); if(apr != string::npos){timestamp.replace(0, 2, "04");}
  size_t may = timestamp.find("May"); if(may != string::npos){timestamp.replace(0, 2, "05");}
  size_t jun = timestamp.find("Jun"); if(jun != string::npos){timestamp.replace(0, 2, "06");}
  size_t jul = timestamp.find("Jul"); if(jul != string::npos){timestamp.replace(0, 2, "07");}
  size_t aug = timestamp.find("Aug"); if(aug != string::npos){timestamp.replace(0, 2, "08");}
  size_t sep = timestamp.find("Sep"); if(sep != string::npos){timestamp.replace(0, 2, "09");}
  size_t oct = timestamp.find("Oct"); if(oct != string::npos){timestamp.replace(0, 2, "10");}
  size_t nov = timestamp.find("Nov"); if(nov != string::npos){timestamp.replace(0, 2, "11");}
  size_t dec = timestamp.find("Dec"); if(dec != string::npos){timestamp.replace(0, 2, "12");}
  timestamp.erase(2, 1);
  timestamp.append(" at ");
  timestamp.append(timeGrab, 11, 5);
  size_t noo = timestamp.find("12:"); if(noo != string::npos){timestamp += " PM";}
  size_t one = timestamp.find("13:"); if(one != string::npos){timestamp.replace(14, 2, "1");  timestamp += " PM";}
  size_t two = timestamp.find("14:"); if(two != string::npos){timestamp.replace(14, 2, "2");  timestamp += " PM";}
  size_t thr = timestamp.find("15:"); if(thr != string::npos){timestamp.replace(14, 2, "3");  timestamp += " PM";}
  size_t fou = timestamp.find("16:"); if(fou != string::npos){timestamp.replace(14, 2, "4");  timestamp += " PM";}
  size_t fiv = timestamp.find("17:"); if(fiv != string::npos){timestamp.replace(14, 2, "5");  timestamp += " PM";}
  size_t six = timestamp.find("18:"); if(six != string::npos){timestamp.replace(14, 2, "6");  timestamp += " PM";}
  size_t sev = timestamp.find("19:"); if(sev != string::npos){timestamp.replace(14, 2, "7");  timestamp += " PM";}
  size_t eig = timestamp.find("20:"); if(eig != string::npos){timestamp.replace(14, 2, "8");  timestamp += " PM";}
  size_t nin = timestamp.find("21:"); if(nin != string::npos){timestamp.replace(14, 2, "9");  timestamp += " PM";}
  size_t ten = timestamp.find("22:"); if(ten != string::npos){timestamp.replace(14, 2, "10"); timestamp += " PM";}
  size_t ele = timestamp.find("23:"); if(ele != string::npos){timestamp.replace(14, 2, "11"); timestamp += " PM";}
  size_t mid = timestamp.find("24:"); if(mid != string::npos){timestamp.replace(14, 2, " 12");}
  size_t aop = timestamp.find(" PM"); if(aop == string::npos){timestamp += " AM"; timestamp.erase(14, 1);}

  wifstream filein("UserInfo.txt", ios::in);
  if(filein.is_open()){
    getline(filein, userID);
  }
  filein.close();

  wofstream fileout("UserInfo.txt", ios::out);
  if(fileout.is_open()){
    fileout<<timestamp.c_str();
  }
  fileout.close();

  filein.open("UserInfo.txt", ios::in);
  if(filein.is_open()){
    getline(filein, userJoinDateString);
  }
  filein.close();

  userID.insert(userID.begin() + 7,  '-');
  userID.insert(userID.begin() + 15, '-');
  userID.resize(23);
}

void writeUserInfo(){ // The function that writes all the user info into individual lines in userinfo.txt
  wofstream fileout("UserInfo.txt", ios::out);
  if(fileout.is_open()){
    fileout<<userID<<endl<<userJoinDate<<endl<<userMx<<endl<<userFirstname<<endl<<userLastname;
  }
  fileout.close();
}

void clearUserInfo(){ // Used for when FTUS does not finish or if player wants to reset save file
  wofstream fileout("UserInfo.txt", ios::out);
  if(fileout.is_open()){
    fileout<<"";
  }
  fileout.close();
}

string makeID(const int len){ // The function that helps make the user's unique ID
  static const char ID[] =
    "0123456789987654321001234567899876543210"
    "BCDFGHJKLMNPRSTVWXY";
  string make;
  for(int i = 0; i < 25; ++i){
    make += ID[rand() % (sizeof(ID) - 1)];
  }
  return make;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd){ // Main
  // Register for main window
  WNDCLASSW wc = {0};

  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hInstance     = hInstance;
  wc.lpszClassName = L"mainWindowClass";
  wc.lpfnWndProc   = MainWndProc;

  if(!RegisterClassW(&wc))
    return -1;

  // Register for User Info window
  WNDCLASSW mui = {0};

  mui.hbrBackground = (HBRUSH)COLOR_WINDOW;
  mui.hCursor       = LoadCursor(NULL, IDC_ARROW);
  mui.hInstance     = hInstance;
  mui.lpszClassName = L"userInfoClass";
  mui.lpfnWndProc   = UserInfoProc;

  if(!RegisterClassW(&mui))
    return -1;

  // Register for First Time User Setup (FTUS) window
  WNDCLASSW ftus = {0};

  ftus.hbrBackground = (HBRUSH)COLOR_WINDOW;
  ftus.hCursor       = LoadCursor(NULL, IDC_ARROW);
  ftus.hInstance     = hInstance;
  ftus.lpszClassName = L"FTUSwindowClass";
  ftus.lpfnWndProc   = FTUSproc;

  if(!RegisterClassW(&ftus))
    return -1;

  // Register for the card table window
  WNDCLASSW crdtbl = {0};

  crdtbl.hbrBackground = (HBRUSH)COLOR_WINDOW;
  crdtbl.hCursor       = LoadCursor(NULL, IDC_ARROW);
  crdtbl.hInstance     = hInstance;
  crdtbl.lpszClassName = L"CardTableClass";
  crdtbl.lpfnWndProc   = CardTableProc;

  if(!RegisterClassW(&crdtbl))
    return -1;

  // Register for the roulette table window
  WNDCLASSW rlttbl = {0};

  rlttbl.hbrBackground = (HBRUSH)COLOR_WINDOW;
  rlttbl.hCursor       = LoadCursor(NULL, IDC_ARROW);
  rlttbl.hInstance     = hInstance;
  rlttbl.lpszClassName = L"RoulTableClass";
  rlttbl.lpfnWndProc   = RoulTableProc;

  if (!RegisterClassW(&rlttbl))
    return -1;

  // FTUS function. If user exists, makes the main window
  wifstream filein("UserInfo.txt", ios::in);
  if(filein.is_open()){
    getline(filein, userID);
    if(userID.empty()){
      MessageBox(hMainWnd, WELCOMETEXT, L"Welcome to RealPhake Ace Casino!", MB_OK);
      srand((unsigned)time(NULL));
      wofstream fileout("UserInfo.txt", ios::out);
      char* ID = new char[makeID(25).length()];
      if(fileout.is_open()){
        for(int i = 0; i < makeID(25).length(); i++)
          ID[i - 1] = makeID(25)[i];
        fileout<<ID;
        fileout.close();
      }
      windowWidth  = 340 + 16;
      windowHeight = 479 + 39;
      int windowX  = (screenWidth  - windowWidth)  / 2;
      int windowY  = (screenHeight - windowHeight) / 2;
      hFTUS = CreateWindowW(L"FTUSwindowClass", L"VIP Member Sign Up", WS_VISIBLE | WS_DLGFRAME, windowX, windowY, windowWidth, windowHeight, NULL, NULL, NULL, NULL);
    }
    else{
      windowWidth  = 640;
      windowHeight = 479;
      int windowX  = (screenWidth  - windowWidth)  / 2;
      int windowY  = (screenHeight - windowHeight) / 2;
      hMainWnd = CreateWindowW(L"mainWindowClass", L"RealPhake Ace Casino", WS_VISIBLE | WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX, windowX, windowY, windowWidth, windowHeight,
      NULL, NULL, NULL, NULL);
      // Location of the copy-from-strings from userinfo.txt
      // To do: Achievements
      getline(filein, userJoinDateString);
      userJoinDateString.copy(userJoinDate, 50, 0);
      getline(filein, userMxString);
      userMxString.copy(userMx, 5, 0);
      getline(filein, userFirstnameString);
      userFirstnameString.copy(userFirstname, 50, 0);
      getline(filein, userLastnameString);
      userLastnameString.copy(userLastname, 50, 0);
    }
    filein.close();
  }

  MSG msg = {0};

  while(GetMessage(&msg, NULL, NULL, NULL)){
    TranslateMessage(&msg);
    DispatchMessage (&msg);
  } return 0;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){ // Main window interactables
  switch(msg){
    case WM_CREATE:
      hMenu         = CreateMenu();
      hTutorialMenu = CreateMenu();
  
      // Bitmap shit(map)
      hMainBG = (HBITMAP) LoadImageW(NULL, L"Assets\\Backgrounds\\testimage2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
      hMainBGWnd = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, CW_DEFAULT, CW_DEFAULT, hWnd, NULL, NULL, NULL);
      SendMessageW(hMainBGWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hMainBG);

      // Main window menu bar
      AppendMenu(hMenu, MF_STRING, 1, L"User Info");
      AppendMenu(hMenu, MF_STRING, 2, L"Card Skins");
      AppendMenu(hMenu, MF_POPUP,  (UINT_PTR) hTutorialMenu, L"How to Play");
      AppendMenu(hMenu, MF_STRING, 11, L"About");
      AppendMenu(hMenu, MF_STRING, 12, L"(phake here)"); // To do: dynamic phake counter

      // Tutorial options
      AppendMenu(hTutorialMenu, MF_STRING, 3,  L"How to Play: RealPhake Ace Casino");
      AppendMenu(hTutorialMenu, MF_SEPARATOR,  NULL, NULL);
      AppendMenu(hTutorialMenu, MF_STRING, 4,  L"How to Play: Poker");
      AppendMenu(hTutorialMenu, MF_STRING, 5,  L"How to Play: Blackjack");
      AppendMenu(hTutorialMenu, MF_STRING, 6,  L"How to Play: Tycoon");
      AppendMenu(hTutorialMenu, MF_STRING, 7,  L"How to Play: War");
      AppendMenu(hTutorialMenu, MF_SEPARATOR,  NULL, NULL);
      AppendMenu(hTutorialMenu, MF_STRING, 8,  L"How to Play: Roulette");
      AppendMenu(hTutorialMenu, MF_STRING, 9,  L"How to Play: Craps");
      AppendMenu(hTutorialMenu, MF_STRING, 10, L"How to Play: Slots");
      SetMenu(hWnd, hMenu);

      // Buttons // Note for later: HIDE/SHOW BUTTONS?????
      CreateWindow(L"BUTTON", L"Play Poker!",     WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 47,  300, 125, 25, hWnd, (HMENU) 13, NULL, NULL);
      CreateWindow(L"BUTTON", L"Play Blackjack!", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 182, 300, 125, 25, hWnd, (HMENU) 14, NULL, NULL);
      CreateWindow(L"BUTTON", L"Play Tycoon!",    WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 317, 300, 125, 25, hWnd, (HMENU) 15, NULL, NULL);
      CreateWindow(L"BUTTON", L"Play War!",       WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 452, 300, 125, 25, hWnd, (HMENU) 16, NULL, NULL);
      CreateWindow(L"BUTTON", L"Play Roulette!",  WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 115, 335, 125, 25, hWnd, (HMENU) 17, NULL, NULL);
      CreateWindow(L"BUTTON", L"Play Craps!",     WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 250, 335, 124, 25, hWnd, (HMENU) 18, NULL, NULL);
      CreateWindow(L"BUTTON", L"Play Slots!",     WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 384, 335, 125, 25, hWnd, (HMENU) 19, NULL, NULL);
      break;

    case WM_COMMAND:
      switch(wp){
        // Make User Info window
        case 1:
          if(alreadyOpen == 0){
            windowWidth  = 691;
            windowHeight = 439;
            int windowX  = (screenWidth  - windowWidth)  / 2;
            int windowY  = (screenHeight - windowHeight) / 2;
            hUserInfo = CreateWindowW(L"userInfoClass", L"User Info", WS_VISIBLE | WS_BORDER | !WS_SIZEBOX, windowX, windowY, windowWidth, windowHeight, hMainWnd,
            NULL, NULL, NULL);
            ShowWindow(hMainWnd, 0); // Uncomment for functioning hide/show
            alreadyOpen++;
          }
          break;

        // Card skins page
        case 2:
          // To do: Card skins page
          MessageBox(hMainWnd, L"Coming soon, I'm working on it", L"Nah", MB_OK);
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
          hCrdTbl = CreateWindowW(L"CardTableClass", L"Poker", WS_VISIBLE | WS_BORDER | !WS_SIZEBOX, 250, 75, 1280, 720, NULL, NULL, NULL, NULL);
          ShowWindow(hMainWnd, 0); // Uncomment for functioning hide/show
          alreadyOpen++;
          break;
        case 14:
          // To do: Add Blackjack
          hCrdTbl = CreateWindowW(L"CardTableClass", L"Blackjack", WS_VISIBLE | WS_BORDER | !WS_SIZEBOX, 250, 75, 1280, 720, NULL, NULL, NULL, NULL);
          ShowWindow(hMainWnd, 0); // Uncomment for functioning hide/show
          alreadyOpen++;
          break;
        case 15:
          // To do: Add Tycoon
          hCrdTbl = CreateWindowW(L"CardTableClass", L"Tycoon", WS_VISIBLE | WS_BORDER | !WS_SIZEBOX, 250, 75, 1280, 720, NULL, NULL, NULL, NULL);
          ShowWindow(hMainWnd, 0); // Uncomment for functioning hide/show
          alreadyOpen++;
          break;
        case 16:
          // To do: Add War
          hCrdTbl = CreateWindowW(L"CardTableClass", L"War", WS_VISIBLE | WS_BORDER | !WS_SIZEBOX, 250, 75, 1280, 720, NULL, NULL, NULL, NULL);
          ShowWindow(hMainWnd, 0); // Uncomment for functioning hide/show
          alreadyOpen++;
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

    case WM_DESTROY:
      writeUserInfo();
      PostQuitMessage(0);
      break;

    default:
      return DefWindowProcW(hWnd, msg, wp, lp);
  }
  return 0;
}

LRESULT CALLBACK UserInfoProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){ // User Info window interactables
  switch(msg){
    case WM_CREATE:
      // Bitmap shit(map)
      hMemberBG    = (HBITMAP) LoadImageW(NULL, L"Assets\\Backgrounds\\MemberCard.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
      hMemberBGWnd = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, CW_DEFAULT, CW_DEFAULT, hWnd, NULL, NULL, NULL);
      SendMessageW(hMemberBGWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hMemberBG);
      
      // Buttons
      CreateWindow(L"BUTTON", L"Save", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 555, 345, 50, 25, hWnd, (HMENU) 1, NULL, NULL);
      CreateWindow(L"BUTTON", L"Done", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 615, 345, 50, 25, hWnd, (HMENU) 2, NULL, NULL);

      // Controls
      CreateWindowW(L"STATIC", userID.c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 37, 304, 231, 20, hWnd, NULL, NULL, NULL);
      CreateWindowW(L"STATIC", userJoinDate, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 37, 354, 231, 20, hWnd, NULL, NULL, NULL);
      hMx        = CreateWindowW(L"EDIT", userMx, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 37, 250, 35, 20, hWnd, NULL, NULL, NULL);
      hFirstname = CreateWindowW(L"EDIT", userFirstname, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 74, 250, 96, 20, hWnd, NULL, NULL, NULL);
      hLastname  = CreateWindowW(L"EDIT", userLastname, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 172, 250, 96, 20, hWnd, NULL, NULL, NULL);
      break;

    case WM_COMMAND:
      switch(wp){
        case 1:
          GetWindowTextW(hMx, userMx, 5);
          GetWindowTextW(hFirstname, userFirstname, 50);
          GetWindowTextW(hLastname, userLastname, 50);
          break;
        case 2:
          alreadyOpen--;
          ShowWindow(hMainWnd, 1); // Uncomment for functioning hide/show
          DestroyWindow(hWnd);
          break;
      }
      break;

    case WM_DESTROY:
      break;

    default:
      return DefWindowProcW(hWnd, msg, wp, lp);
  }
  return 0;
}

LRESULT CALLBACK FTUSproc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){ // FTUS window interactables
  switch(msg){
    case WM_CREATE:
      // Bitmap shit(map)
      hFTUSbg    = (HBITMAP) LoadImageW(NULL, L"Assets\\Backgrounds\\FTUS Clipboard.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); // To do: make a FTUS BG
      hFTUSbgWnd = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, CW_DEFAULT, CW_DEFAULT, hWnd, NULL, NULL, NULL);
      SendMessageW(hFTUSbgWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hFTUSbg);

      // Buttons
      CreateWindow(L"BUTTON", L"Register!", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 37, 345, 75, 25, hWnd, (HMENU) 1, NULL, NULL);

      // Controls
      makeTimestamp();
      CreateWindowW(L"STATIC", userID.c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 37, 304, 231, 20, hWnd, NULL, NULL, NULL);
      hMx        = CreateWindowW(L"EDIT", L"Mx.", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 37, 250, 35, 20, hWnd, NULL, NULL, NULL);
      hFirstname = CreateWindowW(L"EDIT", L"Taylor", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 74, 250, 96, 20, hWnd, NULL, NULL, NULL);
      hLastname  = CreateWindowW(L"EDIT", L"Gogetta", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 172, 250, 96, 20, hWnd, NULL, NULL, NULL);
      break;

    case WM_COMMAND:
      switch(wp){
        case 1:
          userJoinDateString.copy(userJoinDate, 50, 0);
          GetWindowTextW(hMx, userMx, 5);
          GetWindowTextW(hFirstname, userFirstname, 50);
          GetWindowTextW(hLastname, userLastname, 50);
          ShowWindow(hWnd, 0);
          windowWidth  = 640;
          windowHeight = 479;
          int windowX  = (screenWidth  - windowWidth)  / 2;
          int windowY  = (screenHeight - windowHeight) / 2;
          hMainWnd = CreateWindowW(L"mainWindowClass", L"RealPhake Ace Casino", WS_VISIBLE | WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX, windowX, windowY, windowWidth, windowHeight,
          NULL, NULL, NULL, NULL);
          MessageBox(hMainWnd, L"Now you're good to go!\nEnjoy your stay, and go earn some cash!", L"Registration Complete!", MB_OK);
          break;
      }
      break;

    case WM_DESTROY:
      clearUserInfo();
      PostQuitMessage(0);
      break;

    default:
      return DefWindowProcW(hWnd, msg, wp, lp);
  }
  return 0;
}

LRESULT CALLBACK CardTableProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){ // Card Table window interactables
  switch(msg){
    case WM_CREATE:
      // Bitmap shit(map)
      hCrdTblBG    = (HBITMAP)LoadImageW(NULL, L"Assets\\Backgrounds\\testimage.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); // To do: make a Card Table BG
      hCrdTblBGWnd = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, CW_DEFAULT, CW_DEFAULT, hWnd, NULL, NULL, NULL);
      SendMessageW(hCrdTblBGWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hCrdTblBG);

      // Buttons
      CreateWindow(L"BUTTON", L"Done", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 615, 345, 50, 25, hWnd, (HMENU)1, NULL, NULL);

      // Controls

      break;

    case WM_COMMAND:
      switch(wp){
        case 1:
          unsaved = MessageBox(hCrdTbl, IFYOULEAVE_MENUTEXT, L"Wait! Are you sure you want to leave the table?", MB_ICONWARNING | MB_YESNO);
          switch(unsaved){
            case IDYES:{
              alreadyOpen--;
              ShowWindow(hMainWnd, 1); // Uncomment for functioning hide/show
              DestroyWindow(hWnd);
              }
          }
          break;
      }
      break;

    case WM_DESTROY:
      break;

    default:
      return DefWindowProcW(hWnd, msg, wp, lp);
  }
  return 0;
}

LRESULT CALLBACK RoulTableProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) { // Roulette Table window interactables
  switch (msg) {
  case WM_CREATE:
    // Bitmap shit(map)
    hRltTblBG    = (HBITMAP)LoadImageW(NULL, L"Assets\\Backgrounds\\testimage.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); // To do: make a Roulette Table BG
    hRltTblBGWnd = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, CW_DEFAULT, CW_DEFAULT, hWnd, NULL, NULL, NULL);
    SendMessageW(hCrdTblBGWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hRltTblBG);

    // Buttons
    CreateWindow(L"BUTTON", L"Done", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 615, 345, 50, 25, hWnd, (HMENU)1, NULL, NULL);

    // Controls

    break;

  case WM_COMMAND:
    switch (wp) {
    case 1:
      unsaved = MessageBox(hCrdTbl, IFYOULEAVE_MENUTEXT, L"Wait! Are you sure you want to leave the table?", MB_ICONWARNING | MB_YESNO);
      switch (unsaved) {
      case IDYES: {
        alreadyOpen--;
        ShowWindow(hMainWnd, 1); // Uncomment for functioning hide/show
        DestroyWindow(hWnd);
      }
      }
      break;
    }
    break;

  case WM_DESTROY:
    break;

  default:
    return DefWindowProcW(hWnd, msg, wp, lp);
  }
  return 0;
}