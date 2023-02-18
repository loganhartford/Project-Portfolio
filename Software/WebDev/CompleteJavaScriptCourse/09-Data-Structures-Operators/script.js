'use strict';

// Data needed for a later exercise

const weekdays = ['mon', 'tues', 'wed', 'thrus', 'fri', 'sat', 'sun'];

const hours = {
  [weekdays[3]]: {
    open: 12,
    close: 22,
  },
  [weekdays[4]]: {
    open: 11,
    close: 23,
  },
  [weekdays[5]]: {
    open: 0, // Open 24 hours
    close: 24,
  },
};

// Data needed for first part of the section
const restaurant = {
  name: 'Classico Italiano',
  location: 'Via Angelo Tavanti 23, Firenze, Italy',
  categories: ['Italian', 'Pizzeria', 'Vegetarian', 'Organic'],
  starterMenu: ['Focaccia', 'Bruschetta', 'Garlic Bread', 'Caprese Salad'],
  mainMenu: ['Pizza', 'Pasta', 'Risotto'],

  // ES6 enhances object literals
  hours,

  order(starterIndex, mainIndex) {
    return [this.starterMenu[starterIndex], this.mainMenu[mainIndex]];
  },

  // Destructing an oject as a fucntion argument
  orderDelivery({ starterIndex = 1, mainIndex = 0, time = '20:00', address }) {
    console.log(
      `Order recieved: ${this.starterMenu[starterIndex]} and ${this.mainMenu[mainIndex]} will be delivered to ${address} at ${time}`
    );
  },

  orderPasta(ing1, ing2, ing3) {
    console.log(`Here is you delicious pasta with ${ing1}, ${ing2}, ${ing3}.`);
  },

  orderPizza(mainIngredient, ...otherIngredients) {
    console.log(mainIngredient, otherIngredients);
  },
};

// String Methods Practice
const flights =
  '_Delayed_Departure;fao93766109;txl2133758440;11:25+_Arrival;bru0943384722;fao93766109;11:45+_Delayed_Arrival;hel7439299980;fao93766109;12:05+_Departure;fao93766109;lis2323639855;12:30';

const getCode = str => str.slice(0, 3).toUpperCase();

for (const flight of flights.split('+')) {
  const [type, from, to, time] = flight.split(';');
  const output = `${type.startsWith('_Delayed') ? '⛔' : ''}${type.replaceAll(
    '_',
    ' '
  )} from ${getCode(from)} to ${getCode(to)} (${time.replace(
    ':',
    'h'
  )})`.padStart(50);
  console.log(output);
}

// // Coding Challange #4
// document.body.append(document.createElement('textarea'));
// document.body.append(document.createElement('button'));

// document.querySelector('button').addEventListener('click', function () {
//   const text = document.querySelector('textarea').value.toLowerCase();
//   let words = text.split('\n');
//   let moreWords = [];
//   for (let i = 0; i < words.length; i++) {
//     moreWords = words[i].trim().split('_');
//     words[i] = [
//       moreWords[0],
//       moreWords[1].replace(moreWords[1][0], moreWords[1][0].toUpperCase()),
//     ].join('');
//     console.log(words[i].padEnd(20, ' ').padEnd(20 + i + 1, '✅'));
//   }
// });

// // Working with strings part 3
// console.log('a+very+nice+string'.split('+'));
// console.log('Logan Hartford'.split(' '));

// const [firstName, lastName] = 'Logan Hartford'.split(' ');

// const newName = ['Mr.', firstName, lastName.toUpperCase()].join(' ');
// console.log(newName);

// const capitalizeName = function (name) {
//   const names = name.toLowerCase().split(' ');
//   const namesUpper = [];

//   for (const n of names) {
//     // namesUpper.push(n[0].toUpperCase() + n.slice(1));
//     namesUpper.push(n.replace(n[0], n[0].toUpperCase()));
//   }
//   const newName = namesUpper.join(' ');
//   console.log(newName);
// };

// const passenger = 'jessica ann smith davis';
// capitalizeName(passenger);
// capitalizeName('logan allen patrick hartford');

// // Padding
// const message = 'Go to gate 23!';
// console.log(message.padStart(25, '+').padEnd(35, '+'));

// const maskCreditCard = function (number) {
//   const str = number + ''; // convert to string
//   const last = str.slice(-4);
//   return last.padStart(str.length, '*');
// };
// console.log(maskCreditCard(5658451297549754));
// console.log(maskCreditCard('5658451297549754'));

// // Repeat
// const message2 = 'Bad weather... All depatrues delayed...';
// console.log(message2.repeat(5));

