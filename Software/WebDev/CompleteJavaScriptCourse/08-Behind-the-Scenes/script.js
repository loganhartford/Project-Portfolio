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
