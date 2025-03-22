object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'selection sort'
  ClientHeight = 506
  ClientWidth = 882
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 882
    Height = 506
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    ExplicitWidth = 880
    ExplicitHeight = 498
    object TabSheet1: TTabSheet
      Caption = 'sort and search'
      object Label3: TLabel
        Left = 656
        Top = 40
        Width = 47
        Height = 15
        Caption = 'Target = '
      end
      object Label2: TLabel
        Left = 21
        Top = 40
        Width = 44
        Height = 15
        Align = alCustom
        Caption = 'range = '
      end
      object Label1: TLabel
        Left = 44
        Top = 19
        Width = 21
        Height = 15
        Align = alCustom
        Caption = 'n = '
      end
      object Label8: TLabel
        Left = 230
        Top = 19
        Width = 145
        Height = 15
        Caption = 'CPU time decimal places = '
      end
      object Memo5: TMemo
        Left = 230
        Top = 321
        Width = 180
        Height = 152
        Lines.Strings = (
          'Memo5')
        ScrollBars = ssVertical
        TabOrder = 0
      end
      object Memo4: TMemo
        Left = 656
        Top = 107
        Width = 180
        Height = 152
        Lines.Strings = (
          'Memo4')
        ScrollBars = ssVertical
        TabOrder = 1
      end
      object Memo3: TMemo
        Left = 438
        Top = 107
        Width = 180
        Height = 152
        Lines.Strings = (
          'Memo3')
        ScrollBars = ssVertical
        TabOrder = 2
      end
      object Memo2: TMemo
        Left = 230
        Top = 107
        Width = 180
        Height = 152
        Lines.Strings = (
          'Memo2')
        ScrollBars = ssVertical
        TabOrder = 3
      end
      object Memo1: TMemo
        Left = 21
        Top = 109
        Width = 180
        Height = 152
        Lines.Strings = (
          'Memo1')
        ScrollBars = ssVertical
        TabOrder = 4
      end
      object Edit3: TEdit
        Left = 709
        Top = 37
        Width = 127
        Height = 23
        TabOrder = 5
        Text = '200'
      end
      object Edit2: TEdit
        Left = 71
        Top = 40
        Width = 130
        Height = 23
        Align = alCustom
        TabOrder = 6
        Text = '1000'
      end
      object Edit1: TEdit
        Left = 71
        Top = 11
        Width = 130
        Height = 23
        Align = alCustom
        TabOrder = 7
        Text = '100'
      end
      object CheckBox2: TCheckBox
        Left = 333
        Top = 40
        Width = 97
        Height = 17
        Caption = 'self check'
        TabOrder = 8
      end
      object CheckBox1: TCheckBox
        Left = 230
        Top = 40
        Width = 97
        Height = 17
        Caption = 'echo print'
        TabOrder = 9
      end
      object Button5: TButton
        Left = 230
        Top = 290
        Width = 180
        Height = 25
        Caption = 'Quick Sort'
        TabOrder = 10
        OnClick = Button5Click
      end
      object Button4: TButton
        Left = 656
        Top = 76
        Width = 180
        Height = 25
        Caption = 'Binary Search'
        TabOrder = 11
        OnClick = Button4Click
      end
      object Button3: TButton
        Left = 438
        Top = 76
        Width = 180
        Height = 25
        Caption = 'Bubble Sort'
        TabOrder = 12
        OnClick = Button3Click
      end
      object Button2: TButton
        Left = 230
        Top = 76
        Width = 180
        Height = 25
        Caption = 'Selection Sort'
        TabOrder = 13
        OnClick = Button2Click
      end
      object Button1: TButton
        Left = 21
        Top = 74
        Width = 180
        Height = 29
        Caption = 'Generate Random Numbers'
        TabOrder = 14
        OnClick = Button1Click
      end
      object Edit8: TEdit
        Left = 376
        Top = 16
        Width = 34
        Height = 23
        TabOrder = 15
        Text = '5'
      end
      object Button7: TButton
        Left = 21
        Top = 290
        Width = 180
        Height = 25
        Caption = 'Insertion Sort'
        TabOrder = 16
        OnClick = Button7Click
      end
      object Memo7: TMemo
        Left = 21
        Top = 321
        Width = 180
        Height = 152
        Lines.Strings = (
          'Memo7')
        ScrollBars = ssVertical
        TabOrder = 17
      end
      object Button8: TButton
        Left = 438
        Top = 290
        Width = 180
        Height = 25
        Caption = 'Merge Sort'
        TabOrder = 18
        OnClick = Button8Click
      end
      object Memo8: TMemo
        Left = 438
        Top = 321
        Width = 180
        Height = 152
        Lines.Strings = (
          'Memo8')
        ScrollBars = ssVertical
        TabOrder = 19
      end
      object Button9: TButton
        Left = 656
        Top = 290
        Width = 180
        Height = 25
        Caption = 'Heap Sort'
        TabOrder = 20
        OnClick = Button9Click
      end
      object Memo9: TMemo
        Left = 656
        Top = 321
        Width = 180
        Height = 152
        Lines.Strings = (
          'Memo9')
        ScrollBars = ssVertical
        TabOrder = 21
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'chart of CPU time'
      ImageIndex = 1
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 203
        Height = 476
        Align = alLeft
        TabOrder = 0
        ExplicitHeight = 468
        object Label4: TLabel
          Left = 24
          Top = 12
          Width = 47
          Height = 15
          Caption = 'start n = '
        end
        object Label5: TLabel
          Left = 35
          Top = 67
          Width = 36
          Height = 15
          Caption = 'step = '
        end
        object Label6: TLabel
          Left = 6
          Top = 96
          Width = 65
          Height = 15
          Caption = 'repetition = '
        end
        object Label7: TLabel
          Left = 27
          Top = 38
          Width = 44
          Height = 15
          Caption = 'range = '
        end
        object Button6: TButton
          Left = 6
          Top = 263
          Width = 191
          Height = 25
          Caption = 'Generate CPU Time Chart'
          TabOrder = 0
          OnClick = Button6Click
        end
        object Edit4: TEdit
          Left = 77
          Top = 9
          Width = 68
          Height = 23
          TabOrder = 1
          Text = '10000'
        end
        object Edit5: TEdit
          Left = 77
          Top = 67
          Width = 68
          Height = 23
          TabOrder = 2
          Text = '5000'
        end
        object Edit6: TEdit
          Left = 77
          Top = 96
          Width = 68
          Height = 23
          TabOrder = 3
          Text = '6'
        end
        object Edit7: TEdit
          Left = 77
          Top = 38
          Width = 68
          Height = 23
          TabOrder = 4
          Text = '100000'
        end
        object RadioButton1: TRadioButton
          Left = 2
          Top = 194
          Width = 113
          Height = 17
          Caption = 'line chart'
          TabOrder = 5
        end
        object RadioButton2: TRadioButton
          Left = 2
          Top = 217
          Width = 113
          Height = 17
          Caption = 'bar chart'
          TabOrder = 6
        end
        object RadioButton3: TRadioButton
          Left = 2
          Top = 240
          Width = 99
          Height = 17
          Caption = 'horizontal bar'
          TabOrder = 7
        end
        object Memo6: TMemo
          Left = 6
          Top = 294
          Width = 191
          Height = 171
          Lines.Strings = (
            'Memo6')
          ScrollBars = ssVertical
          TabOrder = 8
        end
        object CheckBox3: TCheckBox
          Left = 107
          Top = 125
          Width = 97
          Height = 17
          Caption = 'Selection Sort'
          TabOrder = 9
        end
        object CheckBox4: TCheckBox
          Left = 107
          Top = 148
          Width = 97
          Height = 17
          Caption = 'Bubble Sort'
          TabOrder = 10
        end
        object CheckBox5: TCheckBox
          Left = 107
          Top = 171
          Width = 97
          Height = 17
          Caption = 'Insertion Sort'
          TabOrder = 11
        end
        object CheckBox6: TCheckBox
          Left = 107
          Top = 194
          Width = 97
          Height = 17
          Caption = 'Merge Sort'
          TabOrder = 12
        end
        object CheckBox7: TCheckBox
          Left = 107
          Top = 217
          Width = 97
          Height = 17
          Caption = 'Quick Sort'
          TabOrder = 13
        end
        object CheckBox8: TCheckBox
          Left = 107
          Top = 240
          Width = 97
          Height = 17
          Caption = 'Heap Sort'
          TabOrder = 14
        end
        object CheckBox9: TCheckBox
          Left = 4
          Top = 125
          Width = 97
          Height = 17
          Caption = 'self check'
          TabOrder = 15
        end
      end
      object Panel2: TPanel
        Left = 203
        Top = 0
        Width = 671
        Height = 476
        Align = alClient
        Caption = 'Panel2'
        TabOrder = 1
        ExplicitWidth = 669
        ExplicitHeight = 468
        object Chart1: TChart
          Left = 1
          Top = 1
          Width = 669
          Height = 474
          ScrollMouseButton = mbLeft
          Title.Text.Strings = (
            'TChart')
          BottomAxis.Title.Caption = 'input size (n)'
          LeftAxis.Title.Caption = 'CPU time (sec.)'
          TopAxis.Title.Caption = 'CPU time under different Sorting Algorithm'
          View3D = False
          View3DOptions.HorizOffset = 87
          View3DOptions.Perspective = 21
          View3DOptions.VertOffset = 87
          View3DOptions.Zoom = 225
          Zoom.MouseButton = mbRight
          Align = alClient
          TabOrder = 0
          ExplicitWidth = 667
          ExplicitHeight = 466
          DefaultCanvas = 'TGDIPlusCanvas'
          ColorPaletteIndex = 13
          object Series1: TLineSeries
            HoverElement = [heCurrent]
            SeriesColor = clRed
            Brush.BackColor = clDefault
            LineHeight = 29
            Pointer.InflateMargins = True
            Pointer.Style = psRectangle
            XValues.Name = 'X'
            XValues.Order = loAscending
            YValues.Name = 'Y'
            YValues.Order = loNone
          end
        end
      end
    end
  end
end
