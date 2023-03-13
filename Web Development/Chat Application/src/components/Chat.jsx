import React, { useContext } from "react";
import Cam from "./img/video-camera.png"
import Add from "./img/add-user.png"
import More from "./img/list.png"
import Messages from "./Messages";
import Input from "./Input";
import { ChatContext } from "../context/ChatContext";
import { Link } from "react-router-dom";

const Chat = () => {
    const {data} = useContext(ChatContext);
    var displayName = "";

    if(data.user?.displayName == null)
    {
        displayName = "Please Select a User!";
    }
    else
    {
        displayName = data.user?.displayName;
    }

    return (
        <div className="chat">
            <div className="chatInfo">
                <span>{displayName}</span>
                <div className="chatIcons">
                    <img src={Cam} alt="" />
                    <img src={Add} alt="" />
                    <Link to="/settings"><img src={More} alt=""/></Link>
                </div>
            </div>
            <Messages/>
            <Input/>
        </div>
    )
}

export default Chat