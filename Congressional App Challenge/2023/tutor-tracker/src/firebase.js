// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAuth } from "firebase/auth";
import { getStorage } from "firebase/storage";
import { getFirestore } from "firebase/firestore";
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
export const app = initializeApp(firebaseConfig);
export const auth = getAuth();
export const storage = getStorage();
export const db = getFirestore();