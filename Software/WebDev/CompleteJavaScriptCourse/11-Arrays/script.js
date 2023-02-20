'use strict';

/////////////////////////////////////////////////
/////////////////////////////////////////////////
// BANKIST APP

// Data
const account1 = {
  owner: 'Jonas Schmedtmann',
  movements: [200, 450, -400, 3000, -650, -130, 70, 1300],
  interestRate: 1.2, // %
  pin: 1111,
};

const account2 = {
  owner: 'Jessica Davis',
  movements: [5000, 3400, -150, -790, -3210, -1000, 8500, -30],
  interestRate: 1.5,
  pin: 2222,
};

const account3 = {
  owner: 'Steven Thomas Williams',
  movements: [200, -200, 340, -300, -20, 50, 400, -460],
  interestRate: 0.7,
  pin: 3333,
};

const account4 = {
  owner: 'Sarah Smith',
  movements: [430, 1000, 700, 50, 90],
  interestRate: 1,
  pin: 4444,
};

const accounts = [account1, account2, account3, account4];

// Elements
const labelWelcome = document.querySelector('.welcome');
const labelDate = document.querySelector('.date');
const labelBalance = document.querySelector('.balance__value');
const labelSumIn = document.querySelector('.summary__value--in');
const labelSumOut = document.querySelector('.summary__value--out');
const labelSumInterest = document.querySelector('.summary__value--interest');
const labelTimer = document.querySelector('.timer');

const containerApp = document.querySelector('.app');
const containerMovements = document.querySelector('.movements');

const btnLogin = document.querySelector('.login__btn');
const btnTransfer = document.querySelector('.form__btn--transfer');
const btnLoan = document.querySelector('.form__btn--loan');
const btnClose = document.querySelector('.form__btn--close');
const btnSort = document.querySelector('.btn--sort');

const inputLoginUsername = document.querySelector('.login__input--user');
const inputLoginPin = document.querySelector('.login__input--pin');
const inputTransferTo = document.querySelector('.form__input--to');
const inputTransferAmount = document.querySelector('.form__input--amount');
const inputLoanAmount = document.querySelector('.form__input--loan-amount');
const inputCloseUsername = document.querySelector('.form__input--user');
const inputClosePin = document.querySelector('.form__input--pin');

////////////////////////////////////////////////////////
const displayMovements = function (movements, sort = false) {
  containerMovements.innerHTML = '';

  const movs = sort ? movements.slice().sort((a, b) => a - b) : movements;

  movs.forEach(function (mov, i, arr) {
    const type = mov > 0 ? 'deposit' : 'withdrawal';

    const html = `
    <div class="movements__row">
      <div class="movements__type movements__type--${type}">${
      i + 1
    } ${type}</div>
      <div class="movements__value">${mov}</div>
  </div>`;

    containerMovements.insertAdjacentHTML('afterbegin', html);
  });
};

const calcDisplayBalance = function (acc) {
  acc.balance = acc.movements.reduce((acc, mov) => acc + mov, 0);
  labelBalance.textContent = `${acc.balance} EUR`;
};

const calcDisplaySummary = function (acc) {
  const incomes = acc.movements
    .filter(mov => mov > 0)
    .reduce((acc, mov) => acc + mov, 0);
  labelSumIn.textContent = `${incomes}€`;

  const out = acc.movements
    .filter(mov => mov < 0)
    .reduce((acc, mov) => acc + mov, 0);
  labelSumOut.textContent = `${Math.abs(out)}€`;

  const interest = acc.movements
    .filter(mov => mov > 0)
    .map(mov => mov * acc.interestRate)
    .filter(int => int >= 1)
    .reduce((acc, int) => acc + int, 0);
  labelSumInterest.textContent = `${interest}€`;
};

const createUsernames = function (accs) {
  accs.forEach(function (acc) {
    acc.username = acc.owner
      .toLowerCase()
      .split(' ')
      .map(name => name[0])
      .join('');
  });
};
createUsernames(accounts);

const updateUI = function (acc) {
  // Display movments
  displayMovements(acc.movements);

  // Display balance
  calcDisplayBalance(acc);

  // Display Summary
  calcDisplaySummary(acc);
};

// Event Handlers
let currentAccount;

btnLogin.addEventListener('click', function (e) {
  // Prevent form from submitting
  e.preventDefault();

  currentAccount = accounts.find(
    acc => acc.username === inputLoginUsername.value
  );

  if (currentAccount?.pin === Number(inputLoginPin.value)) {
    // Display UI and Welcom message
    labelWelcome.textContent = `Welcome back, ${
      currentAccount.owner.split(' ')[0]
    }`;

    containerApp.style.opacity = 100;

    // Clear input fields
    inputLoginUsername.value = inputLoginPin.value = '';
    inputLoginUsername.blur();
    inputLoginPin.blur();

    updateUI(currentAccount);
  }
});

