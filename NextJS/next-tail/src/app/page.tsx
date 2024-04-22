import { loadProducts } from '@/api/products'
import Header from '@/components/header'
import ListOfItens from '@/components/list_of_itens'

export default function Home() {
  return (
    <main className="flex min-h-screen flex-col items-center justify-between p-24">
      <Header></Header>
      <ListOfItens/>
    </main>
  )
}
