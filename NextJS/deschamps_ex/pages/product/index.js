import Link from "next/link";

function ProductList( { productId = 100 } ) {
    return (
        <>
            <Link href="/">
                <a>Home</a>
            </Link>
            <Link href="/product/1">
                <a> <h2>Product 1</h2> </a>
            </Link>
            <Link href="/product/2">
                <a> <h2>Product 2</h2> </a>
            </Link>
            <Link href="/product/3" replace>
                <a> <h2>Product 3</h2> </a>
            </Link>
            <Link href={`/product/${productId}`}>
                <a> <h2>Product {productId}</h2> </a>
            </Link>
        </>
    )
}

export default ProductList;