// const planesInLine = function (n) {
//   console.log(`There are ${n} planes in line ${'✈️'.repeat(n)}`);
// };
// planesInLine(5);

// // Working with string part 2
// const airline = 'TAP Air Portugal';
// const plane = 'A320';
// console.log(airline.toLowerCase());
// console.log(airline.toUpperCase());

// // Fix captilization in name
// const passenger = 'lOgAN';
// const passengerLower = passenger.toLowerCase();
// const passengerCorrect =
//   passengerLower[0].toUpperCase() + passengerLower.slice(1);
// console.log(passengerCorrect);

// // Check email
// const email = 'hello@jonas.io';
// const loginEmail = ' Hello@Jonas.Io \n';

// const lowerEmail = loginEmail.toLowerCase();
// const trimmedEmail = lowerEmail.trim();
// console.log(trimmedEmail);

// const normailizeEmail = loginEmail.toLowerCase().trim();
// console.log(normailizeEmail);
// console.log(email === normailizeEmail);
// // trimStart and trimEnd are olso a thing

// // Replacing
// const priceGB = '288,97#';
// const priceUS = priceGB.replace('#', '$').replace(',', '.');
// console.log(priceUS);

// const announcement =
//   'All passengers come to boarding door 23. Boarding door 23!';
// console.log(announcement.replaceAll('door', 'gate'));

// console.log(announcement.replaceAll(/door/g, 'gate'));

// // Booleans
// const plane2 = 'A320neo';
// console.log(plane2.includes('A320'));
// console.log(plane2.startsWith('A3'));
// console.log(plane2.endsWith('neo'));

// if (plane2.startsWith('A') && plane2.endsWith('neo')) {
//   console.log('Part of the NEW Airbus fam');
// }

// // Practice excersice
// const checkBaggage = function (items) {
//   const baggage = items.toLowerCase();
//   if (baggage.includes('knife') || baggage.includes('gun')) {
//     console.log('You are NOT allowed onboard');
//   } else {
//     console.log('Welcom Abord!');
//   }
// };

// checkBaggage('Ihave a laptop, some food and a pocket knife');
// checkBaggage('Socks and camera');
// checkBaggage('Got some snacks and a gun for protection');

// // Working with strings
// console.log(plane[0]);
// console.log(plane[1]);
// console.log(plane[2]);
// console.log('B737'[0]);
// console.log(airline.length);
// console.log('B737'.length);

// console.log(airline.indexOf('r'));
// console.log(airline.lastIndexOf('r'));
// console.log(airline.indexOf('Portugal'));
// console.log(airline.indexOf('portugal'));

// console.log(airline.slice(4));
// console.log(airline.slice(4, 7));

// console.log(airline.slice(0, airline.indexOf(' ')));
// console.log(airline.slice(airline.lastIndexOf(' ') + 1));

// console.log(airline.slice(-2));
// console.log(airline.slice(1, -2));

// const checkMiddleSeat = function (seat) {
//   // B and E are middle seats
//   const s = seat.slice(-1);
//   if (s === 'B' || s === 'E') {
//     console.log('You got the middle seat');
//   } else {
//     console.log('Fuck you');
//   }
// };

// checkMiddleSeat('11B');
// checkMiddleSeat('23C');
// checkMiddleSeat('3E');

// Coding Challange #3
const gameEvents = new Map([
  [17, '⚽️ GOAL'],
  [36, '🔁 Substitution'],
  [47, '⚽️ GOAL'],
  [61, '🔁 Substitution'],
  [64, '🔶 Yellow card'],
  [69, '🔴 Red card'],
  [70, '🔁 Substitution'],
  [72, '🔁 Substitution'],
  [76, '⚽️ GOAL'],
  [80, '⚽️ GOAL'],
  [92, '🔶 Yellow card'],
]);

// // 1.
// let events = [...new Set(gameEvents.values())];
// console.log(events);

// // 2.
// gameEvents.delete(64);
// console.log(gameEvents);

// // 3.
// const average = [...gameEvents.keys()].pop() / gameEvents.size;
// console.log(`An event happened on average, every ${average} minutes`);

// // 4.
// for (const [key, value] of gameEvents) {
//   console.log(
//     `${key < 45 ? '[FIRST HALF]' : '[SECOND HALF]'} ${key}: ${value}}`
//   );
// }

// // Map Ineration
// const question = new Map([
//   ['question', 'What is the best programming language in the world?'],
//   [1, 'C'],
//   [2, 'Java'],
//   [3, 'JavaScript'],
//   ['correct', 3],
//   [true, 'Correct!'],
//   [false, 'Try again!'],
// ]);
// console.log(question);

