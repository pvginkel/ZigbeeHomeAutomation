const fz = require("zigbee-herdsman-converters/converters/fromZigbee");
const tz = require("zigbee-herdsman-converters/converters/toZigbee");
const exposes = require("zigbee-herdsman-converters/lib/exposes");
const reporting = require("zigbee-herdsman-converters/lib/reporting");
const extend = require("zigbee-herdsman-converters/lib/extend");
const e = exposes.presets;
const ea = exposes.access;

const fzLocal = {
  illuminance: {
    cluster: 'msIlluminanceMeasurement',
    type: ['attributeReport', 'readResponse'],
    options: [
      exposes.options.calibration('illuminance', 'percentual'),
      exposes.options.calibration('illuminance_lux', 'percentual'),
      exposes.options.calibration('illuminance_33k', 'percentual'),
      exposes.options.calibration('illuminance_33k_lux', 'percentual'),
      exposes.options.calibration('illuminance_60k', 'percentual'),
      exposes.options.calibration('illuminance_60k_lux', 'percentual'),
      exposes.options.calibration('illuminance_200k', 'percentual'),
      exposes.options.calibration('illuminance_200k_lux', 'percentual'),
    ],
    convert: (model, msg, publish, options, meta) => {
      const readValue = (attribute, name) => {
        if (msg.data.hasOwnProperty(attribute)) {
          const raw = msg.data[attribute];
          const VIN = 5.0;
          const R = 10000;
          
          // Conversion analog to voltage
          const Vout = raw * (VIN / 1023);
          // Conversion voltage to resistance
          const RLDR = (R * (VIN - Vout)) / Vout;
          // Conversion resitance to lumen
          const phys = 500 / (RLDR / 1000);
  
          result[name] = RLDR | 0;
          result[name + '_lux'] = phys | 0;
        }
      };

      const result = {};
      readValue('measuredValue', 'illuminance');
      readValue(0x0201, 'illuminance_33k');
      readValue(0x0202, 'illuminance_60k');
      readValue(0x0203, 'illuminance_200k');
      return result;
    }
  }
};

const definition = {
  zigbeeModel: ["Sensors"],
  model: "Sensors",
  vendor: "Pieter",
  description: "Temperature, humidity and photoresistor sensors",
  fromZigbee: [fz.temperature, fz.humidity, fzLocal.illuminance],
  toZigbee: [],
  exposes: [
    e.temperature(),
    e.humidity(),
    e.illuminance(),
    e.illuminance_lux(),
    exposes.numeric('illuminance_33k', ea.STATE).withDescription('Raw measured illuminance for 33K Ω photoresistor'),
    exposes.numeric('illuminance_33k_lux', ea.STATE).withUnit('lx').withDescription('Measured illuminance in lux for 33K Ω photoresistor'),
    exposes.numeric('illuminance_60k', ea.STATE).withDescription('Raw measured illuminance for 60K Ω photoresistor'),
    exposes.numeric('illuminance_60k_lux', ea.STATE).withUnit('lx').withDescription('Measured illuminance in lux for 60K Ω photoresistor'),
    exposes.numeric('illuminance_200k', ea.STATE).withDescription('Raw measured illuminance for 200K Ω photoresistor'),
    exposes.numeric('illuminance_200k_lux', ea.STATE).withUnit('lx').withDescription('Measured illuminance in lux for 200K Ω photoresistor'),
  ],
};

module.exports = definition;