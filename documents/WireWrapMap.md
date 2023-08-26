# WireWrapMap

-- This file is still a stub --

### Chips used in Jelly

  - U1 AT28C16 [at28c16](https://github.com/agsb/jelly/assets/14941647/0e6a42e7-9d13-4c5b-8078-834cc9717078)
  - U2 AT28C16 [at28c16](https://github.com/agsb/jelly/assets/14941647/0e6a42e7-9d13-4c5b-8078-834cc9717078)
  - U3 AT28C26 [at28c16](https://github.com/agsb/jelly/assets/14941647/0e6a42e7-9d13-4c5b-8078-834cc9717078)
  - U4 74HC574 [74hc574](https://github.com/agsb/jelly/assets/14941647/389d5967-7fb1-4645-8b06-98f8ca35686f)
  - U5 74HC574 [74hc574](https://github.com/agsb/jelly/assets/14941647/389d5967-7fb1-4645-8b06-98f8ca35686f)
  - U6 74HC574 [74hc574](https://github.com/agsb/jelly/assets/14941647/389d5967-7fb1-4645-8b06-98f8ca35686f)
  - U7 74HC245 [74hc245](https://github.com/agsb/jelly/assets/14941647/2990746c-01e9-4c97-b71f-3ceca05f751b)
  - U8 74HC393 [74hc393](https://github.com/agsb/jelly/assets/14941647/131a82d1-9269-4ded-93cc-4d0f6053b101)
  - U9  74HC74 [74hc74](https://github.com/agsb/jelly/assets/14941647/7b43e177-1a82-49fd-ad0a-cf376e5011dd)
  - U10 74HC00 [74hc00](https://github.com/agsb/jelly/assets/14941647/2f70cb16-b870-4e8b-bac9-e86a2bcbbb6e)
  - C1 to C10, capacitor 100nF
  - C11 to C14, capacitor 4.7uF 

### Connections for WireWrap

  - POWER, all VCC connect U1.24, U2.24, U3.24, U4.20, U5.20, U6.20, U7.20, U8.14, U9.14, U10.14
  - GROUND, all GND connect U1.12, U2.12, U3.12, U4.10, U5.10, U6.10, U7.10, U8.7, U9.7, U10.7
  - CAPS, (U1.24-C1.1, C1.2-U1.12) for U1 C1 to U10 C10

#### 
	// master FSM eeprom
	U1.01-ZERO
	U1.02-U4.16
	U1.03-U4.17
	U1.04-U4.18
	U1.05-U4.19
	U1.06-U8.11
	U1.07-U8.10
	U1.08-U8.09
	U1.09-
	U1.10-
	U1.11-
	U1.12-GND
	U1.13-
	U1.14-
	U1.15-
	U1.16-
	U1.17-
	U1.18-GND
	U1.19-A10-NC
	U1.20-GND
	U1.21-VCC
	U1.22-A9
	U1.23-A8
	U1.24-VCC


	// master Math/Decode eeprom
	U2.01-U5.12
	U2.02-U5.13
	U2.03-U5.14
	U2.04-U5.15
	U2.05-U5.16
	U2.06-U5.17
	U2.07-U5.18
	U2.08-U5.19
	U2.09-U6.02
	U2.10-U6.03
	U2.11-U6.04
	U2.12-GND
	U2.13-U6.05
	U2.14-U6.06
	U2.15-U6.07
	U2.16-U6.08
	U2.17-U6.09
	U2.18-GND
	U2.19-A10 ???
	U2.20-GND
	U2.21-VCC
	U2.22-A9 ???
	U2.23-A8 ???
	U2.24-VCC


	// control FSM eeprom
	U3.01-ZERO
	U3.02-U1.02
	U3.03-U1.03
	U3.04-U1.04
	U3.05-U1.05
	U3.06-U1.06
	U3.07-U1.07
	U3.08-U1.08
	U3.09-
	U3.10-
	U3.11-
	U3.12-GND
	U3.13-
	U3.14-
	U3.15-
	U3.16-
	U3.17-
	U3.18-GND
	U3.19-A10-NC
	U3.20-GND
	U3.21-VCC
	U3.22-A9 ????
	U3.23-A8 ????
	U3.24-VCC
	
	// code byte latch, only low nibble used
	U4.01-GND
	U4.02-U5.02
	U4.03-U5.03
	U4.04-U5.04
	U4.05-U5.05
	U4.06-U5.06
	U4.07-U5.07
	U4.08-U5.08
	U4.09-U5.09
	U4.10-GND
	U4.11-CLK ????
	U4.12-NC
	U4.13-NC
	U4.14-NC
	U4.15-NC
	U4.16-X
	U4.17-X
	U4.18-X
	U4.19-X
	U4.20-VCC


	// data byte latch, input into Math
	U5.01-GND
	U5.02-U6.19
	U5.03-U6.18
	U5.04-U6.17
	U5.05-U6.16
	U5.06-U6.15
	U5.07-U6.14
	U5.08-U6.13
	U5.09-U6.12
	U5.10-GND
	U5.11-CLK ????
	U5.12-U2.01
	U5.13-U2.02
	U5.14-U2.03
	U5.15-U2.04
	U5.16-U2.05
	U5.17-U2.06
	U5.18-U2.07
	U5.19-U2.08
	U5.20-VCC


	// data byte latch, output from Math
	U6.01-????
	U6.02-U2.19
	U6.03-U2.18
	U6.04-U2.17
	U6.05-U2.16
	U6.06-U2.15
	U6.07-U2.14
	U6.08-U2.13
	U6.09-U2.12
	U6.10-GND
	U6.11-CLK ????
	U6.12-U7.09
	U6.13-U7.08
	U6.14-U7.07
	U6.15-U7.06
	U6.16-U7.05
	U6.17-U7.04
	U6.18-U7.03
	U6.19-U7.02
	U6.20-VCC


	// input output switch
	U7.01-DIR ???
	U7.02-U6.19
	U7.03-U6.18
	U7.04-U6.17
	U7.05-U6.16
	U7.06-U6.15
	U7.07-U6.14
	U7.08-U6.13
	U7.09-U6.12
	U7.10-GND
	U7.11-CONN9
	U7.12-CONN8
	U7.13-CONN6
	U7.14-CONN5
	U7.15-CONN4
	U7.16-CONN3
	U7.17-CONN2
	U7.18-CONN1
	U7.19-OE ????
	U7.20-VCC



	U8.12-U8.08	// counts 0 to 7 and resets.
	U8.13-?????	// whats comes to clear it



	NC-U8.01
	NC-U8.02
	NC-U8.03
	NC-U8.04
	NC-U8.05
	NC-U8.06