// // convert object to map
// console.log(Object.entries(hours));
// const hoursMap = new Map(Object.entries(hours));
// console.log(hoursMap);

// for (const [key, value] of question) {
//   if (typeof key === 'number') {
//     console.log(`Answer ${key}: ${value}`);
//   }
// }

// //const answer = prompt('Your answer');
// const answer = 3;
// console.log(answer);
// console.log(question.get(question.get('correct') === Number(answer)));

// // Map back to an array
// console.log(...question);
// console.log(question.entries());
// console.log(question.keys());
// console.log(question.values());

// // Maps
// const rest = new Map();
// rest.set('name', 'Classico Italiano');
// rest.set(1, 'Firenze, Italy');
// console.log(rest.set(2, 'Lisbon, Portugal'));

// rest
//   .set('catagories', ['Italian', 'Pizzeria', 'Vegetarian', 'Organic'])
//   .set('open', 11)
//   .set('close', 23)
//   .set(true, 'We are open :D')
//   .set(false, 'we are clsoed D:');

// console.log(rest.get('name'));
// console.log(rest.get(true));

// const time = 21;
// console.log(rest.get(time > rest.get('open') && time < rest.get('close')));

// console.log(rest.has('catagories'));
// console.log(rest);
// console.log(rest.delete(2));
// console.log(rest);
// console.log(rest.size);
// // console.log(rest.clear());

// const arr = [1, 2];
// rest.set(arr, 'Test');
// console.log(rest.get(arr));

// rest.set(document.querySelector('h1'), 'Heading');
// console.log(rest);

// // Sets
// const ordersSet = new Set([
//   'Pasta',
//   'Pizza',
//   'Pizza',
//   'Risotto',
//   'Pasta',
//   'Pizza',
// ]);
// console.log(ordersSet);

// console.log(new Set('Logan'));

// console.log(ordersSet.size);
// console.log(ordersSet.has('Pizza'));
// console.log(ordersSet.has('Bread'));
// ordersSet.add('Garlic');
// ordersSet.add('Garlic');
// console.log(ordersSet);
// ordersSet.delete('Risotto');
// console.log(ordersSet);
// // ordersSet.clear();
// console.log(ordersSet);

// for (const order of ordersSet) console.log(order);

// // Example: removing duplicates in an array
// const staff = ['Waiter', 'Chef', 'Waiter', 'Manager', 'Chef', 'Waiter'];
// const staffUnique = [...new Set(staff)];
// console.log(staffUnique);
// console.log(
//   new Set(['Waiter', 'Chef', 'Waiter', 'Manager', 'Chef', 'Waiter']).size
// );

// console.log(new Set('loganhartford').size);

const game = {
  team1: 'Bayern Munich',
  team2: 'Borrussia Dortmund',
  players: [
    [
      'Neuer',
      'Pavard',
      'Martinez',
      'Alaba',
      'Davies',
      'Kimmich',
      'Goretzka',
      'Coman',
      'Muller',
      'Gnarby',
      'Lewandowski',
    ],
    [
      'Burki',
      'Schulz',
      'Hummels',
      'Akanji',
      'Hakimi',
      'Weigl',
      'Witsel',
      'Hazard',
      'Brandt',
      'Sancho',
      'Gotze',
    ],
  ],
  score: '4:0',
  scored: ['Lewandowski', 'Gnarby', 'Lewandowski', 'Hummels'],
  date: 'Nov 9th, 2037',
  odds: {
    team1: 1.33,
    x: 3.25,
    team2: 6.5,
  },
};

// // Coding Challenge #2
// // 1.
// for (const [i, el] of game.scored.entries()) {
//   console.log(`Goal ${i + 1}: ${el}`);
// }

// // 2.
// let sum = 0;
// for (const odd of Object.values(game.odds)) {
//   sum += odd;
// }
// console.log(sum);
// sum /= Object.values(game.odds).length;
// console.log(sum);

// // 3.
// for (const [key, value] of Object.entries(game.odds)) {
//   console.log(`Odd victory ${game[key] ?? 'draw'}: ${value}`);
// }

// // Bonus
// const scorers = {};
// for (const player of game.scored) {
//   scorers[player] &&= scorers[player] + 1;
//   scorers[player] ??= 1;
// }
// console.log(scorers);

/////////////////////////////////
// // Property Names
// const properties = Object.keys(hours);
// console.log(properties);

// let openStr = `We are opend on ${properties.length} days: `;
// for (const day of Object.keys(hours)) {
//   openStr += `${day}, `;
// }
// console.log(openStr);

