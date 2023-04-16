#include "ZigBeeHomeAutomation.h"
#include "ACS712.h"
#include "Bounce2.h"
#include "U8g2lib.h"
#include "Display.h"

constexpr int SCREEN_HEIGHT = 64;
constexpr int SCREEN_WIDTH = 128;

constexpr uint8_t IO_XBEE_IN = 2;
constexpr uint8_t IO_XBEE_OUT = 3;
constexpr uint8_t IO_STATUS_LED = 10;
constexpr uint8_t IO_PB = 9;
constexpr uint8_t IO_RELAY = 5;
constexpr uint8_t IO_AMETER = A7;

ACS712  ACS(IO_AMETER, 5.0, 1023, 185);
StatusControl status;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);
Display display;

void setup() {
	LOG_BEGIN();

	ACS.autoMidPoint();

	//pinMode(IO_STATUS_LED, OUTPUT);
	//digitalWrite(IO_STATUS_LED, 1);
	//pinMode(IO_BUTTON, INPUT);
	pinMode(IO_RELAY, OUTPUT);

	status.onClick([](uintptr_t) {
		digitalWrite(IO_RELAY, !digitalRead(IO_RELAY));
	});

	status.onReset([](uintptr_t) {
	});

	status.setBounce(Bounce(IO_PB, 50));
	status.setLed(IO_STATUS_LED);

	status.onResetCountdown([](int remaining, uintptr_t) {
		if (remaining > 0) {
			display.setStatus(String(F("Resetting in ")) + remaining);
		}
		else if (remaining == 0) {
			display.setStatus(F("Resetting NOW"));
		}
		else {
			display.setStatus(String());
		}
	});

	u8g2.begin();
	display.begin(u8g2, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void loop() {
	status.update();
	display.update();
}

#if 0

constexpr int valueRange = 64;
uint16_t values[valueRange * 2 + 1];

void printValues(int samples) {
	for (int i = 0; i < ARRAY_LENGTH(values); i++) {
		if (i > 0) {
			Serial.print(' ');
		}
		auto value = (int)(((float)values[i] / (float)samples) * 100);
		if (value < 10) {
			Serial.print(' ');
		}
		Serial.print(value);
		values[i] = 0;
	}

	Serial.println();
}

void printGraph(int samples) {
	auto max = values[0];
	for (int i = 1; i < ARRAY_LENGTH(values); i++) {
		if (values[i] > max) {
			max = values[i];
		}
	}

	for (int i = 9; i >= 0; i--) {
		for (int j = 0; j < ARRAY_LENGTH(values); j++) {
			auto value = (int)(((float)values[j] / (float)max) * 100) - 1;
			if (value < i * 10 || value >= (i + 1) * 10) {
				Serial.print(' ');
			}
			else if (value < i * 10 + 5) {
				Serial.print('.');
			}
			else {
				Serial.print('*');
			}
		}
		Serial.println();
	}
}

void loop() {
	auto midPoint = ACS.getMidPoint();

	auto start = millis();
	//constexpr auto sampleInterval = 1000 / 50;
	constexpr auto sampleInterval = 500;
	auto samples = 0;

	while (millis() - start < sampleInterval) {
		samples++;

		auto sample = analogRead(0);

		auto index = sample - (int)midPoint + valueRange;
		if (index >= 0 && index < ARRAY_LENGTH(values)) {
			values[index]++;
		}
	}

	printGraph(samples);
	printValues(samples);
}

#elif 0

void loopx() {
	auto m1 = ACS.mA_AC(50, 5);
	auto m2 = ACS.mA_AC_sampling(50, 5);
	Serial.print("mA:\t");
	Serial.print(m1, 2);
	Serial.print("\t\t");
	Serial.println(m2, 2);
	delay(1000);
}

void loop() {
	digitalWrite(4, 1);
	delay(20);
	digitalWrite(4, 0);
	delay(20);
}

#elif 0

float getAverage(float* values, int count) {
	float result = 0;
	for (int i = 0; i < count; i++) {
		result += values[i];
	}
	return result / (float)count;
}

// perform bubble sort
void bubbleSort(float* array, int size) {

	// loop to access each array element
	for (int step = 0; step < size; ++step) {

		// loop to compare array elements
		for (int i = 0; i < size - step; ++i) {

			// compare two adjacent elements
			// change > to < to sort in descending order
			if (array[i] > array[i + 1]) {

				// swapping elements if elements
				// are not in the intended order
				auto temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
	}
}

float calculateSD(float* data, int count) {
	float mean = getAverage(data, count);
	float standardDeviation = 0.0;

	for (int i = 0; i < count; ++i) {
		standardDeviation += pow(data[i] - mean, 2);
	}

	return sqrt(standardDeviation / 10);
}

volatile uint16_t samples = 0;
volatile float sumSquared = 0;

void getSample() {
	samples++;
	int value = analogRead(A0);
	if (/* _suppresNoise */ false)  //  average 2 samples.
	{
		value = (value + analogRead(A0)) / 2;
	}
	float current = value - ACS.getMidPoint();
	sumSquared += (current * current);
}

float mA_AC_sampling()
{
	auto sum = sqrt(sumSquared / samples);

	float mA = sum * ACS.getmAPerStep();

	DEBUG(sum, ", ", sumSquared, ", ", samples, ", ", ACS.getmAPerStep());

	sumSquared = 0;
	samples = 0;

	return mA;
}

int index = 0;
constexpr int count = 50;
float values[count];

uint32_t start = 0;

void loop() {
	auto frequency = 50.0f;
	uint32_t period = round(1000000UL / frequency);
	auto currentMicros = micros();

	if (currentMicros - start >= period) {
		start = currentMicros;

		auto sample = mA_AC_sampling();
		DEBUG(sample);
		values[index++] = sample;

		if (index >= count) {
			index = 0;

			float average = getAverage(values, count);
			//DEBUG("x1");
			float standardDeviation = calculateSD(values, count);
			//DEBUG("x2");
			bubbleSort(values, count);
			//DEBUG("x3");
			float percentile50 = values[count / 2];
			//DEBUG("x4");
			float percentile95 = values[(int)((float)count * .95)];
			//DEBUG("x5");

			Serial.print(average, 2);
			Serial.print("\t");
			Serial.print(standardDeviation, 2);
			Serial.print("\t");
			Serial.print(percentile50, 2);
			Serial.print("\t");
			Serial.print(percentile95, 2);
			Serial.print("\n");
		}
	}
}

#endif

// -- END OF FILE --