import { initializeApp } from "firebase/app";
import { getAuth } from "firebase/auth";
import { getStorage } from "firebase/storage";
import { getFirestore } from "firebase/firestore";

const firebaseConfig = {
  apiKey: "AIzaSyDS2mLI-YuoAiEBgVX0QG2125c7jv-iybQ",
  authDomain: "real-time-texting-demo.firebaseapp.com",
  projectId: "real-time-texting-demo",
  storageBucket: "real-time-texting-demo.appspot.com",
  messagingSenderId: "1088642878295",
  appId: "1:1088642878295:web:178f76c74d0c3d74f24c12",
  measurementId: "G-Z11L1Y9YQJ"
};

// Initialize Firebase
export const app = initializeApp(firebaseConfig);
export const auth = getAuth();
export const storage = getStorage();
export const db = getFirestore()