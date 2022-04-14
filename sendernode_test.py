import unittest
import os
import sendernode

ANALOG2DIGITAL_MAX_VAL = 4094
BATTERYTEMPERATURE_MIN_CELSIUS = 0
BATTERYTEMPERATURE_MAX_CELSIUS = 100
CELSIUSTOFARENHEIT_CONVERSIONPARAMETER = 1.8
MAX_NO_OF_DATATOBESTREAMED = 50

class test_sendernode(unittest.TestCase):

    def testcase_getADCsensorvalue(self):
        self.assertTrue(sendernode.getADCsensorvalue() in range(0,ANALOG2DIGITAL_MAX_VAL))

    def testcase_convertADCvalueTo16BitResolution(self):
        self.assertTrue(sendernode.convertADCvalueTo16BitResolution(4000) == 16)

    def testcase_getBatteryTemperatureinCelcius(self):
        self.assertTrue(sendernode.getBatteryTemperatureinCelcius() in range(BATTERYTEMPERATURE_MIN_CELSIUS,BATTERYTEMPERATURE_MAX_CELSIUS))
    
    def testcase_convertCelciusToFarenheit(self):
        self.assertTrue(sendernode.convertCelciusToFarenheit(90) == 194.0)
    
    def testcase_formatOutputString(self):
        self.assertTrue(sendernode.formatOutputString(4000,90) == True)
    
    def testcase_printOnConsole(self):
        self.assertTrue(sendernode.printOnConsole('{ BATTERYAPMS:16, BATTERYTEMPERATURE:194}') == True)

    def testcase_senderstream_BMSdata(self):
        self.assertTrue(sendernode.senderstream_BMSdata(50) == 50)

    def test_main(self):
        result = os.system("python sendernode.py")
        self.assertEqual(result, 0)

if __name__ == '__main__':
  unittest.main()
