"use strict";

function logger() {
  console.log("My name is Logan");
}

logger();
logger();

console.log(fruitProcessor2(5, 0));

function fruitProcessor2(apples, oranges) {
  console.log(apples, oranges);
  const juice = `Juice with ${apples} apples and ${oranges} oranges.`;
  return juice;
}

console.log(fruitProcessor2(5, 0));

// Function Declaration
function calcAge1(birthYear) {
  return 2037 - birthYear;
}

console.log(calcAge1(2020));

// Fucntion Expression
// Can't access before declaration
const calcAge2 = function (birthYear) {
  return 2037 - birthYear;
};
console.log(calcAge2(2020));

// Arrow Fucntion
const calcAge3 = (birthYear) => 2037 - birthYear;
console.log(calcAge3(2020));

const yearUntilRetirement = (birthYear) => {
  const age = 2037 - birthYear;
  const retirment = 65 - age;
  return retirment;
};
console.log(yearUntilRetirement(2020));

function cutFruitPeices(fruit) {
  return fruit * 4;
}

function fruitProcessor(apples, oranges) {
  const applesPeices = cutFruitPeices(apples);
  const orangePeices = cutFruitPeices(oranges);
  const juice = `Juice with ${applesPeices} apples and ${orangePeices} oranges.`;
  return juice;
}
console.log(fruitProcessor(2, 3));

// Coding Challange #1
const calcAverage = (score1, score2, score3) => (score1 + score2 + score3) / 3;

const dolphins = calcAverage(44, 23, 71);

const koalas = calcAverage(85, 54, 41);

console.log(`The dolphins score ${dolphins}, and the koalas score ${koalas}.`);

function checkWinner(dolphins, koalas) {
  if (koalas > 2 * dolphins) {
    console.log("Koalas win!");
  } else if (dolphins > 2 * koalas) {
    console.log("Dolphins win!");
  } else {
    console.log("Draw!");
  }
}
checkWinner(dolphins, koalas);

// Arrays
const friends = ["Jaden", "Greg", "Fiegs"];
console.log(friends);

const years = new Array(1991, 2012, 2034, 3948);
console.log(years);

console.log(friends[0]);
console.log(friends.length);

// Basic Array Operations

// Add
const newLength = friends.push("Steve");
console.log(friends);
console.log(newLength);

friends.unshift("Luc");
console.log(friends);

// Remove
friends.pop();
console.log(friends);

friends.shift();
console.log(friends);

// Finding
console.log(friends.indexOf("Greg"));

console.log(friends.includes("Jaden"));

// Coding Challange #2
function calcTip(bill) {
  const tip = bill > 50 && bill < 300 ? 0.15 : 0.2;
  return bill * tip;
}
console.log(calcTip(250));

const bills = [125, 555, 44];
const tip1 = calcTip(bills[0]);
const tip2 = calcTip(bills[1]);
const tip3 = calcTip(bills[2]);

const tips = [tip1, tip2, tip3];
console.log(tips);

// Objects
const logan = {
  firstName: "Logan",
  lastName: "Hartford",
  age: 23,
  job: "Student",
  friends: ["Jaden", "Greg", "Fiegs"],
};
console.log(logan.lastName);
console.log(logan["lastName"]);

const nameKey = "Name";
console.log(logan["first" + nameKey]);
console.log(logan["last" + nameKey]);

// const interestedIn = prompt("What would you like to know about logan?");

// if (logan[interestedIn]) {
//   console.log(logan[interestedIn]);
// } else {
//   console.log("Bad");
// }

// Adding new properties
logan.location = "Austin, TX";
console.log(logan.location);

// Mini Challange
console.log(
  `${logan.firstName} has ${logan.friends.length} firends, and his best friends is called ${logan.friends[1]}`
);

// Methods
const logan2 = {
  firstName: "Logan",
  lastName: "Hartford",
  age: 23,
  job: "Student",
  friends: ["Jaden", "Greg", "Fiegs"],
  birthYear: 1999,
  hasDriversLicense: false,

  calcAge: function () {
    this.age = 2022 - this.birthYear;
    return this.age;
  },
  // Challange
  summary: function () {
    return `${this.firstName} is a ${this.calcAge()} year old ${
      this.job
    }, and he ${
      this.hasDriversLicense ? "does" : "does not"
    } have his drivers license.`;
  },
};

console.log(logan2.age);
console.log(logan2.summary());

// Challange #3
const mark = {
  name: "Mark Miller",
  weight: 78,
  height: 1.69,

  calcBMI: function () {
    this.BMI = this.weight / this.height ** 2;
    return this.BMI;
  },
};
const john = {
  name: "John Smith",
  weight: 92,
  height: 1.95,
  calcBMI: function () {
    this.BMI = this.weight / this.height ** 2;
    return this.BMI;
  },
};

console.log(
  mark.calcBMI() > john.calcBMI()
    ? `${mark.name}'s BMI (${mark.BMI}) is higher than ${john.name}'s BMI (${john.BMI}.)`
    : `${john.name}'s BMI (${john.BMI}) is higher than ${mark.name}'s BMI (${mark.BMI}.)`
);

// Loops
for (let rep = 1; rep <= 10; rep++) {
  console.log(`Lifting rep ${rep}.`);
}

// Looping over and array backwareds
for (let i = years.length - 1; i >= 0; i--) {
  console.log(years[i]);
}

// Loop in a loop
for (let i = 1; i < 4; i++) {
  console.log(`Excercise ${i}`);
  for (let j = 1; j < 6; j++) {
    console.log(`Rep ${j}`);
  }
}

let i = 1;
while (i < 5) {
  console.log(i, "your moms a hoe");
  i++;
}

let dice = Math.trunc(Math.random() * 6);

while (dice !== 6) {
  console.log(`You rolled a ${dice}`);
  dice = Math.trunc(Math.random() * 6 + 1);
}

// Challange #4
const billz = [200, 458, 29, 659, 2349, 38, 7, 239, 9, 10];
const tipz = [];
const totalz = [];

for (let i = 0; i < billz.length; i++) {
  tipz[i] = calcTip(billz[i]);
  totalz[i] = billz[i] + tipz[i];
  console.log(tipz[i], totalz[i]);
}

// Bonus
const arr = [5, 9, 27];

function calcAvg(arr) {
  let total = 0;
  for (let i = 0; i < arr.length; i++) {
    total += arr[i];
    console.log(total);
  }
  return total / arr.length;
}
console.log(calcAvg(arr));
