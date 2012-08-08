object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Darwinet 1'
  ClientHeight = 458
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
  object Label1: TLabel
    Left = 8
    Top = 16
    Width = 229
    Height = 22
    Caption = 'Test of two Darwninet nodes'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -18
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 8
    Top = 44
    Width = 73
    Height = 39
    Caption = 'Node'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 8
    Top = 89
    Width = 64
    Height = 39
    Caption = 'User'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object TimeAccountListView: TListView
    Left = 8
    Top = 144
    Width = 233
    Height = 249
    Columns = <
      item
        Caption = 'Entry Time'
      end
      item
        Caption = 'Entered Time'
      end>
    TabOrder = 0
    ViewStyle = vsReport
  end
  object TotalTimeEdit: TEdit
    Left = 135
    Top = 399
    Width = 106
    Height = 21
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    Text = '0'
  end
  object ReportTimeEdit: TEdit
    Left = 8
    Top = 429
    Width = 106
    Height = 21
    TabOrder = 2
    Text = '1'
  end
  object Button1: TButton
    Left = 135
    Top = 425
    Width = 108
    Height = 25
    Caption = 'Report'
    TabOrder = 3
  end
  object NodeComboBox: TComboBox
    Left = 87
    Top = 44
    Width = 156
    Height = 47
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    Text = 'NodeComboBox'
    OnChange = NodeComboBoxChange
  end
  object UserComboBox: TComboBox
    Left = 87
    Top = 91
    Width = 156
    Height = 47
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    Text = 'ComboBox1'
  end
  object MainMenu1: TMainMenu
    Left = 248
    Top = 8
    object File1: TMenuItem
      Caption = 'File'
    end
    object Edit1: TMenuItem
      Caption = 'Edit'
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object About1: TMenuItem
        Caption = 'Help'
      end
    end
  end
  object IdSMTP1: TIdSMTP
    OnDisconnected = IdSMTP1Disconnected
    Host = 'mail1.comhem.se'
    SASLMechanisms = <>
    Left = 248
    Top = 104
  end
  object IdPOP31: TIdPOP3
    OnDisconnected = IdPOP31Disconnected
    AutoLogin = True
    SASLMechanisms = <>
    Left = 248
    Top = 72
  end
end
