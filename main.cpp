//Author: David Martin 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Copyright 2008 David Martin. All Rights Reserved.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "resource.h"
#include "winnetwk.h"

#include <ctype.h>
#include <process.h>
#include <commctrl.h>

const char ClassName[] = "MainWindowClass";
HWND hWndButton;
void Thread(PVOID pvoid);
void secondPage();
void mainBuilding();
void commerceBuilding();
void sheaBuilding();
void okPrinterButton();
void check_username();
void serverConn();
void printerConnection();
void createStatic();
char* errorCode(DWORD dwResult);

HWND hold;
HWND hWndUserbox;
HWND hWndUserStatic;
HWND hWndPasswordEditBox;
HWND hWndPasswordStatic;
HWND hWndOKButton;
HWND hWndCancelButton;
HWND hWnd;
HWND hWndBuildingComboBox;
HWND hWndOKPrinterButton;
HWND hWndMainBuildingComboBox;
HWND hWndCommerceBuildingComboBox;
HWND hWndSheaBuildingComboBox;
HWND hWndBuildingStatic;
HWND hWndPrinterStatic;
HWND hWndProgressBar;
HWND hWndConnectionStatic;
HWND hWndCopyStatic;
//char printerBuffer[256];
char* tempBuffer=new char[25];
char UserBuffer[40];
char PasswordBuffer[6];
char BuildingBuffer[25];

