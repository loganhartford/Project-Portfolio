// Exporting module
console.log('Exporting');

// Blocking Code
console.log('Start fetching users');
const res = await fetch('https://jsonplaceholder.typicode.com/posts');
const data = await res.json();
console.log('Finish fetching users');

const shippingCost = 10;
const cart = [];

export const addtoCart = function (product, quantity) {
  cart.push({ product, quantity });
  console.log(`${quantity} ${product} added to cart`);
};

const totalPrice = 237;
const totalQuantity = 23;

export { totalPrice, totalQuantity as qt };

export default function (product, quantity) {
  cart.push({ product, quantity });
  console.log(`${quantity} ${product} added to cart`);
}
