# Simple_fridge_humidifier

This project is a continuation of the cheese madness that overwhelmed me. How do I get 80% humidity in a wine refrigerator? It is quite a challenge. On cheese forums I read about leaving the dish with brine to increase the humidity, but this is not enough. I got 50% with this method. I bought a small humidator from China and decided to use what I have at home. Arduino, DTH11 (I'm waiting for the BMP280), the mentioned humidator and the 7-segment display on the TM1637 layout. Initially, the program was supposed to run on battery, but after a series of tests, I found that it did not make sense. So I connected a 12v power supply.

Now I have approx. 80% humidity in the fridge and my Cheddar, Emmental and Parmesan mature in the right conditions.

Inside the humidator is the LM317 stabilizer. The obtained 5v powers the sensor, the display and the humidator itself. 12V powers the Arduino.


Simple humidifier for the cheese refrigerator