btnTransfer.addEventListener('click', function (e) {
  e.preventDefault();
  const amount = Number(inputTransferAmount.value);
  const receiverAcc = accounts.find(
    acc => acc.username === inputTransferTo.value
  );
  inputTransferAmount.value = inputTransferTo.value = '';
  inputTransferAmount.blur();
  inputTransferTo.blur();

  if (
    amount > 0 &&
    receiverAcc &&
    currentAccount.balance >= amount &&
    receiverAcc?.username !== currentAccount.username
  ) {
    // Doint the transfer
    currentAccount.movements.push(-amount);
    receiverAcc.movements.push(amount);

    updateUI(currentAccount);

    console.log('transfer valid');
  }
});

btnClose.addEventListener('click', function (e) {
  e.preventDefault();
  if (
    inputCloseUsername.value === currentAccount.username &&
    Number(inputClosePin.value) === currentAccount.pin
  ) {
    const index = accounts.findIndex(
      acc => acc.username === currentAccount.username
    );

    // Delete account
    accounts.splice(index, 1);

    // Hide UI
    containerApp.style.opacity = 0;
    console.log(accounts);
  }

  inputClosePin.value = inputCloseUsername.value = '';
  inputClosePin.blur();
  inputCloseUsername.blur();
});

btnLoan.addEventListener('click', function (e) {
  e.preventDefault();

  const amount = Number(inputLoanAmount.value);

  if (amount > 0 && currentAccount.movements.some(mov => mov >= amount / 10)) {
    // Add a positive movment
    currentAccount.movements.push(amount);

    // Update UI
    updateUI(currentAccount);

    inputLoanAmount.value = '';
    inputLoanAmount.blur();
  }
});

let sorted = false;
btnSort.addEventListener('click', function (e) {
  e.preventDefault();
  sorted = !sorted;
  displayMovements(currentAccount.movements, sorted);
});

/////////////////////////////////////////////////
/////////////////////////////////////////////////
// LECTURES

/////////////////////////////////////////////////
// let arr = ['a', 'b', 'c', 'd', 'e'];

// // Slice
// console.log(arr.slice(2));
// console.log(arr.slice(2, 4));
// console.log(arr.slice(-2));
// console.log(arr.slice(-1));
// console.log(arr.slice(1, -2));
// console.log(arr.slice());
// console.log([...arr]);

// // SPLICE
// // console.log(arr.splice(2));
// console.log(arr.splice(-1));
// console.log(arr);
// arr.splice(1, 2);
// console.log(arr);

// // REVERSE
// arr = ['a', 'b', 'c', 'd', 'e'];
// const arr2 = ['j', 'i', 'h', 'g', 'f'];
// console.log(arr2.reverse());
// console.log(arr2);

// // CONCAT
// const letters = arr.concat(arr2);
// console.log(letters);
// console.log([...arr, ...arr2]);

// // JOIN
// console.log(letters.join('-'));

// // AT
// const arr = [23, 11, 64];
// console.log(arr[0]);
// console.log(arr.at(0));

// console.log(arr[arr.length - 1]);
// console.log(arr.slice(-1)[0]);
// console.log(arr.at(-1));

// console.log('jonas'.at(-1));

// Looping arrays ForEach
const movements = [200, 450, -400, 3000, -650, -130, 70, 1300];

// for (const [i, movement] of movements.entries()) {
//   if (movement > 0) {
//     console.log(`${i + 1}: You deposited ${Math.abs(movement)}`);
//   } else {
//     console.log(`${i + 1} You withdrew ${Math.abs(movement)}`);
//   }
// }

// console.log('-------------------');
// movements.forEach(function (movement, index, array) {
//   if (movement > 0) {
//     console.log(`${index + 1}: You deposited ${Math.abs(movement)}`);
//   } else {
//     console.log(`${index + 1}: You withdrew ${Math.abs(movement)}`);
//   }
// });

// ForEach with maps and sets
// Map
const currencies = new Map([
  ['USD', 'United States dollar'],
  ['EUR', 'Euro'],
  ['GBP', 'Pound sterling'],
]);

// currencies.forEach(function (value, key, map) {
//   console.log(`${key}: ${value}`);
// });

// const currenciesU = new Set(['USD', 'GPB', 'USD', 'EUR', 'EUR']);

// currenciesU.forEach(function (value, _, map) {
//   console.log(`${_}: ${value}`);
// });

// // Coding Challenge #1
// const julia = [3, 5, 2, 12, 7];
// const kate = [4, 1, 15, 8, 3];

// const checkDogs = function (julia, kate) {
//   const juliaDogs = julia.slice(1, -2);
//   const dogs = julia.concat(kate);
//   dogs.forEach(function (dog, i, dogs) {
//     console.log(
//       `Dog number ${i + 1} ${dog >= 3 ? 'is and adult' : 'is still a puppy 🐶'}`
//     );
//   });
// };

