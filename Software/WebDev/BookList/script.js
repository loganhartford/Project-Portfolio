'use strict';

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

// Purchased Buttons
for (let i = 0; i < btnPurchased.length; i++) {
  btnPurchased[i].addEventListener('click', function () {
    // Set the specific listing to purchased
    document.getElementById(`000${i}`).classList.toggle('purchased');
    // Style the children of the listing
    const numChildren = document.getElementById(`000${i}`).childElementCount;
    // Book Title
    document
      .getElementById(`000${i}`)
      .children[1].classList.toggle('purchased');
    // Modify purhcased button
    if (document.getElementById(`000${i}`).classList.contains('purchased')) {
      document.getElementById(`000${i}`).children[numChildren - 1].textContent =
        'Not Purchased';
    } else {
      document.getElementById(`000${i}`).children[numChildren - 1].textContent =
        "I've Purchased";
    }
    document.getElementById(`000${i}`).children[0].classList.toggle('darken');
    document
      .getElementById(`000${i}`)
      .children[numChildren - 2].classList.toggle('inactive-tag');
  });
}

// TODO: make sort option arrow flip direction when pressed
