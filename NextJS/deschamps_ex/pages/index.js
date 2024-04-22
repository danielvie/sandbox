import { useState } from 'react'
import Link from "next/link";
import { useRouter } from "next/router";

function Home()
{
    const router = useRouter()

    const handleClick = () => {
        console.log("Placing your order")
        router.push('/product') // can also be:: replace
    }
    return (
        <div>
            <h2>Home Page</h2>
            <Link href='/blog'>
                <a>Blog</a>
            </Link>
            <Link href='/product'>
                <a>Product</a>
            </Link>
            <button onClick={handleClick}>
                Place Order
            </button>
            <Contador/>
        </div>
    )
}

function Contador()
{
    const [contador, setContador] = useState(1)
    
    function AdicionarContador()
    {
        setContador(contador + 1)
    }
    
    return (
        <div>
            <div className='conta'>{contador}</div>
            <button onClick={AdicionarContador}>adicionar</button>
        </div>
    )
}

export default Home