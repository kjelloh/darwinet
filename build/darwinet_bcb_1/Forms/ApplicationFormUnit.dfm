object ApplicationForm: TApplicationForm
  Left = 0
  Top = 0
  Caption = 'Darwinet Application'
  ClientHeight = 94
  ClientWidth = 344
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object SpinEdit1: TSpinEdit
    Left = 16
    Top = 8
    Width = 121
    Height = 22
    MaxValue = 0
    MinValue = 0
    TabOrder = 0
    Value = 0
    OnChange = SpinEdit1Change
  end
end
