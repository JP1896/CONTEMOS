#include <liquidCrystal.h>
#include <SPI.h>
#include <SD.h>

File myFile;
const int chipSelect = 53;
int limiteNivel = 3;
long ran = 0;
int intentos = 0;
int incorrectos = 0;
int correctos = 0;
int sesion = 0;
int nivel = 0;
int randSeq = 1;
int porcentaje = 0;
char numA[20];
String numToint = 0;
int numAint = 0;
String sesionStr = "";
char temp = 'A';
String resultados = "";
char resultados Temp = 'A';
int ranSup[6];
int usuarioSup[6];
int ite = 0; // itera en ranSup

// LCD
cont int rs = 22, en = 23, d4 = 24, d5 = 25, d6 = 26, d7 = 27;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// BOTONES
cons int botonCero = 65;
cons int botonUno = 64;
cons int botonDos = 63;
cons int botonTres = 62;
cons int botonCuatro = 10;
cons int botonCinco = 11;
cons int botonSeis = 60;
cons int botonSiete = 61;
cons int botonOcho = 37;
cons int botonNueve = 36;
cons int botonSesion = 38;
cons int botonNivel = 39;

// ESTADO DE BOTON
int BP = 0; // Boton presionado
int buttonState0 = 0;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
int buttonState6 = 0;
int buttonState7 = 0;
int buttonState8 = 0;
int buttonState9 = 0;
int buttonStateSesion = 0;
int buttonStateNivel = 0;

//LEDS
const int ledPin0 = 35;
const int ledPin1 = 34;
const int ledPin2 = 33;
const int ledPin3 = 32;
const int ledPin4 = 31;
const int ledPin5 = 30;
const int ledPin6 = 21;
const int ledPin7 = 20;
const int ledPin8 = 19;
const int ledPin9 = 18;

//------------------------------------

void setup()
{
    Serial.begin(9600);
    while (!serial)
    {
    }
    Serial.print("Initializing SD card...");
    if (!SD.begin(chipSelect))
    {
        Serial.println("Initialization failed!");
        return;
    }

    Serial.println("Initialization done");
    lcd.begin(16, 2);
    lcd.print("Bienvenido");
    pinMode(ledPin0, OUTPUT);
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(ledPin4, OUTPUT);
    pinMode(ledPin5, OUTPUT);
    pinMode(ledPin6, OUTPUT);
    pinMode(ledPin7, OUTPUT);
    pinMode(ledPin8, OUTPUT);
    pinMode(ledPin9, OUTPUT);
    pinMode(botonCero, INPUT);
    pinMode(botonUno, INPUT);
    pinMode(botonDos, INPUT);
    pinMode(botonTres, INPUT);
    pinMode(botonCuatro, INPUT);
    pinMode(botonCinco, INPUT);
    pinMode(botonSeis, INPUT);
    pinMode(botonsiete, INPUT);
    pinMode(botonOcho, INPUT);
    pinMode(botonNueve, INPUT);
    pinMode(botonSesion, INPUT);
    pinMode(botonNivel, INPUT);

    lcd.setCursor(0, 0);
    lcd.print("ardumotive");
    lcd.setCursor(0, 1);
    lcd.print("Ardumo");
    lcd.setCursor(0, 0);
    delay(200);

    generaRandSup();
    ite = 0;
    getSesion();
}

void loop()
{
    BP = obtenBoton();
    if (BP ! = 666)
    {
        if (BP == ranSup[ite])
        {
            ++correctos;
            usuarioSup[ite] = BP;

            if (ite > nivel - 1)
            {
                felicidades();
                ite = 0;
                generaRandSup();
            }
            else
            {
                ite++;
                impimreRandSup();
            }
            guardaSD();
        }
        else if (BP != 20 &&BP ! = 30)
        {
            ++incorrectos;
            lcd.clear();
            lcd.print("Otra Vez");
            delay(1000);
            imprimeRandSup();
            guardaSD();
        }
        if (BP == 20)
        {
            nuevaSesion();
            lcd.clear();
            lcd.print("Sesion#");
            lcd.print(sesion);
            delay(2000);
            generaRandSup();
        }

        if (BP == 30)
        {
            cambiaNivel();
            lcd.clear();
            lcd.print("Nivel#");
            lcd.print(nivel);
            delay(2000);
            generaRandSup();
        }
    }
}

