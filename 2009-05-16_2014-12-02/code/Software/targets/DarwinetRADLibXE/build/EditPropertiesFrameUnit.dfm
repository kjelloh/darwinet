object EditApplicationPropertiesFrame: TEditApplicationPropertiesFrame
  Left = 0
  Top = 0
  Width = 320
  Height = 240
  TabOrder = 0
  object ValueListEditor1: TValueListEditor
    Left = 0
    Top = 0
    Width = 320
    Height = 240
    Align = alClient
    TabOrder = 0
    OnEditButtonClick = ValueListEditor1EditButtonClick
    OnGetPickList = ValueListEditor1GetPickList
    OnValidate = ValueListEditor1Validate
    ColWidths = (
      150
      164)
  end
  object OpenDialog1: TOpenDialog
    Left = 272
    Top = 64
  end
end
