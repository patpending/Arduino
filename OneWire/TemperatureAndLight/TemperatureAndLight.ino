#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>


// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 10

//set up the pixel ring
#define PIN 9
int POTPIN = A1;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


//Neopixel vars
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);
uint32_t colorMap[255];
double tempMin = 23.0;
double tempMax = 31.0;


void setup(void)
{
  // start serial port
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
  pinMode(PIN,OUTPUT);
  setUpColorMap();
  // Start up the library
  sensors.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement
}


void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures
  double temp = sensors.getTempCByIndex(0);// Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.print(temp); 
  Serial.print('\n'); 
  tempToColour(temp);
}

void tempToColour(double temp)
{
    if (temp <= tempMin)
    {
      temp = tempMin;
    }
    if (temp>= tempMax)
    {
      temp = tempMax;
    }
    
    //val = map(val, 0, 1023, 0, 255);
    int colourInt = mapDouble(temp, tempMin, tempMax, 0, 255);
    Serial.print(colourInt);
    colorWipe(colorMap[colourInt-1]);
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(2);
  }
}



void setUpColorMap()
{
//colorMap[0] = strip.Color(59,76,192);
colorMap[0] = strip.Color(60,78,194);
colorMap[1] = strip.Color(60,78,194);
colorMap[2] = strip.Color(61,80,195);
colorMap[3] = strip.Color(62,81,197);
colorMap[4] = strip.Color(63,83,198);
colorMap[5] = strip.Color(64,85,200);
colorMap[6] = strip.Color(66,87,201);
colorMap[7] = strip.Color(67,88,203);
colorMap[8] = strip.Color(68,90,204);
colorMap[9] = strip.Color(69,92,206);
colorMap[10] = strip.Color(70,93,207);
colorMap[11] = strip.Color(71,95,209);
colorMap[12] = strip.Color(73,97,210);
colorMap[13] = strip.Color(74,99,211);
colorMap[14] = strip.Color(75,100,213);
colorMap[15] = strip.Color(76,102,214);
colorMap[16] = strip.Color(77,104,215);
colorMap[17] = strip.Color(79,105,217);
colorMap[18] = strip.Color(80,107,218);
colorMap[19] = strip.Color(81,109,219);
colorMap[20] = strip.Color(82,110,221);
colorMap[21] = strip.Color(84,112,222);
colorMap[22] = strip.Color(85,114,223);
colorMap[23] = strip.Color(86,115,224);
colorMap[24] = strip.Color(87,117,225);
colorMap[25] = strip.Color(89,119,226);
colorMap[26] = strip.Color(90,120,228);
colorMap[27] = strip.Color(91,122,229);
colorMap[28] = strip.Color(93,123,230);
colorMap[29] = strip.Color(94,125,231);
colorMap[30] = strip.Color(95,127,232);
colorMap[31] = strip.Color(96,128,233);
colorMap[32] = strip.Color(98,130,234);
colorMap[33] = strip.Color(99,131,235);
colorMap[34] = strip.Color(100,133,236);
colorMap[35] = strip.Color(102,135,237);
colorMap[36] = strip.Color(103,136,238);
colorMap[37] = strip.Color(104,138,239);
colorMap[38] = strip.Color(106,139,239);
colorMap[39] = strip.Color(107,141,240);
colorMap[40] = strip.Color(108,142,241);
colorMap[41] = strip.Color(110,144,242);
colorMap[42] = strip.Color(111,145,243);
colorMap[43] = strip.Color(112,147,243);
colorMap[44] = strip.Color(114,148,244);
colorMap[45] = strip.Color(115,150,245);
colorMap[46] = strip.Color(116,151,246);
colorMap[47] = strip.Color(118,153,246);
colorMap[48] = strip.Color(119,154,247);
colorMap[49] = strip.Color(120,156,247);
colorMap[50] = strip.Color(122,157,248);
colorMap[51] = strip.Color(123,158,249);
colorMap[52] = strip.Color(124,160,249);
colorMap[53] = strip.Color(126,161,250);
colorMap[54] = strip.Color(127,163,250);
colorMap[55] = strip.Color(129,164,251);
colorMap[56] = strip.Color(130,165,251);
colorMap[57] = strip.Color(131,167,252);
colorMap[58] = strip.Color(133,168,252);
colorMap[59] = strip.Color(134,169,252);
colorMap[60] = strip.Color(135,171,253);
colorMap[61] = strip.Color(137,172,253);
colorMap[62] = strip.Color(138,173,253);
colorMap[63] = strip.Color(140,174,254);
colorMap[64] = strip.Color(141,176,254);
colorMap[65] = strip.Color(142,177,254);
colorMap[66] = strip.Color(144,178,254);
colorMap[67] = strip.Color(145,179,254);
colorMap[68] = strip.Color(147,181,255);
colorMap[69] = strip.Color(148,182,255);
colorMap[70] = strip.Color(149,183,255);
colorMap[71] = strip.Color(151,184,255);
colorMap[72] = strip.Color(152,185,255);
colorMap[73] = strip.Color(153,186,255);
colorMap[74] = strip.Color(155,187,255);
colorMap[75] = strip.Color(156,188,255);
colorMap[76] = strip.Color(158,190,255);
colorMap[77] = strip.Color(159,191,255);
colorMap[78] = strip.Color(160,192,255);
colorMap[79] = strip.Color(162,193,255);
colorMap[80] = strip.Color(163,194,255);
colorMap[81] = strip.Color(164,195,254);
colorMap[82] = strip.Color(166,196,254);
colorMap[83] = strip.Color(167,197,254);
colorMap[84] = strip.Color(168,198,254);
colorMap[85] = strip.Color(170,199,253);
colorMap[86] = strip.Color(171,199,253);
colorMap[87] = strip.Color(172,200,253);
colorMap[88] = strip.Color(174,201,253);
colorMap[89] = strip.Color(175,202,252);
colorMap[90] = strip.Color(176,203,252);
colorMap[91] = strip.Color(178,204,251);
colorMap[92] = strip.Color(179,205,251);
colorMap[93] = strip.Color(180,205,251);
colorMap[94] = strip.Color(182,206,250);
colorMap[95] = strip.Color(183,207,250);
colorMap[96] = strip.Color(184,208,249);
colorMap[97] = strip.Color(185,208,248);
colorMap[98] = strip.Color(187,209,248);
colorMap[99] = strip.Color(188,210,247);
colorMap[100] = strip.Color(189,210,247);
colorMap[101] = strip.Color(190,211,246);
colorMap[102] = strip.Color(192,212,245);
colorMap[103] = strip.Color(193,212,245);
colorMap[104] = strip.Color(194,213,244);
colorMap[105] = strip.Color(195,213,243);
colorMap[106] = strip.Color(197,214,243);
colorMap[107] = strip.Color(198,214,242);
colorMap[108] = strip.Color(199,215,241);
colorMap[109] = strip.Color(200,215,240);
colorMap[110] = strip.Color(201,216,239);
colorMap[111] = strip.Color(203,216,238);
colorMap[112] = strip.Color(204,217,238);
colorMap[113] = strip.Color(205,217,237);
colorMap[114] = strip.Color(206,217,236);
colorMap[115] = strip.Color(207,218,235);
colorMap[116] = strip.Color(208,218,234);
colorMap[117] = strip.Color(209,219,233);
colorMap[118] = strip.Color(210,219,232);
colorMap[119] = strip.Color(211,219,231);
colorMap[120] = strip.Color(213,219,230);
colorMap[121] = strip.Color(214,220,229);
colorMap[122] = strip.Color(215,220,228);
colorMap[123] = strip.Color(216,220,227);
colorMap[124] = strip.Color(217,220,225);
colorMap[125] = strip.Color(218,220,224);
colorMap[126] = strip.Color(219,220,223);
colorMap[127] = strip.Color(220,221,222);
colorMap[128] = strip.Color(221,221,221);
colorMap[129] = strip.Color(222,220,219);
colorMap[130] = strip.Color(223,220,218);
colorMap[131] = strip.Color(224,219,216);
colorMap[132] = strip.Color(225,219,215);
colorMap[133] = strip.Color(226,218,214);
colorMap[134] = strip.Color(227,218,212);
colorMap[135] = strip.Color(228,217,211);
colorMap[136] = strip.Color(229,216,209);
colorMap[137] = strip.Color(230,216,208);
colorMap[138] = strip.Color(231,215,206);
colorMap[139] = strip.Color(232,215,205);
colorMap[140] = strip.Color(232,214,203);
colorMap[141] = strip.Color(233,213,202);
colorMap[142] = strip.Color(234,212,200);
colorMap[143] = strip.Color(235,212,199);
colorMap[144] = strip.Color(236,211,197);
colorMap[145] = strip.Color(236,210,196);
colorMap[146] = strip.Color(237,209,194);
colorMap[147] = strip.Color(238,209,193);
colorMap[148] = strip.Color(238,208,191);
colorMap[149] = strip.Color(239,207,190);
colorMap[150] = strip.Color(240,206,188);
colorMap[151] = strip.Color(240,205,187);
colorMap[152] = strip.Color(241,204,185);
colorMap[153] = strip.Color(241,203,184);
colorMap[154] = strip.Color(242,202,182);
colorMap[155] = strip.Color(242,201,181);
colorMap[156] = strip.Color(243,200,179);
colorMap[157] = strip.Color(243,199,178);
colorMap[158] = strip.Color(244,198,176);
colorMap[159] = strip.Color(244,197,174);
colorMap[160] = strip.Color(245,196,173);
colorMap[161] = strip.Color(245,195,171);
colorMap[162] = strip.Color(245,194,170);
colorMap[163] = strip.Color(245,193,168);
colorMap[164] = strip.Color(246,192,167);
colorMap[165] = strip.Color(246,191,165);
colorMap[166] = strip.Color(246,190,163);
colorMap[167] = strip.Color(246,188,162);
colorMap[168] = strip.Color(247,187,160);
colorMap[169] = strip.Color(247,186,159);
colorMap[170] = strip.Color(247,185,157);
colorMap[171] = strip.Color(247,184,156);
colorMap[172] = strip.Color(247,182,154);
colorMap[173] = strip.Color(247,181,152);
colorMap[174] = strip.Color(247,180,151);
colorMap[175] = strip.Color(247,178,149);
colorMap[176] = strip.Color(247,177,148);
colorMap[177] = strip.Color(247,176,146);
colorMap[178] = strip.Color(247,174,145);
colorMap[179] = strip.Color(247,173,143);
colorMap[180] = strip.Color(247,172,141);
colorMap[181] = strip.Color(247,170,140);
colorMap[182] = strip.Color(247,169,138);
colorMap[183] = strip.Color(247,167,137);
colorMap[184] = strip.Color(247,166,135);
colorMap[185] = strip.Color(246,164,134);
colorMap[186] = strip.Color(246,163,132);
colorMap[187] = strip.Color(246,161,131);
colorMap[188] = strip.Color(246,160,129);
colorMap[189] = strip.Color(245,158,127);
colorMap[190] = strip.Color(245,157,126);
colorMap[191] = strip.Color(245,155,124);
colorMap[192] = strip.Color(244,154,123);
colorMap[193] = strip.Color(244,152,121);
colorMap[194] = strip.Color(244,151,120);
colorMap[195] = strip.Color(243,149,118);
colorMap[196] = strip.Color(243,147,117);
colorMap[197] = strip.Color(242,146,115);
colorMap[198] = strip.Color(242,144,114);
colorMap[199] = strip.Color(241,142,112);
colorMap[200] = strip.Color(241,141,111);
colorMap[201] = strip.Color(240,139,109);
colorMap[202] = strip.Color(240,137,108);
colorMap[203] = strip.Color(239,136,106);
colorMap[204] = strip.Color(238,134,105);
colorMap[205] = strip.Color(238,132,103);
colorMap[206] = strip.Color(237,130,102);
colorMap[207] = strip.Color(236,129,100);
colorMap[208] = strip.Color(236,127,99);
colorMap[209] = strip.Color(235,125,97);
colorMap[210] = strip.Color(234,123,96);
colorMap[211] = strip.Color(233,121,95);
colorMap[212] = strip.Color(233,120,93);
colorMap[213] = strip.Color(232,118,92);
colorMap[214] = strip.Color(231,116,90);
colorMap[215] = strip.Color(230,114,89);
colorMap[216] = strip.Color(229,112,88);
colorMap[217] = strip.Color(228,110,86);
colorMap[218] = strip.Color(227,108,85);
colorMap[219] = strip.Color(227,106,83);
colorMap[220] = strip.Color(226,104,82);
colorMap[221] = strip.Color(225,102,81);
colorMap[222] = strip.Color(224,100,79);
colorMap[223] = strip.Color(223,98,78);
colorMap[224] = strip.Color(222,96,77);
colorMap[225] = strip.Color(221,94,75);
colorMap[226] = strip.Color(220,92,74);
colorMap[227] = strip.Color(218,90,73);
colorMap[228] = strip.Color(217,88,71);
colorMap[229] = strip.Color(216,86,70);
colorMap[230] = strip.Color(215,84,69);
colorMap[231] = strip.Color(214,82,67);
colorMap[232] = strip.Color(213,80,66);
colorMap[233] = strip.Color(212,78,65);
colorMap[234] = strip.Color(210,75,64);
colorMap[235] = strip.Color(209,73,62);
colorMap[236] = strip.Color(208,71,61);
colorMap[237] = strip.Color(207,69,60);
colorMap[238] = strip.Color(205,66,59);
colorMap[239] = strip.Color(204,64,57);
colorMap[240] = strip.Color(203,62,56);
colorMap[241] = strip.Color(202,59,55);
colorMap[242] = strip.Color(200,57,54);
colorMap[243] = strip.Color(199,54,53);
colorMap[244] = strip.Color(198,51,52);
colorMap[245] = strip.Color(196,49,50);
colorMap[246] = strip.Color(195,46,49);
colorMap[247] = strip.Color(193,43,48);
colorMap[248] = strip.Color(192,40,47);
colorMap[249] = strip.Color(190,37,46);
colorMap[250] = strip.Color(189,34,45);
colorMap[251] = strip.Color(188,30,44);
colorMap[252] = strip.Color(186,26,43);
colorMap[253] = strip.Color(185,22,41);
colorMap[254] = strip.Color(183,17,40);


}

int mapDouble(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

