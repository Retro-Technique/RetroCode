/**
 *
 * Retro Code
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2025 Retro Technique
 *
 * This software is a computer program whose purpose is to provide
 * minimalist "C with classes" functionalities.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 *
 */

#include "pch.h"
#include "SimulationDlg.h"
#include "resource.h"

#pragma region Constructors

IMPLEMENT_DYNAMIC(CSimulationDlg, CDialogEx)

CSimulationDlg::CSimulationDlg(CWnd* pParent)
	: CDialogEx(IDD_DIALOG_SIMULATION, pParent)
{

}

#pragma endregion
#pragma region Overridables

BOOL CSimulationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	BOOL bValue = TRUE;
	DwmSetWindowAttribute(m_hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &bValue, sizeof(BOOL));

	return TRUE;
}

void CSimulationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_REGEX, m_strRegex);
	DDX_Text(pDX, IDC_EDIT_STRING, m_strInput);
	DDX_Control(pDX, IDC_LIST_MATCHES, m_lbMatches);
	DDX_Text(pDX, IDC_EDIT_ERROR, m_strStatus);
}

#pragma endregion
#pragma region Implementations

void CSimulationDlg::RegexMatch()
{
	m_lbMatches.ResetContent();
	m_strStatus.Empty();

	if (!m_strRegex.IsEmpty() && !m_strInput.IsEmpty())
	{
		try
		{
			retro::regex::CRegExp Regex;

			Regex.Compile(m_strRegex.GetString());

			Regex.Match(m_strInput.GetString(), [](LPCTSTR pszMatch, LPVOID pData) -> BOOL
				{
					CListBox* pList = reinterpret_cast<CListBox*>(pData);
					ASSERT_POINTER(pList, CListBox);
					ASSERT_VALID(pList);

					pList->AddString(pszMatch);

					return TRUE;

				}, &m_lbMatches);
		}
		catch (CException* e)
		{
			static constexpr const INT_PTR EXCEPTION_MAX_ERROR_LENGTH = 512;

			LPTSTR pszStatus = m_strStatus.GetBufferSetLength(EXCEPTION_MAX_ERROR_LENGTH);
			e->GetErrorMessage(pszStatus, EXCEPTION_MAX_ERROR_LENGTH, 0);
			m_strStatus.ReleaseBuffer();
			e->Delete();
		}
	}

	UpdateData(FALSE);
}

#pragma endregion
#pragma region Message

BEGIN_MESSAGE_MAP(CSimulationDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_REGEX, &CSimulationDlg::OnEnChangeEditRegex)
	ON_EN_CHANGE(IDC_EDIT_STRING, &CSimulationDlg::OnEnChangeEditString)
END_MESSAGE_MAP()

void CSimulationDlg::OnEnChangeEditRegex()
{
	UpdateData(TRUE);

	RegexMatch();
}

void CSimulationDlg::OnEnChangeEditString()
{
	UpdateData(TRUE);

	RegexMatch();
}

#pragma endregion