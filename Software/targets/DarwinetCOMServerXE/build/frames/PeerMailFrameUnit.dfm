object PeerMailFrame: TPeerMailFrame
  Left = 0
  Top = 0
  Width = 320
  Height = 240
  TabOrder = 0
  object IdSMTP1: TIdSMTP
    OnStatus = IdSMTP1Status
    AuthType = satSASL
    SASLMechanisms = <
      item
        SASL = IdSMTPSASLLogin1
      end>
    Left = 224
    Top = 40
  end
  object IdMessage1: TIdMessage
    AttachmentEncoding = 'UUE'
    BccList = <>
    CCList = <>
    Encoding = meDefault
    FromList = <
      item
      end>
    Recipients = <
      item
        Address = 'darwinet2@itfied.se'
        Text = 'darwinet2@itfied.se'
        Domain = 'itfied.se'
        User = 'darwinet2'
      end>
    ReplyTo = <>
    ConvertPreamble = True
    Left = 168
    Top = 40
  end
  object IdSMTPSASLLogin1: TIdSASLLogin
    UserPassProvider = Darwinet2IdUserPassProvider
    Left = 224
    Top = 96
  end
  object Darwinet2IdUserPassProvider: TIdUserPassProvider
    Username = 'darwinet2@itfied.se'
    Password = 'darw1n3t2'
    Left = 216
    Top = 152
  end
end
