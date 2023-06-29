import React, {useState}  from "react";
import icon from "../src/img/picture.png";


const Register = () => {

    const [err, setErr] = useState(false);
    //const navigate = useNavigate();
    
    /*const handleSubmit = async(e) => {
        e.preventDefault();
        const displayName = e.target[0].value;
        const email = e.target[1].value;
        const password = e.target[2].value;
        const file = e.target[3].files[0];
    }*/

    return (
        <div className="formContainer">
            <div className="formWrapper">
                <span className="logo">Tutor Finder</span>
                <span className="title">Register</span>
                <form>
                    <input type="text" placeholder="Display Name"/>
                    <input type="email" placeholder="Email"/>
                    <input type="password" placeholder="Password"/>
                    <input style={{display:"none"}} type="file" id="file"/>
                    <label htmlFor="file" placeholder="https://cdn-icons-png.flaticon.com/512/456/456212.png">
                        <img src={icon} alt="" />
                        <span>Add an avatar</span>
                    </label>
                    <button>Sign Up</button>
                    {err && <span>Something went wrong</span>}
                </form>
                <p>You do have an account? Login</p>
            </div>
        </div>
    )
}

export default Register;