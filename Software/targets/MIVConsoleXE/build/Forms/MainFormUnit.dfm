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
  object LogSplitter: TSplitter
    Left = 0
    Top = 449
    Width = 804
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ExplicitWidth = 85
  end
  object EngineGroupBox: TGroupBox
    Left = 0
    Top = 0
    Width = 804
    Height = 89
    Align = alTop
    Caption = 'Engine'
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
    Caption = 'Engine -> Domain'
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
    Caption = 'Engine -> Domain -> View'
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
  object SEPSIGroupBox: TGroupBox
    Left = 0
    Top = 257
    Width = 804
    Height = 105
    Align = alTop
    Caption = 'Engine -> Domain -> View -> SEPSI'
    TabOrder = 3
    object SEPSIConnectButton: TButton
      Left = 16
      Top = 32
      Width = 75
      Height = 25
      Caption = 'Connect'
      TabOrder = 0
      OnClick = SEPSIConnectButtonClick
    end
  end
  object ValuesEditGroupBox: TGroupBox
    Left = 0
    Top = 362
    Width = 804
    Height = 87
    Align = alTop
    Caption = 'Engine -> Domain -> View -> SEPSI -> Values'
    TabOrder = 4
    object ValuePathLabel: TLabel
      Left = 16
      Top = 40
      Width = 100
      Height = 13
      Caption = 'darwinet.hello_world'
    end
    object IntValueEdit: TCSpinEdit
      Left = 122
      Top = 40
      Width = 121
      Height = 22
      TabOrder = 0
      OnChange = IntValueEditChange
    end
  end
  object LogPanel: TPanel
    Left = 0
    Top = 452
    Width = 804
    Height = 82
    Align = alClient
    Caption = 'Log Frame goes here at run time'
    TabOrder = 5
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
