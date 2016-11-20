
#include "stdafx.h"
#include "Planner.h"
#include "Interface.h"
#include "Model.h"

//
//  ‘”Ќ ÷»я: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ќј«Ќј„≈Ќ»≈:  обрабатывает сообщени€ в главном окне.
//
//  WM_COMMAND Ч обработать меню приложени€
//  WM_PAINT Ч отрисовать главное окно
//  WM_DESTROY Ч отправить сообщение о выходе и вернутьс€
//
//

extern HINSTANCE hInst;
Model MyModel;
Model MyModel2;
float DeltaMove = 30;
float DeltaRotate = 10;
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

		Button ButMoveXp(TEXT("Move OX+"), 10, 140, 25, 80, ID_BMXp);
		Button ButMoveXm(TEXT("Move OX-"), 100, 140, 25, 80, ID_BMXm);

		Button ButMoveYp(TEXT("Move OY+"), 10, 180, 25, 80, ID_BMYp);
		Button ButMoveYm(TEXT("Move OY-"), 100, 180, 25, 80, ID_BMYm);

		Button ButMoveZp(TEXT("Move OZ+"), 10, 220, 25, 80, ID_BMZp);
		Button ButMoveZm(TEXT("Move OZ-"), 100, 220, 25, 80, ID_BMZm);

		Label LabScale(TEXT("Scaling"), 55, 260, 25, 80);

		Label LabCoefficient(TEXT("Coefficient"), 10, 300, 25, 80);
		Edit EdCoefficient(TEXT(""), 100, 300, 25, 80, ID_Coeff);

		Label LabRotate(TEXT("Rotation"), 55, 340, 25, 80);

		Label LabAngle(TEXT("Angle"), 10, 380, 25, 80);
		Edit EdAngle(TEXT(""), 100, 380, 25, 80, ID_Angle);

		Button ButRotateXp(TEXT("Rotate OX+"), 10, 420, 25, 80, ID_BRXp);
		Button ButRotateXm(TEXT("Rotate OX-"), 100, 420, 25, 80, ID_BRXm);

		Button ButRotateYp(TEXT("Rotate OY+"), 10, 460, 25, 80, ID_BRYp);
		Button ButRotateYm(TEXT("Rotate OY-"), 100, 460, 25, 80, ID_BRYm);

		Button ButRotateZp(TEXT("Rotate OZ+"), 10, 500, 25, 80, ID_BRZp);
		Button ButRotateZm(TEXT("Rotate OZ-"), 100, 500, 25, 80, ID_BRZm);

		Label LabCamera(TEXT("Camera options"), 740, 10, 25, 120);

		Button ButClear(TEXT("Clear"), 840, 400, 25, 80, ID_BClear);
		Button ButSave(TEXT("Save"), 840, 450, 25, 80, ID_BSave);
		Button ButLoad(TEXT("Load"), 840, 500, 25, 80, ID_BLoad);

		Button ButCube(TEXT("Cube"), 200, 505, 25, 80, ID_BCube);
		Button ButZigZag(TEXT("Zigzag"), 280, 505, 25, 80, ID_BZigZag);
		Button ButLine(TEXT("line"), 360, 505, 25, 80, ID_BLine);
		Button Buttblock(TEXT("T-Block"), 440, 505, 25, 80, ID_Btblock);

		Button ButCamRotateHorL(TEXT("Rotate Left"), 705, 100, 25, 105, ID_BCamRotHorL);
		Button ButCamRotateHorR(TEXT("Rotate Right"), 820, 100, 25, 105, ID_BCamRotHorR);
		Button ButCamRotateVerU(TEXT("Rotate Up"), 705, 150, 25, 105, ID_BCamRotVerU);
		Button ButCamRotateVerD(TEXT("Rotate Down"), 820, 150, 25, 105, ID_BCamRotVerD);

		
	}
	break;
	//case WM_KEYDOWN:
	case WM_COMMAND:
	{
		//SetFocus(hWnd);
		int wmId = LOWORD(wParam);
		// –азобрать выбор в меню:
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
				MyScene.MyModels[ModelNum].MoveZ(DeltaMove);
				MyScene.DrawScene();
			}
			break;
		case ID_BMZm:
			if (ModelNum <= MyScene.MyModels.size() - 1)
			{
				MyScene.MyModels[ModelNum].MoveZ(-DeltaMove);
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
				if (wcslen(Buf) == 0)
					ModelNum = 0;
				else
				    ModelNum = _wtoi(Buf)-1;
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
			MyScene.cam->rotateHorizontalSphere(-10*M_PI/180);
			MyScene.DrawScene();
		}
		break;
		case ID_BCamRotHorR:
		{
			MyScene.cam->rotateHorizontalSphere(10 * M_PI / 180);
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

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ƒобавьте сюда любой код прорисовки, использующий HDC...
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