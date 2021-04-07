# exam1

I/O:
用PA_4作為AnalogOut，PB_1作為AnalogIn，PA_7作為調高頻率的button，PA_6作為調低頻率的button，PA_2作為確認調整頻率的button，USER_BUTTON作為傳送DACdata回PC端的button。
button 都使用InteruptIn。

Display:
顯示不同rate在螢幕上。

Generate waveform:
利用for loops每5毫秒改變一次AnalogOut，根據rate和上升或下降每次改變的大小會不同。

Measure:
用picoscope測量的結果在圖中。

Sample:
總共sample 128個資料點，每10毫秒sample一次，利用變數s，每5毫秒變換一次，當s=1時就會sample。
按下USER_BUTTON後，會把data送回PC端。

Analysis:
sample interval=840us
從/dev/ttyACM0抓取振幅的資料，經過FFT後，分別輸出結果。
