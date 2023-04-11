'use strict';

const btn = document.querySelector('.btn-country');
const countriesContainer = document.querySelector('.countries');

///////////////////////////////////////
// const getCoutnryData = function (country) {
//   const request = new XMLHttpRequest(); // old school
//   request.open(
//     'GET',
//     `https://restcountries.com/v3.1/name/${country}?fullText=true`
//   );
//   request.send();

//   request.addEventListener('load', function () {
//     let data = JSON.parse(this.responseText);
//     data = data[0];
//     console.log(data);
//     console.log(data.languages);

//     const html = `
//         <article class="country">
//           <img class="country__img" src="${
//             data.flags[Object.keys(data.flags)[0]]
//           }" />
//           <div class="country__data">
//             <h3 class="country__name">${data.name.common}</h3>
//             <h4 class="country__region">${data.region}</h4>
//             <p class="country__row"><span>👫</span>${(
//               +data.population / 1000000
//             ).toFixed(1)} people</p>
//             <p class="country__row"><span>🗣️</span>${
//               data.languages[Object.keys(data.languages)[0]]
//             }</p>
//             <p class="country__row"><span>💰</span>${
//               data.currencies[Object.keys(data.currencies)[0]][
//                 Object.keys(data.currencies[Object.keys(data.currencies)[0]])[0]
//               ]
//             }</p>
//           </div>
//         </article>`;

//     countriesContainer.insertAdjacentHTML('beforeend', html);
//     countriesContainer.style.opacity = 1;
//   });
// };

const renderCountry = function (data, className = '') {
  const html = `
        <article class="country ${className}">
          <img class="country__img" src="${
            data.flags[Object.keys(data.flags)[0]]
          }" />
          <div class="country__data ">
            <h3 class="country__name">${data.name.common}</h3>
            <h4 class="country__region">${data.region}</h4>
            <p class="country__row"><span>👫</span>${(
              +data.population / 1000000
            ).toFixed(1)} people</p>
            <p class="country__row"><span>🗣️</span>${
              data.languages[Object.keys(data.languages)[0]]
            }</p>
            <p class="country__row"><span>💰</span>${
              data.currencies[Object.keys(data.currencies)[0]][
                Object.keys(data.currencies[Object.keys(data.currencies)[0]])[0]
              ]
            }</p>
          </div>
        </article>`;

  countriesContainer.insertAdjacentHTML('beforeend', html);
  countriesContainer.style.opacity = 1;
};

const renderError = function (msg) {
  countriesContainer.insertAdjacentText('beforeend', msg);
};

const getJSON = function (url, errorMsg = 'Something went wrong') {
  return fetch(url).then(response => {
    if (!response.ok) throw new Error(`${errorMsg} (${response.status})`);

    return response.json();
  });
};

// const getCoutnryAndNeighbour = function (country) {
//   const request = new XMLHttpRequest(); // old school
//   request.open(
//     'GET',
//     `https://restcountries.com/v3.1/name/${country}?fullText=true`
//   );
//   request.send();
//   request.addEventListener('load', function () {
//     let [data] = JSON.parse(this.responseText);
//     console.log(data);
//     console.log(data.flags[Object.keys(data.flags)[0]]);

//     // Render country 1
//     renderCountry(data);

//     // Get Neighbour country

//     // Get neighboor country 2
//     const [neighboor] = data.borders;

//     if (!neighboor) return;

//     // AJAX call country 2
//     const request2 = new XMLHttpRequest(); // old school
//     request2.open(
//       'GET',
//       `https://restcountries.com/v3.1/alpha/${neighboor}?fullText=true`
//     );
//     request2.send();

//     request2.addEventListener('load', function () {
//       console.log(this.responseText);
//       let [data2] = JSON.parse(this.responseText);
//       console.log(data2);
//       renderCountry(data2, 'neighbour');
//     });
//   });
// };

// getCoutnryAndNeighbour('canada');

// const request = fetch(
//   'https://restcountries.com/v3.1/name/canada?fullText=tru'
// );

// const getCoutnryData = function (country) {
//   fetch(`https://restcountries.com/v3.1/name/${country}?fullText=tru`)
//     .then(function (response) {
//       console.log(response);
//       return response.json();
//     })
//     .then(function (data) {
//       console.log(data);
//       renderCountry(data[0]);
//     });
// };

//

// // c

