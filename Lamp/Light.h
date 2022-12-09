#pragma once

class Light {
	CallbackArgs<int> _levelChanged;

	int _pin;
	int _level;
	int _actualLevel;
	int _startLevel;
	time_t _transitionStart;
	time_t _transitionTime;

public:
	Light() : _pin(-1), _level(0), _actualLevel(0), _startLevel(0), _transitionStart(0), _transitionTime(0) {
	}

	void begin(uint8_t pin) {
		_pin = pin;

		pinMode(pin, OUTPUT);

		resetTransition();
	}

	bool isOn() {
		return !!_level;
	}
	int getLevel() {
		return _level;
	}
	void onLevelChanged(CallbackArgs<int>::Func func, uintptr_t data = 0) {
		_levelChanged.set(func, data);
	}

	void update() {
		if (_pin == -1 || !_transitionStart) {
			return;
		}

		auto diff = millis() - _transitionStart;

		if (diff >= _transitionTime) {
			resetTransition();
		}
		else {
			// Interpolate the level.

			float progress = float(diff) / float(_transitionTime);

			int level =
				_startLevel +
				int(float(_level - _startLevel) * progress);

			if (level != _actualLevel) {
				_actualLevel = level;
				analogWrite(_pin, _actualLevel);
			}
		}
	}

	void setLevel(int level, time_t time = 0) {
		_level = level;

		if (time == 0) {
			resetTransition();
		}
		else {
			_startLevel = _actualLevel;
			_transitionStart = millis();
			_transitionTime = time;

			// Let update handle setting the value.
		}

		_levelChanged.call(_level);
	}

	void resetTransition() {
		_startLevel = _level;
		_transitionStart = 0;
		_transitionTime = 0;

		if (_actualLevel != _level) {
			_actualLevel = _level;
			analogWrite(_pin, _actualLevel);
		}
	}
};
