// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#define _USE_MATH_DEFINES

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
// ����� ���������� Windows:
#include <windows.h>

// ����� ���������� C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "stdio.h"

#include <ShlObj.h>
#pragma comment(lib, "Comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define ID_BMXp 3456
#define ID_BMXm 3457
#define ID_BMYp 3458
#define ID_BMYm 3459
#define ID_BMZp 3460
#define ID_BMZm 3461

#define ID_Step 3462
#define ID_Choose 3463
#define ID_Coeff 3464
#define ID_Angle 3465

#define ID_BRXp 3466
#define ID_BRXm 3467
#define ID_BRYp 3468
#define ID_BRYm 3469
#define ID_BRZp 3470
#define ID_BRZm 3471

#define ID_BClear 3472
#define ID_BSave 3473
#define ID_BLoad 3474

#define ID_BCube 3475
#define ID_BZigZag 3476
#define ID_BLine 3477
#define ID_Btblock 3478

#define ID_BCamRotHorL 3479
#define ID_BCamRotHorR 3480
#define ID_BCamRotVerU 3481
#define ID_BCamRotVerD 3482

#define ID_BColModel 3483
#define ID_BColGround 3484

#define ID_BCoeff 3485

#define ID_BDel 3486

#define ID_Xcam 3487
#define ID_Ycam 3488
#define ID_Zcam 3489
#define ID_BLight 3490

#define ID_BG 3491
#define ID_BCross 3492


// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������
