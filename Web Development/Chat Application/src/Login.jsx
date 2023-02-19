import React from "react";
import icon from "../src/img/photo.png"

const Login = () => {
    return(
        <div className="formContainer">

            <div className="formWrapper">
                <span className="logo">Giga Chat</span>
                <span className="title">Register</span>
                <form>
                    <input type="email" placeholder="Email"/>
                    <input type="password" placeholder="Password"/>
                    <input style={{display: "none"}} type="file" id="file"/>
                    <button>Sign In</button>
                </form>
                <p>You don't have an account? Register</p>
            </div>
        </div>
    )
}

export default Login