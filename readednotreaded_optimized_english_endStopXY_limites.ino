/*
    LÍMITES por soft, funcionan. y se activa finZero() cuando termina de leer
*/

int burningTime = 2000;

#include <avr/pgmspace.h>
/*
  //PROGMEM prog_int16_t pixelX[]=
  const PROGMEM uint16_t pixelX[] = {1900, 1281, 1276, 1078, 1103, 1805, 1827, 1686, 1654, 1645, 1496, 1507, 1185, 1260, 986, 1005, 890, 839, 758, 778, 512, 395, 377, 285, 288, 121, 126, 1842, 1845, 1703, 1715, 1379, 1294, 1272, 1125, 1024, 933, 762, 1024, 424, 442, 230, 220, 15, 41, 1838, 1685, 1726, 1507, 1538, 1393, 1410, 1328, 1342, 1158, 1169, 1158, 958, 963, 919, 935, 710, 730, 616, 650, 493, 523, 404, 411, 236, 243, 191, 197, 7, 1881, 1837, 1635, 1653, 1443, 1398, 1290, 1242, 1171, 1172, 1069, 1074, 880, 882, 793, 795, 608, 615, 460, 456, 364, 322, 91, 77, 1848, 1839, 1767, 1765, 1677, 1661, 1496, 1493, 1309, 1306, 1236, 1249, 1178, 1186, 987, 985, 909, 916, 732, 735, 609, 607, 377, 377, 191, 211, 1819, 1887, 1707, 1709, 1488, 1487, 1438, 1443, 1369, 1370, 1178, 1192, 895, 927, 682, 699, 642, 603, 596, 494, 341, 327, 314, 224, 125, 118, 1823, 1834, 1783, 1801, 1709, 1517, 1528, 1440, 1458, 1159, 1033, 1031, 870, 872, 829, 823, 641, 654, 546, 562, 303, 377, 176, 175, 38, 47, 1762, 1776, 1649, 1646, 1410, 1425, 1337, 1339, 1830, 1814, 1703, 1703, 1600, 1592, 1428, 1423, 1209, 1212, 1209, 1212, 1192, 1212, 1192, 1212, 880, 861, 880, 861, 739, 735, 580, 584, 404, 406, 404, 406, 217, 242, 217, 242, 1805, 1797, 1805, 1797, 1611, 1594, 1418, 1414, 1298, 1295, 890, 915, 706, 709, 485, 481, 399, 405, 244, 251, 201, 198, 1755, 1772, 1648, 1649, 1596, 1582, 1396, 1393, 1333, 1324, 1196, 1205, 1014, 1023, 794, 799, 651, 670, 454, 473, 171, 170, 11, 12, 1884, 1884, 1667, 1677, 1544, 1539, 1342, 1267, 1267, 994, 995, 795, 819, 679, 671, 430, 428, 280, 274, 195, 192, 43, 60, 1846, 1854, 1669, 1634, 1500, 1522, 1283, 1243, 1231, 1211, 1132, 1146, 953, 962, 912, 907, 674, 677, 607, 615, 365, 371, 182, 192, 1802, 1825, 1589, 1569, 1551, 1360, 1404, 1293, 1100, 1129, 977, 998, 918, 922, 847, 869, 651, 666, 588, 596, 467, 486, 370, 380, 292, 330, 130, 12, 21, 1803, 1802, 1562, 1580, 1509, 1512, 1413, 1433, 1243, 1263, 1098, 1056, 1049, 924, 820, 831, 547, 549, 406, 419, 314, 324, 196, 205, 9, 1858, 1598, 1608, 1479, 1475, 1415, 1420, 1247, 1217, 1210, 1011, 1014, 845, 862, 666, 829, 516, 519, 306, 308, 94, 87, 1817, 1793, 1580, 1566, 1399, 1386, 1361, 1350, 1197, 1184, 1052, 1005, 993, 705, 673, 474, 347, 348, 168, 106, 153, 1825, 1768, 1816, 1564, 1550, 1338, 1235, 1067, 1072, 947, 933, 870, 868, 829, 828, 640, 611, 417, 399, 247, 247, 1784, 1792, 1658, 1681, 1534, 1530, 1461, 1446, 1391, 1079, 1089, 1021, 805, 796, 651, 679, 486, 498, 305, 255, 265, 15, 1884, 1883, 1652, 1649, 1501, 1507, 1312, 1294, 1052, 1058, 887, 921, 813, 853, 686, 570, 587, 300, 311, 98, 99, 38, 56, 1860, 1887, 1693, 1719, 1573, 1576, 1326, 1322, 1236, 1326, 956, 966, 899, 918, 785, 809, 526, 536, 279, 296, 159, 187, 64, 51, 1896, 1900, 1720, 1711, 1665, 1671, 1455, 1458, 1414, 1400, 1218, 1217, 1158, 1146, 1026, 1018, 995, 988, 845, 848, 623, 623, 532, 424, 432, 226, 258, 115, 115, 1851, 1869, 1616, 1628, 1550, 1481, 1467, 1361, 1373, 1140, 1157, 968, 964, 731, 725, 663, 665, 1800, 1823, 1617, 1594, 1347, 1355, 1127, 1065, 1084, 825, 845, 628, 588, 595, 382, 391, 335, 326, 173, 177, 1873, 1863, 1843, 1772, 1745, 1651, 1669, 1577, 1592, 1418, 1449, 1211, 1221, 926, 938, 852, 803, 822, 586, 585, 488, 482, 330, 324, 183, 196, 11, 44, 1882, 1860, 1834, 1792, 1834, 1610, 1627, 1400, 1394, 1184, 1188, 1060, 1068, 774, 786, 576, 589, 486, 527, 287, 281, 107, 106, 1847, 1850, 1621, 1625, 1483, 1439, 1411, 1262, 1241, 1116, 1094, 945, 941, 761, 758, 547, 546, 470, 459, 419, 422, 347, 337, 196, 201, 1848, 1855, 1635, 1623, 1564, 1557, 1285, 1265, 1099, 1071, 952, 961, 745, 745, 557, 561, 345, 345, 121, 119, 1828, 1769, 1662, 1543, 1565, 1350, 1359, 1177, 1189, 1033, 1024, 910, 924, 810, 806, 646, 634, 518, 516, 414, 415, 211, 209, 166, 1812, 1803, 1730, 1725, 1522, 1555, 1325, 1323, 1104, 1104, 956, 942, 840, 836, 583, 590, 338, 214, 235, 109, 114, 1803, 1810, 1650, 1663, 1407, 1440, 1241, 1263, 1041, 1038, 914, 927, 795, 806, 671, 685, 401, 414, 299, 272, 23, 38, 1900};
  //PROGMEM prog_int16_t pixelY[]=
  const PROGMEM uint16_t pixelY[] = {0, 0, 1, 2, 0, 201, 165, 176, 173, 186, 167, 181, 180, 181, 178, 187, 164, 186, 180, 168, 171, 239, 168, 239, 187, 165, 173, 317, 231, 256, 262, 224, 301, 246, 244, 304, 303, 241, 304, 228, 225, 244, 240, 241, 258, 290, 289, 307, 321, 317, 292, 315, 301, 306, 302, 328, 302, 302, 329, 303, 325, 296, 315, 294, 297, 309, 308, 304, 304, 292, 318, 312, 329, 308, 359, 374, 353, 371, 385, 373, 397, 361, 376, 380, 373, 363, 390, 376, 379, 368, 373, 376, 358, 373, 377, 364, 353, 381, 426, 444, 441, 468, 413, 462, 437, 481, 441, 460, 426, 434, 457, 451, 458, 473, 433, 422, 453, 436, 434, 418, 405, 420, 425, 436, 516, 462, 471, 471, 470, 488, 506, 525, 480, 496, 478, 495, 495, 477, 505, 513, 500, 503, 485, 504, 464, 498, 487, 468, 471, 491, 544, 561, 564, 559, 545, 562, 565, 534, 533, 544, 546, 535, 527, 548, 525, 540, 524, 543, 524, 536, 524, 548, 542, 570, 533, 556, 595, 626, 612, 627, 604, 608, 613, 632, 667, 692, 668, 670, 645, 678, 662, 680, 674, 683, 674, 683, 679, 683, 679, 683, 675, 701, 675, 701, 659, 677, 677, 678, 654, 673, 654, 673, 665, 683, 665, 683, 732, 747, 732, 747, 730, 754, 722, 721, 736, 742, 780, 785, 728, 756, 729, 757, 752, 755, 735, 727, 763, 752, 828, 815, 805, 817, 815, 832, 809, 814, 807, 816, 789, 795, 791, 784, 798, 811, 804, 793, 780, 772, 789, 802, 806, 790, 825, 821, 883, 863, 854, 858, 857, 851, 869, 881, 880, 840, 854, 854, 864, 842, 838, 871, 830, 836, 847, 857, 877, 914, 925, 920, 911, 934, 928, 921, 929, 925, 932, 923, 922, 917, 915, 925, 925, 914, 931, 924, 927, 927, 920, 936, 957, 980, 999, 982, 998, 990, 985, 985, 993, 1007, 969, 972, 987, 972, 976, 964, 966, 975, 967, 985, 978, 977, 978, 980, 994, 989, 966, 1008, 970, 997, 1015, 1030, 1029, 1056, 1003, 1027, 1034, 1010, 1042, 1047, 1055, 1071, 1029, 1029, 1045, 1056, 1013, 1040, 1042, 1053, 1033, 1057, 1018, 1027, 1043, 1082, 1107, 1118, 1086, 1119, 1094, 1112, 1099, 1120, 1090, 1114, 1130, 1093, 1087, 1081, 1109, 1114, 1122, 1099, 1103, 1094, 1117, 1149, 1176, 1144, 1158, 1141, 1156, 1142, 1144, 1168, 1173, 1151, 1163, 1122, 1151, 1149, 1150, 1180, 1160, 1154, 1151, 1167, 1199, 1200, 1219, 1196, 1219, 1207, 1223, 1216, 1218, 1216, 1232, 1202, 1220, 1213, 1204, 1197, 1211, 1210, 1228, 1214, 1217, 1351, 1366, 1333, 1335, 1353, 1343, 1331, 1337, 1342, 1353, 1347, 1334, 1370, 1370, 1356, 1336, 1336, 1349, 1302, 1342, 1366, 1364, 1409, 1411, 1417, 1431, 1408, 1404, 1387, 1405, 1382, 1407, 1397, 1419, 1377, 1423, 1381, 1416, 1416, 1398, 1396, 1398, 1416, 1397, 1395, 1425, 1474, 1469, 1452, 1463, 1472, 1443, 1460, 1451, 1443, 1454, 1458, 1446, 1450, 1450, 1459, 1470, 1477, 1492, 1495, 1487, 1473, 1452, 1499, 1517, 1543, 1510, 1545, 1527, 1517, 1542, 1522, 1520, 1543, 1539, 1533, 1565, 1552, 1537, 1541, 1534, 1543, 1525, 1530, 1514, 1529, 1537, 1524, 1511, 1552, 1518, 1536, 1537, 1593, 1573, 1586, 1562, 1566, 1543, 1593, 1626, 1605, 1617, 1596, 1584, 1578, 1588, 1576, 1602, 1600, 1659, 1664, 1645, 1630, 1636, 1633, 1654, 1638, 1642, 1631, 1652, 1624, 1619, 1646, 1630, 1647, 1633, 1667, 1626, 1641, 1676, 1737, 1687, 1722, 1687, 1727, 1729, 1708, 1715, 1690, 1697, 1678, 1697, 1685, 1712, 1684, 1684, 1705, 1721, 1717, 1724, 1715, 1681, 1726, 1704, 1716, 1710, 1715, 1751, 1791, 1736, 1792, 1736, 1781, 1802, 1768, 1790, 1746, 1765, 1756, 1771, 1770, 1774, 1777, 1796, 1762, 1758, 1739, 1741, 1733, 1756, 1791, 1819, 1812, 1839, 1854, 1805, 1844, 1816, 1832, 1835, 1855, 1829, 1846, 1814, 1821, 1850, 1836, 1841, 1845, 1828, 1813, 1815, 1827, 1826, 1813, 1899, 1862, 1919, 1902, 1912, 1906, 1885, 1870, 1858, 1871, 1863, 1868, 1908, 1889, 1907, 1869, 1894, 1876, 1903, 1876, 1926, 1939, 1926, 1977, 1969, 1963, 1945, 1934, 1922, 1928, 1944, 1926, 1946, 1912, 1918, 1939, 1919, 1967, 1931, 1951, 1943, 1952, 1947, 1918, 2008, 1989, 2004, 1979, 1987, 2003, 1993, 2008, 2010, 2005, 2004, 2023, 1994, 1990, 2022, 2000, 1987, 2018, 2019, 1999, 2021, 2048, 2076, 2067, 2068, 2066, 2064, 2069, 2085, 2052, 2074, 2052, 2068, 2043, 2063, 2058, 2068, 2055, 2077, 2096, 2066, 2081, 2086, 0};
*/

