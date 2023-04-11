'use strict';

// const jonas = new Person('Jonas', 1991);
// console.log(jonas);

// // 1. New {} is created
// // 2. Function is called, this = {}
// // 3. {} is linked to prototype
// // 4. funciton automatically return {}

// const matilda = new Person('Matilda', 2017);
// console.log(matilda);

// console.log(jonas instanceof Person);

// Person.hey = function () {
//   console.log('Hey there');
//   console.log(this);
// };

// Person.hey();
// // jonas.hey();

// jonas.calcAge();
// matilda.calcAge();

// console.log(jonas.__proto__);

// Person.prototype.species = 'Homo Sapiens';
// console.log(jonas.species, matilda.species);

// console.log(jonas.hasOwnProperty('firstName'));
// console.log(jonas.hasOwnProperty('species'));

// console.log(jonas.__proto__.__proto__);
// console.dir(Person.prototype.constructor);

// const arr = [3, 4, 5, 6, 6, 7, 8, 9, 9, 0];
// console.log(arr.__proto__);

// Array.prototype.unique = function () {
//   return [...new Set(this)];
// };
// console.log(arr.unique());

// const h1 = document.querySelector('h1');
// console.dir(x => x + 1);

// // Coding Challange #1
// const Car = function (make, speed) {
//   this.make = make;
//   this.speed = speed;
// };

// Car.prototype.accelerate = function () {
//   this.speed = this.speed + 10;
//   console.log(this.speed);
// };

// Car.prototype.brake = function () {
//   this.speed = this.speed - 5;
//   console.log(this.speed);
// };

// const myCar = new Car('Hyundai', 130);
// const leaCar = new Car('Nissan', 60);

// myCar.brake();
// myCar.brake();
// leaCar.brake();
// leaCar.accelerate();
// leaCar.accelerate();
// console.log(myCar.speed);
// console.log(leaCar.speed);

// // ES6 Classes
// // class expressions
// // const PersonCl = class {}

// class declaration
// class PersonCl {
//   constructor(fullName, birthYear) {
//     this.fullName = fullName;
//     this.birthYear = birthYear;
//   }

//   // Methods will be added to the .prototype property
//   calcAge() {
//     console.log(2037 - this.birthYear);
//   }

//   get age() {
//     return 2037 - this.birthYear;
//   }

//   // Set a property that already exists
//   set fullName(name) {
//     if (name.includes(' ')) this._fullName = name;
//     else alert('This given name is not a full name');
//   }

//   get fullName() {
//     return this._fullName;
//   }

//   static hey() {
//     console.log('Hey there');
//     console.log(this);
//   }
// }

// const jessica = new PersonCl('Jessica Davis', 1996);
// console.log(jessica);
// jessica.calcAge();

// PersonCl.prototype.greet = function () {
//   console.log('Yooo');
// };
// jessica.greet();

// // 1. Classes are NOT hoisted
// // 2. Class are firsty-class citizens
// // 3. Classes are executed in strict mode

// const walter = new PersonCl('Walter White', 1965);
// console.log(walter);

// // Getters and Setters
// const account = {
//   owner: 'Jonas',
//   movements: [200, 530, 120, 300],

//   get latest() {
//     return this.movements.slice(-1).pop();
//   },

//   set latest(mov) {
//     this.movements.push(mov);
//   },
// };

// account.latest = 50;
// console.log(account.movements);

// console.log(jessica.age);

// // Static Mehods
// PersonCl.hey();

// // Object.create()
// const PersonProto = {
//   calcAge() {
//     console.log(2037 - this.birthYear);
//   },

//   init(firstName, birthYear) {
//     this.firstName = firstName;
//     this.birthYear = birthYear;
//   },
// };

// const steven = Object.create(PersonProto);
// console.log(steven);
// steven.name = 'Steven';
// steven.birthYear = 2002;
// steven.calcAge();

// console.log(steven.__proto__ === PersonProto);

// const sarah = Object.create(PersonProto);
// sarah.init('Sarah', 1979);
// sarah.calcAge();

