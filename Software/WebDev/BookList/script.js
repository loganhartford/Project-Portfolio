'use strict';

// ---- User Data ----
const user0000 = {
  id: 'user-example',
  password: '1111',
  booklists: [
    {
      list: "Logan's List",
      books: [
        {
          title: 'Building a Second Brain',
          subtitle:
            'A Proven Method to Organize Your Digital Life and Unlock Your Creative Potential',
          author: 'Tiago Forte',
          authorSource:
            'https://www.amazon.ca/Tiago-Forte/e/B076PVMTQQ/ref=aufs_dp_fta_dsk',
          genre: 'Self-Improvement',
          source:
            'https://www.amazon.ca/dp/1982167386/?coliid=I1KETX8MUBNQ3A&colid=2S4999TCVODHV&psc=1&ref_=lv_ov_lig_dp_it_im',
          cover: 'img/brain.jpg',
          dateAdded: Date(),
          id: '0000',
        },
        {
          title: 'Echiridion',
          subtitle: '',
          author: 'Epictetus',
          authorSource:
            'https://www.amazon.ca/s?i=stripbooks&rh=p_27%3AEpictetus&s=relevancerank&text=Epictetus&ref=dp_byline_sr_book_1',
          genre: 'Philosophy',
          source:
            'https://www.amazon.ca/Enchiridion-Epictetus/dp/0486433595/ref=sr_1_1?crid=10FI86VTG1HW9&keywords=enchiridion&qid=1674528464&s=books&sprefix=enchiridion%2Cstripbooks%2C77&sr=1-1',
          cover: 'img/enchiro.jpg',
          dateAdded: Date(),
          id: '0001',
        },
      ],
    },
    {
      list: 'Christmas List',
      books: [
        {
          title: 'The God Equation',
          subtitle: 'The Quest for a Theory of Everything',
          author: 'Michio Kaku',
          authorSource:
            'https://www.amazon.ca/Michio-Kaku/e/B00J02CFW0/ref=aufs_dp_fta_dsk',
          genre: 'Self-Improvement',
          source:
            'https://www.amazon.ca/God-Equation-Quest-Theory-Everything/dp/0525434569/ref=sr_1_1?crid=3DNS3C51RID4E&keywords=the+god+equation+by+michio+kaku&qid=1674528494&s=books&sprefix=the+god+eq%2Cstripbooks%2C87&sr=1-1m',
          cover: 'img/god.jpg',
          dateAdded: Date(),
          id: '0000',
        },
      ],
    },
  ],
};

// ---- Selecting Elements ----

// Buttons
const btnFind = document.querySelector('.find-button');
const btnSort = document.querySelector('.sort-button');
const btnFilter = document.querySelector('.filter-button');
const btnPurchased = document.querySelectorAll('.purchased-button');
const btnAdd = document.querySelector('.add-button');

// Forms
const formListSearch = document.querySelector('.list-search-form');
const formAddBook = document.querySelector('.add-book-form');

// Lists
const listSearch = document.querySelector('.sort-list');
const listFilter = document.querySelector('.filter-list');
const listSearchOption = document.querySelectorAll('.sort-list-option');
const listFilterOption = document.querySelectorAll('.filter-list-option');
const listCurrentBookList = document.querySelector('.book-list');

// Headings
const headingBookList = document.querySelector('.list-name');

// ---- Fucntions ----

const dynamicSort = function (property) {
  let sortOrder = 1; // Normal sort order
  // Reverse sort order
  if (property[0] === '-') {
    sortOrder = -1;
    property = property.slice(1);
  }
  // Return the fucntion to be used by sort
  return function (a, b) {
    const result =
      a[property] < b[property] ? -1 : a[property] > b[property] ? 1 : 0;
    return result * sortOrder;
  };
};

// Add a - in front of property to reverse sort order
const findBookList = function (user, listName) {
  return user.booklists.find(lists => lists.list === `${listName}`);
};

const sortBookList = function (user, listName, sortByProperty) {
  return findBookList(user, listName).books.sort(dynamicSort(sortByProperty));
};

