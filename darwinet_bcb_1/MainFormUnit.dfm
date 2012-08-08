object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Darwinet 1'
  ClientHeight = 118
  ClientWidth = 337
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object SpinEdit1: TSpinEdit
    Left = 8
    Top = 20
    Width = 121
    Height = 22
    MaxValue = 0
    MinValue = 0
    TabOrder = 0
    Value = 0
    OnChange = SpinEdit1Change
  end
  object MainMenu1: TMainMenu
    Left = 280
    Top = 8
    object File1: TMenuItem
      Caption = 'File'
    end
    object Edit1: TMenuItem
      Caption = 'Edit'
    end
    object Help1: TMenuItem
      Caption = 'Help'
    end
  end
end
