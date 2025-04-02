// dllmain.cpp : Définit les routines d'initialisation pour la DLL.
//

#include "pch.h"
#include "framework.h"
#include <afxwin.h>
#include <afxdllx.h>
#include "SimulationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE RetroCodeRegexDLL = { false, nullptr };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Supprimez cet élément si vous utilisez lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("Initialisation de RetroCode-Regex.DLL !\n");

		// Initialisation unique de la DLL d'extension
		if (!AfxInitExtensionModule(RetroCodeRegexDLL, hInstance))
			return 0;

		// Insérez cette DLL dans la chaîne de ressource
		// REMARQUE : Si cette DLL d'extension est implicitement liée par
		//  une DLL régulière MFC (par exemple un contrôle ActiveX)
		//  au lieu d'une application MFC, supprimez
		//  cette ligne de DllMain et placez-la dans une fonction
		//  séparée exportée à partir de cette DLL d'extension.  La DLL régulière
		//  qui utilise cette DLL d'extension doit ensuite explicitement appeler cette
		//  fonction pour initialiser cette DLL d'extension.  Dans le cas contraire,
		//  l'objet CDynLinkLibrary ne sera pas attaché à la chaîne de ressource
		//  de la DLL régulière et de nombreux problèmes
		//  seront générés.

		new CDynLinkLibrary(RetroCodeRegexDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Fin d'exécution de RetroCode-Regex.DLL !\n");

		// Terminez la bibliothèque avant que les destructeurs soient appelés
		AfxTermExtensionModule(RetroCodeRegexDLL);
	}
	return 1;   // ok
}

#ifdef _WIN64
#pragma comment(linker, "/EXPORT:Simulation=Simulation")
#else
#pragma comment(linker, "/EXPORT:Simulation=_Simulation@16")
#endif


extern "C" void CALLBACK Simulation(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hinst);
	UNREFERENCED_PARAMETER(lpszCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		return;
	}

	CWnd* pWnd = CWnd::FromHandle(hwnd);

	CSimulationDlg dlg(pWnd);
	dlg.DoModal();
}