// checkDogs(julia, kate);

// map
// const euroToUsd = 1.1;
// console.log(movements);

// const movementsUSD = movements.map(mov => Math.trunc(mov * euroToUsd));
// console.log(movementsUSD);

// const movementsUSDfor = [];
// for (const mov of movements) movementsUSDfor.push(Math.trunc(mov * euroToUsd));
// console.log(movementsUSDfor);

// const movementsDescriptions = movements.map(
//   (mov, i) =>
//     `Movement ${i + 1}: You ${mov > 0 ? 'deposited' : 'withdrew'} ${Math.abs(
//       mov
//     )}`
// );

// console.log(movementsDescriptions);

// // Filter
// const deposits = movements.filter(function (mov) {
//   return mov > 0;
// });
// console.log(deposits);

// const depositsFor = [];
// for (const mov of movements) if (mov > 0) depositsFor.push(mov);
// console.log(depositsFor);

// const withdrawals = movements.filter(mov => mov < 0);
// console.log(withdrawals);

// // Reduce
// const balance = movements.reduce((acc, mov) => acc + mov, 0); // 0 is starting value of accumulator
// console.log(balance);

// // Maximum value
// const max = movements.reduce((m, mov) => mov > m && (m = mov), 0);
// console.log(max);

// // Coding Challenge #2
// const calcAverageHumanAge = function (ages) {
//   const humanAges = ages
//     .map(dogAge => (dogAge <= 2 ? 2 * dogAge : 16 + dogAge * 4))
//     .filter(dogAge => dogAge >= 18);
//   console.log(humanAges);
//   const avg = humanAges.reduce(
//     (acc, dogAges, i, arr) => acc + dogAges / arr.length,
//     0
//   );
//   return avg;
// };
// console.log(calcAverageHumanAge([5, 2, 4, 1, 15, 8, 3]));
// console.log(calcAverageHumanAge([16, 6, 10, 5, 6, 1, 4]));

// Chaining methods
const euroToUsd = 1.1;

// // PIPELINE
// console.log(
//   movements
//     .filter(mov => mov > 0)
//     .map(mov => mov * euroToUsd)
//     .reduce((acc, mov) => acc + mov, 0)
// );

// // Coding Challange #3
// const calcAverageHumanAge = function (ages) {
//   const avgHumanAge = ages
//     .map(dogAge => (dogAge <= 2 ? 2 * dogAge : 16 + dogAge * 4))
//     .filter(dogAge => dogAge >= 18)
//     .reduce((acc, dogAges, i, arr) => acc + dogAges / arr.length, 0);
//   return avgHumanAge;
// };
// console.log(calcAverageHumanAge([5, 2, 4, 1, 15, 8, 3]));
// console.log(calcAverageHumanAge([16, 6, 10, 5, 6, 1, 4]));

// // Find
// console.log(movements.find(mov => mov < 0));
// const account = accounts.find(acc => acc.owner === 'Jessica Davis');
// console.log(account);

// // SOME
// console.log(movements);
// console.log(movements.some(mov => mov === -130));
// console.log(movements.includes(-130)); // equality

// console.log(movements.some(mov => mov > 1500)); // condition

// // EVERY
// console.log(account4.movements.every(mov => mov > 0));
// console.log(movements.every(mov => mov > 0));

// // Seperate callback
// const deposit = mov => mov > 0;
// console.log(movements.some(deposit));
// console.log(movements.every(deposit));
// console.log(movements.filter(deposit));

// // FLAT
// const arr = [[1, 2, 3], [4, 5, 6], 7, 8];
// const arrDeep = [[[1, 2], 3], [4, [5, 6]], 7, 8];
// console.log(arr.flat());
// console.log(arrDeep.flat());
// console.log(arrDeep.flat(2));
// console.log(arrDeep.flat().flat());

// const accountMovements = accounts.map(acc => acc.movements).flat();
// console.log(accountMovements);
// const overallBalance = accountMovements.reduce((acc, mov) => acc + mov, 0);
// console.log(overallBalance);

// // flatMap
// const overallBalance2 = accounts
//   .flatMap(acc => acc.movements)
//   .reduce((acc, mov) => acc + mov, 0);
// console.log(overallBalance);

// const owners = ['Jonas', 'Zack', 'Adam', 'Martha'];
// console.log(owners.sort());
// // Ascending
// console.log(
//   movements.sort((a, b) => {
//     // return > 0, A, B (keep order)
//     // return < 0, B, A (switch order)
//     if (a > b) return 1;
//     if (a < b) return -1;
//   })
// );

// // Descending
// console.log(
//   movements.sort((a, b) => {
//     // return > 0, A, B (keep order)
//     // return < 0, B, A (switch order)
//     if (a > b) return -1;
//     if (a < b) return 1;
//   })
// );

