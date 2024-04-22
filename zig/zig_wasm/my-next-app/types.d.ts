declare module "loadWasm" {
  function loadWasm(): Promise<{
    add: (a: number, b: number) => number;
    fibonacci: (n: number) => number;
  }>;
  export { loadWasm };
}