// // Property Values
// const values = Object.values(hours);
// console.log(values);

// // Property entries --  entire object
// const entries = Object.entries(hours);
// console.log(entries);

// // [key, value]
// for (const [key, { open, close }] of entries) {
//   console.log(`On ${key} we open at ${open} and close at ${close}.`);
// }

/////////////////////////////////////////////////
// console.log(restaurant);
// if (restaurant.hours && restaurant.hours.mon)
//   console.log(restaurant.hours.mon.open);

// // WITH optional chaining
// console.log(restaurant.hours.mon?.open);
// // console.log(restaurant.hours.mon.open); // ERROR
// console.log(restaurant.hours?.mon?.open);

// // Example
// const days = ['mon', 'tues', 'wed', 'thrus', 'fri', 'sat', 'sun'];
// for (const day of days) {
//   console.log(day);
//   const open = restaurant.hours[day]?.open ?? 'closed';
//   console.log(`On ${day}, we open at ${open}`);
// }

// // Methods
// console.log(restaurant.order?.(0, 1) ?? 'Method does not exist');
// console.log(restaurant.orderRisotto?.(0, 1) ?? 'Method does not exist');

// // Arrays
// let users = [{ name: 'logan', email: 'logan@logan' }];
// console.log(users[0].name ?? 'User array empty');

/////////////////////////////////////////////
// const menu = [...restaurant.starterMenu, ...restaurant.mainMenu];

// for (const item of menu) console.log(item);

// for (const [i, el] of menu.entries()) {
//   console.log(`${i + 1}: ${el}`);
// }
// // console.log([...menu.entries()]);

// Coding Challenge #1

// const [players1, players2] = game.players;
// console.log(players1, players2);

// const [gk, ...fieldPlayers] = players1;
// console.log(gk, fieldPlayers);

// const allPlayers = [...players1, ...players2];
// console.log(allPlayers);

// const playersFinal = [...players1, 'Thiago', 'Coutinho', 'Perisic'];
// console.log(playersFinal);

// const { team1, x: draw, team2 } = game.odds;
// console.log(team1, draw, team2);

// function printGoals(...names) {
//   for (let i = 0; i < names.length; i++) {
//     console.log(names[i]);
//   }
// }
// printGoals('Logan', 'Jonas', 'Jeff');

// // --------------------- //
// // How to print conditionally //
// team1 < team2 && console.log('Team 1 is more likely to win');
// team1 > team2 && console.log('Team 2 is more likely to win');

/////////////////////////////////////
// const rest1 = {
//   name: 'capri',
//   // numGuests: 20,
//   numGuests: 0,
// };

// const rest2 = {
//   name: 'La Piazza',
//   owner: 'Giovanni Rossi',
// };

// // Or assignment operator
// // rest1.numGuests = rest1.numGuests || 10;
// // rest2.numGuests = rest2.numGuests || 10;
// // rest1.numGuests ||= 10;
// // rest2.numGuests ||= 10;

// // Nullish assignment operator
// rest1.numGuests ??= 10;
// rest2.numGuests ??= 10;

// // And assignment operator
// // rest1.owner = rest1.owner && '<ANONYMOUS>';
// // rest2.owner = rest2.owner && '<ANONYMOUS>';
// rest1.owner &&= '<ANONYMOUS>';
// rest2.owner &&= '<ANONYMOUS>';

// console.log(rest1);
// console.log(rest2);

///////////////////////////////////////////////////
// // Use any data type, can return any data typs,
// // short circuiting
// // if first value is truthy it doesn't look at the second
// console.log('---- OR ----');
// console.log(3 || 'Logan');
// console.log('' || 'Logan');
// console.log(true || 0);
// console.log(undefined || null);

// console.log(undefined || 0 || '' || 'Hello' || 23 || null);

// restaurant.numGuests = 23;

// const guests1 = restaurant.numGuests ? restaurant.numGuests : 10;
// console.log(guests1);

// const guests2 = restaurant.numGuests || 10;
// console.log(guests2);

// console.log('---- AND ----');

// console.log(0 && 'Logan');
// console.log(7 && 'Logan');

// console.log('hello' && 23 && null && 'Logan');

// if (restaurant.orderPizza) {
//   restaurant.orderPizza('mushrooms', 'spinach');
// }

// restaurant.orderPizza && restaurant.orderPizza('mushrooms', 'spinach');

// // Nullish Coalescing Operator
// console.log('---- ?? -----');
// restaurant.numGuests = 0;
// const guests = restaurant.numGuests ? restaurant.numGuests : 10;
// console.log(guests);

