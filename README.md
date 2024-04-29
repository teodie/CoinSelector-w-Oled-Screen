Goal:
Be able to detect the coins correctly and desplaying it in the oled Screen

Components:
Allan Universal Coin Selector
pesos : pulse
1 : 4 
5 : 5 
10 : 6 
(disturbance in one pulse make false readings)

SSD1306 Oled I2C
10K Resistor

Strugles - solution/workaround
Power Supply Noise - Change to less noise power supply
one pulse Random Noise overtime - Change the default pulse set on the coinselector to avoid the one pulse noise (1pulse -> 4 pulse to detect 1peso coin)
