import React, { useContext, useEffect, useRef } from "react";
import { AuthContext } from "../context/AuthContext";
import { ChatContext } from "../context/ChatContext";

const Message = ({message}) => {

    const {currentUser} = useContext(AuthContext);
    const {data} = useContext(ChatContext);

    const ref = useRef();
    
    useEffect(() => {
        ref.current?.scrollIntoView({behavior:"smooth"})
    }, [message]);

    const month = message.date.toDate().toDateString().substring(0, 10);
    const time = message.date.toDate().toLocaleTimeString('en-US').substring(0, 5);
    const pm = message.date.toDate().toLocaleTimeString('en-US').substring(8, 11);

    const handleClick = (e) => {
        if(e.type === 'click')
        {
            console.log("left click");
        }
    }

    return (
        <div ref={ref} className={`message ${message.senderId === currentUser.uid && "owner"}`}>
            <div className="messageInfo">
                <img src= {message.senderId === currentUser.uid ? currentUser.photoURL : data.user.photoURL} alt="" />
                <span>{month} </span>
                <span>at {time} {pm}</span>
            </div>
            <div className="messageContent" onClick={handleClick}>
                <p>{message.text}</p>
                {message.img && <img src={message.img} alt="" />}
            </div>
        </div>
    )
}

export default Message