// const lotteryPromise = new Promise(function (resolve, reject) {
//   console.log('Lottery draw is happening');
//   setTimeout(function () {
//     if (Math.random() >= 0.5) {
//       resolve('You WIN');
//     } else {
//       reject('You lost you money SHIT');
//     }
//   }, 2000);
// });

// lotteryPromise.then(res => console.log(res)).catch(err => console.log(err));

// Promisifying setTimeout
const wait = function (seconds) {
  return new Promise(function (resolve) {
    setTimeout(resolve, seconds * 1000);
  });
};

// wait(2)
//   .then(() => {
//     console.log('I waited for 2 seconds');
//     return wait(1);
//   })
//   .then(() => console.log('I waited for 1 second'));

// getPosition().then(pos => console.log(pos));

/* 
Build the image loading functionality that I just showed you on the screen.

Tasks are not super-descriptive this time, so that you can figure out some stuff on your own. Pretend you're working on your own 😉

PART 1
1. Create a function 'createImage' which receives imgPath as an input. This function returns a promise which creates a new image (use document.createElement('img')) and sets the .src attribute to the provided image path. When the image is done loading, append it to the DOM element with the 'images' class, and resolve the promise. The fulfilled value should be the image element itself. In case there is an error loading the image ('error' event), reject the promise.

If this part is too tricky for you, just watch the first part of the solution.

PART 2
2. Comsume the promise using .then and also add an error handler;
3. After the image has loaded, pause execution for 2 seconds using the wait function we created earlier;
4. After the 2 seconds have passed, hide the current image (set display to 'none'), and load a second image (HINT: Use the image element returned by the createImage promise to hide the current image. You will need a global variable for that 😉);
5. After the second image has loaded, pause execution for 2 seconds again;
6. After the 2 seconds have passed, hide the current image.

TEST DATA: Images in the img folder. Test the error handler by passing a wrong image path. Set the network speed to 'Fast 3G' in the dev tools Network tab, otherwise images load too fast.

GOOD LUCK 😀
*/
// // Part 1
const imgContainer = document.querySelector('.images');

// const createImage = function (imgPath) {
//   return new Promise(function (resolve, reject) {
//     const img = document.createElement('img');
//     img.src = imgPath;

//     img.addEventListener('load', function () {
//       imgContainer.append(img);
//       resolve(img);
//     });

//     img.addEventListener('error', function () {
//       reject(new Error('Image not found'));
//     });
//   });
// };

// // Part 2
// let currentImg;

// createImage('img/img-1.jpg')
//   .then(img => {
//     currentImg = img;
//     return wait(2);
//   })
//   .then(() => {
//     currentImg.style.display = 'none';
//     return createImage('img/img-2.jpg');
//   })
//   .then(img => {
//     currentImg = img;
//     return wait(2);
//   })
//   .then(() => (currentImg.style.display = 'none'))
//   .catch(err => console.error(err));

// const getPosition = function () {
//   return new Promise(function (resolve, reject) {
//     navigator.geolocation.getCurrentPosition(resolve, reject);
//   });
// };

// const geoAPIKey = '253348299789136906173x89395';
// // Async/Await
const whereAmI = async function () {
  try {
    const pos = await getPosition();

    const { latitude: lat, longitude: lng } = pos.coords;

    const geo = await fetch(
      `https://geocode.xyz/${lat},${lng}?geoit=json&auth=${geoAPIKey}`
    );
    if (!geo.ok) throw new Error('Problem getting location data');

    const dataGeo = await geo.json();

    // fetch(`https://restcountries.com/v3.1/name/${country}?fullText=tru`).then(res => console.log(res))
    const res = await fetch(
      `https://restcountries.com/v3.1/name/${dataGeo.country}?fullText=tru`
    );
    if (!res.ok) throw new Error('Problem getting country data');
    const data = await res.json();

    renderCountry(data[0]);
    return `You are in, ${dataGeo.country}`;
  } catch (err) {
    renderError(`Something bad: ${err}`);
  }
};

// // whereAmI();
// console.log(`1: you will get location`);
// (async function () {
//   try {
//     const city = await whereAmI();
//     console.log(`2: ${city}`);
//   } catch (err) {
//     console.error();
//   }
//   console.log('3: finished getting location');
// })();