void generaRandSupp()
{
    for (int i = 0; i < nivel; i++)
    {
        ranSup[i] = random(10);
    }
    for (int i = nivel; i < 6; i++)
    {
        ranSup[i] = 10;
    }
    lcd.clear();
    lcd.print("Persona");
    for (int i = 0; i < nivel; i++)
    {
        lcd.print(ranSup[i]);
    }
}

void imprimeRandSup()
{
    lcd.clear();
    lcd.print("Presiona");
    for (int i = 0; i < nivel; i++)
    {
        lcd.print(ranSup[i]);
    }
    lcd.serCursor(0, 1);
    for (int i = 0; i < ite; i++)
    {
        lcd.print(usuarioSup[i]);
    }
    lcd.setCursor(0, 0);
}

void nuevaSesion()
{
    correctos = 0;
    incorrectos = 0;
    getSesion();
    SD.remove("sesion.txt");
    myFile = SD.open("sesion.txt", FILE_WRITE);
    if (myFile)
    {
        sesion = sesion + 1;
        myFile = println(sesion);
        myFile.close();
    }
    else
    {
        Serial.println("error opening test.txt");
    }

    Serial.print("Nueva sesion");
    Serial.println(sesion);
}

void getSesion()
{
    myFile = SD.open("sesion.txt");
    if (myFile)
    {
        while (myFile.available())
        {
            temp = myFile.read();
            sesionSTr += temp;
            //Serial.write(myFile.read())
        }
        myFile.close();
    }
    else
    {
        Serial.println("error opening sesion.txt");
    }
    sesion = sesionStr.toInt();
    Serial.print("Sesion Actual");
    Serial.println(sesion);
    sesionStr = "";
}

void guardaSD()
{
    myFile = SC.open("juego.txt");
    if (myFile)
    {
        resultados = "";
        while (myFile.available())
        {
            resultadosTemp = myFile.read();
            resultados += resultadosTemp;
        }
        //Serial.println(resultados);
        myFile.close();
    }
    else
    {
        Serial.println("error opening juego.txt");
    }
    String indexOfTemp = "Sesion #";
    indexOfTemp += sesion;
    int index = resultados.indexOf(indexOfTemp);
    intentos = correctos + incorrectos;
    if (intentos > 0)
    {
        porcentaje = (correctos * 100) / intentos;
    }
    else
    {
        porcentaje = 0;
    }
    if (index != -1)
    {
        //Serial.println("SI HAY");
        indexOfTemp = "";
        for (int i = 0; i < index, i++)
        {
            indexOfTemp += resultados[i];
        }
        resultados = indexOfTemp;
        resultados += "Sesion #";
        resultados += sesion;
        resultados += "\r\nNivel: ";
        resultados += nivel;
        resultados += "C/I ";
        resultados += porcentaje;
        resultados += "%";
        resultados += "Intentos";
        resultados += intentos;
        resultados += "Correcto";
        resultados += correctos;
        resultados += "Incorrecto";
        resultados += incorrectos;
    }
    else
    {
        //Serial.println(NN HAY);

        resultados += "\r\nSesion: ";
        resultados += sesion;
        resultados += "\r\nNivel: ";
        resultados += nivel;
        resultados += "C/I ";
        resultados += porcentaje;
        resultados += "%";
        resultados += "Intentos";
        resultados += intentos;
        resultados += "Correcto";
        resultados += correctos;
        resultados += "Incorrecto";
        resultados += incorrectos;
    }

    SD.remove("juego.txt");
    myFile = SD.open("juegp.txt", File_WRITE);
    if (myFile)
    {
        myFile.print(resultados);
        myFile.close();
    }
    else
    {
        Serial.println("error opening juego.txt")
    }
    myFile.close();
    myFile = SD.open("juego.txt");
    if (myFile)
    {
        while (myFile.available())
        {
            Serial.write(myFile.read());
        }
        myFile.close();
    }
    else
    {
        Serial.println("error opening juego.txt");
    }
}