// // Nullish: null and undifined
// const guestsCorrect = restaurant.numGuests ?? 10;
// console.log(guestsCorrect);

//////////////////////////////////////
// // 1) Destructuring

// // Rest operator
// // SPREAD, because on right hand side of equal sign
// const arr = [1, 2, ...[3, 4]];
// console.log(arr);
// // REST, because on left hand side of equal sign
// const [a, b, ...others] = [1, 2, 3, 4, 50];
// console.log(a, b, others);

// const [pizza, , risotto, ...otherFood] = [
//   ...restaurant.mainMenu,
//   ...restaurant.starterMenu,
// ];
// console.log(pizza, risotto, otherFood);

// // Objects
// const { sat, ...weekdays } = restaurant.openingHours;
// console.log(weekdays);

// // 2) Fucntions
// const add = function (...numbers) {
//   console.log(numbers);
//   let sum = 0;
//   for (let i = 0; i < numbers.length; i++) {
//     sum += numbers[i];
//   }
//   console.log(sum);
//   return sum;
// };
// add(2, 3);
// add(5, 3, 7, 10, 20);

// const x = [23, 5, 7];
// add(...x);

// restaurant.orderPizza('Mushrooms', 'pussy', 'salad', 'ketchup');
// restaurant.orderPizza('pepskis');

// /////////////////////////////////////////////////
// const arr = [7, 8, 9];
// const newArr = [1, 2, 3, ...arr];
// const badArr = [1, 2, 3, arr];
// console.log(newArr, badArr);

// console.log(...newArr);

// const newMenu = [...restaurant.mainMenu, 'Gnocci'];
// console.log(newMenu);

// // Copy array
// const mainMenuCopy = [...restaurant.mainMenu];
// console.log(mainMenuCopy);

// // Join arrays
// const menu = [...restaurant.starterMenu, ...restaurant.mainMenu];
// console.log(menu);

// // Iterables: arrays, strings, maps, sets. Not objects
// const str = 'Logan';
// const letters = [...str, ' ', 'H.'];
// console.log(letters);

// // const ingredients = [
// //   prompt("Let's make pasta! Ingredient 1?"),
// //   prompt("Let's make pasta! Ingredient 2?"),
// //   prompt("Let's make pasta! Ingredient 3?"),
// // ];

// // console.log(ingredients);
// // restaurant.orderPasta(...ingredients);

// // Objects
// const newRestaurant = { ...restaurant, founder: 'Guiseppe', foundedIn: 1998 };
// console.log(newRestaurant);

// const restaurantCopy = { ...restaurant };
// restaurantCopy.name = 'Risorante Roma';
// console.log(restaurant.name);
// console.log(restaurantCopy.name);

/////////////////////////////
// restaurant.orderDelivery({
//   time: '22:30',
//   address: '9808 Eloquence Drive',
//   mainIndex: 2,
//   starterIndex: 2,
// });

// // Default Values
// restaurant.orderDelivery({
//   address: '9808 Eloquence Drive',
//   mainIndex: 2,
// });

// // Object destructuring
// const { name, openingHours, categories } = restaurant;
// console.log(name, openingHours, categories);

// const {
//   name: restuarantName,
//   openingHours: hours,
//   categories: tags,
// } = restaurant;
// console.log(restuarantName, hours, tags);

// // Default values
// const { menu = [], starterMenu: starters = [] } = restaurant;
// console.log(menu, starters);

// // Mutating Variables
// let a = 111;
// let b = 999;
// const obj = { a: 23, b: 7, c: 14 };

// ({ a, b } = obj);
// console.log(a, b);

// // Nested Objects
// const {
//   fri: { open: o, close: c },
// } = openingHours;
// console.log(o, c);

/////////////////////////////////////
// const arr = [2, 3, 4];
// const [a, b, c] = arr;
// console.log(a, b, c);
// console.log(arr);

// let [main, , secondary] = restaurant.categories;
// console.log(main, secondary);

// // Swithcing Variables
// // const temp = main;
// // main = secondary;
// // secondary = temp;
// [main, secondary] = [secondary, main];
// console.log(main, secondary);

// const [starter, mainCourse] = restaurant.order(2, 0);
// console.log(starter, mainCourse);

// // Nested destructuring
// const nested = [2, 4, [5, 6]];
// const [i, , j] = nested;
// console.log(i, j);

// const [x, , [y, z]] = nested;
// console.log(x, y, z);

// // Default Values
// const [p = 1, q = 1, r = 1] = [8, 9];
// console.log(p, q, r);
