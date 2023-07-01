//import Home from "./Home";
import Login from "./Login";
import Register from "./Register";
import "./style.scss";
import { BrowserRouter, Routes, Route, Navigate } from "react-router-dom";
//import { AuthContext } from "./context/AuthContext";

function App() {
  //const { currentUser } = useContext(AuthContext);

  /*const ProtectedRoute = ({ children }) => {
    if (!currentUser) {
      return <Navigate to="/login" />;
    }

    return children
  };
  */  

  return (
    <Register/>
  );
}

export default App;