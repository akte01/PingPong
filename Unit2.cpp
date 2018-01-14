//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
AnsiString leftName = "";
AnsiString rightName = "";

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
   leftName = Form2 -> Edit1 -> Text;
   rightName = Form2 -> Edit2 -> Text;
   Form1 -> Visible = true;
   Form1 -> Enabled = true;
   Form1 -> ball_Timer -> Enabled = true;
   Form2 -> Visible = false;
   Form2 -> Enabled = false;
}
//---------------------------------------------------------------------------

