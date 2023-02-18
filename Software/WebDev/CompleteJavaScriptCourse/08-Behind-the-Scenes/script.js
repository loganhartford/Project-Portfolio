'use strict';

function calcAge(birthYear) {
  const age = 2037 - birthYear;

  function printAge() {
    let output = `Your are born in ${birthYear}`;
    console.log(output);

    if (birthYear >= 1981 && birthYear <= 1996) {
      var millenial = true;
      const firstName = 'Stevon'; // Comment our for magic in console
      const str = `Oh, and you are a millenial, ${firstName}`;
      console.log(str);

      function add(a, b) {
        return a + b;
      }

      output = 'new output';
    }
    // console.log(str); RefError
    console.log(millenial);
    // console.log(add(3, 4)); RefError
    console.log(output);
  }

  printAge();

  return age;
}

const firstName = 'Logan';
// console.log(age); RefError
calcAge(1996);
// printAge(); RefError

// Never use an arrow function as a method
// Using and arrow function inside of an object declaration allows you access to the object's this, normal functions do not

const addExpr = function (a, b) {
  console.log(arguments);
  return a + b;
};
addExpr(10, 12);
addExpr(1, 2, 3, 4);
// Aruments are still part of the argumetns array
// doesn't work for arrow functions

let age = 30;
let oldAge = 30;
age = 31;

console.log(age);
console.log(oldAge);

const me = {
  name: 'logan',
  age: 30,
};

const friend = me;
friend.me = 27;
console.log('Friend:', friend);
console.log('Me:', me);

// Copying objecs
const jessica = {
  firstName: 'Jessica',
  lastName: 'Williams',
  family: ['Alice', 'Bob'],
};

const jessicaCopy = Object.assign({}, jessica);
jessicaCopy.firstName = 'not Jessica';
console.log(jessica, jessicaCopy);

// The array is changes in both since jessicaCopy is not a deep clone
jessicaCopy.family.push('Mary');
jessicaCopy.family.push('John');
console.log(jessica, jessicaCopy);
