import path from "path";
import { promises as fs } from "fs";
import { NextApiRequest, NextApiResponse } from "next/types";
import { Product } from "@/app/types/types";
// import { Product } from "../types/types";

export async function loadProducts() {
  //Find the absolute path of the json directory
  const jsonDirectory = path.join(process.cwd(), "json");

  //Read the json data file data.json
  const fileContents = await fs.readFile(jsonDirectory + "/data.json", "utf8");

  return fileContents;
}

export async function loadProduct(productId: number) {
  const fileContentsJson = await loadProducts();

  const prod = await JSON.parse(fileContentsJson).products.find(
    (prod: Product) => prod.id == productId
  );

  return JSON.stringify(prod);
}

export default async function Products(
  _req: NextApiRequest,
  res: NextApiResponse
) {
  const fileContents = await loadProducts();

  //Return the content of the data file in json format
  res.status(200).json(fileContents);
}
