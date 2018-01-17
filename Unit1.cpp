//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"
#include "Markup.h"
#include <vector>
#include <string.h>
#include <algorithm>

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
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
//---------------------------------------------------------------------------
class Player
{
  public:
  std:: string name;
  std:: string scores;
  Player(std:: string name, std:: string scores);
};
//---------------------------------------------------------------------------
Player::Player(std::string name, std::string scores)
{
    this -> name = name;
    this -> scores = scores;
}

std:: vector <Player> players;
//---------------------------------------------------------------------------
void importScoresList(std:: vector <Player> &players)
{
    std:: string name;
    std:: string scores;
    CMarkup xml;
    xml.Load("scores.xml");
    xml.ResetPos();
    while ( xml.FindElem("Player") )
    {
        xml.IntoElem();
        xml.FindElem( "Name" );
        name = xml.GetData();
        xml.FindElem( "Scores" );
        scores = xml.GetData();
        players.push_back(Player(name, scores));
        xml.OutOfElem();
     }
}
//---------------------------------------------------------------------------
void sortScoresList(std:: vector <Player> &players, std::vector <Player> &sortedPlayers)
{
  int maxScorePosition;
  std::vector <int> scores;
  for (int i = 0; i < players.size(); i++)
    {
        scores.push_back(atoi(players[i].scores.c_str()));
    }

  while (scores.size() > 0)
    {
        maxScorePosition = std::max_element(scores.begin(), scores.end()) - scores.begin();
        sortedPlayers.push_back(Player(players[maxScorePosition].name, players[maxScorePosition].scores));
        scores.erase(scores.begin() + maxScorePosition);
        players.erase(players.begin() + maxScorePosition);
    }
}
//---------------------------------------------------------------------------
void saveScoresList(AnsiString nameToSave, AnsiString scoresToSave)
{
    CMarkup xml;
    xml.Load("scores.xml");
    xml.AddElem("Player");
    xml.IntoElem();
    xml.AddElem("Name", nameToSave.c_str());
    xml.AddElem("Scores", scoresToSave.c_str());
    xml.OutOfElem();
    xml.Save("scores.xml");
}
//---------------------------------------------------------------------------
void showScores()
{
   std::vector <Player> sortedPlayers;
   importScoresList(players);
   sortScoresList(players, sortedPlayers);
   AnsiString name1 = sortedPlayers[0].name.c_str();
   AnsiString score1 = sortedPlayers[0].scores.c_str();
   AnsiString name2 = sortedPlayers[1].name.c_str();
   AnsiString score2 = sortedPlayers[1].scores.c_str();
   AnsiString name3 = sortedPlayers[2].name.c_str();
   AnsiString score3 = sortedPlayers[2].scores.c_str();
   AnsiString name4 = sortedPlayers[3].name.c_str();
   AnsiString score4 = sortedPlayers[3].scores.c_str();
   AnsiString name5 = sortedPlayers[4].name.c_str();
   AnsiString score5 = sortedPlayers[4].scores.c_str();
   Form4 ->Label1->Caption = "LISTA NAJLEPSZYCH WYNIKÓW";
   Form4 ->Label2->Caption = "1. " + name1 + "................................" + score1;
   Form4 ->Label3->Caption = "2. " + name2 + "................................" + score2;
   Form4 ->Label4->Caption = "3. " + name3 + "................................" + score3;
   Form4 ->Label5->Caption = "4. " + name4 + "................................" + score4;
   Form4 ->Label6->Caption = "5. " + name5 + "................................" + score5;
}
//---------------------------------------------------------------------------
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
  showScores();
  Form4 -> Visible = true;

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
        y = 0.9*y + 0.5;
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
         y = 1.1*y + 0.5;
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

void __fastcall TForm1::Tabelawynikw1Click(TObject *Sender)
{
   showScores();
   Form4 -> Visible = true;
}
//---------------------------------------------------------------------------