LRESULT CALLBACK WndProc( HWND    hWnd,
                          UINT    Msg,
                          WPARAM  wParam,          
                          LPARAM  lParam )
{
    switch (Msg)
	{

		   
        case WM_CREATE:
		{
             hWndUserbox = CreateWindow(
            "EDIT", 
            NULL, 
            WS_VISIBLE | WS_CHILD | WS_BORDER, 
            125, 
            10, 
            250, 
            25, 
            hWnd, 
            (HMENU)IDC_USERBOX_TEXT, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL);
//WS_VISIBLE | WS_CHILD | SS_CENTER
            if (!hWndUserbox)
                MessageBox(NULL, "Edit Box Failed.", "Error", MB_OK | MB_ICONERROR);

			

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			
            hWndUserStatic = CreateWindow(
            "STATIC", 
            NULL, 
            WS_VISIBLE | WS_CHILD | SS_CENTER | SS_SIMPLE, 
            5, 
            10, 
            100, 
            20, 
            hWnd, 
            (HMENU)IDC_USERSTATIC_TEXT, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL);

            if (!hWndUserStatic)
                MessageBox(NULL, "ERROR", "Error", MB_OK | MB_ICONERROR);

            if (!SetWindowText(hWndUserStatic, "UserName"))
             MessageBox(NULL, "Failed To Set Text.", "Error", MB_OK | MB_ICONERROR);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			hWndPasswordEditBox = CreateWindow(
            "EDIT", 
            NULL, 
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 
            125, 
            50, 
            45, 
            25, 
            hWnd, 
            (HMENU)IDC_PASSWORDEDITBOX_TEXT, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL);
//WS_VISIBLE | WS_CHILD | SS_CENTER
            if (!hWndPasswordEditBox)
                MessageBox(NULL, "Edit Box Failed.", "Error", MB_OK | MB_ICONERROR);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            hWndPasswordStatic = CreateWindow(
            "STATIC", 
            NULL, 
            WS_VISIBLE | WS_CHILD | SS_CENTER | SS_SIMPLE, 
            5, 
            50, 
            100, 
            20, 
            hWnd, 
            (HMENU)IDC_PASSWORDSTATIC_TEXT, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL);

            if (!hWndPasswordStatic)
                MessageBox(NULL, "ERROR", "Error", MB_OK | MB_ICONERROR);

            if (!SetWindowText(hWndPasswordStatic, "Password"))
              MessageBox(NULL, "Failed To Set Text.", "Error", MB_OK | MB_ICONERROR);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			hWndOKButton = CreateWindowEx(
            0, 
            "BUTTON", 
            "OK", 
            WS_VISIBLE | WS_CHILD, 
            100, 
            100, 
            80, 
            20, 
            hWnd, 
            (HMENU) IDB_OKBUTTON, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL); 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			hWndCancelButton = CreateWindowEx(
            0, 
            "BUTTON", 
            "CANCEL", 
            WS_VISIBLE | WS_CHILD, 
            200, 
            100, 
            80, 
            20, 
            hWnd, 
            (HMENU) IDB_CANCELBUTTON, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL); 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
        }
        break; 

        case WM_COMMAND: 
      {
            switch (LOWORD(wParam))
         {
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
                case IDB_OKBUTTON:
            {
                    switch (HIWORD(wParam))
                    {
                        case BN_CLICKED:
							{    //MessageBox(NULL, "Selected Button", "Success", MB_OK | MB_ICONINFORMATION);

								check_username();
							}
							break;
					};
            }break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				case IDB_CANCELBUTTON:
            {
                    switch (HIWORD(wParam))
                    {
                        case BN_CLICKED:
							{    //MessageBox(NULL, "Selected Button", "Success", MB_OK | MB_ICONINFORMATION);

								SendMessage(hWnd,WM_DESTROY,NULL,NULL);
							}
							break;
					};
            }break;

//////////////////////////////////////////////////////////////////////////////////////////////////////
				case IDC_USERBOX_TEXT:
                {
                    switch(HIWORD(wParam))
                    {
                        case EN_CHANGE:
                        {
                            
                            GetWindowText(hWndUserbox, UserBuffer, 256);
                            //SetWindowText(hWnd, Buffer);

                        }
                    }
                }
                break;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
				case IDC_PASSWORDEDITBOX_TEXT:
                {
                    switch(HIWORD(wParam))
                    {
                        case EN_CHANGE:
                        {
                            
                            GetWindowText(hWndPasswordEditBox, PasswordBuffer, 256);
                            //SetWindowText(hWnd, Buffer);

                        }
                    }
                }
                break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
				case IDC_BUILDINGCOMBOBOX_TEXT:
              {
					
					switch(HIWORD(wParam))
					{
						case CBN_SELCHANGE:
						{
							
							long lResult=SendMessage(GetDlgItem(hWnd, IDC_BUILDINGCOMBOBOX_TEXT), CB_GETCURSEL , 0, 0);
									
							switch(lResult)
							{
							case 0:
								mainBuilding();
								break;
							case 1:
								commerceBuilding();
								break;
							case 2:
								sheaBuilding();
								break;
							default:break;
							};

								
							 
							 
							 
							 
							 //MessageBox(NULL,"Happy",(LPCTSTR)(lResult), MB_OK | MB_ICONERROR);

                            //SetWindowText(hWnd, Buffer);

                        }
                    }
                }
                break;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				case IDC_MAINBUILDINGCOMBOBOX_TEXT:
              {
					switch(HIWORD(wParam))
					{
						case CBN_SELCHANGE:
						{
							long lResult=SendMessage(GetDlgItem(hWnd, IDC_BUILDINGCOMBOBOX_TEXT), CB_GETCURSEL , 0, 0);
									
							switch(lResult)
							{
							case 0:
								
								tempBuffer="wlab3";
								break;
													
							default:break;
							};

								
							 
							 
						okPrinterButton();	 
							 
							 //MessageBox(NULL,"Happy",(LPCTSTR)(lResult), MB_OK | MB_ICONERROR);

                            //SetWindowText(hWnd, Buffer);

                        }
                    }
                }
                break;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				case IDC_COMMERCEBUILDINGCOMBOBOX_TEXT:
					{
					switch(HIWORD(wParam))
					{
						case CBN_SELCHANGE:
						{
							long lResult=SendMessage(GetDlgItem(hWnd, IDC_BUILDINGCOMBOBOX_TEXT), CB_GETCURSEL , 0, 0);
									
							switch(lResult)
							{
							case 0:
								tempBuffer="comet1";
								break;
														
							default:break;
							};

								
							 
							 
							 okPrinterButton();
							 
							 //MessageBox(NULL,"Happy",(LPCTSTR)(lResult), MB_OK | MB_ICONERROR);

                            //SetWindowText(hWnd, Buffer);

                        }
                    }
                }
                break;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				case IDC_SHEABUILDINGCOMBOBOX_TEXT:
              {
					switch(HIWORD(wParam))
					{
						case CBN_SELCHANGE:
						{
							long lResult=SendMessage(GetDlgItem(hWnd, IDC_BUILDINGCOMBOBOX_TEXT), CB_GETCURSEL , 0, 0);
									
							switch(lResult)
							{
							case 0:
								tempBuffer="commons1";
								break;
							case 1:
								tempBuffer="commons2";
								break;
							
							default:break;
							};

								
							 
							okPrinterButton();
							 
							 
							 //MessageBox(NULL,"Happy",(LPCTSTR)(lResult), MB_OK | MB_ICONERROR);

                            //SetWindowText(hWnd, Buffer);

                        }
                    }
                }
                break;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				  case IDB_OKPRINTERBUTTON:
            {
                    switch (HIWORD(wParam))
                    {
                        case BN_CLICKED:
							{    //MessageBox(NULL, "Selected Button", "Success", MB_OK | MB_ICONINFORMATION);

								printerConnection();
							}
							break;
					};
            }break;
					



















/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                case IDB_BUTTON:
            {
                    switch (HIWORD(wParam))
                    {
                        case BN_CLICKED:
							{    //MessageBox(NULL, "Selected Button", "Success", MB_OK | MB_ICONINFORMATION);

							//	_beginthread(Thread, 0, NULL);
					
	}
	break;
	};
                    }break;
//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
				case IDB_BUTTON2:
                {
 //
// Call the WNetAddConnection2 function to make the connection,
//   specifying a persistent connection

NETRESOURCE nr;

TCHAR szUserName[256] = UserBuffer,
    szPassword[32] = PasswordBuffer,
    //szLocalName[32] = NULL,
    szRemoteName[50] = "\\\\prometheus";

nr.dwType = RESOURCETYPE_ANY;
nr.lpLocalName = NULL;
nr.lpRemoteName = szRemoteName;
nr.lpProvider = NULL;


DWORD dwResult = WNetAddConnection2(&nr, szPassword, szUserName, FALSE);
int connection=0;
 
// Process errors.
//  The local device is already connected to a network resource.
//

if(dwResult == ERROR_NO_NETWORK)
  MessageBox(NULL,"Connection added to ","Test",MB_OK | MB_ICONERROR);
else 
{  MessageBox(NULL,"ERROR","ERROR",MB_OK | MB_ICONERROR);
	connection=1;
}
//////////////////////////////////////////////////////////////////////////////
//if(connection==1)
//{
//	PRINTER_INFO_2 pr;
//
//	pr.pServerName="prometheus";
//	pr.pPrinterName="commons1";
//	pr.Attributes=NULL;
//	pr.AveragePPM=NULL;
//	pr.cJobs=NULL;
//	pr.DefaultPriority=NULL;
//	pr.pComment=NULL;
//	pr.pDatatype=NULL;
//	pr.pDevMode=NULL;
//	pr.pDriverName=NULL;
//	pr.pLocation=NULL;
//	pr.pParameters=NULL;
//	pr.pPortName=NULL;
//	pr.pPrintProcessor=NULL;
//	pr.Priority=NULL;
//	pr.pSecurityDescriptor=NULL;
//	pr.pSepFile=NULL;
//	pr.StartTime=NULL;
//	pr.Status=NULL;
//	pr.UntilTime=NULL;
//
//	AddPrinter(
//		LPTSTR("prometheus"),     // server name
//		2,      // printer information level
//		LPBYTE(&pr)   // printer information buffer
//	);
}break;*/
	};
                    }break;
				
        case WM_CLOSE:
            DestroyWindow(hWnd);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;
		

        default:
            return (DefWindowProc(hWnd, Msg, wParam, lParam));
    }

    return 0;
}

