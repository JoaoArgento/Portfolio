import {useState, useRef, useEffect} from "react";
import {responses} from "../Data/TerminalResponses.js"
import {audioSrcByName} from "../Data/AudiosPath.js"

export default function MatrixTerminal(props)
{
    const [lines, SetLines] = useState([])
    const [input, SetInput] = useState("");
    const inputRef = useRef(null);
    const audioRef = useRef(null);

    useEffect(() =>
    {
        if (inputRef.current)
        {
            inputRef.current.focus();
        }

    }, [input])


    const HandleKeyDown = (event) =>
    {
        if (event.key == "Enter")
        {
            const command = input.trim().toLowerCase();
            const commandWithoutSpace = command.replace(/[^\w]/g, "");

            let response = responses[commandWithoutSpace];
            audioRef.current.src = null;

            if (response !== undefined)
            {
                SetInput("");
                SetLines((prev)=>[...prev, `> ${input}`, response])
                inputRef.current.value = "";
                return;
            }

            switch(commandWithoutSpace)
                {
                    case "clear":
                        SetLines([]);
                        SetInput("");
                        response = "Limpando!"
                        break;
                    // case "instakill": 
                    //     response = "INSTA KILL!"
                    //     audioRef.current.src = audioSrcByName["instakill"]
                    //     break;
                    // case "kaboom":
                    //     response = "KABOOOOM!"
                    //     audioRef.current.src = audioSrcByName["kaboom"]
                    //     break;
                    // case "fetchme": 
                    //     response = "FETCH ME THEIR SOULS!";
                    //     audioRef.current.src = audioSrcByName["fetchme"]
                    //     break;
                    case "exit":
                        response = "Saindo!";
                        props.DisableMatrixMode();
                        break;
                    default:
                        response = `Comando "${command}" não reconhecido. Digite 'help'.`;
                        break
                }

            if (audioRef.current.src != null)
            {
                audioRef.current.play();
            }
           
            SetInput("");
            SetLines((prev)=>[...prev, `> ${input}`, response])
            inputRef.current.value = "";
            
        }
        else if (event.key == "Backspace") 
        {
            SetInput((prev) => prev.slice(0, prev.length -1))
    
        }
        else if (event.key.length === 1)
        {
            SetInput((prev) => prev + event.key);
        }
    }

    return <div onClick = {() => {inputRef.current?.focus()}}className = "relative w-full h-full bottom-10 left-10 text-green-400 font-mono text-sm z-50">
        {lines.map((line, index) =>
        {
            return <div key = {index}>
                {line}
            </div>

        })}
        <audio ref = {audioRef} src = {null}></audio>
        <div>
            <span className="text-white">{">"}</span>

                    <input ref = {inputRef}
                onKeyDown={HandleKeyDown}
                className="absolute pointer-events-none border-none outline-none focus:outline-none bg-transparent"
                />
        </div>

      
    </div>
}