// // Coding Challange #1
// const Car = function (make, speed) {
//   this.make = make;
//   this.speed = speed;
// };

// Car.prototype.accelerate = function () {
//   this.speed = this.speed + 10;
//   console.log(this.speed);
// };

// Car.prototype.brake = function () {
//   this.speed = this.speed - 5;
//   console.log(this.speed);
// };

// const myCar = new Car('Hyundai', 130);
// const leaCar = new Car('Nissan', 60);

// class Car {
//   constructor(make, speed) {
//     this.make = make;
//     this.speed = speed;
//   }

//   accelerate() {
//     this.speed += 10;
//     console.log(this.speed);
//   }

//   brake() {
//     this.speed -= 5;
//     console.log(this.speed);
//   }

//   get speedUS() {
//     return this.speed / 1.6;
//   }

//   set speedUS(speed) {
//     this.speed = speed * 1.6;
//   }
// }

// const myCar = new Car('Hyundai', 130);
// const leaCar = new Car('Nissan', 60);

// myCar.brake();
// myCar.brake();
// leaCar.brake();
// leaCar.accelerate();
// leaCar.accelerate();
// console.log(myCar.speed);
// console.log(leaCar.speed);
// console.log(myCar.speedUS);
// myCar.speedUS = 100;
// console.log(myCar.speed);

// const Person = function (firstName, birthYear) {
//   // Instance properties
//   this.firstName = firstName;
//   this.birthYear = birthYear;

//   // // Never create methods in constructor function
//   // this.calcAge = function() {
//   //   console.log(2037 - this.birthYear);
//   // }
// };

// // Prototypes
// Person.prototype.calcAge = function () {
//   console.log(2037 - this.birthYear);
// };

// const Student = function (firstName, birthYear, course) {
//   Person.call(this, firstName, birthYear);
//   this.course = course;
// };

// // Linking prototypes
// Student.prototype = Object.create(Person.prototype);

// Student.prototype.introduce = function () {
//   console.log(`My name id ${this.firstName} and I study ${this.course}`);
// };

// const mike = new Student('Mike', 2020, 'Computer Science');
// console.log(mike);
// mike.introduce();
// mike.calcAge();

// console.log(mike.__proto__);
// console.log(mike.__proto__.__proto__);
// console.log(mike instanceof Student);
// console.log(mike instanceof Person);

// Student.prototype.constructor = Student;
// console.dir(Student.prototype.constructor);

// // Coding Challange #3
// const Car = function (make, speed) {
//   this.make = make;
//   this.speed = speed;
// };

// Car.prototype.accelerate = function () {
//   this.speed = this.speed + 10;
//   console.log(this.speed);
// };

// Car.prototype.brake = function () {
//   this.speed = this.speed - 5;
//   console.log(this.speed);
// };

// // EV
// const EV = function (make, speed, charge) {
//   Car.call(this, make, speed);
//   this.charge = charge;
// };

// EV.prototype = Object.create(Car.prototype);

// EV.prototype.chargeBattery = function (chargeTo) {
//   this.charge = chargeTo;
// };

// EV.prototype.accelerate = function () {
//   this.charge -= 1;
//   this.speed += 20;
//   console.log(
//     `${this.make} going at ${this.speed} km/h, with a charge of ${this.charge}%`
//   );
// };

// const model_y = new EV('Tesla', 200, 87);
// model_y.brake();
// model_y.accelerate();
// model_y.chargeBattery(95);
// model_y.accelerate();

// class PersonCl {
//   constructor(fullName, birthYear) {
//     this.fullName = fullName;
//     this.birthYear = birthYear;
//   }

//   // Methods will be added to the .prototype property
//   calcAge() {
//     console.log(2037 - this.birthYear);
//   }

//   get age() {
//     return 2037 - this.birthYear;
//   }

//   // Set a property that already exists
//   set fullName(name) {
//     if (name.includes(' ')) this._fullName = name;
//     else alert('This given name is not a full name');
//   }

//   get fullName() {
//     return this._fullName;
//   }

//   static hey() {
//     console.log('Hey there');
//     console.log(this);
//   }
// }

