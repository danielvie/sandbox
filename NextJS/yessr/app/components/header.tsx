import { red } from "@mui/material/colors";
import Image from "next/image";
import { FaMoneyBillWave } from "react-icons/fa";

enum MenuOpt {
    DRINKS = 0,
    FOOD = 1,
    DEALS = 2,
}

function Header() {
    const funMenu = (opt:MenuOpt) => {
        console.log(`selecionada a opcao ${opt}`)
    }
    return (
        <>
            <div className="w-full"> 
                <div className="flex justify-center">
                    <Image src="/images/logo_restaurant.png" alt="" width={200} height={200} />
                </div>
                <div className="grid text-white grid-cols-12 w-full text-center mb-4 bg-gray-500">
                    <button onClick={()=>funMenu(MenuOpt.DRINKS)} className="col-span-4 py-4 bg-fuchsia-500">DRINKS</button>
                    <button onClick={()=>funMenu(MenuOpt.FOOD)} className="col-span-4 py-4 bg-fuchsia-800">FOOD</button>
                    <button onClick={()=>funMenu(MenuOpt.DEALS)} className="col-span-4 py-4 bg-blue-500">DEALS</button>
                </div>
            </div>
        </>
    )
}

export default Header