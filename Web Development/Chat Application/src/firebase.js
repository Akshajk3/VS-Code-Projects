import { initializeApp } from "firebase/app";
import { getAuth } from "firebase/auth"

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
const app = initializeApp(firebaseConfig);
const auth = getAuth()