INT WINAPI WinMain( HINSTANCE  hInstance,
                    HINSTANCE  hPrevInstance,
                    LPSTR      lpCmdLine,
                    INT        nCmdShow )
{
    WNDCLASSEX    wc;

    wc.cbSize           = sizeof(WNDCLASSEX);
    wc.style            = 0;
    wc.lpfnWndProc      = (WNDPROC)WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    wc.hIconSm          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)(COLOR_APPWORKSPACE+11);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = ClassName;

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Failed To Register The Window Class.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    

    hWnd = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    ClassName,
    "Wireless Print Manager ©2008 David Martin. All Rights Reserved.",
    WS_EX_APPWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    450,
    200,
    NULL,
    NULL,
    hInstance,
    NULL);

    if (!hWnd)
    {
        MessageBox(NULL, "Window Creation Failed.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    MSG    Msg;

    while (GetMessage(&Msg, NULL, 0, 0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

void Thread (PVOID pvoid)
{
 //HWND shell;
//	MessageBox(NULL,PasswordBuffer,"NULL",MB_OK | MB_ICONINFORMATION);

					ShellExecute(NULL, "open", "http://prometheus/cgi-bin/webclient.exe"
						, NULL, NULL, SW_HIDE);





							
      //Sleep(5000); 
		//MessageBox(NULL,"HELP1","HELP1",MB_OK | MB_ICONINFORMATION);
	while(!hold)
	{
		hold = FindWindow(NULL,LPCSTR("Connect to prometheus.uhd.campus"));
			
	}
	//if(!hold)
	//{
	//Sleep(10000);
	//	hold = FindWindow(NULL,LPCSTR("Connect to prometheus.uhd.campus"));
	//}

		//if(!hold)
		//	MessageBox(NULL,"FOUND","FOUND",MB_OK | MB_ICONINFORMATION);
	//Sleep(5000);
  
	//if (hold!=0) //SendMessage(hold,WM_CLOSE,0,0)
	//{
		SetFocus(hold);
		Sleep(500);
		//MessageBox(NULL,"HELP","HELP",MB_OK | MB_ICONINFORMATION);

//char* domain=new char[11];
//domain="academic\\";
int count=0;
//while(count < 9)
//{
//keybd_event(BYTE(VkKeyScan(*(domain+count))),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
//keybd_event(BYTE(VkKeyScan(*(domain+count))),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
//count++;
//}

count=0;

while(count < (int)(strlen(UserBuffer)))
{
keybd_event(BYTE(VkKeyScan(*(UserBuffer+count))),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan(*(UserBuffer+count))),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
count++;
}

keybd_event(VK_TAB,0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(VK_TAB ,0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);

count=0;

while(count < (int)(strlen(PasswordBuffer)))
{
	if(isupper(*(PasswordBuffer+count)))
	{
		keybd_event(VK_SHIFT,0,KEYEVENTF_EXTENDEDKEY | 0,0 );
	

	}

keybd_event(BYTE(VkKeyScan(*(PasswordBuffer+count))),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan(*(PasswordBuffer+count))),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);

if(isupper(*(PasswordBuffer+count)))
	{
		
		keybd_event(VK_SHIFT,0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);

	}

count++;
}

//keybd_event(VK_TAB,0,KEYEVENTF_EXTENDEDKEY | 0,0 );
//keybd_event(VK_TAB ,0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);

//keybd_event(VK_TAB,0,KEYEVENTF_EXTENDEDKEY | 0,0 );
//keybd_event(VK_TAB ,0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);


keybd_event(VK_RETURN,0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(VK_RETURN ,0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);

SendMessage(hWnd,WM_DESTROY,NULL,NULL);




/*
keybd_event(BYTE(VkKeyScan('a')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('a')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('c')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('c')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('a')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('a')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('d')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('d')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('e')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('e')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('m')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('m')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('i')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('i')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('c')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('c')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('\\')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('\\')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('a')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('a')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('d')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('d')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('m')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('m')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('i')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('i')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('n')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('n')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(VK_TAB,0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(VK_TAB ,0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('1')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('1')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('2')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('2')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('3')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('3')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('4')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('4')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('5')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('5')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
keybd_event(BYTE(VkKeyScan('6')),0,KEYEVENTF_EXTENDEDKEY | 0,0 );
keybd_event(BYTE(VkKeyScan('6')),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
	//}*/
 }


void secondPage()
{




DestroyWindow(hWndConnectionStatic);
DestroyWindow(hWndProgressBar);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

hWndBuildingComboBox = CreateWindow(
            "COMBOBOX", 
            NULL, 
            WS_VISIBLE | WS_CHILD | CBS_DROPDOWN, 
            10, 
            25, 
            125, 
            800, 
            hWnd, 
            (HMENU)IDC_BUILDINGCOMBOBOX_TEXT, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL);

            if (!hWndBuildingComboBox)
                MessageBox(NULL, "ComboBox Failed.", "Error", MB_OK | MB_ICONERROR);

            SendMessage(GetDlgItem(hWnd, IDC_BUILDINGCOMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)"Main");
            SendMessage(GetDlgItem(hWnd, IDC_BUILDINGCOMBOBOX_TEXT), CB_ADDSTRING, 1, (LPARAM)"Commerce");
            SendMessage(GetDlgItem(hWnd, IDC_BUILDINGCOMBOBOX_TEXT), CB_ADDSTRING, 2, (LPARAM)"Shea");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//MessageBox(NULL,(LPCTSTR)(BuildingBuffer),"ERROR", MB_OK | MB_ICONERROR);




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            hWndBuildingStatic = CreateWindow(
            "STATIC", 
            NULL, 
            WS_VISIBLE | WS_CHILD | SS_CENTER | SS_SIMPLE, 
            10, 
            5,
            150, 
            20, 
            hWnd, 
            (HMENU)IDC_BUILDINGSTATIC_TEXT, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL);

            if (!hWndBuildingStatic)
                MessageBox(NULL, "ERROR", "Error", MB_OK | MB_ICONERROR);

            if (!SetWindowText(hWndBuildingStatic, "Select Building"))
              MessageBox(NULL, "Failed To Set Text.", "Error", MB_OK | MB_ICONERROR);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			hWndPrinterStatic = CreateWindow(
            "STATIC", 
            NULL, 
            WS_VISIBLE | WS_CHILD | SS_CENTER | SS_SIMPLE, 
            250, 
            5,
            150, 
            20, 
            hWnd, 
            (HMENU)IDC_PRINTERSTATIC_TEXT, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL);

            if (!hWndPrinterStatic)
                MessageBox(NULL, "ERROR", "Error", MB_OK | MB_ICONERROR);

            if (!SetWindowText(hWndPrinterStatic, "Choose a Printer"))
                MessageBox(NULL, "Failed To Set Text.", "Error", MB_OK | MB_ICONERROR);



}

void mainBuilding()
{


DestroyWindow(hWndMainBuildingComboBox);
DestroyWindow(hWndCommerceBuildingComboBox);
DestroyWindow(hWndSheaBuildingComboBox);
DestroyWindow(hWndOKPrinterButton);


hWndMainBuildingComboBox = CreateWindow(
            "COMBOBOX", 
            NULL, 
            WS_VISIBLE | WS_CHILD | CBS_DROPDOWN, 
            225, 
            25, 
            150, 
            800,  
            hWnd, 
            (HMENU)IDC_MAINBUILDINGCOMBOBOX_TEXT, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL);

            if (!hWndBuildingComboBox)
                MessageBox(NULL, "ComboBox Failed.", "Error", MB_OK | MB_ICONERROR);

            SendMessage(GetDlgItem(hWnd, IDC_MAINBUILDINGCOMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)"WLAB3");
            //SendMessage(GetDlgItem(hWnd, IDC_MAINBUILDINGCOMBOBOX_TEXT), CB_ADDSTRING, 1, (LPARAM)"main_printer2");

}


void commerceBuilding()
{

	DestroyWindow(hWndMainBuildingComboBox);
DestroyWindow(hWndCommerceBuildingComboBox);
DestroyWindow(hWndSheaBuildingComboBox);
DestroyWindow(hWndOKPrinterButton);

	hWndCommerceBuildingComboBox = CreateWindow(
            "COMBOBOX", 
            NULL, 
            WS_VISIBLE | WS_CHILD | CBS_DROPDOWN, 
            225, 
            25, 
            150, 
            800,   
            hWnd, 
            (HMENU)IDC_COMMERCEBUILDINGCOMBOBOX_TEXT, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL);

            if (!hWndBuildingComboBox)
                MessageBox(NULL, "ComboBox Failed.", "Error", MB_OK | MB_ICONERROR);

            SendMessage(GetDlgItem(hWnd, IDC_COMMERCEBUILDINGCOMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)"COMET1");
            //SendMessage(GetDlgItem(hWnd, IDC_COMMERCEBUILDINGCOMBOBOX_TEXT), CB_ADDSTRING, 1, (LPARAM)"");







}


void sheaBuilding()
{

	DestroyWindow(hWndMainBuildingComboBox);
DestroyWindow(hWndCommerceBuildingComboBox);
DestroyWindow(hWndSheaBuildingComboBox);
DestroyWindow(hWndOKPrinterButton);

	hWndSheaBuildingComboBox = CreateWindow(
            "COMBOBOX", 
            NULL, 
            WS_VISIBLE | WS_CHILD | CBS_DROPDOWN, 
            225, 
            25, 
            150, 
            800, 
            hWnd, 
            (HMENU)IDC_SHEABUILDINGCOMBOBOX_TEXT, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL);

            if (!hWndBuildingComboBox)
                MessageBox(NULL, "ComboBox Failed.", "Error", MB_OK | MB_ICONERROR);

            SendMessage(GetDlgItem(hWnd, IDC_SHEABUILDINGCOMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)"COMMONS1");
            SendMessage(GetDlgItem(hWnd, IDC_SHEABUILDINGCOMBOBOX_TEXT), CB_ADDSTRING, 1, (LPARAM)"COMMONS2");

}


void okPrinterButton()
{


hWndOKPrinterButton = CreateWindowEx(
            0, 
            "BUTTON", 
            "OK", 
            WS_VISIBLE | WS_CHILD, 
            100, 
            100, 
            80, 
            20, 
            hWnd, 
            (HMENU) IDB_OKPRINTERBUTTON, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL); 







}


void check_username()
{

	int max_user=strlen(UserBuffer);
	int max_pass=strlen(PasswordBuffer);
int counter_user=0;
int counter_pass=0;
int result_user=0;
int result_pass=0;
while(counter_user < max_user)
{
result_user=isalnum(UserBuffer[counter_user]);

if(result_user!=0)
	counter_user++;

else
	break;


}

while(counter_pass < max_pass)
{
result_pass=isalnum(PasswordBuffer[counter_pass]);

if(result_pass!=0)
	counter_pass++;

else
	break;


}
 
if(result_user!=0)
	if(result_pass != 0)
		serverConn();
	else
	MessageBox(NULL,"Password is not in the correct format. Please try again.","ERROR", MB_ICONERROR | MB_OK);

else
	MessageBox(NULL,"Username is not in the correct format. Please try again.","ERROR", MB_ICONERROR | MB_OK);









}

void serverConn()
{

DestroyWindow(hWndUserbox);
DestroyWindow(hWndUserStatic);
DestroyWindow(hWndPasswordEditBox);
DestroyWindow(hWndPasswordStatic);
DestroyWindow(hWndOKButton);
DestroyWindow(hWndOKPrinterButton);
DestroyWindow(hWndCancelButton);

hWndProgressBar = CreateWindowEx( 
            0,
            PROGRESS_CLASS, 
            (LPSTR)NULL, 
            WS_VISIBLE | WS_CHILD, 
            0, 
            50, 
            500, 
            20, 
            hWnd, 
            (HMENU)IDPB_PROGRESS_BAR, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL); 

            if (!hWndProgressBar)
            MessageBox(NULL, "Progress Bar Failed.", "Error", MB_OK | MB_ICONERROR);











createStatic();


if (!SetWindowText(hWndConnectionStatic, "Setting up connection structure"))
              MessageBox(NULL, "Failed To Set Text.", "Error", MB_OK | MB_ICONERROR);


SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
Sleep(1000);


NETRESOURCE nr;

char* _UserBuffer=new char[50];
_UserBuffer="academic\\";
strcat(_UserBuffer,UserBuffer);
strcpy(UserBuffer, _UserBuffer);
//copy error buffers algorithim and change error message insted of just the error code
//tp=UserBuffer;

//char* tc=new char[6];
//tc=PasswordBuffer;

//TCHAR szUserName = *tp ,
  //  szPassword =*tc,
    //szLocalName[32] = NULL,
    //szRemoteName[15] = "\\\\prometheus$";

TCHAR szRemoteName[15] = "\\\\prometheus";
nr.dwType = RESOURCETYPE_ANY;
nr.lpLocalName = NULL;
nr.lpRemoteName = szRemoteName;
nr.lpProvider = NULL;

DestroyWindow(hWndConnectionStatic);
createStatic();


if (!SetWindowText(hWndConnectionStatic, "Connecting to printer server.............."))
              MessageBox(NULL, "Failed To Set Text.", "Error", MB_OK | MB_ICONERROR);


SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
Sleep(1000);


DWORD dwResult = WNetAddConnection2(&nr, PasswordBuffer, UserBuffer, FALSE);
int connection=0;
char* retrieve=new char[25];
retrieve=errorCode(dwResult);
char* ta=new char[7];
ta="Error: ";
strcat(ta,retrieve);
strcpy(retrieve,ta);

// Process errors.
//  The local device is already connected to a network resource.
//
//if(dwResult == NO_ERROR)

if(dwResult == NO_ERROR)
{
DestroyWindow(hWndConnectionStatic);
createStatic();
SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);



if (!SetWindowText(hWndConnectionStatic, "Connection Established           "))
              MessageBox(NULL, "Failed To Set Text.", "Error", MB_OK | MB_ICONERROR);

Sleep(1000);
secondPage();

}
else 
{  
	DestroyWindow(hWndConnectionStatic);
createStatic();

	if (!SetWindowText(hWndConnectionStatic, (LPCTSTR)retrieve))
                MessageBox(NULL, "Failed To Set Text.", "Error", MB_OK | MB_ICONERROR);


	
	hWndCancelButton = CreateWindowEx(
            0, 
            "BUTTON", 
            "CANCEL", 
            WS_VISIBLE | WS_CHILD, 
            200, 
            100, 
            80, 
            20, 
            hWnd, 
            (HMENU) IDB_CANCELBUTTON, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL); 

}

}


char* errorCode(DWORD dwResult)
{
char* hold=new char[10];
ltoa(dwResult,hold,10);
char* error=new char[40];





switch(dwResult)
{
case ERROR_ACCESS_DENIED: 
	error="Network Access Denied";
	break;
case ERROR_ALREADY_ASSIGNED:  
	error="Network Already Connected";
	break;
case ERROR_BAD_DEV_TYPE: 
	error="Drive Type Mismatch"; 
	break;
case ERROR_BAD_DEVICE: 
	error="Computer name is invalid";
	break;
case ERROR_BAD_NET_NAME:
	error="Bad or unknown network drive name";
	break;
case ERROR_BAD_PROFILE:
	error="Bad profile";
	break;
case ERROR_BAD_PROVIDER:
	error="Bad network provider layer";
	break;
case ERROR_BUSY: 
	error="Network is busy";
	break;
case ERROR_CANCELLED:
	error="Connection terminated by user";
	break;
case ERROR_CANNOT_OPEN_PROFILE: 
	error="Profile cannot be opened";
	break;
case ERROR_DEVICE_ALREADY_REMEMBERED:
	error="Device is auto-connected by the user profile";
	break;
case ERROR_EXTENDED_ERROR:
	error="Network-specific error occured.";
	break;
case ERROR_INVALID_PASSWORD:
	error="Invalid password";
	break;
case ERROR_NO_NET_OR_BAD_PATH:
	error="no network or bad connection path";
	break;
case ERROR_NO_NETWORK: 
	error="Network is Unavailable";
	break;
case ERROR_BAD_NETPATH: 
	error="no network or bad connection path";
	break;
case NO_ERROR: 
	error="Connection Established";
	break;
case ERROR_LOGON_FAILURE:
	error="Username or password is incorrect";
	break;
case ERROR_SESSION_CREDENTIAL_CONFLICT:
	error="Multiple connections to a server";
	break;


default:
	{
	error="Error Code: ";
	strcpy(error,hold);
	break;
	}
	};



return error;



}

void printerConnection()
{




DestroyWindow(hWndBuildingComboBox);
DestroyWindow(hWndMainBuildingComboBox);
DestroyWindow(hWndCommerceBuildingComboBox);
DestroyWindow(hWndSheaBuildingComboBox);
DestroyWindow(hWndBuildingStatic);
DestroyWindow(hWndPrinterStatic);
//DestroyWindow(hWndCancelButton);

hWndProgressBar = CreateWindowEx( 
            0,
            PROGRESS_CLASS, 
            (LPSTR)NULL, 
            WS_VISIBLE | WS_CHILD, 
            0, 
            50, 
            500, 
            20, 
            hWnd, 
            (HMENU)IDPB_PROGRESS_BAR, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL); 

            if (!hWndProgressBar)
            MessageBox(NULL, "Progress Bar Failed.", "Error", MB_OK | MB_ICONERROR);








DestroyWindow(hWndConnectionStatic);
createStatic();
if (!SetWindowText(hWndConnectionStatic, "Printer connection structure intializing..."))
               MessageBox(NULL, "Failed To Set Text.", "Error", MB_OK | MB_ICONERROR);


//if (!SetWindowText(hWndConnectionStatic, "Setting up connection structure"))
  //            MessageBox(NULL, "Failed To Set Text.", "Error", MB_OK | MB_ICONERROR);


SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
Sleep(1000);

//tempBuffer
PRINTER_INFO_2 pr;

	pr.pServerName="prometheus";
	pr.pPrinterName=tempBuffer;
//	pr.Attributes=NULL;
//	pr.AveragePPM=NULL;
//	pr.cJobs=NULL;
//	pr.DefaultPriority=NULL;
//	pr.pComment=NULL;
//	pr.pDatatype=NULL;
//	pr.pDevMode=NULL;
//	pr.pDriverName=NULL;
//	pr.pLocation=NULL;
//	pr.pParameters=NULL;
//	pr.pPortName=NULL;
//	pr.pPrintProcessor=NULL;
//	pr.Priority=NULL;
//	pr.pSecurityDescriptor=NULL;
//	pr.pSepFile=NULL;
//	pr.StartTime=NULL;
//	pr.Status=NULL;
//	pr.UntilTime=NULL;


DestroyWindow(hWndConnectionStatic);
createStatic();

if (!SetWindowText(hWndConnectionStatic, "Connecting to printer"))
               MessageBox(NULL, "Failed To Set Text.", "Error", MB_OK | MB_ICONERROR);


SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);



AddPrinterConnection("\\\\prometheus\\commons1");


//	AddPrinter("prometheus",2,(LPBYTE)(&pr));

	DestroyWindow(hWndConnectionStatic);
createStatic();

if (!SetWindowText(hWndConnectionStatic, "Please wait while the printer queue is loading up..."))
                MessageBox(NULL, "Failed To Set Text.", "Error", MB_OK | MB_ICONERROR);


SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);



	_beginthread(Thread, 0, NULL);

}

void createStatic()
{

hWndConnectionStatic = CreateWindow(
            "STATIC", 
            NULL, 
            WS_VISIBLE | WS_CHILD | SS_CENTER | SS_SIMPLE, 
            75, 
            10, 
            2500, 
            20, 
            hWnd, 
            (HMENU)IDC_CONNECTIONSTATIC_TEXT, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL);

            if (!hWndConnectionStatic)
                MessageBox(NULL, "ERROR", "Error", MB_OK | MB_ICONERROR);

            




}




