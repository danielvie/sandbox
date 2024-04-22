import { loadProducts } from './api/products';
import Header from './components/header'
import ListOfItens from './components/list_of_itens'
import { Product } from './types/types';

export default function Home(props: {products:Product[]}) {
  return (
    <main style={{minWidth:400}} className="flex min-h-screen flex-col items-center justify-between mb-36">
      <Header></Header>
      <ListOfItens products={props.products}/>
  </main>
  )
}

export async function getStaticProps() {

  // no lugar de ler api interna, estou lendo a funcao com a logica
  // diretamente do /api/products
  const jsonData = await loadProducts()

  // lendo api externa:
  // const res = await fetch('http://localhost:3000/api/staticdata')
  // const jsonData = await res.json()

  const objectData = JSON.parse(jsonData);

  return {
      props: objectData
  }

}