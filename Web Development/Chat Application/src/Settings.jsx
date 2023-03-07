import React, { useContext, useState } from "react";
import icon from "../src/img/photo.png";
import { Link, useNavigate } from "react-router-dom";
import { AuthContext } from "./context/AuthContext";
import { getDownloadURL, ref, uploadBytesResumable } from "firebase/storage";
import { auth, db, storage } from "./firebase";
import { v4 as uuid } from "uuid"
import { doc, updateDoc } from "firebase/firestore";
import { updateProfile, updateCurrentUser } from "firebase/auth";

const Settings = () => {
    const [err, setErr] = useState(false);
    const navigate = useNavigate();
    const {currentUser} = useContext(AuthContext);
    const [ text, setText ] = useState("");
    const [ img, setImg ] = useState(null);
    const [ blank, setBlank ] = useState(false);

    const handleSubmit = async (e) => {
      e.preventDefault();
      const displayName = e.target[0].value;

      console.log(currentUser.uid);

      try{
        if(img && text !== ""){
        setBlank(false);
        const storageRef = ref(storage,  uuid());

        const uploadTask = uploadBytesResumable(storageRef, img);

        uploadTask.on(
            (error) => {

            },
            () => {
                getDownloadURL(uploadTask.snapshot.ref).then(async (downloadURL) => {
                    await updateDoc(doc(db, "users", currentUser.uid),{
                        displayName,
                        photoURL: downloadURL,
                    })
                    await updateProfile(currentUser, {
                        displayName,
                        photoURL: downloadURL,
                    })
                })
            }
        )
        navigate("/");
      }
      else if(img === null && text !== ""){
        setBlank(false);
        await updateDoc(doc(db, "users", currentUser.uid), {
            displayName,
        })
        await updateProfile(currentUser, {
            displayName,
        })
        navigate("/");
      }
      else if(img && text === "")
      {
        setBlank(false);
        const storageRef = ref(storage, uuid());
        const uploadTask = uploadBytesResumable(storageRef, img);

        uploadTask.on(
            (error) => {

            },
            () => {
                getDownloadURL(uploadTask.snapshot.ref).then(async (downloadURL) => {
                    await updateDoc(doc(db, "users", currentUser.uid),{
                        photoURL: downloadURL,
                    })
                    await updateProfile(currentUser, {
                        photoURL: downloadURL,
                    })
                })
            }
        )
      }
      else{
        setBlank(true);
      }

      setText("");
      setImg(null);
    }
    catch(err){
        setErr(true);
    }
    console.log(currentUser);
  };
    return(
        <div className="formContainer">

            <div className="formWrapper">
                <span className="logo">Settings</span>
                <span className="title">Update Profile</span>
                <form onSubmit={handleSubmit}>
                    <input type="text" placeholder="New display name" onChange={e=>setText(e.target.value)} value={text}/>
                    <input style={{display: "none"}} type="file" id="file" onChange={e=>setImg(e.target.files[0])}/>
                    <label htmlFor="file" placeholder="https://cdn-icons-png.flaticon.com/512/456/456212.png">
                        <img src={icon} alt="" />
                        <span>New avatar</span>
                    </label>
                    <button>Save Changes</button>
                    {err && <span>Something went wrong</span>}
                    {blank && <span>No changes have been made!</span>}
                </form>
                <p>Don't want to make any changes? <Link to="/">Return Home</Link></p>
            </div>
        </div>
    )
}

export default Settings