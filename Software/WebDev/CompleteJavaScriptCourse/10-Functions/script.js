'use strict';

// const bookings = [];

// const createBooking = function (flightNum, numPassengers = 1, price = 199) {
//   // numPassengers ||= 1;
//   // price ||= 199;

//   const booking = {
//     flightNum,
//     numPassengers,
//     price,
//   };

//   console.log(booking);
//   bookings.push(booking);
// };

// createBooking('LH123', 'yuh');
// createBooking('LH123', undefined, 1000); // skip a default parameter

// const flight = 'LH234';
// const jonas = {
//   name: 'Logan hartford',
//   passport: 10239809234,
// };

// const checkIn = function (flightNum, passenger) {
//   flightNum = 'LH999';
//   passenger.name = 'Mr. ' + passenger.name;

//   if (passenger.passport === 10239809234) {
//     alert('Check in');
//   } else {
//     alert('Worng passport!');
//   }
// };

// // checkIn(flight, jonas);
// // console.log(flight);
// // console.log(jonas);

// const flightNum = flight; // not the original
// const passenger = jonas; // only points to the object in the memory heap

// const newPassport = function (person) {
//   person.passport = Math.trunc(Math.random() * 1000000000);
// };

// newPassport(jonas);
// checkIn(flight, jonas);

// JavaScript does not have pass by referance
// can pass in a value that is a memeory address however

// // Higher Order Functions
// const oneWord = function (str) {
//   return str.replace(/ /g, '').toLowerCase();
// };

// const upperFirstWord = function (str) {
//   const [first, ...others] = str.split(' ');
//   return [first.toUpperCase(), ...others].join(' ');
// };

// const transformer = function (str, fn) {
//   console.log(`Original string ${str}`);
//   console.log(`Transformed string: ${fn(str)}`);

//   console.log(`Transformed by: ${fn.name}`);
// };

// transformer('JavaScript is the best!', upperFirstWord);
// transformer('JavaScript is the best!', oneWord);

// // JS use callbacks all the time
// const high5 = function () {
//   console.log('✋');
// };

// // document.body.addEventListener('click', high5);

// ['Jonas', 'Martha', 'Adam'].forEach(high5);

// // Fucntions returning fucntions
// const greet = function (greeting) {
//   return function (name) {
//     console.log(`${greeting} ${name}`);
//   };
// };

// const greeter = greet('Hey');
// greeter('Logan');
// greeter('Fatty');

// greet('Hello')('Jenn');

// const greet_ = greeting => name => console.log(`New: ${greeting} ${name}`);

// greet_('Suuuuh')('Homie G');

// // The call and apply methods

// const lufthansa = {
//   airline: 'Lufthansa',
//   iataCode: 'LH',
//   bookings: [],
//   book(flighNum, name) {
//     console.log(
//       `${name} booked a seat on ${this.airline} flight ${this.iataCode}${flighNum}`
//     );
//     this.bookings.push({
//       flight: `${name} booked a seat on ${this.airline} flight ${this.iataCode}${flighNum}`,
//       name,
//     });
//   },
// };

// lufthansa.book(239, 'Logan Hartford');
// lufthansa.book(339, 'sucky sucky');

// const eurowings = {
//   airline: 'Eurowings',
//   iataCode: 'EW',
//   bookings: [],
// };

// const book = lufthansa.book;

// // DOES NOT WORK
// // book(23, 'Sarah Williams');
// book.call(eurowings, 23, 'Sarah Williams'); // Set 'this' to the first argument
// book.call(lufthansa, 239, 'Mary Cooper');
// console.log(lufthansa);

// const swiss = {
//   airline: 'Swiss Air Lines',
//   iataCode: 'LX',
//   bookings: [],
// };

// book.call(swiss, 616, 'Jesus');

// // Apply method
// const flightData = [583, 'George Cooper'];
// book.apply(swiss, flightData);
// console.log(swiss);

