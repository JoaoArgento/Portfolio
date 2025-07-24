import { FaGithub, FaLinkedin } from "react-icons/fa"
import { motion } from "framer-motion"


export default function Footer()
{
    return <footer className = "bg-black text-gray-400 text-center py-6 text-sm">
        &copy; {new Date().getFullYear()} - João Pedro. Todos os direitos reservados.

    <div className="flex justify-center gap-6 mt-4 text-2xl">
            <motion.a
            href="https://www.linkedin.com/in/joão-pedro-argento-garcia-501083288/"
            target="_blank"
            rel="noopener noreferrer"
            whileHover={{ scale: 1.2, y: -5 }}
            transition={{ type: "spring", stiffness: 300 }}
            className="hover:text-indigo-400 transition"
            >
            <FaLinkedin />
            </motion.a>

            <motion.a
            href="https://github.com/JoaoArgento"
            target="_blank"
            rel="noopener noreferrer"
            whileHover={{ scale: 1.2, y: -5 }}
            transition={{ type: "spring", stiffness: 300 }}
            className="hover:text-indigo-400 transition"
            >
            <FaGithub />
            </motion.a>
        </div>
    </footer>
}