/*
  const PROGMEM uint16_t pixelX[] = {  1900, 50, 0};
  const PROGMEM uint16_t pixelY[] = {  0, 50, 0};
*/

//const PROGMEM uint16_t pixelX[] = {  1000, 950, 700, 600, 550, 1100, 500, 200, 600};    //DEFAULT
const PROGMEM uint16_t pixelX[] = {  200, 300, 100, 400, 600, 800, 500, 100, 600}; 
const PROGMEM uint16_t pixelY[] = {  300, 400, 450, 50, 500, 400, 600, 500, 450};


long arraySize = 9;  //726; //cantidad de fijaciones
long n = 1;
long m = 0;
//int sheetWidth = 1900;//fijarse si está haciendo algo

//NO HAY HOJA
//configurar estas variables según dimensiones de hoja a usar
const int minX = 0;
const int maxX = 1000;
const int minY = 300;
const int maxY = 1000;

//variables correspondientes al motor
int speedXY = 500; //speedXY en microsegundos // speedXY //no funciona igual para ambos lados a menos de 500
int speedZ = 500; //speedZ en microsegundos // speedZ
//motor Z
const int pinStepsZ = 11;
const int pinDirZ = 10;
const int pinResetZ = 12;
int stepsZ = 100; //stepsZ (cambiar a mano)
//X
const int pinStepsX = 3;
const int pinDirX = 4;
const int pinResetX = 2;
//Y
const int pinStepsY = 6;
const int pinDirY = 5;
const int pinResetY = 7;

