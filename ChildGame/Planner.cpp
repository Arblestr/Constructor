
#include "stdafx.h"
#include "Planner.h"
#include "Interface.h"
#include "Model.h"
#include <Windows.h>
#include <commdlg.h>

extern HINSTANCE hInst;
Model MyModel;
Model MyModel2;
float DeltaMove = 40;
float DeltaCoeff = 1;
float DeltaRotate = 90;
int ModelNum = 0;




LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Scene MyScene(hWnd, 200, 10, 500, 490);
	switch (message)
	{
	case WM_CREATE:
	{
		Inter MainInter(hWnd, hInst);

		Label LabChoose(TEXT("Object Number"), 10, 20, 25, 115);
		Edit EdChoose(TEXT(""), 130, 20, 25, 50, ID_Choose);

		Label LabMove(TEXT("Moving"), 55, 60, 25, 80);

		Label LabStep(TEXT("Step"), 10, 100, 25, 80);
		Edit EdStep(TEXT(""), 100, 100, 25, 80, ID_Step);
		SetDlgItemText(hWnd, ID_Step, L"40");

		Button ButMoveXp(TEXT("Move OX+"), 10, 140, 25, 80, ID_BMXp);
		Button ButMoveXm(TEXT("Move OX-"), 100, 140, 25, 80, ID_BMXm);

		Button ButMoveYp(TEXT("Move OY+"), 10, 180, 25, 80, ID_BMYp);
		Button ButMoveYm(TEXT("Move OY-"), 100, 180, 25, 80, ID_BMYm);

		Button ButMoveZp(TEXT("Move OZ+"), 10, 220, 25, 80, ID_BMZp);
		Button ButMoveZm(TEXT("Move OZ-"), 100, 220, 25, 80, ID_BMZm);

		Label LabScale(TEXT("Scaling"), 55, 260, 25, 80);

		Label LabCoefficient(TEXT("Coefficient"), 10, 300, 25, 80);
		Edit EdCoefficient(TEXT(""), 100, 300, 25, 30, ID_Coeff);
		SetDlgItemText(hWnd, ID_Coeff, L"1");
		Button ButCoeff(TEXT("OK"), 150, 300, 25, 30, ID_BCoeff);

		Label LabRotate(TEXT("Rotation"), 55, 340, 25, 80);

		Label LabAngle(TEXT("Angle"), 10, 380, 25, 80);
		Edit EdAngle(TEXT(""), 100, 380, 25, 80, ID_Angle);
		SetDlgItemText(hWnd, ID_Angle, L"90");

		Button ButRotateXp(TEXT("Rotate OX+"), 10, 420, 25, 80, ID_BRXp);
		Button ButRotateXm(TEXT("Rotate OX-"), 100, 420, 25, 80, ID_BRXm);

		Button ButRotateYp(TEXT("Rotate OY+"), 10, 460, 25, 80, ID_BRYp);
		Button ButRotateYm(TEXT("Rotate OY-"), 100, 460, 25, 80, ID_BRYm);

		Button ButRotateZp(TEXT("Rotate OZ+"), 10, 500, 25, 80, ID_BRZp);
		Button ButRotateZm(TEXT("Rotate OZ-"), 100, 500, 25, 80, ID_BRZm);

		Label LabCamera(TEXT("Camera options"), 755, 10, 25, 120);

		Button ButClear(TEXT("Clear"), 780, 350, 25, 80, ID_BClear);
		Button ButSave(TEXT("Save"), 780, 400, 25, 80, ID_BSave);
		Button ButLoad(TEXT("Load"), 780, 450, 25, 80, ID_BLoad);
		Button ButDel(TEXT("Delete"), 780, 500, 25, 80, ID_BDel);

		Button ButCube(TEXT("Cube"), 200, 505, 25, 80, ID_BCube);
		Button ButZigZag(TEXT("Zigzag"), 280, 505, 25, 80, ID_BZigZag);
		Button ButLine(TEXT("line"), 360, 505, 25, 80, ID_BLine);
		Button Buttblock(TEXT("T-Block"), 440, 505, 25, 80, ID_Btblock);

		Button ButCamRotateHorL(TEXT("Rotate Left"), 705, 70, 25, 105, ID_BCamRotHorL);
		Button ButCamRotateHorR(TEXT("Rotate Right"), 820, 70, 25, 105, ID_BCamRotHorR);
		Button ButCamRotateVerU(TEXT("Rotate Up"), 705, 120, 25, 105, ID_BCamRotVerU);
		Button ButCamRotateVerD(TEXT("Rotate Down"), 820, 120, 25, 105, ID_BCamRotVerD);

		Label LabColors(TEXT("Colors"), 755, 180, 25, 125);
		Button ButColModel(TEXT("Model Color"), 755, 220, 25, 125, ID_BColModel);
		Button ButColGround(TEXT("Background Color"), 755, 260, 25, 125, ID_BColGround);

		
	}
	break;
	//case WM_KEYDOWN:
	case WM_COMMAND:
	{
		//SetFocus(hWnd);
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case ID_BMXp:
			if (ModelNum <= MyScene.MyModels.size() - 1)
			{
				MyScene.MyModels[ModelNum].MoveX(DeltaMove);
				MyScene.DrawScene();
			}
			break;
		case ID_BMXm:
			if (ModelNum <= MyScene.MyModels.size() - 1)
			{
				MyScene.MyModels[ModelNum].MoveX(-DeltaMove);
				MyScene.DrawScene();
			}
			break;
		case ID_BMYp:
			if (ModelNum <= MyScene.MyModels.size() - 1)
			{
				MyScene.MyModels[ModelNum].MoveY(-DeltaMove);
				MyScene.DrawScene();
			}
			break;
		case ID_BMYm:
			if (ModelNum <= MyScene.MyModels.size() - 1)
			{
				MyScene.MyModels[ModelNum].MoveY(DeltaMove);
				MyScene.DrawScene();
			}
			break;
		case ID_BMZp:
			if (ModelNum <= MyScene.MyModels.size() - 1)
			{
				MyScene.MyModels[ModelNum].MoveZ(-DeltaMove);
				MyScene.DrawScene();
			}
			break;
		case ID_BMZm:
			if (ModelNum <= MyScene.MyModels.size() - 1)
			{
				MyScene.MyModels[ModelNum].MoveZ(DeltaMove);
				MyScene.DrawScene();
			}
			break;
		case ID_BRXp:
			if (ModelNum <= MyScene.MyModels.size() - 1)
			{
				MyScene.MyModels[ModelNum].RotateX(DeltaRotate);
				MyScene.DrawScene();
			}
			break;
		case ID_BRYp:
			if (ModelNum <= MyScene.MyModels.size() - 1)
			{
				MyScene.MyModels[ModelNum].RotateY(DeltaRotate);
				MyScene.DrawScene();
			}
			break;
		case ID_BRZp:
			if (ModelNum <= MyScene.MyModels.size() - 1)
			{
				MyScene.MyModels[ModelNum].RotateZ(DeltaRotate);
				MyScene.DrawScene();
			}
			break;
		case ID_BRXm:
			if (ModelNum <= MyScene.MyModels.size() - 1)
			{
				MyScene.MyModels[ModelNum].RotateX(-DeltaRotate);
				MyScene.DrawScene();
			}
			break;
		case ID_BRYm:
			if (ModelNum <= MyScene.MyModels.size() - 1)
			{
				MyScene.MyModels[ModelNum].RotateY(-DeltaRotate);
				MyScene.DrawScene();
			}
			break;
		case ID_BRZm:
			if (ModelNum <= MyScene.MyModels.size() - 1)
			{
				MyScene.MyModels[ModelNum].RotateZ(-DeltaRotate);
				MyScene.DrawScene();
			}
			break;
		case ID_BClear:
			MyScene.Clear();
			MyScene.DrawScene();
			break;
		case ID_Choose:
			if (HIWORD(wParam) == EN_CHANGE)
			{
				TCHAR Buf[4];
				HWND Edit = GetDlgItem(hWnd, ID_Choose);
				GetWindowText(Edit, Buf, 4);
				if (_wtoi(Buf)>MyScene.MyModels.size())
				{
					MessageBox(hWnd, L"There is no model\nwith such number", L"Attention!", MB_OK);
				}
				else
				{
					ModelNum = _wtoi(Buf) - 1;				
				}
			}
			break;
		case ID_Angle:
			if (HIWORD(wParam) == EN_CHANGE)
			{
				TCHAR Buf[4];
				HWND Edit = GetDlgItem(hWnd, ID_Angle);
				GetWindowText(Edit, Buf, 4);
				if (_wtoi(Buf)>360 || _wtoi(Buf)<0)
				{
					MessageBox(hWnd, L"Please, enter the value\n     of angle between\n           0 and 360", L"Attention!", MB_OK);
				}
				else
				{
					DeltaRotate = _wtof(Buf);
				}
			}
			break;
		case ID_Step:
			if (HIWORD(wParam) == EN_CHANGE)
			{
				TCHAR Buf[4];
				HWND Edit = GetDlgItem(hWnd, ID_Step);
				GetWindowText(Edit, Buf, 4);
				if (_wtoi(Buf) < 0)
				{
					MessageBox(hWnd, L"Please, enter the value\n     of Step > 0", L"Attention!", MB_OK);
				}
				else
				{
					DeltaMove = _wtof(Buf);
				}
			}
			break;
		case ID_Coeff:
			if (HIWORD(wParam) == EN_CHANGE)
			{
				TCHAR Buf[4];
				HWND Edit = GetDlgItem(hWnd, ID_Coeff);
				GetWindowText(Edit, Buf, 4);
				if (_wtoi(Buf) < 0)
				{
					MessageBox(hWnd, L"Please, enter the value\n     of Coefficient > 0", L"Attention!", MB_OK);
				}
				else
				{
					DeltaCoeff = _wtof(Buf);
				}
			}
			break;
		case ID_BCoeff:
		{
			for (int i = 0; i < MyScene.MyModels[ModelNum].NodesNum; i++)
			{
				MyScene.MyModels[ModelNum].Nodes[i].X *= DeltaCoeff;
				MyScene.MyModels[ModelNum].Nodes[i].Y *= DeltaCoeff;
				MyScene.MyModels[ModelNum].Nodes[i].Z *= DeltaCoeff;
			}
			MyScene.DrawScene();
		}
		break;
		case ID_BCube:
		{
			MyModel.LoadFromFile("Cube.txt");
			MyScene.AddModel(MyModel);
			MyScene.DrawScene();
			MyModel.ClearModel();
		}
		break;
		case ID_BZigZag:
		{
			MyModel.LoadFromFile("zigzag.txt");
			MyScene.AddModel(MyModel);
			MyScene.DrawScene();
			MyModel.ClearModel();
		}
		break;
		case ID_BLine:
		{
			MyModel.LoadFromFile("line.txt");
			MyScene.AddModel(MyModel);
			MyScene.DrawScene();
			MyModel.ClearModel();
		}
		break;
		case ID_Btblock:
		{
			MyModel.LoadFromFile("tblock.txt");
			MyScene.AddModel(MyModel);
			MyScene.DrawScene();
			MyModel.ClearModel();
		}
		break;
		case ID_BCamRotHorL:
		{	
			MyScene.cam->rotateHorizontalSphere(10*M_PI/180);
			MyScene.DrawScene();
		}
		break;
		case ID_BCamRotHorR:
		{
			MyScene.cam->rotateHorizontalSphere(-10 * M_PI / 180);
			MyScene.DrawScene();
		}
		break;
		case ID_BCamRotVerU:
		{
			MyScene.cam->rotateVerticalSphere(10 * M_PI / 180);
			MyScene.DrawScene();
		}
		break;
		case ID_BCamRotVerD:
		{
			MyScene.cam->rotateVerticalSphere(-10 * M_PI / 180);
			MyScene.DrawScene();
		}
		break;

		case ID_BColModel:
		{
			DWORD cust_bcolors[3] = { 255,222,222 };
			CHOOSECOLOR but_color;
			but_color.Flags = CC_RGBINIT | CC_FULLOPEN;
			but_color.hwndOwner = hWnd;
			but_color.lCustData = 0L;
			but_color.lpCustColors = cust_bcolors;
			but_color.lStructSize = sizeof(CHOOSECOLOR);
			but_color.rgbResult = RGB(255, 0, 0);
			if (ChooseColor(&but_color))
			{
				MyScene.MyModels[ModelNum].Color = (COLORREF)but_color.rgbResult;
				MyScene.DrawScene();
			}
		}
		break;

		case ID_BColGround:
		{
			DWORD cust_gcolors[3] = { 255,222,222 };
			CHOOSECOLOR gr_color;
			gr_color.Flags = CC_RGBINIT | CC_FULLOPEN;
			gr_color.hwndOwner = hWnd;
			gr_color.lCustData = 0L;
			gr_color.lpCustColors = cust_gcolors;
			gr_color.lStructSize = sizeof(CHOOSECOLOR);
			gr_color.rgbResult = RGB(255, 0, 0);
			if (ChooseColor(&gr_color))
			{
				MyScene.color = (COLORREF)gr_color.rgbResult;
				MyScene.DrawScene();
			}
		}
		break;

		case ID_BDel:
		{
			MyScene.MyModels.erase(MyScene.MyModels.begin()+ModelNum);
			MyScene.DrawScene();
		}
		break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		MyScene.DrawScene();
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}