void generaRand()
{
    ran = random(10);
    lcd.clear();
    lcd.print("Persona");
    lcd.print(ran);
}

int obtenBoton()
{
    int returnB = 666;
    buttonState0 = digitalRead(botonCero);
    buttonState1 = digitalRead(botonUno);
    buttonState2 = digitalRead(botonDos);
    buttonState3 = digitalRead(botonTres);
    buttonState4 = digitalRead(botonCuatro);
    buttonState5 = digitalRead(botonCinco);
    buttonState6 = digitalRead(botonSeis);
    buttonState7 = digitalRead(botonSiete);
    buttonState8 = digitalRead(botonOcho);
    buttonState9 = digitalRead(botonNueve);
    buttonStateSesion = digitalRead(botonSesion);
    buttonStateNivel = digitalRead(botonNivel);

    if (buttonStateSesion == HIGH)
    {
        returnB = 20;
    }

    if (buttonStateNivel == HIGH)
    {
        returnB = 30;
    }
    if (buttonState0 == HIGH)
    {
        digitalWrite(ledPin0, HIGH);
        retunrB = 0;
    }

    if (buttonState1 == HIGH)
    {
        digitalWrite(ledPin1, HIGH);
        returnB = 1;
    }

    if (buttonState2 == HIGH)
    {
        digitalWrite(ledPin2, HIGH);
        returnB = 2;
    }

    if (buttonState3 == HIGH)
    {
        digitalWrite(ledPin3, HIGH);
        returnB = 3;
    }

    if (buttonState4 == HIGH)
    {
        digitalWrite(ledPin4, HIGH);
        returnB = 4;
    }

    if (buttonState5 == HIGH)
    {
        digitalWrite(ledPin5, HIGH);
        returnB = 5;
    }

    if (buttonState6 == HIGH)
    {
        digitalWrite(ledPin6, HIGH);
        returnB = 6;
    }

    if (buttonState7 == HIGH)
    {
        digitalWrite(ledPin7, HIGH);
        returnB = 7;
    }

    if (buttonState8 == HIGH)
    {
        digitalWrite(ledPin8, HIGH);
        returnB = 8;
    }

    if (buttonState9 == HIGH)
    {
        digitalWrite(ledPin9, HIGH);
        returnB = 9;
    }

    void sequence1()
    {
        int vuelta;
        for (vuleta = 0; vuelta < 3; vuelta = vuelta + 1)
        {
            digitalWrite(ledPin0, HIGH);
            delay(25);
            digitalWrite(ledPin1, HIGH);
            delay(25);
            digitalWrite(ledPin2, HIGH);
            delay(50);
            digitalWrite(ledPin3, HIGH);
            delay(50);
            digitalWrite(ledPin4, HIGH);
            delay(75);
            digitalWrite(ledPin5, HIGH);
            delay(75);
            digitalWrite(ledPin6, HIGH);
            delay(100);
            digitalWrite(ledPin7, HIGH);
            delay(100);
            digitalWrite(ledPin8, HIGH);
            delay(125);
            digitalWrite(ledPin9, HIGH);
            delay(125);
            digitalWrite(ledPin9, LOW);
            delay(25);
            digitalWrite(ledPin8, LOW);
            delay(25);
            digitalWrite(ledPin7, LOW);
            delay(50);
            digitalWrite(ledPin6, LOW);
            delay(50);
            digitalWrite(ledPin5, LOW);
            delay(75);
            digitalWrite(ledPin4, LOW);
            delay(75);
            digitalWrite(ledPin3, LOW);
            delay(100);
            digitalWrite(ledPin2, LOW);
            delay(100);
            digitalWrite(ledPin1, LOW);
            delay(125);
            digitalWrite(ledPin9, LOW);
            delay(125);
        }
    }

    void sequence2()
    {
        int vuelta;
        for (vuleta = 0; vuelta < 3; vuelta = vuelta + 1)
        {
            digitalWrite(ledPin0, HIGH);
            delay(25);
            digitalWrite(ledPin9, HIGH);
            delay(25);
            digitalWrite(ledPin1, HIGH);
            delay(50);
            digitalWrite(ledPin8, HIGH);
            delay(50);
            digitalWrite(ledPin3, HIGH);
            delay(75);
            digitalWrite(ledPin7, HIGH);
            delay(75);
            digitalWrite(ledPin3, HIGH);
            delay(100);
            digitalWrite(ledPin6, HIGH);
            delay(100);
            digitalWrite(ledPin4, HIGH);
            delay(125);
            digitalWrite(ledPin5, HIGH);
            delay(125);
            digitalWrite(ledPin0, LOW);
            delay(25);
            digitalWrite(ledPin9, LOW);
            delay(25);
            digitalWrite(ledPin1, LOW);
            delay(50);
            digitalWrite(ledPin8, LOW);
            delay(50);
            digitalWrite(ledPin2, LOW);
            delay(75);
            digitalWrite(ledPin7, LOW);
            delay(75);
            digitalWrite(ledPin3, LOW);
            delay(100);
            digitalWrite(ledPin6, LOW);
            delay(100);
            digitalWrite(ledPin4, LOW);
            delay(125);
            digitalWrite(ledPin5, LOW);
            delay(125);
        }
    }

    void sequence3()
    {
        int vuelta;
        for (vuleta = 0; vuelta < 3; vuelta = vuelta + 1)
        {
            digitalWrite(ledPin0, HIGH);
            delay(25);
            digitalWrite(ledPin2, HIGH);
            delay(25);
            digitalWrite(ledPin4, HIGH);
            delay(50);
            digitalWrite(ledPin6, HIGH);
            delay(50);
            digitalWrite(ledPin8, HIGH);
            delay(75);
            digitalWrite(ledPin1, HIGH);
            delay(75);
            digitalWrite(ledPin3, HIGH);
            delay(100);
            digitalWrite(ledPin5, HIGH);
            delay(100);
            digitalWrite(ledPin7, HIGH);
            delay(125);
            digitalWrite(ledPin9, HIGH);
            delay(125);
            digitalWrite(ledPin0, LOW);
            delay(25);
            digitalWrite(ledPin2, LOW);
            delay(25);
            digitalWrite(ledPin4, LOW);
            delay(50);
            digitalWrite(ledPin6, LOW);
            delay(50);
            digitalWrite(ledPin8, LOW);
            delay(75);
            digitalWrite(ledPin1, LOW);
            delay(75);
            digitalWrite(ledPin3, LOW);
            delay(100);
            digitalWrite(ledPin5, LOW);
            delay(100);
            digitalWrite(ledPin7, LOW);
            delay(125);
            digitalWrite(ledPin9, LOW);
            delay(125);
        }
    }

    void felicidades()
    {
        lcd.clear();
        int rando = random(15);
        switch (rando)
        {
        case 1:
            lcd.print("Muy bien!");
            break;
        case 2:
            lcd.print("Bien hecho!") break;
        case 3:
            lcd.print("Excelente!");
            break;
        case4:
            lcd.print("Genial!");
            break;
        case 5:
            lcd.print("Buen trabajo");
            break;
        }

        randSeq = random(1, 3);
        if (randSeq == 1)
        {
            sequence1();
        }
        if (randSeq == 2)
        {
            sequence2();
        }
        if (randSeq == 3)
        {
            sequence3();
        }
    }