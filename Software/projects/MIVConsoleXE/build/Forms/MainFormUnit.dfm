object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Darwinet MIV Console'
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
        Action = ViewApplicationAction
      end
      object ViewMIV1: TMenuItem
        Action = ViewMIVAction
      end
      object ViewMessaging1: TMenuItem
        Action = ViewMessagingAction
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
    object ViewApplicationAction: TAction
      Category = 'View'
      Caption = 'View Application'
      OnExecute = ViewApplicationActionExecute
    end
    object ViewMIVAction: TAction
      Category = 'View'
      Caption = 'View MIV'
      OnExecute = ViewMIVActionExecute
    end
    object ViewMessagingAction: TAction
      Category = 'View'
      Caption = 'View Messaging'
      OnExecute = ViewMessagingActionExecute
    end
  end
end
