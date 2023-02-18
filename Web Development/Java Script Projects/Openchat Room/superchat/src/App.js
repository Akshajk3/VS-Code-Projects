import React from 'react';
import './App.css';

import firebase from 'firebase/compat/app'
import { initializeApp } from "firebase/app";
import { getAuth } from "firebase/auth";
import { useAuthState } from 'react-firebase-hooks/auth'
import { useCollectionData } from 'react-firebase-hooks/firestore'
import { getFirestore, collection, getDocs } from 'firebase/firestore/lite';

const firebaseConfig = {
  apiKey: "AIzaSyDS2mLI-YuoAiEBgVX0QG2125c7jv-iybQ",
  authDomain: "real-time-texting-demo.firebaseapp.com",
  projectId: "real-time-texting-demo",
  storageBucket: "real-time-texting-demo.appspot.com",
  messagingSenderId: "1088642878295",
  appId: "1:1088642878295:web:178f76c74d0c3d74f24c12",
  measurementId: "G-Z11L1Y9YQJ"
};

const app = initializeApp(firebaseConfig);
const auth = getAuth(app);
const firestore = getFirestore(app);

function App() {

  const [user] = useAuthState(auth);

  return (
    <div className="App">
      <header className="App-header">
        
      </header>

      <section>
        {user ? <ChatRoom /> : <SignIn />}
      </section>
    </div>
  );
}

function SignIn()
{

}

function ChatRoom()
{

}

export default App;