//QUE ES ESTO? variables viejas de botón de encendido
//const int pinSensor = 24;
int valSensor = LOW;
//int oldvalSensor = LOW;
//int stateSensor = 0;
int flag = LOW;

//finales de carrera
const int endStopX = A0;
const int thresholdEndStopX = 50;
int valEndX;

const int endStopY = A2;
const int thresholdEndStopY = 30;
int valEndY;

const int endStopZ = A3;
const int umbralEndStopZ = 10;
int valEndZ;

int flagEndX = LOW;
int flagEndY = LOW;
int flagEndZ = LOW;

long counterX = 0;
long counterY = 0;


/*factor de conversión de pixel a pasos
    1000 pasos son 6,2 mm(de motor paso a paso de brida 28mm con acople de 5mm a 8mm y
  varilla roscada de 8mm)
  como convertir pixeles a pasos:
  (159mm(ancho de formato de texto)* 1000pap/ 6.2mm)/ 1890pX(ancho en pixeles) = f
  (159mm(ancho de formato de texto)* 1000pap/ 6.2mm)= 25645,16 (cantidad de pasos necesarios para recorrer el ancho del formato del texto)
  25646,16 / 1890pX= 13.56 = f */
float f = 7;//con guias lineales 13.5

long posX = 0; //Pasos convertidos a partir de la variable en X
long posY = 0; //Pasos convertidos a partir de la variable en Y

