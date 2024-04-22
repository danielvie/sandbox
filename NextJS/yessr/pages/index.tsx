import { loadProducts } from "./api/products";
import Header from "../app/components/header";
import ListOfItens from "../app/components/list_of_itens";
import { Product, qntProductsType } from "@/app/types/types";
import "app/globals.css";
import { useState } from "react";
import FloatMenu from "@/app/components/float_menu";

export default function Home(props: { products: Product[] }) {
  // initializing dictionary
  const [qntProducts, setQntProducts] = useState<qntProductsType>({});
  const [toastMsg, setToastMsg] = useState("");

  // function to update qnt of items in list
  function updateQnt(id: number, value: number) {
    // criating update value
    let qnt_ = qntProducts[id] || 0;
    let update = { [id]: Math.max(qnt_ + value, 0) };

    // updating value of `qnt`
    setQntProducts({ ...qntProducts, ...update });
  }

  function updateToast(msg: string) {
    setToastMsg(msg);

    const toast = document.getElementById("toast");
    toast?.classList.remove("opacity-0");
    toast?.classList.add("opacity-100");

    setTimeout(() => {
      toast?.classList.remove("opacity-100");
      toast?.classList.add("opacity-0");
    }, 3000);
  }

  function handleOrder() {
    console.log("order: ", qntProducts);

    updateToast(`order: ${JSON.stringify(qntProducts)}`);
  }

  return (
    <main className="mb-36 flex min-h-screen min-w-[400px] flex-col items-center justify-between">
      <div
        id="toast"
        className="fixed left-1/2 top-3 z-50 w-11/12 -translate-x-1/2 transform rounded bg-blue-500 px-4 py-3 text-white opacity-0 shadow-lg transition duration-500 ease-in-out"
      >
        {toastMsg}
      </div>

      <Header></Header>
      <ListOfItens
        products={props.products}
        qntProducts={qntProducts}
        updateQnt={updateQnt}
      />
      <FloatMenu handleOrder={handleOrder} />
    </main>
  );
}

export async function getStaticProps() {
  // no lugar de ler api interna, estou lendo a funcao com a logica
  // diretamente do /api/products
  const jsonData = await loadProducts();

  // lendo api externa:
  // const res = await fetch('http://localhost:3000/api/staticdata')
  // const jsonData = await res.json()

  const objectData = JSON.parse(jsonData);

  return {
    props: objectData,
  };
}
