import React, {useRef, useEffect} from "react";


export default function MatrixRain({isActive})
{
  const canvasRef = useRef(null);

    useEffect(() =>
    {
        const canvas = canvasRef.current;
        const ctx = canvas.getContext("2d");
        let animationId = 0;
        
        const resizeCanvas = () =>
        {
            canvas.width = window.innerWidth;
            canvas.height = window.innerHeight;
        }
        
        resizeCanvas();

        window.addEventListener("resize", resizeCanvas);

        const letters = 'アァイィウウェエカキクケコサシスセソタチツテトナニヌネノ0123456789'
        const fontSize = 16;
        const columns = Math.floor(window.innerWidth /fontSize);
        const drops = Array(columns).fill(1);

        const Draw = () =>
        {
            ctx.fillStyle = "rgba(0, 0, 0, 0.05)";
            ctx.fillRect(0, 0, canvas.width, canvas.height);
            ctx.fillStyle = "rgba(0, 255, 0, 0.2)"
            ctx.font = `${fontSize}px monospace`;

            for (let i = 0; i < drops.length; i++)
            {
                const text = letters.charAt(Math.floor(Math.random() * letters.length))
                ctx.fillText(text, i * fontSize, drops[i] * fontSize);

                if (drops[i] * fontSize > canvas.height && Math.random() > 0.975)
                {
                    drops[i] = 0;
                }
                drops[i]++;
            }

            animationId = requestAnimationFrame(Draw);
        }

        if (isActive)
        {
            Draw();
        }

        return () => {
            cancelAnimationFrame(animationId);
            window.removeEventListener("resize", resizeCanvas);
        }
    }, [isActive])

    return <canvas ref = {canvasRef}
            className= {`absolute top-0 left-0 w-full h-full transition-opacity duration-500 ${isActive ? "opacity-100" : "opacity-0"}`}
    >

    </canvas>

  
}