//VARIABLES SENSOR LDR
boolean readSheet = true; //readSheet
boolean flagEnableRollMotor = false;//flagEnableRollMotor
boolean exitOfMark = true;// exitOfMark
boolean flagTemperature = false;// flagTemperature

///MOTOR rollo arriba
const int pinDirUp = 30;
const int pinStepsUp = 28;
const int pinResetUp = 26;

///MOTOR rollo abajo
const int pinDirDown = 38;
const int pinStepsDown = 36;
const int pinResetDown = 34;

int speedRoll = 16000;

int POTE;
int LDR;
int LED = 11;

int temperatureSensor = 0;
const int temperaturePin = 44;
int temperatureLoopCounter = 3; //arranca solo si está en 3 temperatureLoopCounter

int flagFindZero = HIGH;//si pongo LOW evita buscar el cero
int flagEnableMotors = HIGH;

//leds testigos para usos múltiples
const int pinLed1 = 41;
const int pinLed2 = 40;
int led1;
int led2;

void setup() {
  //Serial.begin(115200);

  pinMode(pinStepsX, OUTPUT);
  pinMode(pinDirX, OUTPUT);
  pinMode(pinResetX, OUTPUT);
  pinMode(pinStepsY, OUTPUT);
  pinMode(pinDirY, OUTPUT);
  pinMode(pinResetY, OUTPUT);
  pinMode(pinStepsZ, OUTPUT);
  pinMode(pinDirZ, OUTPUT);
  pinMode(pinResetZ, OUTPUT);

  digitalWrite(pinResetX, LOW);
  digitalWrite(pinResetY, LOW);
  digitalWrite(pinResetZ, HIGH);

  //  pinMode(pinSensor, INPUT);
  pinMode(endStopZ, INPUT);

  ///SENSORES
  pinMode(LED, OUTPUT);
  pinMode(temperaturePin, INPUT);

  ///MOTOR UP
  pinMode(pinDirUp, OUTPUT);
  pinMode(pinStepsUp, OUTPUT);
  pinMode(pinResetUp, OUTPUT);

  ///MOTOR DOWN
  pinMode(pinDirDown, OUTPUT);
  pinMode(pinStepsDown, OUTPUT);
  pinMode(pinResetDown, OUTPUT);

  digitalWrite(pinStepsUp, LOW);
  digitalWrite(pinResetDown, LOW);
  //poner al sistema en cero (0,0,0)
  //funcion cero
  //libero motor abajo del rollo
  digitalWrite(pinResetDown, LOW);

  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);

  delay(3000); //para que no arranque directo

  sequenceUp2();

}

