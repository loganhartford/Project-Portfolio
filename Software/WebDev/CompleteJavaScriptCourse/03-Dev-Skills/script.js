// Remember, we're gonna use strict mode in all scripts now!
'use strict';

// Temperature array problem
const temperatures = [3, -2, -6, -1, 'error', 9, 13, 17, 15, 14, 9, 5];

// How to compute max or min temperatures
// What do do with a sensor error?

// TODO: Find max value in the array
// TODO: Find min value in the array
// TODO: How to ignore errors
// TODO: Find amplitude

const calcAlt = function (temps) {
  let max = temps[0];
  let min = temps[0];
  for (let i = 0; i < temps.length; i++) {
    if (typeof temps[i] !== 'number') continue;
    if (temps[i] > max) max = temps[i];
    if (temps[i] < min) min = temps[i];
  }
  console.log(min, max);
  return max - min;
};
console.log(calcAlt(temperatures));

// Now make it accept two arrays of temp

const calcAltMulti = function (t1, t2) {
  const temps = t1.concat(t2);

  let max = temps[0];
  let min = temps[0];
  for (let i = 0; i < temps.length; i++) {
    if (typeof temps[i] !== 'number') continue;
    if (temps[i] > max) max = temps[i];
    if (temps[i] < min) min = temps[i];
  }
  console.log(min, max);
  return max - min;
};
console.log(calcAltMulti(temperatures, [24, 235, 7]));

// Debugging
const measureKelvin = function () {
  const measurement = {
    type: 'temp',
    unit: 'celcius',
    value: 10, //Number(prompt('Degrees celsisus: ')),
  };
  console.log(typeof measurement.value);
  console.table(measurement);

  const kelvin = measurement.value + 273;
  return kelvin;
};
console.log(measureKelvin());

// Challange #1
const printForcast = function (temps) {
  let forcast = '';
  for (let i = 0; i < temps.length; i++) {
    forcast = forcast + `... ${temps[i]}°C in  ${i + 1} days`;
  }
  console.log(forcast);
};

printForcast([17, 21, 23]);
printForcast([12, 5, -5, 0, 4]);
