; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CM3Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "m3.h"

ClassCount=3
Class1=CM3App
Class2=CM3Dlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_M3_DIALOG

[CLS:CM3App]
Type=0
HeaderFile=m3.h
ImplementationFile=m3.cpp
Filter=N

[CLS:CM3Dlg]
Type=0
HeaderFile=m3Dlg.h
ImplementationFile=m3Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=TextView

[CLS:CAboutDlg]
Type=0
HeaderFile=m3Dlg.h
ImplementationFile=m3Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_M3_DIALOG]
Type=1
Class=CM3Dlg
ControlCount=5
Control1=IDCANCEL,button,1342242816
Control2=IDC_EDIT1,edit,1350631552
Control3=send,button,1342242816
Control4=TextView,edit,1353783300
Control5=IDC_STATIC,static,1342308352

