import React, { useContext, useEffect } from "react";
import { signOut } from "firebase/auth";
import { auth, db } from "../firebase";
import { AuthContext } from "../context/AuthContext";
import { doc, onSnapshot } from "firebase/firestore";

const Navbar = () => {
    const {currentUser} = useContext(AuthContext);

    return (
        <div className="navbar">
            <span className="logo">Giga Chat</span>
            <div className="user">
                <img src={currentUser.photoURL} alt=""/>
                <span>{currentUser.displayName}</span>
                <button onClick={()=>signOut(auth)}>Logout</button>
            </div>
        </div>
    )
}

export default Navbar