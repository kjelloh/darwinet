object MIVsViewFrame: TMIVsViewFrame
  Left = 0
  Top = 0
  Width = 152
  Height = 86
  TabOrder = 0
  object MyIntSpinEdit: TSpinEdit
    Left = 12
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
    Left = 12
    Top = 45
    Width = 121
    Height = 21
    TabOrder = 1
    OnChange = MyTextEditChange
  end
end
