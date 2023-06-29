// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyDg-3fiffGt0bQkSSprWRNJgiku0lTodJw",
  authDomain: "app-challenge-2023.firebaseapp.com",
  projectId: "app-challenge-2023",
  storageBucket: "app-challenge-2023.appspot.com",
  messagingSenderId: "154043150613",
  appId: "1:154043150613:web:847d6ce0ae10f0a782791c",
  measurementId: "G-YH0CWKPZ2X"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);