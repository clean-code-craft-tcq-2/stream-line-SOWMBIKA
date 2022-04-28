import random

ANALOG2DIGITAL_MAX_VAL = 4094
BATTERYTEMPERATURE_MIN_CELSIUS = 0
BATTERYTEMPERATURE_MAX_CELSIUS = 100
CELSIUSTOFARENHEIT_CONVERSIONPARAMETER = 1.8
MAX_NO_OF_DATATOBESTREAMED = 50

def getADCsensorvalue():
    return random.randint(0, ANALOG2DIGITAL_MAX_VAL)
  
def convertADCvalueTo16BitResolution(currentADCvalue):
    return round(currentADCvalue*16/ANALOG2DIGITAL_MAX_VAL)

def getBatteryTemperatureinCelcius():
    return random.randint(BATTERYTEMPERATURE_MIN_CELSIUS,BATTERYTEMPERATURE_MAX_CELSIUS)

def convertCelciusToFarenheit(currentTemp_Celcius):
    return round((currentTemp_Celcius * CELSIUSTOFARENHEIT_CONVERSIONPARAMETER) + 32)

def formatOutputString(currentADCvalue,currentTemp_Celcius):
    outputstring = {}
    outputstring = "{" + " BATTERYAPMS:"  + str(convertADCvalueTo16BitResolution(currentADCvalue))
    outputstring = outputstring + "," + " BATTERYTEMPERATURE:"  + str(convertCelciusToFarenheit(currentTemp_Celcius)) + "}"  
    printOnConsole(outputstring)
    return True

def printOnConsole(string):
    print(string)
    return True

def senderstream_BMSdata(streamcount):
    for i in range(streamcount):
        formatOutputString(getADCsensorvalue(),getBatteryTemperatureinCelcius())
    return streamcount

if __name__ == "__main__":
    senderstream_BMSdata(MAX_NO_OF_DATATOBESTREAMED)