// console.log(movements.sort((a, b) => a - b));
// console.log(movements.sort((a, b) => b - a));

// // Programatically creating arrays
// const x = new Array(7);
// console.log(x);
// // console.log(x.map(() => 5));
// // console.log(x.fill(1));
// // console.log(x.fill(1, 3));
// console.log(x.fill(1, 3, 5));
// console.log(x.fill(33));

// // Array.from
// console.log(Array.from({ length: 7 }, () => 1));
// console.log(Array.from({ length: 7 }, (curr, i) => i + 1));

// // second parameter is a map paramenter
// labelBalance.addEventListener('click', function () {
//   const movementsUI = Array.from(
//     document.querySelectorAll('.movements__value'),
//     el => Number(el.textContent.replace('€', ''))
//   );
//   console.log(movementsUI);
// });

// // Which array method to use?
// // see sc

// // Array proactice methods
// const bankDepositSum = accounts
//   .flatMap(acc => acc.movements)
//   .filter(mov => mov > 0)
//   .reduce((sum, cur) => sum + cur, 0);
// console.log(bankDepositSum);

// // const numDeposits1000 = accounts
// //   .flatMap(acc => acc.movements)
// //   .filter(mov => mov > 1000).length;

// const numDeposits1000 = accounts
//   .flatMap(acc => acc.movements)
//   .reduce((sum, cur) => (cur >= 1000 ? ++sum : sum), 0);

// console.log(numDeposits1000);

// let a = 10;
// console.log(a++); // Increments value but returns original value
// console.log(a);
// console.log(++a);
// console.log(a);

// const { deposits, withdrawals } = accounts
//   .flatMap(acc => acc.movements)
//   .reduce(
//     (sums, cur) => {
//       // cur > 0 ? (sums.deposits += cur) : (sums.withdrawals += cur);
//       sums[cur > 0 ? 'deposits' : 'withdrawals'] += cur;
//       return sums;
//     },
//     { deposits: 0, withdrawals: 0 }
//   );
// console.log(deposits, withdrawals);

// // this is a nice title -> This Is a Nice Title

// const convertTitleCase = function (title) {
//   const capitalize = str => str[0].toUpperCase() + str.slice(1);

//   const exceptions = ['a', 'an', 'the', 'but', 'or', 'on', 'in', 'with', 'and'];

//   const titleCase = title
//     .toLowerCase()
//     .split(' ')
//     .map(word => (exceptions.includes(word) ? word : capitalize(word)))
//     .join(' ');
//   return capitalize(titleCase);
// };
// console.log(convertTitleCase('this is a nice title'));

// // Coding Challange #4
// const dogs = [
//   { weight: 22, curFood: 250, owners: ['Alice', 'Bob'] },
//   { weight: 8, curFood: 200, owners: ['Matilda'] },
//   { weight: 13, curFood: 275, owners: ['Sarah', 'John'] },
//   { weight: 32, curFood: 340, owners: ['Michael'] },
// ];

// // 1
// dogs.map(dog => (dog.recommededFood = Math.trunc(dog.weight ** 0.75 * 28)));

// // 2
// dogs.forEach(dog => {
//   dog.owners.includes('Sarah') &&
//     console.log(dog.curFood > dog.recommededFood ? 'Too Much' : 'Too Little');
// });

// // 3
// const { ownersEatTooMuch, ownersEatTooLittle } = dogs
//   .map(dog => [dog.owners, dog.curFood, dog.recommededFood])
//   .reduce(
//     (owns, curr) => {
//       owns[curr[1] > curr[2] ? 'ownersEatTooMuch' : 'ownersEatTooLittle'].push(
//         ...curr[0]
//       );
//       return owns;
//     },
//     { ownersEatTooMuch: [], ownersEatTooLittle: [] }
//   );

// console.log(ownersEatTooMuch, ownersEatTooLittle);

// // 4
// console.log(`${ownersEatTooMuch.join(' and ')}'s dogs eat too much!`);
// console.log(`${ownersEatTooLittle.join(' and ')}'s dogs eat too little!`);

// // 5
// console.log(dogs.some(dog => dog.curFood === dog.recommededFood));

// // 6
// console.log(
//   dogs.some(
//     dog =>
//       dog.curFood > dog.recommededFood * 0.9 &&
//       dog.curFood < dog.recommededFood * 1.1
//   )
// );

// // 7
// const good = dogs.filter(
//   dog =>
//     dog.curFood > dog.recommededFood * 0.9 &&
//     dog.curFood < dog.recommededFood * 1.1
// );
// console.log(good);
// console.log(dogs);

// // 8
// const sortied = dogs
//   .slice()
//   .sort((a, b) => a.recommededFood - b.recommededFood);
// console.log(sortied);
