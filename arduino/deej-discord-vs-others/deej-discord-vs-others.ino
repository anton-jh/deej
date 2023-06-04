const int NUM_SLIDERS = 2;
const int analogInputs[1] = {A0};

int analogSliderValues[NUM_SLIDERS];

void setup()
{
    for (int i = 0; i < NUM_SLIDERS; i++)
    {
        pinMode(analogInputs[i], INPUT);
    }

    Serial.begin(9600);
}

void loop()
{
    updateSliderValues();
    sendSliderValues(); // Actually send data (all the time)
    // printSliderValues(); // For debug
    delay(10);
}

void updateSliderValues()
{
    analogSliderValues[0] = analogRead(analogInputs[0]);
    analogSliderValues[1] = 1023 - analogRead(analogInputs[0]);

    // analogSliderValues[0] = min(map(analogRead(analogInputs[0]), 0, 512, 0, 1023), 1023);
    // analogSliderValues[1] = 1023 - max(map(analogRead(analogInputs[0]), 512, 1023, 0, 1023), 0);
}

void sendSliderValues()
{
    String builtString = String("");

    for (int i = 0; i < NUM_SLIDERS; i++)
    {
        builtString += String((int)analogSliderValues[i]);

        if (i < NUM_SLIDERS - 1)
        {
            builtString += String("|");
        }
    }

    Serial.println(builtString);
}

void printSliderValues()
{
    for (int i = 0; i < NUM_SLIDERS; i++)
    {
        String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
        Serial.write(printedString.c_str());

        if (i < NUM_SLIDERS - 1)
        {
            Serial.write(" | ");
        }
        else
        {
            Serial.write("\n");
        }
    }
}
