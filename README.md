# Mallar för robochallenge

1. Installera Arduino IDE: https://www.arduino.cc/en/software
2. Utgå från en av mallarna, varje fil är en egen mall.

## mall_baradisplay.ino
Mallen har bara funktionen showDisplay().

1. Skapa ett mönster på http://dotmatrixtool.com/ (16 Width, 8 Height).
2. Klicka på "Genereate" och kopiera koden som kapas.
3. Klistra in koden under "//Display Patterns (16*8)" i mallen.
Exempel: 
```
//Display Patterns (16*8)
//http://dotmatrixtool.com/

const uint_8 data[] =
{
0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x0c, 0x0a, 0x0b, 0x0a, 0x0c, 0x08, 0x08, 0x00, 0x00, 0x00
};
```
4. Om du ska använda flera mönster måste du döpa dem olika
5. Se till att showDisplay() använder samma namn som koden du klistrat in.
Exempel: 
```
showDisplay(data);
```

## mall_nageringsrobot.ino

## mall_demo.ino