// const get3Countries = async function (c1, c2, c3) {
//   try {
//     // const [data1] = await getJSON(
//     //   `https://restcountries.com/v3.1/name/${c1}?fullText=tru`
//     // );
//     // const [data2] = await getJSON(
//     //   `https://restcountries.com/v3.1/name/${c2}?fullText=tru`
//     // );
//     // const [data3] = await getJSON(
//     //   `https://restcountries.com/v3.1/name/${c3}?fullText=tru`
//     // );

//     const data = await Promise.all([
//       getJSON(`https://restcountries.com/v3.1/name/${c1}?fullText=tru`),
//       getJSON(`https://restcountries.com/v3.1/name/${c2}?fullText=tru`),
//       getJSON(`https://restcountries.com/v3.1/name/${c3}?fullText=tru`),
//     ]);

//     console.log(data.map(d => d[0].capital));
//   } catch (err) {
//     console.log(err);
//   }
// };

// get3Countries('canada', 'portugal', 'tanzania');

// // Promise.race
// (async function () {
//   const res = await Promise.race([
//     getJSON(`https://restcountries.com/v3.1/name/italy?fullText=tru`),
//     getJSON(`https://restcountries.com/v3.1/name/egypt?fullText=tru`),
//     getJSON(`https://restcountries.com/v3.1/name/mexico?fullText=tru`),
//   ]);
//   console.log(res[0]);
// })();

// const timeout = function (s) {
//   return new Promise(function (_, reject) {
//     setTimeout(function () {
//       reject(new Error('request took too long'));
//     }, s * 1000);
//   });
// };

// Promise.race([
//   getJSON(`https://restcountries.com/v3.1/name/italy?fullText=tru`),
//   timeout(0.5),
// ])
//   .then(res => console.log(res[0]))
//   .catch(err => console.error(err));

// // Promise.allSettled
// Promise.allSettled([
//   Promise.resolve('sucess'),
//   Promise.reject('failure'),
//   Promise.resolve('success'),
// ]).then(res => console.log(res));

// // Promise.any [ES2021]
// Promise.any([
//   Promise.resolve('sucess'),
//   Promise.reject('failure'),
//   Promise.resolve('success'),
// ]).then(res => console.log(res));

///////////////////////////////////////
// Coding Challenge #3

/* 
PART 1
Write an async function 'loadNPause' that recreates Coding Challenge #2, this time using async/await (only the part where the promise is consumed). Compare the two versions, think about the big differences, and see which one you like more.
Don't forget to test the error handler, and to set the network speed to 'Fast 3G' in the dev tools Network tab.

PART 2
1. Create an async function 'loadAll' that receives an array of image paths 'imgArr';
2. Use .map to loop over the array, to load all the images with the 'createImage' function (call the resulting array 'imgs')
3. Check out the 'imgs' array in the console! Is it like you expected?
4. Use a promise combinator function to actually get the images from the array 😉
5. Add the 'paralell' class to all the images (it has some CSS styles).

TEST DATA: ['img/img-1.jpg', 'img/img-2.jpg', 'img/img-3.jpg']. To test, turn off the 'loadNPause' function.

GOOD LUCK 😀
*/

const createImage = function (imgPath) {
  return new Promise(function (resolve, reject) {
    const img = document.createElement('img');
    img.src = imgPath;

    img.addEventListener('load', function () {
      imgContainer.append(img);
      resolve(img);
    });

    img.addEventListener('error', function () {
      reject(new Error('Image not found'));
    });
  });
};

// const createImage = async function (imgPath) {
//   try {
//     img = await Promise(function () {
//       const img = document.createElement('img');
//       img.src = imgPath;
//     });
//   } catch (err) {
//     console.log(err);
//   }
// };
let currentImg;
const loadNPause = async function () {
  try {
    let img = await createImage('img/img-1.jpg');
    console.log('Image 1 loaded');
    await wait(2);

    img.style.display = 'none';

    img = await createImage('img/img-2.jpg');
    console.log('Image 2 loaded');
    await wait(2);

    img.style.display = 'none';

    img = await createImage('img/img-3.jpg');
    console.log('Image 3 loaded');
    await wait(2);
  } catch (err) {
    console.log(err);
  }
};

// loadNPause();

const loadAll = async function (imgArr) {
  try {
    const imgs = imgArr.map(async img => await createImage(img));
    const imgsEl = await Promise.all(imgs);

    imgsEl.forEach(img => img.classList.add('parallel'));
  } catch (err) {
    console.log(err);
  }
};

loadAll(['img/img-1.jpg', 'img/img-2.jpg', 'img/img-3.jpg']);
