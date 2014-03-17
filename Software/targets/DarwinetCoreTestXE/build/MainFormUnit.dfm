object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Darwinet Core Test'
  ClientHeight = 388
  ClientWidth = 852
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 232
    Width = 852
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 0
    ExplicitWidth = 388
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 235
    Width = 852
    Height = 153
    Align = alBottom
    Caption = 'Business log goes here at run-time'
    TabOrder = 0
    ExplicitTop = 232
  end
  object GridPanel1: TGridPanel
    Left = 0
    Top = 0
    Width = 852
    Height = 232
    Align = alClient
    Caption = 'MIVs views goes here at run-time'
    ColumnCollection = <
      item
        Value = 50.000000000000000000
      end
      item
        Value = 50.000000000000000000
      end>
    ControlCollection = <>
    RowCollection = <
      item
        Value = 50.000000000000000000
      end
      item
        Value = 50.000000000000000000
      end>
    TabOrder = 1
    ExplicitLeft = 336
    ExplicitTop = 112
    ExplicitWidth = 185
    ExplicitHeight = 41
  end
end
