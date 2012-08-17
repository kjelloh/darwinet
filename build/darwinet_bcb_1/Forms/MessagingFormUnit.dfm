object MessagingForm: TMessagingForm
  Left = 0
  Top = 0
  Caption = 'Messaging'
  ClientHeight = 388
  ClientWidth = 852
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
  object Label1: TLabel
    Left = 16
    Top = 8
    Width = 55
    Height = 13
    Caption = 'Our IP:Port'
    Enabled = False
  end
  object Label2: TLabel
    Left = 16
    Top = 35
    Width = 65
    Height = 13
    Caption = 'Other IP:Port'
  end
  object OurIPAndPortEdit: TEdit
    Left = 100
    Top = 5
    Width = 121
    Height = 21
    Enabled = False
    TabOrder = 0
    Text = 'OurIPAndPortEdit'
  end
  object OtherIPAndPortEdit: TEdit
    Left = 100
    Top = 32
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'OtherIPAndPortEdit'
  end
  object ToOtherPeerTCPClient: TIdTCPClient
    ConnectTimeout = 0
    IPVersion = Id_IPv4
    Port = 0
    ReadTimeout = -1
    Left = 264
    Top = 8
  end
  object FromOtherPeerTCPServer: TIdTCPServer
    Bindings = <>
    DefaultPort = 0
    Left = 264
    Top = 64
  end
end
