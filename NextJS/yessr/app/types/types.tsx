export type Product = {
  id: number;
  img: string;
  detail: string;
  title: string;
  desc: string;
};

export enum MainPageType {
  HOME = 1,
  BEBIDAS = 2,
  COMIDAS = 3,
  OFERTAS = 4,
}

export type qntProductsType = { [key: number]: number };
