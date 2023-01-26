let js = "amazing";
console.log(49 + 8);

console.log("Jonas");

let nameF = "Logan";
let nameL = "Hartford";
console.log(nameL, nameF);

// Operators
console.log(nameL + "-" + nameF);
console.log(typeof nameF);

const high = 100;
const low = 22;

console.log(high > low); // >, <, <=, >=
console.log(high == low);

// Procedance of Operators

// Challange 1 & 2
const markW = 78;
const markH = 1.69;
const johnW = 95;
const johnH = 1.95;

const markBMI = markW / markH ** 2;
const johnBMI = johnW / johnH ** 2;

const markHigherBMI = markBMI > johnBMI;
let output;

if (markHigherBMI) {
  output = `Mark's BMI (${markBMI}) is higher than John's (${johnBMI})`;
} else {
  output = `John's BMI (${markBMI}) is higher than Mark's (${johnBMI})`;
}
console.log(markBMI, johnBMI, markHigherBMI);
console.log(output);

// Strings and Template Literals
const logan = `My name is ${nameF}, ${nameL}`;
console.log(logan);

// can use for normal strings
const logan2 = "My name is logan hartford";
console.log(logan2);

// automatically creates multiline strings
const logan3 = `My 
Name
Is 
Logan`;
console.log(logan3);

// Type Conversion
const year = `1999`;
console.log(Number(year) + 1);

// Type Coercion
console.log("I am " + 23 + " years old");
console.log("23" * "3");

// 5 Falsey values: 0, '', undefined, null, NaN
// Any number is truthy

// ===  or !== strict -- does not perform type coercion
// == or != loose -- does perform type coersion
console.log(18 == "18");
console.log(18 === "18");
// avoid loose equality operator

// const fav = prompt("What is you fave number? 23?");
// if (fav == 23) {
//   alert("23 is an amazing number");
// }
// if (fav === 23) {
//   console.log("23 is an amazing number");
// }

// Logical Operators
console.log(true && true);
console.log(true && false);

// Switch statments
const day = "wednesday";

switch (day) {
  case "monday":
    console.log("Plan course structure");
    break;
  case "tuesday":
    console.log("shave balls");
    break;
  case "wednesday": // This works like wednesday || thrusday
  case "thursday":
    console.log("shave balls again");
    break;
  default:
    console.log("non a valid day");
}

// The turnary  operator
const age = 23;
age >= 18
  ? console.log("I like to drink wine")
  : console.log("I like to drink water");

// Coding challang #4
const bill = 40;
const tip = bill >= 50 && bill <= 300 ? 0.15 : 0.2;

console.log(
  `The Bill is ${bill}, the tip is ${tip * 100}% and the total cost is ${
    bill + bill * tip
  }.`
);
