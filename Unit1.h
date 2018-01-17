//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *background;
        TImage *p_right;
        TImage *p_left;
        TImage *ball;
        TTimer *ball_Timer;
        TTimer *p_left_Timer_top;
        TTimer *p_left_Timer_down;
        TTimer *p_right_Timer_top;
        TTimer *p_right_Timer_down;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TButton *Button1;
        TMainMenu *MainMenu1;
        TMenuItem *Gra1;
        TMenuItem *Pomoc1;
        TMenuItem *NowaGra1;
        TMenuItem *Pauza1;
        TMenuItem *Wskazwki1;
        TMenuItem *Tabelawynikw1;
        TMenuItem *Zakoczgr1;
        void __fastcall ball_TimerTimer(TObject *Sender);
        void __fastcall p_left_Timer_downTimer(TObject *Sender);
        void __fastcall p_left_Timer_topTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall p_right_Timer_downTimer(TObject *Sender);
        void __fastcall p_right_Timer_topTimer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall NowaGra1Click(TObject *Sender);
        void __fastcall Pauza1Click(TObject *Sender);
        void __fastcall Zakoczgr1Click(TObject *Sender);
        void __fastcall Wskazwki1Click(TObject *Sender);
        void __fastcall Tabelawynikw1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