const displayList = function (user, listName) {
  headingBookList.innerHTML = ''; // Clear book list title
  listCurrentBookList.innerHTML = ''; // Clear book list content
  const bookList = findBookList(user, listName);
  console.log(bookList);
  headingBookList.innerHTML = `${bookList.list}`;

  bookList.books.forEach(function (book) {
    const html = `
    <li class="book-listing" id="${book.id}">
          <img
            src="${book.cover}"
            alt=""
            class="book-cover"
          />
          <h3 class="book-title">
            <a
              href="${book.source}"
              >${book.title}${book.subtitle ? ` :${book.subtitle}` : ''}</a
            >
          </h3>
          <p class="author">
            by
            <a
              href="${book.authorSource}"
              >${book.author}</a
            >
          </p>
          <button class="genre-button">${book.genre}</button>
          <button class="purchased-button">I've Purchased!</button>
      </li>`;

    listCurrentBookList.insertAdjacentHTML('afterbegin', html);
  });
};

displayList(user0000, "Logan's List");

// ---- UI ----

// Seearch List
btnFind.addEventListener('click', function () {
  formListSearch.classList.toggle('hidden');
});

// Sort
btnSort.addEventListener('click', function () {
  listSearch.classList.toggle('hidden');
});

// Filter
btnFilter.addEventListener('click', function () {
  listFilter.classList.toggle('hidden');
});

// Add a book
btnAdd.addEventListener('click', function () {
  formAddBook.classList.toggle('hidden');
});

// Purchased Buttons
for (let i = 0; i < btnPurchased.length; i++) {
  btnPurchased[i].addEventListener('click', function () {
    // Set the specific listing to purchased
    document.getElementById(`i000${i}`).classList.toggle('purchased');
    // Style the children of the listing
    const numChildren = document.getElementById(`i000${i}`).childElementCount;
    // Book Title
    document
      .getElementById(`i000${i}`)
      .children[1].classList.toggle('purchased');
    // Modify purhcased button
    if (document.getElementById(`i000${i}`).classList.contains('purchased')) {
      document.getElementById(`i000${i}`).children[
        numChildren - 1
      ].textContent = 'Not Purchased';
    } else {
      document.getElementById(`i000${i}`).children[
        numChildren - 1
      ].textContent = "I've Purchased";
    }
    // Darken Containter
    document.getElementById(`i000${i}`).children[0].classList.toggle('darken');
    // Darken Tag
    document
      .getElementById(`i000${i}`)
      .children[numChildren - 2].classList.toggle('inactive-tag');
    document
      .getElementById(`i000${i}`)
      .children[1].classList.toggle('strike-through');
  });
}

document.querySelector('.book-list').addEventListener('click', function (e) {
  if (e.target && e.target.matches('button.purchased-button')) {
    const parent = e.target.parentNode;
    const numChildren = parent.childElementCount;

    // Change book listing's state
    parent.classList.toggle('purchased');

    // Modify the button text
    if (parent.classList.contains('purchased')) {
      parent.children[numChildren - 1].textContent = 'Not Purchased';
    } else {
      parent.children[numChildren - 1].textContent = "I've purchsed";
    }

    // Darken the tag
    parent.children[numChildren - 2].classList.toggle('inactive-tag');

    // Strike through the title;
    parent.children[1].classList.toggle('strike-through');

    console.log(numChildren);
  }
});

/*
User data structure

Fucntions:
- Have multiple users who can login and see their specific lsit\
- logout
- book lists are attached to user objects
- need to be able to add new lists
- 

Booklist data structure:
- Need to be able to sort the list 
- Need to be able to add and delete from the list
- Need to be able to filter list

Booklisting data sturcure

Functions
- Need to be able to track when the book was added



- EACH BOOKLIST NEEDS TO BE AN ARRAY OF OF BOOK OBJECTS
- USER IS AN OBJECT
- HOW ARE THE BOOKLISTS STORED INSIDE THE USER?

*/

const compare = function (a, b, property) {
  const bookProperty1 = '';
  const bookProperty2 = '';
  if (property === 'title') {
    bookProperty1 = a.title;
    bookProperty2 = b.title;
  }
  bookProperty1 < bookProperty1 ? -1 : 1;
  return 0;
};

// TODO: make sort option arrow flip direction when pressed