void loop() {
  //Esperar que la resistencia calienta. - Esta máquina no quema.
  countTemperatureLoops();

  // BUSCAR EL (0,0)
  if (flagFindZero == HIGH) {
    findZero();
  }

  //a partir de acá la maquina está lista para Burn - Esta máquina no quema.
  burn();
}

void countTemperatureLoops() {  //secuencia para contar ciclos de prendido Y apagado de la resistencia
  temperatureSensor = digitalRead(temperaturePin);

  if (temperatureSensor == LOW && flagTemperature == false ) {
    temperatureLoopCounter++;
    flagTemperature = true;
  }
  if (temperatureSensor == HIGH && flagTemperature == true ) {
    temperatureLoopCounter++;
    flagTemperature = false;
  }
  //Serial.println(temperatureLoopCounter);
}

void findZero() {
  enableMotorsXY(); //Prendo motores para buscar el cero
  valEndX = analogRead(endStopX);
  //fin de carrera en X
  if ((valEndX > thresholdEndStopX) && (flagEndX == LOW)) {
    // Fijarse la direccion de X
    digitalWrite(pinDirX, HIGH);
    moveMotor(pinStepsX, speedXY);
  }
  if (valEndX < thresholdEndStopX) {
    flagEndX = HIGH;
    digitalWrite(pinResetX, LOW); //apago motorX
  }
  //fin de carrera en Y
  valEndY = analogRead(endStopY); //leo fin de carrera en Y
  if ((valEndY > thresholdEndStopY) && (flagEndY == LOW)) {
    // Fijarse la direccion de Y
    digitalWrite(pinDirY, LOW);
    moveMotor(pinStepsY, speedXY);
  }
  if (valEndY < thresholdEndStopY) {
    flagEndY = HIGH;
    digitalWrite(pinResetY, LOW);
  }
  if (flagEndX == HIGH && flagEndY == HIGH) { //si tocaron ambos fines de carrera ya está en 0,0
    flagFindZero = LOW;
    //jueguito de luces para darme cuenta que llegó a cero
    digitalWrite(pinLed1, HIGH);
    delay(500);
    digitalWrite(pinLed2, HIGH);
    delay(500);
    digitalWrite(pinLed1, LOW);
    delay(500);
    digitalWrite(pinLed2, LOW);
    delay(500);
  }
}