// // Inheritance between ES6 classes
// class StudentCl extends PersonCl {
//   constructor(fullName, birthYear, course) {
//     // Always needs to happen first
//     super(fullName, birthYear);
//     this.course = course;
//   }

//   introduce() {
//     console.log(`My name is ${this.fullName} and I study ${this.course}`);
//   }

//   calcAge() {
//     console.log(
//       `I'm ${
//         2037 - this.birthYear
//       } years old, but as a studnet, I feel more like ${
//         2037 - this.birthYear + 10
//       }`
//     );
//   }
// }

// const martha = new StudentCl('Marth Jones', 2012, 'Computer Science');
// const bill = new StudentCl('Marth Jones', 2012);

// console.log(martha);
// console.log(bill);

// martha.introduce();
// martha.calcAge();

// // Inheritance with Object.create
// // Object.create()
// const PersonProto = {
//   calcAge() {
//     console.log(2037 - this.birthYear);
//   },

//   init(firstName, birthYear) {
//     this.firstName = firstName;
//     this.birthYear = birthYear;
//   },
// };

// const steven = Object.create(PersonProto);
// const StudentProto = Object.create(PersonProto);

// StudentProto.init = function (firstName, birthYear, course) {
//   PersonProto.init.call(this, firstName, birthYear);
//   this.course = course;
// };
// const jay = Object.create(StudentProto);
// jay.init('Jay', 2010, 'Computer Science');

// StudentProto.introduce = function () {
//   console.log(`My name is ${this.firstName} and I study ${this.course}`);
// };

// jay.introduce();
// jay.calcAge();

// Another Class Example
// 1. Public fields
// 2. Private fields
// 3. Public methods
// 4. Private methods
// (there is also the static version)

class Account {
  // 1. Public field (istances)
  locale = navigator.language;
  // _movements = [];

  // 2. Private fields
  #movements = [];
  #pin;

  constructor(owner, currency, pin) {
    this.owner = owner;
    this.currency = currency;
    // Protected property
    this.#pin = pin;
    // this._movements = [];
    // this.locale = navigator.language;

    console.log(`Thanks for opening an account, ${owner}`);
  }

  // 3. Public Mehods
  getMovements() {
    return this.#movements;
  }

  deposit(val) {
    this.#movements.push(val);
    return this;
  }

  _approveLoan(val) {
    return true;
  }

  withdraw(val) {
    this.deposit(-val);
    return this;
  }

  requestLoan(val) {
    if (this._approveLoan(val)) {
      this.deposit(val);
      console.log(`Load approved.`);
    }
    return this;
  }

  static helper() {
    console.log('HELP');
  }

  // // 4. Private Methods -- Not yet supported
  // #approveLoan(val) {
  //   return true;
  // }
}

const acc1 = new Account('Jonas', 'EUR', 1111);

acc1.deposit(250);
acc1.withdraw(140);
acc1.requestLoan(1000);
// acc1._approveLoan(1000); // Shouldn't be able to access this
console.log(acc1.getMovements());

console.log(acc1);
// console.log(acc1.#pin); // Shouldn't be able to access this
// console.log(acc1.#approveLoan(100));
// console.log(acc1.#movements);
Account.helper();

// Chaining
acc1.deposit(300).deposit(400).withdraw(35).requestLoan(25000).withdraw(4000);
console.log(acc1.getMovements());

// # Coding Challange
class CarCl {
  constructor(make, speed) {
    this.make = make;
    this.speed = speed;
  }

  accelerate() {
    this.speed += 10;
    console.log(`${this.make} is going at ${this.speed} km/h`);
    return this;
  }

  brake() {
    this.speed -= 5;
    console.log(`${this.make} is going at ${this.speed} km/h`);
    return this;
  }

  get speedUS() {
    return this.speed / 1.6;
  }

  set speedUS(speed) {
    this.speed = speed * 1.6;
  }
}

class EVCl extends CarCl {
  #charge;
  constructor(make, speed, charte) {
    super(make, speed);
    this.#charge = charge;
  }

  charge(chargeTo) {
    this.#charge = chargeTo;
    return this;
  }
}
