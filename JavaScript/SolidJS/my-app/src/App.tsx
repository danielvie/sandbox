import type { Component } from 'solid-js';

import logo from './logo.svg';
import styles from './App.module.css';
import { createSignal } from 'solid-js';

const App: Component = () => {

  const [count, setCount] = createSignal(2);
  
  function increment(value:number) {
    const new_value = Math.max(0, count() + value);
    setCount(new_value);
  }
  
  return (
    <div class={styles.App}>
      <header class={styles.header}>
        <img src={logo} class={styles.logo} alt="logo" />
        <p class="mt-20">
          Edit <code>src/App.tsx</code> and save to reload.
        </p>
        <div class="mt-5">
          <button class="bg-blue-400 px-4 rounded-md w-20" onclick={() => increment(-1)}>-</button>
          <button class="bg-blue-400 px-4 rounded-md ml-3 w-20" onclick={() => increment(1)}>+</button>
        </div>
        <div class="mt-10">{count()}</div>
      </header>
    </div>
  );
};

export default App;