void burn() {
  if ((temperatureLoopCounter > 2) && (flagFindZero == LOW)) {
    valSensor = HIGH;  //digitalRead(pinSensor);//leo el boton de encendido
    //    flag == LOW;
    if ((valSensor == HIGH) && (flag == LOW)) {
      arrayRead();
      // digitalWrite prepara los motores para mover
      //secuencia de encendido()
      digitalWrite(pinResetZ, HIGH); //el motorZ no está prendido siempre?!?!
      digitalWrite(pinResetY, HIGH);
      digitalWrite(pinResetX, HIGH);
      flag = HIGH;
      //    Serial.println("ENCENDIDO");
    }
    /*if ((valSensor == HIGH) && (flag == HIGH)) {
      flag = LOW;
      //delay(1000);
      //    Serial.println("APAGADO");
      }*/
    if ( readSheet == true) { //empieza a Burn
      //apagar motores de rollo una vez
      if (flagEnableRollMotor == false) {
        digitalWrite(pinResetUp, LOW);
        digitalWrite(pinResetDown, LOW);
        flagEnableRollMotor = true;
      }
      //movimiento de motores en X e Y
      if (flag == HIGH) {
        if (posX > 0) {//hacia la izquierda
          /* valEndX = analogRead(endStopX);//LÍMITES MECÁNICOS. leo el sensor
            if (valEndX < thresholdEndStopX) {//si llega al sensor
            posX = 0;                     // cree que llegó al punto
            counterX= posX;
            } */
          digitalWrite(pinDirX, HIGH);
          if (counterX < posX) {
            moveMotor(pinStepsX, speedXY); //Move
            counterX++;
          }
        }
        else if (posX < 0) {
          digitalWrite(pinDirX, LOW);
          if (counterX < (-posX)) {
            moveMotor(pinStepsX, speedXY);
            counterX++;
          }
        }

        if (posY > 0) {//hacia abajo
          digitalWrite(pinDirY, HIGH);
          if (counterY < posY) {
            moveMotor(pinStepsY, speedXY);
            counterY++;
          }
        }
        else if (posY < 0) {//hacia arriba
          /* valEndY = analogRead(endStopY);//LÍMITES MECÁNICOS. leo el sensor
            if (valEndY < thresholdEndStopY) {//si llega al sensor
             posY = 0;                     // cree que llegó al punto
             counterY = posY;
            }  */
          digitalWrite(pinDirY, LOW);
          if (counterY < (-posY)) {
            moveMotor(pinStepsY, speedXY);
            counterY++;
          }
        }
      }
    }

    if (readSheet == false) {//si no esta leyendo, ir a nueva pagina
      sheetSensing();//Sensar hoja, para saber si esta en una marca o no //SheetSensing
    }
    if (counterX == abs(posX) && counterY == abs(posY)) {
      sequenceDown();//marco la fijacion
      counterX = 0;
      counterY = 0;
      m = n;
      n++;//avanzo una posición en el array
      if (n == arraySize - 1) {
        for (int i = 0; i < 3; i++) {//probando que llegó
          sequenceDown();
        }
        readSheet = false; //terminó de Burn la hoja
        exitOfMark = true;
        flagEnableRollMotor = true;
        n = 1;
        m = 0;
        flagFindZero = HIGH;//faltaba agregar esto :)
        flagEndX = LOW;
        flagEndY = LOW;
        findZero();
      }
      arrayRead(); //busca una nueva posición
    }
  }
}

void enableMotorsXY() {
  if ((flagFindZero == HIGH) && (flagEnableMotors == HIGH)) {
    digitalWrite(pinResetY, HIGH);
    digitalWrite(pinResetX, HIGH);
    flagEnableMotors = LOW;
  }
}

