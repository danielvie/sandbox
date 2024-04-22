import { useState } from 'react';
import Image from 'next/image'
import { Product } from '../types/types'
import { FaPlus, FaMinus, FaShoppingCart } from 'react-icons/fa';

function ListOfItens(props: {products:Product[]}) {
    const products = props.products
    const [qnt, setQnt] = useState(0)

    const funClick = (add:number) => {
        setQnt(qnt + add)
    }

    return (
        <>
            <div className='flex flex-col gap-3 px-2'>
                {products.map((prod) => ( 
                    <div key={prod.id} className='flex h-[128px] justify-between items-center bg-white rounded shadow-md shadow-gray-400'>
                        <div className='overflow-hidden hidden min-[320px]:block'>
                            <Image className='h-[128px]' src={prod.img} alt="bla" width={150} height={150}/>
                        </div>
                        <div className='w-full p-3'>
                            <h2 className='text-xl mb-2'>{prod.title}</h2>
                            <p className='text-sm text-gray-500'>{qnt}: R$ 10,00</p>

                            <div className='flex justify-end m-2'>
                                <button onClick={() => funClick(-1)} 
                                    className='rounded-md p-2 bg-blue-500 text-white'><FaMinus/></button>
                                <div className='text-2xl justify-center items-center flex text-gray-500 px-2'>
                                    <FaShoppingCart/>
                                </div>
                                <button onClick={() => funClick(1)} 
                                    className='rounded-md p-2 bg-blue-500 text-white'><FaPlus/></button>
                            </div>
                        </div>
                    </div>
                 ))}
            </div>
        </>
    )
}

export default ListOfItens