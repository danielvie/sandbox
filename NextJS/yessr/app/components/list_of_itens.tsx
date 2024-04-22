import { useState } from "react";
import Image from "next/image";
import { Product, qntProductsType } from "../types/types";
import { FaPlus, FaMinus, FaShoppingCart } from "react-icons/fa";

function ListOfItens(props: {
  products: Product[];
  qntProducts: qntProductsType;
  updateQnt: (id: number, add: number) => void;
}) {
  const products = props.products;
  const [qnt, setQnt] = useState(0);

  const funClick = (id: number, add: number) => {
    setQnt(qnt + add);
    props.updateQnt(id, add);
  };

  return (
    <>
      <div className="flex flex-col gap-3 px-2">
        {products.map((prod) => (
          <div
            key={prod.id}
            className="flex h-[128px] items-center justify-between rounded bg-white shadow-md shadow-gray-400"
          >
            <div className="hidden overflow-hidden min-[320px]:block">
              <Image
                className="h-[128px]"
                src={prod.img}
                alt="bla"
                width={150}
                height={150}
              />
            </div>
            <div className="w-full p-3">
              <h2 className="mb-2 text-xl">{prod.title}</h2>
              <p className="text-sm text-gray-500">R$ 10,00</p>

              <div className="m-2 flex justify-end gap-2">
                <button
                  onClick={() => funClick(prod.id, -1)}
                  className="rounded-md bg-blue-500 p-2 text-white"
                >
                  <FaMinus />
                </button>
                <div className="flex items-center justify-center px-2 text-2xl text-gray-500">
                  <div className="relative">
                    <span className="absolute -right-3 -top-1/2 justify-center rounded-md border-2 border-white bg-sky-600 px-[7px] font-mono text-[8pt] leading-5 text-white">
                      {props.qntProducts[prod.id] || ""}
                    </span>
                    <FaShoppingCart />
                  </div>
                </div>
                <button
                  onClick={() => funClick(prod.id, 1)}
                  className="rounded-md bg-blue-500 p-2 text-white"
                >
                  <FaPlus />
                </button>
              </div>
            </div>
          </div>
        ))}
      </div>
    </>
  );
}

export default ListOfItens;