void moveMotor(int pinStep, int velocidad) {
  digitalWrite(pinStep, HIGH);
  delayMicroseconds(velocidad);
  digitalWrite(pinStep, LOW);
  delayMicroseconds(velocidad);
}

void sequenceDown() {
  turnOffXY();
  digitalWrite(pinDirZ, HIGH);
  for (int i = 0; i < stepsZ; i++) {
    moveMotor(pinStepsZ, speedZ);
  }
  delay(burningTime);
  //sequenceUp();
  sequenceUp2();
  turnOnXY();
}

void sequenceUp() {//función para evantar en Z, con sensor
  digitalWrite(pinDirZ, LOW);
  while (flagEndZ == LOW) {
    valEndZ = analogRead(endStopZ);
    if (valEndZ > umbralEndStopZ) {
      digitalWrite(pinResetZ, HIGH);
      moveMotor(pinStepsZ, speedZ);
    } else {
      digitalWrite(pinResetZ, LOW);
      flagEndZ = HIGH; //flag en HIGH cuando está en 0
    }
  }
}

void sequenceUp2() { //función antigüa, sin sensor
  digitalWrite(pinDirZ, LOW);
  for (int i = 0; i < stepsZ; i++) {
    moveMotor(pinStepsZ, speedZ);
  }
}

void turnOffXY() {
  digitalWrite(pinResetX, LOW);
  digitalWrite(pinResetY, LOW);
}

void turnOnXY() {
  digitalWrite(pinResetX, HIGH);
  digitalWrite(pinResetY, HIGH);
}

void arrayRead() {
  /*
     chequear antes de moverme si se puede ir o no a ese punto, segun límites de ancho de hoja
     si está fuera de los límites paso al siguiente punto (sin actualizar el punto anterior)
     tengo que saber mi posición actual Y hacer el calculo Y ver si está dentro de mi hoja
     si no está dentro de mi hoja n++
  */
  //posX = arraX[n];
  posX = pgm_read_word_near(pixelX + n);      //leo nueva cordenada en X
  while ( posX < minX || posX > maxX) {       //si posX se sale de lo límites
    n++;                                      //avanzo una posición
    posX = pgm_read_word_near(pixelX + n);
    digitalWrite(pinLed1, HIGH);
    delay(200);
    digitalWrite(pinLed1, LOW);
  }

  posY = pgm_read_word_near(pixelY + n);
  while ( posY < minY || posY > maxY) {//si posY se sale de lo límites
    n++;                               //avanzo una posición
    posY = pgm_read_word_near(pixelY + n);
    digitalWrite(pinLed2, HIGH);
    delay(500);
    digitalWrite(pinLed2, LOW);
  }
  posY = pgm_read_word_near(pixelY + n);//leo nueva posición en Y
  posX = pgm_read_word_near(pixelX + n);//leo nueva posición en X

  posX = (posX - pgm_read_word_near(pixelX + m)) * f; //posX = cantidad de pasos de motor en "x" que debe efectuar para ir a destino
  posY = (posY - pgm_read_word_near(pixelY + m)) * f; //posY = cantidad de pasos de motor en "y" que debe efectuar para ir a destino

}

void sheetSensing() {
  //me fijo si el LDR detecta la marca
  if (exitOfMark == true) {
    digitalWrite(pinResetUp, HIGH);
    for (int i = 0; i < 50; i++) {
      moveMotor(pinStepsUp, speedRoll);
    }
    exitOfMark = false;
  }
  POTE = analogRead(A4); //usado para calibración
  LDR = analogRead(A7);
  if (flagEnableRollMotor == true) {
    digitalWrite(pinResetUp, HIGH);
    digitalWrite(pinDirUp, LOW);
    flagEnableRollMotor = false;
  }
  moveMotor(pinStepsUp, speedRoll);
  if (LDR > POTE) { //si detecta marca, haY que leer nueva hoja
    digitalWrite(LED, HIGH);
    readSheet = true;
  }
  else {
    digitalWrite(LED, LOW);
  }
}
