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

// Body
const body = document.querySelector('body');

// Buttons
const btnFind = document.querySelector('.find-button');
const btnSort = document.querySelector('.sort-button');
const btnFilter = document.querySelector('.filter-button');
const btnPurchased = document.querySelectorAll('.purchased-button');
const btnAdd = document.querySelector('.add-button');
const btnAddBook = document.querySelector('.add-book-form-button-add');
const btnCancelAddBook = document.querySelector('.add-book-form-button-cancel');
const btnFindList = document.querySelector('.find-list-button');
const btnSortTitle = document.querySelector('.sort-title-button');
const btnSortAuthor = document.querySelector('.sort-author-button');
const btnSortDate = document.querySelector('.sort-dateAdded-button');

// Forms
const formListSearch = document.querySelector('.list-search-form');
const formAddBook = document.querySelector('.add-book-form');

// Form Field
const fieldFindListName = document.querySelector('.find-list-list-name');
const fieldAddBookTitle = document.querySelector('.add-book-form-title');
const fieldAddBookSubTitle = document.querySelector('.add-book-form-sub-title');
const fieldAddBookAuthor = document.querySelector('.add-book-form-author');
const fieldAddBookGenre = document.querySelector('.add-book-form-genre');
const fieldAddBookSource = document.querySelector('.add-book-form-source');

// Lists
const listSearch = document.querySelector('.sort-list');
const listFilter = document.querySelector('.filter-list');
const listCurrentBookList = document.querySelector('.book-list');
const listSortList = document.querySelector('.sort-list');

// Headings
const headingBookList = document.querySelector('.list-name');

// ---- Paramenters ----
let currentUser = user0000;
let currentBookList = "Logan's List";

// ---- Fucntions ----

const dynamicSort = function (property) {
  let sortOrder = 1; // Normal sort order
  // Reverse sort order
  if (property[0] === '-') {
    sortOrder = -1;
    property = property.slice(1);
  }
  // Return the fucntion to be used by sort
  // Sorting by date untested, need to try with manually added date
  return function (a, b) {
    if (property === 'dateAdded') {
      const result =
        new Date(a[property]) < new Date(b[property])
          ? -1
          : new Date(a[property]) > new Date(b[property])
          ? 1
          : 0;
      return result * sortOrder;
    }
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
  // find the book list, if empty, take first
  const bookList = findBookList(user, listName);

  // if listName is invalid
  if (!bookList?.list) {
    alert('Invalid List Name');
    return 0;
  }
  headingBookList.innerHTML = ''; // Clear book list title
  listCurrentBookList.innerHTML = ''; // Clear book list content

  headingBookList.innerHTML = `${bookList?.list}`;

  bookList?.books.forEach(function (book) {
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
              target="_blank"
              >${book.title}${book.subtitle ? ` :${book.subtitle}` : ''}</a
            >
          </h3>
          <p class="author">
            by
            <a
              href="${book.authorSource}"
              target="_blank"
              >${book.author}</a
            >
          </p>
          <button class="genre-button">${book.genre}</button>
          <button class="purchased-button">I've Purchased!</button>
      </li>`;

    listCurrentBookList.insertAdjacentHTML('beforeend', html);
  });
  currentBookList = listName;
  return 1;
};

sortBookList(currentUser, currentBookList, 'dateAdded');
displayList(currentUser, currentBookList);

// ---- UI ----

// Finding a list
btnFindList.addEventListener('click', function (e) {
  e.preventDefault();
  const findListName = fieldFindListName.value;
  const findListSuccess = displayList(currentUser, findListName);

  if (findListSuccess) {
    e.target.parentNode.classList.toggle('hidden');
    formListSearch.reset();
  }
});

// Seearch List
btnFind.addEventListener('click', function () {
  formListSearch.classList.toggle('hidden');
});

// Sort
btnSort.addEventListener('click', function () {
  listSearch.classList.toggle('hidden');
});

// Sort by title
const upArrow = '&#8593';
const downArrow = '&#8595';
listSortList.addEventListener('click', function (e) {
  // Select current button
  let button;
  if (e.target.classList.contains('sort-title-button')) button = btnSortTitle;
  if (e.target.classList.contains('sort-author-button')) button = btnSortAuthor;
  if (e.target.classList.contains('sort-dateAdded-button'))
    button = btnSortDate;
  const buttonType = e.target.classList[1].split('-')[1];

  // Unpress other sort buttons
  let buttons = [btnSortTitle, btnSortAuthor, btnSortDate];
  buttons.forEach(function (btn) {
    if (btn != button) {
      btn.classList.remove('sort-filter-pressed');
    }
  });

  // Unsorted
  if (
    button.innerHTML.includes('↑') &&
    !button.classList.contains('sort-filter-pressed')
  ) {
    sortBookList(currentUser, currentBookList, buttonType);
    displayList(currentUser, currentBookList);
    button.classList.add('sort-filter-pressed');
  }
  // Sorted ↑
  else if (
    button.innerHTML.includes('↑') &&
    button.classList.contains('sort-filter-pressed')
  ) {
    sortBookList(currentUser, currentBookList, `-${buttonType}`);
    displayList(currentUser, currentBookList);
    button.innerHTML = `${button.innerHTML.slice(0, -1)}${downArrow}`;
  }
  // Sorted ↓
  else if (button.innerHTML.includes('↓')) {
    button.innerHTML = `${button.innerHTML.slice(0, -1)}${upArrow}`;
    button.classList.remove('sort-filter-pressed');
    // go back to being sorted by date added
  }
});

// Filter
btnFilter.addEventListener('click', function () {
  listFilter.classList.toggle('hidden');
});

// Purchased buttons
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
  }
});

// Add a book
btnAdd.addEventListener('click', function () {
  formAddBook.classList.toggle('hidden');
});

btnAddBook.addEventListener('click', function (e) {
  e.preventDefault();
  // Read in data from form
  const addTitle = fieldAddBookTitle.value;
  const addSubTitle = fieldAddBookSubTitle.value;
  const addAuthor = fieldAddBookAuthor.value;
  const addGenre = fieldAddBookGenre.value;
  const addSource = fieldAddBookSource.value;

  const newBook = {
    title: addTitle,
    subtitle: addSubTitle,
    author: addAuthor,
    authorSource: '',
    genre: addGenre,
    source: addSource,
    cover: 'img/build.jpg', // FIXME:
    dateAdded: Date(),
    id: `000${findBookList(currentUser, currentBookList).books.length - 1}`,
  };

  findBookList(currentUser, currentBookList).books.unshift(newBook);
  displayList(currentUser, currentBookList);
  formAddBook.reset();
  formAddBook.classList.add('hidden');
});

btnCancelAddBook.addEventListener('click', function (e) {
  e.preventDefault();
  formAddBook.reset();
  formAddBook.classList.add('hidden');
});

// Close open menus
body.addEventListener('click', function () {});

// TODO: make sort option arrow flip direction when pressed
