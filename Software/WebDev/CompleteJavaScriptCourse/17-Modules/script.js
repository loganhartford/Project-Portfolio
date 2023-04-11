// import { addtoCart, totalPrice as price, qt } from './shoppingCart.js';
// addtoCart('cheese', 4);
// console.log(price, qt);

// console.log('Importinng');

// import * as ShoppingCart from './shoppingCart.js';

// ShoppingCart.addtoCart('cheese', 4);
// console.log(ShoppingCart.totalPrice);

// import add from './shoppingCart.js';
// add('corn', 3);

// // const res = await fetch('https://jsonplaceholder.typicode.com/posts');
// // const data = await res.json();
// // console.log(data);

// const getLastPost = async function () {
//   const res = await fetch('https://jsonplaceholder.typicode.com/posts');
//   const data = await res.json();
//   console.log(data);
//   return { title: data.at(-1).title, text: data.at(-1).body };
// };

// const lastPost = getLastPost();
// console.log(lastPost);
// // Not very clean
// lastPost.then(res => console.log(res));

// const lastPost2 = await getLastPost();
// console.log(lastPost2);

// const ShoppingCart2 = (function () {
//   const cart = [];
//   const shippingCost = 10;
//   const totalPrice = 237;
//   const totalQuantity = 23;

//   const addtoCart = function (product, quantity) {
//     cart.push({ product, quantity });
//     console.log(`${quantity} ${product} added to cart`);
//   };

//   const orderStock = function (product, quantity) {
//     console.log(`${quantity} ${product} ordered from supplier`);
//   };

//   return {
//     addtoCart,
//     cart,
//     totalPrice,
//     totalQuantity,
//   };
// })();

// ShoppingCart2.addtoCart('apple', 4);
// ShoppingCart2.addtoCart('pizza', 2);
// console.log(ShoppingCart2);
// console.log(ShoppingCart2.shippingCost);
import cloneDeep from 'lodash-es';

if (module.hot) {
  module.hot.accept();
}

import 'core-js/stable';
import 'regenerator-runtime';
