object MIVsViewFrame: TMIVsViewFrame
  Left = 0
  Top = 0
  Width = 261
  Height = 185
  TabOrder = 0
  object myIntLabel: TLabel
    Left = 16
    Top = 20
    Width = 28
    Height = 13
    Caption = 'myInt'
  end
  object myStringLabel: TLabel
    Left = 16
    Top = 48
    Width = 42
    Height = 13
    Caption = 'myString'
  end
  object MyIntSpinEdit: TSpinEdit
    Left = 100
    Top = 17
    Width = 121
    Height = 22
    MaxValue = 0
    MinValue = 0
    TabOrder = 0
    Value = 0
    OnChange = MyIntSpinEditChange
  end
  object MyTextEdit: TEdit
    Left = 100
    Top = 45
    Width = 121
    Height = 21
    TabOrder = 1
    OnChange = MyTextEditChange
  end
  object myIntArrayGroupBox: TGroupBox
    Left = 16
    Top = 72
    Width = 225
    Height = 105
    Caption = 'myIntArray'
    TabOrder = 2
    object myIntArrayxLabel: TLabel
      Left = 11
      Top = 72
      Width = 65
      Height = 13
      Caption = 'myIntArray.x'
    end
    object myIntArrayxSpinEdit: TSpinEdit
      Left = 82
      Top = 71
      Width = 121
      Height = 22
      MaxValue = 0
      MinValue = 0
      TabOrder = 0
      Value = 0
    end
    object myIntArrayListView: TListView
      Left = 82
      Top = 11
      Width = 123
      Height = 54
      Columns = <
        item
          Caption = 'Member'
          MinWidth = 100
        end>
      Items.ItemData = {
        05320000000100000000000000FFFFFFFFFFFFFFFF00000000FFFFFFFF000000
        000C6D00790049006E007400410072007200610079002E003100}
      TabOrder = 1
      ViewStyle = vsList
    end
  end
end
