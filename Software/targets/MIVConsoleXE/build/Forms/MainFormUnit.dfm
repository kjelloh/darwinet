object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Darwinet MIV Console'
  ClientHeight = 534
  ClientWidth = 804
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
  object EngineGroupBox: TGroupBox
    Left = 0
    Top = 0
    Width = 804
    Height = 89
    Align = alTop
    Caption = 'Darwinet Engine'
    TabOrder = 0
    object EngineConnectButton: TButton
      Left = 16
      Top = 32
      Width = 75
      Height = 25
      Caption = 'Connect'
      TabOrder = 0
      OnClick = EngineConnectButtonClick
    end
  end
  object DomainGroupBox: TGroupBox
    Left = 0
    Top = 89
    Width = 804
    Height = 88
    Align = alTop
    Caption = 'Darwinet Domain'
    TabOrder = 1
    object DomainConnectButton: TButton
      Left = 16
      Top = 32
      Width = 75
      Height = 25
      Caption = 'Connect'
      TabOrder = 0
      OnClick = DomainConnectButtonClick
    end
  end
  object View: TGroupBox
    Left = 0
    Top = 177
    Width = 804
    Height = 80
    Align = alTop
    Caption = 'Domain View'
    TabOrder = 2
    object ViewConnectButton: TButton
      Left = 16
      Top = 32
      Width = 75
      Height = 25
      Caption = 'Connect'
      TabOrder = 0
      OnClick = ViewConnectButtonClick
    end
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
    object View1: TMenuItem
      Caption = 'View'
      object ViewApplication1: TMenuItem
        Caption = 'View Application'
      end
      object ViewMIV1: TMenuItem
        Caption = 'View MIV'
      end
      object ViewMessaging1: TMenuItem
        Caption = 'View Messaging'
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
    end
  end
  object ActionManager1: TActionManager
    Left = 216
    Top = 8
    StyleName = 'Platform Default'
  end
end
