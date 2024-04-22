import Image from 'next/image'

function ListOfItens() {
    return (
        <>
            <div className='grid grid-cols-12 gap-x-0 max-w-2xl shadow-md shadow-black'>
                <div className='col-span-4'>
                    <Image src="https://www.themealdb.com/images/media/meals/tvttqv1504640475.jpg" alt="bla" width={200} height={200}/>
                </div>
                <div className='col-span-8 p-4 font-mono'>
                    <p className='text-2xl'>Massaman Beef</p>
                    <p className='text-gray-700'>R$ 10,00</p>
                </div>
                
            </div>
        </>
    )
}

export default ListOfItens