// book.call(swiss, ...flightData); // same as apply

// // Bind mehtod
// const bookEW = book.bind(eurowings); // returns a fucntion with 'this' bound to eurowings
// const bookLH = book.bind(lufthansa);
// const bookLX = book.bind(swiss);

// bookEW(777, 'Lucky Jack');

// const bookEW23 = book.bind(eurowings, 23); // sets the first argument as well
// bookEW23('Just a name');

// // With Event Listeners

// lufthansa.planes = 300;
// lufthansa.buyPlane = function () {
//   console.log(this);

//   this.planes++;
//   console.log(this.planes);
// };

// document
//   .querySelector('.buy')
//   .addEventListener('click', lufthansa.buyPlane.bind(lufthansa));

// // Partial application
// const addTax = (rate, value) => value + value * rate;
// console.log(addTax(0.01, 200));

// const addVAT = addTax.bind(null, 0.23);
// // const addVAT = (value) => value + value * 0.23;

// console.log(addVAT(100));

// // const specify = (fn, value) => fn(value);
// // const addHST = specify(addTax, 0.13);
// // console.log(addHST(100));
// const addTaxRate = function (rate) {
//   return function (value) {
//     return value + value * rate;
//   };
// };

// const addHST = addTaxRate(0.13);
// console.log(addHST(100));

// Coding Challange #1
const poll = {
  question: 'What is your favorite programming language?',
  options: ['0: JavaScript', '1: Python', '2: Rust', '3: C++'],
  answers: new Array(4).fill(0), // [0, 0, 0, 0]
  registerNewAnswer() {
    const i = Number(
      prompt(
        `${this.question}\n${this.options.join('\n')}\n(Write option number)`
      )
    );
    typeof i === 'number' &&
      i >= 0 &&
      i < this.answers.length &&
      this.answers[i]++;
    this.displayResults();
  },
  displayResults(input = 'array') {
    if (input === 'string') {
      console.log(`Pole results are ${this.answers.join(', ')}`);
    } else {
      console.log(this.answers);
    }
  },
};

document
  .querySelector('.poll')
  .addEventListener('click', poll.registerNewAnswer.bind(poll));

// poll.displayResults.call({ answers: [5, 2, 3] });
// poll.displayResults.call({ answers: [1, 5, 3, 9, 6, 1] });

// Immediately invoked function expressions [IIFE]
const runOnce = function () {
  console.log('this will never run again');
};
runOnce();

(function () {
  console.log('This will never run again');
})();

(() => console.log('This will never run again'))();

{
  const isPrivate = 23;
  var notPrivate = 46;
}
// console.log(isPrivate);
console.log(notPrivate);

// Closures
//const passengerCount = 99;
const secureBooking = function () {
  let passengerCount = 0;

  return function () {
    passengerCount++;
    console.log(`${passengerCount} passengers`);
  };
};

const booker = secureBooking();

booker();
booker();
booker();
booker();
console.dir(booker);

// Example 1
let f;

const g = function () {
  const a = 23;
  f = function () {
    console.log(a * 2);
  };
};

const h = function () {
  const b = 777;
  f = function () {
    console.log(b * 2);
  };
};

g();
f();
console.dir(f);
// Re-assigning f function
h();
f();
console.dir(f);

// Example 2
const boardPassengers = function (n, wait) {
  const perGroup = n / 3;

  setTimeout(function () {
    console.log(`We are now boarding all ${n} passengers`);
    console.log(`There are 3 groups each with ${perGroup} passengers`);
  }, wait * 1000);

  console.log(`Will start boarding in ${wait} seconds`);
};

const perGroup = 1000;
boardPassengers(180, 3);

// Coding Challange #2
(function () {
  const header = document.querySelector('h1');
  const body = document.querySelector('body');
  body.addEventListener('click', function () {
    header.style.color = 'red';
  });
})();
// the function is attached to the body and has access to the variables present in the scope in which it was created due to closure
