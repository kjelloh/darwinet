object EditPropertiesForm: TEditPropertiesForm
  Left = 0
  Top = 0
  ClientHeight = 605
  ClientWidth = 562
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object BottomPanel: TPanel
    Left = 0
    Top = 544
    Width = 562
    Height = 61
    Align = alBottom
    TabOrder = 0
    DesignSize = (
      562
      61)
    object OKButton: TButton
      Left = 168
      Top = 22
      Width = 75
      Height = 25
      Caption = 'OK'
      TabOrder = 0
      OnClick = OKButtonClick
    end
    object CancelButton: TButton
      Left = 288
      Top = 22
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Cancel'
      TabOrder = 1
      OnClick = CancelButtonClick
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 562
    Height = 544
    Align = alClient
    Caption = 'Property editor frame goes here in run time'
    TabOrder = 1
  end
  object OpenDialog1: TOpenDialog
    Left = 480
    Top = 64
  end
end
