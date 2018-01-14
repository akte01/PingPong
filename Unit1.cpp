//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"
#include "Markup.h"
#include <vector>
#include <string.h>

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x = -8;
int y = -8;
int leftScores = 0;
int rightScores = 0;
int bounceNumber = 0;
int turn = 1;
AnsiString nameToSave = "";
AnsiString scoresToSave = "";

void saveScoresList(AnsiString nameToSave, AnsiString scoresToSave)
{
 ;
}

void endGame (int rightScores, int leftScores)
{
  sndPlaySound("snd/applause.wav",SND_ASYNC);
  Form1 -> ball_Timer -> Enabled = false;

  if (rightScores > leftScores)
  {
    Form1 -> Label1 -> Caption = "Wygrywa gracz " + rightName + "!";
    Form1 -> Label1 -> Visible = true;
    nameToSave = rightName;
    scoresToSave = IntToStr(rightScores);
  }
  else if (rightScores < leftScores)
  {
    Form1 -> Label1 -> Caption = "Wygrywa gracz " + leftName + "!";
    Form1 -> Button1 -> Visible = true;
    nameToSave = leftName;
    scoresToSave = IntToStr(leftScores);
  }
  else
  {
    Form1 -> Label1 -> Caption = "Remis!";
    Form1 -> Label1 -> Visible = true;
  }
  saveScoresList(nameToSave, scoresToSave);
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ball_TimerTimer(TObject *Sender)
{
 ball -> Left += x;
 ball -> Top += y;
 Label2 -> Caption = "Wynik dla " + leftName + ": " + IntToStr(leftScores);
 Label3 -> Caption = "Wynik dla " + rightName + ": " + IntToStr(rightScores);

 // odbij od górnej sciany
  if(ball -> Top - 5 <= background -> Top)
  {
    y = -y;
    sndPlaySound("snd/S27.wav",SND_ASYNC);
  }

  // odbij od dolnej sciany
  if(ball -> Top + ball -> Height >= background -> Top + background -> Height)
  {
    y = -y;
    sndPlaySound("snd/S27.wav",SND_ASYNC);
  }


  if(ball -> Left + ball -> Width <= p_left -> Left + p_left -> Width - 15)
  {
    sndPlaySound("snd/fanfare.wav",SND_ASYNC);
    rightScores++;
    ball_Timer -> Enabled = false;
    ball -> Visible = false;
    Label1 -> Caption = "Punkt dla " + rightName + "!";
    Button1 -> Visible = true;
    Label1 -> Visible = true;
    Label3 -> Caption = "Wynik dla " + rightName + ": " + IntToStr(rightScores);
      if ( turn < 5)
      {
      turn++;
      Label4 -> Caption = "Runda: " + IntToStr(turn);
      }
      else if (turn == 5)
      {
       endGame(rightScores, leftScores);
       Application->ProcessMessages(); Sleep(1000);
       turn = 1;
       Label4 -> Caption = "Runda: " + IntToStr(turn);
       rightScores = 0;
       Label3 -> Caption = "Wynik dla " + rightName + ": " + IntToStr(rightScores);
       leftScores = 0;
       Label2 -> Caption = "Wynik dla " + leftName + ": " + IntToStr(leftScores);
       Button1 -> Caption = "Jeszcze raz?";
       Button1 -> Visible = true;
      }
  }

  else if(ball -> Left >= p_right -> Left)
  {
    sndPlaySound("snd/fanfare.wav",SND_ASYNC);
    leftScores++;
    ball_Timer -> Enabled = false;
    ball -> Visible = false;
    Label1 -> Caption = "Punkt dla " + leftName + "!";
    Label1 -> Visible = true;
    Button1 -> Visible = true;
    Label2 -> Caption = "Wynik dla " + leftName + ": " + IntToStr(leftScores);
      if ( turn < 5)
      {
      turn++;
      Label4 -> Caption = "Runda: " + IntToStr(turn);
      }
      else if (turn == 5)
      {
       endGame(rightScores, leftScores);
       Application->ProcessMessages(); Sleep(3000);
       turn = 1;
       Label4 -> Caption = "Runda: " + IntToStr(turn);
       rightScores = 0;
       Label3 -> Caption = "Wynik dla " + rightName + ": " + IntToStr(rightScores);
       leftScores = 0;
       Label2 -> Caption = "Wynik dla " + leftName + ": " + IntToStr(leftScores);
       Button1 -> Caption = "Jeszcze raz?";
       Button1 -> Visible = true;
      }
  }

  else if (ball -> Top > p_left -> Top + ball -> Height/2 &&
        ball -> Top < p_left -> Top + p_left -> Height &&
        ball -> Left < p_left -> Left + p_left -> Width)
  {
      if ((ball -> Top + ball -> Height/2) - (p_left -> Top + p_left -> Height/2) < 10
         && x < 0)
      {
        x = -x;
        y = 0.9*y;
        sndPlaySound("snd/S27.wav",SND_ASYNC);
      }
       else if (x < 0)
       {
         x = -x;
         sndPlaySound("snd/S27.wav",SND_ASYNC);
       }

       bounceNumber++;
       if (bounceNumber%2 == 0 && bounceNumber != 0)
       {
         x = x*1.2;
         y = y*1.2;
         sndPlaySound("snd/S27.wav",SND_ASYNC);
       }
  }

  else if (ball -> Top > p_right -> Top + ball -> Height/2 &&
        ball -> Top < p_right -> Top + p_right -> Height &&
        ball -> Left + ball -> Width > p_right -> Left)
  {
       if ((ball -> Top + ball -> Height/2) - (p_right -> Top + p_right -> Height/2) < 10
       && x > 0)
       {
         x = -x;
         y = 1.1*y;
         sndPlaySound("snd/S27.wav",SND_ASYNC);
       }
       else if (x > 0)
       {
         x = -x;
         sndPlaySound("snd/S27.wav",SND_ASYNC);
       }

       bounceNumber++;
       if (bounceNumber%2 == 0 && bounceNumber != 0)
       {
         x = x*1.2;
         y = y*1.2;
         sndPlaySound("snd/S27.wav",SND_ASYNC);
       }
  }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::p_left_Timer_downTimer(TObject *Sender)
{
  if (p_left -> Top + p_left -> Height < background -> Height - 10)
  p_left -> Top += 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::p_left_Timer_topTimer(TObject *Sender)
{
    if (p_left -> Top > 10) p_left -> Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (Key == 'A') p_left_Timer_top -> Enabled = true;
   if (Key == 'Z') p_left_Timer_down -> Enabled = true;
   if (Key == VK_UP) p_right_Timer_top -> Enabled = true;
   if (Key == VK_DOWN) p_right_Timer_down -> Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (Key == 'A') p_left_Timer_top -> Enabled = false;
   if (Key == 'Z') p_left_Timer_down -> Enabled = false;
   if (Key == VK_UP) p_right_Timer_top -> Enabled = false;
   if (Key == VK_DOWN) p_right_Timer_down -> Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::p_right_Timer_downTimer(TObject *Sender)
{
   if (p_right -> Top + p_right -> Height < background -> Height - 10)
  p_right -> Top += 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::p_right_Timer_topTimer(TObject *Sender)
{
   if (p_right -> Top > 10) p_right -> Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    if ( turn < 5)
    {
    Button1 -> Caption = "OK";
    ball -> Left = 520;
    ball -> Top = 80;
    ball -> Visible = true;
    x = -8;
    y = -8;
    ball_Timer -> Enabled = true;
    Label1 -> Visible = false;
    Button1 -> Visible = false;
    }
    if (turn == 5)
    {
    ball -> Left = 520;
    ball -> Top = 80;
    ball -> Visible = true;
    x = -8;
    y = -8;
    ball_Timer -> Enabled = true;
    Label1 -> Visible = false;
    Button1 -> Visible = false;
    }
}
//---------------------------------------------------------------------------




void __fastcall TForm1::NowaGra1Click(TObject *Sender)
{
     Form1 -> ball_Timer -> Enabled = false;
    if (Application -> MessageBox("Czy na pewno chcesz rozpocz¹æ grê od nowa?",
        "PotwierdŸ", MB_YESNO | MB_ICONQUESTION) == IDYES)
    {
      turn= 1;
      Form1 -> Label4 -> Caption = "Runda: " + IntToStr(turn);
      rightScores = 0;
      Form1 -> Label3 -> Caption = "Wynik dla " + rightName + ": " + IntToStr(rightScores);
      leftScores = 0;
      Form1 -> Label2 -> Caption = "Wynik dla " + leftName + ": " + IntToStr(leftScores);
      Form1 -> ball -> Left = 520;
      Form1 -> ball -> Top = 80;
      Form1 -> ball -> Visible = true;
      x = -8;
      y = -8;
      Form1 -> ball_Timer -> Enabled = true;
      Form1 -> Label1 -> Visible = false;
      Form1 -> Button1 -> Visible = false;
    }
    else Form1 -> ball_Timer -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Pauza1Click(TObject *Sender)
{
  Form1 -> ball_Timer -> Enabled = false;
  Application -> MessageBox("Wróciæ  do gry?", "Pauza", MB_OK);
  Form1 -> ball_Timer -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zakoczgr1Click(TObject *Sender)
{
  Form1 -> ball_Timer -> Enabled = false;
  if (Application -> MessageBox("Czy na pewno chcesz zakonczæ program?",
        "PotwierdŸ", MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
        Application -> Terminate();
        }
   Form1 -> ball_Timer -> Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Wskazwki1Click(TObject *Sender)
{
   Form1 -> ball_Timer -> Enabled = false;
   Form3 -> Enabled = true;
   Form3 -> Visible = true;
}
//---------------------------------------------------------------------------



