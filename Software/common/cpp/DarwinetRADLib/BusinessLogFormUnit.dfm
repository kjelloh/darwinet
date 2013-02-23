object BusinessLogForm: TBusinessLogForm
  Left = 0
  Top = 0
  Caption = 'Application internal Log'
  ClientHeight = 294
  ClientWidth = 562
  Color = clBtnFace
  DragKind = dkDock
  DragMode = dmAutomatic
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object LogsPageControl: TPageControl
    Left = 0
    Top = 0
    Width = 562
    Height = 294
    ActivePage = AllTabSheet
    Align = alClient
    TabOrder = 0
    object BusinessTabSheet: TTabSheet
      Caption = 'Business'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object BusinessLogRichEdit: TRichEdit
        Left = 0
        Top = 0
        Width = 554
        Height = 266
        Align = alClient
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Lines.Strings = (
          '<Log to be read by user of the application>')
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
      end
    end
    object DesignInsuffiiciencyTabSheet: TTabSheet
      Caption = 'Design Insufficiency'
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object DesignInsufficiencyLogRichEdit: TRichEdit
        Left = 0
        Top = 0
        Width = 554
        Height = 266
        Align = alClient
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Lines.Strings = (
          
            '<Log to be read by the developer by this application. Entries In' +
            'dicates application insufficiency to handle situations>')
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
      end
    end
    object DevelopmentTraceTabSheet: TTabSheet
      Caption = 'Developer Trace'
      ImageIndex = 3
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object DeveloperLogRichEdit: TRichEdit
        Left = 0
        Top = 0
        Width = 554
        Height = 266
        Align = alClient
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Lines.Strings = (
          '<Trace to be read by the developer of this application>')
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
      end
    end
    object AllTabSheet: TTabSheet
      Caption = 'All'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object AllRichEdit: TRichEdit
        Left = 0
        Top = 0
        Width = 554
        Height = 266
        Align = alClient
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Lines.Strings = (
          '<All log entries are merged into this log>')
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
      end
    end
  end
  object PollLogTimer: TTimer
    OnTimer = PollLogTimerTimer
    Left = 440
    Top = 8
  end
end
